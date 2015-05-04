/*******************************************************************************
* FILE		: listDlg.c
* Description	: 
*			  
* Copyright (c) 2014 by XXX. All Rights Reserved.
* 
* History:
* Version		Name       		Date			Description
   0.1			XXX			2014/03/31		Initial Version
   
*******************************************************************************/
#define  LISTDLG_GLOBALS
#include "includes.h"

#define LISTDLG_CHOICE_NUM (IDC_LIST_ITEMUP_B - IDC_LIST_FIRST)
static STRINGID *StringId;
static INT16 CurChoi, ChoiNum, PageNdx, PageMax;
static INT16 ListDlgItemId[10] = 
{
    IDC_LIST_ITEM0_B,
	IDC_LIST_ITEM1_B,
    IDC_LIST_ITEM2_B,
    IDC_LIST_ITEM3_B,
    IDC_LIST_ITEM4_B,
    IDC_LIST_ITEM5_B,
    IDC_LIST_ITEMUP_B,
    IDC_LIST_ITEMDN_B,
};

VOID SetListBoxDlgValue2(VOID)
{
	PageNdx = 0;
	PageMax = 1;
    if (ChoiNum > LISTDLG_CHOICE_NUM)
    {
		if (CurChoi > LISTDLG_CHOICE_NUM)
		{
			PageNdx = CurChoi / LISTDLG_CHOICE_NUM;
		}
		PageMax = ChoiNum / LISTDLG_CHOICE_NUM;
		if (ChoiNum % LISTDLG_CHOICE_NUM > 0)
			PageMax++;
	}
}

VOID SetListBoxDlgValueEx(RESID parent_id, RESID ctrl_id)
{
	GetListBoxString(parent_id, ctrl_id, &StringId,  &ChoiNum);
	CurChoi = GetListBoxCurChoi(parent_id, ctrl_id);
	SetListBoxDlgValue2();
}

VOID SetListBoxDlgValue(STRINGID * string, INT16 choi_num, INT16 cur_choi)
{
	StringId = string;
	ChoiNum = choi_num;
	CurChoi = cur_choi;
	SetListBoxDlgValue2();
}


INT32 GetListBoxDlgCurChoi(HWND hWnd)
{
	return CurChoi;
}

VOID SetListDlgUpDnCtrl(HWND hWnd)
{
	HWND hCtrl;
	if (hCtrl = GetDlgItem(hWnd, IDC_LIST_ITEMUP_B))
		EnableWindow(hCtrl, (PageNdx > 0));
	if (hCtrl = GetDlgItem(hWnd, IDC_LIST_ITEMDN_B))
		EnableWindow(hCtrl, (PageNdx < PageMax - 1));
}

VOID  ListBoxDlgShow(HWND hWnd, DWORD wParam, LPARAM lParam)
{
    HWND     hCtrl;
    PCONTROL pCtrl;
    int i = 0;
	int loops = ChoiNum;
	int target;
    wParam = wParam;
    lParam = lParam;

	SetListDlgUpDnCtrl(hWnd);
	if (loops > LISTDLG_CHOICE_NUM)
	{
		loops = LISTDLG_CHOICE_NUM;
	}
	
    for (i = 0; i < loops; ++ i)
    {
        pCtrl = GetSubCtrlItem(IDD_LIST, ListDlgItemId[i]);
		target = i + PageNdx * LISTDLG_CHOICE_NUM;
        if (CurChoi != target)
        {
            BUTTON_STATUS(pCtrl)  &= ~BST_MARKED;
        }
        else
        {
            BUTTON_STATUS(pCtrl)  |= BST_MARKED;
            SetFocus((HWND)pCtrl);
        }
		ShowWindow((HWND)pCtrl,(target < ChoiNum) ? SW_SHOW : SW_HIDE);
		
		if (target < ChoiNum)
		{
			SetWindowText((HWND)pCtrl, StringId[target]);
			ShowWindow((HWND)pCtrl, SW_SHOW);
		}
		else
		{
			ShowWindow((HWND)pCtrl, SW_HIDE);
		}
    }
}

INT32  ListBoxDlgProc(HANDLE hWnd, INT32 message, DWORD wParam, LPARAM lParam)
{
    HANDLE hCtrl;
    char *text, tbuf[32];
    int i, len, cur;
    
   
    switch (message) {
        case MSG_INITDIALOG:
//            ListBoxDlgInit(hWnd, wParam, lParam);
            break;

  	 case MSG_SHOWWINDOW: 
            ListBoxDlgShow(hWnd, wParam, lParam);
            break;
			
        case MSG_COMMAND: //系统菜单全部是按键,只有一种通知消息.
			switch (LOWORD(wParam)) 
			{
				case IDC_LIST_ITEMUP_B:
					if (PageNdx > 0)
						PageNdx--;
					SetListDlgUpDnCtrl(hWnd);
					ListBoxDlgShow(hWnd, wParam, lParam);
					break;

				case IDC_LIST_ITEMDN_B:
					if (PageNdx < PageMax - 1)
						PageNdx++;
					SetListDlgUpDnCtrl(hWnd);
					ListBoxDlgShow(hWnd, wParam, lParam);
					break;

				case IDC_LIST_ITEM0_B:
				case IDC_LIST_ITEM1_B:
				case IDC_LIST_ITEM2_B:		  	
				case IDC_LIST_ITEM3_B:
				case IDC_LIST_ITEM4_B:               	
				case IDC_LIST_ITEM5_B:
					CurChoi = LOWORD(wParam) - IDC_LIST_ITEM0_B
								+ PageNdx * LISTDLG_CHOICE_NUM;
					EndDialog (hWnd, IDOK);
					break;

				default:
					break;
			}
            return 0;

        default:
            break;
    }
    
    return DefaultDialogProc (hWnd, message, wParam, lParam);
}


/**
    系统设置菜单.
**/
DWORD  ListBoxDialog(HANDLE hOwner, STRINGID caption)
{
	enum _dlg_size_ 
	{
		LISTBOX_HALF_W = 100,
		LISTBOX_OFFSET = CTRL_HEIGHT, // ListBox中控件之间的间隔
		LISTBOX_WIDTH  = LISTBOX_HALF_W * 2 + DLG_OFFSET, // ListBox中控件的宽度
		DLG_GAP        = DLG_MENU_HIGHT, // 标题栏的高度
		DLG_WIDTH		= LISTBOX_WIDTH + DLG_OFFSET * 2
	};
	if (caption == 0)
	{
		caption = ((PWIN)hOwner)->caption;
		if (caption == 0)
			caption = ((PWIN)(((PWIN)hOwner)->hParent))->caption;
		if (caption == 0)
			return 0;
	}
	DLGTEMPLATE dlg_data = {
		WS_ABSSCRPOS | WS_CAPTION | WS_BORDER | WS_MODALDLG | WS_THICKFRAME, 0, 
		0, 0, DLG_WIDTH, 0,
		caption, 0,
		NULL, 0L,
	};

	BUTTONDATA btn_list[IDC_LIST_ITEMDN_B - IDC_LIST_FIRST + 1] = {0};
	CTRLDATA ctrl_data[] = 
	{
		{
			CTRL_BUTTON, WS_VISIBLE | WS_TABSTOP, WS_EX_NONE,
			DLG_OFFSET, DLG_OFFSET + LISTBOX_OFFSET * 0,
			LISTBOX_WIDTH, KEY_HEIGHT,
			IDC_LIST_ITEM0_B, 0, 0L, 0L}, //1
		{
			CTRL_BUTTON, WS_VISIBLE | WS_TABSTOP, WS_EX_NONE,
			DLG_OFFSET, DLG_OFFSET + LISTBOX_OFFSET * 1,
			LISTBOX_WIDTH, KEY_HEIGHT,
			IDC_LIST_ITEM1_B, 0, 0L, 0L}, //2
		{
			CTRL_BUTTON, WS_VISIBLE | WS_TABSTOP, WS_EX_NONE,
			DLG_OFFSET, DLG_OFFSET + LISTBOX_OFFSET * 2,
			LISTBOX_WIDTH, KEY_HEIGHT,
			IDC_LIST_ITEM2_B, 0, 0L, 0L}, //3
		{
			CTRL_BUTTON, WS_VISIBLE | WS_TABSTOP, WS_EX_NONE,
			DLG_OFFSET, DLG_OFFSET + LISTBOX_OFFSET * 3,
			LISTBOX_WIDTH, KEY_HEIGHT,
			IDC_LIST_ITEM3_B, 0, 0L, 0L}, //4
		{
			CTRL_BUTTON, WS_VISIBLE | WS_TABSTOP, WS_EX_NONE,
			DLG_OFFSET, DLG_OFFSET + LISTBOX_OFFSET * 4,
			LISTBOX_WIDTH, KEY_HEIGHT,
			IDC_LIST_ITEM4_B, 0, 0L, 0L}, //5
		{
			CTRL_BUTTON, WS_VISIBLE | WS_TABSTOP, WS_EX_NONE,
			DLG_OFFSET, DLG_OFFSET + LISTBOX_OFFSET * 5,
			LISTBOX_WIDTH, KEY_HEIGHT,
			IDC_LIST_ITEM5_B, 0, 0L, 0L}, //6
		{
			CTRL_BUTTON, WS_VISIBLE | WS_TABSTOP, WS_EX_NONE,
			DLG_OFFSET, DLG_OFFSET + LISTBOX_OFFSET * 6,
			LISTBOX_HALF_W, KEY_HEIGHT,
			IDC_LIST_ITEMUP_B, STR_DLG_PAGE_UP, 0L, 0L}, //7
		{
			CTRL_BUTTON, WS_VISIBLE | WS_TABSTOP, WS_EX_NONE,
			DLG_OFFSET * 2 + LISTBOX_HALF_W, DLG_OFFSET + LISTBOX_OFFSET * 6,
			LISTBOX_HALF_W, KEY_HEIGHT,
			IDC_LIST_ITEMDN_B, STR_DLG_PAGE_DOWN, 0L, 0L}, //8
	};

	INT16 i;
	INT16 nr = ChoiNum;
	INT16 target;
	if (nr > LISTDLG_CHOICE_NUM)
	{
		dlg_data.controlnr = LISTDLG_CHOICE_NUM + 2;
		dlg_data.h =
			DLG_OFFSET + LISTBOX_OFFSET * (LISTDLG_CHOICE_NUM + 1) + DLG_GAP;
		nr = dlg_data.controlnr;
	}
	else
	{
		dlg_data.controlnr = nr;
		dlg_data.h = DLG_OFFSET + LISTBOX_OFFSET * nr + DLG_GAP;
	}
	dlg_data.controls  = ctrl_data;

	WNDMEM wndMem;

	wndMem.pMainWin = GetMainWndMem(IDD_LIST);
	wndMem.pControl = GetCtrlWndMem(IDC_LIST_FIRST);
	wndMem.ctrlNum  = nr;
	wndMem.task     = SysGui_HTSK;

	for (i = 0; i < nr; ++ i)
	{
		//加入字符串
		target = i + PageNdx * LISTDLG_CHOICE_NUM;
		if (target < ChoiNum)
		{
			if (0 == ctrl_data[i].caption)
				ctrl_data[i].caption = StringId[target];
		}
		ctrl_data[i].dwAddData2 = (DWORD)&btn_list[i];
	}

	DWORD result = DialogBoxIndirectParam
		(&dlg_data, hOwner, IDD_LIST, ListBoxDlgProc, 0, &wndMem);
	return result;
}

INT32 OnTouchListbox(HWND hWnd, RESID parent, RESID ctrl, STRINGID strid)
{
	SetListBoxDlgValueEx(parent, ctrl);
	ListBoxDialog(hWnd, strid);
	SetListBoxCurChoi(parent, ctrl, GetListBoxDlgCurChoi(0));
	return GetListBoxCurChoi(parent, ctrl);
}



