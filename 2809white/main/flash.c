#include "DSP280x_Device.h"     // DSP280x Headerfile Include File
#include "DSP280x_Examples.h"   // DSP280x Examples Include File

void InitFlashAPI2808(void)
{
	Uint16 VersionHex;
	float  Version;
	
	Flash_CPUScaleFactor = SCALE_FACTOR;

	VersionHex = Flash_APIVersionHex();
	//TxPrintf("\nVersionHex %x\n",VersionHex);
	if(VersionHex != 0x0302)
	{
		TxPrintf("\nFlash API Error!!\n");
		asm("	ESTOP0");
	}

	Version = Flash_APIVersion();
	if(Version != (float)3.02)
	{
		TxPrintf("\nFlash API Error!!\n");
		asm("	ESTOP0");
	}
	
}

FLASH_ST FlashStatus;
FLASH_ST ProgStatus;
void DeleteAllFlash(void)
{
	Uint16 Status;

	Status = Flash_Erase((SECTORB | SECTORC | SECTORD), &FlashStatus);
	while(Status != STATUS_SUCCESS);
	TxPrintf("\n  Delete All Sector OK!!\n");
	
}
void DeleteSecletFlash(void)
{
	Uint16 Status;
	char RcvData;
	Uint16 DeleteSector;

	RcvData = SCIx_RxChar();
	SCIx_TxChar(RcvData);
	if(RcvData != ' ')
	{
		TxPrintf("\nIllegal Command!!\n");
		return;
	}
	RcvData = SCIx_RxChar();
	SCIx_TxChar(RcvData);
	switch(RcvData)
	{
		case 'b':
		case 'B':
			DeleteSector = SECTORB;
			TxPrintf("\n  Delete SectorB.\n");
			break;
		case 'c':
		case 'C':
			DeleteSector = SECTORC;
			TxPrintf("\n  Delete SectorC.\n");
			break;
		case 'd':
		case 'D':
			DeleteSector = SECTORD;
			TxPrintf("\n  Delete SectorD.\n");
			break;
		default:
			TxPrintf("\nWrong Sector Select!!\n");
			return;
	}

	Status = Flash_Erase(DeleteSector, &FlashStatus);
	while(Status != STATUS_SUCCESS);
	TxPrintf("\n  Delete Sector OK!!\n");
	
}
void UserFlashErase_DownloadPrm(void)
{
	TxPrintf("\n  User Sector Flash Erase.\n");
	DeleteAllFlash();
	InitUserHexDownVariable();
	TxPrintf("\n  Send User Program *.Hex\n");

	SCIx_TxChar(BELL);
	SCIx_TxChar(BELL);

	if(UserPrmHexFileDownLoading(0)) 
		SCIx_TxString("\nDownLoading Success");
    else 
		SCIx_TxString("\nDownLoading Failure"); 
	
	SCIx_TxString("\n Go To User Program !!\n\r");

	UserProgramStart();

	
}
Uint32 UserPrgAddress = (Uint32)0x3e8000;
void UserProgramStart(void)
{
	void (*UserPrg)(void) = (void(*)(void))UserPrgAddress;
	
	DINT;

	UserPrg();
}


void InitUserHexDownVariable(void)
{
    memset((void *)&DownLoadingHex, 0x00, sizeof(HEX_FIELD));
}

#pragma CODE_SECTION(UserPrmHexFileDownLoading,"ramfuncs1");
Uint16 Temp[10];
Uint16 UserPrmHexFileDownLoading(char StartState)
{
    int i;
    Uint16  Status;
    Uint16	CheckSum;

	Flash_CPUScaleFactor = SCALE_FACTOR;
	
    while( !DownLoadingHex.Status.Bit.bit0 && !DownLoadingHex.Status.Bit.bit1 ){  
        if( !StartState ) while( SCIx_RxChar() != ':' );
        StartState = 0;
        DownLoadingHex.Checksum = CheckSum = 0;
        //      Data Length
        DownLoadingHex.DataLength = (Uint16)HEXDOWN_AsciiConvert(2);
        //      Offset Address
        DownLoadingHex.Address.Word.Low = (Uint16)HEXDOWN_AsciiConvert(4);
        //      Data Type
        DownLoadingHex.RecordType = (Uint16)HEXDOWN_AsciiConvert(2);
    
        switch (DownLoadingHex.RecordType) {
        //      DATA  
        case 0x00:
            // in this point, it will be able to write the data to the fresh rom directly.
            for( i = 0; i < DownLoadingHex.DataLength; i += 2){
                if( ( DownLoadingHex.DataLength - i ) == 1 ) Temp[0] = (Uint16)HEXDOWN_AsciiConvert(2);
                else Temp[0] = (Uint16)HEXDOWN_AsciiConvert(4);
                Status = Flash_Program((Uint16 *)DownLoadingHex.Address.Long,Temp,1,&ProgStatus);
                if(Status != STATUS_SUCCESS) 
                {
                    SCIx_TxString("\nFlashError");
                    return FALSE;
                }
                DownLoadingHex.Address.Long ++;
//                if(DownLoadingHex.FrameNumber == 0x42) buf[i] = temp[0]; 
            }
            break;
        //      End Of File 
        case 0x01:
            DownLoadingHex.Status.Bit.bit0 = ON;
            break;
        //      Extended Linear Address 
        case 0x04:
            DownLoadingHex.Address.Word.High = (Uint16)HEXDOWN_AsciiConvert(4);
            break;
        //      Start Linear Address 
        case 0x05:
            break;
    
        }
        CheckSum = ((~DownLoadingHex.Checksum) + 1) & 0xff;

        if( CheckSum != (Uint16)HEXDOWN_AsciiConvert(2) ){
           if( DownLoadingHex.ErrorCnt < MAX_ERROR_COUNT ){
               DownLoadingHex.ErrorFrame[DownLoadingHex.ErrorCnt] = DownLoadingHex.FrameNumber;
               DownLoadingHex.ErrorCnt ++;
           }
           else {
               DownLoadingHex.Status.Bit.bit1 = ON;
               return FALSE;
           }
           SCIx_TxString("\nCheckSumError");
        }
        DownLoadingHex.FrameNumber++;
        SCIx_TxChar('.');
    }
 
    return TRUE;
}
#pragma CODE_SECTION(HEXDOWN_AsciiConvert,"ramfuncs1");
Uint32 HEXDOWN_AsciiConvert( Uint16 NumByte )
{
    Uint32 Value,i;
    char Rcvdata;

    Value = 0;
    
    for ( i = 0; i < NumByte; i++ ) {
        Rcvdata = SCIx_RxChar();
        Value |= HEXDOWN_AsciiToHex( Rcvdata ) << ( ( (NumByte-1) - i ) * 4 );
    }
    if( NumByte == 4 ){
        DownLoadingHex.Checksum += (( Value >> 8 ) & 0xff);
        DownLoadingHex.Checksum += (Value & 0xff);
    }
    else {
        DownLoadingHex.Checksum += (Value & 0xff);
    }
    return Value;
}



#pragma CODE_SECTION(HEXDOWN_AsciiToHex,"ramfuncs1");
char HEXDOWN_AsciiToHex(char Ascii)
{
	if(Ascii >= '0' && Ascii <= '9')return(Ascii-'0');
	else if(Ascii >= 'a' && Ascii<= 'f')return(Ascii-'a'+10);
	else if(Ascii >= 'A' && Ascii <= 'F')return(Ascii-'A'+10);
	else return(0xFF);
}


