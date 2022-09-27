/*************************************************************/
/*  flash_access */
/*  èàóù */
/*************************************************************/


#ifndef ACCESS_FLASH
#define ACCESS_FLASH

#include "Sys.h"
#include "constants.h"
#include "def_local.h"

void access_flash_main(void);
void init_flash(void);
void datf_task(void);
void flash_write_erase_task(void);
void flash_read_data_task(void);
void flash_soft_clear(void);
void h_size_data_clear(void);
void check_sum_data(void);
void reset_flash_learndata(void);
bool check_flash_learndata(void);

extern u1 u1g_fg_data_erase;
extern u1 u1g_fg_block_format;
extern u1 u1g_fg_data_read;
extern u2 u2g_flash_read_data[FLASH_DATA_SIZE];
extern u2 u2g_soft_clear_timer_counter;


#endif
