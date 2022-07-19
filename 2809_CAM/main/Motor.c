//###########################################################################
//
// FILE		: Motor.c
//
// TITLE	: Motor c file.
//
// Author	: Yuk Keun Ho
//
// Company	: Maze & Hz
//
//###########################################################################
// $Release Date: 2011.10.16 $
//###########################################################################

#define   _MOTOR_


#include "DSP280x_Device.h"
#include "DSP280x_Examples.h"   // DSP280x Examples Include File
#include "Main.h"
#include "Motor.h"

#define MAX_PWM_VAL	2500

#define RIGHT_DIR	0x00000002		// 0000 0000 0000 0000  0000 0000 0000 0010
#define LEFT_DIR	0x00000020		// 0000 0000 0000 0000  0000 0000 0010 0000

#define FORWARD_DIR		0x00000002
#define BACK_DIR		0x00000020
#define RIGHT_SPIN_DIR	0x00000000
#define LEFT_SPIN_DIR	0x00000022

#define RMOTOR_PWM_VAL	EPwm1Regs.CMPA.half.CMPA
#define LMOTOR_PWM_VAL	EPwm3Regs.CMPA.half.CMPA

#define R_DIR	GpioDataRegs.GPADAT.bit.GPIO1
#define L_DIR	GpioDataRegs.GPADAT.bit.GPIO5

#define DECIDE_DIR(x)															\
	do {																		\
		GpioDataRegs.GPADAT.all = x | (GpioDataRegs.GPADAT.all & 0xffffffdd);	\
	} while(0)

#define LIMIT_VAL(x)															\
	do {																		\
		if(x > _IQ17(MAX_PWM_VAL))			x = _IQ17(MAX_PWM_VAL);				\
		else if(x < -_IQ17(MAX_PWM_VAL))	x = -_IQ17(MAX_PWM_VAL);			\
	} while(0)

static void _motor_struct_init(MotorData *p_motor);
static void _motor_handle(void);

void motor_init(void)
{	
	DECIDE_DIR(FORWARD_DIR);

	RMOTOR_PWM_VAL = 0;
	LMOTOR_PWM_VAL = 0;

	EPwm1Regs.TBPRD = MAX_PWM_VAL;
	EPwm3Regs.TBPRD = MAX_PWM_VAL;

	memset((void*)&sd, 0x00, sizeof(SciData));

	_motor_struct_init(&rmotor);
	_motor_struct_init(&lmotor);

	//sd.velocity_i32 = 500;
	//sd.position_i32 = -10;
}

static void _motor_struct_init(MotorData *p_motor)
{
	p_motor->value = _IQ17(0.0);
	p_motor->increase_rate = _IQ17(0.5);

	p_motor->gain = _IQ17(0.0);

	p_motor->pos_acc = _IQ17(0.05);
	p_motor->pos_dec = _IQ17(0.05);
}

static void _motor_handle(void)
{
	_iq17 sci_pos = ((long)sd.position_i32) << 17;

	// right turn pos minus
	if(sci_pos > _IQ17(0.0))		// left_turn
	{
		rmotor.gain = _IQ17(1.0) + _IQ17mpy(sci_pos, rmotor.pos_acc);
		lmotor.gain = _IQ17(1.0) - _IQ17mpy(sci_pos, lmotor.pos_dec);
	}
	else if(sci_pos < _IQ17(0.0))
	{
		rmotor.gain = _IQ17(1.0) + _IQ17mpy(sci_pos, rmotor.pos_dec);
		lmotor.gain = _IQ17(1.0) - _IQ17mpy(sci_pos, lmotor.pos_acc);
	}
	else
	{
		rmotor.gain = _IQ17(1.0);
		lmotor.gain = _IQ17(1.0);
	}
}

interrupt void motor_ISR(void)
{
	_iq17 sci_rval = ((long)sd.velocity_i32) << 17;	
	_iq17 sci_lval = ((long)sd.velocity_i32) << 17;

	_motor_handle();

	sci_rval = _IQ17mpy(sci_rval, rmotor.gain);
	sci_lval = _IQ17mpy(sci_lval, lmotor.gain);

	if(rmotor.value < sci_rval)
	{
		rmotor.value += rmotor.increase_rate;
	}
	else if(rmotor.value > sci_rval)
	{
		rmotor.value -= rmotor.increase_rate;
	}

	if(lmotor.value < sci_lval)
	{
		lmotor.value += lmotor.increase_rate;
	}
	else if(lmotor.value > sci_lval)
	{
		lmotor.value -= lmotor.increase_rate;
	}

	LIMIT_VAL(rmotor.value);	
	LIMIT_VAL(lmotor.value);

	if(rmotor.value < 0)	
	{
		GpioDataRegs.GPACLEAR.bit.GPIO1 = 1;

		RMOTOR_PWM_VAL = (Uint16)((-rmotor.value) >> 17);
	}
	else
	{
		GpioDataRegs.GPASET.bit.GPIO1 = 1;

		RMOTOR_PWM_VAL = (Uint16)(rmotor.value >> 17);
	}

	if(lmotor.value < 0)
	{
		GpioDataRegs.GPASET.bit.GPIO5 = 1;

		LMOTOR_PWM_VAL = (Uint16)((-lmotor.value) >> 17);
	}
	else
	{
		GpioDataRegs.GPACLEAR.bit.GPIO5 = 1;

		LMOTOR_PWM_VAL = (Uint16)(lmotor.value >> 17);
	}
}

