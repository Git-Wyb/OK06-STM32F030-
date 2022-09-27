
#ifndef _STORAGE_INCLUDED
#define _STORAGE_INCLUDED

#include "Sys.h"


#define STORAGE_ID_SIZE_STUDY_LOAD	20	
#define STORAGE_ID_SIZE_RECORD_ERR1	20
#define STORAGE_ID_SIZE_RECORD_ERR2	80	
#define STORAGE_ID_SIZE_STUDY_BASE	6	
#define STORAGE_ID_SIZE_FACTORY		4	
#define STORAGE_ID_MAX_SIZE			STORAGE_ID_SIZE_RECORD_ERR2


typedef enum {
	STORAGE_STUDY_LOAD,		
	STORAGE_RECORD_ERR1,
	STORAGE_RECORD_ERR2,	
	STORAGE_STUDY_BASE,	
	STORAGE_FACTORY		
} storage_id;
#define N_STORAGE_ID	5


typedef union {
	u1 strgdat[STORAGE_ID_MAX_SIZE];
	TYPE_FLASH_LEARN_BODY strgload;
	TYPE_FLASH_ERROR_BODY_1 strgrecorderr1;
	TYPE_FLASH_ERROR_BODY_2 strgrecorderr2;
	TYPE_FLASH_HSIZE_BODY strgbase;
	TYPE_FLASH_FACT_BODY factory;
} strg_blk;

/* EEL status set  */
typedef enum  {                                             /* ---------------------------------------------------- */
                EEL_OK                    = (0x00 | 0x00),  /* 0x00, no error occurred                              */
                EEL_BUSY                  = (0x00 | 0x01),  /* 0x01, request is under processing                    */
                EEL_ERR_CONFIGURATION     = (0x80 | 0x02),  /* 0x82, bad FDL or EEL configuration                   */
                EEL_ERR_INITIALIZATION    = (0x80 | 0x03),  /* 0x83, EEL_Init(), EEL_Open missed                    */
                EEL_ERR_ACCESS_LOCKED     = (0x80 | 0x04),  /* 0x84, STARTUP missing or fatal operation error       */
                EEL_ERR_PARAMETER         = (0x80 | 0x05),  /* 0x85, wrong parameter (wrong command or identifier)  */
                EEL_ERR_VERIFY            = (0x80 | 0x06),  /* 0x86, verify error on any byte in active block       */
                EEL_ERR_REJECTED          = (0x80 | 0x07),  /* 0x87, another request already under processing       */
                EEL_ERR_NO_INSTANCE       = (0x80 | 0x08),  /* 0x88, no instance found (variable never written)     */
                EEL_ERR_POOL_FULL         = (0x80 | 0x09),  /* 0x89, no space for writing data                      */
                EEL_ERR_POOL_INCONSISTENT = (0x80 | 0x0A),  /* 0x8A, no active block found within EEL-pool          */
                EEL_ERR_POOL_EXHAUSTED    = (0x80 | 0x0B),  /* 0x8B, EEL pool to small for correct operation        */
                EEL_ERR_INTERNAL          = (0x80 | 0x0C)   /* 0x8C, internal error (should never occur)            */
              } eel_status_t; 
                /* EEL command set  */
typedef enum  {                                             /* ---------------------------------------------------- */
                EEL_CMD_UNDEFINED         = (0x00 | 0x00),  /* 0x00, undefined command (initial value)              */
                EEL_CMD_STARTUP           = (0x00 | 0x01),  /* 0x01, plausibility check of the EEL data and driver  */
                EEL_CMD_WRITE             = (0x00 | 0x02),  /* 0x02, creates a new instance of EEL variable         */
                EEL_CMD_READ              = (0x00 | 0x03),  /* 0x03, reads last instance of the EEL variable        */
                EEL_CMD_REFRESH           = (0x00 | 0x04),  /* 0x04, copy all last instances into a new active block*/
                EEL_CMD_VERIFY            = (0x00 | 0x05),  /* 0x05, verifies electrically byte by byte the         */
                                                            /*       complete active block                          */
                EEL_CMD_FORMAT            = (0x00 | 0x06),  /* 0x06, format the EEL pool, all instances are lost    */
                EEL_CMD_SHUTDOWN          = (0x00 | 0x07)   /* 0x07, deactivates the EEL in secure state            */
              } eel_command_t; 

typedef struct {                                            /* ---------------------------------------------------- */
         u1*       address_pu08;       /* 2, r/w, source/destination RAM-address               */
         u1        identifier_u08;     /* 1, w,   variable identifier                          */
         eel_command_t  command_enu;        /* 1, w,   command has to be processed                  */
         eel_status_t   status_enu;         /* 1, r,   error code after command execution           */
} eel_request_t;

//¹²400Byte£¬addr£º0-399
#define ADDR_STORAGE_ID0    0
#define ADDR_STORAGE_ID1    80
#define ADDR_STORAGE_ID2    160
#define ADDR_STORAGE_ID3    240
#define ADDR_STORAGE_ID4    320

void storage_init(void);						
void storage_memory_handler(void);				
void get_storage_data(storage_id, u1 *);		
void store_storage_data(storage_id, const u1 *);
u1 check_storage_cmd_idle(void);				

#endif
