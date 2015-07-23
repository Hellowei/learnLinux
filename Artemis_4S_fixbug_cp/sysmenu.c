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

#define   SYSMENU_GLOBALS 
#include  "includes.h"

#define  SYSMENU_TEST	0  // 调试开关


STRINGID gOnOff[]  = { 
	STR_SWITCH_OFF, STR_SWITCH_ON
};

STRINGID gAlmLev[] = {
	STR_LEVEL_HIGH, STR_LEVEL_MIDDLE, STR_LEVEL_LOW
};

STRINGID gWeekName[] = {
	STR_WEEK_SUNDAY,
	STR_WEEK_MONDAY,
	STR_WEEK_TUESDAY,
	STR_WEEK_WEDNESDAY,
	STR_WEEK_THURSDAY,
	STR_WEEK_FIRDAY,
	STR_WEEK_SATURDAY
};

PMAINWIN GetMainWndMem(INT16 id)
{
  // 因为控件数目多
  // 而对一个对话框需要一段连续内存
  // 这里就分成两部分
  // 在添加新的对话框时候要特别注意
  return (PMAINWIN)(GlobalWndMem + id);
}

PCONTROL GetCtrlWndMem(INT16 id)
{
  return (PCONTROL)GetMainWndMem(id);
}



#if 0
/**
	对本主窗口所属的控件进行特定的设置;
	
	控件默认的颜色, 可能不符合标题栏的要求;重新设置颜色.
	控件默认的字体可能不适合, 需要重新设置.
	在winstr.cpp,定义全局字符缓冲区时, 定义了一些填充的字符:0123456789...,
	在第一次显示时会错误.
**/

void AllModuleSettingToBuffer(void)
{
	static UCHAR sNetSendDataBuffer[1024 * 5];
	INT16 exist_module_count = 0;
	INT16 exist_module_name[8];
	
	INT16 onlaod_module_count = 0;
	INT16 onload_module_name[8];
	
	INT16 unload_module_count = 0;
	INT16 unload_module_name[8];

	// 取得当前模块数
	GetParaModuleInfo( &exist_module_count, exist_module_name,
		&onlaod_module_count, onload_module_name,
		&unload_module_count, unload_module_name );

	INT32 data_len = 0;
	INT16 i;
	
	for (  i = 0; i < exist_module_count; i ++ )
	{
		data_len = 0;
		//PackModuleInitSetting( exist_module_name[i], sNetSendDataBuffer, &data_len);
//		SaveDataToTcpSendBuffer( sNetSendDataBuffer, data_len );
	}
}
#endif

#if 1

enum doctor_mark_index
{
	DR_NULL,
	DR_MARK_A,
	DR_MARK_B,
	DR_MARK_C,
	DR_MARK_D,
	DR_MARK_E,
	DR_MARK_F,
	DR_MARK_G,
	DR_MARK_H,
	DR_MARK_I,
	DR_MARK_J,
	DR_MARK_K,
	DR_MARK_L,
	DR_MARK_M,
	DR_MARK_N,
	DR_MARK_O,
	DR_MARK_MAX
}DRM_INDEX;

INT32 DoctorMarkProc(HANDLE hWnd, INT32 message, DWORD wParam, LPARAM lParam)
{
	switch( message )
	{
		case MSG_COMMAND:
		{
			UINT8 type = (UINT8)(LOWORD(wParam) - IDC_DOCTOR_MARK_A + 1);
			if (type < DR_MARK_MAX)
			{
				FetalWaveBuffWritePtr->event = type;
			}
			else
			{
				FetalWaveBuffWritePtr->event = 0;
			}
			EndDialog(hWnd, IDOK);
			return 0;
		}		

		default:
			break;
	}
	return DefaultDialogProc (hWnd, message, wParam, lParam);
}


VOID DoctorMarkDialog(HANDLE hOwner)
{
	enum dialog_size{
		DLG_COLUMN_WIDTH = 200,
		DLG_ROW_H = 29,
		XPOS1 = DLG_OFFSET,
		XPOS2 = XPOS1 + DLG_COLUMN_WIDTH + DLG_OFFSET,
		XPOS3 = XPOS2 + DLG_COLUMN_WIDTH + DLG_OFFSET,
		YPOS1 = DLG_OFFSET,
		YPOS2 = YPOS1 + DLG_ROW_H + DLG_OFFSET,
		YPOS3 = YPOS2 + DLG_ROW_H + DLG_OFFSET,
		YPOS4 = YPOS3 + DLG_ROW_H + DLG_OFFSET,
		YPOS5 = YPOS4 + DLG_ROW_H + DLG_OFFSET,
		DLG_WIDTH = XPOS3 + DLG_COLUMN_WIDTH + DLG_OFFSET,
		DLG_HEIGHT = YPOS5 + DLG_ROW_H + DLG_OFFSET + DLG_MENU_HIGHT,
	}DLG_SIZE;
	DLGTEMPLATE dlg_data = {
		WS_ABSSCRPOS | WS_CAPTION | WS_BORDER | WS_MODALDLG, 0, 
		20, 50, DLG_WIDTH, DLG_HEIGHT, STR_DLG_DRM_TITLE, 0, NULL, 0L,
	};
	static BUTTONDATA btn[DR_MARK_MAX] = {0};
	BUTTONDATA btn_exit	= gBtn_Exit;
	CTRLDATA ctrl_data[] = {
		{	CTRL_BUTTON, 
			WS_VISIBLE | WS_TABSTOP, WS_EX_NONE,
			XPOS1,  YPOS1, DLG_COLUMN_WIDTH, DLG_ROW_H,
			IDC_DOCTOR_MARK_A, STR_DLG_DRM_A, 0L, 0L},
		{	CTRL_BUTTON, 
			WS_VISIBLE | WS_TABSTOP, WS_EX_NONE,
			XPOS2,  YPOS1, DLG_COLUMN_WIDTH, DLG_ROW_H,
			IDC_DOCTOR_MARK_B, STR_DLG_DRM_B, 0L, 0L},
		{	CTRL_BUTTON, 
			WS_VISIBLE | WS_TABSTOP, WS_EX_NONE,
			XPOS3,  YPOS1, DLG_COLUMN_WIDTH, DLG_ROW_H,
			IDC_DOCTOR_MARK_C, STR_DLG_DRM_C, 0L, 0L},
		{	CTRL_BUTTON, 
			WS_VISIBLE | WS_TABSTOP, WS_EX_NONE,
			XPOS1,  YPOS2, DLG_COLUMN_WIDTH, DLG_ROW_H,
			IDC_DOCTOR_MARK_D, STR_DLG_DRM_D, 0L, 0L},
		{	CTRL_BUTTON, 
			WS_VISIBLE | WS_TABSTOP, WS_EX_NONE,
			XPOS2,  YPOS2, DLG_COLUMN_WIDTH, DLG_ROW_H,
			IDC_DOCTOR_MARK_E, STR_DLG_DRM_E, 0L, 0L},
		{	CTRL_BUTTON, 
			WS_VISIBLE | WS_TABSTOP, WS_EX_NONE,
			XPOS3,  YPOS2, DLG_COLUMN_WIDTH, DLG_ROW_H,
			IDC_DOCTOR_MARK_F, STR_DLG_DRM_F, 0L, 0L},
		{	CTRL_BUTTON, 
			WS_VISIBLE | WS_TABSTOP, WS_EX_NONE,
			XPOS1,  YPOS3, DLG_COLUMN_WIDTH, DLG_ROW_H,
			IDC_DOCTOR_MARK_G, STR_DLG_DRM_G, 0L, 0L},
		{	CTRL_BUTTON, 
			WS_VISIBLE | WS_TABSTOP, WS_EX_NONE,
			XPOS2,  YPOS3, DLG_COLUMN_WIDTH, DLG_ROW_H,
			IDC_DOCTOR_MARK_H, STR_DLG_DRM_H, 0L, 0L},
		{	CTRL_BUTTON, 
			WS_VISIBLE | WS_TABSTOP, WS_EX_NONE,
			XPOS3,  YPOS3, DLG_COLUMN_WIDTH, DLG_ROW_H,
			IDC_DOCTOR_MARK_I, STR_DLG_DRM_I, 0L, 0L},
		{	CTRL_BUTTON, 
			WS_VISIBLE | WS_TABSTOP, WS_EX_NONE,
			XPOS1,  YPOS4, DLG_COLUMN_WIDTH, DLG_ROW_H,
			IDC_DOCTOR_MARK_J, STR_DLG_DRM_J, 0L, 0L},
		{	CTRL_BUTTON, 
			WS_VISIBLE | WS_TABSTOP, WS_EX_NONE,
			XPOS2,  YPOS4, DLG_COLUMN_WIDTH, DLG_ROW_H,
			IDC_DOCTOR_MARK_K, STR_DLG_DRM_K, 0L, 0L},
		{	CTRL_BUTTON, 
			WS_VISIBLE | WS_TABSTOP, WS_EX_NONE,
			XPOS3,  YPOS4, DLG_COLUMN_WIDTH, DLG_ROW_H,
			IDC_DOCTOR_MARK_L, STR_DLG_DRM_L, 0L, 0L},
		{	CTRL_BUTTON, 
			WS_VISIBLE | WS_TABSTOP, WS_EX_NONE,
			XPOS1,  YPOS5, DLG_COLUMN_WIDTH, DLG_ROW_H,
			IDC_DOCTOR_MARK_M, STR_DLG_DRM_M, 0L, 0L},
		{	CTRL_BUTTON, 
			WS_VISIBLE | WS_TABSTOP, WS_EX_NONE,
			XPOS2,  YPOS5, DLG_COLUMN_WIDTH, DLG_ROW_H,
			IDC_DOCTOR_MARK_N, STR_DLG_DRM_N, 0L, 0L},
		{	CTRL_BUTTON, 
			WS_VISIBLE | WS_TABSTOP, WS_EX_NONE,
			XPOS3,  YPOS5, DLG_COLUMN_WIDTH, DLG_ROW_H,
			IDC_DOCTOR_MARK_O, STR_DLG_DRM_O, 0L, 0L},
		{	CTRL_BUTTON,  WS_VISIBLE | WS_TABSTOP | BS_ICON, WS_EX_NONE,
			DLG_WIDTH-EXIT_ICON_WIDTH - DLG_OFFSET,
			-(DLG_MENU_HIGHT + EXIT_ICON_HIGH) / 2,
			EXIT_ICON_WIDTH,  EXIT_ICON_HIGH,
			IDC_DOCTOR_MARK_EXIT, STR_DLG_EXIT, 0L, 0L}
	};
	dlg_data.y = SCREEN_HIGH - BOTBAR_HEIGHT- dlg_data.h;
	int i = TABLESIZE(ctrl_data) - 1;
	ctrl_data[i].x = dlg_data.w - 60;
	WNDMEM   wndMem;

	wndMem.pMainWin = GetMainWndMem(IDD_DOCTOR_MARK);
	wndMem.pControl = GetCtrlWndMem(IDC_DOCTOR_MARK_FIRST);
	wndMem.ctrlNum  = TABLESIZE(ctrl_data);
	wndMem.task	 = SysGui_HTSK;

	dlg_data.controlnr = TABLESIZE(ctrl_data);
	dlg_data.controls  = ctrl_data;
	i = 0;
	int loops = IDC_DOCTOR_MARK_O - IDC_DOCTOR_MARK_A + 1;
	for (i = 0; i < loops; i++)
	{
		SetCtrlDataAddData2(ctrl_data, dlg_data.controlnr,
							i + IDC_DOCTOR_MARK_A, (UINT32)&btn[i]);
	}
	SetCtrlDataAddData2(ctrl_data, dlg_data.controlnr, IDC_DOCTOR_MARK_EXIT,
		(UINT32)&btn_exit);
	DialogBoxIndirectParam
		(&dlg_data, hOwner, IDD_DOCTOR_MARK, DoctorMarkProc, 0, &wndMem);
}
#endif


extern UINT8 LCSysBoard;

INT32  ShutdownProc(HANDLE hWnd, INT32 message, DWORD wParam, LPARAM lParam)
{
	if( MSG_COMMAND == message )
	{
		if (IDC_SHUTDOWN_OK_B == LOWORD(wParam))
		{
			if (LCSysBoard)
			{
				HWND hCtrl;
				hCtrl = GetDlgItem(hWnd, IDC_SHUTDOWN_OK_B);
				ShowWindow(hCtrl, SW_HIDE);
				hCtrl = GetDlgItem(hWnd, IDC_SHUTDOWN_CANCEL_B);
				ShowWindow(hCtrl, SW_HIDE);
				hCtrl = GetDlgItem(hWnd, IDC_SHUTDOWN_ASKED_L);
				SetWindowText(hCtrl, 0);
				hCtrl = GetDlgItem(hWnd, IDC_SHUTDOWN_WARNED_L);
				SetWindowText(hCtrl, STR_MSGBOX_CAP_SYSTEM_POWEROFF);
				while(!KillSignal)
				{
					SendSystemBoardCmd(SYSKB_CMD_POWER, TRUE);
					ms_sleep(500);
				}
			}
			else
			{
				SysPowerOff();
				system("halt");
				SendSystemBoardCmd(SYSKB_CMD_POWER, TRUE);
				SendSystemBoardCmd(SYSKB_CMD_POWER, TRUE);
				SendSystemBoardCmd(SYSKB_CMD_POWER, TRUE);
				SendSystemBoardCmd(SYSKB_CMD_POWER, TRUE);
				SendSystemBoardCmd(SYSKB_CMD_POWER, TRUE);
			}
		}
		EndDialog(hWnd, IDOK);
	}
	return DefaultDialogProc (hWnd, message, wParam, lParam);
}

VOID ShutdownDialog(VOID)
{
	if (_menu_lev > 0)
	{
		// 非主窗口则返回主窗口
		BacktoMainScreen();
		return;
	}
	
	DLGTEMPLATE dlg_data = {
		WS_ABSSCRPOS | WS_CAPTION | WS_BORDER | WS_MODALDLG, 0, 
		0, 0, 0, 0, STR_MSGBOX_CAP_SYSTEM_POWEROFF, 0, NULL, 0L,
	};
	
	BUTTONDATA btn[2] = {0};
	
	CTRLDATA ctrl_data[] = {
		{	CTRL_STATIC, WS_VISIBLE | SS_CENTER, WS_EX_NONE,
			0, 0, 0, 0,
			IDC_SHUTDOWN_ASKED_L, 	STR_MSGBOX_PRO_SYSTEM_POWEROFF1, 0L, 0L },
		{	CTRL_STATIC, WS_VISIBLE | SS_CENTER, WS_EX_NONE,
			0, 0, 0, 0,
			IDC_SHUTDOWN_WARNED_L, 	STR_MSGBOX_PRO_SYSTEM_POWEROFF2, 0L, 0L },
		{	CTRL_BUTTON, WS_VISIBLE | WS_TABSTOP, WS_EX_NONE,
			0, 0, 80, 24,
			IDC_SHUTDOWN_CANCEL_B, 	STR_MSGBOX_CANCEL, 0L, 0L	},
		{	CTRL_BUTTON, WS_VISIBLE | WS_TABSTOP, WS_EX_NONE,
			0, 0, 80, 24,
			IDC_SHUTDOWN_OK_B, 		STR_MSGBOX_OK, 0L, 0L	}
	};

	WNDMEM   wndMem;
	SIZE text1_size;
	SIZE text2_size;
	short width = 0; 
	short height;
	
	GetTextExtentEx(GetSystemFont(SYSLOGFONT_SMAFONT), 
		LoadString(STR_MSGBOX_PRO_SYSTEM_POWEROFF1), -1, &text1_size);
	GetTextExtentEx(GetSystemFont(SYSLOGFONT_SMAFONT), 
		LoadString(STR_MSGBOX_PRO_SYSTEM_POWEROFF2), -1, &text2_size);

	width = DLG_OFFSET * 2 + MAX(text1_size.cx, text2_size.cx) + 2;
	height = 8;
	ctrl_data[0].w = text1_size.cx + 2;
	ctrl_data[0].h = text1_size.cy + 2;
	ctrl_data[0].x = (width - ctrl_data[0].w) >> 1;
	ctrl_data[0].y = height;
	height += ctrl_data[0].h + 5;
	ctrl_data[1].w = text2_size.cx + 2;
	ctrl_data[1].h = text2_size.cy + 2;
	ctrl_data[1].x = (width - ctrl_data[1].w) >> 1;
	ctrl_data[1].y = height;
	height += ctrl_data[1].h + DLG_OFFSET;
	ctrl_data[2].x = (width - (ctrl_data[2].w + 10 + ctrl_data[3].w)) / 2;
	ctrl_data[2].y = height;
	ctrl_data[2].dwAddData2 = (DWORD)&btn[0];
	if (ctrl_data[2].x < 0)
		return;

	ctrl_data[3].x = ctrl_data[2].x + ctrl_data[2].w + 10;
	ctrl_data[3].y = height;
	ctrl_data[3].dwAddData2 = (DWORD)&btn[1];
	height += ctrl_data[3].h + DLG_OFFSET;
	height += GetMainWinMetrics (MWM_CAPTIONY);
	
	wndMem.pMainWin = GetMainWndMem(IDD_SHUTDOWN);
	wndMem.pControl = GetCtrlWndMem(IDC_SHUTDOWN_FIRST);
	wndMem.ctrlNum  = TABLESIZE(ctrl_data);
	wndMem.task	 = SysGui_HTSK;

	dlg_data.w = width;
	dlg_data.h = height;
	dlg_data.controlnr = wndMem.ctrlNum;
	dlg_data.controls  = ctrl_data;
	DialogBoxIndirectParam
		(&dlg_data, 0, IDD_SHUTDOWN, ShutdownProc, 0, &wndMem);
}

#define DEBUG_MENU 0
#if DEBUG_MENU > 0
VOID TestFunc1(HWND parent, HWND ctrl, LPARAM lParam)
{
	parent = parent;
	ctrl = ctrl;
	lParam = lParam;
	printf("TestFunc1\n");
}

VOID TestFunc2(HWND parent, HWND ctrl, LPARAM lParam)
{
	parent = parent;
	ctrl = ctrl;
	lParam = lParam;
	printf("TestFunc2\n");
	SetPenColor(HDC_SCREEN, PIXEL_yellow);
	D3DLine(HDC_SCREEN, 10, 100,100, 400, 390);
	DrawLine(HDC_SCREEN, 80,100, 260, 390);
	D3DLine(HDC_SCREEN, 1, 100,100, 280, 390);
	D3DLine(HDC_SCREEN, 2, 120,100, 300, 390);
	D3DLine(HDC_SCREEN, 3, 140,100, 320, 390);
	D3DLine(HDC_SCREEN, 4, 160,100, 340, 390);
	D3DLine(HDC_SCREEN, 5, 180,100, 360, 390);
	D3DLine(HDC_SCREEN, 6, 200,100, 380, 390);
}

VOID TestFunc3(HWND parent, HWND ctrl, LPARAM lParam)
{
	parent = parent;
	ctrl = ctrl;
	lParam = lParam;
	printf("TestFunc3\n");
}

VOID TestFunc4(HWND parent, HWND ctrl, LPARAM lParam)
{
	parent = parent;
	ctrl = ctrl;
	lParam = lParam;
	printf("TestFunc4\n");
}
#endif

static VOID ChangeFaceType(VOID)
{
	BacktoMainScreen();
	MonitorConfig.faceType++;
	if (MonitorConfig.faceType == FACE_MAX)
		MonitorConfig.faceType = FACE_STD;
	
	if (MonitorInfo.inDemo)
		SetFetalMonitorDemoStyle(TRUE);

	StartLayoutSession();
}

static BOOL sUnlockFlag = FALSE;

static VOID SystemSetupInit(HWND hWnd, DWORD wParam, LPARAM lParam)
{
	HWND hCtrl;
	wParam = wParam;
	lParam = lParam;
	sUnlockFlag = FALSE;
	SetListBoxCurChoi(IDD_SYSTEM_CONFIG, IDC_SYSTEM_CONFIG_FETAL_MODE_LB,
		FhrConfig.mode);
	SetListBoxCurChoi(IDD_SYSTEM_CONFIG, IDC_SYSTEM_CONFIG_FETAL_VOL_CH_LB,
		FhrConfig.source);
	SetListBoxCurChoi(IDD_SYSTEM_CONFIG, IDC_SYSTEM_CONFIG_FETAL_TOCO_VAL_LB,
		FhrConfig.zero);
	SetListBoxCurChoi(IDD_SYSTEM_CONFIG, IDC_SYSTEM_CONFIG_FETAL_FM_MODE_LB,
		FhrConfig.type);
	SetListBoxCurChoi(IDD_SYSTEM_CONFIG, IDC_SYSTEM_CONFIG_ALM_SWITCH_LB,
		FhrConfig.alarm);
	if (FALSE == MonitorConfig.alarmSoundOn)
	{
		SetListBoxCurChoi(IDD_SYSTEM_CONFIG, IDC_SYSTEM_CONFIG_ALM_VOL_LB, 0);
	}
	else
	{
		SetListBoxCurChoi(IDD_SYSTEM_CONFIG, IDC_SYSTEM_CONFIG_ALM_VOL_LB,
			MonitorConfig.alarmVolume);
	}
	SetListBoxCurChoi(IDD_SYSTEM_CONFIG, IDC_SYSTEM_CONFIG_FETAL_VOL_LB,
		FhrConfig.volume);
	SetListBoxCurChoi(IDD_SYSTEM_CONFIG, IDC_SYSTEM_CONFIG_KEY_VOL_LB,
		MonitorConfig.kbVol);
	SetListBoxCurChoi(IDD_SYSTEM_CONFIG, IDC_SYSTEM_CONFIG_SPEED_LB,
		FhrConfig.sweep);
	SetListBoxCurChoi(IDD_SYSTEM_CONFIG, IDC_SYSTEM_CONFIG_SPLINE_LB,
		FhrConfig.detach);
		
	SetSpinBoxIntValue(IDD_SYSTEM_CONFIG, IDC_SYSTEM_CONFIG_ALM_FHR_HI_SB,
		FhrConfig.FhrAlarmLimitHi, 239, FhrConfig.FhrAlarmLimitLo + 2);
	SetSpinBoxIntValue(IDD_SYSTEM_CONFIG, IDC_SYSTEM_CONFIG_ALM_FHR_LO_SB,
		FhrConfig.FhrAlarmLimitLo, FhrConfig.FhrAlarmLimitHi - 2, 31);

   if (MonitorInfo.inDemo)
   {
//        hCtrl = GetDlgItem(hWnd, IDC_SYSTEM_CONFIG_ALM_FHR_HI_SB);
//	    EnableWindow(hCtrl, FALSE);

//        hCtrl = GetDlgItem(hWnd, IDC_SYSTEM_CONFIG_ALM_FHR_LO_SB);
//	    EnableWindow(hCtrl, FALSE);
   }
   
    hCtrl = GetDlgItem(hWnd, IDC_SYSTEM_CONFIG_FETAL_VOL_CH_LB);
	EnableWindow(hCtrl, (FhrConfig.mode == 2));
	int i;
	for (i = IDC_SYSTEM_CONFIG_FIRST; i < IDC_SYSTEM_CONFIG_EXIT_B; i++)
	{
		if (0 == (hCtrl = GetDlgItem(hWnd, i))) continue;
		SetWindowBkColor(hCtrl, ((PCONTROL)hWnd)->iBkColor);
	}

	
	if (MonitorInfo.inDemo)
	{
		hCtrl = GetDlgItem(hWnd, IDC_SYSTEM_CONFIG_DEFAULT_B);
		if (hCtrl)
		{
			EnableWindow(hCtrl, FALSE);
		}
		hCtrl = GetDlgItem(hWnd, IDC_SYSTEM_CONFIG_SET_FM_B);
		if (hCtrl)
		{
			EnableWindow(hCtrl, FALSE);
		}
	}
	
	
//    if ((FhrConfig.mode != 2) && ((MonitorConfig.faceType == FACE_STD 
//        || MonitorConfig.faceType == FACE_STD_SINGLE)))
	if (FhrConfig.mode != 2)
	{
    	hCtrl = GetDlgItem(hWnd, IDC_SYSTEM_CONFIG_SPLINE_LB);
    	if (hCtrl)
    	{
    		EnableWindow(hCtrl, FALSE);
    	}
    	SetListBoxCurChoi(IDD_SYSTEM_CONFIG, IDC_SYSTEM_CONFIG_SPLINE_LB, 0);
    	FhrConfig.detach = 0;
    	SetFetalDetach(FhrConfig.detach);
    	ReDrawFetalWave(FetalWavePrint);
	}
	
#if 0  //由系统版发音，不再从参数板发音
	hCtrl = GetDlgItem(hWnd, IDC_SYSTEM_CONFIG_ALM_VOL_LB);
	if (hCtrl)
	{
		EnableWindow(hCtrl, FALSE);
	}
	hCtrl = GetDlgItem(hWnd, IDC_SYSTEM_CONFIG_KEY_VOL_LB);
	if (hCtrl)
	{
		EnableWindow(hCtrl, FALSE);
	}
#endif
}

BOOL g_changeSpeed = FALSE;//事件且又变速的情况下，改变画刷 @VinYin 2015-05-22
static BOOL SystemSetup_OnCommand(HWND hWnd, DWORD wParam, LPARAM lParam)
{
	BOOL ret;
	ret = TRUE;
	switch(LOWORD(wParam))
	{
		case IDC_SYSTEM_CONFIG_EXIT_B:
			EndDialog(hWnd,  IDOK);
			break;

		case IDC_SYSTEM_CONFIG_DEFAULT_B:
			if (MonitorInfo.inDemo == FALSE)
			{
				if (IDYES == MessageBox(hWnd,
					STR_MSGBOX_PRO_DEFAULT_CONFIG, STR_NULL,
					STR_DLG_SETUP_DEFAULT,
					MB_ALIGNCENTER | MB_YESNO, SysGui_HTSK))
				{
					Load_DefCfg_Monitor(TRUE);
					Load_DefCfg_Fetal();
					Save_Config(CFG_KEYID_MAX);
					ReInitFhrGphMem(!MonitorConfig.nightModeOn);
					BacktoMainScreen();
					StartLayoutSession();
					ClearAllAlarm(0);
				}
			}
			break;

		case IDC_SYSTEM_CONFIG_FETAL_MODE_LB:
			if (HIWORD(wParam) == LBN_CHANGED || HIWORD(wParam) == LBN_ENTER)
			{
				INT16 ret = FhrConfig.mode;
				if (HIWORD(wParam) == LBN_CHANGED)
				{
					ret = GetListBoxCurChoi(IDD_SYSTEM_CONFIG,
										IDC_SYSTEM_CONFIG_FETAL_MODE_LB);
				}
				if (HIWORD(wParam) == LBN_ENTER)
				{
					ret = OnTouchListbox(hWnd, IDD_SYSTEM_CONFIG,
						IDC_SYSTEM_CONFIG_FETAL_MODE_LB, STR_DLG_FHR_TYPE);
				}
				if (ret == FhrConfig.mode)
					break;
				if (sUnlockFlag == FALSE)
				{
					if (IDOK == PasswordDialog(hWnd, 2, 0))
					{
						sUnlockFlag = TRUE;
					}
				}
				if (sUnlockFlag == TRUE)
				{
					HWND  hCtrl;
					sUnlockFlag == FALSE;
					FhrConfig.mode = ret;
					Save_Config(CFG_KEYID_FETALMODE);
					hCtrl = GetDlgItem(hWnd, IDC_SYSTEM_CONFIG_FETAL_VOL_CH_LB);
					if (hCtrl)
					{
						if (ret < 2)
						{
							FhrConfig.source = ret;
							EnableWindow(hCtrl, FALSE);
						}
						else
						{
							EnableWindow(hCtrl, TRUE);
						}
						SetListBoxCurChoi(IDD_SYSTEM_CONFIG,
										  IDC_SYSTEM_CONFIG_FETAL_VOL_CH_LB,
										  FhrConfig.source);
						Save_Config(CFG_KEYID_FHRVOICECHANNEL);
					}
					FetalSetMoudle(FALSE,FALSE);
					ClearAllAlarm(0);
					
				    if ((FhrConfig.mode != 2) && ((MonitorConfig.faceType == FACE_STD 
                        || MonitorConfig.faceType == FACE_STD_SINGLE)))
                	{
                    	SetListBoxCurChoi(IDD_SYSTEM_CONFIG, IDC_SYSTEM_CONFIG_SPLINE_LB, 0);
                    	FhrConfig.detach = 0;
                    	SetFetalDetach(FhrConfig.detach);
                    	ReDrawFetalWave(FetalWavePrint);
                	}
					
					//if (ret == 2 || FhrConfig.mode == 2)
					{
						StartLayoutSession();
					}
				}
				else
				{
					SetListBoxCurChoi(IDD_SYSTEM_CONFIG,
									  IDC_SYSTEM_CONFIG_FETAL_MODE_LB,
									  FhrConfig.mode);
				}
				//Save_Fetal_Config(NMAP_FHR_TYPE_CH_VOL_TOCO);
			}
			break;

		case IDC_SYSTEM_CONFIG_FETAL_VOL_CH_LB:
			if (HIWORD(wParam) == LBN_CHANGED || HIWORD(wParam) == LBN_ENTER)
			{
				INT16 ret = FhrConfig.source;
				if (HIWORD(wParam) == LBN_CHANGED)
				{
					ret = GetListBoxCurChoi(IDD_SYSTEM_CONFIG,
										IDC_SYSTEM_CONFIG_FETAL_VOL_CH_LB);
				}
				if (HIWORD(wParam) == LBN_ENTER)
				{
					ret = OnTouchListbox(hWnd, IDD_SYSTEM_CONFIG,
						IDC_SYSTEM_CONFIG_FETAL_VOL_CH_LB, STR_DLG_FHR_SOURCE);
				}
				if (ret == FhrConfig.source)
					break;
				FhrConfig.source = ret;
				//Save_Fetal_Config(NMAP_FHR_TYPE_CH_VOL_TOCO);
				Save_Config(CFG_KEYID_FHRVOICECHANNEL);
				FetalSetMoudle(FALSE,FALSE);
			}
			break;

		case IDC_SYSTEM_CONFIG_FETAL_TOCO_VAL_LB:
			if (HIWORD(wParam) == LBN_CHANGED || HIWORD(wParam) == LBN_ENTER)
			{
				INT16 ret = FhrConfig.zero;
				if (HIWORD(wParam) == LBN_CHANGED)
				{
					ret = GetListBoxCurChoi(IDD_SYSTEM_CONFIG,
										IDC_SYSTEM_CONFIG_FETAL_TOCO_VAL_LB);
				}
				if (HIWORD(wParam) == LBN_ENTER)
				{
					ret = OnTouchListbox(hWnd, IDD_SYSTEM_CONFIG,
						IDC_SYSTEM_CONFIG_FETAL_TOCO_VAL_LB,
						STR_DLG_TOCO_ZERO_VAL);
				}
				if (ret == FhrConfig.zero)
					break;
				FhrConfig.zero= ret;
				Save_Config(CFG_KEYID_TOCOZEROVALUE);
				//Save_Fetal_Config(NMAP_FHR_TYPE_CH_VOL_TOCO);
				FetalSetMoudle(TRUE,FALSE);
			}
			break;

		case IDC_SYSTEM_CONFIG_FETAL_FM_MODE_LB:
			if (HIWORD(wParam) == LBN_CHANGED || HIWORD(wParam) == LBN_ENTER)
			{
				INT16 ret = FhrConfig.type;
				if (HIWORD(wParam) == LBN_CHANGED)
				{
					ret = GetListBoxCurChoi(IDD_SYSTEM_CONFIG,
										IDC_SYSTEM_CONFIG_FETAL_FM_MODE_LB);
				}
				if (HIWORD(wParam) == LBN_ENTER)
				{
					ret = OnTouchListbox(hWnd, IDD_SYSTEM_CONFIG,
						IDC_SYSTEM_CONFIG_FETAL_FM_MODE_LB,
						STR_DLG_FM_MOVEMENTCAL);
				}
				if (ret != FhrConfig.type)
				{
					FhrConfig.type= ret;
					Save_Config(CFG_KEYID_FETALMOVECALC);
				}
			}
			break;

		case IDC_SYSTEM_CONFIG_ALM_FHR_HI_SB:
			if (HIWORD(wParam) == SBN_CHANGED || HIWORD(wParam) == SBN_ENTER)
			{
				INT16 ret;
				if (HIWORD(wParam) == SBN_CHANGED){
    				ret = GetSpinBoxIntCurValue(IDD_SYSTEM_CONFIG,
    											IDC_SYSTEM_CONFIG_ALM_FHR_HI_SB);
                }

				if (HIWORD(wParam) == SBN_ENTER) 
				{
					INT32 value;
                    char tips[16];
					sprintf(tips, "%d - 239", FhrConfig.FhrAlarmLimitLo + 2);
					value = GetSpinBoxIntCurValue(
									IDD_SYSTEM_CONFIG, IDC_SYSTEM_CONFIG_ALM_FHR_HI_SB);
					SelectKeyboardType(0,
									LoadString(STR_DLG_FHR_ALM_HI), 
									tips);
					UseKeyboard(hWnd, IDC_SYSTEM_CONFIG_ALM_FHR_HI_SB, (LPARAM)&value);
					ret = (INT16)value;
					SetSpinBoxIntCurValue(IDD_SYSTEM_CONFIG,
									IDC_SYSTEM_CONFIG_ALM_FHR_HI_SB, ret);
				}
				ret = GetSpinBoxIntCurValue(IDD_SYSTEM_CONFIG,
											IDC_SYSTEM_CONFIG_ALM_FHR_HI_SB);
											
				if (ret != FhrConfig.FhrAlarmLimitHi)
				{
					ParaAlarmInfo[ALM_PARA_FHR1].AlarmLimitIsChangingFlag = TRUE;
					ParaAlarmInfo[ALM_PARA_FHR2].AlarmLimitIsChangingFlag = TRUE;

					FhrConfig.FhrAlarmLimitHi = ret;
					SetSpinBoxIntMaxValue(IDD_SYSTEM_CONFIG,
											IDC_SYSTEM_CONFIG_ALM_FHR_LO_SB,
											FhrConfig.FhrAlarmLimitHi - 2);
					Save_Config(CFG_KEYID_ALARMFHRHI);

					ParaAlarmInfo[ALM_PARA_FHR1].AlarmLimitIsChangingFlag = FALSE;
					ParaAlarmInfo[ALM_PARA_FHR2].AlarmLimitIsChangingFlag = FALSE;
				}
			}
			break;

		case IDC_SYSTEM_CONFIG_ALM_FHR_LO_SB:
			if (HIWORD(wParam) == SBN_CHANGED || HIWORD(wParam) == SBN_ENTER)
			{
				INT16 ret;

				if (HIWORD(wParam) == SBN_CHANGED){
    				ret = GetSpinBoxIntCurValue(IDD_SYSTEM_CONFIG,
    											IDC_SYSTEM_CONFIG_ALM_FHR_LO_SB);
                }

				if (HIWORD(wParam) == SBN_ENTER) 
				{
					INT32 value;
                    char tips[16];
					sprintf(tips, "31 - %d", FhrConfig.FhrAlarmLimitHi - 2);
					value = GetSpinBoxIntCurValue(
									IDD_SYSTEM_CONFIG, IDC_SYSTEM_CONFIG_ALM_FHR_LO_SB);
					SelectKeyboardType(0,
									LoadString(STR_DLG_FHR_ALM_LO), 
									tips);
					UseKeyboard(hWnd, IDC_SYSTEM_CONFIG_ALM_FHR_LO_SB, (LPARAM)&value);
					ret = (INT16)value;
					SetSpinBoxIntCurValue(IDD_SYSTEM_CONFIG,
									IDC_SYSTEM_CONFIG_ALM_FHR_LO_SB, ret);
				}
				ret = GetSpinBoxIntCurValue(IDD_SYSTEM_CONFIG,
											IDC_SYSTEM_CONFIG_ALM_FHR_LO_SB);

				if (ret != FhrConfig.FhrAlarmLimitLo)
				{
					ParaAlarmInfo[ALM_PARA_FHR1].AlarmLimitIsChangingFlag = TRUE;
					ParaAlarmInfo[ALM_PARA_FHR2].AlarmLimitIsChangingFlag = TRUE;

					FhrConfig.FhrAlarmLimitLo = ret;
					SetSpinBoxIntMinValue(IDD_SYSTEM_CONFIG,
											IDC_SYSTEM_CONFIG_ALM_FHR_HI_SB,
											FhrConfig.FhrAlarmLimitLo + 2);
					Save_Config(CFG_KEYID_ALARMFHRLO);

					ParaAlarmInfo[ALM_PARA_FHR1].AlarmLimitIsChangingFlag = FALSE;
					ParaAlarmInfo[ALM_PARA_FHR2].AlarmLimitIsChangingFlag = FALSE;
				}
			}
			break;

		case IDC_SYSTEM_CONFIG_ALM_SWITCH_LB:
			if (HIWORD(wParam) == LBN_CHANGED || HIWORD(wParam) == LBN_ENTER)
			{
				INT16 ret = FhrConfig.alarm;
				if (HIWORD(wParam) == LBN_CHANGED)
				{
					ret = GetListBoxCurChoi(IDD_SYSTEM_CONFIG,
										IDC_SYSTEM_CONFIG_ALM_SWITCH_LB);
				}
				if (HIWORD(wParam) == LBN_ENTER)
				{
					ret = OnTouchListbox(hWnd, IDD_SYSTEM_CONFIG,
						IDC_SYSTEM_CONFIG_ALM_SWITCH_LB,
						STR_DLG_ALARM_SWITCH);
				}
				if (ret != FhrConfig.alarm)
				{
					FhrConfig.alarm = ret;
					Save_Config(CFG_KEYID_ALARMSWITCH);
					DisplayAlarmSign();
				}
			}
			break;

		case IDC_SYSTEM_CONFIG_ALM_VOL_LB:
			if (HIWORD(wParam) == LBN_CHANGED || HIWORD(wParam) == LBN_ENTER)
			{
				INT16 ret = MonitorConfig.alarmVolume;
				
				if (FALSE == MonitorConfig.alarmSoundOn)
				{
					ret = 0;
				}
				if (HIWORD(wParam) == LBN_CHANGED)
				{
					ret = GetListBoxCurChoi(IDD_SYSTEM_CONFIG,
										IDC_SYSTEM_CONFIG_ALM_VOL_LB);
				}
				if (HIWORD(wParam) == LBN_ENTER)
				{
					ret = OnTouchListbox(hWnd, IDD_SYSTEM_CONFIG,
						IDC_SYSTEM_CONFIG_ALM_VOL_LB,
						STR_DLG_SETUP_ALM_VOL);
				}
				if (ret != MonitorConfig.alarmVolume)
				{
					if (ret == 0)
					{
						if (TRUE == MonitorConfig.alarmSoundOn)
							OnSilence();
					}
					else
					{
						if (FALSE == MonitorConfig.alarmSoundOn)
							OnSilence();
						MonitorConfig.alarmVolume = ret;
						Save_Config(CFG_KEYID_ALARMVOLUME);
					}
				}
			}
			break;

		case IDC_SYSTEM_CONFIG_FETAL_VOL_LB:
			if (HIWORD(wParam) == LBN_CHANGED || HIWORD(wParam) == LBN_ENTER)
			{
				INT16 ret = FhrConfig.volume;
				if (HIWORD(wParam) == LBN_CHANGED)
				{
					ret = GetListBoxCurChoi(IDD_SYSTEM_CONFIG,
										IDC_SYSTEM_CONFIG_FETAL_VOL_LB);
				}
				if (HIWORD(wParam) == LBN_ENTER)
				{
					ret = OnTouchListbox(hWnd, IDD_SYSTEM_CONFIG,
						IDC_SYSTEM_CONFIG_FETAL_VOL_LB,
						STR_DLG_FHR_VOLUME);
				}
				if (ret != FhrConfig.volume)
				{
					FhrConfig.volume = ret;
					Save_Config(CFG_KEYID_FHRVOLUME);
					FetalSetMoudle(FALSE,FALSE);
				}
			}
			break;

		case IDC_SYSTEM_CONFIG_KEY_VOL_LB:
			if (HIWORD(wParam) == LBN_CHANGED || HIWORD(wParam) == LBN_ENTER)
			{
				INT16 ret = MonitorConfig.kbVol;
				if (HIWORD(wParam) == LBN_CHANGED)
				{
					ret = GetListBoxCurChoi(IDD_SYSTEM_CONFIG,
										IDC_SYSTEM_CONFIG_KEY_VOL_LB);
				}
				if (HIWORD(wParam) == LBN_ENTER)
				{
					ret = OnTouchListbox(hWnd, IDD_SYSTEM_CONFIG,
						IDC_SYSTEM_CONFIG_KEY_VOL_LB,
						STR_DLG_SETUP_KEY_VOL);
				}
				if (ret != MonitorConfig.kbVol)
				{
					MonitorConfig.kbVol = ret;
					Save_Config(CFG_KEYID_KEYVOLUME);
					//Save_Fetal_Config(MMAP_ALARM_KEYBOARD_VOLUME);
					
				}
				
			}
			break;

		case IDC_SYSTEM_CONFIG_SPEED_LB:
			if (HIWORD(wParam) == LBN_CHANGED || HIWORD(wParam) == LBN_ENTER)
			{
				INT16 ret = FhrConfig.sweep;
				if (HIWORD(wParam) == LBN_CHANGED)
				{
					ret = GetListBoxCurChoi(IDD_SYSTEM_CONFIG,
											IDC_SYSTEM_CONFIG_SPEED_LB);
				}
				if (HIWORD(wParam) == LBN_ENTER)
				{
					ret = OnTouchListbox(hWnd, IDD_SYSTEM_CONFIG,
						IDC_SYSTEM_CONFIG_SPEED_LB, STR_DLG_SETUP_SPEED);
				}
				if (ret != FhrConfig.sweep)
				{
					g_changeSpeed = TRUE;//事件且又变速的情况下，改变画刷 @VinYin 2015-05-22
					FhrConfig.sweep= ret;
					ReDrawFetalWave(FetalWavePrint);
					ShowSweepSpeed();
					Save_Config(CFG_KEYID_PRINTSPEED);
					g_changeSpeed = FALSE;//事件且又变速的情况下，改变画刷 @VinYin 2015-05-22
				}
			}
			break;

		case IDC_SYSTEM_CONFIG_SPLINE_LB:
			if (HIWORD(wParam) == LBN_CHANGED || HIWORD(wParam) == LBN_ENTER)
			{
				INT16 ret = FhrConfig.detach;
				if (HIWORD(wParam) == LBN_CHANGED)
				{
					ret = GetListBoxCurChoi(IDD_SYSTEM_CONFIG,
											IDC_SYSTEM_CONFIG_SPLINE_LB);
				}
				if (HIWORD(wParam) == LBN_ENTER)
				{
					ret = OnTouchListbox(hWnd, IDD_SYSTEM_CONFIG,
						IDC_SYSTEM_CONFIG_SPLINE_LB, STR_DLG_FHR_DETACH_SPLINE);
				}
				if (ret != FhrConfig.detach)
				{
					FhrConfig.detach = ret;
					SetFetalDetach(FhrConfig.detach);
					ReDrawFetalWave(FetalWavePrint);
					Save_Config(CFG_KEYID_PRINTDETACH);
				}
			}
			break;

		case IDC_SYSTEM_CONFIG_SET_FM_B:
			if (MonitorInfo.inDemo == FALSE)
			{
				if (IDYES == MessageBox(hWnd, STR_MSGBOX_PRO_FMSETZERO, 0,
					STR_MSGBOX_CAP_FMSETZERO, MB_YESNO, SysGui_HTSK))
				{
					FhrParams.fm = 0;
				}
			}
			break;

		case IDC_SYSTEM_CONFIG_PRINT_TEST_B:
		#if _ENB_REC_FUNC
			PrintSetupDialog(hWnd);
		#endif
			break;

		case IDC_SYSTEM_CONFIG_SETUP_B:
			MaintainDialog(hWnd);
			break;

		default:
			ret = FALSE;
			break;
	}
	return ret;
}

static INT32 SystemSetupProc(HANDLE hWnd, INT32 message, DWORD wParam, LPARAM lParam)
{
	switch (message)
	{
		case MSG_INITDIALOG:
			SystemSetupInit(hWnd, wParam, lParam);
			break;
		
		case MSG_COMMAND:

			if (SystemSetup_OnCommand(hWnd, wParam, lParam))
			{
				return 0;
			}
			break;

		default:
			break;
	}
	
	return DefaultDialogProc (hWnd, message, wParam, lParam);
}

static STRINGID FhrType[] = {
	STR_DLG_FHR_FHR1,
	STR_DLG_FHR_FHR2,
	STR_DLG_FHR_DOUBLE
};

static STRINGID FhrSource[] = {
	STR_DLG_FHR_FHR1,
	STR_DLG_FHR_FHR2
};

static STRINGID TocoZero[] = {
	STR_DLG_TOCO_ZERO_00,
	STR_DLG_TOCO_ZERO_05,
	STR_DLG_TOCO_ZERO_10,
	STR_DLG_TOCO_ZERO_15,
	STR_DLG_TOCO_ZERO_20
};

static STRINGID FmCalc[] = {
	STR_DLG_FM_MOVEMENTCAL_AUTO,
	STR_DLG_FM_MOVEMENTCAL_MANUAL,
};

static STRINGID Fhr_vol[] = {
	STR_DLG_CHAR_0,
	STR_DLG_CHAR_1,
	STR_DLG_CHAR_2,
	STR_DLG_CHAR_3,
	STR_DLG_CHAR_4,
	STR_DLG_CHAR_5,
	STR_DLG_CHAR_6,
	STR_DLG_CHAR_7,
	STR_DLG_CHAR_8,
};

static STRINGID SweepSpeed[] = {
	STR_SWEEP_SPEED_1,
	STR_SWEEP_SPEED_2,
	STR_SWEEP_SPEED_3,
};

static STRINGID SoundLev[] = {
	STR_SWITCH_OFF,
	STR_LEVEL_LOW,
	STR_LEVEL_MIDDLE,
	STR_LEVEL_HIGH
};

INT32 SystemSetupDialog(HWND parent)
{
	enum dialog_size{
		DLG_COLUMN1_W = 128,
		DLG_COLUMN2_W = 128,
		DLG_COLUMN3_W = 128,
		DLG_COLUMN4_W = 128,
		DLG_COLUMN1_X = DLG_OFFSET,
		DLG_COLUMN2_X = DLG_COLUMN1_X + DLG_COLUMN1_W + DLG_OFFSET,
		DLG_COLUMN3_X = DLG_COLUMN2_X + DLG_COLUMN2_W + DLG_OFFSET,
		DLG_COLUMN4_X = DLG_COLUMN3_X + DLG_COLUMN3_W + DLG_OFFSET,
			DLG_WIDTH = DLG_COLUMN4_X + DLG_COLUMN4_W + DLG_OFFSET,
		DLG_ROW_H	 = KEY_HEIGHT,
		LABEL_HIGH	= 14,
		LABEL_OFFSET  = (DLG_ROW_H - LABEL_HIGH) / 2,
		DLG_ROW1_Y	= 5,
		DLG_ROW2_Y	= DLG_ROW1_Y + DLG_ROW_H + DLG_OFFSET,
		DLG_ROW3_Y	= DLG_ROW2_Y + DLG_ROW_H + DLG_OFFSET,
		DLG_ROW4_Y	= DLG_ROW3_Y + DLG_ROW_H + DLG_OFFSET,
		DLG_ROW5_Y	= DLG_ROW4_Y + DLG_ROW_H + DLG_OFFSET,
		DLG_ROW6_Y	= DLG_ROW5_Y + DLG_ROW_H + DLG_OFFSET,
		DLG_ROW7_Y	= DLG_ROW6_Y + DLG_ROW_H + DLG_OFFSET,
		DLG_ROW8_Y	= DLG_ROW7_Y + DLG_ROW_H + DLG_OFFSET,
			DLG_HIGH  = DLG_ROW8_Y + DLG_ROW_H + DLG_MENU_HIGHT + DLG_OFFSET,
			DLG_XPOS  = (SCREEN_WIDTH - DLG_WIDTH) / 2,
			DLG_YPOS  = SCREEN_HIGH - DLG_HIGH - BOTTOMBAR_HEIGHT
	};
	static DLGTEMPLATE dlg_data = {
	   WS_ABSSCRPOS | WS_CAPTION | WS_BORDER | WS_MODALDLG, WS_NONE, 
	   (SCREEN_WIDTH - DLG_WIDTH) / 2,
	   SCREEN_HIGH - BOTTOMBAR_HEIGHT - DLG_HIGH, DLG_WIDTH, DLG_HIGH,
	   STR_DLG_SETUP, 0, NULL, 0L	};

	static BUTTONDATA btn[] = {{0}, {0}, {0}, {0}, {0}};
	btn[4] = gBtn_Exit;
	static SPINBOXDATA snb[] = {
		{ FORM_3D, SBTXT_NUM,   0,   0,   0,   0,  50, 210, 180,  1,  0,  0 },
		{ FORM_3D, SBTXT_NUM,   0,   0,   0,   0,  50, 120,  90,  1,  0,  0 },
	};
	
	static LISTBOXDATA ltn[] = {
		{ 3, 1, 3, 0, 0, FhrType,   0 },
		{ 2, 1, 2, 0, 0, FhrSource, 0 },
		{ 5, 1, 5, 0, 0, TocoZero,  0 },
		{ 2, 1, 2, 0, 0, FmCalc,	0 },
		{ 2, 1, 2, 0, 0, gOnOff,	0 },
		{ 4, 1, 4, 0, 0, SoundLev,   0 },
		{ 9, 1, 9, 0, 0, Fhr_vol,   0 },
		{ 4, 1, 4, 0, 0, SoundLev,  0 },
		{ 3, 1, 3, 0, 0, SweepSpeed,0 },
		{ 2, 1, 2, 0, 0, gOnOff,	0 },
	};
	POINT   ctrl_POS[] = {
		{ DLG_COLUMN1_X, DLG_ROW1_Y + LABEL_OFFSET },
		{ DLG_COLUMN1_X, DLG_ROW2_Y + LABEL_OFFSET },
		{ DLG_COLUMN1_X, DLG_ROW3_Y + LABEL_OFFSET },
		{ DLG_COLUMN1_X, DLG_ROW4_Y + LABEL_OFFSET },
		{ DLG_COLUMN1_X, DLG_ROW5_Y + LABEL_OFFSET },
		{ DLG_COLUMN1_X, DLG_ROW6_Y + LABEL_OFFSET },
		{ DLG_COLUMN1_X, DLG_ROW7_Y + LABEL_OFFSET },
		{ DLG_COLUMN1_X, DLG_ROW8_Y + LABEL_OFFSET },
		{ DLG_COLUMN3_X, DLG_ROW1_Y + LABEL_OFFSET },
		{ DLG_COLUMN3_X, DLG_ROW2_Y + LABEL_OFFSET },
		{ DLG_COLUMN3_X, DLG_ROW3_Y + LABEL_OFFSET },
		{ DLG_COLUMN3_X, DLG_ROW4_Y + LABEL_OFFSET },
		{ DLG_COLUMN2_X, DLG_ROW1_Y },
		{ DLG_COLUMN2_X, DLG_ROW2_Y },
		{ DLG_COLUMN2_X, DLG_ROW3_Y },
		{ DLG_COLUMN2_X, DLG_ROW4_Y },
		{ DLG_COLUMN2_X, DLG_ROW5_Y },
		{ DLG_COLUMN2_X, DLG_ROW6_Y },
		{ DLG_COLUMN2_X, DLG_ROW7_Y },
		{ DLG_COLUMN2_X, DLG_ROW8_Y },
		{ DLG_COLUMN4_X, DLG_ROW1_Y },
		{ DLG_COLUMN4_X, DLG_ROW2_Y },
		{ DLG_COLUMN4_X, DLG_ROW3_Y },
		{ DLG_COLUMN4_X, DLG_ROW4_Y },
		{ DLG_COLUMN3_X, DLG_ROW5_Y },
		{ DLG_COLUMN3_X, DLG_ROW6_Y },
		{ DLG_COLUMN3_X, DLG_ROW7_Y },
		{ DLG_COLUMN3_X, DLG_ROW8_Y },
		{ DLG_WIDTH-EXIT_ICON_WIDTH - DLG_OFFSET,
			-(DLG_MENU_HIGHT + EXIT_ICON_HIGH) / 2 }
	};

	SIZE	ctrl_size[] = {
		{ DLG_COLUMN1_W, LABEL_HIGH },
		{ DLG_COLUMN1_W, LABEL_HIGH },
		{ DLG_COLUMN1_W, LABEL_HIGH },
		{ DLG_COLUMN1_W, LABEL_HIGH },
		{ DLG_COLUMN1_W, LABEL_HIGH },
		{ DLG_COLUMN1_W, LABEL_HIGH },
		{ DLG_COLUMN1_W, LABEL_HIGH },
		{ DLG_COLUMN1_W, LABEL_HIGH },
		{ DLG_COLUMN3_W, LABEL_HIGH },
		{ DLG_COLUMN3_W, LABEL_HIGH },
		{ DLG_COLUMN3_W, LABEL_HIGH },
		{ DLG_COLUMN3_W, LABEL_HIGH },
		{ DLG_COLUMN2_W, DLG_ROW_H  },
		{ DLG_COLUMN2_W, DLG_ROW_H  },
		{ DLG_COLUMN2_W, DLG_ROW_H  },
		{ DLG_COLUMN2_W, DLG_ROW_H  },
		{ DLG_COLUMN2_W, DLG_ROW_H  },
		{ DLG_COLUMN2_W, DLG_ROW_H  },
		{ DLG_COLUMN2_W, DLG_ROW_H  },
		{ DLG_COLUMN2_W, DLG_ROW_H  },
		{ DLG_COLUMN4_W, DLG_ROW_H  },
		{ DLG_COLUMN4_W, DLG_ROW_H  },
		{ DLG_COLUMN4_W, DLG_ROW_H  },
		{ DLG_COLUMN4_W, DLG_ROW_H  },
		{ DLG_COLUMN3_W + DLG_COLUMN4_W, DLG_ROW_H  },
		{ DLG_COLUMN3_W + DLG_COLUMN4_W, DLG_ROW_H  },
		{ DLG_COLUMN3_W + DLG_COLUMN4_W, DLG_ROW_H  },
		{ DLG_COLUMN3_W + DLG_COLUMN4_W, DLG_ROW_H  },
		{ EXIT_ICON_WIDTH,  EXIT_ICON_HIGH		  },
	};

	CTRLDATA ctrl_data[]={ 
	{ CTRL_STATIC,  WS_VISIBLE | SS_SIMPLE,  WS_EX_NONE, 0, 0, 0, 0, 
		IDC_SYSTEM_CONFIG_FETAL_MODE_L, STR_DLG_FHR_TYPE, 0L, 0L }, 
	{ CTRL_STATIC,  WS_VISIBLE | SS_SIMPLE,  WS_EX_NONE, 0, 0, 0, 0, 
		IDC_SYSTEM_CONFIG_FETAL_VOL_CH_L, STR_DLG_FHR_SOURCE, 0L, 0L }, 
	{ CTRL_STATIC,  WS_VISIBLE | SS_SIMPLE,  WS_EX_NONE, 0, 0, 0, 0, 
		IDC_SYSTEM_CONFIG_FETAL_TOCO_VAL_L, STR_DLG_TOCO_ZERO, 0L, 0L }, 
	{ CTRL_STATIC,  WS_VISIBLE | SS_SIMPLE,  WS_EX_NONE, 0, 0, 0, 0, 
		IDC_SYSTEM_CONFIG_FETAL_FM_MODE_L, STR_DLG_FM_MOVEMENTCAL, 0L, 0L }, 
	{ CTRL_STATIC,  WS_VISIBLE | SS_SIMPLE,  WS_EX_NONE, 0, 0, 0, 0, 
		IDC_SYSTEM_CONFIG_ALM_FHR_HI_L, STR_DLG_FHR_ALM_HI, 0L, 0L }, 
	{ CTRL_STATIC,  WS_VISIBLE | SS_SIMPLE,  WS_EX_NONE, 0, 0, 0, 0, 
		IDC_SYSTEM_CONFIG_ALM_FHR_LO_L, STR_DLG_FHR_ALM_LO, 0L, 0L }, 
	{ CTRL_STATIC,  WS_VISIBLE | SS_SIMPLE,  WS_EX_NONE, 0, 0, 0, 0, 
		IDC_SYSTEM_CONFIG_ALM_SWITCH_L, STR_DLG_ALARM_SWITCH, 0L, 0L }, 
	{ CTRL_STATIC,  WS_VISIBLE | SS_SIMPLE,  WS_EX_NONE, 0, 0, 0, 0, 
		IDC_SYSTEM_CONFIG_ALM_VOL_L, STR_DLG_SETUP_ALM_VOL, 0L, 0L }, 
	{ CTRL_STATIC,  WS_VISIBLE | SS_SIMPLE,  WS_EX_NONE, 0, 0, 0, 0, 
		IDC_SYSTEM_CONFIG_FETAL_VOL_L, STR_DLG_FHR_VOLUME, 0L, 0L }, 
	{ CTRL_STATIC,  WS_VISIBLE | SS_SIMPLE,  WS_EX_NONE, 0, 0, 0, 0, 
		IDC_SYSTEM_CONFIG_KEY_VOL_L, STR_DLG_SETUP_KEY_VOL, 0L, 0L }, 
	{ CTRL_STATIC,  WS_VISIBLE | SS_SIMPLE,  WS_EX_NONE, 0, 0, 0, 0, 
		IDC_SYSTEM_CONFIG_SPEED_L, STR_DLG_SETUP_SPEED, 0L, 0L }, 
	{ CTRL_STATIC,  WS_VISIBLE | SS_SIMPLE,  WS_EX_NONE, 0, 0, 0, 0, 
		IDC_SYSTEM_CONFIG_SPLINE_L, STR_DLG_FHR_DETACH_SPLINE, 0L, 0L },		
	{ CTRL_LISTBOX, WS_VISIBLE | WS_TABSTOP, WS_EX_NONE, 0, 0, 0, 0, 
		IDC_SYSTEM_CONFIG_FETAL_MODE_LB, 0, 0L, 0L }, 
	{ CTRL_LISTBOX, WS_VISIBLE | WS_TABSTOP, WS_EX_NONE, 0, 0, 0, 0, 
		IDC_SYSTEM_CONFIG_FETAL_VOL_CH_LB, 0, 0L, 0L }, 
	{ CTRL_LISTBOX, WS_VISIBLE | WS_TABSTOP, WS_EX_NONE, 0, 0, 0, 0, 
		IDC_SYSTEM_CONFIG_FETAL_TOCO_VAL_LB, 0, 0L, 0L }, 
	{ CTRL_LISTBOX, WS_VISIBLE | WS_TABSTOP, WS_EX_NONE, 0, 0, 0, 0, 
		IDC_SYSTEM_CONFIG_FETAL_FM_MODE_LB, 0, 0L, 0L }, 
	{ CTRL_SPINBOX, WS_VISIBLE | WS_TABSTOP, WS_EX_NONE, 0, 0, 0, 0, 
		IDC_SYSTEM_CONFIG_ALM_FHR_HI_SB, 0, 0L, 0L }, 
	{ CTRL_SPINBOX, WS_VISIBLE | WS_TABSTOP, WS_EX_NONE, 0, 0, 0, 0, 
		IDC_SYSTEM_CONFIG_ALM_FHR_LO_SB, 0, 0L, 0L }, 
	{ CTRL_LISTBOX, WS_VISIBLE | WS_TABSTOP, WS_EX_NONE, 0, 0, 0, 0, 
		IDC_SYSTEM_CONFIG_ALM_SWITCH_LB, 0, 0L, 0L }, 
	{ CTRL_LISTBOX, WS_VISIBLE | WS_TABSTOP, WS_EX_NONE, 0, 0, 0, 0, 
		IDC_SYSTEM_CONFIG_ALM_VOL_LB, 0, 0L, 0L }, 
	{ CTRL_LISTBOX, WS_VISIBLE | WS_TABSTOP, WS_EX_NONE, 0, 0, 0, 0, 
		IDC_SYSTEM_CONFIG_FETAL_VOL_LB, 0, 0L, 0L }, 
	{ CTRL_LISTBOX, WS_VISIBLE | WS_TABSTOP, WS_EX_NONE, 0, 0, 0, 0, 
		IDC_SYSTEM_CONFIG_KEY_VOL_LB, 0, 0L, 0L }, 
	{ CTRL_LISTBOX, WS_VISIBLE | WS_TABSTOP, WS_EX_NONE, 0, 0, 0, 0, 
		IDC_SYSTEM_CONFIG_SPEED_LB, 0, 0L, 0L }, 
	{ CTRL_LISTBOX, WS_VISIBLE | WS_TABSTOP, WS_EX_NONE, 0, 0, 0, 0, 
		IDC_SYSTEM_CONFIG_SPLINE_LB, 0, 0L, 0L }, 		
	{ CTRL_BUTTON,  WS_VISIBLE | WS_TABSTOP, WS_EX_NONE, 0, 0, 0, 0, 
		IDC_SYSTEM_CONFIG_SET_FM_B, STR_DLG_SETUP_SET_FM, 0L, 0L }, 
	{ CTRL_BUTTON,  WS_VISIBLE | WS_TABSTOP, WS_EX_NONE, 0, 0, 0, 0, 
		IDC_SYSTEM_CONFIG_PRINT_TEST_B, STR_DLG_SETUP_PRINT_B, 0L, 0L }, 
	{ CTRL_BUTTON,  WS_VISIBLE | WS_TABSTOP, WS_EX_NONE, 0, 0, 0, 0, 
		IDC_SYSTEM_CONFIG_SETUP_B, STR_DLG_SYSSETUP_B, 0L, 0L }, 
	{ CTRL_BUTTON,  WS_VISIBLE | WS_TABSTOP, WS_EX_NONE, 0, 0, 0, 0, 
		IDC_SYSTEM_CONFIG_DEFAULT_B, STR_DLG_SETUP_DEFAULT, 0L, 0L },
	{ CTRL_BUTTON,  WS_VISIBLE | WS_TABSTOP | BS_ICON, WS_EX_NONE, 0, 0, 0, 0, 
		IDC_SYSTEM_CONFIG_EXIT_B, 0, 0L, 0L }
 };
	
	INT16 i, loops;
	loops = TABLESIZE(ctrl_data);
	WNDMEM   wndMem;
	
	wndMem.pMainWin = GetMainWndMem(IDD_SYSTEM_CONFIG);
	wndMem.pControl = GetCtrlWndMem(IDC_SYSTEM_CONFIG_FIRST);
	wndMem.ctrlNum  = TABLESIZE(ctrl_data);
	wndMem.task	 = SysGui_HTSK;

	dlg_data.controlnr = loops;
	dlg_data.controls  = ctrl_data;
	for (i = 0; i < loops; i++)
	{
		ctrl_data[i].x = ctrl_POS[i].x;
		ctrl_data[i].y = ctrl_POS[i].y;
		ctrl_data[i].w = ctrl_size[i].cx;
		ctrl_data[i].h = ctrl_size[i].cy;
	}
	i = 0;
	SetCtrlDataAddData2(ctrl_data, loops,
		IDC_SYSTEM_CONFIG_FETAL_MODE_LB, (UINT32)&ltn[i++]);
	SetCtrlDataAddData2(ctrl_data, loops,
		IDC_SYSTEM_CONFIG_FETAL_VOL_CH_LB, (UINT32)&ltn[i++]);
	SetCtrlDataAddData2(ctrl_data, loops,
		IDC_SYSTEM_CONFIG_FETAL_TOCO_VAL_LB, (UINT32)&ltn[i++]);
	SetCtrlDataAddData2(ctrl_data, loops,
		IDC_SYSTEM_CONFIG_FETAL_FM_MODE_LB, (UINT32)&ltn[i++]);
	SetCtrlDataAddData2(ctrl_data, loops,
		IDC_SYSTEM_CONFIG_ALM_SWITCH_LB, (UINT32)&ltn[i++]);
	SetCtrlDataAddData2(ctrl_data, loops,
		IDC_SYSTEM_CONFIG_ALM_VOL_LB, (UINT32)&ltn[i++]);
	SetCtrlDataAddData2(ctrl_data, loops,
		IDC_SYSTEM_CONFIG_FETAL_VOL_LB, (UINT32)&ltn[i++]);
	SetCtrlDataAddData2(ctrl_data, loops,
		IDC_SYSTEM_CONFIG_KEY_VOL_LB, (UINT32)&ltn[i++]);
	SetCtrlDataAddData2(ctrl_data, loops,
		IDC_SYSTEM_CONFIG_SPEED_LB, (UINT32)&ltn[i++]);
	SetCtrlDataAddData2(ctrl_data, loops,
		IDC_SYSTEM_CONFIG_SPLINE_LB, (UINT32)&ltn[i++]);		
	i = 0;
	SetCtrlDataAddData2(ctrl_data, loops,
		IDC_SYSTEM_CONFIG_ALM_FHR_HI_SB, (UINT32)&snb[i++]);
	SetCtrlDataAddData2(ctrl_data, loops,
		IDC_SYSTEM_CONFIG_ALM_FHR_LO_SB, (UINT32)&snb[i++]);
	i = 0;
	SetCtrlDataAddData2(ctrl_data, loops,
		IDC_SYSTEM_CONFIG_SET_FM_B, (UINT32)&btn[i++]);
	SetCtrlDataAddData2(ctrl_data, loops,
		IDC_SYSTEM_CONFIG_PRINT_TEST_B, (UINT32)&btn[i++]);
	SetCtrlDataAddData2(ctrl_data, loops,
		IDC_SYSTEM_CONFIG_DEFAULT_B, (UINT32)&btn[i++]);
	SetCtrlDataAddData2(ctrl_data, loops,
		IDC_SYSTEM_CONFIG_SETUP_B, (UINT32)&btn[i++]);
	SetCtrlDataAddData2(ctrl_data, loops,
		IDC_SYSTEM_CONFIG_EXIT_B, (UINT32)&btn[i++]);

	DialogBoxIndirectParam(&dlg_data, parent, IDD_SYSTEM_CONFIG,
							SystemSetupProc, 0, &wndMem);
	return 0;
}

static INT32
	SystemInfoProc(HANDLE hWnd, INT32 message, DWORD wParam, LPARAM lParam)
{
	HWND hInfo = GetDlgItem(hWnd, IDC_SYSTEM_INFO_L);
	switch (message)
	{
		case MSG_INITDIALOG:
			if (hInfo)
			{
				SetWindowBkColor(hInfo, ((PCONTROL)hWnd)->iBkColor);
				SetWindowFont(hInfo, GetSystemFont(SYSLOGFONT_BIGFONT));
				SetWindowTextColor(hInfo, PIXEL_black);
			}
			break;

		case MSG_SHOWWINDOW:
			if (hInfo)
			{
				SetWindowText(hInfo, 0);
				HDC hdc = GetDC(hInfo);
				UCHAR info[32];
				INT32 offset = GetFontHeight(hdc) + 2;
				sprintf(info, "Version: %s", VERSION);
				SetTextColor(hdc, PIXEL_black);
				SetBkColor(hdc, ((PWIN)hWnd)->iBkColor);
				TextOut(hdc, 0, offset * 0, info);
				sprintf(info, "RunTime: %02d:%02d:%02d",
					MonitorInfo.SystemRunTime/ 3600,
					(MonitorInfo.SystemRunTime % 3600) / 60,
					MonitorInfo.SystemRunTime % 60);
				TextOut(hdc, 0, offset * 1, info);
				ReleaseDC(hdc);
			}
			break;
		
		case MSG_COMMAND:
			if (IDC_SYSTEM_INFO_EXIT_B == LOWORD(wParam))
			{
				EndDialog(hWnd, IDOK);
				return 0;
			}
			break;

		default:
			break;
	}
	
	return DefaultDialogProc (hWnd, message, wParam, lParam);
}

VOID SystemInfoDialog(HANDLE hOwner)
{
	DLGTEMPLATE dlg_data = {
		WS_ABSSCRPOS | WS_CAPTION | WS_BORDER | WS_MODALDLG, WS_NONE, 
		0, 0, 300, 150, STR_DLG_STATUS, 0, NULL, 0L	};

	CTRLDATA ctrl_data[]={ 
	{ CTRL_STATIC,  WS_VISIBLE | SS_SIMPLE,  WS_EX_NONE,
		DLG_OFFSET, DLG_OFFSET, 300 - DLG_OFFSET * 2, 100 - DLG_OFFSET * 2, 
		IDC_SYSTEM_INFO_L, STR_NULL, 0L, 0L }, 

	{ CTRL_BUTTON,  WS_VISIBLE | WS_TABSTOP | BS_ICON, WS_EX_NONE,
		300 - EXIT_ICON_WIDTH - 15, -35, EXIT_ICON_WIDTH, EXIT_ICON_HIGH, 
		IDC_SYSTEM_INFO_EXIT_B, 0, 0L, 0L }
	};
	BUTTONDATA btn = gBtn_Exit;
	INT16 i, loops;
	loops = TABLESIZE(ctrl_data);
	WNDMEM   wndMem;
	
	wndMem.pMainWin = GetMainWndMem(IDD_SYSTEM_INFORMATION);
	wndMem.pControl = GetCtrlWndMem(IDC_SYSTEM_INFO_FIRST);
	wndMem.ctrlNum  = TABLESIZE(ctrl_data);
	wndMem.task	 = SysGui_HTSK;

	dlg_data.controlnr = loops;
	dlg_data.controls  = ctrl_data;
	
	SetCtrlDataAddData2(ctrl_data, loops, IDC_SYSTEM_INFO_EXIT_B, (UINT32)&btn);
	DialogBoxIndirectParam(&dlg_data, hOwner, IDD_SYSTEM_INFORMATION,
							SystemInfoProc, 0, &wndMem);
}

static INT32 OnClickWavePageUp(HWND parent, HWND ctrl, LPARAM lParam)
{
	parent = parent;
	ctrl  = ctrl;
	lParam = lParam;
	WavePageUp();
	return 0;
}

static INT32 OnClickWavePageDown(HWND parent, HWND ctrl, LPARAM lParam)
{
	parent = parent;
	ctrl  = ctrl;
	lParam = lParam;
	WavePageDown();
	return 0;
}

static INT32 OnClickChangeFaceType(HWND parent, HWND ctrl, LPARAM lParam)
{
	parent = parent;
	ctrl  = ctrl;
	lParam = lParam;
	ChangeFaceType();
	return 0;
}

INT32 OnClickSystemSetupDialog(HWND parent, HWND ctrl, LPARAM lParam)
{
	parent = parent;
	ctrl  = ctrl;
	lParam = lParam;
	if ((HWND)GetTopWndItem(IDD_SYSTEM_CONFIG) == HWND_INVALID && _menu_lev <= 0)
		SystemSetupDialog(0);
	return 0;
}

INT32 OnClickAnalysisDialog(HWND parent, HWND ctrl, LPARAM lParam)
{
	parent = parent;
	ctrl  = ctrl;
	lParam = lParam;
	if ((HWND_INVALID == (HWND)GetTopWndItem(IDD_ANALY_SETUP))
		&& (_menu_lev <= 0))
	{
		AnalysisDialog(0);
	}
	return 0;
}

INT32 OnClickSystemInfo(HANDLE hOwner)
{
	if ((HWND_INVALID == (HWND)GetTopWndItem(IDD_ANALY_SETUP))
		&& (_menu_lev <= 0))
	{
		SystemInfoDialog(hOwner);
	}
}

INT32 OnClickFactoryMaintainDialog(HANDLE hOwner)
{
	if ((HWND_INVALID == (HWND)GetTopWndItem(IDD_FACTORY_MAINTAIN))
		&& (_menu_lev <= 0))
	{
		FactoryMaintainDialog(hOwner);
	}
}

BOOL CreateSysMenus(VOID)
{
	int i = 0;
#if DEBUG_MENU > 0
	CreateMenuGroupsCtrlGroup(i++,STR_WEEK_SUNDAY, WS_VISIBLE | SS_CENTER,
								0, 0, TestFunc1);
	CreateMenuGroupsCtrlGroup(i++,STR_WEEK_MONDAY, WS_VISIBLE | SS_CENTER,
								0, 0, TestFunc2);
	CreateMenuGroupsCtrlGroup(i++,STR_WEEK_TUESDAY, WS_VISIBLE | SS_CENTER,
								0, 0, TestFunc3);
	CreateMenuGroupsCtrlGroup(i++,STR_WEEK_WEDNESDAY, WS_VISIBLE | SS_CENTER,
								0, 0, TestFunc4);
#endif
	INT8 night = MonitorConfig.nightModeOn;
//	CreateMenuGroupsCtrlGroup (i++, 0, WS_VISIBLE | SS_BITMAP,
//					(DWORD)pageup_24bmp[night], 0L, OnClickWavePageUp);
//	CreateMenuGroupsCtrlGroup (i++, 0, WS_VISIBLE | SS_BITMAP,
//					(DWORD)pagedn_24bmp[night], 0L, OnClickWavePageDown);
	CreateMenuGroupsCtrlGroup (i++, 0, WS_VISIBLE | SS_BITMAP,
					(DWORD)face_24bmp[night],   0L, OnClickChangeFaceType);
	CreateMenuGroupsCtrlGroup (i++, 0, WS_VISIBLE | SS_BITMAP,
					(DWORD)syscfg_24bmp[night], 0L, OnClickSystemSetupDialog);
}

