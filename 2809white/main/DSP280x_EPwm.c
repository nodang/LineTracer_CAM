// TI File $Revision: /main/3 $
// Checkin $Date: December 2, 2004   14:54:39 $
//###########################################################################
//
// FILE:   DSP280x_EPwm.c
//
// TITLE:  DSP280x ePWM Initialization & Support Functions.
//
//###########################################################################
// $TI Release: DSP280x V1.10 $
// $Release Date: April 18, 2005 $
//###########################################################################

#include "DSP280x_Device.h"     // DSP280x Headerfile Include File
#include "DSP280x_Examples.h"   // DSP280x Examples Include File

//---------------------------------------------------------------------------
// InitEPwm: 
//---------------------------------------------------------------------------
// This function initializes the ePWM(s) to a known state.
//
#define	AQ_NO_ACTION	0x0
#define	AQ_CLEAR		0x1
#define	AQ_SET			0x2
#define	AQ_TOGGLE		0x3


void InitEPWM(volatile struct EPWM_REGS *pPWM)
{
	pPWM->TBCTL.bit.FREE_SOFT= 2;//Free Run
	pPWM->TBCTL.bit.PHSDIR = 0;//ignored
	pPWM->TBCTL.bit.CLKDIV = 0;//
	pPWM->TBCTL.bit.HSPCLKDIV = 0;// SYSCLKOUT -> PWM  100MHz
	pPWM->TBCTL.bit.SWFSYNC = 0;//
	pPWM->TBCTL.bit.SYNCOSEL = 3;//Disable SyncOut
	pPWM->TBCTL.bit.PRDLD = 1;//Load immediately
	pPWM->TBCTL.bit.PHSEN = 0;//
	pPWM->TBCTL.bit.CTRMODE = 0;//Count up
	//0010 0000 0000 0000 0000 0011 0001 0000 //
	

	pPWM->CMPCTL.bit.SHDWAMODE = 1;//Immediate mode.
	pPWM->CMPCTL.bit.SHDWBMODE = 1;

	pPWM->AQCTLA.bit.ZRO = AQ_SET;
	pPWM->AQCTLA.bit.CAU = AQ_CLEAR;
	
	pPWM->AQCTLB.bit.ZRO = AQ_SET;
	pPWM->AQCTLB.bit.CBU = AQ_CLEAR;

	pPWM->DBCTL.bit.OUT_MODE = 0;//Dead band disable
	pPWM->PCCTL.bit.CHPEN = 0;//PC cntrol disable
	pPWM->TZSEL.all = 0;//TZ Module select..all disable
	pPWM->TZCTL.all = 0xf;//TZ Control all disable
	pPWM->TZEINT.all = 0;//TZ INT disable
	pPWM->ETSEL.all = 0;
	pPWM->ETPS.all = 0;

	pPWM->CMPA.half.CMPA = 0;
	pPWM->CMPB = 0;

	pPWM->TBPRD = 2000;
	
}	


//===========================================================================
// End of file.
//===========================================================================
