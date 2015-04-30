
#define MAINTAIN_GLOBALS
#include "includes.h"

STRINGID str_language[MAX_LANGUAGE] =
{
	STR_DLG_LANGUAGE_ENGLISH,
	STR_DLG_LANGUAGE_CHINESE,
	STR_DLG_LANGUAGE_RUSSIAN,
	STR_DLG_LANGUAGE_SPANISH,
	STR_DLG_LANGUAGE_TURKISH
};

STRINGID str_delimiter[] =
{
	STR_DLG_DATE_DELIMITER1,
	STR_DLG_DATE_DELIMITER2,
	STR_DLG_DATE_DELIMITER3
};

STRINGID str_dateformat[] =
{
	STR_DLG_DATE_FORMAT_YMD,
	STR_DLG_DATE_FORMAT_MDY,
	STR_DLG_DATE_FORMAT_DMY
};

STRINGID str_timeformat[] =
{
	STR_DLG_DATE_FORMAT_HMS,
	STR_DLG_DATE_FORMAT_HM,
	STR_DLG_DATE_FORMAT_THMS,
	STR_DLG_DATE_FORMAT_THM
};

STRINGID str_monitor_name[] = {
	STR_DLG_FACTORY_ARTEMIS4S,
	STR_DLG_FACTORY_ARTEMIS2
};

STRINGID str_recorder_type[] = {
	STR_DLG_FACTORY_REC_112,
	STR_DLG_FACTORY_REC_150
};

INT16 GetUsefulLanguage(STRINGID *id, INT16 *nr)
{
	char fileName[MAX_LANGUAGE][24] = 
		{	FPL_EN_US, FPL_ZH_CN, FPL_RU_RU, FPL_ES_ES, FPL_TR_TR	};
	int i;
	INT16 ret = 0;
	INT16 num = 0;
	for (i = 0; i < MAX_LANGUAGE; i++)
	{
		if (CheckFileExist(fileName[i]))
		{
			if (i == MonitorConfig.language)
				ret = num;
			id[num++] = STR_DLG_LANGUAGE_ENGLISH + i;
		}
	}
	*nr = num;
	return ret;
}

static INT16 sMapLanguage(INT16 choice)
{
	INT16 i;
	for (i = 0; i < MAX_LANGUAGE; i++)
	{
		if (str_language[choice] == STR_DLG_LANGUAGE_ENGLISH + i)
			break;
	}
	return i;
}

BOOL LanguageSetupDLgOnCommand(HWND hWnd, WPARAM wParam, LPARAM lParam)
{
	int ret = TRUE;
	static char LanChangeFlag = FALSE;
	INT16 choice = -1;
	switch (LOWORD(wParam))
	{
		case IDC_LANGUAGE_CHOICE_LB:
			if (HIWORD(wParam) == LBN_CHANGED || HIWORD(wParam) == LBN_ENTER)
			{
				choice = MonitorConfig.language;
				if (HIWORD(wParam) == LBN_CHANGED)
				{

					choice = GetListBoxCurChoi(IDD_SETUP_LANGUAGE,
						IDC_LANGUAGE_CHOICE_LB);
					choice = sMapLanguage(choice);
				}
				if (HIWORD(wParam) == LBN_ENTER)
				{
				
					choice = OnTouchListbox(hWnd, IDD_SETUP_LANGUAGE,
						IDC_LANGUAGE_CHOICE_LB, STR_DLG_LANGUAGE_CHOICE);
               						
					choice = sMapLanguage(choice);
				}
				if (choice != MonitorConfig.language && choice < MAX_LANGUAGE)
				{

					LanChangeFlag = TRUE;
					MonitorConfig.language = choice;
				}

			}
			//SetFetalDetach(FhrConfig.detach);
			//ReDrawFetalWave(FetalWavePrint);
			break;

		case IDC_LANGUAGE_DATEFORMAT_LB:
			if (HIWORD(wParam) == LBN_CHANGED || HIWORD(wParam) == LBN_ENTER)
			{
				choice = MonitorConfig.date_format_type;
				if (HIWORD(wParam) == LBN_CHANGED)
				{
					choice = GetListBoxCurChoi(IDD_SETUP_LANGUAGE,
						IDC_LANGUAGE_DATEFORMAT_LB);
				}
				if (HIWORD(wParam) == LBN_ENTER)
				{
					choice = OnTouchListbox(hWnd, IDD_SETUP_LANGUAGE,
						IDC_LANGUAGE_DATEFORMAT_LB, STR_DLG_DATE_FORMAT);
				}
				if (MonitorConfig.date_format_type != choice)
				{
					MonitorConfig.date_format_type = choice;
					Save_Config(CFG_KEYID_DATETIME_FORMAT);
				}
			}
			break;

		case IDC_LANGUAGE_DATE_DELIMITER_LB:
			if (HIWORD(wParam) == LBN_CHANGED || HIWORD(wParam) == LBN_ENTER)
			{
				if (HIWORD(wParam) == LBN_CHANGED)
				{
					choice = GetListBoxCurChoi(IDD_SETUP_LANGUAGE,
						IDC_LANGUAGE_DATE_DELIMITER_LB);
				}
				if (HIWORD(wParam) == LBN_ENTER)
				{
					choice = OnTouchListbox(hWnd, IDD_SETUP_LANGUAGE,
						IDC_LANGUAGE_DATE_DELIMITER_LB, STR_DLG_DATE_DELIMITER);
				}
				char *deli = LoadString(str_delimiter[choice]);
				if (MonitorConfig.date_delimiter != *deli)
				{
					MonitorConfig.date_delimiter = *deli;
					Save_Config(CFG_KEYID_DATETIME_FORMAT);
				}
			}
			break;

		case IDC_LANGUAGE_TIMEFORMAT_LB:
			if (HIWORD(wParam) == LBN_CHANGED || HIWORD(wParam) == LBN_ENTER)
			{
				choice = MonitorConfig.time_format_type - FORMAT_HH_MM_SS;
				if (HIWORD(wParam) == LBN_CHANGED)
				{
					choice = GetListBoxCurChoi(IDD_SETUP_LANGUAGE,
						IDC_LANGUAGE_TIMEFORMAT_LB);
				}
				if (HIWORD(wParam) == LBN_ENTER)
				{
					choice = OnTouchListbox(hWnd, IDD_SETUP_LANGUAGE,
						IDC_LANGUAGE_TIMEFORMAT_LB, STR_DLG_TIME_FORMAT);
				}
				choice += FORMAT_HH_MM_SS;
				if (MonitorConfig.time_format_type != choice)
				{
					MonitorConfig.time_format_type = choice;
					Save_Config(CFG_KEYID_DATETIME_FORMAT);
				}
			}
			break;

		case IDC_LANGUAGE_EXIT_B:
			if (LanChangeFlag)
			{
				LanChangeFlag = FALSE;
//				ChoiceFont(MonitorConfig.language);
				PostMessage(SysGui_HTSK, MSG_GUI_LANG_CHANGE,
					MonitorConfig.language, 0);
				// 保存设置
				Save_Config(CFG_KEYID_LANGUAGE);
				ReInitGlobalStrPtr(MonitorConfig.language);
				SetFetalDetach(FhrConfig.detach);
				ShowPatinetInfo();
				StartLayoutSession();
				AlmGlbCtlr.LanChange = TRUE;
			}
			else
			{
				EndDialog(hWnd, IDOK);
			}
			break;
	}
	return ret;
}

VOID LanguageSetupDlgInit(HWND hWnd)
{
	INT16 num;
	INT16 i;
	INT16 lan = GetUsefulLanguage(str_language, &num);
	SetListBoxString(IDD_SETUP_LANGUAGE, IDC_LANGUAGE_CHOICE_LB,
		str_language, num);
	SetListBoxCurChoi(IDD_SETUP_LANGUAGE, IDC_LANGUAGE_CHOICE_LB, lan);
//	printf("LanguageSetupDlgInit::num, lan %d, %d\n", num, lan);
	SetListBoxString(IDD_SETUP_LANGUAGE, IDC_LANGUAGE_DATEFORMAT_LB,
		str_dateformat, TABLESIZE(str_dateformat));
	SetListBoxCurChoi(IDD_SETUP_LANGUAGE, IDC_LANGUAGE_DATEFORMAT_LB,
		MonitorConfig.date_format_type);
//	printf("LanguageSetupDlgInit::MonitorConfig.date_format_type %d\n", MonitorConfig.date_format_type);
	SetListBoxString(IDD_SETUP_LANGUAGE, IDC_LANGUAGE_DATE_DELIMITER_LB,
		str_delimiter, TABLESIZE(str_delimiter));
	for (i = 0; i < TABLESIZE(str_delimiter); i++)
	{
		if (MonitorConfig.date_delimiter == *LoadString(str_delimiter[i]))
		{
			SetListBoxCurChoi(IDD_SETUP_LANGUAGE,
				IDC_LANGUAGE_DATE_DELIMITER_LB, i);
//			printf("LanguageSetupDlgInit::i %d\n", i);
			break;
		}
	}
	SetListBoxString(IDD_SETUP_LANGUAGE, IDC_LANGUAGE_TIMEFORMAT_LB,
		str_timeformat, TABLESIZE(str_timeformat));
	SetListBoxCurChoi(IDD_SETUP_LANGUAGE, IDC_LANGUAGE_TIMEFORMAT_LB,
		MonitorConfig.time_format_type - FORMAT_HH_MM_SS);

	if (SaveLanguageFile(MAX_LANGUAGE))
	{
//		printf("SaveLanguageFile successed\n");
	}
}

INT32 LanguageSetupProc(HWND hWnd, INT32 msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
		case MSG_INITDIALOG:
			LanguageSetupDlgInit(hWnd);
			break;
		
		case MSG_COMMAND:
			if (LanguageSetupDLgOnCommand(hWnd, wParam, lParam))
			{
				return 0;
			}
			break;

		default:
			break;
	}
	
	return DefaultDialogProc (hWnd, msg, wParam, lParam);
}

VOID LanguageSetupDialog(HANDLE hOwner)
{
	enum __tagDlgPos{
		DLG_COLUMN_W = 150,
		DLG_COLUMN1	= DLG_OFFSET,
		DLG_COLUMN2 = DLG_COLUMN1 + DLG_COLUMN_W + DLG_OFFSET,
		DLG_ROW1_Y = 5,
		DLG_ROW2_Y	= DLG_ROW1_Y + KEY_HEIGHT + DLG_OFFSET,
		DLG_ROW3_Y	= DLG_ROW2_Y + KEY_HEIGHT + DLG_OFFSET,
		DLG_ROW4_Y	= DLG_ROW3_Y + KEY_HEIGHT + DLG_OFFSET,
		DLG_HIGH = DLG_ROW4_Y + KEY_HEIGHT + DLG_MENU_HIGHT + DLG_OFFSET,
		DLG_WIDTH = DLG_OFFSET + (DLG_COLUMN_W + DLG_OFFSET) * 2,
	};
	DLGTEMPLATE dlg_data = {
	   WS_ABSSCRPOS | WS_CAPTION | WS_BORDER | WS_MODALDLG, WS_NONE, 
	   (SCREEN_WIDTH - DLG_WIDTH) / 2,
	   SCREEN_HIGH - BOTTOMBAR_HEIGHT - DLG_HIGH, DLG_WIDTH, DLG_HIGH,
	   STR_DLG_SYSSETUP_LANGUAGE, 0, NULL, 0L	};

	CTRLDATA ctrl_data[]={
		{
			CTRL_STATIC, WS_VISIBLE | SS_SIMPLE, WS_NONE,
			DLG_COLUMN1, DLG_ROW1_Y+5, DLG_COLUMN_W, STATIC_HEIGHT,
			IDC_LANGUAGE_CHOICE_L, STR_DLG_LANGUAGE_CHOICE, 0L, 0L
		},
		{
			CTRL_STATIC, WS_VISIBLE | SS_SIMPLE, WS_NONE,
			DLG_COLUMN1, DLG_ROW2_Y+5, DLG_COLUMN_W, STATIC_HEIGHT,
			IDC_LANGUAGE_DATEFORMAT_L, STR_DLG_DATE_FORMAT, 0L, 0L
		},
		{
			CTRL_STATIC, WS_VISIBLE | SS_SIMPLE, WS_NONE,
			DLG_COLUMN1, DLG_ROW3_Y+5, DLG_COLUMN_W, STATIC_HEIGHT,
			IDC_LANGUAGE_DATE_DELIMITER_L, STR_DLG_DATE_DELIMITER, 0L, 0L
		},
		{
			CTRL_STATIC, WS_VISIBLE | SS_SIMPLE, WS_NONE,
			DLG_COLUMN1, DLG_ROW4_Y+5, DLG_COLUMN_W, STATIC_HEIGHT,
			IDC_LANGUAGE_TIMEFORMAT_L, STR_DLG_TIME_FORMAT, 0L, 0L
		},
		{
			CTRL_LISTBOX, WS_VISIBLE | WS_TABSTOP, WS_NONE,
			DLG_COLUMN2, DLG_ROW1_Y, DLG_COLUMN_W, KEY_HEIGHT,
			IDC_LANGUAGE_CHOICE_LB, 0, 0L, 0L
		},
		{
			CTRL_LISTBOX, WS_VISIBLE | WS_TABSTOP, WS_NONE,
			DLG_COLUMN2, DLG_ROW2_Y, DLG_COLUMN_W, KEY_HEIGHT,
			IDC_LANGUAGE_DATEFORMAT_LB, 0, 0L, 0L
		},
		{
			CTRL_LISTBOX, WS_VISIBLE | WS_TABSTOP, WS_NONE,
			DLG_COLUMN2, DLG_ROW3_Y, DLG_COLUMN_W, KEY_HEIGHT,
			IDC_LANGUAGE_DATE_DELIMITER_LB, 0, 0L, 0L
		},
		{
			CTRL_LISTBOX, WS_VISIBLE | WS_TABSTOP, WS_NONE,
			DLG_COLUMN2, DLG_ROW4_Y, DLG_COLUMN_W, KEY_HEIGHT,
			IDC_LANGUAGE_TIMEFORMAT_LB, 0, 0L, 0L
		},
		{
			CTRL_BUTTON, WS_VISIBLE | WS_TABSTOP | BS_ICON, WS_NONE,
			DLG_WIDTH-EXIT_ICON_WIDTH - DLG_OFFSET,
			-(DLG_MENU_HIGHT + EXIT_ICON_HIGH) / 2,
			EXIT_ICON_WIDTH,  EXIT_ICON_HIGH,
			IDC_LANGUAGE_EXIT_B, 0, 0L, 0L
		}
	};
	static LISTBOXDATA lb[4] = {{0},{0},{0},{0}};

	int loops = TABLESIZE(ctrl_data);
	SetCtrlDataAddData2(ctrl_data, loops,
		IDC_LANGUAGE_CHOICE_LB, (UINT32)&lb[0]);
	SetCtrlDataAddData2(ctrl_data, loops,
		IDC_LANGUAGE_DATEFORMAT_LB, (UINT32)&lb[1]);
	SetCtrlDataAddData2(ctrl_data, loops,
		IDC_LANGUAGE_DATE_DELIMITER_LB, (UINT32)&lb[2]);
	SetCtrlDataAddData2(ctrl_data, loops,
		IDC_LANGUAGE_TIMEFORMAT_LB, (UINT32)&lb[3]);
	SetCtrlDataAddData2(ctrl_data, loops,
		IDC_LANGUAGE_EXIT_B, (UINT32)&gBtn_Exit);

	WNDMEM   wndMem;
	
	wndMem.pMainWin = GetMainWndMem(IDD_SETUP_LANGUAGE);
	wndMem.pControl = GetCtrlWndMem(IDC_LANGUAGE_FIRST);
	wndMem.ctrlNum  = TABLESIZE(ctrl_data);
	wndMem.task	 = SysGui_HTSK;

	dlg_data.controlnr = loops;
	dlg_data.controls  = ctrl_data;
	DialogBoxIndirectParam(&dlg_data, hOwner, IDD_SETUP_LANGUAGE,
							LanguageSetupProc, 0, &wndMem);
}

VOID SetMonitorName(int name)
{
	switch (name)
	{
		case MONITOR_TYPE_AR4S:
			MonitorConfig.MonitorName = MONITOR_TYPE_AR4S;
			MonitorConfig.RecorderType = PAPER_TYPE_112MM;
			MonitorConfig.UseTouch = FALSE;
        	MonitorInfo.deviceInfo[DEV_TOUCH].port = COM8; //artemis4
        	MonitorInfo.deviceInfo[DEV_REC].port = COM9;   //artemis4
			MonitorConfig.nightModeOn = TRUE;
			break;

		case MONITOR_TYPE_AR2:
			MonitorConfig.MonitorName = MONITOR_TYPE_AR2;
			MonitorConfig.RecorderType = PAPER_TYPE_112MM;//PAPER_TYPE_PT1561P;
			MonitorConfig.UseTouch = TRUE;
        	MonitorInfo.deviceInfo[DEV_TOUCH].port = COM9;  //artemis2
        	MonitorInfo.deviceInfo[DEV_REC].port = COM4;    //artemis2
			MonitorConfig.nightModeOn = FALSE;
			break;

		default:
			break;
	}
	Load_DefCfg_Recorder();
	Load_DefCfg_Touch();
	Save_Config(CFG_KEYID_MONITORTYPE);
	Save_Config(CFG_KEYID_PRINTERCOM);
	Save_Config(CFG_KEYID_NIGHTMODE);
	Save_Record_Config(0, TRUE);
	Save_Touch_Config(0);
	SetListBoxCurChoi(IDD_FACTORY_MAINTAIN,
		IDC_FACTORY_MAINTAIN_ENABLE_TOUCH_LB, MonitorConfig.UseTouch);
	INT16 choice = 2;
	switch (MonitorConfig.RecorderType)
	{
		case PAPER_TYPE_112MM:
			choice = 0;
			break;

		case PAPER_TYPE_PT1561P:
			choice = 1;
			break;

		default:
			break;
	}
	SetListBoxCurChoi(IDD_FACTORY_MAINTAIN,
		IDC_FACTORY_MAINTAIN_RECORDER_TYPE_LB, choice);
}


VOID SetAnalyFunctionStatus(HWND hWnd)
{
	HWND hCtrl = GetDlgItem(hWnd, IDC_FACTORY_MAINTAIN_ENBALALY_B);
	STRINGID strid = STR_DLG_FACTORY_ANALY_ENABLE;
	if (!get_analysis_enable())
		strid = STR_DLG_FACTORY_ANALY_DISABLE;
	if (hCtrl)
		SetWindowText(hCtrl, strid);
}

VOID FactoryMaintainDlgInit(HWND hWnd)
{
	HWND hCtrl;
	int i;
	for (i = IDC_FACTORY_MAINTAIN_FIRST; i <= IDC_FACTORY_MAINTAIN_VERSION_L; i++)
	{
		hCtrl = GetDlgItem(hWnd, i);
		if (hCtrl != 0)
		{
			SetWindowBkColor(hCtrl, ((PCONTROL)hWnd)->iBkColor);
			SetWindowFont(hCtrl, GetSystemFont(SYSLOGFONT_SMAFONT));
			SetWindowTextColor(hCtrl, PIXEL_black);
		}
	}

	char *txt = LoadString(STR_DLG_FACTORY_VERSION);
	if (*txt == 0)
	{
		sprintf(LoadString(STR_DLG_FACTORY_VERSION), "%s %s %s",
			__TIME__, __DATE__ , VERSION_SVN);
	}

	SetListBoxCurChoi(IDD_FACTORY_MAINTAIN,
		IDC_FACTORY_MAINTAIN_MONITOR_TYPE_NAME_LB,	MonitorConfig.MonitorName);
	SetListBoxCurChoi(IDD_FACTORY_MAINTAIN,
		IDC_FACTORY_MAINTAIN_ENABLE_TOUCH_LB,		MonitorConfig.UseTouch);
	switch (MonitorConfig.RecorderType)
	{
		case PAPER_TYPE_112MM:
			i = 0;
			break;

		case PAPER_TYPE_PT1561P:
			i = 1;
			break;

		default:
			i = 2;
			break;
	}
	SetListBoxCurChoi(IDD_FACTORY_MAINTAIN,
		IDC_FACTORY_MAINTAIN_RECORDER_TYPE_LB,		i);

	SetAnalyFunctionStatus(hWnd);
}

BOOL FactoryMaintainDlgOnCommand(HWND hWnd, WPARAM wParam)
{
	BOOL ret = TRUE;
	static INT8 RebootFlag = FALSE;
	switch (LOWORD(wParam))
	{
		case IDC_FACTORY_MAINTAIN_MONITOR_TYPE_NAME_LB:
			if (HIWORD(wParam) == LBN_CHANGED || HIWORD(wParam) == LBN_ENTER)
			{
				INT16 ret = (INT16)MonitorConfig.MonitorName;
				if (HIWORD(wParam) == LBN_CHANGED)
				{
					ret = GetListBoxCurChoi(IDD_FACTORY_MAINTAIN,
						LOWORD(wParam));
				}
				if (HIWORD(wParam) == LBN_ENTER)
				{
					ret = OnTouchListbox(hWnd, IDD_FACTORY_MAINTAIN,
						LOWORD(wParam), STR_DLG_FACTORY_MONITORTYPE);
				}
				if (ret == (INT16)MonitorConfig.MonitorName)
					break;
				SetMonitorName(ret);
				RebootFlag = TRUE;
			}
			break;

		case IDC_FACTORY_MAINTAIN_ENABLE_TOUCH_LB:
			if (HIWORD(wParam) == LBN_CHANGED || HIWORD(wParam) == LBN_ENTER)
			{
				INT16 ret = (INT16)MonitorConfig.UseTouch;
				if (HIWORD(wParam) == LBN_CHANGED)
				{
					ret = GetListBoxCurChoi(IDD_FACTORY_MAINTAIN,
						LOWORD(wParam));
				}
				if (HIWORD(wParam) == LBN_ENTER)
				{
					ret = OnTouchListbox(hWnd, IDD_FACTORY_MAINTAIN,
						LOWORD(wParam), STR_DLG_FACTORY_ENBTOUCH);
				}
				if (ret == (INT16)MonitorConfig.UseTouch)
					break;
				RebootFlag = TRUE;
				MonitorConfig.UseTouch = ret;
				Load_DefCfg_Touch();
				Save_Touch_Config(0);
			}
			break;

		case IDC_FACTORY_MAINTAIN_RECORDER_TYPE_LB:
			if (HIWORD(wParam) == LBN_CHANGED || HIWORD(wParam) == LBN_ENTER)
			{
				if (HIWORD(wParam) == LBN_CHANGED)
				{
					ret = GetListBoxCurChoi(IDD_FACTORY_MAINTAIN,
						LOWORD(wParam));
				}
				if (HIWORD(wParam) == LBN_ENTER)
				{
					ret = OnTouchListbox(hWnd, IDD_FACTORY_MAINTAIN,
						LOWORD(wParam), STR_DLG_FACTORY_RECORDERTYPE);
				}
				if (STR_DLG_FACTORY_REC_112 == str_recorder_type[ret])
				{
					ret = PAPER_TYPE_112MM;
				}
				else
				{
					ret = PAPER_TYPE_PT1561P;
				}
				if (ret == (INT16)MonitorConfig.RecorderType)
					break;
				RebootFlag = TRUE;
				MonitorConfig.RecorderType = ret;
				Load_DefCfg_Recorder();
				Save_Record_Config(0, TRUE);
			}
			break;

		case IDC_FACTORY_MAINTAIN_RECORDER_SETUP_B:
			PrinterSetupDialog(hWnd);
			break;

		case IDC_FACTORY_MAINTAIN_UPDATE_B:
			EndDialog(hWnd, IDYES);
			BacktoMainScreen();
			break;

		case IDC_FACTORY_MAINTAIN_ENBALALY_B:
			if (IDOK == PasswordDialog(hWnd, 4, STR_DLG_ANALY_FUNC))
			{
				set_analysis_enable(!get_analysis_enable());
				SetAnalyFunctionStatus(hWnd);
			}
			break;

		case IDC_FACTORY_MAINTAIN_EXIT_B:
			if (TRUE == RebootFlag)
			{
				SysPowerOff();
				//#if _ENB_WATCHDOG < 1
				system("reboot");
				//#endif
			}
			EndDialog(hWnd, IDOK);
			break;

		default:
			break;
	}
	return ret;
}

INT32 FactoryMaintainDlgProc(HWND hWnd, INT32 msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
		case MSG_INITDIALOG:
			FactoryMaintainDlgInit(hWnd);
			break;

		case MSG_COMMAND:
			if (FactoryMaintainDlgOnCommand(hWnd, wParam))
				return 0;
			break;

		default:
			break;
	}
	return DefaultDialogProc (hWnd, msg, wParam, lParam);
}


VOID FactoryMaintainDialog(HANDLE hOwner)
{
	if (IDOK != PasswordDialog(hOwner, 3, 0))
	{
		return;
	}
	enum __dialog_size
	{
		DLG_COLUMN1_W	= 100,
		DLG_COLUMN2_W	= 120,
		DLG_COLUMN3_W	= DLG_COLUMN1_W + DLG_COLUMN2_W + DLG_OFFSET,
		DLG_COLUMN1_X	= DLG_OFFSET,
		DLG_COLUMN2_X	= DLG_COLUMN1_X + DLG_COLUMN1_W + DLG_OFFSET,
		DLG_COLUMN3_X	= DLG_COLUMN1_X,
		DLG_ROW1_Y	= DLG_OFFSET + CTRL_HEIGHT * 0,
		DLG_ROW2_Y	= DLG_OFFSET + CTRL_HEIGHT * 1,
		DLG_ROW3_Y	= DLG_OFFSET + CTRL_HEIGHT * 2,
		DLG_ROW4_Y	= DLG_OFFSET + CTRL_HEIGHT * 3,
		DLG_ROW5_Y	= DLG_OFFSET + CTRL_HEIGHT * 4,
		DLG_ROW6_Y	= DLG_OFFSET + CTRL_HEIGHT * 5,
		DLG_ROW7_Y	= DLG_OFFSET + CTRL_HEIGHT * 6,
		DLG_ROW_END	= DLG_ROW7_Y + CTRL_HEIGHT,
		LABEL_OFFSET= (KEY_HEIGHT - 12) / 2,
		DLG_HIGH	= DLG_MENU_HIGHT + DLG_ROW_END,
		DLG_WIDTH	= DLG_COLUMN3_W + DLG_OFFSET * 2
	}DLG_SIZE;

	DLGTEMPLATE dlg_data = {
	   WS_ABSSCRPOS | WS_CAPTION | WS_BORDER | WS_MODALDLG, WS_NONE, 
	   (SCREEN_WIDTH - DLG_WIDTH) / 2,
	   SCREEN_HIGH - BOTTOMBAR_HEIGHT - DLG_HIGH, DLG_WIDTH, DLG_HIGH,
	   STR_DLG_FACTORY_MAINTAIN, 0, NULL, 0L };

	CTRLDATA ctrl_data[]={ 
		{ CTRL_STATIC,	WS_VISIBLE | SS_SIMPLE,  WS_EX_NONE,
			DLG_COLUMN1_X, DLG_ROW1_Y + LABEL_OFFSET, DLG_COLUMN1_W, KEY_HEIGHT, 
			IDC_FACTORY_MAINTAIN_MONITOR_TYPE_NAME_L,
			STR_DLG_FACTORY_MONITORTYPE, 0L, 0L }, 
		{ CTRL_LISTBOX, WS_VISIBLE | WS_TABSTOP, WS_EX_NONE,
			DLG_COLUMN2_X, DLG_ROW1_Y, DLG_COLUMN2_W, KEY_HEIGHT, 
			IDC_FACTORY_MAINTAIN_MONITOR_TYPE_NAME_LB, 0, 0, 0 },

		{ CTRL_STATIC,	WS_VISIBLE | SS_SIMPLE,  WS_EX_NONE,
			DLG_COLUMN1_X, DLG_ROW2_Y + LABEL_OFFSET, DLG_COLUMN1_W, KEY_HEIGHT, 
			IDC_FACTORY_MAINTAIN_ENABLE_TOUCH_L,
			STR_DLG_FACTORY_ENBTOUCH, 0L, 0L }, 
		{ CTRL_LISTBOX, WS_VISIBLE | WS_TABSTOP, WS_EX_NONE,
			DLG_COLUMN2_X, DLG_ROW2_Y, DLG_COLUMN2_W, KEY_HEIGHT, 
			IDC_FACTORY_MAINTAIN_ENABLE_TOUCH_LB, 0, 0, 0 },

		{ CTRL_STATIC,	WS_VISIBLE | SS_SIMPLE,  WS_EX_NONE,
			DLG_COLUMN1_X, DLG_ROW3_Y + LABEL_OFFSET, DLG_COLUMN1_W, KEY_HEIGHT, 
			IDC_FACTORY_MAINTAIN_RECORDER_TYPE_L,
			STR_DLG_FACTORY_RECORDERTYPE, 0L, 0L },
		{ CTRL_LISTBOX, WS_VISIBLE | WS_TABSTOP, WS_EX_NONE,
			DLG_COLUMN2_X, DLG_ROW3_Y, DLG_COLUMN2_W, KEY_HEIGHT, 
			IDC_FACTORY_MAINTAIN_RECORDER_TYPE_LB, 0, 0, 0 },

		{ CTRL_BUTTON, WS_VISIBLE | WS_TABSTOP, WS_EX_NONE,
			DLG_COLUMN3_X, DLG_ROW4_Y, DLG_COLUMN3_W, KEY_HEIGHT,
			IDC_FACTORY_MAINTAIN_RECORDER_SETUP_B,
			STR_DLG_FACTORY_REC_SETUP, 0, 0 },

		{ CTRL_BUTTON, WS_VISIBLE | WS_TABSTOP, WS_EX_NONE,
			DLG_COLUMN3_X, DLG_ROW5_Y, DLG_COLUMN3_W, KEY_HEIGHT,
			IDC_FACTORY_MAINTAIN_UPDATE_B,
			STR_DLG_FACTORY_UPDATE, 0, 0 },

		{ CTRL_BUTTON, WS_VISIBLE | WS_TABSTOP, WS_EX_NONE,
			DLG_COLUMN3_X, DLG_ROW6_Y, DLG_COLUMN3_W, KEY_HEIGHT,
			IDC_FACTORY_MAINTAIN_ENBALALY_B,
			STR_DLG_FACTORY_ANALY_ENABLE, 0, 0 },

		{ CTRL_STATIC,	WS_VISIBLE | SS_RIGHT,  WS_EX_NONE,
			DLG_COLUMN3_X, DLG_ROW7_Y + LABEL_OFFSET, DLG_COLUMN3_W, KEY_HEIGHT, 
			IDC_FACTORY_MAINTAIN_VERSION_L,
			STR_DLG_FACTORY_VERSION, 0L, 0L }, 

		{ CTRL_BUTTON,	WS_VISIBLE | WS_TABSTOP | BS_ICON, WS_EX_NONE,
			DLG_WIDTH - EXIT_ICON_WIDTH - 15,
			-(EXIT_ICON_HIGH + DLG_MENU_HIGHT) / 2,
			EXIT_ICON_WIDTH, EXIT_ICON_HIGH, 
			IDC_FACTORY_MAINTAIN_EXIT_B, 0, 0L, 0L }
	};
	
	static LISTBOXDATA lb_name =
		{ TABLESIZE(str_monitor_name), 0, TABLESIZE(str_monitor_name), 0, 0,
			str_monitor_name, 0, 0, 0, 0 };
	static LISTBOXDATA lb_touch =
		{ TABLESIZE(gOnOff), 0, TABLESIZE(gOnOff), 0, 0, gOnOff, 0, 0, 0, 0 };
	static LISTBOXDATA lb_type =
		{ TABLESIZE(str_recorder_type), 0, TABLESIZE(str_recorder_type), 0, 0,
			str_recorder_type, 0, 0, 0, 0 };
	
	static BUTTONDATA btn_setup = { 0 };
	static BUTTONDATA btn_update = { 0 };
	static BUTTONDATA btn_analy = { 0 };
	
	btn_setup.status = 0;
	btn_update.status = 0;
	gBtn_Exit.status = 0;
	
	int loops = TABLESIZE(ctrl_data);
	
	SetCtrlDataAddData2(ctrl_data, loops,
		IDC_FACTORY_MAINTAIN_MONITOR_TYPE_NAME_LB, (UINT32)&lb_name);
	SetCtrlDataAddData2(ctrl_data, loops,
		IDC_FACTORY_MAINTAIN_ENABLE_TOUCH_LB, (UINT32)&lb_touch);
	SetCtrlDataAddData2(ctrl_data, loops,
		IDC_FACTORY_MAINTAIN_RECORDER_TYPE_LB, (UINT32)&lb_type);
	SetCtrlDataAddData2(ctrl_data, loops,
		IDC_FACTORY_MAINTAIN_RECORDER_SETUP_B, (UINT32)&btn_setup);
	SetCtrlDataAddData2(ctrl_data, loops,
		IDC_FACTORY_MAINTAIN_UPDATE_B, (UINT32)&btn_update);
	SetCtrlDataAddData2(ctrl_data, loops,
		IDC_FACTORY_MAINTAIN_ENBALALY_B, (UINT32)&btn_analy);
	SetCtrlDataAddData2(ctrl_data, loops,
		IDC_FACTORY_MAINTAIN_EXIT_B, (UINT32)&gBtn_Exit);
	
	WNDMEM	 wndMem;
	
	wndMem.pMainWin = GetMainWndMem(IDD_FACTORY_MAINTAIN);
	wndMem.pControl = GetCtrlWndMem(IDC_FACTORY_MAINTAIN_FIRST);
	wndMem.ctrlNum	= TABLESIZE(ctrl_data);
	wndMem.task  = SysGui_HTSK;
	
	dlg_data.controlnr = loops;
	dlg_data.controls  = ctrl_data;

	INT32 ret = DialogBoxIndirectParam(&dlg_data, hOwner, IDD_FACTORY_MAINTAIN,
							FactoryMaintainDlgProc, 0, &wndMem);
	if (ret == IDYES)
	{
		EnterStandby();
		UsbUpdateProc();
	}
}

INT32  AboutDlgProc(HWND hWnd, INT32 msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
		case MSG_INITDIALOG:
		{
			HWND hCtrl;
			int i;
			for (i = IDC_ABOUT_FIRST; i < IDC_ABOUT_EXIT_B; i++)
			{
				hCtrl = GetDlgItem(hWnd, i);
				if (hCtrl != 0)
				{
					SetWindowBkColor(hCtrl, ((PCONTROL)hWnd)->iBkColor);
					SetWindowFont(hCtrl, GetSystemFont(SYSLOGFONT_BIGFONT));
					SetWindowTextColor(hCtrl, PIXEL_black);
				}
			}
			//更改厂家名称为机器编号
			char tmp[11];
			snprintf(tmp, sizeof(tmp), "%010u", GetMachineNumber());
			char *txt = LoadString(STR_DLG_ABOUT_COMPANY);
			sprintf(txt, "NO. %c%c%c-%c%c%c-%s", tmp[0], tmp[1], tmp[2],
				tmp[3], tmp[4], tmp[5], &tmp[6]);
			
		}
			break;

		case MSG_SHOWWINDOW:
		{
			HWND hCtrl;
			PCONTROL pCtrl;
			CHAR *txt;
			hCtrl = GetDlgItem(hWnd, IDC_ABOUT_START_TIME_L);
			if (hCtrl != 0)
			{
				pCtrl = (PCONTROL)hCtrl;
				txt = LoadString(pCtrl->caption);
				printf("MonitorInfo.SystemRunTime...%ld\n", MonitorInfo.SystemRunTime);
				if (MonitorInfo.SystemRunTime < 36000000)
				{
					sprintf(txt, "%d:%02d:%02d",
						MonitorInfo.SystemRunTime/ 3600,
						(MonitorInfo.SystemRunTime % 3600) / 60,
						MonitorInfo.SystemRunTime % 60);
				}
				else
				{
					strcpy(txt, "9999:59:59");
				}
				SetWindowText(hCtrl, pCtrl->caption);
			}
			hCtrl = GetDlgItem(hWnd, IDC_ABOUT_VERSION_NUMBER_L);
			if (hCtrl != 0)
			{
				pCtrl = (PCONTROL)hCtrl;
				txt = LoadString(pCtrl->caption);
				strcpy(txt, VERSION);
				SetWindowText(hCtrl, pCtrl->caption);
			}
			hCtrl = GetDlgItem(hWnd, IDC_ABOUT_COMPILE_DATE_L);
			if (hCtrl != 0)
			{
				pCtrl = (PCONTROL)hCtrl;
				txt = LoadString(pCtrl->caption);
				DATETIME *dt = GetCompileDateTime();
				FormatDateString(dt, txt);
				SetWindowText(hCtrl, pCtrl->caption);
			}
		}
			break;

		case MSG_COMMAND:
			// press any key to exit!
			EndDialog(hWnd, IDOK);
			return 0;

		default:
			break;
	}
	return DefaultDialogProc (hWnd, msg, wParam, lParam);
}

VOID AboutDialog(HANDLE hOwner)
{
	DLGTEMPLATE dlg_data = {
		.dwStyle	= WS_ABSSCRPOS | WS_CAPTION | WS_BORDER | WS_MODALDLG,
		.dwExStyle	= WS_NONE,
		.x			= (SCREEN_WIDTH - 300) / 2,
		.y			= SCREEN_HIGH - BOTTOMBAR_HEIGHT - 200,
		.w			= 300,
		.h			= 200,
		.caption	= STR_DLG_ABOUT,
		.controlnr	= 0,
		.controls	= NULL,
		.dwAddData	= 0L,
	};
	/* 
	DLGTEMPLATE dlg_data = {
	   WS_ABSSCRPOS | WS_CAPTION | WS_BORDER | WS_MODALDLG, WS_NONE, 
	   (SCREEN_WIDTH - 300) / 2,
	   SCREEN_HIGH - BOTTOMBAR_HEIGHT - 200, 300, 200,
	   STR_DLG_ABOUT, 0, NULL, 0L	};
   */

   
   CTRLDATA ctrl_data[]={ 
	   { CTRL_STATIC,  WS_VISIBLE | SS_SIMPLE,	WS_EX_NONE,
		   DLG_OFFSET, DLG_OFFSET, 200 - DLG_OFFSET * 2, STATIC_HEIGHT, 
		   IDC_ABOUT_TIME_L, STR_DLG_ABOUT_TIME, 0L, 0L }, 
	   { CTRL_STATIC,  WS_VISIBLE | SS_SIMPLE,	WS_EX_NONE,
		   200, DLG_OFFSET, 300 - DLG_OFFSET - 200, STATIC_HEIGHT, 
		   IDC_ABOUT_START_TIME_L, STR_DLG_ABOUT_START, 0L, 0L }, 

	   { CTRL_STATIC,  WS_VISIBLE | SS_SIMPLE,	WS_EX_NONE,
		   DLG_OFFSET, DLG_OFFSET + KEY_HEIGHT,
		   200 - DLG_OFFSET * 2, STATIC_HEIGHT, 
		   IDC_ABOUT_VERSION_L, STR_DLG_ABOUT_VERSION, 0L, 0L }, 
	   { CTRL_STATIC,  WS_VISIBLE | SS_SIMPLE,	WS_EX_NONE,
		   200, DLG_OFFSET + KEY_HEIGHT,
		   300 - DLG_OFFSET - 200, STATIC_HEIGHT, 
		   IDC_ABOUT_VERSION_NUMBER_L, STR_DLG_ABOUT_VERSION_NUM, 0L, 0L }, 

	   { CTRL_STATIC,  WS_VISIBLE | SS_SIMPLE,	WS_EX_NONE,
		   DLG_OFFSET, DLG_OFFSET + KEY_HEIGHT * 2,
		   200 - DLG_OFFSET * 2, STATIC_HEIGHT, 
		   IDC_ABOUT_COMPILE_TIME_L, STR_DLG_ABOUT_COMPILE_TIME, 0L, 0L }, 
	   { CTRL_STATIC,  WS_VISIBLE | SS_SIMPLE,	WS_EX_NONE,
		   200, DLG_OFFSET + KEY_HEIGHT * 2,
		   300 - DLG_OFFSET - 200, STATIC_HEIGHT, 
		   IDC_ABOUT_COMPILE_DATE_L, STR_DLG_ABOUT_COMPILE_DATE, 0L, 0L }, 

	   { CTRL_STATIC,  WS_VISIBLE | SS_SIMPLE,	WS_EX_NONE,
		   DLG_OFFSET, DLG_OFFSET + KEY_HEIGHT * 3,
		   300 - DLG_OFFSET * 2, STATIC_HEIGHT, 
		   IDC_ABOUT_COMPANY_L, STR_DLG_ABOUT_COMPANY, 0L, 0L }, 
   
	   { CTRL_BUTTON,  WS_VISIBLE | WS_TABSTOP | BS_ICON, WS_EX_NONE,
		   300 - EXIT_ICON_WIDTH - 15, -35, EXIT_ICON_WIDTH, EXIT_ICON_HIGH, 
		   IDC_ABOUT_EXIT_B, 0, 0L, 0L }
   };
   BUTTONDATA btn = gBtn_Exit;
   INT16 loops;
   loops = TABLESIZE(ctrl_data);
   WNDMEM	wndMem;
   
   wndMem.pMainWin = GetMainWndMem(IDD_ABOUT_DIALOG);
   wndMem.pControl = GetCtrlWndMem(IDC_ABOUT_FIRST);
   wndMem.ctrlNum  = TABLESIZE(ctrl_data);
   wndMem.task	= SysGui_HTSK;
   
   dlg_data.controlnr = loops;
   dlg_data.controls  = ctrl_data;
   
   SetCtrlDataAddData2(ctrl_data, loops, IDC_ABOUT_EXIT_B, (UINT32)&btn);
   DialogBoxIndirectParam(&dlg_data, hOwner, IDD_ABOUT_DIALOG,
						   AboutDlgProc, 0, &wndMem);
}


VOID SetMaintainDialogStatus(HWND hWnd)
{
	HWND hCtrl;
	if (0 != (hCtrl = GetDlgItem(hWnd, IDC_MAINTAIN_NIGHTMODE_B)))
	{
		if (MonitorConfig.nightModeOn)
		{
			SetWindowText(hCtrl, STR_DLG_EXIT_NIGHT_MODE);
		}
		else
		{
			SetWindowText(hCtrl, STR_DLG_NIGHT_MODE);
		}
		if (MonitorInfo.inDemo)
		{
			EnableWindow(hCtrl, FALSE);
		}
	}
	if (0 != (hCtrl = GetDlgItem(hWnd, IDC_MAINTAIN_HELPINFO_B)))
	{
		if (MonitorConfig.showHelp)
		{			
			SetWindowText(hCtrl, STR_DISABLE_HELP_STRING);
		}
		else
		{			
			SetWindowText(hCtrl, STR_ENABLE_HELP_STRING);
		}
		if (MonitorInfo.inDemo)
		{
			EnableWindow(hCtrl, FALSE);
		}
	}
	if (0 != (hCtrl = GetDlgItem(hWnd, IDC_MAINTAIN_DEMO_B)))
	{
		if (MonitorInfo.inDemo)
		{
			SetWindowText(hCtrl, STR_DLG_SETUP_DEMO_EXIT);
		}
		else
		{
			SetWindowText(hCtrl, STR_DLG_SETUP_DEMO);
		}
	}
	if (0 != (hCtrl = GetDlgItem(hWnd, IDC_MAINTAIN_NETWORK_B)))
	{
		if (MonitorInfo.inDemo)
		{
			EnableWindow(hCtrl, FALSE);
		}
	}
	if (0 != (hCtrl = GetDlgItem(hWnd, IDC_MAINTAIN_LANGUAGE_B)))
	{
		if (MonitorInfo.inDemo)
		{
			EnableWindow(hCtrl, FALSE);
		}
	}
}

VOID MaintainDlgInit(HWND hWnd, WPARAM wParam, LPARAM lParam)
{
	SetMaintainDialogStatus(hWnd);
}

BOOL MaintainDLgOnCommand(HWND hWnd, WPARAM wParam, LPARAM lParam)
{
	
	BOOL ret;
	ret = TRUE;
	switch(LOWORD(wParam))
	{
		case IDC_MAINTAIN_EXIT_B:
			EndDialog(hWnd, IDOK);
			break;
			
		case IDC_MAINTAIN_DEMO_B:
			if (MonitorInfo.inDemo == FALSE)
			{
				if (IDOK == PasswordDialog(hWnd, 1, 0))
				{
					EnterDemo();
					HWND hCtrl = GetDlgItem(hWnd, IDC_MAINTAIN_DEMO_B);
					if (hCtrl)
						SetWindowText(hCtrl, STR_DLG_SETUP_DEMO_EXIT);
				}
			}
			else
			{
				ExitDemo();
				HWND hCtrl = GetDlgItem(hWnd, IDC_MAINTAIN_DEMO_B);
				if (hCtrl)
					SetWindowText(hCtrl, STR_DLG_SETUP_DEMO);
			}
			BacktoMainScreen();
		break;

		case IDC_MAINTAIN_ABOUT_B:
			AboutDialog(hWnd);
			break;

		case IDC_MAINTAIN_FACTORY_B:
			FactoryMaintainDialog(hWnd);
			break;

		case IDC_MAINTAIN_NETWORK_B:
			NetworkSetupDialog(hWnd);
			break;

		case IDC_MAINTAIN_HELPINFO_B:
			MonitorConfig.showHelp = !MonitorConfig.showHelp;
			Save_Config(CFG_KEYID_HELPINFO);
			BacktoMainScreen();
			StartLayoutSession();
			break;

		case IDC_MAINTAIN_NIGHTMODE_B:
			MonitorConfig.nightModeOn = !MonitorConfig.nightModeOn;
			Save_Config(CFG_KEYID_NIGHTMODE);
			ReInitFhrGphMem(!MonitorConfig.nightModeOn);
			if (MonitorInfo.inDemo) SetFetalMonitorDemoStyle(TRUE);
			BacktoMainScreen();
			StartLayoutSession();
			break;

		case IDC_MAINTAIN_LANGUAGE_B:
			LanguageSetupDialog(hWnd);
			break;
	}
	return ret;
}

INT32 MaintainProc(HWND hWnd, INT32 msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
		case MSG_INITDIALOG:
			MaintainDlgInit(hWnd, wParam, lParam);
			break;
		
		case MSG_COMMAND:
			if (MaintainDLgOnCommand(hWnd, wParam, lParam))
			{
				return 0;
			}
			break;

		default:
			break;
	}
	
	return DefaultDialogProc (hWnd, msg, wParam, lParam);
}


VOID  MaintainDialog (HANDLE hOwner)
{
	enum __tagDlgPos{
		DLG_COLUMN_W = 190+20,
		DLG_ROW1_Y = 5,
		DLG_ROW2_Y	= DLG_ROW1_Y + KEY_HEIGHT + DLG_OFFSET,
		DLG_ROW3_Y	= DLG_ROW2_Y + KEY_HEIGHT + DLG_OFFSET,
		DLG_ROW4_Y	= DLG_ROW3_Y + KEY_HEIGHT + DLG_OFFSET,
		DLG_ROW5_Y	= DLG_ROW4_Y + KEY_HEIGHT + DLG_OFFSET,
		DLG_ROW6_Y	= DLG_ROW5_Y + KEY_HEIGHT + DLG_OFFSET,
		DLG_ROW7_Y	= DLG_ROW6_Y + KEY_HEIGHT + DLG_OFFSET,
		DLG_HIGH = DLG_ROW7_Y + KEY_HEIGHT + DLG_MENU_HIGHT + DLG_OFFSET,
		DLG_WIDTH = DLG_OFFSET + DLG_COLUMN_W + DLG_OFFSET,
	};
	DLGTEMPLATE dlg_data = {
	   WS_ABSSCRPOS | WS_CAPTION | WS_BORDER | WS_MODALDLG, WS_NONE, 
	   (SCREEN_WIDTH - DLG_WIDTH) / 2,
	   SCREEN_HIGH - BOTTOMBAR_HEIGHT - DLG_HIGH, DLG_WIDTH, DLG_HIGH,
	   STR_DLG_SYSSETUP, 0, NULL, 0L	};

	BUTTONDATA btn[IDC_MAINTAIN_EXIT_B - IDC_MAINTAIN_FIRST + 1] =
		{ {0}, {0}, {0}, {0}, {0}, {0}, {0}, gBtn_Exit};


	CTRLDATA ctrl_data[IDC_MAINTAIN_EXIT_B - IDC_MAINTAIN_FIRST + 1]={
		{CTRL_BUTTON, WS_VISIBLE | WS_TABSTOP, WS_EX_NONE,
			DLG_OFFSET, DLG_ROW1_Y, DLG_COLUMN_W, KEY_HEIGHT,
			IDC_MAINTAIN_NIGHTMODE_B, STR_DLG_NIGHT_MODE, 0, 0 },

		{CTRL_BUTTON, WS_VISIBLE | WS_TABSTOP, WS_EX_NONE,
			DLG_OFFSET, DLG_ROW2_Y, DLG_COLUMN_W, KEY_HEIGHT,
			IDC_MAINTAIN_HELPINFO_B, STR_ENABLE_HELP_STRING, 0, 0 },

		{CTRL_BUTTON, WS_VISIBLE | WS_TABSTOP, WS_EX_NONE,
			DLG_OFFSET, DLG_ROW3_Y, DLG_COLUMN_W, KEY_HEIGHT,
			IDC_MAINTAIN_NETWORK_B, STR_DLG_SETUP_NETWORK_B, 0, 0 },

		{CTRL_BUTTON, WS_VISIBLE | WS_TABSTOP, WS_EX_NONE,
			DLG_OFFSET, DLG_ROW4_Y, DLG_COLUMN_W, KEY_HEIGHT,
			IDC_MAINTAIN_LANGUAGE_B, STR_DLG_SYSSETUP_LANGUAGE_B, 0, 0 },

		{CTRL_BUTTON, WS_VISIBLE | WS_TABSTOP, WS_EX_NONE,
			DLG_OFFSET, DLG_ROW5_Y, DLG_COLUMN_W, KEY_HEIGHT,
			IDC_MAINTAIN_FACTORY_B, STR_DLG_FACTORY_MAINTAIN_B, 0, 0 },

		{CTRL_BUTTON, WS_VISIBLE | WS_TABSTOP, WS_EX_NONE,
			DLG_OFFSET, DLG_ROW6_Y, DLG_COLUMN_W, KEY_HEIGHT,
			IDC_MAINTAIN_ABOUT_B, STR_DLG_ABOUT_B, 0, 0 },

		{CTRL_BUTTON, WS_VISIBLE | WS_TABSTOP, WS_EX_NONE,
			DLG_OFFSET, DLG_ROW7_Y, DLG_COLUMN_W, KEY_HEIGHT,
			IDC_MAINTAIN_DEMO_B, STR_DLG_SETUP_DEMO, 0, 0 },

		{CTRL_BUTTON, WS_VISIBLE | WS_TABSTOP | BS_ICON, WS_EX_NONE,
			DLG_WIDTH-EXIT_ICON_WIDTH - DLG_OFFSET,
			-(DLG_MENU_HIGHT + EXIT_ICON_HIGH) / 2,
			EXIT_ICON_WIDTH,  EXIT_ICON_HIGH,
			IDC_MAINTAIN_EXIT_B, STR_DLG_EXIT, 0, 0 }
	};
	int loops = TABLESIZE(ctrl_data);
	WNDMEM   wndMem;
	
	wndMem.pMainWin = GetMainWndMem(IDD_MAINTAIN_DIALOG);
	wndMem.pControl = GetCtrlWndMem(IDC_MAINTAIN_FIRST);
	wndMem.ctrlNum  = TABLESIZE(ctrl_data);
	wndMem.task	 = SysGui_HTSK;

	dlg_data.controlnr = loops;
	dlg_data.controls  = ctrl_data;

	SetCtrlDataAddData2(ctrl_data, loops, IDC_MAINTAIN_NIGHTMODE_B,
		(UINT32)&btn[IDC_MAINTAIN_NIGHTMODE_B	- IDC_MAINTAIN_FIRST]);
	SetCtrlDataAddData2(ctrl_data, loops, IDC_MAINTAIN_HELPINFO_B,
		(UINT32)&btn[IDC_MAINTAIN_HELPINFO_B	- IDC_MAINTAIN_FIRST]);
	SetCtrlDataAddData2(ctrl_data, loops, IDC_MAINTAIN_NETWORK_B,
		(UINT32)&btn[IDC_MAINTAIN_NETWORK_B		- IDC_MAINTAIN_FIRST]);
	SetCtrlDataAddData2(ctrl_data, loops, IDC_MAINTAIN_LANGUAGE_B,
		(UINT32)&btn[IDC_MAINTAIN_LANGUAGE_B	- IDC_MAINTAIN_FIRST]);
	SetCtrlDataAddData2(ctrl_data, loops, IDC_MAINTAIN_FACTORY_B,
		(UINT32)&btn[IDC_MAINTAIN_FACTORY_B		- IDC_MAINTAIN_FIRST]);
	SetCtrlDataAddData2(ctrl_data, loops, IDC_MAINTAIN_ABOUT_B,
		(UINT32)&btn[IDC_MAINTAIN_ABOUT_B		- IDC_MAINTAIN_FIRST]);
	SetCtrlDataAddData2(ctrl_data, loops, IDC_MAINTAIN_DEMO_B,
		(UINT32)&btn[IDC_MAINTAIN_DEMO_B		- IDC_MAINTAIN_FIRST]);
	SetCtrlDataAddData2(ctrl_data, loops, IDC_MAINTAIN_EXIT_B,
		(UINT32)&btn[IDC_MAINTAIN_EXIT_B		- IDC_MAINTAIN_FIRST]);
	DialogBoxIndirectParam(&dlg_data, hOwner, IDD_MAINTAIN_DIALOG,
							MaintainProc, 0, &wndMem);
	btn[0].status = 0;
}

