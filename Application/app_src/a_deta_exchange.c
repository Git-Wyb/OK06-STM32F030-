#include <math.h>
#include "Sys.h"
#include "Timer.h"
#include "a_data_exchange.h"

#define F4L_PULSE_MOTOR_ROTATION	(f4)(4.0)			
#define F4L_GEAR_PERCENT			(f4)(36.54)			
#define	F4L_EX_CLOSE_VER_2JI		(f4)(0.0536)	
#define	F4L_EX_CLOSE_VER_1JI		(f4)(0.1053)	
#define	F4L_EX_CLOSE_VER_CONST		(f4)(0.056)		
#define	F4L_U2_MAX					(f4)(65535.0)	
#define	F4L_U2_MIN					(f4)(0.0)		
#define	F4L_ROTATION_RADIX			(f4)(10.0)		
#define	F4L_NM_RADIX				(f4)(100.0)			
#define	F4L_BORAD_MAX_VER			(f4)(5.0)	
#define	F4L_AD_MAX					(f4)(1024.0)
#define	U2L_AD_MAX					1024		


u1 a_u1g_data_exchange0_word_to_byte(u2 u2a_worddata)
{
	u2 u2a_workspace = 0;
	u1 u1a_bytedata = 0;

	u2a_workspace = u2a_worddata & 0x00ff;
	u1a_bytedata = (u1)u2a_workspace;

	return u1a_bytedata;

}


u1 a_u1g_data_exchange1_word_to_byte(u2 u2a_worddata)
{
	u2 u2a_workspace = 0;
	u1 u1a_bytedata = 0;

	u2a_workspace = u2a_worddata & 0xff00;
	u1a_bytedata = (u1)(u2a_workspace >> 8);

	return u1a_bytedata;

}


u2 a_u2g_data_exchange_byte_to_word(u1 u1a_byte0,u1 u1a_byte1)
{
	u2 u2a_workspace = 0;

	u2a_workspace = (u2)(u1a_byte1);
	u2a_workspace = u2a_workspace << 8;

	u2a_workspace += u1a_byte0;

	return u2a_workspace;

}

u2 a_u2g_pulse_exchange_to_rotation(u2 u2a_encoder_pulse)
{
	u2 u2a_rotation = 0;
	f4 f4a_motor_rotation = 0;

	f4a_motor_rotation = (f4)u2a_encoder_pulse / F4L_PULSE_MOTOR_ROTATION;
	u2a_rotation = (u2)(f4a_motor_rotation / F4L_GEAR_PERCENT * F4L_ROTATION_RADIX);

	return u2a_rotation;
}


u2 a_u2g_close_AD_exchange_to_Nm(u1 u1a_close_AD_data)
{
	u2 u2a_Nm = 0;		
	f4 f4a_VER = 0.0;	
	f4 f4a_result = 0.0;

	f4a_VER = (f4)u1a_close_AD_data * F4L_BORAD_MAX_VER / F4L_AD_MAX;
	f4a_result = (-F4L_EX_CLOSE_VER_1JI + sqrt(F4L_EX_CLOSE_VER_1JI * F4L_EX_CLOSE_VER_1JI - 4.0 * F4L_EX_CLOSE_VER_2JI * (F4L_EX_CLOSE_VER_CONST - f4a_VER))) * F4L_NM_RADIX / (2.0 * F4L_EX_CLOSE_VER_2JI);


	if(f4a_result > F4L_U2_MAX){
		u2a_Nm = U2L_MAX;
	}else if(f4a_result < F4L_U2_MIN){
		u2a_Nm = U2L_ZERO;
	}else{
		u2a_Nm = (u2)f4a_result;
	}
	
	return u2a_Nm;
}


u2 a_u2g_close_Nm_exchange_to_AD(u2 u2a_close_Nm)
{
	u2 u2a_AD_data = 0;
	f4 f4a_Nm = 0.0;		
	f4 f4a_VER = 0.0;		
	f4 f4a_result = 0.0;	

	f4a_Nm = (f4)u2a_close_Nm / F4L_NM_RADIX;	
	f4a_VER = F4L_EX_CLOSE_VER_2JI * f4a_Nm * f4a_Nm + F4L_EX_CLOSE_VER_1JI * f4a_Nm + F4L_EX_CLOSE_VER_CONST;
	f4a_result = f4a_VER * F4L_AD_MAX / F4L_BORAD_MAX_VER;

	
	if(f4a_result > F4L_AD_MAX){
		u2a_AD_data = U2L_AD_MAX;
	}else if(f4a_result < F4L_U2_MIN){
		u2a_AD_data = U2L_ZERO;
	}else{
		u2a_AD_data = (u2)f4a_result;
	}
	
	return u2a_AD_data;
}

