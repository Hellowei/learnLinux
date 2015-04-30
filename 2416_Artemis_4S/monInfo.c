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
#define   MONINFO_GLOBALS 
#include  "includes.h"

VOID UpdateAlmVolIcon(VOID)
{
	HWND hMainCtrl;
	HWND hDlgCtrl;
	HWND hDlgInfo;
	
	hMainCtrl = GetDlgItem(MainScnHWnd, IDC_TOPBAR_STATUS_AVOL_L);
	hDlgCtrl = (HWND)GetSubCtrlItem(IDD_STATUS_INFO, IDC_STATUS_INFO_ICON6_B);
	hDlgInfo = (HWND)GetSubCtrlItem(IDD_STATUS_INFO, IDC_STATUS_INFO_INFO6_L);
	
	if(OFF == MonitorConfig.alarmSoundOn)
	{
		if (hMainCtrl)
		{
			SetWindowItem(hMainCtrl, (DWORD)alm_icon[MonitorConfig.nightModeOn]);
		}
		if (hDlgCtrl)
		{
			SetWindowText(hDlgCtrl, 0);
		}
		if (hDlgInfo)
		{
			SetWindowText(hDlgInfo, STR_MAIN_BOTTOM_SILENCE);
		}
	}
	else
	{
		if (hMainCtrl)
		{
			SetWindowItem(hMainCtrl, 0);
		}
		if (hDlgCtrl)
		{
			SetWindowText(hDlgCtrl, 0);
		}
		if (hDlgInfo)
		{
			SetWindowText(hDlgInfo, STR_DLG_STATUS_ALARM);
		}
	}
}

VOID UpdateFhrVolIcon(VOID)
{
	HWND hMainCtrl;
	HWND hDlgCtrl;
	HWND hDlgInfo;
	
	hMainCtrl = GetDlgItem(MainScnHWnd, IDC_TOPBAR_STATUS_FVOL_L);
	hDlgCtrl = (HWND)GetSubCtrlItem(IDD_STATUS_INFO, IDC_STATUS_INFO_ICON5_B);
	hDlgInfo = (HWND)GetSubCtrlItem(IDD_STATUS_INFO, IDC_STATUS_INFO_INFO5_L);
	
	if (hMainCtrl)
	{
		SetWindowItem(hMainCtrl, (UINT32)GetFetalHearIcon());
	}
	if (hDlgCtrl)
	{
		SetWindowText(hDlgCtrl, 0);
	}
	if (hDlgInfo)
	{
		sprintf(LoadString(STR_DLG_STATUS_INFO5), "%s:%d",
			LoadString(STR_DLG_FHR_VOLUME),	FhrConfig.volume);
		SetWindowText(hDlgInfo, STR_DLG_STATUS_INFO5);
	}
}

VOID UpdatePrinterIcon(VOID)
{
	HWND hMainCtrl  = 0;
	HWND hDlgWnd	= 0;
	HWND hDlgCtrl   = 0;
	HWND hDlgInfo   = 0;
	
	hMainCtrl = GetDlgItem(MainScnHWnd, IDC_TOPBAR_STATUS_REC_L);
	hDlgWnd = (HWND)GetTopWndItem(IDD_STATUS_INFO);
	if (hDlgWnd != HWND_INVALID)
	{
		hDlgCtrl = GetDlgItem(hDlgWnd, IDC_STATUS_INFO_ICON4_B);
		hDlgInfo = GetDlgItem(hDlgWnd, IDC_STATUS_INFO_INFO4_L);
	}
	if(!GetPrinterStatus())
	{
		if (hMainCtrl)
		{
			SetWindowItem(hMainCtrl, (DWORD)print_icon[MonitorConfig.nightModeOn]);
		}
		if (hDlgCtrl)
		{
			SetWindowText(hDlgCtrl, 0);
		}
		if (hDlgInfo)
		{
			SetWindowText(hDlgInfo, STR_DLG_STATUS_PRINTER);
		}
	}
	else
	{
		if (hMainCtrl)
		{
			SetWindowItem(hMainCtrl, (DWORD)noprint_icon[MonitorConfig.nightModeOn]);
		}
		if (hDlgCtrl)
		{
			SetWindowText(hDlgCtrl, 0);
		}
		if (hDlgInfo)
		{
			if (PRINT_RTN_PAPER == GetPrinterStatus())
				SetWindowText(hDlgInfo, STR_ALM_PRINTER_PAPER_OUT);
			if (PRINT_RTN_OPEN == GetPrinterStatus())
				SetWindowText(hDlgInfo, STR_ALM_PRINTER_DOOR_NOT_CLOSED);
		}
	}
}

VOID UpdateNetworkIcon(VOID)
{
	HWND hMainCtrl  = 0;
	HWND hDlgWnd	= 0;
	HWND hDlgCtrl   = 0;
	HWND hDlgInfo   = 0;
	
	hMainCtrl = GetDlgItem(MainScnHWnd, IDC_TOPBAR_STATUS_NET_L);
	hDlgWnd = (HWND)GetTopWndItem(IDD_STATUS_INFO);
	if (hDlgWnd != HWND_INVALID)
	{
		hDlgCtrl = GetDlgItem(hDlgWnd, IDC_STATUS_INFO_ICON3_B);
		hDlgInfo = GetDlgItem(hDlgWnd, IDC_STATUS_INFO_INFO3_L);
	}
	if (hMainCtrl)
	{
		SetWindowItem(hMainCtrl, (DWORD)pNetIcon);
	}
	if (hDlgCtrl)
	{
		SetWindowText(hDlgCtrl, 0);
	}
	if (hDlgInfo)
	{
		SetWindowText(hDlgInfo, STR_DLG_STATUS_INFO3);
	}
}

VOID UpdateBatteryIcon(VOID)
{
	HWND hMainCtrl;
	HWND hDlgCtrl;
	HWND hDlgInfo;
	
	hMainCtrl = GetDlgItem(MainScnHWnd, IDC_TOPBAR_STATUS_BAT_L);
	hDlgCtrl = (HWND)GetSubCtrlItem(IDD_STATUS_INFO, IDC_STATUS_INFO_ICON2_B);
	hDlgInfo = (HWND)GetSubCtrlItem(IDD_STATUS_INFO, IDC_STATUS_INFO_INFO2_L);
	
    //printf("UpdateBatteryIcon::hMainCtrl 0x%X\n", hMainCtrl);
	if (hMainCtrl)
	{
        DWORD addData2 = (DWORD)batt_icon[MonitorConfig.nightModeOn][3];
		if (GetBattErr())		// 无电池/电池故障
		{
			addData2 = (DWORD)batt_icon[MonitorConfig.nightModeOn][0];
		}
		SetWindowItem(hMainCtrl, addData2);
	}
	if (hDlgCtrl)
	{
		SetWindowText(hDlgCtrl, 0);
	}
	if (hDlgInfo)
	{
		SetWindowText(hDlgInfo, STR_DLG_STATUS_INFO2);
	}
}

VOID UpdateACIcon(VOID)
{
	HWND hMainCtrl;
	HWND hDlgCtrl;
	HWND hDlgInfo;
	
	hMainCtrl = GetDlgItem(MainScnHWnd, IDC_TOPBAR_STATUS_AC_L);
	hDlgCtrl = (HWND)GetSubCtrlItem(IDD_STATUS_INFO, IDC_STATUS_INFO_ICON1_B);
	hDlgInfo = (HWND)GetSubCtrlItem(IDD_STATUS_INFO, IDC_STATUS_INFO_INFO1_L);
	
	if(GetACStatus())
	{
		if (hMainCtrl)
		{
			SetWindowItem(hMainCtrl, (DWORD)ac_icon[MonitorConfig.nightModeOn]);
		}
		if (hDlgCtrl)
		{
			SetWindowText(hDlgCtrl, 0);
		}
		if (hDlgInfo)
		{
			SetWindowText(hDlgInfo, STR_DLG_STATUS_INFO1);
		}
	}
	else
	{
		if (hMainCtrl)
		{
			SetWindowItem(hMainCtrl, 0);
		}
		if (hDlgCtrl)
		{
			SetWindowText(hDlgCtrl, 0);
		}
		if (hDlgInfo)
		{
			SetWindowText(hDlgInfo, STR_DLG_STATUS_INFO1);
		}
	}
}

