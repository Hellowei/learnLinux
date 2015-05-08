/*****************************************************************************************
版权所有:			和心重典
版本号:				1.0.0
生成日期:			2011.04.15
文件名:				
作者:				和心重典
功能说明:			
其它说明:			无
所属文件关系:		本文件为工程规约代码文件

修改记录:
记录1:
修改者:
修改日期:
修改内容:
修改原因:
*****************************************************************************************/
#if !defined(_KB_H)
#define	  _KB_H

#define  KB_NOTIFY_ACK()		   sem_post(&IoAckMbox)
#define  KB_WAIT_ACK()			 sem_wait(&IoAckMbox)


#define  KB_POWER_12V_TOOHI_FLAG   0x01
#define  KB_POWER_12V_TOOLO_FLAG   0x02
#define  KB_POWER_5V_TOOHI_FLAG	0x01
#define  KB_POWER_5V_TOOLO_FLAG	0x02
#define  KB_BATT_TOOLO_FLAG		0x10


// After sending command, sleep for a while if need waiting for
// acknowledgement. See OS_TIME_TICK for how long one tick is.
#define KB_DELAY_FOR_RCV_ACK   60 // (60 / 20 + 1)//OS_TICK_TIME)
#if 0
static UINT8  Kb_MsgPackMapTab[][2] = {
	/*packet head	mask				   */
	{ 0x78,		  0xff },  /*按键数据(78)*/
	{ 0x79,		  0xff },  /*系统状态(79)*/
	{ 0x7B,		  0xff },  /*触摸数据(7B)*/
	{ 0x7D,		  0xff },  /*报警数据(7D)*/
	{ 0x7A,		  0xff },  /*氧浓度数据(7A)*/
	{ 0x7C,		  0xff },  /*氧浓度校准(7C)*/
	{ 0x77,		  0xff },  /*系统参数数据（77）*/
	{ 0x04,		  0xff },  /*校准数据包(04)*/
};

#define NUM_KB_RCVAPCKET  TABLESIZE(Kb_MsgPackMapTab)
#endif
#define ID_KEYBOARD_KEY		(0x78)		/*按键数据(78)*/
#define ID_KEYBOARD_SDS		(0x79)		/*系统状态(79)*/
#define ID_KEYBOARD_TS		(0x7B)		/*触摸数据(7B)*/
#define ID_KEYBOARD_ALARM	(0x7D)		/*报警数据(7D)*/
#define ID_KEYBOARD_O2		(0x7A)		/*氧浓度数据(7A)*/
#define ID_KEYBOARD_O2ADJ	(0x7C)		/*氧浓度校准(7C)*/
#define ID_KEYBOARD_PARAM	(0x77)		/*系统参数数据（77）*/
#define ID_KEYBOARD_ACK		(0x04)		/*主板向按键板发送应答数据(04)*/

/* 报警级别 */
typedef enum  _kb_alm_lev {
   KB_ALM_LEV_NO_ALARM,
   KB_ALM_LEV_LOW,
   KB_ALM_LEV_MED,
   KB_ALM_LEV_HIGH

} KBALARMLEVEL;

/* 音量级别 */
typedef enum _kb_vol_lev {
   KB_VOLUME_LEV_SILENCE,
   KB_VOLUME_LEV_LOW,
   KB_VOLUME_LEV_MED,
   KB_VOLUME_LEV_HIGH
} KBVOLUMELEVEL;

/* 按键板指令ID. */
typedef enum _kb_cmd_id {

   CMD_KB_SET_ALARM_LEVEL,	  /* 设置报警级别		 */
   CMD_KB_SET_ALARM_VOLUME,	 /* 设置报警音量		 */
   CMD_KB_SET_BEAT_VOLUME,	  /* 心跳声音量		   */
   CMD_KB_SET_KNOB_VOLUME,	  /* 键盘声音量		   */
   CMD_KB_SET_KNOB_SOUND,
   CMD_KB_SET_ALM_SOUND,
   CMD_KB_REQ_SELF_TEST,		/* 请求自检结果		 */
   CMD_KB_SET_PULSE_VOLUME,	 /* 设置脉搏音量		 */
   CMD_KB_SET_VERSION,			/* 设置按键板的协议版本 */
   CMD_KB_SET_NURSECALL,		/* 设置nurse call	   */
   CMD_KB_SWITCH_NURSECALL,	 /* 开关nurse call报警   */
   CMD_KB_REQ_SHUTOFF_POWER,	/* 请求关机			 */
   
   CMD_KB_MAX

} KBCMDID;

/* 按键板 消息包ID */
typedef enum  _msgpack_id {

	MSGPACK_KB_KNOB_ROTATE_RIGHT,  /* 编码器右旋		*/
	MSGPACK_KB_KNOB_ROTATE_LEFT,   /* 编码器左旋		*/
	MSGPACK_KB_KNOB_ROTATE_DOWN,   /* 编码器按下		*/
	MSGPACK_KB_KEY_MENU,		   /* 按键, 菜单		*/
	MSGPACK_KB_KEY_NIBP,		   /* 按键, NIBP		*/
	MSGPACK_KB_KEY_RECORD,		 /* 按键, 记录		*/
	MSGPACK_KB_KEY_PAUSE,		  /* 按键, 暂停		*/
	MSGPACK_KB_KEY_FREEZE,		 /* 按键, 冻结		*/
	MSGPACK_KB_KEY_MAIN,		   /* 按键, 主屏		*/
	MSGPACK_KB_KYE_ALARM,		  /* 按键, 报警设置	*/
	MSGPACK_KB_KEY_SILENCE,		/* 按键, 静音		*/
	MSGPACK_KB_KEY_SHORTCUT,	   /* 任意键短路		*/
	MSGPACK_KB_KEY_SHUTOFF,		/* 按键, 关机		*/
	MSGPACK_KB_VER_PROTOCOL,	   /* 协议版本		  */
	MSGPACK_KB_BATT_VOLUME,		/* 电池电量		  */
	MSGPACK_KB_SELFTEST,		   /* 自检结果		  */
	MSGPACK_KB_POWER_STATE,		/* 电源状态		  */
	MSGPACK_KB_VER_SOFTWARE,	   /* 软件版本		  */
	MSGPACK_KB_ESCAPE,			 /* 转义符,为以后扩展 */

	MSGPACK_KB_MAX
} KBMSGPACKID;

#define SHORT_CUT_ALM_PRESENT_TIME  ( 3000 / MSECOND_OF_TICK )

typedef enum _kb_ACK_id{
	KB_ACK_SUCCESS,
	KB_ACK_CHECKSUM_ERROR,
	KB_ACK_PACKLENG_ERROR,
	KB_ACK_NULL_CMD,
	KB_ACK_CMDPARAMDATA_ERROR,
	KB_ACK_NOTACCEPT_CMD
}KEYPACKDATAACKSINGLE;
typedef enum{
	KB_ALL_SOUND_MODULE,
	KB_KEY_SOUND_MODULE,
	KB_ALM_SOUND_MODULE,
	KB_BEAT_SOUND_MODULE,
	KB_PULSE_SOUND_MODULE
}KBSOUND_MODULE;
typedef enum{
	KB_PHYSALM_LEV,
	KB_FLUSH_ALARM,
	KB_PULSE_STATUS,
	KB_PHYS_ALARM,
	KB_TECH_ALARM,
	KB_BEAT_STATUS,
	KB_ALARM_PAUSE
}KBALARM_MODULE;
typedef struct 
{
	UINT8	Nibp;
	UINT8	Rec;
	UINT8	Zero;
	UINT8	TouchDisp;
	UINT8	BackLight_Level;
} KEYBOARDLAMP ,*PKEYBOARDLAMP;	
typedef struct 
{
	INT8	kbvol;
	INT8	alarmVolume;
	INT8	selectBeep;
	INT8	Almflush;
	INT8	Pulsestatus;
	INT8	Beatstatus;
	INT8	PhsAlmstatus;
	INT8	TechAlmstatus;
	INT8	PhsAlmLev;
	INT8	TechAlmflag;			//开机第一次不报警
}KBALARMINFO ,*PKBALARMINFO;
typedef struct 
{
	UINT8	status5v;		//00：电压正常，01：电压太高，10：电压太低
	UINT8	status12v;		//00：电压正常，01：电压太高，10：电压太低
	UINT8	volume;			//000---111： 电池电量节数，0 电池电量空，7：电池电量满电
	UINT8	ACtype;			//交流状态：  0: 电池供电， 1：交流电供电
	UINT8	Chargstatus;	//充电状态：  0：正在充电， 1：电池充满 (在有电池时候，数据有效)
	UINT8	Battestatus;	//电池状态：  00：有电池， 01：没有电池， 10：电池故障
}KBBATTERLINFO ,*PKBBATTERLINFO;
typedef struct
{
	UINT8  key_msg; 
	UINT8  nibpflag;
	UINT8  recdlgstatus;
}KBACKINFO , *PKBACKINFO;
typedef struct _kb_info {
   UINT8   shortcut;
   UINT8   cpuError;
   UINT8   wdError;
   UINT8   ramError;
   UINT8   romError;
   UINT8   protocol;  /* 按键板的通讯协议版本10表示1.0版	 11表示:1.1版 */
}KBINFO;


extern KBINFO  KbInfo;
extern UINT8   Kb_CurrPack;			 /* 当前发送的数据包			*/
extern UINT8   Kb_AckPack;			  /* 接收的相应包				*/
extern UINT8   Kb_SelfTestResult;	   /* 自检结果;系统暂时不处理.	*/
extern INT8	Kb_Acked;				/* 是否响应.TRUE, 已经响应.	*/
extern INT8	Kb_TimeEscaped;		  /* 对于指令允许的最大响应时间. */
extern INT8	Kb_TimeRest;			 /* 时间计数器				  */
extern INT8	KbCmdNeedAck[CMD_KB_MAX];
extern UINT8   KbCmdPackMapTbl[][2];
extern KEYBOARDLAMP		keyboardlamp;   /* 按键板灯处理					*/
extern KBALARMINFO		 keyboardsound;	/* 按键板报警信息处理			*/
extern KBACKINFO		keyboardACK;	/* 按键板ACK信息				*/
extern KBBATTERLINFO	KBbatteryinfo;	/* 按键板电池电量信息				*/


BOOL  InitKboard(VOID);
VOID  KbCheckAckPacks(VOID);
VOID  KbUnpackProc (VOID);

VOID  KbSetAlmLevel(UINT8 level);
VOID  KbSetAlmVolume(UINT8 volume);
VOID  KbSetBeatVolume(UINT8 volume);
VOID  KbSetKeyVolume(UINT8 volume);
VOID  KbSetPulseVolume(UINT8 volume);
VOID  KbSetVersion(UINT8 ver);
VOID  KbSetNurseCallMode(UINT8 mode);
VOID  KbSwitchNurseCall(UINT8 flag);
VOID  KbQuerySelfTest(VOID);

INT32  KbSendPacket2(UINT8 cmd_id, UINT32 lParam);
BOOL   InitKeyModule (VOID); //add by empty 2011/04/28

UINT8 AnalysisIDKeyPack(UINT8 *data);
BOOL  Keyboard_RcvACKPACK(UINT8 *data);
VOID  ACKIDKeyPackSend (UINT8 single);
VOID  InitKeyBoardAlarmInfo(VOID);
VOID  KeyBoardSignalLampSet (UINT8 key_msg ,PKEYBOARDLAMP pKBlamp);
VOID  Keyboard_ProcRcvPack(UINT8 key, UINT8 *data);
VOID  AlarmInfoPackSend(PKBALARMINFO pKBAlarm);
VOID AdjustRECLampSingle (VOID);
VOID AdjustNIBPLampSingle (VOID);
VOID AdjustZEROLampSingle (VOID);
VOID AdjustTOUCHLampSingle (VOID);
extern	VOID AdjustKeyBoardLampSingle (VOID);
extern	VOID RECLampONOFF (UINT8 status);
extern	VOID KeyBoardSetMonitorALMFlag(UINT8 alarm_module,INT8 Single,PKBALARMINFO pKBAlarm);
extern	VOID CleanKeyBoardAlarm(VOID);
extern	VOID KeyBoardChangMonitorVol(UINT8 sound_module,INT8 sound_level);
extern	VOID KBTechAlarmTriggerSound(VOID);
extern	VOID ShowMonitorPower (UINT8 KBVolume);
extern	VOID ShowMonitorBattery(UINT8 KBVolume);
extern	VOID ShowMonitorBatteryIcon(VOID);
extern	VOID MonitorVoltageAlarm (UINT8 Status5v ,UINT8 Status12v);
extern	VOID MonitorBatteryAlarm (UINT8 KBVolume);
#endif
