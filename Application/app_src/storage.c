
#define _STORAGE_DEFINE

#include "Sys.h"
#include "def_local.h"
#include "M24C16.h"
#include "storage.h"
#include "variables.h"

const u1 c_storage_id_size[N_STORAGE_ID] = {
	STORAGE_ID_SIZE_STUDY_LOAD,
	STORAGE_ID_SIZE_RECORD_ERR1,
	STORAGE_ID_SIZE_RECORD_ERR2,
	STORAGE_ID_SIZE_STUDY_BASE,
	STORAGE_ID_SIZE_FACTORY
};


typedef enum {
	STRGMEM_OK,		
	STRGMEM_NG,	
	STRGMEM_READ,	
	STRGMEM_WRITE,
	STRGMEM_VERIFY,
	STRGMEM_REWRITE,
	STRGMEM_REFRESH	
} mem_cmd;
#define N_STRGMEM_CMD	7	

typedef struct {
	mem_cmd cmd;		
	storage_id id;	
} strg_cmd;	


typedef enum {
	STRG_HNDL_NO_AVAIL,	
	STRG_HNDL_UNFORMAT,
	STRG_HNDL_IDLE,	
	STRG_HNDL_BUSY	
} strg_hndl_st;		


strg_blk storage[N_STORAGE_ID] = {0};	
STATIC strg_blk strg_verify = {0};			
//STATIC eel_request_t eel_req;			
//STATIC strg_hndl_st eel_status;		

#define N_CMDBUF	32	
//STATIC strg_cmd strg_cmdbuf[N_CMDBUF];	
//STATIC u1 u1l_top_strg;					
//STATIC u1 u1l_btm_strg;				


//STATIC strg_hndl_st open_storage_driver(void);
STATIC bool read_storage_all(bool);
//STATIC bool format_memory(void);
//STATIC void exec_cmd_EEL(eel_command_t);
//STATIC void set_strg_mem_command(mem_cmd, storage_id);
//STATIC void strg_mem_exec_EEL(mem_cmd cmd);
//STATIC void set_param_EEL(mem_cmd cmd);
//STATIC void chk_result_strg_mem_verify(void);
STATIC void set_storage_data(storage_id strg_id, const u1 *info);

u2 Storage_AddrBuf[5] = {ADDR_STORAGE_ID0,ADDR_STORAGE_ID1,ADDR_STORAGE_ID2,ADDR_STORAGE_ID3,ADDR_STORAGE_ID4};

void storage_init(void)
{
	Init_M24C16();
	(void) read_storage_all(TRUE);
}


//STATIC strg_hndl_st open_storage_driver(void)
//{
//	strg_hndl_st hndl = STRG_HNDL_NO_AVAIL;

//	R_WDT_Restart();
//	if (FDL_Init(&fdl_descriptor_str) == FDL_OK) {
//		FDL_Open();
//		R_WDT_Restart();
//		if (EEL_Init() == EEL_OK) {
//			R_WDT_Restart();
//			EEL_Open();
//			R_WDT_Restart();

//			exec_cmd_EEL(EEL_CMD_STARTUP);

//			switch (eel_req.status_enu) {
//			case EEL_OK:
//				hndl = STRG_HNDL_IDLE;
//				break;
//			case EEL_ERR_POOL_INCONSISTENT:
//				hndl = STRG_HNDL_UNFORMAT;
//				break;
//			default:
//				break;
//			}
//		}
//	}
//	return hndl;
//}


STATIC bool read_storage_all(bool preset)
{
	u1 i;
	bool result = TRUE;

	for (i = 0; i < N_STORAGE_ID; i++)
    {	
        M24C16_Read(i*80,&storage[i].strgdat[0],80);
		R_WDT_Restart();
	}
	return result;
}


//STATIC bool format_memory(void)
//{
//	bool ret = FALSE;

//	exec_cmd_EEL(EEL_CMD_FORMAT);
//	if (eel_req.status_enu == EEL_OK) {
//		exec_cmd_EEL(EEL_CMD_STARTUP);
//		if (eel_req.status_enu == EEL_OK) {
//			eel_status = STRG_HNDL_IDLE;
//			ret = TRUE;
//		}
//	}
//	return ret;
//}


//test STATIC void exec_cmd_EEL(eel_command_t cmd)
//{
//	eel_req.command_enu = cmd;
//	//EEL_Execute(&eel_req);
//	while (eel_req.status_enu == EEL_BUSY) {
//		//EEL_Handler();
//		R_WDT_Restart();
//	}
//}


void get_storage_data(storage_id strg_id, u1 *info)
{
	u1 i = 0;

	for (i = 0; i < c_storage_id_size[strg_id]; i++) {
		info[i] = storage[strg_id].strgdat[i];
	}
}


STATIC void set_storage_data(storage_id strg_id, const u1 *info)
{
	u1 i = 0;
	
	for (i = 0; i < c_storage_id_size[strg_id]; i++) {
		if (storage[strg_id].strgdat[i] != info[i]) {
			storage[strg_id].strgdat[i] = info[i];
		}
	}
}


void store_storage_data(storage_id strg_id, const u1 *info)
{
    u1 i = 0,j = 0;
	set_storage_data(strg_id, info);
    
    M24C16_Write(Storage_AddrBuf[strg_id],&storage[strg_id].strgdat[0],c_storage_id_size[strg_id]);
    R_WDT_Restart();
    M24C16_Read(Storage_AddrBuf[strg_id],&strg_verify.strgdat[0],c_storage_id_size[strg_id]);
    R_WDT_Restart();
    for(i=0; i<c_storage_id_size[strg_id]; i++)
    {
        if(strg_verify.strgdat[i] != storage[strg_id].strgdat[i])
        {
            j = 1;
            break;
        }
    }
    if(j == 1)  M24C16_Write(Storage_AddrBuf[strg_id],&storage[strg_id].strgdat[0],c_storage_id_size[strg_id]);
    j = 0;
    R_WDT_Restart();
//test	set_strg_mem_command(STRGMEM_WRITE, strg_id);	
}


/************************************************/
//test STATIC void set_strg_mem_command(mem_cmd cmd, storage_id strg_id)
//{
//	strg_cmdbuf[u1l_btm_strg].cmd = cmd;
//	strg_cmdbuf[u1l_btm_strg].id = strg_id;
//	if (++u1l_btm_strg >= N_CMDBUF) {
//		u1l_btm_strg = 0;
//	}
//}


//test void storage_memory_handler(void)
//{
//	mem_cmd mcmd;

//	switch (eel_status) {
//	case STRG_HNDL_IDLE:
//		if (u1l_top_strg != u1l_btm_strg) {
//			if (strg_cmdbuf[u1l_top_strg].cmd >= STRGMEM_READ) {
//				//strg_mem_exec_EEL(strg_cmdbuf[u1l_top_strg].cmd);
//			} else {
//				if (++u1l_top_strg >= N_CMDBUF) {
//					u1l_top_strg = 0;
//				}
//			}
//		}
//		break;
//	case STRG_HNDL_BUSY:
//		//EEL_Handler();
//		if (eel_req.status_enu != EEL_BUSY) {	
//			eel_status = STRG_HNDL_IDLE;
//			switch (strg_cmdbuf[u1l_top_strg].cmd) {
//			case STRGMEM_WRITE:
//				switch (eel_req.status_enu) {
//				case EEL_OK:
//					mcmd = STRGMEM_VERIFY;
//					break;
//				case EEL_ERR_POOL_FULL:
//					mcmd = STRGMEM_REFRESH;
//					break;
//				default:
//					mcmd = STRGMEM_REWRITE;
//					break;
//				}
//				set_strg_mem_command(mcmd, strg_cmdbuf[u1l_top_strg].id);
//				break;
//			case STRGMEM_VERIFY:
//				if (eel_req.status_enu == EEL_OK) {
//					chk_result_strg_mem_verify();
//				} else {
//					set_strg_mem_command(STRGMEM_REWRITE, strg_cmdbuf[u1l_top_strg].id);
//				}
//				break;
//			case STRGMEM_REFRESH:
//				if (eel_req.status_enu == EEL_OK) {
//					set_strg_mem_command(STRGMEM_WRITE, strg_cmdbuf[u1l_top_strg].id);
//				}
//				break;
//			case STRGMEM_READ:
//			case STRGMEM_REWRITE:
//			default:
//				break;
//			}
//			strg_cmdbuf[u1l_top_strg].cmd = (eel_req.status_enu == EEL_OK) ? STRGMEM_OK : STRGMEM_NG;
//			if (++u1l_top_strg >= N_CMDBUF) {
//				u1l_top_strg = 0;
//			}
//		}
//		break;
//	default:	/* STRG_HNDL_NO_AVAIL, STRG_HNDL_UNFORMAT */
//		break;
//	}
//}


//test STATIC void strg_mem_exec_EEL(mem_cmd cmd)
//{
//	static const eel_command_t eel_cmd[N_STRGMEM_CMD] = {
//		EEL_CMD_WRITE,	/* dummy */
//		EEL_CMD_WRITE,	/* dummy */
//		EEL_CMD_READ,	
//		EEL_CMD_WRITE,
//		EEL_CMD_READ,
//		EEL_CMD_WRITE,
//		EEL_CMD_REFRESH	
//	};

//	set_param_EEL(cmd);
//	eel_req.command_enu = eel_cmd[cmd];
//	//EEL_Execute(&eel_req);
//	eel_status = STRG_HNDL_BUSY;
//}

/********************************************/

//test STATIC void set_param_EEL(mem_cmd cmd)
//{
//	if (cmd == STRGMEM_VERIFY) {
//		eel_req.address_pu08 = &strg_verify.strgdat[0];
//	} else {
//		eel_req.address_pu08 = &storage[strg_cmdbuf[u1l_top_strg].id].strgdat[0];
//		eel_req.identifier_u08 = (u1) strg_cmdbuf[u1l_top_strg].id + 1;
//	}
//}

//test STATIC void chk_result_strg_mem_verify(void)
//{
//	u1 i;
//	
//	for (i = 0; i < c_storage_id_size[strg_cmdbuf[u1l_top_strg].id]; i++) {
//		if (storage[strg_cmdbuf[u1l_top_strg].id].strgdat[i] != strg_verify.strgdat[i]) {	
//			set_strg_mem_command(STRGMEM_REWRITE, strg_cmdbuf[u1l_top_strg].id);
//			break;
//		}
//	}	
//}


//test u1 check_storage_cmd_idle(void) {
//	return (u1) (u1l_top_strg == u1l_btm_strg);
//}


