//###########################################################################
//
// FILE		: main.h
//
// TITLE	: main h file.
//
// Author	: Yuk Keun Ho
//
// Company	: Maze & Hz
//
//###########################################################################
// $Release Date: 2011.10.10 $
//###########################################################################

#ifdef	_MAIN_
	#ifndef _MAIN_GLOBAL_
		#define _MAIN_GLOBAL_	
	#endif
#else
	#ifndef _MAIN_GLOBAL_
		#define _MAIN_GLOBAL_	extern
	#endif
#endif



#define D_MODE_BASE_TEST	3
#define D_MODE_MINOR_TEST	2
#define D_MODE_MAJOR_TSET	1
#define D_MODE_CONTEST		0

#define DEBUG_MODE 			D_MODE_BASE_TEST

#if(DEBUG_MODE == 3)
#define PRINT_DEBUG3	TxPrintf
#define PRINT_DEBUG2	TxPrintf
#define PRINT_DEBUG1	TxPrintf
#elif(DEBUG_MODE == 2)
#define PRINT_DEBUG3	
#define PRINT_DEBUG2	TxPrintf
#define PRINT_DEBUG1	TxPrintf
#elif(DEBUG_MODE == 1)
#define PRINT_DEBUG3	
#define PRINT_DEBUG2	
#define PRINT_DEBUG1	TxPrintf
#elif(DEBUG_MODE == 0)
#define PRINT_DEBUG3	
#define PRINT_DEBUG2	
#define PRINT_DEBUG1	
#endif

extern void main(void);
extern void Delay(Uint32 Cnt);
extern void Init_System(void);
extern void Variable_Init(void);




//_MAIN_GLOBAL_ UINT32 Base_info_Write_Rom(void);
//_MAIN_GLOBAL_ UINT32 Base_info_Read_Rom(void);


