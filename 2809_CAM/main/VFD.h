//###########################################################################
//
// FILE		: VFD.h
//
// TITLE	: VFD h file.
//
// Author	: Choi Woo Yong
//
// Company	: Maze
//
//###########################################################################
// $Release Date: 2011.10.10 $
//###########################################################################


#ifndef __VFD_H__
#define __VFD_H__

extern void VfdCtlRegInit(Uint16 CrlReg);
extern void VfdInit(void);
extern void VfdDataLoad(char *Buff);
extern void VFDPrintf(char *Form, ... );


#endif
