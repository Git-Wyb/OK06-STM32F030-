#ifndef	__A_DATA_EXCHANGE_H__
#define __A_DATA_EXCHANGE_H__


u1 a_u1g_data_exchange0_word_to_byte(u2 u2a_worddata);
u1 a_u1g_data_exchange1_word_to_byte(u2 u2a_worddata);
u2 a_u2g_data_exchange_byte_to_word(u1 u1a_byte0,u1 u1a_byte1);
u2 a_u2g_pulse_exchange_to_rotation(u2 u2a_encoder_pulse);
u2 a_u2g_close_AD_exchange_to_Nm(u1 u1a_close_AD_data);
u2 a_u2g_close_Nm_exchange_to_AD(u2 u2a_close_Nm);

#endif




