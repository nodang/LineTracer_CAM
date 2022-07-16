// TI File $Revision: /main/1 $
// Checkin $Date: December 1, 2004   12:32:52 $
//###########################################################################
//
// FILE:	DSP280x_GlobalVariableDefs.c
//
// TITLE:	DSP280x Global Variables and Data Section Pragmas.
//
//###########################################################################
// $TI Release: DSP280x V1.30 $
// $Release Date: February 10, 2006 $
//###########################################################################

#include "DSP280x_Device.h"     // DSP280x Headerfile Include File

//---------------------------------------------------------------------------
// Define Global Peripheral Variables:
//
//----------------------------------------
#ifdef __cplusplus 
#pragma DATA_SECTION("AdcRegsFile") 
#else 
#pragma DATA_SECTION(AdcRegs,"AdcRegsFile");
#endif 
volatile struct ADC_REGS AdcRegs;

//----------------------------------------
#ifdef __cplusplus 
#pragma DATA_SECTION("AdcMirrorFile") 
#else 
#pragma DATA_SECTION(AdcMirror,"AdcMirrorFile");
#endif 
volatile struct ADC_RESULT_MIRROR_REGS AdcMirror;

//----------------------------------------
#ifdef __cplusplus 
#pragma DATA_SECTION("CpuTimer0RegsFile") 
#else 
#pragma DATA_SECTION(CpuTimer0Regs,"CpuTimer0RegsFile");
#endif
volatile struct CPUTIMER_REGS CpuTimer0Regs;

//----------------------------------------
#ifdef __cplusplus 
#pragma DATA_SECTION("CpuTimer1RegsFile") 
#else 
#pragma DATA_SECTION(CpuTimer1Regs,"CpuTimer1RegsFile");
#endif
volatile struct CPUTIMER_REGS CpuTimer1Regs;


//----------------------------------------
#ifdef __cplusplus 
#pragma DATA_SECTION("CpuTimer2RegsFile") 
#else 
#pragma DATA_SECTION(CpuTimer2Regs,"CpuTimer2RegsFile");
#endif
volatile struct CPUTIMER_REGS CpuTimer2Regs;


//----------------------------------------
#ifdef __cplusplus 
#pragma DATA_SECTION("CsmPwlFile") 
#else
#pragma DATA_SECTION(CsmPwl,"CsmPwlFile");
#endif
volatile struct CSM_PWL CsmPwl;

//----------------------------------------
#ifdef __cplusplus 
#pragma DATA_SECTION("CsmRegsFile") 
#else
#pragma DATA_SECTION(CsmRegs,"CsmRegsFile");
#endif
volatile struct CSM_REGS CsmRegs;



//----------------------------------------
#ifdef __cplusplus 
#pragma DATA_SECTION("DevEmuRegsFile") 
#else
#pragma DATA_SECTION(DevEmuRegs,"DevEmuRegsFile");
#endif
volatile struct DEV_EMU_REGS DevEmuRegs;

//----------------------------------------
#ifdef __cplusplus 
#pragma DATA_SECTION("ECanaRegsFile") 
#else 
#pragma DATA_SECTION(ECanaRegs,"ECanaRegsFile");
#endif
volatile struct ECAN_REGS ECanaRegs;

//----------------------------------------
#ifdef __cplusplus 
#pragma DATA_SECTION("ECanaMboxesFile") 
#else 
#pragma DATA_SECTION(ECanaMboxes,"ECanaMboxesFile");
#endif
volatile struct ECAN_MBOXES ECanaMboxes;

//----------------------------------------
#ifdef __cplusplus 
#pragma DATA_SECTION("ECanaLAMRegsFile") 
#else 
#pragma DATA_SECTION(ECanaLAMRegs,"ECanaLAMRegsFile");
#endif
volatile struct LAM_REGS ECanaLAMRegs;

//----------------------------------------
#ifdef __cplusplus 
#pragma DATA_SECTION("ECanaMOTSRegsFile") 
#else 
#pragma DATA_SECTION(ECanaMOTSRegs,"ECanaMOTSRegsFile");
#endif
volatile struct MOTS_REGS ECanaMOTSRegs;


//----------------------------------------
#ifdef __cplusplus 
#pragma DATA_SECTION("ECanaMOTORegsFile") 
#else 
#pragma DATA_SECTION(ECanaMOTORegs,"ECanaMOTORegsFile");
#endif
volatile struct MOTO_REGS ECanaMOTORegs;


//----------------------------------------
#ifdef __cplusplus 
#pragma DATA_SECTION("ECanbRegsFile") 
#else 
#pragma DATA_SECTION(ECanbRegs,"ECanbRegsFile");
#endif
volatile struct ECAN_REGS ECanbRegs;

//----------------------------------------
#ifdef __cplusplus 
#pragma DATA_SECTION("ECanbMboxesFile") 
#else 
#pragma DATA_SECTION(ECanbMboxes,"ECanbMboxesFile");
#endif
volatile struct ECAN_MBOXES ECanbMboxes;

//----------------------------------------
#ifdef __cplusplus 
#pragma DATA_SECTION("ECanbLAMRegsFile") 
#else 
#pragma DATA_SECTION(ECanbLAMRegs,"ECanbLAMRegsFile");
#endif
volatile struct LAM_REGS ECanbLAMRegs;

//----------------------------------------
#ifdef __cplusplus 
#pragma DATA_SECTION("ECanbMOTSRegsFile") 
#else 
#pragma DATA_SECTION(ECanbMOTSRegs,"ECanbMOTSRegsFile");
#endif
volatile struct MOTS_REGS ECanbMOTSRegs;


//----------------------------------------
#ifdef __cplusplus 
#pragma DATA_SECTION("ECanbMOTORegsFile") 
#else 
#pragma DATA_SECTION(ECanbMOTORegs,"ECanbMOTORegsFile");
#endif
volatile struct MOTO_REGS ECanbMOTORegs;

//----------------------------------------
#ifdef __cplusplus 
#pragma DATA_SECTION("EPwm1RegsFile") 
#else 
#pragma DATA_SECTION(LeftPwmRegs,"EPwm1RegsFile");
#endif
volatile struct EPWM_REGS LeftPwmRegs;


//----------------------------------------
#ifdef __cplusplus 
#pragma DATA_SECTION("EPwm2RegsFile") 
#else 
#pragma DATA_SECTION(RightPwmRegs,"EPwm2RegsFile");
#endif
volatile struct EPWM_REGS RightPwmRegs;

//----------------------------------------
#ifdef __cplusplus 
#pragma DATA_SECTION("EPwm3RegsFile") 
#else 
#pragma DATA_SECTION(EPwm3Regs,"EPwm3RegsFile");
#endif
volatile struct EPWM_REGS EPwm3Regs;

//----------------------------------------
#ifdef __cplusplus 
#pragma DATA_SECTION("EPwm4RegsFile") 
#else 
#pragma DATA_SECTION(EPwm4Regs,"EPwm4RegsFile");
#endif
volatile struct EPWM_REGS EPwm4Regs;

//----------------------------------------
#ifdef __cplusplus 
#pragma DATA_SECTION("EPwm5RegsFile") 
#else 
#pragma DATA_SECTION(EPwm5Regs,"EPwm5RegsFile");
#endif
volatile struct EPWM_REGS EPwm5Regs;

//----------------------------------------
#ifdef __cplusplus 
#pragma DATA_SECTION("EPwm6RegsFile") 
#else 
#pragma DATA_SECTION(EPwm6Regs,"EPwm6RegsFile");
#endif
volatile struct EPWM_REGS EPwm6Regs;


//----------------------------------------
#ifdef __cplusplus 
#pragma DATA_SECTION("ECap1RegsFile") 
#else 
#pragma DATA_SECTION(ECap1Regs,"ECap1RegsFile");
#endif
volatile struct ECAP_REGS ECap1Regs;


//----------------------------------------
#ifdef __cplusplus 
#pragma DATA_SECTION("ECap2RegsFile") 
#else 
#pragma DATA_SECTION(ECap2Regs,"ECap2RegsFile");
#endif
volatile struct ECAP_REGS ECap2Regs;

//----------------------------------------
#ifdef __cplusplus 
#pragma DATA_SECTION("ECap3RegsFile") 
#else 
#pragma DATA_SECTION(ECap3Regs,"ECap3RegsFile");
#endif
volatile struct ECAP_REGS ECap3Regs;

//----------------------------------------
#ifdef __cplusplus 
#pragma DATA_SECTION("ECap4RegsFile") 
#else 
#pragma DATA_SECTION(ECap4Regs,"ECap4RegsFile");
#endif
volatile struct ECAP_REGS ECap4Regs;


//----------------------------------------
#ifdef __cplusplus 
#pragma DATA_SECTION("EQep1RegsFile") 
#else 
#pragma DATA_SECTION(RightQepRegs,"EQep1RegsFile");
#endif
volatile struct EQEP_REGS RightQepRegs;

//----------------------------------------
#ifdef __cplusplus 
#pragma DATA_SECTION("EQep2RegsFile") 
#else 
#pragma DATA_SECTION(LeftQepRegs,"EQep2RegsFile");
#endif
volatile struct EQEP_REGS LeftQepRegs;

//----------------------------------------
#ifdef __cplusplus 
#pragma DATA_SECTION("GpioCtrlRegsFile") 
#else 
#pragma DATA_SECTION(GpioCtrlRegs,"GpioCtrlRegsFile");
#endif
volatile struct GPIO_CTRL_REGS GpioCtrlRegs;

//----------------------------------------
#ifdef __cplusplus 
#pragma DATA_SECTION("GpioDataRegsFile") 
#else 
#pragma DATA_SECTION(GpioDataRegs,"GpioDataRegsFile");
#endif
volatile struct GPIO_DATA_REGS GpioDataRegs;

//----------------------------------------
#ifdef __cplusplus 
#pragma DATA_SECTION("GpioIntRegsFile") 
#else 
#pragma DATA_SECTION(GpioIntRegs,"GpioIntRegsFile");
#endif
volatile struct GPIO_INT_REGS GpioIntRegs;

//----------------------------------------
#ifdef __cplusplus 
#pragma DATA_SECTION("I2caRegsFile") 
#else 
#pragma DATA_SECTION(I2caRegs,"I2caRegsFile");
#endif
volatile struct I2C_REGS I2caRegs;

//----------------------------------------
#ifdef __cplusplus 
#pragma DATA_SECTION("PieCtrlRegsFile") 
#else
#pragma DATA_SECTION(PieCtrlRegs,"PieCtrlRegsFile");
#endif
volatile struct PIE_CTRL_REGS PieCtrlRegs;

//----------------------------------------
#ifdef __cplusplus 
#pragma DATA_SECTION("PieVectTableFile") 
#else
#pragma DATA_SECTION(PieVectTable,"PieVectTableFile");
#endif
struct PIE_VECT_TABLE PieVectTable;

//----------------------------------------
#ifdef __cplusplus 
#pragma DATA_SECTION("SciaRegsFile") 
#else
#pragma DATA_SECTION(SciaRegs,"SciaRegsFile");
#endif
volatile struct SCI_REGS SciaRegs;

//----------------------------------------
#ifdef __cplusplus 
#pragma DATA_SECTION("ScibRegsFile") 
#else
#pragma DATA_SECTION(ScibRegs,"ScibRegsFile");
#endif
volatile struct SCI_REGS ScibRegs;

//----------------------------------------
#ifdef __cplusplus 
#pragma DATA_SECTION("SpiaRegsFile") 
#else
#pragma DATA_SECTION(SpiaRegs,"SpiaRegsFile");
#endif
volatile struct SPI_REGS SpiaRegs;

//----------------------------------------
#ifdef __cplusplus 
#pragma DATA_SECTION("SpibRegsFile") 
#else
#pragma DATA_SECTION(SpibRegs,"SpibRegsFile");
#endif
volatile struct SPI_REGS SpibRegs;

//----------------------------------------
#ifdef __cplusplus 
#pragma DATA_SECTION("SpicRegsFile") 
#else
#pragma DATA_SECTION(SpicRegs,"SpicRegsFile");
#endif
volatile struct SPI_REGS SpicRegs;

//----------------------------------------
#ifdef __cplusplus 
#pragma DATA_SECTION("SpidRegsFile") 
#else
#pragma DATA_SECTION(SpidRegs,"SpidRegsFile");
#endif
volatile struct SPI_REGS SpidRegs;

//----------------------------------------
#ifdef __cplusplus 
#pragma DATA_SECTION("SysCtrlRegsFile") 
#else
#pragma DATA_SECTION(SysCtrlRegs,"SysCtrlRegsFile");
#endif
volatile struct SYS_CTRL_REGS SysCtrlRegs;

//----------------------------------------
#ifdef __cplusplus 
#pragma DATA_SECTION("FlashRegsFile") 
#else
#pragma DATA_SECTION(FlashRegs,"FlashRegsFile");
#endif
volatile struct FLASH_REGS FlashRegs;

//----------------------------------------
#ifdef __cplusplus 
#pragma DATA_SECTION("XIntruptRegsFile") 
#else
#pragma DATA_SECTION(XIntruptRegs,"XIntruptRegsFile");
#endif
volatile struct XINTRUPT_REGS XIntruptRegs;





//===========================================================================
// End of file.
//===========================================================================









