// TI File $Revision: /main/2 $
// Checkin $Date: December 2, 2004   11:43:13 $
//###########################################################################
//
// FILE:   DSP280x_EQep.c
//
// TITLE:  DSP280x eQEP Initialization & Support Functions.
//
//###########################################################################
// $TI Release: DSP280x V1.10 $
// $Release Date: April 18, 2005 $
//###########################################################################

#include "DSP280x_EQep.h"



//---------------------------------------------------------------------------
// InitEQep: 
//---------------------------------------------------------------------------
// This function initializes the eQEP(s) to a known state.


void InitEQep( volatile struct EQEP_REGS *pQEP)
{
/*
	pQEP->QDECCTL.all = 0;

	pQEP->QDECCTL.bit.QSRC = 0;//Quadrature count mode
	pQEP->QDECCTL.bit.SOEN = 0;//Disable position-compare sync output
	pQEP->QDECCTL.bit.SPSEL = 0;//index pin is used for sync output
	pQEP->QDECCTL.bit.XCR = 0;// 2x resolution
	pQEP->QDECCTL.bit.SWAP = 0;//Quadrature-clk inputs are not swapped
	pQEP->QDECCTL.bit.IGATE = 0;//Disable gating of index pulse
	pQEP->QDECCTL.bit.QAP = 0;//NO effect
	pQEP->QDECCTL.bit.QBP = 0;//NO effect
	pQEP->QDECCTL.bit.QIP = 0;//NO effect
	pQEP->QDECCTL.bit.QSP = 0;//NO effect
	

	pQEP->QEPCTL.all = 0; 
	
	pQEP->QEPCTL.bit.FREE_SOFT = 2;//unaffected by emulation suspend
	pQEP->QEPCTL.bit.PCRM = 1;//Position counter reset on the maximum position
	pQEP->QEPCTL.bit.SEI = 0;//disable Strobe event
	pQEP->QEPCTL.bit.IEI = 0;//disable Index event
	pQEP->QEPCTL.bit.SWI = 0;// do noting   software init position counter
	pQEP->QEPCTL.bit.SEL = 0;//.
	pQEP->QEPCTL.bit.IEL = 0;//.
	pQEP->QEPCTL.bit.QPEN = 1;//position counter is enabled
	pQEP->QEPCTL.bit.QCLM = 0;//.
	pQEP->QEPCTL.bit.UTE = 0;//Enable unit timer
	pQEP->QEPCTL.bit.WDE = 0;//Disable the QEP watch dog
	
	// 1001 0000 0000 1010
	
	pQEP->QPOSCTL.all = 0;//Disable position compare unit

	pQEP->QUPRD = 50000;//Unit Timer for 100Hz

//	pQEP->QCAPCTL.bit.CEN = 0;//Diasble QEP capture
//	pQEP->QCAPCTL.bit.CCPS = 4;//CAPCLK = SYSCLKOUT/16
//	pQEP->QCAPCTL.bit.UPPS = 4;//UPEVNT = QCLK/2
//	pQEP->QCAPCTL.bit.CEN = 1;//Enable QEP capture

	pQEP->QEINT.all = 0;
	pQEP->QPOSINIT = 0;
	pQEP->QPOSMAX = ~0;
	pQEP->QEPCTL.bit.SWI = 1;
*/
	/*
	pQEP->QDECCTL.bit.QSRC = 0;//Quadrature count mode
	pQEP->QDECCTL.bit.SOEN = 0;//Disable position-compare sync output
	pQEP->QDECCTL.bit.SPSEL = 0;//index pin is used for sync output
	pQEP->QDECCTL.bit.XCR = 0;// 2x resolution
	pQEP->QDECCTL.bit.SWAP = 0;//Quadrature-clk inputs are not swapped
	pQEP->QDECCTL.bit.IGATE = 0;//Disable gating of index pulse
	pQEP->QDECCTL.bit.QAP = 0;//NO effect
	pQEP->QDECCTL.bit.QBP = 0;//NO effect
	pQEP->QDECCTL.bit.QIP = 0;//NO effect
	pQEP->QDECCTL.bit.QSP = 0;//NO effect
	*/
	pQEP->QDECCTL.all = 0;

	/*
	pQEP->QEPCTL.bit.FREE_SOFT = 2;//unaffected by emulation suspend
	pQEP->QEPCTL.bit.PCRM = 1;//Position counter reset on the maximum position
	pQEP->QEPCTL.bit.SEI = 0;//disable Strobe event
	pQEP->QEPCTL.bit.IEI = 0;//disable Index event
	pQEP->QEPCTL.bit.SWI = 0;// do noting   software init position counter
	pQEP->QEPCTL.bit.SEL = 0;//.
	pQEP->QEPCTL.bit.IEL = 0;//.
	pQEP->QEPCTL.bit.QPEN = 1;//position counter is enabled
	pQEP->QEPCTL.bit.QCLM = 0;//.
	pQEP->QEPCTL.bit.UTE = 1;//Enable unit timer
	pQEP->QEPCTL.bit.WDE = 0;//Disable the QEP watch dog
	*/
	// 1001 0000 0000 1010
	pQEP->QEPCTL.all =0x900a; 
	
	pQEP->QPOSCTL.all = 0;//Disable position compare unit

	pQEP->QUPRD = 50000;//Unit Timer for 100Hz

	pQEP->QCAPCTL.bit.CEN = 0;//Diasble QEP capture
	pQEP->QCAPCTL.bit.CCPS = 4;//CAPCLK = SYSCLKOUT/16
	pQEP->QCAPCTL.bit.UPPS = 4;//UPEVNT = QCLK/2
	pQEP->QCAPCTL.bit.CEN = 1;//Enable QEP capture

	pQEP->QEINT.all = 0;
	pQEP->QPOSINIT = 0;			//	
	pQEP->QPOSMAX = 2048;		//	QEP MAX VALUE
	pQEP->QEPCTL.bit.SWI = 1;
	
}





//===========================================================================
// End of file.
//===========================================================================
