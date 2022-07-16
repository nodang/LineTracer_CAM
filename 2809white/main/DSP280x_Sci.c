// TI File $Revision: /main/2 $
// Checkin $Date: December 2, 2004   11:59:53 $
//###########################################################################
//
// FILE:	DSP280x_Sci.c
//
// TITLE:	DSP280x SCI Initialization & Support Functions.
//
//###########################################################################
// $TI Release: DSP280x V1.10 $
// $Release Date: April 18, 2005 $
//###########################################################################

#include "DSP280x_Device.h"     // DSP280x Headerfile Include File
#include "DSP280x_Examples.h"   // DSP280x Examples Include File

#include "stdio.h"
#include "stdlib.h"
#include "stdarg.h"

//---------------------------------------------------------------------------
// InitSci: 
//---------------------------------------------------------------------------
// This function initializes the SCI(s) to a known state.
//
#define BRR115200	((Uint16)26)
void InitSci(void)
{
    volatile struct SCI_REGS *Reg = &SciaRegs;

/*
	Reg->SCICCR.bit.STOPBITS = 0;//One stop bit
	Reg->SCICCR.bit.PARITY = 0;// not care
	Reg->SCICCR.bit.PARITYENA = 0;//parity disable
	Reg->SCICCR.bit.LOOPBKENA = 0;//loop back test mode disable
	Reg->SCICCR.bit.ADDRIDLE_MODE = 0;//idle-line protocol selected
	Reg->SCICCR.bit.SCICHAR = 7;//length = 8
*/
	Reg->SCICCR.all = 0x0007;
/*
	Reg->SCICTL1.bit.RXERRINTENA = 0;//error int disable
	Reg->SCICTL1.bit.SWRESET = 0;//not rst
	Reg->SCICTL1.bit.TXWAKE = 0;//transmit feature is not selected
	Reg->SCICTL1.bit.SLEEP = 0;//sleep mode disable
	Reg->SCICTL1.bit.TXENA = 1;//Transmitter enabled
	Reg->SCICTL1.bit.RXENA = 1;//Received enabled
*/
	Reg->SCICTL1.all = 0x03;

	//BRR = lspclk / (sci baud *8) -1
	// 115200 = 26
	Reg->SCIHBAUD = BRR115200 >> 8;
	Reg->SCILBAUD = BRR115200 & 0xff;

	Reg->SCICTL2.bit.RXBKINTENA = 0;//Disable RxRDY int
	Reg->SCICTL2.bit.TXINTENA = 0;//Disable TxRDY int

 	Reg->SCIFFTX.all = 0xa000;		// FIFO reset
 	Reg->SCIFFCT.all = 0x4000;		// Clear ABD(Auto baud bit)
 	
                                   		// No parity,8 char bits,
	
	Reg->SCICTL1.bit.SWRESET = 1;// SCI from Reset 

}

char SCIx_RxChar(void)
{
	volatile struct SCI_REGS *Reg = &SciaRegs;
	
    while( !(Reg->SCIRXST.bit.RXRDY) );
    return (char)Reg->SCIRXBUF.all;
}

void SCIx_TxChar(char Data)
{
	volatile struct SCI_REGS *Reg = &SciaRegs;

    while(!(Reg->SCICTL2.bit.TXRDY));
    Reg->SCITXBUF = Data;
}

void SCIx_TxString(char *Str)
{
    while(*Str) 
    {
        if(*Str == '\n'){
            SCIx_TxChar('\r');
        }
		
        SCIx_TxChar(*Str++ );
    }
}      
void TxPrintf(char *Form, ... )
{
    static char Buff[128];
    va_list ArgPtr;
    va_start(ArgPtr,Form);	 
    vsprintf(Buff, Form, ArgPtr);
    va_end(ArgPtr);
    SCIx_TxString(Buff);
}


//===========================================================================
// End of file.
//===========================================================================
