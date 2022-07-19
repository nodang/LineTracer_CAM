//###########################################################################
//
// FILE		: Variable.h
//
// TITLE	: Variable.h file.
//
// Author	: Yuk Keun Ho
//
// Company	: Maze & Hz
//
//###########################################################################
// $Release Date: 2011.10.6 $
//###########################################################################



#ifdef _MAIN_
	#ifndef __VARIABLE_EXT__
		#define __VARIABLE_EXT__
	#endif
#else
	#ifndef __VARIABLE_EXT__
		#define __VARIABLE_EXT__	extern
	#endif
#endif	

#define SCI_ISR_ON								\
	do {										\
		SciaRegs.SCICTL2.bit.RXBKINTENA = 1;	\
	} while(0)
#define SCI_ISR_OFF								\
	do {										\
		SciaRegs.SCICTL2.bit.RXBKINTENA = 0;	\
	} while(0)

typedef struct
{
	int32 position_i32;
	int32 velocity_i32;

	unsigned char buf[128];
} SciData;

__VARIABLE_EXT__ SciData sd;

typedef struct
{
	_iq17 value;
	_iq17 increase_rate;

	_iq17 gain;

	_iq17 pos_dec;
	_iq17 pos_acc;
} MotorData;

__VARIABLE_EXT__ MotorData rmotor;
__VARIABLE_EXT__ MotorData lmotor;

