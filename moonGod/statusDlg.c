
#include "includes.h"

#define SHOW_MIN_STATUS_NUM	 6
static UCHAR szStatusInfo[9][80]={ {'\0'} };
static BUTTONBMP sBtnBmp[9] = { {0} };
typedef struct _battery_status{
	UCHAR ACpower   :1;
	UCHAR charged1   :1;
	UCHAR charged2   :1;
	UCHAR nobatt1   :1;
	UCHAR nobatt2   :1;
	UCHAR batt1err  :1;
	UCHAR batt2err  :1;
	//UCHAR		   :0;
	UCHAR stat12V   :2;
	UCHAR stat5V	:2;
	UCHAR stat3V	:2;
	//UCHAR		   :0;
	UCHAR battery1;//
	UCHAR battery2;//
}BATTSTAT;

static BATTSTAT BatteryStatus;

extern VOID UpdateBatteryIcon(VOID);
// 获取交流电状态
BOOL GetACStatus(VOID)
{
	return BatteryStatus.ACpower;
}

// 获取电池充电状态
BOOL GetBattCharge(VOID)
{
	// 无电池直接返回False;
	if (BatteryStatus.nobatt1 && BatteryStatus.nobatt1)
	{
		return FALSE;
	}
	if (GetACStatus() && ((!BatteryStatus.nobatt1 && !BatteryStatus.charged1)
		||(!BatteryStatus.nobatt2 && !BatteryStatus.charged2)))
		return TRUE;
	return FALSE;
}

BOOL GetBattFull(VOID)
{
	// 无电池直接返回False;
	if (GetBattCharge())
		return FALSE;

	if (BatteryStatus.batt1err || BatteryStatus.batt2err)
		return FALSE;

	if (GetACStatus()
		&& ((BatteryStatus.battery1 == 4) || (BatteryStatus.battery2 == 4)))
		return TRUE;

	return FALSE;
}

BOOL GetBattErr(VOID)
{
	if (BatteryStatus.batt1err && BatteryStatus.batt2err)
		return TRUE;
	if (BatteryStatus.nobatt1 && BatteryStatus.nobatt2)
		return TRUE;
	return FALSE;
}

UINT8 GetBattElectricPower(VOID)
{
	int batt1 = -1;// 百分比换算 0~100,-1无效
	int batt2 = -1;// 百分比换算 0~100,-1无效
	UINT8 ret = 0;
	static INT8 cnt1 = 0;
	static INT8 cnt2 = 0;
	if (BatteryStatus.nobatt1 && BatteryStatus.nobatt2)//无电池状态
	{
		if (cnt1 != 0 || cnt2 != 0)
		{
			cnt1 = 0;
			cnt2 = 0;
		}
		ret = 0xFF;
		return ret;
	} 
	if (!BatteryStatus.nobatt1)//电池1在位
	{
		if (!BatteryStatus.batt1err)
		{
			if (!BatteryStatus.charged1 && BatteryStatus.ACpower) // 正在充电
			{
				cnt1++;
				if (BatteryStatus.battery1 + cnt1 > 4)
				{
					cnt1 = -1;
					if (BatteryStatus.battery1 == 0)
					{
						cnt1 = 0;
					}
				}
			}
			else	// 电池充满或电池供电,显示电池电量
			{
				cnt1 = 0;
			}
			batt1 = ((BatteryStatus.battery1 + cnt1) & 0x07) * 100L / 4;
		}
	} 
	if (!BatteryStatus.nobatt2)// 电池2在位
	{
		if (!BatteryStatus.batt2err)
		{
			if (BatteryStatus.charged2 && BatteryStatus.ACpower) // 正在充电
			{
				cnt2++;
				if (BatteryStatus.battery2 + cnt2 > 4)
				{
					cnt2 = -1;
					if (BatteryStatus.battery2 == 0)
					{
						cnt2 = 0;
					}
				}
			}
			else	// 电池充满或电池供电,显示电池电量
			{
				cnt2 = 0;
			}
			batt2 = ((BatteryStatus.battery2 + cnt2) & 0x07) * 100L / 4;
		}
	}
	if ((batt1 > 0 ) && (batt2 > 0))
	{
		ret = (UINT8)((batt1 + batt2) >> 1);
	}
	else
	{
		if (batt1 > 0)
		{
			ret = (UINT8)batt1;
		}
		if (batt2 > 0)
		{
			ret = (UINT8)batt2;
		}
	}
	return ret;
}

BOOL GetBatteryBmp(VOID)
{
	UCHAR night = MonitorConfig.nightModeOn;
	UCHAR *pBmp;
	UINT8 elect = GetBattElectricPower();
	static UINT8 old_elect = 0xEE;
	//prinfo("elect is %d\n", elect);
	if (old_elect != elect)
	{
		if (elect == 0xFF)
		{
			BmpCopy(batt_icon[night][3], batt_icon[night][0]);
		}
		else 
			if (elect < 16 && !GetBattCharge())// 低电量
		{
			BmpCopy(batt_icon[night][3], batt_icon[night][1]);
		}
		else
		{
			pBmp = ChangeBatteryBmpEx(elect);
			if (pBmp)
			{
				if (BmpCopy(batt_icon[night][3], pBmp) == FALSE)
				{
					printf("BmpCopy error\n");
				}
			}
		}
		old_elect = elect;
		return TRUE;
	}
	return FALSE;
}

INT32 GetSystemVolume(VOID)
{
	return MonitorConfig.kbVol;
}

INT32 GetAlarmVolume(VOID)
{
	return MonitorConfig.alarmVolume;
}

INT32 GetFhrVolume(VOID)
{
	return FhrConfig.volume;
}

INT32 GetPrinterStatus(VOID)
{
	return RecConfig.recstatus;
}

VOID PutStatusInfoString(UINT8 index, UCHAR *str, PBUTTONBMP pbmp)
{
	if (index < TABLESIZE(szStatusInfo))
	{
		strcpy((char*)szStatusInfo[index], (char*)str);
	}
	if (index < TABLESIZE(sBtnBmp))
	{
		sBtnBmp[index].release  = pbmp->release;
		sBtnBmp[index].pass	 = pbmp->pass;
		sBtnBmp[index].press	= pbmp->press;
		sBtnBmp[index].down	 = pbmp->down;
	}
	
}

VOID PutStatusInfoStr_ID(UINT8 index, STRINGID str_id, PBUTTONBMP pbmp)
{
	PutStatusInfoString(index, (UCHAR*)LoadString(str_id), pbmp);
}

VOID SetStatusDlgItem(VOID)
{
	BUTTONBMP btnbmp;
	INT32 strInfoID;
	UINT8 index = 0;
	strInfoID = STR_DLG_STATUS_INFO1;

	if (1)
	{
		if (GetACStatus())
			strcpy(LoadString(strInfoID), LoadString(STR_DLG_STATUS_AC));
		else
			strcpy(LoadString(strInfoID), LoadString(STR_DLG_STATUS_DC));
		btnbmp.release = ac_icon[MonitorConfig.nightModeOn];
		btnbmp.pass	= btnbmp.release;
		PutStatusInfoStr_ID(index, strInfoID++, &btnbmp);
		index++;
	}
	if (1)  // 总是显示电池状态
	{
		if (GetBattCharge())		// 正在充电
		{
			btnbmp.release = batt_icon[MonitorConfig.nightModeOn][3];
			btnbmp.pass	= btnbmp.release;
			strcpy(LoadString(strInfoID), LoadString(STR_DLG_STATUS_CHARGING));
			PutStatusInfoStr_ID(index, strInfoID++, &btnbmp);
		}
		else if (GetBattFull())		// 电池充满
		{
			btnbmp.release = batt_icon[MonitorConfig.nightModeOn][3];
			btnbmp.pass	= btnbmp.release;
			strcpy(LoadString(strInfoID), LoadString(STR_DLG_STATUS_FULLCHARGED));
			PutStatusInfoStr_ID(index, strInfoID++, &btnbmp);
		}
		else if (GetBattErr())		// 无电池/电池故障
		{
			btnbmp.release = batt_icon[MonitorConfig.nightModeOn][0];
			btnbmp.pass	= btnbmp.release;
			strcpy(LoadString(strInfoID), LoadString(STR_DLG_STATUS_NOBATT));
			PutStatusInfoStr_ID(index, strInfoID++, &btnbmp);
		}
		else						// 电池供电
		{
			btnbmp.release = batt_icon[MonitorConfig.nightModeOn][3];
			btnbmp.pass	= btnbmp.release;
			strcpy(LoadString(strInfoID), LoadString(STR_DLG_STATUS_BATTPOWER));
			PutStatusInfoStr_ID(index, strInfoID++, &btnbmp);
		}
		index++;
	}
	if (1)  // 总是显示网络状态
	{
		int ret = SetNetStatus();
		STRINGID str[2] =
			{ STR_DLG_STATUS_NETWORKDISCONN, STR_DLG_STATUS_NETWORKRUNNING };
		btnbmp.release = pNetIcon;
		strcpy(LoadString(strInfoID), LoadString(str[ret == 1]));
		btnbmp.pass	= btnbmp.release;
		PutStatusInfoStr_ID(index, strInfoID++, &btnbmp);
		index++;
	}
	if (1)  // 总是显示打印机状态
	{
		btnbmp.release = print_icon[MonitorConfig.nightModeOn];
		btnbmp.pass	= btnbmp.release;
		if(!GetPrinterStatus())
			strcpy(LoadString(strInfoID), LoadString(STR_DLG_STATUS_PRINTER));
		else if (PRINT_RTN_PAPER == GetPrinterStatus())
			strcpy(LoadString(strInfoID), LoadString(STR_ALM_PRINTER_PAPER_OUT));
		else if (PRINT_RTN_OPEN == GetPrinterStatus())
			strcpy(LoadString(strInfoID), LoadString(STR_ALM_PRINTER_DOOR_NOT_CLOSED));
		PutStatusInfoStr_ID(index, strInfoID++, &btnbmp);
		index++;
	}
	if (1)  // 总是显示胎心音量
	{
		btnbmp.release = GetFetalHearIcon();
		btnbmp.pass	= btnbmp.release;
		sprintf(LoadString(strInfoID), "%s:%d", LoadString(STR_DLG_FHR_VOLUME),
			FhrConfig.volume);
		PutStatusInfoStr_ID(index, strInfoID++, &btnbmp);
		index++;
	}
	if (1)  // 总是显示报警静音状态图标
	{
		btnbmp.release = alm_icon[MonitorConfig.nightModeOn];
		btnbmp.pass	= btnbmp.release;
		if(ON == MonitorConfig.alarmSoundOn)
			strcpy(LoadString(strInfoID), LoadString(STR_DLG_STATUS_ALARM));
		else
			strcpy(LoadString(strInfoID), LoadString(STR_MAIN_BOTTOM_SILENCE));
		PutStatusInfoStr_ID(index, strInfoID++, &btnbmp);
		index++;
	}
}

static INT32
StatusDlgProc(HANDLE hWnd, INT32 message, DWORD wParam, LPARAM lParam)
{
	switch (message) {
		case MSG_INITDIALOG:
			{
				int i;
				HWND hCtrl;
				PWIN pWin = (PWIN)hWnd;
				SetStatusDlgItem();
				for (i = IDC_STATUS_INFO_ICON1_B; i < IDC_STATUS_INFO_EXIT_B; i++)
				{
					hCtrl = GetDlgItem(hWnd, i);
					if (((PCONTROL)hCtrl)->dwAddData2)
					{
						//BUTTONDATAP pbtn = ((PCONTROL)hCtrl)->dwAddData2;
						//pbtn = *((PBUTTONBMP)pbtn->data);
						//EnableWindow(hCtrl, btnbmp.release && btnbmp.pass);
						EnableWindow(hCtrl, FALSE);
					}
					else
					{
						EnableWindow(hCtrl, FALSE);
					}
				}
				for (i = IDC_STATUS_INFO_INFO1_L; i < IDC_STATUS_INFO_ICON1_B; i++)
				{
					hCtrl = GetDlgItem(hWnd, i);
					SetWindowBkColor(hCtrl, pWin->iBkColor);
				}
			}
			break;

		case MSG_COMMAND:
			EndDialog(hWnd, IDOK);
			return 0;
			/**
			switch (LOWORD(wParam))
			{
				case IDC_STATUS_INFO_EXIT_B:
					EndDialog(hWnd, IDOK);
					return 0;

				case IDC_STATUS_INFO_ICON1_B:
				case IDC_STATUS_INFO_ICON2_B:
				case IDC_STATUS_INFO_ICON3_B:
				case IDC_STATUS_INFO_ICON4_B:
				case IDC_STATUS_INFO_ICON5_B:
				case IDC_STATUS_INFO_ICON6_B:
					//guiOnKeyMenu();
					break;

				default:
					break;
			}
			**/

		default:
			break;
	}
	return DefaultDialogProc (hWnd, message, wParam, lParam);
}

VOID StatusDialog(HWND parent)
{
	BUTTONDATA btn[] = {
		{(INT32)&sBtnBmp[0], 0, 0, 0 },
		{(INT32)&sBtnBmp[1], 0, 0, 0 },
		{(INT32)&sBtnBmp[2], 0, 0, 0 },
		{(INT32)&sBtnBmp[3], 0, 0, 0 },
		{(INT32)&sBtnBmp[4], 0, 0, 0 },
		{(INT32)&sBtnBmp[5], 0, 0, 0 },
		{(INT32)&sBtnBmp[6], 0, 0, 0 },
		{(INT32)&sBtnBmp[7], 0, 0, 0 },
		{(INT32)&sBtnBmp[8], 0, 0, 0 },
		{0, 0, 0, 0 }
	};
	
	CTRLDATA	 ctrl_data [] =  {
		{   CTRL_STATIC, WS_VISIBLE | SS_LEFTNOWORDWRAP, WS_EX_NONE,
			40, DLG_OFFSET + KEY_HEIGHT * 0, 120, KEY_HEIGHT - 2,
			IDC_STATUS_INFO_INFO1_L,  STR_DLG_STATUS_INFO1, 0L, 0L},

		{   CTRL_STATIC, WS_VISIBLE | SS_LEFTNOWORDWRAP, WS_EX_NONE,
			40, DLG_OFFSET + KEY_HEIGHT * 1, 120, KEY_HEIGHT - 2,
			IDC_STATUS_INFO_INFO2_L,  STR_DLG_STATUS_INFO2, 0L, 0L},

		{   CTRL_STATIC, WS_VISIBLE | SS_LEFTNOWORDWRAP, WS_EX_NONE,
			40, DLG_OFFSET + KEY_HEIGHT * 2, 120, KEY_HEIGHT - 2,
			IDC_STATUS_INFO_INFO3_L,  STR_DLG_STATUS_INFO3, 0L, 0L},

		{   CTRL_STATIC, WS_VISIBLE | SS_LEFTNOWORDWRAP, WS_EX_NONE,
			40, DLG_OFFSET + KEY_HEIGHT * 3, 120, KEY_HEIGHT - 2,
			IDC_STATUS_INFO_INFO4_L,  STR_DLG_STATUS_INFO4, 0L, 0L},

		{   CTRL_STATIC, WS_VISIBLE | SS_LEFTNOWORDWRAP, WS_EX_NONE,
			40, DLG_OFFSET + KEY_HEIGHT * 4, 120, KEY_HEIGHT - 2,
			IDC_STATUS_INFO_INFO5_L,  STR_DLG_STATUS_INFO5, 0L, 0L},

		{   CTRL_STATIC, WS_VISIBLE | SS_LEFTNOWORDWRAP, WS_EX_NONE,
			40, DLG_OFFSET + KEY_HEIGHT * 5, 120, KEY_HEIGHT - 2,
			IDC_STATUS_INFO_INFO6_L,  STR_DLG_STATUS_INFO6, 0L, 0L},

		{
			CTRL_BUTTON, WS_VISIBLE | WS_TABSTOP | BS_BITMAP, WS_EX_NONE,
			DLG_OFFSET, DLG_OFFSET + KEY_HEIGHT * 0, 24, 24,
			IDC_STATUS_INFO_ICON1_B, STR_DLG_EXIT, 0L, (DWORD)&btn[0]
		},

		{
			CTRL_BUTTON, WS_VISIBLE | WS_TABSTOP | BS_BITMAP, WS_EX_NONE,
			DLG_OFFSET, DLG_OFFSET + KEY_HEIGHT * 1, 24, 24,
			IDC_STATUS_INFO_ICON2_B, STR_DLG_EXIT, 0L, (DWORD)&btn[1]
		},

		{
			CTRL_BUTTON, WS_VISIBLE | WS_TABSTOP | BS_BITMAP, WS_EX_NONE,
			DLG_OFFSET, DLG_OFFSET + KEY_HEIGHT * 2, 24, 24,
			IDC_STATUS_INFO_ICON3_B, STR_DLG_EXIT, 0L, (DWORD)&btn[2]
		},

		{
			CTRL_BUTTON, WS_VISIBLE | WS_TABSTOP | BS_BITMAP, WS_EX_NONE,
			DLG_OFFSET, DLG_OFFSET + KEY_HEIGHT * 3, 24, 24,
			IDC_STATUS_INFO_ICON4_B, STR_DLG_EXIT, 0L, (DWORD)&btn[3]
		},

		{
			CTRL_BUTTON, WS_VISIBLE | WS_TABSTOP | BS_BITMAP, WS_EX_NONE,
			DLG_OFFSET, DLG_OFFSET + KEY_HEIGHT * 4, 24, 24,
			IDC_STATUS_INFO_ICON5_B, STR_DLG_EXIT, 0L, (DWORD)&btn[4]
		},

		{
			CTRL_BUTTON, WS_VISIBLE | WS_TABSTOP | BS_BITMAP, WS_EX_NONE,
			DLG_OFFSET, DLG_OFFSET + KEY_HEIGHT * 5, 24, 24,
			IDC_STATUS_INFO_ICON6_B, STR_DLG_EXIT, 0L, (DWORD)&btn[5]
		},

		{
			CTRL_BUTTON, WS_VISIBLE | WS_TABSTOP, WS_EX_NONE,
			DLG_OFFSET, DLG_OFFSET + KEY_HEIGHT * 6, 145, KEY_HEIGHT,
			IDC_STATUS_INFO_EXIT_B, STR_DLG_EXIT, 0L, (DWORD)&btn[9]
		}
	};
	ctrl_data[0].dwAddData2 = (DWORD)&btn[9];
	DLGTEMPLATE dlg_data = {
		WS_ABSSCRPOS | WS_BORDER | WS_MODALDLG, 0, 
		SCREEN_WIDTH - 176, TOPBAR_HEIGHT, 175, KEY_HEIGHT * 7 + DLG_OFFSET * 2,
		STR_AUTO, 0, ctrl_data, 0L
	};
	WNDMEM   wndMem;

	wndMem.pMainWin = GetMainWndMem(IDD_STATUS_INFO);
	wndMem.pControl = GetCtrlWndMem(IDC_STATUS_INFO_FIRST);
	wndMem.ctrlNum  = TABLESIZE(ctrl_data);
	wndMem.task	 = SysGui_HTSK;

	dlg_data.controls  = ctrl_data;
	dlg_data.controlnr = TABLESIZE(ctrl_data);
	DialogBoxIndirectParam(&dlg_data, parent, IDD_STATUS_INFO,
							StatusDlgProc, 0, &wndMem);
}

VOID BatteryVoltageAlarm(VOID)
{
	 if (BatteryStatus.batt1err || BatteryStatus.batt2err)
	{
		prinfo("BatteryVoltageAlarm::BatteryStatus::Battery error!\r\n");
		return;
	}

	if (   BatteryStatus.stat5V  < 3 
		&& BatteryStatus.stat12V < 3 
		&& BatteryStatus.stat3V  < 3)
	{
		TriggerAlarm((BatteryStatus.stat5V & 0x01) > 0,
			STR_ALM_POWER_5V_TOO_HIGH);
		TriggerAlarm((BatteryStatus.stat5V & 0x02) > 0,
			STR_ALM_POWER_5V_TOO_LOW);
		TriggerAlarm((BatteryStatus.stat12V & 0x01) > 0,
			STR_ALM_POWER_12V_TOO_HIGH);
		TriggerAlarm((BatteryStatus.stat12V & 0x02) > 0,
			STR_ALM_POWER_12V_TOO_LOW);
		TriggerAlarm((BatteryStatus.stat3V & 0x01) > 0,
			STR_ALM_POWER_3V_TOO_HIGH);
		TriggerAlarm((BatteryStatus.stat3V & 0x02) > 0,
			STR_ALM_POWER_3V_TOO_LOW);
	}
	if (FALSE == GetACStatus() && 0 == GetBattElectricPower())
	{
		TriggerAlarm(TRUE, STR_ALM_POWER_BATTERY_LOW);
	}
	else
	{
		TriggerAlarm(FALSE, STR_ALM_POWER_BATTERY_LOW);
	}
	
	if (GetBatteryBmp())
		UpdateBatteryIcon();
}

VOID PutBatteryStatus(UINT8 BattVol1, UINT8 BattVol2, UINT8 BattStat)
{
	BatteryStatus.ACpower   = ((BattStat & 0x40) >> 6);
	BatteryStatus.charged1  = ((BattStat & 0x20) >> 5);
	BatteryStatus.charged2  = ((BattStat & 0x10) >> 4);
	BatteryStatus.nobatt1   = ((BattStat & 0x04) >> 2);
	BatteryStatus.nobatt2   = ((BattStat & 0x01) >> 0);
	BatteryStatus.batt1err  = ((BattStat & 0x08) >> 3);
	BatteryStatus.batt2err  = ((BattStat & 0x02) >> 1);
	BatteryStatus.stat12V   = ((BattVol1 & 0x18) >> 3);
	BatteryStatus.stat5V	= ((BattVol1 & 0x60) >> 5);
	BatteryStatus.stat3V	= ((BattVol2 & 0x18) >> 3);
	BatteryStatus.battery1  = ( BattVol1 & 0x07	  );
	BatteryStatus.battery2  = ( BattVol2 & 0x07	  );
//	printf("BatteryStatus.ACpower	is %s\n",	BatteryStatus.ACpower	? "True" : "False");
//	printf("BatteryStatus.charged1	is %s\n",	BatteryStatus.charged1	? "True" : "False");
//	printf("BatteryStatus.charged2	is %s\n",	BatteryStatus.charged2	? "True" : "False");
//	printf("BatteryStatus.nobatt1	is %s\n",	BatteryStatus.nobatt1	? "True" : "False");
//	printf("BatteryStatus.nobatt2	is %s\n",	BatteryStatus.nobatt2	? "True" : "False");
//	printf("BatteryStatus.batt1err	is %s\n",	BatteryStatus.batt1err	? "True" : "False");
//	printf("BatteryStatus.batt2err	is %s\n",	BatteryStatus.batt2err	? "True" : "False");
//	printf("BatteryStatus.stat12V	is %s\n",	BatteryStatus.stat12V	? "True" : "False");
//	printf("BatteryStatus.stat5V	is %s\n",	BatteryStatus.stat5V	? "True" : "False");
//	printf("BatteryStatus.stat3V	is %s\n",	BatteryStatus.stat3V	? "True" : "False");
//	printf("BatteryStatus.battery1	is %s\n",	BatteryStatus.battery1	? "True" : "False");
//	printf("BatteryStatus.battery2	is %s\n",	BatteryStatus.battery2	? "True" : "False");
	// 无电池时无效
	if (BatteryStatus.nobatt1 || BatteryStatus.batt1err)
	{
		BatteryStatus.battery1 = INVALID_PARAM;
	}
	if (BatteryStatus.nobatt2 || BatteryStatus.batt2err)
	{
		BatteryStatus.battery2 = INVALID_PARAM;
	}
	BatteryVoltageAlarm();
}

