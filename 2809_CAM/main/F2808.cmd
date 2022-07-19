/*
// TI File $Revision: /main/3 $
// Checkin $Date: September 7, 2005   17:40:17 $
//###########################################################################
//
// FILE:	F2808.cmd
//
// TITLE:	Linker Command File For F2808 Device
//
//###########################################################################
// $TI Release: DSP280x V1.30 $
// $Release Date: February 10, 2006 $
//###########################################################################
*/

/* ======================================================
// For Code Composer Studio V2.2 and later
// ---------------------------------------
// In addition to this memory linker command file, 
// add the header linker command file directly to the project. 
// The header linker command file is required to link the
// peripheral structures to the proper locations within 
// the memory map.
//
// The header linker files are found in <base>\DSP280x_Headers\cmd
//   
// For BIOS applications add:      DSP280x_Headers_BIOS.cmd
// For nonBIOS applications add:   DSP280x_Headers_nonBIOS.cmd    
========================================================= */

/* ======================================================
// For Code Composer Studio prior to V2.2
// --------------------------------------
// 1) Use one of the following -l statements to include the 
// header linker command file in the project. The header linker
// file is required to link the peripheral structures to the proper 
// locations within the memory map                                    */

/* Uncomment this line to include file only for non-BIOS applications */
/* -l DSP280x_Headers_nonBIOS.cmd */

/* Uncomment this line to include file only for BIOS applications */
/* -l DSP280x_Headers_BIOS.cmd */

/* 2) In your project add the path to <base>\DSP280x_headers\cmd to the
   library search path under project->build options, linker tab, 
   library search path (-i).
/*========================================================= */

/* Define the memory block start/length for the F2808  
   PAGE 0 will be used to organize program sections
   PAGE 1 will be used to organize data sections

   Notes: 
         Memory blocks on F2808 are uniform (ie same
         physical memory) in both PAGE 0 and PAGE 1.  
         That is the same memory region should not be
         defined for both PAGE 0 and PAGE 1.
         Doing so will result in corruption of program 
         and/or data. 
         
         L0/L1 and H0 memory blocks are mirrored - that is
         they can be accessed in high memory or low memory.
         For simplicity only one instance is used in this
         linker file. 
         
         Contiguous SARAM memory blocks or flash sectors can be
         be combined if required to create a larger memory block. 
*/

MEMORY
{
PAGE 0:    /* Program Memory */
           /* Memory (RAM/FLASH/OTP) blocks can be moved to PAGE1 for data allocation */

   RAMM1       : origin = 0x000600, length = 0x000200     /* on-chip RAM block M1 */
   OTP         : origin = 0x3D7800, length = 0x000400     /* on-chip OTP */
   USERFLASH   : origin = 0x3E8002, length = 0x00BFF0     /* on-chip FLASH */
   MONITOR     : origin = 0x3F4000, length = 0x003F80     /* on-chip FLASH */
   CSM_RSVD    : origin = 0x3F7F80, length = 0x000076     /* Part of FLASHA.  Program with all 0x0000 when CSM is in use. */
   BEGIN       : origin = 0x3E8000, length = 0x000002     /* Part of FLASHA.  Used for "boot to Flash" bootloader mode. */
   CSM_PWL     : origin = 0x3F7FF8, length = 0x000008     /* Part of FLASHA.  CSM password locations in FLASHA */
   
   ROM         : origin = 0x3FF000, length = 0x000FC0     /* Boot ROM */
   RESET       : origin = 0x3FFFC0, length = 0x000002     /* part of boot ROM  */
   VECTORS     : origin = 0x3FFFC2, length = 0x00003E     /* part of boot ROM  */

/*   RAMH0       : origin = 0x3F8000, length = 0x004000    */ /* on-chip RAM block L0 , L1 , H0 */
   RAMH0       : origin = 0x3F8000, length = 0x004000    
   PAGE 1 :   /* Data Memory */
           /* Memory (RAM/FLASH/OTP) blocks can be moved to PAGE0 for program allocation */
           /* Registers remain on PAGE1                                                  */

   RAMM0       : origin = 0x000000, length = 0x000600     /* on-chip RAM block M0 */
   RAML0_1     : origin = 0x008000, length = 0x002000   	/* on-chip RAM block L1,L2 */

}

/* Allocate sections to memory blocks.
   Note:
         codestart user defined section in DSP28_CodeStartBranch.asm used to redirect code 
                   execution when booting to flash
         ramfuncs  user defined section to store functions that will be copied from Flash into RAM
*/ 
 
SECTIONS
{
 
   /* Allocate program areas: */
   .cinit              : > USERFLASH   PAGE = 0
   .pinit              : > USERFLASH   PAGE = 0
   .text               : > USERFLASH   PAGE = 0
   codestart           : > BEGIN       PAGE = 0
   
   ramfuncs            : LOAD = USERFLASH, 
                         RUN = RAMM1, 
                         LOAD_START(_RamfuncsLoadStart),
                         LOAD_END(_RamfuncsLoadEnd),
                         RUN_START(_RamfuncsRunStart),
                         PAGE = 0

   ramfuncs2            : LOAD = USERFLASH, 
                         RUN = RAMH0, 
                         LOAD_START(_RamfuncsLoadStart1),
                         LOAD_END(_RamfuncsLoadEnd1),
                         RUN_START(_RamfuncsRunStart1),
                         PAGE = 0

                         
   csmpasswds          : > CSM_PWL     PAGE = 0
   csm_rsvd            : > CSM_RSVD    PAGE = 0
   
   /* Allocate uninitalized data sections: */
   .stack              : > RAMM0       	PAGE = 1
   .heap			   : > RAMH0		PAGE = 0
   .ebss               : > RAMH0		PAGE = 0
   .esysmem            : > RAMH0       	PAGE = 0
   .sysmem			   : > RAMH0		PAGE = 0

   /* Initalized sections go in Flash */
   /* For SDFlash to program these, they must be allocated to page 0 */
   .econst             : > USERFLASH    PAGE = 0
   .switch             : > USERFLASH    PAGE = 0      

   /* Allocate IQ math areas: */
   IQmath              : > USERFLASH   PAGE = 0                  /* Math Code */
   IQmathTables        : > ROM         PAGE = 0, TYPE = NOLOAD   /* Math Tables In ROM */

   /* .reset is a standard section used by the compiler.  It contains the */ 
   /* the address of the start of _c_int00 for C Code.   /*
   /* When using the boot ROM this section and the CPU vector */
   /* table is not needed.  Thus the default type is set here to  */
   /* DSECT  */ 
   .reset              : > RESET,      PAGE = 0, TYPE = DSECT
   vectors             : > VECTORS     PAGE = 0, TYPE = DSECT

   VFD_FONT			   : > USERFLASH	   PAGE = 0
   MENU_STR			   : > USERFLASH	   PAGE = 0
}

/*
//===========================================================================
// End of file.
//===========================================================================
*/