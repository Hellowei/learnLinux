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
#define   APPPROC_GLOBALS 
#include  "includes.h"


#define APPPROC_TEST   0


void  test_pm_func(void);

INT32 KbSendPacket2(UINT8 a, UINT32 b){return 0;}

static CMDPROC_ENTRY  App_KbCmdEntry[] = {
	/* nMessage,	  nCode,	pfn */
	{ MSG_APP_KB_CMD, CMD_KB_SET_KNOB_VOLUME,   (CMD_PMSG)KbSendPacket2 },  /* 键盘声音量		   */
	{ MSG_APP_KB_CMD, CMD_KB_SET_PULSE_VOLUME,  (CMD_PMSG)KbSendPacket2 },  /* 设置脉搏音量		 */
	{ MSG_APP_KB_CMD, CMD_KB_SET_BEAT_VOLUME,   (CMD_PMSG)KbSendPacket2 },  /* 心跳声音量		   */
	{ MSG_APP_KB_CMD, CMD_KB_SET_ALARM_VOLUME,  (CMD_PMSG)KbSendPacket2 },  /* 设置报警音量		 */
	{ MSG_APP_KB_CMD, CMD_KB_SET_ALARM_LEVEL,   (CMD_PMSG)KbSendPacket2 },  /* 设置报警级别		 */
	{ MSG_APP_KB_CMD, CMD_KB_REQ_SELF_TEST,	 (CMD_PMSG)KbSendPacket2 },  /* 请求自检结果		 */
	{ MSG_APP_KB_CMD, CMD_KB_SET_VERSION,	   (CMD_PMSG)KbSendPacket2 },  /* 设置按键板的协议版本 */
	{ MSG_APP_KB_CMD, CMD_KB_SET_NURSECALL,	 (CMD_PMSG)KbSendPacket2 },  /* 设置nurse call	   */
	{ MSG_APP_KB_CMD, CMD_KB_SWITCH_NURSECALL,  (CMD_PMSG)KbSendPacket2 },  /* 开关nurse call报警   */
	{ MSG_APP_KB_CMD, CMD_KB_REQ_SHUTOFF_POWER, (CMD_PMSG)KbSendPacket2 },  /* 请求关机			 */
};
#define  NR_KB_CMDENTRY   TABLESIZE(App_KbCmdEntry)

static CMDPROC_ENTRY  App_PmCmdEntry[0];
#define  NR_PM_CMDENTRY   TABLESIZE(App_PmCmdEntry)


/**
 ** 同按键板握手.建立通讯.
 **/
INT32  HandshakeWithKeyBoard (VOID)
{
	INT32  result;
	int	i;

	for (i = 0; i < 3; i++) {
		//result = KbSendPacket2(CMD_KB_REQ_SELF_TEST, 0);
		if (result >= 0)
			break;
	}
#if  IOKB	
	 result = ERR_OK; //buaazy 2010-9-5  跳过自检  
#endif 

	return result;
}




/**
 ** 参数模块复位后(包括上电复位, 或者异常复位).设置参数模块.
 **/
INT32  SetupPatientModule (VOID)
{
	INT32  result;

	result = 0;
	return result;
}


static  INT32  OnMsgKbCmd (UINT32 wParam, UINT32 lParam)
{
	int			   i, j;
	UINT8			 id;
	CMDPROC_ENTRY	*pEntry;
	INT32			 result = 0;

	id = LOWORD(wParam);
	result = ERR_IO_NOCMD;
	for (i = 0; i < NR_KB_CMDENTRY; i++) {
		pEntry = App_KbCmdEntry + i;
		if (id == pEntry->nCode) {
			for (j = 0; j < 3; j++) { // max , Send 3 piece.
				result = (*pEntry->pfn)(id, lParam);
				if (result >= 0)
					break;
			}
			break;
		}
	}

	if (result < 0)
		PostMessage(SysGui_HTSK, MSG_GUI_KB_NOACK, wParam, lParam);
	else
		PostMessage(SysGui_HTSK, MSG_GUI_KB_ACK, wParam, lParam);
	
	return  result;
   
}

INT8 SoundInUsed = 0;

VOID SendAlmSound(INT16 almLev)
{
	char tbuf[128];

	if (MonitorConfig.alarmVolume == ALM_SILENCE || (almLev == 0) 
		|| (TRUE == AlmGlbCtlr.AlmSilent) || (OFF == MonitorConfig.alarmSoundOn))
	{
		return;
	}
	SoundInUsed = 1;
	static int k;

	int vol = 30;
	if (MonitorConfig.alarmVolume == ALM_VOL_LOW)
	{
		vol = 10;
	}
	else if(MonitorConfig.alarmVolume == ALM_VOL_MED)
	{
		vol = 40;
	}
	else if(MonitorConfig.alarmVolume == ALM_VOL_HIGH)
	{
		vol = 70;
	}
	else if(MonitorConfig.alarmVolume == ALM_VOL_MAX)
	{
		vol = 90;
	}
	if (almLev == 1)
	{
		if (vol >= 10)
		{
			vol -= 5;
		}
		ac_sound_high(vol);
	}
	else if (almLev == 2)
	{
		vol += 20;
		ac_sound_middle(vol);
	}
	else if (almLev == 3)
	{
		ac_sound_low(vol);
	}
	SoundInUsed = 0;
}


VOID SendKeySound()
{
	static int keySoundCount = 0;
	char tbuf[128];
	
	if (keySoundCount > 0)
		keySoundCount --;

	if (MonitorConfig.kbVol== KB_SILENCE)
		return;

	SoundInUsed = 1;

	int vol = 20;
	if (MonitorConfig.kbVol == KB_VOL_LOW)
	{
		vol = 5;
	}
	else if(MonitorConfig.kbVol == KB_VOL_MED)
	{
		vol = 15;
	}
	else if(MonitorConfig.kbVol == KB_VOL_HIGH)
	{
		vol = 25;
	}
	else if(MonitorConfig.kbVol == 4)
	{
		vol = 35;
	}
	static int k;
	ac_sound_key(vol);
	SoundInUsed = 0;
}


static INT32 OnMsgSoundCmd (UINT32 wParam, UINT32 lParam)
{
	int			   i, j;
	UINT8			 id;
	CMDPROC_ENTRY	*pEntry;
	INT32			 result = 0;

	id = LOWORD(wParam);
	switch(id)
	{
//		case CMD_SOUND_SET_PULSE_VOLUME:
//			SendPulseSound();
//			break;
//			
//		case CMD_SOUND_SET_BEAT_VOLUME:
//			SendHeartBeatSound();
//			break;

		case CMD_SOUND_SET_KNOB_VOLUME:
			SendKeySound();
			//FetalSendSound(1);
			break;

		case CMD_SOUND_SET_ALM_SOUND:
			SendAlmSound(lParam & 0xff);
		#if 0
			if (	ALM_SILENCE == MonitorConfig.alarmVolume 
				|| (OFF 		== MonitorConfig.alarmSoundOn)
				|| (TRUE 		== AlmGlbCtlr.AlmSilent))
			{
				break;
			}
			if (2 == lParam)
				FetalSendSound(2);
		#endif
			break;

		default:
			break;
	}
	return result;
}


static  VOID  App_PostProcOnMsgPmCmd (UINT8 id, INT32 result)
{
	if (result < 0) {
		;
	}
}


static  INT32  OnMsgPmCmd (UINT32 wParam, UINT32 lParam)
{
	int			   i, j;
	UINT8			 id;
	CMDPROC_ENTRY	*pEntry;
	INT32			 result;
	
	id = LOBYTE(wParam);
	result = ERR_IO_NOCMD;
	for (i = 0; i < NR_PM_CMDENTRY; i++) {
		pEntry = App_PmCmdEntry + i;
		if (id == pEntry->nCode) {
			for (j = 0; j < 3; j++) { // max , Send 3 piece.
				result = (*pEntry->pfn)(id, lParam);
				if (result >= 0)
					break;
			}
			break;
		}
	}
	return  result;
}


VOID  SetupFuncBlock(UINT8 mid)
{
	PostMessage(SysApp_HTSK, MSG_APP_PM_SETUP, mid, 0);
}

INT32  SetupFuncBlock2(UINT8 mid)
{
	INT32   result;
	
	result = -1;
	switch (mid) {

		default:
			break;
	}
	return  result;
}

static VOID  OnMsgSaveConfig(UINT32 wParam, UINT32 lParam)
{
	INT16  info_id;
	INT8   type;

	info_id = LOWORD(lParam);
	type	= LOBYTE(HIWORD(lParam));
	
	switch (wParam) {
		case CONFIGID_SYS:
			break;
			
#if _ENB_FHR_FUNC_SAVE
		case CONFIGID_FHR:
			//Save_Fetal_Config2(info_id);
			break;
#endif

		case CONFIGID_ALL:
			break;

		default:
			break;
	}
}


INT32  AppTskProc (HANDLE hdl, INT32 msg, UINT32 wParam, UINT32 lParam)
{
	INT32  result;
	UINT8  err;
	

	switch (msg)
	{
		case MSG_TIMER:
			break;
			
		case MSG_APP_POWERON:  //上电以后握手
			HandshakeWithKeyBoard();
			return 0;
			
		case MSG_PM_RESET:
			SetupPatientModule();
			return 0;
			
		case MSG_APP_PM_SETUP:
			return  SetupFuncBlock2(LOBYTE(wParam));
			
		case  MSG_APP_KB_CMD:
			return OnMsgKbCmd(wParam, lParam);
			
		case  MSG_APP_PM_CMD:
			return OnMsgPmCmd(wParam, lParam);

		case  MSG_APP_SOUND_CMD:
			return OnMsgSoundCmd(wParam, lParam);
			
#if _ENB_FHR_FUNC
		case MSG_APP_FHR_CMD:
			//return OnMsgFhrCmd(wParam, lParam);
			return 0;
#endif

		case  MSG_APP_SAVE_CONFIG:
			ENTER_FILE_OP();
			OnMsgSaveConfig(wParam, lParam);
			EXIT_FILE_OP();

			return 0;
			
		default:
			break;
	}
	
	return DefaultTskProc(hdl, msg, wParam,lParam);
}





