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
#define   TSKPROC_GLOBALS
#include  "includes.h"



extern VOID InsertNewPatientID(BOOL insert);
extern	INT8  FirstBoot;

INT32  DefaultTskProc(HANDLE hdl, INT32 msg, UINT32 wParam, UINT32 lParam)
{
	hdl	= hdl;
	msg	= msg;
	wParam = wParam;
	lParam = lParam;

	return 0L;
}


static  VOID  guiOnKeyMenu (VOID)
{
	SendMessage(HWND_DESKTOP, MSG_SCRMAN, SM_BACKMAIN, 0);
	PostMessage(SysGui_HTSK, MSG_SCRMAN, SM_MENU, 0);  
}

static  VOID  guiOnKeyFreeze (VOID)
{
	if (MonitorInfo.inFrozen)
		ExitFrozen();  
	else
		EnterFrozen();
}

static VOID gui_OnSysKeyMsg (UINT32 wParam, UINT32 lParam)
{
    //printf("wParam =%d\n",wParam);
	switch (wParam) 
	{
		case KEY_MENU:
			if (LOBYTE(lParam) < 15)
			{
			 if ((HWND)GetTopWndItem(IDD_SYSTEM_CONFIG) == HWND_INVALID)
			 {
				if (_menu_lev > 0)
					BacktoMainScreen();

				PostMessage(SysGui_HTSK,  MSG_SCRMAN, SM_MENU,	  0);  
			 }
			}
			else
			{
				PostMessage(SysGui_HTSK,  MSG_SCRMAN, SM_STATUS,	0);  
			}
			 break;

		case KEY_SILENCE:
//			if (MonitorConfig.alarmSoundOn)
//			{
//				MonitorConfig.alarmSoundOn = OFF;
//				OnSilence();
//			}
//			else
//			{
//				MonitorConfig.alarmSoundOn = ON;
//			}
//			UpdateAlmVolIcon();
//			Save_Config(CFG_KEYID_ALARMSILENCE);
			 OnSilence();
			 break;

		case KEY_PAUSE:
			 OnPause();
			 break;

		case KEY_FREEZE:
			 guiOnKeyFreeze();
			 break;

		case KEY_MAIN:
			 SendMessage(HWND_DESKTOP, MSG_SCRMAN, SM_BACKMAIN, 0);
			 break;

		case KEY_REC_START_STOP:
			#if _ENB_REC_FUNC
			 if (FhrConfig.fastPrint == FALSE) 
			 {
				 if ((HWND)GetTopWndItem(IDD_PATIENT_SETUP) == HWND_INVALID)
				 {
					if (_menu_lev > 0)
						SendMessage(HWND_DESKTOP, MSG_SCRMAN, SM_BACKMAIN,  0);
				 
					PostMessage(SysGui_HTSK,  MSG_SCRMAN, SM_MENU,	  0);  
				 }
			 }
			 else
			 {
				// 按窗口来实现打印机功能
				HWND hWnd;
				hWnd = (HWND)GetTopWndItem(IDD_PRINTER_SETUP);
				if (hWnd != HWND_INVALID && hWnd)
				{
					if (GetDlgItem(hWnd, IDC_PRINTER_SETUP_SELFTEST_B))
					{
						RecordService(REC_SELF_TEST);
						break;
					}
				}
				hWnd = (HWND)GetTopWndItem(IDD_FETAL_RECALL);
				if (hWnd != HWND_INVALID && hWnd)
				{
					PWIN pWin = (PWIN)hWnd;
					if (pWin->hActiveChild == 
						GetDlgItem(hWnd, IDC_FETAL_RECALL_PRINTALL_B))
					{
						RecordService(REC_RECALL_ALL);
						break;
					}
					if (pWin->hActiveChild == 
						GetDlgItem(hWnd, IDC_FETAL_RECALL_PRINTPAGE_B))
					{
						RecordService(REC_RECALL_PAGE);
						break;
					}
					break;
				}
				if (RecFHRControl.elapseSec > 0 && RecFHRControl.isBegin) // 
				{
					if (FmsPtr->GetCurrSaveIndex(FmsPtr) >= 0)//
					{
						EndPatientFile();
						strcpy(LoadString(STR_MAIN_TOPBAR_NAME_NAME), PatientInfo.patientName);
						strcpy(LoadString(STR_MAIN_TOPBAR_ID_NUM), PatientInfo.patientID);
						ShowPatinetInfo();
					}
				}
				else
				{
					if (FmsPtr->GetCurrSaveIndex(FmsPtr) < 0)//
					{
						NewPatient();
						FmsPtr->NewPatient(FmsPtr);
						InsertNewPatientID(1);
						FmsPtr->PutPtnInfo(FmsPtr, &PatientInfo);
						ShowPatinetInfo();
					}
					RecordService(REC_FETAL_RECALL);
				}
			 }
		    #endif
			 break;

		case KEY_NIBP_START_STOP:
			 break;

		case KEY_SOS_PATIENT:
			 prinfo("#####################KEY_SOS_PATIENT\r\n");
			 break;

		case KEY_SOS_POWER:
			 ShutdownDialog();
			 break;

		case KEY_VOL_PLUS:
			 FhrConfig.volume++;
			 if (FhrConfig.volume > 8)
			 {
				 FhrConfig.volume = 8;
				 break;
			 }
			 SetListBoxCurChoi(IDD_SYSTEM_CONFIG,
				IDC_SYSTEM_CONFIG_FETAL_VOL_LB, FhrConfig.volume);
			 Save_Config(CFG_KEYID_FHRVOLUME);
			 FetalSetMoudle(FALSE);;
			 break;

		case KEY_VOL_MINUS:
			 FhrConfig.volume--;
			 if (FhrConfig.volume < 0)
			 {
				 FhrConfig.volume = 0;
				 break;
			 }
			 SetListBoxCurChoi(IDD_SYSTEM_CONFIG,
				IDC_SYSTEM_CONFIG_FETAL_VOL_LB, FhrConfig.volume);
			 Save_Config(CFG_KEYID_FHRVOLUME);
			 FetalSetMoudle(FALSE);;
			 break;

		case KEY_NEW_PATIENT:
			 if ((HWND)GetTopWndItem(IDD_PATIENT_SETUP) == HWND_INVALID)
			 {
				 if (_menu_lev > 0)
					 SendMessage(HWND_DESKTOP, MSG_SCRMAN, SM_BACKMAIN, 0);

				 PostMessage(SysGui_HTSK,  MSG_SCRMAN, SM_PATIENT, 0);  
			 }
			 break;

		case KEY_TOCO:
			 FetalSetMoudle(TRUE);
			 break;

		case KEY_EVENT:
			 if ((HWND)GetTopWndItem(IDD_DOCTOR_MARK) == HWND_INVALID)
			 {
				 if (_menu_lev > 0)
					 SendMessage(HWND_DESKTOP, MSG_SCRMAN, SM_BACKMAIN, 0);

				 PostMessage(SysGui_HTSK,  MSG_SCRMAN, SM_EVENT, 0);  
			 }
			 break;

		case KEY_EXIT:
			 SendMessage(HWND_DESKTOP, MSG_SCRMAN, SM_BACKMAIN, 0);
			 break;

		case KEY_KNOB_PRESSED:
		case KEY_KNOB_ROTATE_RIGHT:
		case KEY_KNOB_ROTATE_LEFT:
			 SendMessage(HWND_DESKTOP, MSG_KEYENCODER, wParam, lParam);
			 break;

		 #if _ENB_TOUCH
		case KEY_TOUCH:
			SendMessage(HWND_DESKTOP, MSG_TOUCHENCODER, wParam, lParam);
			 break;
		 #endif

		default:			
			 break;
	}
	if (LOBYTE(wParam) == 0)
	{
		PostMessage(SysApp_HTSK, MSG_APP_SOUND_CMD, CMD_SOUND_SET_KNOB_VOLUME, 0);
	}
}

#if _ENB_TOUCH
static VOID  gui_OnSysTouchMsg (UINT32 wParam, UINT32 lParam)
{
	if (wParam)		
		SendMessage(HWND_DESKTOP, MSG_TOUCHENCODER, wParam, lParam);
//	switch (wParam)
//	{
//		case TOUCH_PRESSED:
//		case TOUCH_RELEASE:
//			SendMessage(HWND_DESKTOP, MSG_TOUCHENCODER, wParam, lParam);
//			break;

//		default:
//			break;
//	}
}
#endif

/**
** 关于界面布局调整消息的说明:
**	 在开始界面布局前，必须首先结束对话框。所以， 必须调用desktop的MSG_SCRMAN消息处理。
** 窗口管理器会向所有对话框发出quit消息，结束对话框的消息循环。
**	 然后在post消息 MSG_SCRMAN + SM_LAYOUT， 真正的界面布局在这里实现。用post而不是send，
** 这是因为，前面的对话框消息循环还没有结束。所以必须post。
**/
VOID gui_OnScnManMsg (UINT32 wParam, UINT32 lParam)
{
	lParam = lParam;
	switch (wParam) 
	{
		case SM_MENU:			//创建系统主菜单.
			 OnClickSystemSetupDialog(0, 0,0);
			 break;

		case SM_STATUS:
			 OnClickSystemInfo(0);
			 break;

		case SM_FACTORY:
			 OnClickFactoryMaintainDialog(0);
			 break;

		case SM_EVENT:
			if ((HWND)GetTopWndItem(IDD_DOCTOR_MARK) == HWND_INVALID 
			   && _menu_lev <= 0)
			{
				DoctorMarkDialog(0);
			}
			 break;

		case SM_PATIENT:
			 OnClickPatientSetupDialog(0, 0,0);
			 break;

		case SM_FREEZE:
			 break;

		case SM_START_LAYOUT:
			 SendMessage(HWND_DESKTOP, MSG_SCRMAN, SM_BACKMAIN, 0);
			 OSTimeDlyHMSM(0, 0, 0, 1);
			 PostMessage(SysGui_HTSK, MSG_SCRMAN, SM_LAYOUT, 0); //开始屏幕布局
			 break;

		case SM_LAYOUT:
			 LayoutScreen();	//进行屏幕布局
			 break;

		default:
			 break;
	}
	
	return;
}


#if 0
static UCHAR		  sNetSendDataBuffer[1024 * 5];
ALARM_LEVEL_INFO	  phs_alm[256];
TECH_ALARM_LEVEL_INFO tech_alm[512];

void NetSend()
{
	INT16 exist_module_count  = 0;
	INT16 exist_module_name[8];
	
	INT16 onlaod_module_count = 0;
	INT16 onload_module_name[8];
	
	INT16 unload_module_count = 0;
	INT16 unload_module_name[8];

	INT16 phs_alm_count	   = 0;
	INT16 tech_alm_count	  = 0;
	
	INT32 data_len			= 0;	
	INT16 i;

	if (gCmsOnline > 0)
	{
		gCmsOnline--;
		if (gCmsOnline == 0)
		{
			;//DisconnectWithCms();
		}
	}

	// 此处打包
	// 1. TCP的实时数据
	// 3. 广播的实时数据

	BOOL admited_by_cms = 0;//GetNetConnect();
	data_len = 0;
	//PactOnlineNotifyPacket(sNetSendDataBuffer, &data_len, &gHyp6NetInfo);
	
//	if (0 <= gBroadcastSocket)
//		SaveDataToUdpSendBuffer(sNetSendDataBuffer, data_len);

	if (admited_by_cms) 
	{
		// 取得当前模块数
		GetParaModuleInfo(&exist_module_count, exist_module_name,
							&onlaod_module_count, onload_module_name,
							&unload_module_count, unload_module_name);

		if (gHyp6NetInfo.bHaveAdmittedPatient)
		{
			if (GetNewConnect())
			{
				SetNewConnect(FALSE);						
				// 新连接上的,传送机器类型等初始化数据
						
				// 机器基本信息包
				data_len = 0;
				PackDeviceBaseInfo( sNetSendDataBuffer, &data_len );
				SaveDataToTcpSendBuffer( sNetSendDataBuffer, data_len );

				// 病人信息包
				data_len = 0;
				PackPatientInformation( sNetSendDataBuffer, &data_len, cmd_notify_packet);
				SaveDataToTcpSendBuffer( sNetSendDataBuffer, data_len );						

				// 系统通用设置包
				data_len = 0;
				PackDeviceGeneralSetting( sNetSendDataBuffer, &data_len, 0xFFFFFFFF , cmd_notify_packet);
				SaveDataToTcpSendBuffer( sNetSendDataBuffer, data_len );						

				// 报警通用设置包
				data_len = 0;
				PackAlarmGeneralSetting( sNetSendDataBuffer, &data_len, 0xFFFFFFFF, cmd_notify_packet);
				SaveDataToTcpSendBuffer( sNetSendDataBuffer, data_len );							

				for (  i = 0; i < exist_module_count; i ++ )
				{
					// 当前模块的加载通知包
					data_len = 0;							
					PackModuleOnLoadPacket( sNetSendDataBuffer, &data_len, exist_module_name[i] );
					SaveDataToTcpSendBuffer( sNetSendDataBuffer, data_len );

					data_len = 0;
					PackModuleInitSetting( exist_module_name[i], sNetSendDataBuffer, &data_len );
					SaveDataToTcpSendBuffer( sNetSendDataBuffer, data_len );
				}
				/* 网络模块初始化完成*/				
				SetCmsPlusModeNormal();
			}
			else
			{
				// 取得当前新加载的模块或者卸载的模块
				for (  i = 0; i < onlaod_module_count; i ++ )
				{
					// 当前模块的加载通知包
					data_len = 0;							
					PackModuleOnLoadPacket( sNetSendDataBuffer, &data_len, onload_module_name[i] );
					SaveDataToTcpSendBuffer( sNetSendDataBuffer, data_len );

					data_len = 0;
					PackModuleInitSetting( onload_module_name[i], sNetSendDataBuffer, &data_len );
					SaveDataToTcpSendBuffer( sNetSendDataBuffer, data_len );
				}


				// 取得当前新加载的模块或者卸载的模块
				for (  i = 0; i < unload_module_count; i ++ )
				{
					// 当前模块的加载通知包
					data_len = 0;							
					PactModuleUnLoadPacket( sNetSendDataBuffer, &data_len, unload_module_name[i] );
					SaveDataToTcpSendBuffer( sNetSendDataBuffer, data_len );
				}
			}
		}
		for (  i = 0; i < exist_module_count; i ++ )
		{
			
			data_len = 0;
			//PackModuleRealTimeData( exist_module_name[i], sNetSendDataBuffer, & data_len );

			if ( admited_by_cms && gHyp6NetInfo.bHaveAdmittedPatient )
				SaveDataToTcpSendBuffer( sNetSendDataBuffer, data_len );
			
		}
					
		// 得到数据，打包发送
		data_len = 0;
		//PackCurrentAlarmInfo( sNetSendDataBuffer, & data_len, 
		//						phs_alm, phs_alm_count, tech_alm, tech_alm_count );

		if ( admited_by_cms && gHyp6NetInfo.bHaveAdmittedPatient )
			SaveDataToTcpSendBuffer( sNetSendDataBuffer, data_len );
	}
	
}
#endif

/*
有些gui任务需要按usb状态处理
*/
static VOID gui_UsbProcess(VOID)
{
	static INT8 flag = FALSE;
	if (GetUsbStorage() == '1')
	{
		if (flag == FALSE)
		{
			flag = TRUE;
			/* 以下为处理函数 */

			/* 自动加载语言文件到临时目录 */
			GetLanguageFile("/mnt/disk");
			/* 加载语言文件结束 */
		}
		return;
	}
	if (flag == TRUE)
	{
		flag = FALSE;
	}
}


VOID   gui_TimerProc(VOID)
{
	DataCorrection();
	UpdateStatus();
	if (get_analysis_enable())
		AnalyInSecond();
#if 1
	AlarmProcess();
//	ShowSysInfoItem(); // 刷新提示条
//	ShowBattaryState();// 刷新电池电量, 
	ShowStatusIcon();
	ShowDateTime(); 
	ShowDemo();
#endif
	gui_UsbProcess();

/** /
	if (DateTime.second % 5 == 0)
	{
		MonitorConfig.language++;
		if (MonitorConfig.language == MAX_LANGUAGE)
			MonitorConfig.language = ENGLISH;
		ReInitGlobalStrPtr(MonitorConfig.language);
		StartLayoutSession();
	}
**/
//  NetSend();
	if (FirstBoot)
	{
		// while first boot, show factory maintain dialog
		PostMessage(SysGui_HTSK,  MSG_SCRMAN, SM_FACTORY, 0);  
		FirstBoot = FALSE;
	}
	if (10 < GetNetReceivePacketCount())
	{
		PostMessage(SysUdpT_HTSK, MSG_NET_UDP_RESET, 0, 0);
	}
	if (TRUE == gNetStatus)
	{
		SetNetReceivePacketCount(FALSE);
	}
}

VOID   gui_BlinkProc(VOID)
{
	FlushParamValue();
	BlinkParamValue();
}

VOID  gui_OnPmCmdNoAck (UINT32 wParam, UINT32 lParam)
{
//  HWND	 hWnd;
//  UINT8	tmp;
  
  lParam = lParam;
//  hWnd   = hWnd;
//  tmp	= tmp;
  
	switch (wParam) {
		default:
			break;
	}
}





VOID  gui_OnPmCmdAck (UINT32 wParam, UINT32 lParam)
{
//  HWND	 hWnd;
//  UINT8	tmp;
  
  lParam = lParam;
//  hWnd   = hWnd;
//  tmp	= tmp;
  
	switch (wParam) 
	{
		default:
			break;
	}
}

VOID   test_gui_task(VOID);






INT32  GuiTskProc (HANDLE hdl, INT32 msg, UINT32 wParam, UINT32 lParam)
{
//	INT32  x, y;
//	INT16  packet_count = 0;
//	INT32  data_len	 = 0;
//	UCHAR  buff[1024 * 5];

	OSTimeDlyHMSM(0, 0, 0, 1);
	switch (msg)
	{
		case MSG_TIMER:
			 break;
		
		case MSG_CREATE:
			 return 0;

		case MSG_SYS_DATA_CORRECTION:
			 gui_TimerProc();
			 return 0;

		case MSG_SYS_DATA_PROC:
#if _ENB_OXYCRG_FUNC
			 FlushOxycrgWave(0);
#endif
			 return 0;

		case MSG_GUI_BLINK:
			 gui_BlinkProc();
			 return 0;

		case MSG_USER_SYS_KEYMSG:
			 /* 如果是在冻结状态下,处理旋钮以外.按任何一个键将退出冻结. */
			 if (MonitorInfo.inFrozen) 
			 {
				if ((wParam < KEY_KNOB_PRESSED || wParam > KEY_KNOB_ROTATE_LEFT)
					&& wParam != KEY_FREEZE) 
				{
					ExitFrozen();						
					gui_OnSysKeyMsg(wParam, lParam);
				} 
				else
				{
					gui_OnSysKeyMsg(wParam, lParam); // 在冻结菜单下,可以出来'冻结'按键消息.
				}
			 }
			 else 
			 {
				gui_OnSysKeyMsg(wParam, lParam);
			 }
			
			 OSTimeDlyHMSM(0, 0, 0, 1);
			 //printf("MSG_USER_SYS_KEYMSG \n");
			 return 0;

#if _ENB_TOUCH
			case MSG_USER_SYS_TOUCHMSG:
				gui_OnSysTouchMsg(wParam, lParam);
				//OSTimeDlyHMSM(0, 0, 0, 1);
				return  0;
#endif


		case MSG_SCRMAN:
			 gui_OnScnManMsg(wParam, lParam);
			 OSTimeDlyHMSM(0, 0, 0, 1);
			 return 0;

		case MSG_GUI_PM_NOACK:
//			 gui_OnPmCmdNoAck(wParam, lParam);
			 return 0;

		case MSG_GUI_PM_ACK:
//			 gui_OnPmCmdAck(wParam, lParam);
			 return 0;

		case MSG_GUI_PAINT_ECGGAIN:
//			 DrawEcgGainMark();
			 return 0;

		//add by empty to deal with lang change 2011/06/28
		case MSG_GUI_LANG_CHANGE:
			 DealWithLangChange (LOBYTE(wParam));
			 return 0;

		default:
			 break;
	}

	return  DefaultTskProc(hdl, msg, wParam,lParam);
}


#if _ENB_REC_FUNC > 0
INT32  RecTskProc (HANDLE hdl, INT32 msg, UINT32 wParam, UINT32 lParam)
{
	switch (msg)
	{
		case MSG_PRTCL_SYSKB:
			SysKbSendPack((PACKETFRAME*)lParam);
			break;

		case MSG_PRTCL_FETAL:
			FetalSendPack((PACKETFRAME*)lParam);
			break;

		case MSG_PRTCL_PRINTER:
			switch (LOWORD(wParam))
			{
				case REC_RT_CONTI:
				case REC_RT_SLICE:
				case REC_RT_AUTO:
					RecDealWithEvents(REC_EVENT_MONITOR);
					break;
			
				case REC_TREND_GRAPH:
					RecDealWithEvents(REC_EVENT_TRENDGRAPH);
					break;
			
				case REC_TREND_TAB:
					RecDealWithEvents(REC_EVENT_TRENDTABLE);
					break;
			
				case REC_OXYCRG_RECORD:
					RecDealWithEvents(REC_EVENT_OXYCRT);
					break;
			
				case REC_ALARM_RECALL:
					RecDealWithEvents(REC_EVENT_ALM_RECALL);
					break;
			
				case REC_NIBP_RETRO:
					RecDealWithEvents(REC_EVENT_NIBPLIST);
					break;
			
				case REC_WAVE_RECALL:
					RecDealWithEvents(REC_EVENT_WAVERECALL);
					break;
			
				case REC_FREEZE:
					RecDealWithEvents(REC_EVENT_FREEZE);
					break;

				case REC_SELF_TEST:
					RecDealWithEvents(REC_EVENT_SELFTEST);
					break;

				case REC_FETAL_RECALL:
					RecDealWithEvents(REC_EVENT_FETAL);
					break;

				case REC_SETUP_PRINTER:
					PrinterSendPacket((PACKETFRAME*)lParam);
					break;

				case REC_FETAL_TIMING:
					RecFhrGraph_112 (&RecEventClass);
					break;

				case REC_RECALL_PAGE:
					RecDealWithEvents(REC_EVENT_RECALLPAGE);
					break;

				case REC_RECALL_ALL:
					RecDealWithEvents(REC_EVENT_RECALLALL);
					break;

				case REC_STOP:
					if ((TRUE == RecEventClass.fetalAddData->isBegin
						&& REC_EVENT_FETAL == RecEventClass.source)
						|| (TRUE == RecEventClass.semaphore ))
					{
						RecDealWithEvents(RecEventClass.source);
					}
					break;
			
				default:
					break;
			}
			break;

		case MSG_PRTCL_ANALY:
			AnalySendPack((UCHAR*)lParam);
			break;

		default:
			break;
	}
	return DefaultTskProc(hdl, msg, wParam,lParam);
}
#endif


