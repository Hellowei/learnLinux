#ifndef KEYBOARD_COMM_H
#define KEYBOARD_COMM_H

#define SYSKB_MODULE_ID									0x0A

#define SYSKB_RTN_KEYACK_ID								0x04
#define SYSKB_RTN_KEYSTAT_ID							0x79
#define SYSKB_RTN_KEYDATA_ID							0x78
#define SYSKB_RTN_KEYSYSINFO_ID							0x77
#define SYSKB_RTN_KEYSYSFANS_ID							0x76
#define SYSKB_RTN_KEYSYSPOWER_ID						0x7A
#define SYSKB_RTN_WATCHDOG_ID							0x73
#define SYSKB_RTN_VERSION_ID							0x74


typedef enum _syskb_rtn_data_index
{
	SYSKB_RTN_DATA_INDEX_KEYVAL,
	SYSKB_RTN_DATA_INDEX_KEYSTAT,
	SYSKB_RTN_DATA_INDEX_ACK,
	SYSKB_RTN_DATA_INDEX_INFO,
	SYSKB_RTN_DATA_INDEX_FANS,
	SYSKB_RTN_DATA_INDEX_MAX
}SYSKB_RTN_DATA_INDEX;

typedef enum _syskb_set_cmd_index
{
	SYSYKB_SET_CMD_INDEX_ACK,
	SYSYKB_SET_CMD_INDEX_SYSINFO,

	SYSYKB_SET_CMD_INDEX_MAX
}SYSYKB_SET_CMD_INDEX;

typedef enum _syskb_ack_result
{
	SYSKB_CMD_OK				= 0,
	SYSKB_CMD_CHECKSUM_ERROR	= 1,
	SYSKB_CMD_LENTH_ERROR	   = 2,
	SYSKB_CMD_INVALID		   = 3,
	SYSKB_CMD_PARAM_ERROR	   = 4,
	SYSKB_CMD_ACCEPT_ERROR	  = 5,

	SYSKB_CMD_RESULT_MAX
}SYSKB_ACK_RESULT;

typedef enum _syskb_key_code
{
	SYSKB_KEY_CODE_NULL		 = 0x00,
	SYSKB_KEY_CODE_ALARM		= 0x01,
	SYSKB_KEY_CODE_MENU		 = 0x02,
	SYSKB_KEY_CODE_ECGMENU	  = 0x03,
	SYSKB_KEY_CODE_NIBP		 = 0x04,
	SYSKB_KEY_CODE_PRINT		= 0x05,
	SYSKB_KEY_CODE_MAIN		 = 0x06,
	SYSKB_KEY_CODE_ENCODER_L	= 0x07,
	SYSKB_KEY_CODE_ENCODER_OK   = 0x08,
	SYSKB_KEY_CODE_ENCODER_R	= 0x09,
	SYSKB_KEY_CODE_FREEZE	   = 0x0A,
	SYSKB_KEY_CODE_POWEROFF	 = 0x0B,
	SYSKB_KEY_CODE_VOLPLUS	  = 0x0C,
	SYSKB_KEY_CODE_VOLMINUS	 = 0x0D,
	SYSKB_KEY_CODE_NEW		  = 0x0E,
	SYSKB_KEY_CODE_ZERO		 = 0x0F,
	SYSKB_KEY_CODE_EXIT		 = 0x10,
	SYSKB_KEY_CODE_PRESS		= 0x7F,
}SYSKB_KEY_CODE;

typedef enum _syskb_battery_lev
{
	SYSKB_BAT_LEV_NONE,
	SYSKB_BAT_LEV_ZERO,
	SYSKB_BAT_LEV_ONE,
	SYSKB_BAT_LEV_TWO,
	SYSKB_BAT_LEV_THREE,
	SYSKB_BAT_LEV_FULL,

	SYSKB_BAT_LEV_MAX
}SYSKBBATTERYLEV;


typedef enum _syskb_elec_type
{
	SYSKB_ELEC_TYPE_DC,
	SYSKB_ELEC_TYPE_AC,

	SYSKB_ELEC_TYPE_MAX
}SYSKBELECTYPE;

typedef enum _sysbk_cmd_index
{
	SYSKB_CMD_SW_PRINT,
	SYSKB_CMD_SW_NIBP,
	SYSKB_CMD_SW_CO2,
	SYSKB_CMD_SW_IBP,
	SYSKB_CMD_SW_IRBOARD,
	SYSKB_CMD_SW_ECG,
	SYSKB_CMD_SW_SPO2,
	SYSKB_CMD_RESET,
	SYSKB_CMD_DEBUG,
	SYSKB_CMD_SW_MODLE,
	SYSKB_CMD_REBOOT,
	SYSKB_CMD_POWER,
	SYSKB_CMD_MAX
}SYSKBCMD;


#ifndef KBCOMM_GLOBALS
#define KBCOMM_EXT extern
#else
#define KBCOMM_EXT
#endif /*_KBCOMM_H_*/

KBCOMM_EXT BOOL SysKbSendPack(PACKETFRAME *pack);
KBCOMM_EXT VOID SendSystemBoardCmd(SYSKBCMD cmd, UINT8 param);
KBCOMM_EXT VOID UpdateKeyboardStatus(VOID);
KBCOMM_EXT BOOL InitKboard(VOID);
KBCOMM_EXT VOID SysBrdPacketProc(PACKETFRAME *pack);
#endif
