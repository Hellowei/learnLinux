/*****************************************************************************************
��Ȩ����:			�����ص�
�汾��:				1.0.0
��������:			2011.04.15
�ļ���:				
����:				�����ص�
����˵��:			
����˵��:			��
�����ļ���ϵ:		���ļ�Ϊ���̹�Լ�����ļ�

�޸ļ�¼:
��¼1:
�޸���:
�޸�����:
�޸�����:
�޸�ԭ��:
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
	{ 0x78,		  0xff },  /*��������(78)*/
	{ 0x79,		  0xff },  /*ϵͳ״̬(79)*/
	{ 0x7B,		  0xff },  /*��������(7B)*/
	{ 0x7D,		  0xff },  /*��������(7D)*/
	{ 0x7A,		  0xff },  /*��Ũ������(7A)*/
	{ 0x7C,		  0xff },  /*��Ũ��У׼(7C)*/
	{ 0x77,		  0xff },  /*ϵͳ�������ݣ�77��*/
	{ 0x04,		  0xff },  /*У׼���ݰ�(04)*/
};

#define NUM_KB_RCVAPCKET  TABLESIZE(Kb_MsgPackMapTab)
#endif
#define ID_KEYBOARD_KEY		(0x78)		/*��������(78)*/
#define ID_KEYBOARD_SDS		(0x79)		/*ϵͳ״̬(79)*/
#define ID_KEYBOARD_TS		(0x7B)		/*��������(7B)*/
#define ID_KEYBOARD_ALARM	(0x7D)		/*��������(7D)*/
#define ID_KEYBOARD_O2		(0x7A)		/*��Ũ������(7A)*/
#define ID_KEYBOARD_O2ADJ	(0x7C)		/*��Ũ��У׼(7C)*/
#define ID_KEYBOARD_PARAM	(0x77)		/*ϵͳ�������ݣ�77��*/
#define ID_KEYBOARD_ACK		(0x04)		/*�����򰴼��巢��Ӧ������(04)*/

/* �������� */
typedef enum  _kb_alm_lev {
   KB_ALM_LEV_NO_ALARM,
   KB_ALM_LEV_LOW,
   KB_ALM_LEV_MED,
   KB_ALM_LEV_HIGH

} KBALARMLEVEL;

/* �������� */
typedef enum _kb_vol_lev {
   KB_VOLUME_LEV_SILENCE,
   KB_VOLUME_LEV_LOW,
   KB_VOLUME_LEV_MED,
   KB_VOLUME_LEV_HIGH
} KBVOLUMELEVEL;

/* ������ָ��ID. */
typedef enum _kb_cmd_id {

   CMD_KB_SET_ALARM_LEVEL,	  /* ���ñ�������		 */
   CMD_KB_SET_ALARM_VOLUME,	 /* ���ñ�������		 */
   CMD_KB_SET_BEAT_VOLUME,	  /* ����������		   */
   CMD_KB_SET_KNOB_VOLUME,	  /* ����������		   */
   CMD_KB_SET_KNOB_SOUND,
   CMD_KB_SET_ALM_SOUND,
   CMD_KB_REQ_SELF_TEST,		/* �����Լ���		 */
   CMD_KB_SET_PULSE_VOLUME,	 /* ������������		 */
   CMD_KB_SET_VERSION,			/* ���ð������Э��汾 */
   CMD_KB_SET_NURSECALL,		/* ����nurse call	   */
   CMD_KB_SWITCH_NURSECALL,	 /* ����nurse call����   */
   CMD_KB_REQ_SHUTOFF_POWER,	/* ����ػ�			 */
   
   CMD_KB_MAX

} KBCMDID;

/* ������ ��Ϣ��ID */
typedef enum  _msgpack_id {

	MSGPACK_KB_KNOB_ROTATE_RIGHT,  /* ����������		*/
	MSGPACK_KB_KNOB_ROTATE_LEFT,   /* ����������		*/
	MSGPACK_KB_KNOB_ROTATE_DOWN,   /* ����������		*/
	MSGPACK_KB_KEY_MENU,		   /* ����, �˵�		*/
	MSGPACK_KB_KEY_NIBP,		   /* ����, NIBP		*/
	MSGPACK_KB_KEY_RECORD,		 /* ����, ��¼		*/
	MSGPACK_KB_KEY_PAUSE,		  /* ����, ��ͣ		*/
	MSGPACK_KB_KEY_FREEZE,		 /* ����, ����		*/
	MSGPACK_KB_KEY_MAIN,		   /* ����, ����		*/
	MSGPACK_KB_KYE_ALARM,		  /* ����, ��������	*/
	MSGPACK_KB_KEY_SILENCE,		/* ����, ����		*/
	MSGPACK_KB_KEY_SHORTCUT,	   /* �������·		*/
	MSGPACK_KB_KEY_SHUTOFF,		/* ����, �ػ�		*/
	MSGPACK_KB_VER_PROTOCOL,	   /* Э��汾		  */
	MSGPACK_KB_BATT_VOLUME,		/* ��ص���		  */
	MSGPACK_KB_SELFTEST,		   /* �Լ���		  */
	MSGPACK_KB_POWER_STATE,		/* ��Դ״̬		  */
	MSGPACK_KB_VER_SOFTWARE,	   /* ����汾		  */
	MSGPACK_KB_ESCAPE,			 /* ת���,Ϊ�Ժ���չ */

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
	INT8	TechAlmflag;			//������һ�β�����
}KBALARMINFO ,*PKBALARMINFO;
typedef struct 
{
	UINT8	status5v;		//00����ѹ������01����ѹ̫�ߣ�10����ѹ̫��
	UINT8	status12v;		//00����ѹ������01����ѹ̫�ߣ�10����ѹ̫��
	UINT8	volume;			//000---111�� ��ص���������0 ��ص����գ�7����ص�������
	UINT8	ACtype;			//����״̬��  0: ��ع��磬 1�������繩��
	UINT8	Chargstatus;	//���״̬��  0�����ڳ�磬 1����س��� (���е��ʱ��������Ч)
	UINT8	Battestatus;	//���״̬��  00���е�أ� 01��û�е�أ� 10����ع���
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
   UINT8   protocol;  /* �������ͨѶЭ��汾10��ʾ1.0��	 11��ʾ:1.1�� */
}KBINFO;


extern KBINFO  KbInfo;
extern UINT8   Kb_CurrPack;			 /* ��ǰ���͵����ݰ�			*/
extern UINT8   Kb_AckPack;			  /* ���յ���Ӧ��				*/
extern UINT8   Kb_SelfTestResult;	   /* �Լ���;ϵͳ��ʱ������.	*/
extern INT8	Kb_Acked;				/* �Ƿ���Ӧ.TRUE, �Ѿ���Ӧ.	*/
extern INT8	Kb_TimeEscaped;		  /* ����ָ������������Ӧʱ��. */
extern INT8	Kb_TimeRest;			 /* ʱ�������				  */
extern INT8	KbCmdNeedAck[CMD_KB_MAX];
extern UINT8   KbCmdPackMapTbl[][2];
extern KEYBOARDLAMP		keyboardlamp;   /* ������ƴ���					*/
extern KBALARMINFO		 keyboardsound;	/* �����屨����Ϣ����			*/
extern KBACKINFO		keyboardACK;	/* ������ACK��Ϣ				*/
extern KBBATTERLINFO	KBbatteryinfo;	/* �������ص�����Ϣ				*/


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
