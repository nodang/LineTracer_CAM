// TI File $Revision: /main/4 $
// Checkin $Date: September 8, 2005   17:32:45 $
//###########################################################################
//
// FILE:   DSP280x_SysCtrl.c
//
// TITLE:  DSP280x Device System Control Initialization & Support Functions.
//
// DESCRIPTION:
//
//         Example initialization of system resources.
//
//###########################################################################
// $TI Release: DSP280x V1.30 $
// $Release Date: February 10, 2006 $
//###########################################################################


#include "DSP280x_Device.h"     // Headerfile Include File
#include "DSP280x_Examples.h"   // Examples Include File

// Functions that will be run from RAM need to be assigned to 
// a different section.  This section will then be mapped to a load and 
// run address using the linker cmd file.

#pragma CODE_SECTION(InitFlash, "ramfuncs");

//---------------------------------------------------------------------------
// InitSysCtrl: 
//---------------------------------------------------------------------------
// This function initializes the System Control registers to a known state.
// - Disables the watchdog
// - Set the PLLCR for proper SYSCLKOUT frequency 
// - Set the pre-scaler for the high and low frequency peripheral clocks
// - Enable the clocks to the peripherals

void InitSysCtrl(void)
{

   // Disable the watchdog        
   DisableDog();
   
   // Initialize the PLLCR to 0xA
   InitPll(0xA);// 10 - 100Mhz operation

   // Initialize the peripheral clocks
   InitPeripheralClocks();

}


//---------------------------------------------------------------------------
// Example: InitFlash: 
//---------------------------------------------------------------------------
// This function initializes the Flash Control registers

//                   CAUTION 
// This function MUST be executed out of RAM. Executing it
// out of OTP/Flash will yield unpredictable results

void InitFlash(void)
{
   EALLOW;
   //Enable Flash Pipeline mode to improve performance
   //of code executed from Flash.
   FlashRegs.FOPT.bit.ENPIPE = 1; //Flash Pipeline active
   
   //                CAUTION
   //Minimum waitstates required for the flash operating
   //at a given CPU rate must be characterized by TI. 
   //Refer to the datasheet for the latest information.  

   //highest power..
   FlashRegs.FPWR.bit.PWR = 3;

   //Set the Paged Waitstate for the Flash
   FlashRegs.FBANKWAIT.bit.PAGEWAIT = 3;

   //Set the Random Waitstate for the Flash
   FlashRegs.FBANKWAIT.bit.RANDWAIT = 3;
   
   //Set the Waitstate for the OTP
   FlashRegs.FOTPWAIT.bit.OTPWAIT = 5;
   
   //                CAUTION
   //ONLY THE DEFAULT VALUE FOR THESE 2 REGISTERS SHOULD BE USED
   FlashRegs.FSTDBYWAIT.bit.STDBYWAIT = 0x01FF;       
   FlashRegs.FACTIVEWAIT.bit.ACTIVEWAIT = 0x01FF;   
   EDIS;

   //Force a pipeline flush to ensure that the write to 
   //the last register configured occurs before returning.  

   asm(" RPT #10 || NOP");
}	


//---------------------------------------------------------------------------
// Example: ServiceDog: 
//---------------------------------------------------------------------------
// This function resets the watchdog timer.
// Enable this function for using ServiceDog in the application 

void ServiceDog(void)
{
    EALLOW;
    SysCtrlRegs.WDKEY = 0x0055;
    SysCtrlRegs.WDKEY = 0x00AA;
    EDIS;
}

//---------------------------------------------------------------------------
// Example: DisableDog: 
//---------------------------------------------------------------------------
// This function disables the watchdog timer.

void DisableDog(void)
{
    EALLOW;
    SysCtrlRegs.WDCR= 0x0068;
    EDIS;
}

//---------------------------------------------------------------------------
// Example: InitPll: 
//---------------------------------------------------------------------------
// This function initializes the PLLCR register.

void InitPll(Uint16 val)
{
   volatile Uint16 iVol;   

   // Make sure the PLL is not running in limp mode
   if (SysCtrlRegs.PLLSTS.bit.MCLKSTS != 0)
   {
      // Missing external clock has been detected
      // Replace this line with a call to an appropriate
      // SystemShutdown(); function. 
      asm("        ESTOP0");
   }

   // CLKINDIV MUST be 0 before PLLCR can be changed from
   // 0x0000. It is set to 0 by an external reset XRSn
   if (SysCtrlRegs.PLLSTS.bit.CLKINDIV != 0)
   {
       SysCtrlRegs.PLLSTS.bit.CLKINDIV = 0; //2//2분주
   }
   
   // Change the PLLCR
   if (SysCtrlRegs.PLLCR.bit.DIV != val)
   {
       
      EALLOW;
      // Before setting PLLCR turn off missing clock detect logic
      SysCtrlRegs.PLLSTS.bit.MCLKOFF = 1; //클럭분실회로 감지 off
      SysCtrlRegs.PLLCR.bit.DIV = val;
      EDIS;
   
      // Optional: Wait for PLL to lock.
      // During this time the CPU will switch to OSCCLK/2 until
      // the PLL is stable.  Once the PLL is stable the CPU will 
      // switch to the new PLL value. 
      //
      // This time-to-lock is monitored by a PLL lock counter.   
      //   
      // Code is not required to sit and wait for the PLL to lock.   
      // However, if the code does anything that is timing critical, 
      // and requires the correct clock be locked, then it is best to 
      // wait until this switching has completed.  
  
      // Wait for the PLL lock bit to be set.  
      // Note this bit is not available on 281x devices.  For those devices
      // use a software loop to perform the required count. 

      // The watchdog should be disabled before this loop, or fed within 
      // the loop via ServiceDog().   
      
	  // Uncomment to disable the watchdog
      DisableDog();
   
      while(SysCtrlRegs.PLLSTS.bit.PLLLOCKS != 1) 
      {
	      // Uncomment to service the watchdog
          // ServiceDog();
      }
       
      EALLOW;
      SysCtrlRegs.PLLSTS.bit.MCLKOFF = 0;
      EDIS;   
    }
}

//--------------------------------------------------------------------------
// Example: InitPeripheralClocks: 
//---------------------------------------------------------------------------
// This function initializes the clocks to the peripheral modules.
// First the high and low clock prescalers are set
// Second the clocks are enabled to each peripheral.
// To reduce power, leave clocks to unused peripherals disabled
//
// Note: If a peripherals clock is not enabled then you cannot 
// read or write to the registers for that peripheral 

void InitPeripheralClocks(void)
{
   EALLOW;

// HISPCP/LOSPCP prescale register settings, normally it will be set to default values
   SysCtrlRegs.HISPCP.all = 0x0001;// sysclkout/2 = 50MHz
   SysCtrlRegs.LOSPCP.all = 0x0002;// 0x2 =>sysclkout/4 = 25MHz

// XCLKOUT to SYSCLKOUT ratio.  By default XCLKOUT = 1/4 SYSCLKOUT
   SysCtrlRegs.XCLK.bit.XCLKOUTDIV=2;
      	
// Peripheral clock enables set for the selected peripherals.   
// If you are not using a peripheral leave the clock off
// to save on power. 
// 
// Note: not all peripherals are available on all 280x derivates.
// Refer to the datasheet for your particular device. 

	SysCtrlRegs.PCLKCR0.all = 0;
	SysCtrlRegs.PCLKCR1.all = 0;

/*
	// Peripheral clock control register 0 bit definitions:
struct PCLKCR0_BITS  {  // bits  description
   Uint16 rsvd1:2;      // 1:0   reserved
   Uint16 TBCLKSYNC:1;  // 2     EPWM Module TBCLK enable/sync 
   Uint16 ADCENCLK:1;   // 3     Enable high speed clk to ADC
   Uint16 I2CAENCLK:1;  // 4     Enable SYSCLKOUT to I2C-A
   Uint16 rsvd2:1;      // 5     reserved
   Uint16 SPICENCLK:1;  // 6     Enable low speed clk to SPI-C
   Uint16 SPIDENCLK:1;  // 7     Enable low speed clk to SPI-D
   Uint16 SPIAENCLK:1;  // 8     Enable low speed clk to SPI-A
   Uint16 SPIBENCLK:1;  // 9     Enable low speed clk to SPI-B   
   Uint16 SCIAENCLK:1;  // 10    Enable low speed clk to SCI-A
   Uint16 SCIBENCLK:1;  // 11    Enable low speed clk to SCI-B
   Uint16 rsvd3:2;      // 13:12 reserved
   Uint16 ECANAENCLK:1; // 14    Enable system clk to eCAN-A
   Uint16 ECANBENCLK:1; // 15    Enable system clk to eCAN-B
};
*/
	SysCtrlRegs.PCLKCR0.bit.ADCENCLK = 1;//adc clk enable
	SysCtrlRegs.PCLKCR0.bit.SCIAENCLK = 1;//SCIA clk enable
	SysCtrlRegs.PCLKCR0.bit.SPIAENCLK = 1;//SPIA clk enable

/*	
// Peripheral clock control register 1 bit definitions:
struct PCLKCR1_BITS  {    // bits  description
   Uint16 EPWM1ENCLK:1;   // 0     Enable SYSCLKOUT to EPWM1
   Uint16 EPWM2ENCLK:1;   // 1     Enable SYSCLKOUT to EPWM2
   Uint16 EPWM3ENCLK:1;   // 2     Enable SYSCLKOUT to EPWM3
   Uint16 EPWM4ENCLK:1;   // 3     Enable SYSCLKOUT to EPWM4
   Uint16 EPWM5ENCLK:1;   // 4     Enable SYSCLKOUT to EPWM5
   Uint16 EPWM6ENCLK:1;   // 5     Enable SYSCLKOUT to EPWM6               
   Uint16 rsvd1:2;        // 7:6   reserved
   Uint16 ECAP1ENCLK:1;   // 8     Enable SYSCLKOUT to ECAP1   
   Uint16 ECAP2ENCLK:1;   // 9     Enable SYSCLKOUT to ECAP2   
   Uint16 ECAP3ENCLK:1;   // 10    Enable SYSCLKOUT to ECAP3   
   Uint16 ECAP4ENCLK:1;   // 11    Enable SYSCLKOUT to ECAP4   
   Uint16 rsvd2:2;        // 13:12 reserved
   Uint16 EQEP1ENCLK:1;   // 11    Enable SYSCLKOUT to EQEP1      
   Uint16 EQEP2ENCLK:1;   // 11    Enable SYSCLKOUT to EQEP2         
};
*/
	SysCtrlRegs.PCLKCR1.bit.EQEP1ENCLK = 1;//QEPA clk enable
	SysCtrlRegs.PCLKCR1.bit.EQEP2ENCLK = 1;//QEPB clk enable

	SysCtrlRegs.PCLKCR1.bit.EPWM1ENCLK = 1;//PWM1 clk enable
	SysCtrlRegs.PCLKCR1.bit.EPWM2ENCLK = 1;//PWM2 clk ebable
	SysCtrlRegs.PCLKCR0.bit.TBCLKSYNC = 1;
	
   	EDIS;
}

	
//===========================================================================
// End of file.
//===========================================================================
