// TI File $Revision: /main/3 $
// Checkin $Date: December 2, 2004   15:16:48 $
//###########################################################################
//
// FILE:   DSP280x_Spi.c
//
// TITLE:  DSP280x SPI Initialization & Support Functions.
//
//###########################################################################
// $TI Release: DSP280x V1.10 $
// $Release Date: April 18, 2005 $
// Hwang Ha yun Edit 2006.12.22
// use for user variable save
//###########################################################################

#include "DSP280x_Device.h"     // DSP280x Headerfile Include File
#include "DSP280x_Examples.h"   // DSP280x Examples Include File

#define SPIA_CS_H	{GpioDataRegs.GPASET.bit.GPIO19 = 1;}
#define SPIA_CS_L	{GpioDataRegs.GPACLEAR.bit.GPIO19 = 1;}

#define SPI_CS_DELAY	Delay(0xc000)
void InitSpi(void)
{
	SpiaRegs.SPICCR.all=0x0007;
	SpiaRegs.SPICTL.all=0x001F;
	SpiaRegs.SPISTS.all=0x00;
	SpiaRegs.SPIBRR = 0x00;
	SpiaRegs.SPIFFTX.all=0x8000;
	SpiaRegs.SPIFFRX.all=0x0000;
	SpiaRegs.SPIFFCT.all=0x00;
	SpiaRegs.SPIPRI.all=0x0010; 
}   

#define PAGE_PROGRAM_DIRECT 	0x82
#define PAGE_READ				0xd2
#define STATUS_REG_READ			0xd7

void SpiBusyOK(void)
{	
	Uint16 StatusReg = 0;

	while((StatusReg & 0x08) != 0x08)
	{
		SPIA_CS_H;
		SPI_CS_DELAY;
		SPIA_CS_L;
		
		SPI_CS_DELAY;
		
		SpiaRegs.SPICCR.bit.SPISWRESET = 1;
		
		SpiTx(STATUS_REG_READ);
		StatusReg = SpiTx(0);

		SPIA_CS_H;
		SPI_CS_DELAY;
	}
}


void SpiReadRom(Uint16 PageAdd, Uint16 BufAdd, Uint16 Number, Uint16 *pBuf)
{
	Uint16 SpiCMD = 0;
	Uint16 Add1 = 0;
	Uint16 Add2 = 0;
	Uint16 Add3 = 0;
	Uint16 i = 0;

	SpiBusyOK();

	//rom address ..
	//xxxx xxPP // PPPP PPPB // BBBB BBBB //

	Add1 = (PageAdd & 0x1ff) >> 7;
	Add2 = ((PageAdd & 0x7f) << 1)	| ((BufAdd & 0x1ff) >> 8);	
	Add3 = (BufAdd & 0xff);
	SpiCMD = PAGE_READ;

	SPIA_CS_H;
	SPI_CS_DELAY;
	SPIA_CS_L;
	SPI_CS_DELAY;

	//send 0x82
	SpiaRegs.SPICCR.bit.SPISWRESET = 1;

	SpiTx(SpiCMD);
	SpiTx(Add1);
	SpiTx(Add2);
	SpiTx(Add3);
	//dont care byte
	SpiTx(0);
	SpiTx(0);
	SpiTx(0);
	SpiTx(0);

	for(i = 0; i < Number; i++)
	{
		pBuf[i] = SpiTx(0);
	//	pBuf[i] |= SpiTx(0);
	}

	SPIA_CS_H;
	SPI_CS_DELAY;
	
	
}


// PageAdd = 페이지 번호, BufAd = 시작주소, Number = 크기, *pBuf = 저장될 변수 이름
void SpiWriteRom(Uint16 PageAdd, Uint16 BufAdd, Uint16 Number, Uint16 *pBuf)
{
	Uint16 SpiCMD = 0;
	Uint16 Add1 = 0;
	Uint16 Add2 = 0;
	Uint16 Add3 = 0;
	Uint16 i = 0;

	SpiBusyOK();

	//rom address ..
	//xxxx xxPP // PPPP PPPB // BBBB BBBB //

	Add1 = (PageAdd & 0x1ff) >> 7;
	Add2 = ((PageAdd & 0x7f) << 1)	| ((BufAdd & 0x1ff) >> 8);	
	Add3 = (BufAdd & 0xff);
	SpiCMD = PAGE_PROGRAM_DIRECT;
	
	SPIA_CS_H;
	SPI_CS_DELAY;
	SPIA_CS_L;
	SPI_CS_DELAY;

	//send 0x82
	SpiaRegs.SPICCR.bit.SPISWRESET = 1;

	SpiTx(SpiCMD);
	SpiTx(Add1);
	SpiTx(Add2);
	SpiTx(Add3);

	for(i = 0; i < Number; i++)
	{
		SpiTx(pBuf[i] & 0xff);
	//	SpiTx((pBuf[i]>>8) & 0xff);
	}

	SPIA_CS_H;
	SPI_CS_DELAY;


}


Uint16 SpiTx(Uint16 Buf)
{	
	SpiaRegs.SPITXBUF = (Uint16)((Buf & 0xff) << 8);
	SpiaRegs.SPISTS.bit.BUFFULL_FLAG = ON;
	while(SpiaRegs.SPISTS.bit.INT_FLAG == OFF);
	
	return ((SpiaRegs.SPIRXBUF) & 0xff);
}


//===========================================================================
// End of file.
//===========================================================================
