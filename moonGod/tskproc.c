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
				// ��������ʵ�ִ�ӡ������
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
** ���ڽ��沼�ֵ�����Ϣ��˵��:
**	 �ڿ�ʼ���沼��ǰ���������Ƚ����Ի������ԣ� �������desktop��MSG_SCRMAN��Ϣ����
** ���ڹ������������жԻ��򷢳�quit��Ϣ�������Ի������Ϣѭ����
**	 Ȼ����post��Ϣ MSG_SCRMAN + SM_LAYOUT�� �����Ľ��沼��������ʵ�֡���post������send��
** ������Ϊ��ǰ��ĶԻ�����Ϣѭ����û�н��������Ա���post��
**/
VOID gui_OnScnManMsg (UINT32 wParam, UINT32 lParam)
{
	lParam = lParam;
	switch (wParam) 
	{
		case SM_MENU:			//����ϵͳ���˵�.
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
			 PostMessage(SysGui_HTSK, MSG_SCRMAN, SM_LAYOUT, 0); //��ʼ��Ļ����
			 break;

		case SM_LAYOUT:
			 LayoutScreen();	//������Ļ����
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

	// �˴����
	// 1. TCP��ʵʱ����
	// 3. �㲥��ʵʱ����

	BOOL admited_by_cms = 0;//GetNetConnect();
	data_len = 0;
	//PactOnlineNotifyPacket(sNetSendDataBuffer, &data_len, &gHyp6NetInfo);
	
//	if (0 <= gBroadcastSocket)
//		SaveDataToUdpSendBuffer(sNetSendDataBuffer, data_len);

	if (admited_by_cms) 
	{
		// ȡ�õ�ǰģ����
		GetParaModuleInfo(&exist_module_count, exist_module_name,
							&onlaod_module_count, onload_module_name,
							&unload_module_count, unload_module_name);

		if (gHyp6NetInfo.bHaveAdmittedPatient)
		{
			if (GetNewConnect())
			{
				SetNewConnect(FALSE);						
				// �������ϵ�,���ͻ������͵ȳ�ʼ������
						
				// ����������Ϣ��
				data_len = 0;
				PackDeviceBaseInfo( sNetSendDataBuffer, &data_len );
				SaveDataToTcpSendBuffer( sNetSendDataBuffer, data_len );

				// ������Ϣ��
				data_len = 0;
				PackPatientInformation( sNetSendDataBuffer, &data_len, cmd_notify_packet);
				SaveDataToTcpSendBuffer( sNetSendDataBuffer, data_len );						

				// ϵͳͨ�����ð�
				data_len = 0;
				PackDeviceGeneralSetting( sNetSendDataBuffer, &data_len, 0xFFFFFFFF , cmd_notify_packet);
				SaveDataToTcpSendBuffer( sNetSendDataBuffer, data_len );						

				// ����ͨ�����ð�
				data_len = 0;
				PackAlarmGeneralSetting( sNetSendDataBuffer, &data_len, 0xFFFFFFFF, cmd_notify_packet);
				SaveDataToTcpSendBuffer( sNetSendDataBuffer, data_len );							

				for (  i = 0; i < exist_module_count; i ++ )
				{
					// ��ǰģ��ļ���֪ͨ��
					data_len = 0;							
					PackModuleOnLoadPacket( sNetSendDataBuffer, &data_len, exist_module_name[i] );
					SaveDataToTcpSendBuffer( sNetSendDataBuffer, data_len );

					data_len = 0;
					PackModuleInitSetting( exist_module_name[i], sNetSendDataBuffer, &data_len );
					SaveDataToTcpSendBuffer( sNetSendDataBuffer, data_len );
				}
				/* ����ģ���ʼ�����*/				
				SetCmsPlusModeNormal();
			}
			else
			{
				// ȡ�õ�ǰ�¼��ص�ģ�����ж�ص�ģ��
				for (  i = 0; i < onlaod_module_count; i ++ )
				{
					// ��ǰģ��ļ���֪ͨ��
					data_len = 0;							
					PackModuleOnLoadPacket( sNetSendDataBuffer, &data_len, onload_module_name[i] );
					SaveDataToTcpSendBuffer( sNetSendDataBuffer, data_len );

					data_len = 0;
					PackModuleInitSetting( onload_module_name[i], sNetSendDataBuffer, &data_len );
					SaveDataToTcpSendBuffer( sNetSendDataBuffer, data_len );
				}


				// ȡ�õ�ǰ�¼��ص�ģ�����ж�ص�ģ��
				for (  i = 0; i < unload_module_count; i ++ )
				{
					// ��ǰģ��ļ���֪ͨ��
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
					
		// �õ����ݣ��������
		data_len = 0;
		//PackCurrentAlarmInfo( sNetSendDataBuffer, & data_len, 
		//						phs_alm, phs_alm_count, tech_alm, tech_alm_count );

		if ( admited_by_cms && gHyp6NetInfo.bHaveAdmittedPatient )
			SaveDataToTcpSendBuffer( sNetSendDataBuffer, data_len );
	}
	
}
#endif

/*
��Щgui������Ҫ��usb״̬����
*/
static VOID gui_UsbProcess(VOID)
{
	static INT8 flag = FALSE;
	if (GetUsbStorage() == '1')
	{
		if (flag == FALSE)
		{
			flag = TRUE;
			/* ����Ϊ������ */

			/* �Զ����������ļ�����ʱĿ¼ */
			GetLanguageFile("/mnt/disk");
			/* ���������ļ����� */
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
//	ShowSysInfoItem(); // ˢ����ʾ��
//	ShowBattaryState();// ˢ�µ�ص���, 
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
			 /* ������ڶ���״̬��,������ť����.���κ�һ�������˳�����. */
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
					gui_OnSysKeyMsg(wParam, lParam); // �ڶ���˵���,���Գ���'����'������Ϣ.
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


