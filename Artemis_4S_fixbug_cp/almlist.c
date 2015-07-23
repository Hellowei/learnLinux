
#include "includes.h"
#define ALMLIST_GLOBALS

ALM_INFO_LIST TechAlmInfoList = {0};
ALM_INFO_LIST PhysAlmInfoList = {0};

/*******************************************************************************
函数名称:DisplayAlmInfo
功能说明:在指定DC上显示指定的报警信息
输入参数:hdc:当前DC的句柄;pInfo:显示信息的储存地址;index:要显示信息的数组下标
调用函数:GetSystemFont GetFontHeight TextOut
其它说明:函数内报警信息缓存长度为固定分配，如果报警信息长度大于26字节，需增大数组
*******************************************************************************/
static VOID DisplayAlmInfo(HDC hdc, PALMLIST pInfo, INT16 index)
{
	PDC   pdc	= dc_HDC2PDC(hdc);
	INT16 height = RECTH(pdc->DevRC);
	INT16 width  = RECTW(pdc->DevRC);
	INT16 offset;
	INT16 i;
	INT16 j;
	INT16 id;
	INT16 ndx;
	//CHAR  szInfo[32];//如果报警信息长度大于26字节，需增大数组
	CHAR  szInfo[64]={0};//添加俄语后增大数组长度，panhonghui

	CHAR  szDate[12];
	CHAR  szTime[12];
	DATETIME time;
	//pdc->pLogFont = GetSystemFont(SYSLOGFONT_FIXED);
	pdc->pLogFont = GetSystemFont( SYSLOGFONT_SMAFONT);//phh

	offset = (STATIC_HEIGHT - GetFontHeight(hdc)) / 2;
	for (i = 0; i < ALARM_INFO_ITEM_NUM; i ++)
	{
		if (index < i)
		{
			if (ALARM_INFO_LIST_MAX > pInfo->count)
			{
				break;
			}
		}
		id  = (index - i + pInfo->count) % pInfo->count;
		ndx = pInfo->index - id;
		if (ndx <= 0)
			ndx += ALARM_INFO_LIST_MAX;
		snprintf(szInfo,sizeof(szInfo)-1, "%03d. %s", ndx, LoadString(pInfo->info[id].id));
		TextOut(hdc, 1, offset + i * STATIC_HEIGHT, szInfo);
	}
	pdc->pLogFont = GetSystemFont(SYSLOGFONT_DEFAULT);
	offset = STATIC_HEIGHT / 2;
	for (j = 0; j < i; j++)
	{
		id = (index - j + pInfo->count) % pInfo->count;
		time = pInfo->info[id].time;
		if (MonitorConfig.language == CHINESE)
		{
			sprintf(szDate, "%d-%02d-%02d", time.year, time.month, time.day);
		}
		else
		{
			sprintf(szDate, "%02d-%02d-%d", time.month, time.day, time.year);
		}
		sprintf(szTime, "%02d:%02d:%02d", time.hour, time.minute, time.second);
		TextOut(hdc, width - 72, j * STATIC_HEIGHT,szTime);
		TextOut(hdc, width - 81, j * STATIC_HEIGHT + offset,szDate);
	}
}

static VOID ShowAlmList(HWND hWnd, INT8 movepage, PALMLIST pInfo)
{
	SetWindowText(hWnd, 0);
	if (pInfo->count > 0)
	{
		INT16 page	  =  pInfo->page;
		INT16 pagemax   =  (pInfo->count - 1) / ALARM_INFO_ITEM_NUM;
		INT16 index;
		HDC   hdc;
		PDC   pdc;
		page += movepage;
		if (page < 0)
		{
			page = pagemax;
		}
		else if (page > pagemax)
		{
			page = 0;
		}
		index = pInfo->index - 1 - page * ALARM_INFO_ITEM_NUM + ALARM_INFO_LIST_MAX;
		index %= ALARM_INFO_LIST_MAX;
		
		hdc = GetDC(hWnd);
		pdc = dc_HDC2PDC(hdc);
		pdc->bkcolor   = GetWindowBkColor(hWnd);
		pdc->textcolor = GetWindowTextColor(hWnd);
        //printf("index=%d\n",index);

		DisplayAlmInfo(hdc, pInfo, index);
		ReleaseDC(hdc);
		pInfo->page = page;
	}
}

static INT32 AlmThListDlgProc(HANDLE hWnd, INT32 message, DWORD wParam, LPARAM lParam)
{
	HWND hCtrl;
	switch(message)
	{
		case MSG_INITDIALOG:
		{
			hCtrl = GetDlgItem(hWnd, IDC_ALARM_TECH_INFO_BOARD_L);
			if (hCtrl)
			{
				SetWindowBkColor(hCtrl, ((PCONTROL)hWnd)->iBkColor);

				SetWindowTextColor(hCtrl,
					GetWindowElementColor(WEC_EXCOLOR_BLACK));//WEC_EXCOLOR_PEACHPUFF
			}
			if (hCtrl = GetDlgItem(hWnd,IDC_ALARM_TECH_INFO_PAGEDN_B))
				SetWindowBkColor(hCtrl, ((PCONTROL)hWnd)->iBkColor);

			if (hCtrl = GetDlgItem(hWnd,IDC_ALARM_TECH_INFO_PAGEUP_B))
				SetWindowBkColor(hCtrl, ((PCONTROL)hWnd)->iBkColor);
		}
			break;

		case MSG_SHOWWINDOW:
			hCtrl = GetDlgItem(hWnd, IDC_ALARM_TECH_INFO_BOARD_L);
			if (hCtrl)
			{
				ShowAlmList(hCtrl, 0, &TechAlmInfoList);
			}
			break;

		case MSG_COMMAND:
			{
				hCtrl = GetDlgItem(hWnd, IDC_ALARM_TECH_INFO_BOARD_L);
				switch(LOWORD(wParam))
				{
					case IDC_ALARM_TECH_INFO_PAGEUP_B:
						if (TechAlmInfoList.page == 0)
						{
							EndDialog(hWnd, IDOK);
							break;
						}
						if (hCtrl)
						{
							ShowAlmList(hCtrl, -1, &TechAlmInfoList);
						}
						break;

					case IDC_ALARM_TECH_INFO_PAGEDN_B:
						if (hCtrl)
						{
							ShowAlmList(hCtrl, 1, &TechAlmInfoList);
						}
						break;
				}
				hCtrl = GetDlgItem(hWnd, IDC_ALARM_TECH_INFO_PAGEUP_B);
				if (!hCtrl) break;
				if (TechAlmInfoList.page == 0)
				{
					SetWindowText(hCtrl, STR_DLG_EXIT);
				}
				else
				{
					SetWindowText(hCtrl, STR_DLG_PAGE_UP);
				}
			}
			break;

		default:
			break;
	}
	return DefaultDialogProc (hWnd, message, wParam, lParam);
}


VOID AlarmThListDialog(HWND parent)
{
	BUTTONDATA btn_pgup = {IDI_PAGE_UP, 0, 0, 0};
	BUTTONDATA btn_pgdn = {IDI_PAGE_DN, 0, 0, 0};
	CTRLDATA ctrl_data[] = {
		{   CTRL_STATIC, SS_SIMPLE | WS_VISIBLE, WS_EX_NONE,
			DLG_OFFSET, DLG_OFFSET,270+DLG_ADD_W*2, (STATIC_HEIGHT+1)*ALARM_INFO_PAGE_MAX,
			IDC_ALARM_TECH_INFO_BOARD_L, STR_NULL, 0L, 0L	   },


		{   CTRL_BUTTON, WS_VISIBLE | WS_TABSTOP, WS_EX_NONE,
			DLG_OFFSET, (STATIC_HEIGHT+1)*(ALARM_INFO_PAGE_MAX+1), 130+DLG_ADD_W, KEY_HEIGHT,
			IDC_ALARM_TECH_INFO_PAGEDN_B, STR_DLG_PAGE_DOWN, 0L, 0L	  },
			
		{   CTRL_BUTTON, WS_VISIBLE | WS_TABSTOP, WS_EX_NONE,
			DLG_OFFSET + 130 + 10+DLG_ADD_W, (STATIC_HEIGHT+1)*(ALARM_INFO_PAGE_MAX+1), 130+DLG_ADD_W, KEY_HEIGHT,
			IDC_ALARM_TECH_INFO_PAGEUP_B, STR_DLG_EXIT, 0L, 0L	  },
	};
	DLGTEMPLATE dlg_data = {
		WS_ABSSCRPOS | WS_BORDER | WS_MODALDLG | WS_CAPTION, 0, 
		1, TOPBAR_HEIGHT, 300+DLG_ADD_W*2, 320,
		STR_DlG_TECH_ALM, 0, 0L, 0L
	};
	WNDMEM   wndMem;

	wndMem.pMainWin = GetMainWndMem(IDD_ALARM_TECH_INFO);
	wndMem.pControl = GetCtrlWndMem(IDC_ALARM_TECH_INFO_FIRST);
	wndMem.ctrlNum  = TABLESIZE(ctrl_data);
	wndMem.task	 = SysGui_HTSK;

	dlg_data.controls  = &ctrl_data[0];
	dlg_data.controlnr = TABLESIZE(ctrl_data);
	SetCtrlDataAddData2(ctrl_data, TABLESIZE(ctrl_data),
						IDC_ALARM_TECH_INFO_PAGEUP_B, (UINT32)&btn_pgup);
	SetCtrlDataAddData2(ctrl_data, TABLESIZE(ctrl_data),
						IDC_ALARM_TECH_INFO_PAGEDN_B, (UINT32)&btn_pgdn);
	DialogBoxIndirectParam(&dlg_data, parent, IDD_ALARM_TECH_INFO, 
							AlmThListDlgProc, 0, &wndMem);
}

static INT32 AlmPhListDlgProc(HANDLE hWnd, INT32 message, DWORD wParam, LPARAM lParam)
{
	HWND hCtrl;
	switch(message)
	{
		case MSG_INITDIALOG:
		{
			hCtrl = GetDlgItem(hWnd, IDC_ALARM_PHYS_INFO_BOARD_L);
			if (hCtrl)
			{
				SetWindowBkColor(hCtrl, ((PCONTROL)hWnd)->iBkColor);

				SetWindowTextColor(hCtrl,
					GetWindowElementColor(WEC_EXCOLOR_BLACK));
			}
			if (hCtrl = GetDlgItem(hWnd,IDC_ALARM_PHYS_INFO_PAGEDN_B))
				SetWindowBkColor(hCtrl, ((PCONTROL)hWnd)->iBkColor);
			if (hCtrl = GetDlgItem(hWnd,IDC_ALARM_PHYS_INFO_PAGEUP_B))
				SetWindowBkColor(hCtrl, ((PCONTROL)hWnd)->iBkColor);
		}
			break;

		case MSG_SHOWWINDOW:
			hCtrl = GetDlgItem(hWnd, IDC_ALARM_PHYS_INFO_BOARD_L);
			if (hCtrl)
			{
				ShowAlmList(hCtrl, 0, &PhysAlmInfoList);
			}
			break;

		case MSG_COMMAND:
			{
				hCtrl = GetDlgItem(hWnd, IDC_ALARM_PHYS_INFO_BOARD_L);
				switch(LOWORD(wParam))
				{
					case IDC_ALARM_PHYS_INFO_PAGEUP_B:
						if (PhysAlmInfoList.page == 0)
						{
							EndDialog(hWnd, IDOK);
							break;
						}
						if (hCtrl)
						{
							ShowAlmList(hCtrl, -1, &PhysAlmInfoList);
						}
						break;

					case IDC_ALARM_PHYS_INFO_PAGEDN_B:
						if (hCtrl)
						{
							ShowAlmList(hCtrl, 1, &PhysAlmInfoList);
						}
						break;
				}
				hCtrl = GetDlgItem(hWnd, IDC_ALARM_PHYS_INFO_PAGEUP_B);
				if (!hCtrl) break;
				if (PhysAlmInfoList.page == 0)
				{
					SetWindowText(hCtrl, STR_DLG_EXIT);
				}
				else
				{
					SetWindowText(hCtrl, STR_DLG_PAGE_UP);
				}
			}
			break;

		default:
			break;
	}
	return DefaultDialogProc (hWnd, message, wParam, lParam);
}


VOID AlarmPhListDialog(HWND parent)
{
	BUTTONDATA btn_pgup = {0};//{IDI_PAGE_UP, 0, 0, 0};
	BUTTONDATA btn_pgdn = {0};//{IDI_PAGE_DN, 0, 0, 0};
	CTRLDATA ctrl_data[] = {
		{   CTRL_STATIC, SS_SIMPLE | WS_VISIBLE, WS_EX_NONE,
			DLG_OFFSET, DLG_OFFSET, 320, STATIC_HEIGHT * ALARM_INFO_PAGE_MAX+10,
			IDC_ALARM_PHYS_INFO_BOARD_L, STR_NULL, 0L, 0L	   },


		{   CTRL_BUTTON,  WS_VISIBLE | WS_TABSTOP, WS_EX_NONE,
			DLG_OFFSET, STATIC_HEIGHT*(ALARM_INFO_PAGE_MAX+1)+10, 155, KEY_HEIGHT,
			IDC_ALARM_PHYS_INFO_PAGEDN_B, STR_DLG_PAGE_DOWN, 0L, 0L	  },
			
		{   CTRL_BUTTON,  WS_VISIBLE | WS_TABSTOP, WS_EX_NONE,
			DLG_OFFSET + 155 + 10, STATIC_HEIGHT*(ALARM_INFO_PAGE_MAX+1) + 10, 155, KEY_HEIGHT,
			IDC_ALARM_PHYS_INFO_PAGEUP_B, STR_DLG_EXIT, 0L, 0L	  },
	};
	DLGTEMPLATE dlg_data = {
		WS_ABSSCRPOS | WS_BORDER | WS_MODALDLG | WS_CAPTION, 0, 
		300, TOPBAR_HEIGHT, 350, 320,
		STR_DlG_PHYS_ALM, 0, 0L, 0L
	};
	WNDMEM   wndMem;

	wndMem.pMainWin = GetMainWndMem(IDD_ALARM_PHYS_INFO);
	wndMem.pControl = GetCtrlWndMem(IDC_ALARM_PHYS_INFO_FIRST);
	wndMem.ctrlNum  = TABLESIZE(ctrl_data);
	wndMem.task	 = SysGui_HTSK;

	dlg_data.controls  = &ctrl_data[0];
	dlg_data.controlnr = TABLESIZE(ctrl_data);
	SetCtrlDataAddData2(ctrl_data, TABLESIZE(ctrl_data),
						IDC_ALARM_PHYS_INFO_PAGEUP_B, (UINT32)&btn_pgup);
	SetCtrlDataAddData2(ctrl_data, TABLESIZE(ctrl_data),
						IDC_ALARM_PHYS_INFO_PAGEDN_B, (UINT32)&btn_pgdn);
	DialogBoxIndirectParam(&dlg_data, parent, IDD_ALARM_PHYS_INFO, 
							AlmPhListDlgProc, 0, &wndMem);
}

VOID AlmRecallNewPatient(VOID)
{

	if (	((HWND)GetTopWndItem(IDD_ALARM_TECH_INFO) != HWND_INVALID)
		||  ((HWND)GetTopWndItem(IDD_ALARM_PHYS_INFO) != HWND_INVALID)  )
	{
		BacktoMainScreen();
	}
	
//	int i;
//	
//	for ( i = 1; i <= STR_ALM_PHS_MAX - STR_ALM_PHS_FIRST; i++ )
//	{
//		TriggerAlarm2( 0x0000,  i + STR_ALM_PHS_FIRST - 1 );
//	}

//	for ( i = 1; i <= STR_ALM_TECH_MAX - STR_ALM_TECH_FIRST + 1; i++ )
//	{
//		TriggerAlarm2( 0x0000, i + STR_ALM_TECH_FIRST - 1 );
//	}

	ZeroMemory(&TechAlmInfoList, sizeof(TechAlmInfoList));

	ZeroMemory(&PhysAlmInfoList, sizeof(PhysAlmInfoList));
}

