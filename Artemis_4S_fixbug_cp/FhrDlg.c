#define FHR_GLOBALS
#include "includes.h"
#include "fhr.h"
#include "keyboardDlg.h"

static STRINGID FhrVolume[] = {
	STR_DLG_CHAR_0,
	STR_DLG_CHAR_1,
	STR_DLG_CHAR_2,
	STR_DLG_CHAR_3,
	STR_DLG_CHAR_4,
	STR_DLG_CHAR_5,
	STR_DLG_CHAR_6,
	STR_DLG_CHAR_7
};

static STRINGID FhrSource[] = {
	STR_DLG_FHR_FHR1,
	STR_DLG_FHR_FHR2
};

static STRINGID FhrType[] = {
	STR_DLG_FHR_SINGLE,
	STR_DLG_FHR_DOUBLE
};

static STRINGID TocoZero[] = {
	STR_DLG_TOCO_ZERO_00,
	STR_DLG_TOCO_ZERO_05,
	STR_DLG_TOCO_ZERO_10,
	STR_DLG_TOCO_ZERO_15,
	STR_DLG_TOCO_ZERO_20
};

static STRINGID FmThreshold[] = {
	STR_DLG_FM_THRESHOLD10,
	STR_DLG_FM_THRESHOLD20,
	STR_DLG_FM_THRESHOLD30,
	STR_DLG_FM_THRESHOLD40,
	STR_DLG_FM_THRESHOLD50,
	STR_DLG_FM_THRESHOLD60,
	STR_DLG_FM_THRESHOLD70,
	STR_DLG_FM_THRESHOLD80,
};

static STRINGID FmMovementCalc[] = {
	STR_DLG_FM_MOVEMENTCAL_AUTO,
	STR_DLG_FM_MOVEMENTCAL_MANUAL,
	STR_DLG_FM_MOVEMENTCAL_BOTH,
};

static VOID FhrSetupDlgInit(HWND hWnd, DWORD wParam, LPARAM lParam)
{
	HWND hCtrl;
	INT16 i;
	for (i = IDC_FHR_SETUP_ALMSWITCH_L; i <= IDC_FHR_SETUP_DETACH_L; i++)
	{
		hCtrl = GetDlgItem(hWnd, i);
		if (!hCtrl) continue;
		SetWindowFont(hCtrl, GetSystemFont(SYSLOGFONT_WCHAR_DEF));
	}
	SetListBoxString(IDD_FHR_SETUP, IDC_FHR_SETUP_SWITCH_LB, gOnOff,	TABLESIZE(gOnOff));
	SetListBoxString(IDD_FHR_SETUP, IDC_FHR_SETUP_LEVEL_LB,  gAlmLev,   TABLESIZE(gAlmLev));
	SetListBoxString(IDD_FHR_SETUP, IDC_FHR_SETUP_TYPE_LB,   FhrType,   TABLESIZE(FhrType));
	SetListBoxString(IDD_FHR_SETUP, IDC_FHR_SETUP_SOURCE_LB, FhrSource, TABLESIZE(FhrSource));
	SetListBoxString(IDD_FHR_SETUP, IDC_FHR_SETUP_VOLUME_LB, FhrVolume, TABLESIZE(FhrVolume));

	SetListBoxCurChoi(IDD_FHR_SETUP, IDC_FHR_SETUP_SWITCH_LB, FhrConfig.alarm);
	SetListBoxCurChoi(IDD_FHR_SETUP, IDC_FHR_SETUP_LEVEL_LB,  FhrConfig.alarmLevel);
	SetListBoxCurChoi(IDD_FHR_SETUP, IDC_FHR_SETUP_TYPE_LB,   FhrConfig.type);
	SetListBoxCurChoi(IDD_FHR_SETUP, IDC_FHR_SETUP_SOURCE_LB, FhrConfig.source);
	SetListBoxCurChoi(IDD_FHR_SETUP, IDC_FHR_SETUP_VOLUME_LB, FhrConfig.volume);

	SetSpinBoxIntValue(IDD_FHR_SETUP,IDC_FHR_SETUP_ALMHI_SB, 180, 240,  92);
	SetSpinBoxIntValue(IDD_FHR_SETUP,IDC_FHR_SETUP_ALMLO_SB,  90, 178,  60);
	for (i = IDC_FHR_SETUP_ALMSWITCH_L; i < IDC_FHR_SETUP_EXIT_B; i++)
	{
		hCtrl = GetDlgItem(hWnd, i);
		if (!hCtrl) continue;
		SetWindowBkColor(hCtrl, ((PCONTROL)hWnd)->iBkColor);
	}
	return;
}

static INT16 FhrSetupDlg_OnCommand(HWND hWnd, DWORD wParam, LPARAM lParam)
{
	INT16 ret = TRUE;
	switch(LOWORD(wParam))
	{
		case IDC_FHR_SETUP_SWITCH_LB:
			break;

		case IDC_FHR_SETUP_LEVEL_LB:
			break;

		case IDC_FHR_SETUP_ALMHI_SB:
			if (HIWORD(wParam) == SBN_ENTER) 
			{
				INT32 value;
				value =
					GetSpinBoxIntCurValue(IDD_FHR_SETUP, IDC_FHR_SETUP_ALMHI_SB);
				SelectKeyboardType(0, LoadString(STR_DLG_FHR_ALM_HI), 
									"输入胎心率报警高限");
				UseKeyboard(hWnd, IDC_FHR_SETUP_ALMHI_SB, (LPARAM)&value);
				SetSpinBoxIntCurValue(IDD_FHR_SETUP, IDC_FHR_SETUP_ALMHI_SB,
					(INT16)value);
				value = 
					GetSpinBoxIntCurValue(IDD_FHR_SETUP, IDC_FHR_SETUP_ALMHI_SB);
				SetSpinBoxIntCurValue(IDD_FHR_SETUP, IDC_FHR_SETUP_ALMHI_SB,
					(INT16)value);
				SetSpinBoxIntMaxValue(IDD_FHR_SETUP, IDC_FHR_SETUP_ALMLO_SB,
					(INT16)value - 2);
			}
			break;

		case IDC_FHR_SETUP_ALMLO_SB:
			if (HIWORD(wParam) == SBN_ENTER) 
			{
				INT32 value;
				value =
					GetSpinBoxIntCurValue(IDD_FHR_SETUP, IDC_FHR_SETUP_ALMLO_SB);
				SelectKeyboardType(0, LoadString(STR_DLG_FHR_ALM_LO), 
									"输入胎心率报警低限");
				UseKeyboard(hWnd, IDC_FHR_SETUP_ALMLO_SB, (LPARAM)&value);
				SetSpinBoxIntCurValue(IDD_FHR_SETUP, IDC_FHR_SETUP_ALMLO_SB,
					(INT16)value);
				value = 
					GetSpinBoxIntCurValue(IDD_FHR_SETUP, IDC_FHR_SETUP_ALMLO_SB);
				SetSpinBoxIntMinValue(IDD_FHR_SETUP, IDC_FHR_SETUP_ALMHI_SB,
					(INT16)value + 2);
			}
			break;

		case IDC_FHR_SETUP_TYPE_LB:
			break;

		case IDC_FHR_SETUP_SOURCE_LB:
			break;

		case IDC_FHR_SETUP_VOLUME_LB:
			break;

		case IDC_FHR_SETUP_DETACH_SB:
			if (HIWORD(wParam) == SBN_ENTER) 
			{
				INT32 value;
				value =
					GetSpinBoxIntCurValue(IDD_FHR_SETUP, IDC_FHR_SETUP_DETACH_SB);
				SelectKeyboardType(0, LoadString(STR_DLG_FHR_DETACH_SPLINE), 
									"输入曲线分离值");
				UseKeyboard(hWnd, IDC_FHR_SETUP_DETACH_SB, (LPARAM)&value);
				SetSpinBoxIntCurValue(IDD_FHR_SETUP, IDC_FHR_SETUP_DETACH_SB,
					(INT16)value);
				value = 
					GetSpinBoxIntCurValue(IDD_FHR_SETUP, IDC_FHR_SETUP_DETACH_SB);
				SetSpinBoxIntCurValue(IDD_FHR_SETUP, IDC_FHR_SETUP_DETACH_SB,
					(INT16)value);
			}
			break;

		case IDC_FHR_SETUP_EXIT_B:
			EndDialog (hWnd, IDOK);
			break;

	}
	return ret;
}

static  INT32  FhrSetupDlgProc (HANDLE hWnd, INT32 message, DWORD wParam, LPARAM lParam)
{
	switch (message)
	{
		case MSG_INITDIALOG:
			FhrSetupDlgInit(hWnd, wParam, lParam);
			break;
		
		case MSG_COMMAND: {
				if (FhrSetupDlg_OnCommand(hWnd, wParam, lParam))
					return 0;
			}
			break;

		default:
			break;
	}
	
	return DefaultDialogProc (hWnd, message, wParam, lParam);
}

VOID FhrSetupDialog (HWND parent)
{
	enum dialog_size{
		DLG_COLUMN1_W = 80,
		DLG_COLUMN2_W = 80,
		DLG_COLUMN3_W = 80,
		DLG_COLUMN4_W = 80,
		DLG_COLUMN1_X = DLG_OFFSET,
		DLG_COLUMN2_X = DLG_COLUMN1_X + DLG_COLUMN1_W + DLG_OFFSET,
		DLG_COLUMN3_X = DLG_COLUMN2_X + DLG_COLUMN2_W + DLG_OFFSET,
		DLG_COLUMN4_X = DLG_COLUMN3_X + DLG_COLUMN3_W + DLG_OFFSET,
			DLG_WIDTH = DLG_COLUMN4_X + DLG_COLUMN4_W + DLG_OFFSET,
		DLG_ROW_H	 = CTRL_HEIGHT,
		DLG_ROW1_Y	= 10,
		DLG_ROW2_Y	= DLG_ROW1_Y + DLG_ROW_H,
		DLG_ROW3_Y	= DLG_ROW2_Y + DLG_ROW_H,
		DLG_ROW4_Y	= DLG_ROW3_Y + DLG_ROW_H,
			DLG_HIGH  = DLG_ROW4_Y + DLG_ROW_H + DLG_MENU_HIGHT,
			DLG_XPOS  = (SCREEN_WIDTH - DLG_WIDTH) / 2,
			DLG_YPOS  = SCREEN_HIGH - DLG_HIGH - BOTTOMBAR_HEIGHT
	};
	
	DLGTEMPLATE dlg_data = {
	   WS_ABSSCRPOS | WS_CAPTION | WS_BORDER | WS_MODALDLG, WS_NONE, 
	   DLG_XPOS, CTRL_HEIGHT, DLG_WIDTH, DLG_HIGH,  STR_DLG_FHR_SETUP, 0, NULL, 0L,
	};

	LISTBOXDATA lb_switch = { 2, 0, 2, 0, 0, gOnOff,	0 };

	LISTBOXDATA lb_level  = { 3, 0, 3, 0, 0, gAlmLev,   0 };

	LISTBOXDATA lb_source = { 2, 1, 2, 0, 0, FhrSource, 0 };

	LISTBOXDATA lb_volume = { 8, 1, 8, 0, 0, FhrVolume, 0 };

	LISTBOXDATA lb_type   = { 2, 1, 2, 0, 0, FhrType,   0 };

	SPINBOXDATA sb_alm_hi = 
		{ FORM_3D, SBTXT_NUM,   0,   0,   0,   0,  50, 210, 180,  1,  0,  0 };

	SPINBOXDATA sb_alm_lo =
		{ FORM_3D, SBTXT_NUM,   0,   0,   0,   0,  50, 120,  90,  1,  0,  0 };

	SPINBOXDATA sb_detach =
		{ FORM_3D, SBTXT_NUM,   0,   0,   0,   0,  10, 100, 100,  1,  0,  0 };

	BUTTONDATA  btn_exit  = gBtn_Exit;

	POINT ctrl_pos[] =
	{
		{ DLG_COLUMN1_X, DLG_ROW1_Y + STATIC_OFFSET }, // IDC_FHR_SETUP_ALMSWITCH_L,
		{ DLG_COLUMN1_X, DLG_ROW2_Y + STATIC_OFFSET }, // IDC_FHR_SETUP_ALMLEVEL_L,
		{ DLG_COLUMN1_X, DLG_ROW3_Y + STATIC_OFFSET }, // IDC_FHR_SETUP_FHR_HI_L,
		{ DLG_COLUMN1_X, DLG_ROW4_Y + STATIC_OFFSET }, // IDC_FHR_SETUP_FHR_LO_L,
		{ DLG_COLUMN3_X, DLG_ROW1_Y + STATIC_OFFSET }, // IDC_FHR_SETUP_TYPE_L,
		{ DLG_COLUMN3_X, DLG_ROW2_Y + STATIC_OFFSET }, // IDC_FHR_SETUP_SOURCE_L,
		{ DLG_COLUMN3_X, DLG_ROW3_Y + STATIC_OFFSET }, // IDC_FHR_SETUP_VOLUME_L,
		{ DLG_COLUMN3_X, DLG_ROW4_Y + STATIC_OFFSET }, // IDC_FHR_SETUP_DETACH_L,
		{ DLG_COLUMN2_X, DLG_ROW1_Y }, // IDC_FHR_SETUP_SWITCH_LB,
		{ DLG_COLUMN2_X, DLG_ROW2_Y }, // IDC_FHR_SETUP_LEVEL_LB,
		{ DLG_COLUMN2_X, DLG_ROW3_Y }, // IDC_FHR_SETUP_ALMHI_SB,
		{ DLG_COLUMN2_X, DLG_ROW4_Y }, // IDC_FHR_SETUP_ALMLO_SB,
		{ DLG_COLUMN4_X, DLG_ROW1_Y }, // IDC_FHR_SETUP_TYPE_LB,
		{ DLG_COLUMN4_X, DLG_ROW2_Y }, // IDC_FHR_SETUP_SOURCE_LB,
		{ DLG_COLUMN4_X, DLG_ROW3_Y }, // IDC_FHR_SETUP_VOLUME_LB,
		{ DLG_COLUMN4_X, DLG_ROW4_Y }, // IDC_FHR_SETUP_DETACH_SB,
		{ DLG_WIDTH-EXIT_ICON_WIDTH - DLG_OFFSET, -(DLG_MENU_HIGHT + EXIT_ICON_HIGH) / 2 }  // IDC_FHR_SETUP_EXIT_B
	};

	SIZE  ctrl_size[] = 
	{
		{ DLG_COLUMN1_W, STATIC_HEIGHT  }, // IDC_FHR_SETUP_ALMSWITCH_L,
		{ DLG_COLUMN1_W, STATIC_HEIGHT  }, // IDC_FHR_SETUP_ALMLEVEL_L,
		{ DLG_COLUMN1_W, STATIC_HEIGHT  }, // IDC_FHR_SETUP_FHR_HI_L,
		{ DLG_COLUMN1_W, STATIC_HEIGHT  }, // IDC_FHR_SETUP_FHR_LO_L,
		{ DLG_COLUMN3_W, STATIC_HEIGHT  }, // IDC_FHR_SETUP_TYPE_L,
		{ DLG_COLUMN3_W, STATIC_HEIGHT  }, // IDC_FHR_SETUP_SOURCE_L,
		{ DLG_COLUMN3_W, STATIC_HEIGHT  }, // IDC_FHR_SETUP_VOLUME_L,
		{ DLG_COLUMN3_W, STATIC_HEIGHT  }, // IDC_FHR_SETUP_DETACH_L,
		{ DLG_COLUMN2_W, KEY_HEIGHT	 }, // IDC_FHR_SETUP_SWITCH_LB,
		{ DLG_COLUMN2_W, KEY_HEIGHT	 }, // IDC_FHR_SETUP_LEVEL_LB,
		{ DLG_COLUMN2_W, KEY_HEIGHT	 }, // IDC_FHR_SETUP_ALMHI_SB,
		{ DLG_COLUMN2_W, KEY_HEIGHT	 }, // IDC_FHR_SETUP_ALMLO_SB,
		{ DLG_COLUMN4_W, KEY_HEIGHT	 }, // IDC_FHR_SETUP_TYPE_LB,
		{ DLG_COLUMN4_W, KEY_HEIGHT	 }, // IDC_FHR_SETUP_SOURCE_LB,
		{ DLG_COLUMN4_W, KEY_HEIGHT	 }, // IDC_FHR_SETUP_VOLUME_LB,
		{ DLG_COLUMN4_W, KEY_HEIGHT	 }, // IDC_FHR_SETUP_DETACH_SB,
		{ EXIT_ICON_WIDTH, EXIT_ICON_HIGH }  // IDC_FHR_SETUP_EXIT_B
	};

	CTRLDATA ctrl_data [] =
	{
		{ CTRL_STATIC, WS_VISIBLE | SS_SIMPLE, WS_EX_NONE, 0, 0, 0, 0,
			IDC_FHR_SETUP_ALMSWITCH_L,  STR_DLG_ALARM_SWITCH,	   0L, 0L},
		{ CTRL_STATIC, WS_VISIBLE | SS_SIMPLE, WS_EX_NONE, 0, 0, 0, 0,
			IDC_FHR_SETUP_ALMLEVEL_L, STR_DLG_ALM_LVL,			  0L, 0L},
		{ CTRL_STATIC, WS_VISIBLE | SS_SIMPLE, WS_EX_NONE, 0, 0, 0, 0,
			IDC_FHR_SETUP_FHR_HI_L,	 STR_DLG_FHR_ALM_HI,		 0L, 0L},
		{ CTRL_STATIC, WS_VISIBLE | SS_SIMPLE, WS_EX_NONE, 0, 0, 0, 0,
			IDC_FHR_SETUP_FHR_LO_L,	 STR_DLG_FHR_ALM_LO,		 0L, 0L},
		{ CTRL_STATIC, WS_VISIBLE | SS_SIMPLE, WS_EX_NONE, 0, 0, 0, 0,
			IDC_FHR_SETUP_TYPE_L,	   STR_DLG_FHR_TYPE,		   0L, 0L},
		{ CTRL_STATIC, WS_VISIBLE | SS_SIMPLE, WS_EX_NONE, 0, 0, 0, 0,
			IDC_FHR_SETUP_SOURCE_L,	 STR_DLG_FHR_SOURCE,		 0L, 0L},
		{ CTRL_STATIC, WS_VISIBLE | SS_SIMPLE, WS_EX_NONE, 0, 0, 0, 0,
			IDC_FHR_SETUP_VOLUME_L,	 STR_DLG_FHR_VOLUME,		 0L, 0L},
		{ CTRL_STATIC, WS_VISIBLE | SS_SIMPLE, WS_EX_NONE, 0, 0, 0, 0,
			IDC_FHR_SETUP_DETACH_L,	 STR_DLG_FHR_DETACH_SPLINE,  0L, 0L},

		{ CTRL_LISTBOX, WS_VISIBLE | WS_TABSTOP, WS_EX_NONE, 0, 0, 0, 0,
			IDC_FHR_SETUP_SWITCH_LB,	0, 0L, 0L},
		{ CTRL_LISTBOX, WS_VISIBLE | WS_TABSTOP, WS_EX_NONE, 0, 0, 0, 0,
			IDC_FHR_SETUP_LEVEL_LB,	 0, 0L, 0L},
		{ CTRL_SPINBOX, WS_VISIBLE | WS_TABSTOP, WS_EX_NONE, 0, 0, 0, 0,
			IDC_FHR_SETUP_ALMHI_SB,	 0, 0L, 0L},
		{ CTRL_SPINBOX, WS_VISIBLE | WS_TABSTOP, WS_EX_NONE, 0, 0, 0, 0,
			IDC_FHR_SETUP_ALMLO_SB,	 0, 0L, 0L},
		{ CTRL_LISTBOX, WS_VISIBLE | WS_TABSTOP, WS_EX_NONE, 0, 0, 0, 0,
			IDC_FHR_SETUP_TYPE_LB,	  0, 0L, 0L},
		{ CTRL_LISTBOX, WS_VISIBLE | WS_TABSTOP, WS_EX_NONE, 0, 0, 0, 0,
			IDC_FHR_SETUP_SOURCE_LB,	0, 0L, 0L},
		{ CTRL_LISTBOX, WS_VISIBLE | WS_TABSTOP, WS_EX_NONE, 0, 0, 0, 0,
			IDC_FHR_SETUP_VOLUME_LB,	0, 0L, 0L},
		{ CTRL_SPINBOX, WS_VISIBLE | WS_TABSTOP, WS_EX_NONE, 0, 0, 0, 0,
			IDC_FHR_SETUP_DETACH_SB,	0, 0L, 0L},
		{ CTRL_BUTTON,  WS_VISIBLE | WS_TABSTOP | BS_ICON, WS_EX_NONE, 0, 0, 0, 0,
			IDC_FHR_SETUP_EXIT_B,		 0, 0L, 0L} 
	};
	
	INT16 i, loops;
	loops = TABLESIZE(ctrl_data);
	WNDMEM   wndMem;
	
	wndMem.pMainWin = GetMainWndMem(IDD_FHR_SETUP);
	wndMem.pControl = GetCtrlWndMem(IDC_FHR_SETUP_FIRST);
	wndMem.ctrlNum  = TABLESIZE(ctrl_data);
	wndMem.task	 = SysGui_HTSK;
	
	dlg_data.controlnr = loops;
	dlg_data.controls  = ctrl_data;

	for(i = 0; i < loops; i++)
	{
		ctrl_data[i].x = ctrl_pos[i].x;
		ctrl_data[i].y = ctrl_pos[i].y;
		ctrl_data[i].w = ctrl_size[i].cx;
		ctrl_data[i].h = ctrl_size[i].cy;
	}
	SetCtrlDataAddData2(ctrl_data, loops, IDC_FHR_SETUP_SWITCH_LB, (UINT32)&lb_switch);
	SetCtrlDataAddData2(ctrl_data, loops, IDC_FHR_SETUP_LEVEL_LB,  (UINT32)&lb_level);
	SetCtrlDataAddData2(ctrl_data, loops, IDC_FHR_SETUP_ALMHI_SB,  (UINT32)&sb_alm_hi);
	SetCtrlDataAddData2(ctrl_data, loops, IDC_FHR_SETUP_ALMLO_SB,  (UINT32)&sb_alm_lo);
	SetCtrlDataAddData2(ctrl_data, loops, IDC_FHR_SETUP_TYPE_LB,   (UINT32)&lb_type);
	SetCtrlDataAddData2(ctrl_data, loops, IDC_FHR_SETUP_SOURCE_LB, (UINT32)&lb_source);
	SetCtrlDataAddData2(ctrl_data, loops, IDC_FHR_SETUP_VOLUME_LB, (UINT32)&lb_volume);
	SetCtrlDataAddData2(ctrl_data, loops, IDC_FHR_SETUP_DETACH_SB, (UINT32)&sb_detach);
	SetCtrlDataAddData2(ctrl_data, loops, IDC_FHR_SETUP_EXIT_B,	  (UINT32)&btn_exit);

	if (parent == MainScnHWnd)
		parent = 0;

	DialogBoxIndirectParam(&dlg_data, parent, IDD_FHR_SETUP, FhrSetupDlgProc, 0, &wndMem);
}


static VOID TocoSetupDlgInit(HWND hWnd, DWORD wParam, LPARAM lParam)
{
	HWND hCtrl;
	hCtrl = GetDlgItem(hWnd, IDC_TOCO_SETUP_ZEROVALUE_L);
	SetWindowFont(hCtrl, GetSystemFont(SYSLOGFONT_WCHAR_DEF));
	SetListBoxString(IDD_TOCO_SETUP, IDC_TOCO_SETUP_ZEROVALUE_LB, TocoZero, TABLESIZE(TocoZero));
	SetListBoxCurChoi(IDD_TOCO_SETUP, IDC_TOCO_SETUP_ZEROVALUE_LB, FhrConfig.zero);
	return;
}

static INT16 TocoSetupDlg_OnCommand(HWND hWnd, DWORD wParam, LPARAM lParam)
{
	INT16 ret = TRUE;
	switch(LOWORD(wParam))
	{

		case IDC_TOCO_SETUP_ZEROVALUE_LB:
			break;

		case IDC_TOCO_SETUP_ZERO_B:
			break;

		case IDC_TOCO_SETUP_EXIT_B:
			EndDialog (hWnd, IDOK);
			break;

	}
	return ret;
}

static  INT32  TocoSetupDlgProc (HANDLE hWnd, INT32 message, DWORD wParam, LPARAM lParam)
{
	switch (message)
	{
		case MSG_INITDIALOG:
			TocoSetupDlgInit(hWnd, wParam, lParam);
			break;
		
		case MSG_COMMAND: 
			{
				if (TocoSetupDlg_OnCommand(hWnd, wParam, lParam))
					return 0;
			}
			break;

		default:
			break;
	}
	
	return DefaultDialogProc (hWnd, message, wParam, lParam);
}


VOID TocoSetupDialog (HWND parent)
{
	enum dialog_size{
		DLG_COLUMN1_W = 80,
		DLG_COLUMN2_W = 80,
		DLG_COLUMN1_X = DLG_OFFSET,
		DLG_COLUMN2_X = DLG_COLUMN1_X + DLG_COLUMN1_W + DLG_OFFSET,
			DLG_WIDTH = DLG_COLUMN2_X + DLG_COLUMN2_W + DLG_OFFSET,
		DLG_ROW_H	 = CTRL_HEIGHT,
		DLG_ROW1_Y	= 10,
		DLG_ROW2_Y	= DLG_ROW1_Y + DLG_ROW_H,
			DLG_HIGH  = DLG_ROW2_Y + DLG_ROW_H + DLG_MENU_HIGHT,
	};
	
	DLGTEMPLATE dlg_data = {
	   WS_ABSSCRPOS | WS_CAPTION | WS_BORDER | WS_MODALDLG, WS_NONE, 
	   0, 0, DLG_WIDTH, DLG_HIGH,  STR_DLG_TOCO_SETUP, 0, NULL, 0L,
	};

	LISTBOXDATA lb_val	= { 5, 1, 5, 0, 0, TocoZero,   0 };

	BUTTONDATA  btn_zero  = { 0 };

	BUTTONDATA  btn_exit  = gBtn_Exit;

	POINT ctrl_pos[] =
	{
		{ DLG_COLUMN1_X, DLG_ROW1_Y + STATIC_OFFSET }, // IDC_FHR_SETUP_ALMSWITCH_L,
		{ DLG_COLUMN2_X, DLG_ROW1_Y }, // IDC_FHR_SETUP_SWITCH_LB,
		{ DLG_COLUMN1_X, DLG_ROW2_Y }, // IDC_FHR_SETUP_LEVEL_LB,
		{ DLG_WIDTH-EXIT_ICON_WIDTH - DLG_OFFSET, -(DLG_MENU_HIGHT + EXIT_ICON_HIGH) / 2 }  // IDC_FHR_SETUP_EXIT_B
	};

	SIZE  ctrl_size[] = 
	{
		{ DLG_COLUMN1_W,	STATIC_HEIGHT   },
		{ DLG_COLUMN2_W,	KEY_HEIGHT	  },
		{ DLG_COLUMN1_W + DLG_COLUMN2_W,	KEY_HEIGHT	  },
		{ EXIT_ICON_WIDTH,  EXIT_ICON_HIGH  } 
	};

	CTRLDATA ctrl_data [] =
	{
		{ CTRL_STATIC,  WS_VISIBLE | SS_SIMPLE, WS_EX_NONE, 0, 0, 0, 0,
			IDC_TOCO_SETUP_ZEROVALUE_L,  STR_DLG_TOCO_ZERO_VAL,	   0L, 0L},

		{ CTRL_LISTBOX, WS_VISIBLE | WS_TABSTOP, WS_EX_NONE, 0, 0, 0, 0,
			IDC_TOCO_SETUP_ZEROVALUE_LB,	0, 0L, 0L},

		{ CTRL_BUTTON,  WS_VISIBLE | WS_TABSTOP, WS_EX_NONE, 0, 0, 0, 0,
			IDC_TOCO_SETUP_ZERO_B,	STR_DLG_TOCO_ZERO, 0L, 0L},

		{ CTRL_BUTTON,  WS_VISIBLE | WS_TABSTOP | BS_ICON, WS_EX_NONE, 0, 0, 0, 0,
			IDC_TOCO_SETUP_EXIT_B,		 0, 0L, 0L} 
	};
	
	INT16 i, loops;
	loops = TABLESIZE(ctrl_data);
	WNDMEM   wndMem;
	
	wndMem.pMainWin = GetMainWndMem(IDD_TOCO_SETUP);
	wndMem.pControl = GetCtrlWndMem(IDC_TOCO_SETUP_FIRST);
	wndMem.ctrlNum  = TABLESIZE(ctrl_data);
	wndMem.task	 = SysGui_HTSK;
	
	dlg_data.controlnr = loops;
	dlg_data.controls  = ctrl_data;

	for(i = 0; i < loops; i++)
	{
		ctrl_data[i].x = ctrl_pos[i].x;
		ctrl_data[i].y = ctrl_pos[i].y;
		ctrl_data[i].w = ctrl_size[i].cx;
		ctrl_data[i].h = ctrl_size[i].cy;
	}
	SetCtrlDataAddData2(ctrl_data, loops, IDC_TOCO_SETUP_ZEROVALUE_LB, (UINT32)&lb_val);
	SetCtrlDataAddData2(ctrl_data, loops, IDC_TOCO_SETUP_ZERO_B, (UINT32)&btn_zero);
	SetCtrlDataAddData2(ctrl_data, loops, IDC_TOCO_SETUP_EXIT_B, (UINT32)&btn_exit);

	if (parent == MainScnHWnd)
		parent = 0;

	DialogBoxIndirectParam(&dlg_data, parent, IDD_TOCO_SETUP, TocoSetupDlgProc, 0, &wndMem);
}

static VOID FmSetupDlgInit(HWND hWnd, DWORD wParam, LPARAM lParam)
{
	HWND hCtrl;
	hCtrl = GetDlgItem(hWnd, IDC_FM_SETUP_THRESHOLD_VAL_L);
	SetWindowFont(hCtrl, GetSystemFont(SYSLOGFONT_WCHAR_DEF));
	hCtrl = GetDlgItem(hWnd, IDC_FM_SETUP_MOVEMENT_CAL_L);
	SetWindowFont(hCtrl, GetSystemFont(SYSLOGFONT_WCHAR_DEF));
	
	SetListBoxString(IDD_FM_SETUP, IDC_FM_SETUP_THRESHOLD_VAL_LB, FmThreshold, TABLESIZE(FmThreshold));
	SetListBoxCurChoi(IDD_FM_SETUP, IDC_FM_SETUP_THRESHOLD_VAL_LB, FhrConfig.threshold);
	SetListBoxString(IDD_FM_SETUP, IDC_FM_SETUP_MOVEMENT_CAL_LB, FmMovementCalc, TABLESIZE(FmMovementCalc));
	SetListBoxCurChoi(IDD_FM_SETUP, IDC_FM_SETUP_MOVEMENT_CAL_LB, FhrConfig.movement_calc);
	return;
}

static fill_rectangle(HWND hWnd,PRECT prc, GAL_PIXEL color)
{
	static BOOL	 flag	= FALSE;
	static UCHAR	*buff   = NULL;
	GAL_PIXEL	   clr;
	HDC			 hdc;
	RECT			rc_src;
	if (flag == FALSE)
	{
		flag = TRUE;
		hdc = GetDC(hWnd);
		clr = SetBrushColor(hdc, color);
		rc_src = *prc;
		ClientToScreen(hWnd, &rc_src.left, &rc_src.top);
		ClientToScreen(hWnd, &rc_src.right, &rc_src.bottom);
		buff = (UCHAR*)getFbCache(hdc, &rc_src);
		FillRect(hdc, prc->left+1, prc->top + DLG_MENU_HIGHT +1, RECTWP(prc), RECTHP(prc));
		SetBrushColor(hdc, clr);
		ReleaseDC(hdc);
	}
	else
	{
		flag = FALSE;
		hdc = GetDC(hWnd);
		rc_src = *prc;
		ClientToScreen(hWnd, &rc_src.left, &rc_src.top);
		ClientToScreen(hWnd, &rc_src.right, &rc_src.bottom);
		putFbCache(hdc, &rc_src, buff);
		ReleaseDC(hdc);
		free(buff);
	}
}

static INT16 FmSetupDlg_OnCommand(HWND hWnd, DWORD wParam, LPARAM lParam)
{
	INT16 ret = TRUE;
	switch(LOWORD(wParam))
	{

		case IDC_FM_SETUP_THRESHOLD_VAL_LB:
			break;
			
		case IDC_FM_SETUP_MOVEMENT_CAL_LB:
			break;

		case IDC_FM_SETUP_MOVEMENT_ZERO_B:
			{
				RECT rc;
				SetRect(&rc, 10, 10, 150, 250);
				fill_rectangle(hWnd, &rc, PIXEL_red);
			}
			break;

		case IDC_FM_SETUP_EXIT_B:
			EndDialog (hWnd, IDOK);
			break;

	}
	return ret;
}

static  INT32  FmSetupDlgProc (HANDLE hWnd, INT32 message, DWORD wParam, LPARAM lParam)
{
	switch (message)
	{
		case MSG_INITDIALOG:
			FmSetupDlgInit(hWnd, wParam, lParam);
			break;
		
		case MSG_COMMAND: 
			{
				if (FmSetupDlg_OnCommand(hWnd, wParam, lParam))
					return 0;
			}
			break;

		default:
			break;
	}
	
	return DefaultDialogProc (hWnd, message, wParam, lParam);
}


VOID FmSetupDialog (HWND parent)
{
	enum dialog_size{
		DLG_COLUMN1_W = 110,
		DLG_COLUMN2_W = 80,
		DLG_COLUMN1_X = DLG_OFFSET,
		DLG_COLUMN2_X = DLG_COLUMN1_X + DLG_COLUMN1_W + DLG_OFFSET,
			DLG_WIDTH = DLG_COLUMN2_X + DLG_COLUMN2_W + DLG_OFFSET,
		DLG_ROW_H	 = CTRL_HEIGHT,
		DLG_ROW1_Y	= 10,
		DLG_ROW2_Y	= DLG_ROW1_Y + DLG_ROW_H,
		DLG_ROW3_Y	= DLG_ROW2_Y + DLG_ROW_H,
			DLG_HIGH  = DLG_ROW3_Y + DLG_ROW_H + DLG_MENU_HIGHT,
			DLG_XPOS  = (SCREEN_WIDTH - DLG_WIDTH) / 2,
			DLG_YPOS  = SCREEN_HIGH - DLG_HIGH - BOTTOMBAR_HEIGHT
	};
	
	DLGTEMPLATE dlg_data = {
	   WS_ABSSCRPOS | WS_CAPTION | WS_BORDER | WS_MODALDLG, WS_NONE, 
	   DLG_XPOS, CTRL_HEIGHT, DLG_WIDTH, DLG_HIGH,  STR_DLG_FM_SETUP, 0, NULL, 0L,
	};

	LISTBOXDATA lb_val	= { 8, 1, 8, 0, 0, FmThreshold,	0 };
	LISTBOXDATA lb_calc   = { 3, 1, 3, 0, 0, FmMovementCalc, 0 };

	BUTTONDATA  btn_zero  = { 0 };
	BUTTONDATA  btn_exit  = gBtn_Exit;

	POINT ctrl_pos[] =
	{
		{ DLG_COLUMN1_X, DLG_ROW1_Y + STATIC_OFFSET },
		{ DLG_COLUMN1_X, DLG_ROW2_Y + STATIC_OFFSET },
		{ DLG_COLUMN2_X, DLG_ROW1_Y },
		{ DLG_COLUMN2_X, DLG_ROW2_Y },
		{ DLG_COLUMN1_X, DLG_ROW3_Y },
		{ DLG_WIDTH-EXIT_ICON_WIDTH - DLG_OFFSET, -(DLG_MENU_HIGHT + EXIT_ICON_HIGH) / 2 }
	};

	SIZE  ctrl_size[] = 
	{
		{ DLG_COLUMN1_W,	STATIC_HEIGHT   },
		{ DLG_COLUMN1_W,	STATIC_HEIGHT   },
		{ DLG_COLUMN2_W,	KEY_HEIGHT	  },
		{ DLG_COLUMN2_W,	KEY_HEIGHT	  },
		{ DLG_COLUMN2_W + DLG_COLUMN1_W,	KEY_HEIGHT	  },
		{ EXIT_ICON_WIDTH,  EXIT_ICON_HIGH  } 
	};

	CTRLDATA ctrl_data [] =
	{
		{ CTRL_STATIC,  WS_VISIBLE | SS_SIMPLE, WS_EX_NONE, 0, 0, 0, 0,
			IDC_FM_SETUP_THRESHOLD_VAL_L,  STR_DLG_FM_THRESHOLD,	   0L, 0L},
		{ CTRL_STATIC,  WS_VISIBLE | SS_SIMPLE, WS_EX_NONE, 0, 0, 0, 0,
			IDC_FM_SETUP_MOVEMENT_CAL_L,  STR_DLG_FM_MOVEMENTCAL,	   0L, 0L},

		{ CTRL_LISTBOX, WS_VISIBLE | WS_TABSTOP, WS_EX_NONE, 0, 0, 0, 0,
			IDC_FM_SETUP_THRESHOLD_VAL_LB,	0, 0L, 0L},
		{ CTRL_LISTBOX, WS_VISIBLE | WS_TABSTOP, WS_EX_NONE, 0, 0, 0, 0,
			IDC_FM_SETUP_MOVEMENT_CAL_LB,	0, 0L, 0L},

		{ CTRL_BUTTON,  WS_VISIBLE | WS_TABSTOP, WS_EX_NONE, 0, 0, 0, 0,
			IDC_FM_SETUP_MOVEMENT_ZERO_B,	STR_DLG_FM_MOVEMENT_ZERO, 0L, 0L},

		{ CTRL_BUTTON,  WS_VISIBLE | WS_TABSTOP | BS_ICON, WS_EX_NONE, 0, 0, 0, 0,
			IDC_FM_SETUP_EXIT_B,		 0, 0L, 0L} 
	};
	
	INT16 i, loops;
	loops = TABLESIZE(ctrl_data);
	WNDMEM   wndMem;
	
	wndMem.pMainWin = GetMainWndMem(IDD_FM_SETUP);
	wndMem.pControl = GetCtrlWndMem(IDC_FM_SETUP_FIRST);
	wndMem.ctrlNum  = TABLESIZE(ctrl_data);
	wndMem.task	 = SysGui_HTSK;
	
	dlg_data.controlnr = loops;
	dlg_data.controls  = ctrl_data;

	for(i = 0; i < loops; i++)
	{
		ctrl_data[i].x = ctrl_pos[i].x;
		ctrl_data[i].y = ctrl_pos[i].y;
		ctrl_data[i].w = ctrl_size[i].cx;
		ctrl_data[i].h = ctrl_size[i].cy;
	}
	SetCtrlDataAddData2(ctrl_data, loops, IDC_FM_SETUP_THRESHOLD_VAL_LB, (UINT32)&lb_val);
	SetCtrlDataAddData2(ctrl_data, loops, IDC_FM_SETUP_MOVEMENT_CAL_LB, (UINT32)&lb_calc);
	SetCtrlDataAddData2(ctrl_data, loops, IDC_FM_SETUP_MOVEMENT_ZERO_B, (UINT32)&btn_zero);
	SetCtrlDataAddData2(ctrl_data, loops, IDC_FM_SETUP_EXIT_B, (UINT32)&btn_exit);

	if (parent == MainScnHWnd)
		parent = 0;

	DialogBoxIndirectParam(&dlg_data, parent, IDD_TOCO_SETUP, FmSetupDlgProc, 0, &wndMem);
}

