#define _MAIN_
#define __STRUCT__


#include "DSP280x_Device.h"     // DSP281x Headerfile Include File
#include "DSP280x_Examples.h"  // DSP281x Examples Include File

void System_Init(void)
{
	DINT;				// 전체 인터럽트 금지
	InitSysCtrl();		// 워치록 금지, PLL 초기화, 주변 장치 클럭설정
	InitGpio();			// 입출력 포트 초기화	
	InitCpuTimers();
	
	MemCopy(&RamfuncsLoadStart, 	&RamfuncsLoadEnd, 		&RamfuncsRunStart); 
	MemCopy(&RamfuncsLoadStart1, 	&RamfuncsLoadEnd1, 	&RamfuncsRunStart1);
	
	InitSci();			
	InitSpi();
	InitPieCtrl();		// PIE 제어 레지스터 초기화 동작
	IER = 0x0000;		// 인터럽트 인에이블 레지스터 클리어
	IFR = 0x0000;		// 인터럽트 플래그 레지스터 클리어
	InitPieVectTable();
	InitAdc();

	Init_ISR();

	InitEPWM( &EPwm1Regs );
	InitEPWM( &EPwm3Regs );
	
	//InitEQep( &LeftQepRegs );
	//InitEQep( &RightQepRegs );
	
}

void Variable_Init( void )
{
	motor_init();
	
	SCI_ISR_ON;
}

void main(void)
{	
	System_Init();
	Variable_Init();
	
	//LOAD

	VFDPrintf("Wait....");

	StartCpuTimer2();

	while( 1 )
	{
		//TxPrintf("rm: %u	lm: %u\n", EPwm1Regs.CMPA.half.CMPA, EPwm3Regs.CMPA.half.CMPA);
		//DELAY_US(10000);
	}

	
}

void Delay(Uint32 Cnt)
{
	while(Cnt--)
	{
		asm("		nop");
		
		asm("	nop");	
	}
}


