#ifndef	__TRQ_ADJUST_TRQCHANGE_H__
#define __TRQ_ADJUST_TRQCHANGE_H__

void a_vog_trqajst_trqinitial(void);
void a_vog_trqajst_dataset(u1 u1a_trq_input);

/* #define TEST_HUKA_DEBUG */

#ifndef TEST_HUKA_DEBUG

#define U2_TRQ_AJST_HIGH_SPEED_105			((u2)155)
#define U2_TRQ_AJST_HIGH_SPEED_100			((u2)145)
#define U2_TRQ_AJST_HIGH_SPEED_95			((u2)137)

#else

#define U2_TRQ_AJST_HIGH_SPEED_105			((u2)22)
#define U2_TRQ_AJST_HIGH_SPEED_100			((u2)22)
#define U2_TRQ_AJST_HIGH_SPEED_95			((u2)22)

#endif

#endif	/* __TRQ_ADJUST_TRQCHANGE_H__ */




