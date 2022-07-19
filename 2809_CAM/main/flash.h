//###########################################################################
#ifndef __FLASH_H__
#define __FLASH_H__

extern void InitFlashAPI2808(void);
extern void DeleteAllFlash(void);
extern void DeleteSecletFlash(void);
extern void UserFlashErase_DownloadPrm(void);
extern void InitUserHexDownVariable(void);
extern Uint16 UserPrmHexFileDownLoading(char StartState);
extern char HEXDOWN_AsciiToHex(char Ascii);
extern Uint32 HEXDOWN_AsciiConvert(Uint16 NumByte );
extern void UserProgramStart(void);
#endif

