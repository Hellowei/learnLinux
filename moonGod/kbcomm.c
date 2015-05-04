#define   KBCOMM_GLOBALS 
#include  "includes.h"

#define SYSKB_PACK_ID   0x0A

static PACKETFRAME PrivateSysKbPacket;

UINT8 LCSysBoard = 0;

BOOL SysKbSendPack(PACKETFRAME *pack)
{
	INT32 send, len;
	len = BuildPacket2(pack);
	MdlUartTran(UART_PORT_KB, pack, len, &send);
	if (len != send)
	{
		TriggerAlarm(TRUE, STR_ALM_KEYBOARD_COMM_ERR);
		printf("SysKbSendPack::injure packet!!\r\n");
		return FALSE;
	}
	else
	{
		TriggerAlarm(FALSE, STR_ALM_KEYBOARD_COMM_ERR);
	}
	#if 0
	int i;
	prinfo("pack[%d]::\n", len);
	for (i = 0; i < len; i++)
	{
		printf("0x%02X,", pack->buffer[i]);
	}
	printf("\r\n");
	#endif
	return TRUE;
}


static VOID sLcSysBoardWatchdogSwitch(BOOL flag)
{
	PACKETFRAME pack;
	pack.frame.id = SYSKB_MODULE_ID;
	pack.frame.len = 2;
	pack.frame.data[0] = SYSKB_RTN_WATCHDOG_ID;
	pack.frame.data[1] = (flag != 0);
	SysKbSendPack(&pack);
}


VOID SendSystemBoardCmd(SYSKBCMD cmd, UINT8 param)
{
	PACKETFRAME *pPack = &PrivateSysKbPacket;
	pPack->frame.len = 3;
	pPack->frame.data[0] = SYSKB_RTN_KEYSYSINFO_ID;
	pPack->frame.data[1] = 0x80;
	pPack->frame.data[2] = 0x80;
	switch (cmd)
	{
		case SYSKB_CMD_SW_PRINT:
			pPack->frame.data[1] |= ((param << 6) & 0x40);
			break;

		case SYSKB_CMD_SW_NIBP:
			pPack->frame.data[1] |= ((param << 5) & 0x20);
			break;

		case SYSKB_CMD_SW_CO2:
			pPack->frame.data[1] |= ((param << 4) & 0x10);
			break;

		case SYSKB_CMD_SW_IBP:
			pPack->frame.data[1] |= ((param << 3) & 0x08);
			break;

		case SYSKB_CMD_SW_IRBOARD:
			pPack->frame.data[1] |= ((param << 2) & 0x04);
			break;

		case SYSKB_CMD_SW_ECG:
			pPack->frame.data[1] |= ((param << 1) & 0x02);
			break;

		case SYSKB_CMD_SW_SPO2:
			pPack->frame.data[1] |= (param & 0x01);
			break;

		case SYSKB_CMD_RESET:
			pPack->frame.data[2] |= ((param << 6) & 0x40);
			break;

		case SYSKB_CMD_DEBUG:
//			pPack->frame.data[2] |= ((param << 5) & 0x20);
//			//进入调试模式需要与设置机型模式一起发送
//			break;
			sLcSysBoardWatchdogSwitch(((param << 5) & 0x20) > 0);
			return;

		case SYSKB_CMD_SW_MODLE:
			pPack->frame.data[2] |= ((param << 2) & 0x1C);
			break;

		case SYSKB_CMD_REBOOT:
			pPack->frame.data[2] |= ((param << 1) & 0x02);
			break;

		case SYSKB_CMD_POWER:
			pPack->frame.data[2] |= (param & 0x01);
			break;

		default:
			return;
	}
	pPack->frame.data[3] = GetChkSum(pPack->buffer);
	pPack->frame.data[4] = cUCAllCommPackEnd;
//	PostMessage(SysRec_HTSK,  MSG_PRTCL_SYSKB, 0, (LPARAM)pPack);  
	SysKbSendPack(pPack);
}

static void get_sysboard_version(void)
{
	
	PACKETFRAME pack;
	pack.frame.id = SYSKB_MODULE_ID;
	pack.frame.len = 1;
	pack.frame.data[0] = SYSKB_RTN_VERSION_ID;
	SysKbSendPack(&pack);
}

VOID SysKbVersionProc(char *ver)
{
	static char setup_flag = FALSE;
	UINT8 type = 0;

	if (setup_flag)
		return;

	float fver = atof(ver);
	int i = 0;
	while(ver[i] != '\0')
	{
		if (islower((int)ver[i]))
			ver[i] = (unsigned char)toupper((int)ver[i]);
		i++;
	}
	char CharLC = (NULL != strstr(ver, "LC"));
	printf("LC is %s\n", CharLC ? "True" : "False");
	if (fver > 2.01 || CharLC)
	{
		if (!LCSysBoard)
		{
			LCSysBoard = TRUE;
			Save_Config(CFG_KEYID_SYS_LCBOARD);
			PrinterInitFunc(RecEventClass.pRecClass);
			PrinterSetChroma(RecEventClass.pRecClass);
		}
	}

	if ( MonitorConfig.MonitorName != MONITOR_TYPE_AR4S)
	{
		if (LCSysBoard)
			type = 6; //0:N2  110:AR2
		sLcSysBoardWatchdogSwitch(_ENB_SYS_KEYBOARD_DEBUG);
	}
	else
	{
		type = 1; // 1:AR4
    	SendSystemBoardCmd(SYSKB_CMD_DEBUG, _ENB_SYS_KEYBOARD_DEBUG);
	}

	SendSystemBoardCmd(SYSKB_CMD_SW_MODLE, type);
	setup_flag = TRUE;
}

static BOOL InitKboardType(VOID)
{
  //  SendSystemBoardCmd(SYSKB_CMD_SW_MODLE, MonitorConfig.MonitorName); //1:A4
#if 1
	get_sysboard_version();
#else
	// SW_MODEL2 BIT 4:2     001:ARTMIS4  000:N2
#if 0 //_ENB_SYS_KEYBOARD_DEBUG
	// 调试需要再次发送命令包,需要先发送初始化命令
	// SW_MODEL2 BIT 5 1:进入调试模式,系统板不会启动, 0:6秒内收不到应答重启arm
	// 调试模式需要在第一次发送命令时打开
	SendSystemBoardCmd(SYSKB_CMD_DEBUG, TRUE);
//#else
#endif
    //printf("MonitorConfig.MonitorName =%d\n",MonitorConfig.MonitorName);
    if ( MonitorConfig.MonitorName != MONITOR_TYPE_AR4S){
	#if _ENB_LCSYS < 1
        #if _ENB_SYS_KEYBOARD_DEBUG
    	// 调试需要再次发送命令包,需要先发送初始化命令
    	// SW_MODEL2 BIT 5 1:进入调试模式,系统板不会启动, 0:6秒内收不到应答重启arm
    	// 调试模式需要在第一次发送命令时打开
    	SendSystemBoardCmd(SYSKB_CMD_DEBUG, TRUE);
        #endif
	#endif
	#if _ENB_LCSYS
		SendSystemBoardCmd(SYSKB_CMD_SW_MODLE, 6); //0:N2  110:AR2
	#else
	    SendSystemBoardCmd(SYSKB_CMD_SW_MODLE, 0); //0:N2  110:AR2 100:N3
    #endif
	}
	else
	{
	#if _ENB_LCSYS < 1
        #if _ENB_SYS_KEYBOARD_DEBUG
    	// 调试需要再次发送命令包,需要先发送初始化命令
    	// SW_MODEL2 BIT 5 1:进入调试模式,系统板不会启动, 0:6秒内收不到应答重启arm
    	// 调试模式需要在第一次发送命令时打开
    	SendSystemBoardCmd(SYSKB_CMD_DEBUG, TRUE);
        #endif
	#endif
	    SendSystemBoardCmd(SYSKB_CMD_SW_MODLE, 1); //1:A4
    }
#if _ENB_LCSYS
	//		打开看门狗：55 02 0a 02 73 01 80 03
	//		关闭看门狗：55 02 0a 02 73 00 7f 03
	sLcSysBoardWatchdogSwitch(_ENB_SYS_KEYBOARD_DEBUG > 0);
#endif

#endif
	return TRUE;
}
/*
	更新系统板状态
*/
VOID UpdateKeyboardStatus(VOID)
{
	static char count = 0;
	// 系统板是否通讯
	if (IsCommStoped(MID_KB))
	{
		// 重新初始化按键板
		if (++count > 30)
		{
			InitKboardType();
			ms_sleep(10);
			count = 0;
		}
		TriggerAlarm(TRUE, STR_ALM_KEYBOARD_COMM_ERR);
	}
	else
	{
		count = 0;
		TriggerAlarm(FALSE, STR_ALM_KEYBOARD_COMM_ERR);
	}
}

static VOID PutSysKbFansStatus(UINT8 fSpeed, UINT8 fStat)
{
	UINT16 speed = ( fSpeed & 0x7F) * 100;
	BOOL   fans  = ((fStat >> 1) & 0x01);
	BOOL   power = ( fStat & 0x01);
	if (!fans || !power)
		speed = 0;
	// 进一步处理
}

static VOID 
	PutSysKbStatus(UINT8 BattVol1, UINT8 BattVol2, UINT8 temp, UINT8 BattStat)
{
	if (BattVol2 & 0x40)
	{
		InitKboardType();
	}

	PutBatteryStatus(BattVol1, BattVol2, BattStat);
}

static VOID SysKeyOnPress(UINT8 key)
{
	key = key;
	int  keycode;
	switch (key)
	{
		case SYSKB_KEY_CODE_ENCODER_L:
			keycode = KEY_KNOB_ROTATE_LEFT;
			break;
			
		case SYSKB_KEY_CODE_ENCODER_R:
			keycode = KEY_KNOB_ROTATE_RIGHT;
			break;

		case SYSKB_KEY_CODE_POWEROFF:
			keycode = KEY_SOS_POWER;
			break;
			//return;

		default:
			keycode = KEY_UNDEFINED;
			break;
	}
	PostMessage(SysGui_HTSK, MSG_USER_SYS_KEYMSG, keycode, 0);
	return;
}

VOID PutSysKeyValue(UINT8 key, UINT8 status, UINT8 second)
{
	if (UpdateLocker == TRUE)
		return;
	if (MonitorInfo.touchCal)
	    return;
	if (MonitorInfo.standby)
	    ExitStandby();
	    
	if (status == SYSKB_KEY_CODE_PRESS)
	{
		int  keycode;
		
		switch (key)
		{
			case SYSKB_KEY_CODE_ALARM:
				keycode = KEY_SILENCE;  //for artemis4
				if (MonitorConfig.MonitorName == MONITOR_TYPE_AR2)
				    keycode = KEY_TOCO;
				break;

			case SYSKB_KEY_CODE_MENU:
				keycode = KEY_MENU; //for artemis4
				if (MonitorConfig.MonitorName == MONITOR_TYPE_AR2)
    				keycode = KEY_EVENT;
				break;

			case SYSKB_KEY_CODE_ECGMENU:
				keycode = KEY_EVENT;
				break;

			case SYSKB_KEY_CODE_NIBP:
				keycode = KEY_UNDEFINED;
				break;

			case SYSKB_KEY_CODE_PRINT:
				keycode = KEY_REC_START_STOP;
				break;

			case SYSKB_KEY_CODE_MAIN:
				keycode = KEY_MAIN;
				break;

			case SYSKB_KEY_CODE_ENCODER_L:
				keycode = KEY_KNOB_ROTATE_LEFT;
				break;

			case SYSKB_KEY_CODE_ENCODER_OK:
				keycode = KEY_KNOB_PRESSED;
				break;

			case SYSKB_KEY_CODE_ENCODER_R:
				keycode = KEY_KNOB_ROTATE_RIGHT;
				break;

			case SYSKB_KEY_CODE_FREEZE:
				keycode = KEY_FREEZE;
				break;

			case SYSKB_KEY_CODE_POWEROFF:
				keycode = KEY_SOS_POWER;
				return;

			case SYSKB_KEY_CODE_VOLPLUS:
				keycode = KEY_VOL_PLUS;
				break;

			case SYSKB_KEY_CODE_VOLMINUS:
				keycode = KEY_VOL_MINUS;
				break;

			case SYSKB_KEY_CODE_NEW:
				keycode = KEY_NEW_PATIENT;
				break;

			case SYSKB_KEY_CODE_ZERO:
				keycode = KEY_TOCO;
				break;

			case SYSKB_KEY_CODE_EXIT:
				keycode = KEY_EXIT;
				break;

			default:
				prinfo("\r\nInvalid key code!!\r\n");
				return;
		}
		PostMessage(SysGui_HTSK, MSG_USER_SYS_KEYMSG, keycode, second);
	}
	else
	{
		SysKeyOnPress(key);
		return;
	}

}

static VOID SysKbAskProc(UCHAR err)
{
	if (err) ASSERT_REPORT(err);
}

static VOID SysKbSendAskPacket(UINT8 err)
{
	#if _ENB_SYS_KEYBOARD_DEBUG
	return;
	#endif
	PrivateSysKbPacket.frame.len = 0x02;
	PrivateSysKbPacket.frame.data[0] = 0x04;
	PrivateSysKbPacket.frame.data[1] = (err | 0x80);
	if (!SysKbSendPack(&PrivateSysKbPacket))
	{
		PrivateSysKbPacket.frame.id = SYSKB_PACK_ID;
		PrivateSysKbPacket.frame.len = 0x02;
		PrivateSysKbPacket.frame.data[0] = 0x04;
		PrivateSysKbPacket.frame.data[1] = (err | 0x80);
		SysKbSendPack(&PrivateSysKbPacket);
	}		
}

BOOL InitKboard(VOID)
{
	MDL_UARTCFG ComCfg;
	ComCfg.baudRate = MapUartBPS(115200);
	ComCfg.parity   = PARITY_NO;
	ComCfg.dataBits = DBTS_8;
	ComCfg.stopBits = STOPBITS_1;
	MdlUartSetup(UART_PORT_KB, &ComCfg);
	if (MdlUartOpen(UART_PORT_KB))
	{
		return FALSE;
	}
	PrivateSysKbPacket.frame.stx	= cUCAllCommPackSTX;
	PrivateSysKbPacket.frame.sync   = cUCAllCommPackSync;
	PrivateSysKbPacket.frame.id	 = SYSKB_PACK_ID;
	return InitKboardType();
}

#ifndef PRINT_MODULE_ID
#define PRINT_MODULE_ID	0x79
#endif

VOID SysBrdPacketProc(PACKETFRAME *pack)
{
	if (pack->frame.id == SYSKB_MODULE_ID)
	{
		UINT8 data1 = 0;
		UINT8 data2 = 0;
		UINT8 data3 = 0;
		UINT8 data4 = 0;
		UINT8 err = 4;// 4：命令参数数据错误；
		data1 = pack->frame.data[1];
		data2 = pack->frame.data[2];
		data3 = pack->frame.data[3];
		data4 = pack->frame.data[4];
		switch (pack->frame.data[0])
		{
			case SYSKB_RTN_KEYACK_ID:
				if (data1 & 0x80)
				{
					data1 |= 0x7F;
					SysKbAskProc(data1);
				}
				break;

			case SYSKB_RTN_KEYSTAT_ID:
				if ((data1 & 0x80) && (data2 & 0x80) && (data3 & 0x80)
					&& (data4 & 0x80))
				{
					data1 &= 0x7F;
					data2 &= 0x7F;
					data3 &= 0x7F;
					data4 &= 0x7F;
					PutSysKbStatus(data1, data2, data3, data4);
					err = 0;
				}
				SysKbSendAskPacket(err);
				break;

			case SYSKB_RTN_KEYDATA_ID:
				if ((data1 & 0x80) && (data2 & 0x80) && (data3 & 0x80))
				{
					data1 &= 0x7F;
					data2 &= 0x7F;
					data3 &= 0x7F;
//					printf("data1=0x%x data2=0x%x data3=0x%x\n",data1,data2,data3);
					PutSysKeyValue(data1, data2, data3);
					err = 0;
				}
				SysKbSendAskPacket(err);
				break;

			case SYSKB_RTN_KEYSYSFANS_ID:
				if ((data1 & 0x80) && (data2 & 0x80))
				{
					data1 &= 0x7F;
					data2 &= 0x7F;
					PutSysKbFansStatus(data1, data2);
					err = 0;
				}
				SysKbSendAskPacket(err);
				break;

			case SYSKB_RTN_KEYSYSPOWER_ID:
				if (LCSysBoard)
				{
					if (data2 & 0x01)
					{
						SysPowerOff();
						system("halt");
					}
				}
				break;

			case SYSKB_RTN_VERSION_ID:
			{
				char version[32];
				int i;
//				printf("SYSKB_RTN_VERSION_ID %d::", pack->frame.len);
				for(i = 1; i < pack->frame.len; i++)
				{
//					printf("%c", (pack->frame.data[i] & 0x7F));
					version[i-1] = (pack->frame.data[i] & 0x7F);
				}
				version[i-1] = '\0';
//				printf("\n");
				SysKbVersionProc(version);
			}
				break;

			default:
				break;
		}
		return;
	}
	if (pack->frame.id == 0x30) return;
	if (pack->frame.id == 0x32) return;
	int len = 0;
	UCHAR *p = NULL;
#if 0
	printf("receive 0x%d\n", pack->frame.len);
	printf("pack->frame.id = 0x%02X\n", pack->frame.id);
	int i;
	for (i = 0; i < pack->frame.len + 4; i++)
	{
		printf("0x%02X,", pack->buffer[i]);
	}
	printf("0x%02X,0x%02X", pack->frame.chksum, pack->frame.end);
	printf("\n");
#endif
	if (pack->frame.id == PRINT_MODULE_ID)
	{
		len = pack->frame.len;
		p = pack->frame.data;
	}
	LCSendPrinterUnPackProc(MonitorConfig.RecorderType, len, p);
	return;
}

