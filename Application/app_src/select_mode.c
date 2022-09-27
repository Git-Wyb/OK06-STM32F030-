#include "Sys.h"
#include "variables.h"

u1 select_mode(void)
{
	if(u1g_signal >= NUM_SIGNAL ){
		return 254;
	}
	else{}
	
	if(u1g_previous_mode < NUM_MODE11 ){
		return u1g_state11[u1g_signal][u1g_previous_mode];
	}
	else{}

	if( (u1g_previous_mode >= 10 ) && (u1g_previous_mode < (NUM_MODE21 + 10))){
		return u1g_state21[u1g_signal][u1g_previous_mode - 10];
	}
	else{}
	
	if((u1g_previous_mode >= 20) && (u1g_previous_mode < (NUM_MODE31 + 20))){
		return u1g_state31[u1g_signal][u1g_previous_mode - 20];
	}
	else{}
	
	if((u1g_previous_mode >= 100) && (u1g_previous_mode < (NUM_MODE51 + 100))){
		return u1g_state51[u1g_signal][u1g_previous_mode - 100];
	}
	else{}
	
	if((u1g_previous_mode >= 160) && (u1g_previous_mode < (NUM_MODE61 + 160))){
		return u1g_state61[u1g_signal][u1g_previous_mode - 160];
	}
	else{}

	if((u1g_previous_mode >= 180) && (u1g_previous_mode < (NUM_MODE71 + 180))){
		return u1g_state71[u1g_signal][u1g_previous_mode - 180];
	}
	else{}
	
	return 254;
}


