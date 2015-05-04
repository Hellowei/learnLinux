#define   TIMEDLG_GLOBALS 
#include  "includes.h"

#define DATE_S_HW(date) SetSysDatetime(date)
//	   int statfs(const char *path, struct statfs *buf);
static VOID SetDateTime(HWND hWnd, char type)
{
//	if(IDYES != MessageBox(hWnd, STR_MSGBOX_PRO_SYSTEM_SETTIME, 0,
//		STR_MSGBOX_CAP_SYSTEM_SETTIME, MB_ALIGNCENTER | MB_YESNO, SysGui_HTSK))
//	{
//		return;
//	}
	FmsPtr->ClosePtnFile(FmsPtr);
	if (type)
	{
		DateTime.year   = GetSpinBoxIntCurValue(IDD_DATETIME_SETUP,
												IDC_DATETIME_SETUP_YEAR_SB);
		DateTime.month  = GetSpinBoxIntCurValue(IDD_DATETIME_SETUP,
												IDC_DATETIME_SETUP_MONTH_SB);
		DateTime.day	= GetSpinBoxIntCurValue(IDD_DATETIME_SETUP,
												IDC_DATETIME_SETUP_DAY_SB);
	}else
	{
		DateTime.hour   = GetSpinBoxIntCurValue(IDD_DATETIME_SETUP,
												IDC_DATETIME_SETUP_HOUR_SB);
		DateTime.minute = GetSpinBoxIntCurValue(IDD_DATETIME_SETUP,
												IDC_DATETIME_SETUP_MINUTE_SB);
		DateTime.second = GetSpinBoxIntCurValue(IDD_DATETIME_SETUP,
												IDC_DATETIME_SETUP_SECOND_SB);
	}
	DATE_S_HW(&DateTime);
}

static INT32 
TimeSetupDlgProc (HANDLE hWnd, INT32 message, DWORD wParam, LPARAM lParam)
{
	switch (message)
	{
		case MSG_INITDIALOG:
			{
				SetSpinBoxIntCurValue(IDD_DATETIME_SETUP,
					IDC_DATETIME_SETUP_YEAR_SB, DateTime.year);
				SetSpinBoxIntCurValue(IDD_DATETIME_SETUP,
					IDC_DATETIME_SETUP_MONTH_SB, DateTime.month);
				SetSpinBoxIntCurValue(IDD_DATETIME_SETUP,
					IDC_DATETIME_SETUP_DAY_SB, DateTime.day);
				SetSpinBoxIntCurValue(IDD_DATETIME_SETUP,
					IDC_DATETIME_SETUP_HOUR_SB, DateTime.hour);
				SetSpinBoxIntCurValue(IDD_DATETIME_SETUP,
					IDC_DATETIME_SETUP_MINUTE_SB, DateTime.minute);
				SetSpinBoxIntCurValue(IDD_DATETIME_SETUP,
					IDC_DATETIME_SETUP_SECOND_SB, DateTime.second);
			}
			break;

		case MSG_COMMAND:
			{
				switch(LOWORD(wParam))
				{
					case IDC_DATETIME_SETUP_EXIT_B:
						EndDialog(hWnd, IDOK);
						return 0;

					case IDC_DATETIME_SETUP_YEAR_SB:
//					case IDC_DATETIME_SETUP_MONTH_SB:
					case IDC_DATETIME_SETUP_DAY_SB:
					case IDC_DATETIME_SETUP_HOUR_SB:
					case IDC_DATETIME_SETUP_MINUTE_SB:
					case IDC_DATETIME_SETUP_SECOND_SB:
						if (0)//(HIWORD(wParam) == SBN_ENTER)
						{
							SelectKeyboardType(0, 
								LoadString(STR_DLG_SETDATETIME)," ");
							OnClickSpinbox(hWnd, (LOWORD(wParam)), -1);
							return 0;
						}
						return 0;

					
					case IDC_DATETIME_SETUP_MONTH_SB:
						// 月份影响日期的最大值，需单独处理
						if (HIWORD(wParam) == SBN_CHANGED)
						{
							INT16 year;
							INT16 month;
							INT16 day;
							INT16 maxday;
//							SelectKeyboardType(0, 
//								LoadString(STR_DLG_SETDATETIME)," ");
//							month = OnClickSpinbox(hWnd, (LOWORD(wParam)), -1);
							month = GetSpinBoxIntCurValue(IDD_DATETIME_SETUP,
													IDC_DATETIME_SETUP_MONTH_SB);
							year = GetSpinBoxIntCurValue(IDD_DATETIME_SETUP,
													IDC_DATETIME_SETUP_YEAR_SB);
							maxday = DaysInThisMonth(year, month);
							day = GetSpinBoxIntCurValue(IDD_DATETIME_SETUP,
													IDC_DATETIME_SETUP_DAY_SB);
							if (maxday < day)
							{
								day = maxday;
							}
							SetSpinBoxIntValue(IDD_DATETIME_SETUP,
								IDC_DATETIME_SETUP_DAY_SB, day, maxday, 1);
							return 0;
						}

					case IDC_DATETIME_SETUP_SETDATE_B:
						if (HIWORD(wParam) == BN_CLICKED)
						{
							SetDateTime(hWnd, 1);
						}
						return 0;

					case IDC_DATETIME_SETUP_SETTIME_B:
						if (HIWORD(wParam) == BN_CLICKED)
						{
							SetDateTime(hWnd, 0);
						}
						return 0;

					default:
						break;
				}
			}
			break;

		default:
			break;
	}
	return DefaultDialogProc (hWnd, message, wParam, lParam);
}

VOID TimeSetupDialog(HWND parent)
{
	if (IDOK != PasswordDialog(0, 2, 0))
	{
		return;
	}
	DLGTEMPLATE dlg_data	= 
	{
		WS_ABSSCRPOS | WS_CAPTION | WS_BORDER | WS_MODALDLG,	 0,
		0, 0, 325, 135, STR_DLG_SETDATETIME,   0,  NULL,  0L,
	};
	
	CTRLDATA	ctrl_data[]	 = 
	{
		{   CTRL_SPINBOX,	WS_VISIBLE | WS_TABSTOP, WS_NONE,
			15 , 15 , 70 , 30 , IDC_DATETIME_SETUP_YEAR_SB,	 0, 0L, 0L },

		{   CTRL_SPINBOX,	WS_VISIBLE | WS_TABSTOP, WS_NONE,
			90 , 15 , 70 , 30 , IDC_DATETIME_SETUP_MONTH_SB,	0, 0L, 0L },

		{   CTRL_SPINBOX,	WS_VISIBLE | WS_TABSTOP, WS_NONE,
			165, 15 , 70 , 30 , IDC_DATETIME_SETUP_DAY_SB,	  0, 0L, 0L },

		{   CTRL_BUTTON,	 WS_VISIBLE | WS_TABSTOP, WS_NONE,
			240, 15 , 70 , 30 , IDC_DATETIME_SETUP_SETDATE_B, STR_DLG_SETDATE, 0L, 0L },

		{   CTRL_SPINBOX,	WS_VISIBLE | WS_TABSTOP, WS_NONE,
			15 , 50 , 70 , 30 , IDC_DATETIME_SETUP_HOUR_SB,	 0, 0L, 0L },

		{   CTRL_SPINBOX,	WS_VISIBLE | WS_TABSTOP, WS_NONE,
			90 , 50 , 70 , 30 , IDC_DATETIME_SETUP_MINUTE_SB,   0, 0L, 0L },

		{   CTRL_SPINBOX,	WS_VISIBLE | WS_TABSTOP, WS_NONE,
			165, 50 , 70 , 30 , IDC_DATETIME_SETUP_SECOND_SB,   0, 0L, 0L },

		{   CTRL_BUTTON,	 WS_VISIBLE | WS_TABSTOP, WS_NONE,
			240, 50 , 70 , 30 , IDC_DATETIME_SETUP_SETTIME_B, STR_DLG_SETTIME, 0L, 0L },

		{   CTRL_BUTTON,	 WS_VISIBLE | WS_TABSTOP | BS_ICON, WS_NONE,
			325-45, (-30-45)/ 2, 30, 30, IDC_DATETIME_SETUP_EXIT_B, 0, 0L, 0L }
	};
	//	format   mode				   imin  imax  icur istep
	SPINBOXDATA sb_year	 = 
		{ FORM_4D, SBTXT_NUM, 0, 0, 0, 0, 2010, 2099, 2013, 1, 0, 0, 0, 0 };
	SPINBOXDATA sb_month	= 
		{ FORM_2D, SBTXT_NUM, 0, 0, 0, 0,	1,   12,	1, 1, 0, 0, 0, 0 };
	SPINBOXDATA sb_day	  = 
		{ FORM_2D, SBTXT_NUM, 0, 0, 0, 0,	1,   31,	1, 1, 0, 0, 0, 0 };
	SPINBOXDATA sb_hour	 = 
		{ FORM_2D, SBTXT_NUM, 0, 0, 0, 0,	0,   23,	0, 1, 0, 0, 0, 0 };
	SPINBOXDATA sb_minute   = 
		{ FORM_2D, SBTXT_NUM, 0, 0, 0, 0,	0,   59,	0, 1, 0, 0, 0, 0 };
	SPINBOXDATA sb_second   = 
		{ FORM_2D, SBTXT_NUM, 0, 0, 0, 0,	0,   59,	0, 1, 0, 0, 0, 0 };

	BUTTONDATA  btn_date = {0, 0, 0, 0 };
	BUTTONDATA  btn_time = {0, 0, 0, 0 };
	BUTTONDATA  btn_exit = gBtn_Exit;

	INT32   loops;
	WNDMEM  wndMem;
	loops = TABLESIZE(ctrl_data);
	wndMem.pMainWin = GetMainWndMem(IDD_DATETIME_SETUP);
	wndMem.pControl = GetCtrlWndMem(IDC_DATETIME_SETUP_FIRST);
	wndMem.ctrlNum  = loops;
	wndMem.task	 = SysGui_HTSK;
	
	dlg_data.controlnr = loops;
	dlg_data.controls  = ctrl_data;
	SetCtrlDataAddData2(ctrl_data, loops, IDC_DATETIME_SETUP_YEAR_SB,
		(UINT32)&sb_year);
	SetCtrlDataAddData2(ctrl_data, loops, IDC_DATETIME_SETUP_MONTH_SB,
		(UINT32)&sb_month);
	SetCtrlDataAddData2(ctrl_data, loops, IDC_DATETIME_SETUP_DAY_SB,
		(UINT32)&sb_day);
	SetCtrlDataAddData2(ctrl_data, loops, IDC_DATETIME_SETUP_HOUR_SB,
		(UINT32)&sb_hour);
	SetCtrlDataAddData2(ctrl_data, loops, IDC_DATETIME_SETUP_MINUTE_SB,
		(UINT32)&sb_minute);
	SetCtrlDataAddData2(ctrl_data, loops, IDC_DATETIME_SETUP_SECOND_SB,
		(UINT32)&sb_second);
	SetCtrlDataAddData2(ctrl_data, loops, IDC_DATETIME_SETUP_SETDATE_B,
		(UINT32)&btn_date);
	SetCtrlDataAddData2(ctrl_data, loops, IDC_DATETIME_SETUP_SETTIME_B,
		(UINT32)&btn_time);
	SetCtrlDataAddData2(ctrl_data, loops, IDC_DATETIME_SETUP_EXIT_B,
		(UINT32)&btn_exit);

	DialogBoxIndirectParam(&dlg_data, parent, IDD_DATETIME_SETUP,
							TimeSetupDlgProc, 0, &wndMem);
}


