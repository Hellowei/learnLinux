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
#define   PATIENT_GLOBALS 
#include "includes.h"

STRINGID gPatientSex[] = {0};

STRINGID gPatientType[] ={0};

static PRE_TABS sPtnList[DATA_SAVE_MAX] = { 0 };
static INT8 sCurrFile = 0;

VOID InitParaForNewPatient(VOID){;}



VOID ClearAllAlmForNewPatient(VOID)
{
	 int	i;
	
	 for(i = 0; i < MID_MAX; i++) {
		if (MonitorConfig.moduleInfo[i].OnLine == TRUE )
			ClearAllAlarm(MonitorConfig.moduleInfo[i].Id);
	 }
}



VOID  NewPatient (VOID)
{
   int		 i;
   STATUS	  Taskstat;
   
   //NU_Change_Preemption(NU_NO_PREEMPT);
   
   //禁止波形显示刷新
#if _ENB_WAVE_DRIVE > 0
   //清除所有的波形
	EraseWaves();
#endif
	//终止打印
#if _ENB_REC_FUNC
	RecordService(REC_STOP);
#endif
	//清除所有的波形缓存
	EraseWavesBuffer();

   //所有参数置为无效值
   InitParaForNewPatient();

   //清除评分缓存数据
   InitDiagnoseData();

   //清除所有参数的趋势
   //InitTrendData(0);

   //清除NIBP的测量结果数据
   //NibpRecallNewPatient();

   //清除报警事件
   AlmRecallNewPatient();

   //清除心律失常事件数据
   //ReInitArrEvent();

   //清除趋势共存界面的趋势数据

   //清除NIBP测量信息
   //ResetMeasureForNewPatient();

   //病人信息设置为默认值
   InitNewPatientInfo();

   //清除所有参数报警和技术报警
   ClearAllAlmForNewPatient();
   
   // 更新病人后3秒内产生的传感器报警为提示信息
   SetSensorStatus(0, -3);

   SetParamStatus(0, FALSE);

   //NU_Change_Preemption(NU_PREEMPT);
}


VOID  ShowPatientType (VOID)
{}


VOID  ShowPatientBedNo (VOID)
{}

static VOID DoAfterPatientTypeChange(VOID)
{
	// 更新病人类型
	ShowPatientType();
	return;
}


/************************************************************************/
/*  函数名：Patient_ChangeType										  */
/*  描述：  改变病人类型的函数										  */
/*  参数：  无														  */
/*  返回值：无														  */
/************************************************************************/
static VOID  Patient_ChangeType (VOID)
{
	INT16		   i;
	// 调用缺省配置
	switch (MonitorConfig.patientType)  
	{
		case PATIENT_ADULT:
			//Load_Default_Adult_Config( PARA_BLOCK_ALL );
			break;
			
		case PATIENT_PEDIATRIC:
			//Load_Default_Ped_Config( PARA_BLOCK_ALL );
			break;
			
		default:
			break;
	}
	// 保存设置
	//Save_Config(SAVE_ALLINFO, 0);
	DoAfterPatientTypeChange();
	
	return;
}

VOID  InitNewPatientInfo (VOID)
{
	//INT16		   i;
	
	ZeroMemory(&PatientInfo, sizeof(PatientInfo));

	//MonitorConfig.bloodType   = BLOOD_INVALID;
	//MonitorConfig.patientType = PATIENT_ADULT;

	//Patient_ChangeType();

	MonitorConfig.bedNo = BEDNO_INVALID;

	FhrParams.fm = 0;

	*LoadString(STR_MAIN_TOPBAR_NAME_NAME) = '\0';
	*LoadString(STR_MAIN_TOPBAR_ID_NUM) = '\0';

	// 显示床号
	//ShowPatientBedNo();

	return;
}

VOID SetIpAddress(INT16 bedno)
{
	char tbuf[128];
	strcpy(tbuf, "ifconfig eth0 200.200.200.0 > /tmp/status");

	if (BEDNO_INVALID != bedno)
	{
		sprintf(tbuf, "ifconfig eth0 200.200.200.%d > /tmp/status", bedno);
	}

	system(tbuf);

	// reset the network task
}

#if 1
int DlgButtonCheckedNum(HWND hWnd, RESID start, int num)
{
	int i, ret;
	ret = 0;
	for (i = 0; i < num; i++)
	{
		if (IsDlgButtonChecked(hWnd, start + i) > 0)
			ret++;
	}
	return ret;
}

INT16 ShowPatientInfoList(HWND hWnd, INT16 index, INT16 count)
{
	INT16 i;
	CHAR *txt;
	HWND hCtrl;
	for (i = 0; i < 8; i++)
	{
		txt = LoadString(STR_DLG_PNT_RECALL_PNAME0 + i);
		memset(txt, '\0', 36);
		if (sPtnList[index + i].ptnName[0] != '0')
			strncpy(txt, sPtnList[index + i].ptnName, 32);
		txt = LoadString(STR_DLG_PNT_RECALL_PID0 + i);
		memset(txt, '\0', 36);
		if (sPtnList[index + i].ptnID[0] != '0')
			strncpy(txt, sPtnList[index + i].ptnID, 32);
		if (0 == (hCtrl = GetDlgItem(hWnd, IDC_PATIENT_RECALL_NAME1_L + i)))
		{
			break;
		}
		SetWindowText(hCtrl, STR_DLG_PNT_RECALL_PNAME0 + i);
		if (0 == (hCtrl = GetDlgItem(hWnd, IDC_PATIENT_RECALL_ID1_C + i)))
		{
			break;
		}
		SetWindowText(hCtrl, STR_DLG_PNT_RECALL_PID0 + i);
		//EnableWindow(hCtrl, sPtnList[index + i].status == 'S');
	}
	if (hCtrl = GetDlgItem(hWnd, IDC_PATIENT_RECALL_ALL_C))
		EnableWindow(hCtrl, sPtnList[index].status == 'S');
	return i;
}

BOOL PtnRecallDlg_OnCommand (HWND hWnd, DWORD wParam, LPARAM lParam)
{
	INT16 ret = TRUE;
	INT32 i, num, status, ret32, count;
	HWND  hCtrl;
	num = 0;
	count = IDC_PATIENT_RECALL_ID8_C - IDC_PATIENT_RECALL_ID1_C + 1;
	for (i = 0; i < count; i++)
	{
		hCtrl = GetDlgItem(hWnd, IDC_PATIENT_RECALL_ID1_C + i);
		
		if (! hCtrl) continue;

		if (0 == (WS_DISABLED & ((PCONTROL)hCtrl)->dwStyle))
		{
			num++;
		}
	}
	switch(LOWORD(wParam))
	{
		case IDC_PATIENT_RECALL_ALL_C:
			status = IsDlgButtonChecked(hWnd, LOWORD(wParam));
			CheckDlgButton(hWnd, LOWORD(wParam), !status);
			status = IsDlgButtonChecked(hWnd, LOWORD(wParam));
			for (i = 0; i < num; i++)
			{
				CheckDlgButton(hWnd, IDC_PATIENT_RECALL_ID1_C + i, status);
			}
			break;

		case IDC_PATIENT_RECALL_ID1_C:
		case IDC_PATIENT_RECALL_ID2_C:
		case IDC_PATIENT_RECALL_ID3_C:
		case IDC_PATIENT_RECALL_ID4_C:
		case IDC_PATIENT_RECALL_ID5_C:
		case IDC_PATIENT_RECALL_ID6_C:
		case IDC_PATIENT_RECALL_ID7_C:
		case IDC_PATIENT_RECALL_ID8_C:
			status = IsDlgButtonChecked(hWnd, LOWORD(wParam));
			CheckDlgButton(hWnd, LOWORD(wParam), !status);
			break;

		case IDC_PATIENT_RECALL_PGUP_B:
			hCtrl = GetDlgItem(hWnd, IDC_PATIENT_RECALL_SCROLL_L);
			if (hCtrl)
			{
				sCurrFile -= count;
				if (sCurrFile < 0)
					sCurrFile = 0;
				ShowPatientInfoList(hWnd, sCurrFile, FmsPtr->GetSaveNum(FmsPtr));
				DrawScrollV(hCtrl, sCurrFile, FmsPtr->GetSaveNum(FmsPtr), count);
			}
			for (i = IDC_PATIENT_RECALL_ID1_C; i <= IDC_PATIENT_RECALL_ID8_C; i++)
			{
				CheckDlgButton(hWnd, i, FALSE);
			}
			break;

		case IDC_PATIENT_RECALL_PGDN_B:
			hCtrl = GetDlgItem(hWnd, IDC_PATIENT_RECALL_SCROLL_L);
			if (hCtrl)
			{
				sCurrFile += count;
				if (sCurrFile > FmsPtr->GetSaveNum(FmsPtr))
				{
					sCurrFile -= count;
					if (sCurrFile < 0)
						sCurrFile = 0;
				}
				ShowPatientInfoList(hWnd, sCurrFile, FmsPtr->GetSaveNum(FmsPtr));
				DrawScrollV(hCtrl, sCurrFile, FmsPtr->GetSaveNum(FmsPtr), count);
			}
			for (i = IDC_PATIENT_RECALL_ID1_C; i <= IDC_PATIENT_RECALL_ID8_C; i++)
			{
				CheckDlgButton(hWnd, i, FALSE);
			}
			break;

		case IDC_PATIENT_RECALL_OPEN_B:
			if (1 == DlgButtonCheckedNum(hWnd, IDC_PATIENT_RECALL_ID1_C, num))
			{
				for (i = 0; i < num; i++)
				{
					if (status = IsDlgButtonChecked(hWnd, i + IDC_PATIENT_RECALL_ID1_C))
						break;
				}
				if (i < num)
				{
					CheckDlgButton(hWnd, i + IDC_PATIENT_RECALL_ID1_C, FALSE);
					FetalRecallDialog(hWnd, i + sCurrFile);
				}
			}
			break;

		case IDC_PATIENT_RECALL_DELETE_B:
			if (DlgButtonCheckedNum(hWnd, IDC_PATIENT_RECALL_ID1_C, num) > 0)
			{
				int record;
				int move = 0;
				short select[8], nr = 0;
				record = MessageBox(hWnd, STR_MSGBOX_PRO_DELFILE, 0,
					STR_MSGBOX_CAP_DELFILE, MB_YESNO, SysGui_HTSK);
				if (IDNO == record)
				{
					break;
				}
				for (i = 0; i < num; i++)
				{
					if (status = IsDlgButtonChecked(hWnd, i + IDC_PATIENT_RECALL_ID1_C))
					{
						select[nr++] = i + sCurrFile;
						CheckDlgButton(hWnd, i + IDC_PATIENT_RECALL_ID1_C, !status);
					}
				}
				FmsPtr->DeletePatient(FmsPtr, select, nr);
				GetPatientInfoList(FmsPtr);
				ShowPatientInfoList(hWnd, sCurrFile, FmsPtr->GetSaveNum(FmsPtr));
			}
			break;

		case IDC_PATIENT_RECALL_EXIT_B:
			EndDialog (hWnd, IDOK);
			break;

		default:
			return ret;
	}
	ret32 = DlgButtonCheckedNum(hWnd, IDC_PATIENT_RECALL_ID1_C, count);
	if (num == ret32)
	{
		CheckDlgButton(hWnd, IDC_PATIENT_RECALL_ALL_C, TRUE);
	}
	else
	{
		CheckDlgButton(hWnd, IDC_PATIENT_RECALL_ALL_C, FALSE);
	}
	hCtrl = GetDlgItem(hWnd, IDC_PATIENT_RECALL_OPEN_B);
	if (hCtrl)
	{
		EnableWindow(hCtrl, ret32 == 1);
	}
	hCtrl = GetDlgItem(hWnd, IDC_PATIENT_RECALL_DELETE_B);
	if (hCtrl)
	{
		EnableWindow(hCtrl, ret32 > 0);
	}
	return ret;
}

int GetPatientInfoList(FILEMRSYS *this)
{
	int i, cnt, loops;
	SAVEFILE *info;
	
	memset(sPtnList, 0, sizeof(sPtnList));

	cnt = 0;
	info = this->GetInfoFile(this);
	loops = this->GetSaveNum(this);
	
	if (!info)
	{
		return cnt;
	}
	
	for(i = 0; i < loops; i++)
	{
		if (info->info[info->sInfo.index[i]].status == 'S')
		{
			sPtnList[cnt++] = info->info[info->sInfo.index[i]];
		}
	}

	if (cnt != loops)
	{
		printf("info list error!\r\n");
	}
	
	return cnt;
}

VOID PtnRecallDlg_Init(HWND hWnd)
{
	HWND hCtrl;
	INT32 i;
	for (i = IDC_PATIENT_RECALL_ID_L; i < IDC_PATIENT_RECALL_EXIT_B; i++)
	{
		hCtrl = GetDlgItem(hWnd, i);
		if (!hCtrl)
			return;
		SetWindowBkColor(hCtrl, ((PWIN)hWnd)->iBkColor);
	}
	
	hCtrl = GetDlgItem(hWnd, IDC_PATIENT_RECALL_PGUP_B);
	SetWindowTextColor(hCtrl, GetWindowElementColor(WEC_EXCOLOR_WHITESMOKE));
	hCtrl = GetDlgItem(hWnd, IDC_PATIENT_RECALL_PGDN_B);
	SetWindowTextColor(hCtrl, GetWindowElementColor(WEC_EXCOLOR_WHITESMOKE));
//	hCtrl = GetDlgItem(hWnd, IDC_PATIENT_RECALL_EXIT_B);
//	SetWindowBkColor(hCtrl, GetWindowElementColor(WEC_EXCOLOR_SILVER));
//	SetWindowTextColor(hCtrl, ((PWIN)hWnd)->iBkColor);
	hCtrl = GetDlgItem(hWnd, IDC_PATIENT_RECALL_SCROLL_L);
	if (!hCtrl)
		return;
	SetWindowBkColor(hCtrl, GetWindowElementColor(WEC_EXCOLOR_GAINSBORO));
	hCtrl = GetDlgItem(hWnd, IDC_PATIENT_RECALL_OPEN_B);
	EnableWindow(hCtrl, FALSE);
	hCtrl = GetDlgItem(hWnd, IDC_PATIENT_RECALL_DELETE_B);
	EnableWindow(hCtrl, FALSE);
	
	sCurrFile = 0;

	if (8 > GetPatientInfoList(FmsPtr))
	{
		if (hCtrl = GetDlgItem(hWnd, IDC_PATIENT_RECALL_PGUP_B))
			EnableWindow(hCtrl, FALSE);
		
		if (hCtrl = GetDlgItem(hWnd, IDC_PATIENT_RECALL_PGDN_B))
			EnableWindow(hCtrl, FALSE);
	}
}

static INT32 PtnRecallDlgProc (HANDLE hWnd, INT32 message, DWORD wParam, LPARAM lParam)
{
	switch(message)
	{
		case MSG_INITDIALOG:
			PtnRecallDlg_Init(hWnd);
			break;

		case MSG_SHOWWINDOW:
			{
				HWND hCtrl = GetDlgItem(hWnd, IDC_PATIENT_RECALL_FIRST);
				DrawScrollV(hCtrl, 0, FmsPtr->GetSaveNum(FmsPtr), 8);
				ShowPatientInfoList(hWnd, 0, FmsPtr->GetSaveNum(FmsPtr));
			}
			break;

		case MSG_COMMAND:
			if (PtnRecallDlg_OnCommand(hWnd, wParam, lParam))
				return 0;
			break;

		default:
			break;
	}
	return DefaultDialogProc (hWnd, message, wParam, lParam);
}

VOID PatientRecallDialog(HANDLE hOwner)
{
	enum dlg_size{
		DLG_WIDTH = 320,
		DLG_HEIGHT = 380,
		DLG_COLUMN1_W = 130,
		DLG_COLUMN2_W = 130,
	};
	
	static BUTTONDATA cbox[11];
	static BUTTONDATA btn_pgup;
	static BUTTONDATA btn_pgdn;
	static BUTTONDATA btn_exit;
	static BUTTONDATA btn_open;
	static BUTTONDATA btn_del;
	memset(cbox, 0, sizeof(cbox));
	memset(&btn_pgup, 0, sizeof(btn_pgup));
	memset(&btn_pgdn, 0, sizeof(btn_pgdn));
	memset(&btn_open, 0, sizeof(btn_open));
	memset(&btn_del, 0, sizeof(btn_del));
	btn_exit = gBtn_Exit;
	btn_pgup.data = IDI_PAGE_UP;
	btn_pgdn.data = IDI_PAGE_DN;
	CTRLDATA ctrl_data[] = {
		{ CTRL_BUTTON,  WS_VISIBLE | WS_TABSTOP | BS_ICON, WS_EX_NONE,
			DLG_WIDTH-EXIT_ICON_WIDTH - DLG_OFFSET,
			-(DLG_MENU_HIGHT + EXIT_ICON_HIGH) / 2,
			EXIT_ICON_WIDTH,  EXIT_ICON_HIGH,
			IDC_PATIENT_RECALL_EXIT_B, STR_DLG_EXIT, 0L, 0L },

		{ CTRL_STATIC,  WS_VISIBLE | SS_SIMPLE, WS_EX_NONE,
			DLG_WIDTH-DLG_OFFSET-24, DLG_OFFSET+21, 24, KEY_HEIGHT*9-42,
			IDC_PATIENT_RECALL_SCROLL_L, 0, 0L, 0L },

		{ CTRL_STATIC,  WS_VISIBLE | SS_CENTER, WS_EX_NONE,
			DLG_OFFSET+65, DLG_OFFSET, STATIC_HEIGHT, STATIC_HEIGHT,
			IDC_PATIENT_RECALL_ID_L, STR_DLG_PNT_RECALL_ID, 0L, 0L },

		{ CTRL_STATIC,  WS_VISIBLE | SS_CENTER, WS_EX_NONE,
			DLG_OFFSET+DLG_COLUMN2_W, DLG_OFFSET, DLG_COLUMN2_W, STATIC_HEIGHT,
			IDC_PATIENT_RECALL_NAME__L, STR_DLG_PNT_RECALL_NAME, 0L, 0L },

		{ CTRL_STATIC,  WS_VISIBLE | SS_CENTER, WS_EX_NONE,
			DLG_OFFSET+DLG_COLUMN1_W, DLG_OFFSET+5+KEY_HEIGHT*1,
			DLG_COLUMN2_W, STATIC_HEIGHT,
			IDC_PATIENT_RECALL_NAME1_L, 0, 0L, 0L },

		{ CTRL_STATIC,  WS_VISIBLE | SS_CENTER, WS_EX_NONE,
			DLG_OFFSET+DLG_COLUMN1_W, DLG_OFFSET+5+KEY_HEIGHT*2,
			DLG_COLUMN2_W, STATIC_HEIGHT,
			IDC_PATIENT_RECALL_NAME2_L, 0, 0L, 0L },

		{ CTRL_STATIC,  WS_VISIBLE | SS_CENTER, WS_EX_NONE,
			DLG_OFFSET+DLG_COLUMN1_W, DLG_OFFSET+5+KEY_HEIGHT*3,
			DLG_COLUMN2_W, STATIC_HEIGHT,
			IDC_PATIENT_RECALL_NAME3_L, 0, 0L, 0L },

		{ CTRL_STATIC,  WS_VISIBLE | SS_CENTER, WS_EX_NONE,
			DLG_OFFSET+DLG_COLUMN1_W, DLG_OFFSET+5+KEY_HEIGHT*4,
			DLG_COLUMN2_W, STATIC_HEIGHT,
			IDC_PATIENT_RECALL_NAME4_L, 0, 0L, 0L },

		{ CTRL_STATIC,  WS_VISIBLE | SS_CENTER, WS_EX_NONE,
			DLG_OFFSET+DLG_COLUMN1_W, DLG_OFFSET+5+KEY_HEIGHT*5,
			DLG_COLUMN2_W, STATIC_HEIGHT,
			IDC_PATIENT_RECALL_NAME5_L, 0, 0L, 0L },

		{ CTRL_STATIC,  WS_VISIBLE | SS_CENTER, WS_EX_NONE,
			DLG_OFFSET+DLG_COLUMN1_W, DLG_OFFSET+5+KEY_HEIGHT*6,
			DLG_COLUMN2_W, STATIC_HEIGHT,
			IDC_PATIENT_RECALL_NAME6_L, 0, 0L, 0L },

		{ CTRL_STATIC,  WS_VISIBLE | SS_CENTER, WS_EX_NONE,
			DLG_OFFSET+DLG_COLUMN1_W, DLG_OFFSET+5+KEY_HEIGHT*7,
			DLG_COLUMN2_W, STATIC_HEIGHT,
			IDC_PATIENT_RECALL_NAME7_L, 0, 0L, 0L },

		{ CTRL_STATIC,  WS_VISIBLE | SS_CENTER, WS_EX_NONE,
			DLG_OFFSET+DLG_COLUMN1_W, DLG_OFFSET+5+KEY_HEIGHT*8,
			DLG_COLUMN2_W, STATIC_HEIGHT,
			IDC_PATIENT_RECALL_NAME8_L, 0, 0L, 0L },

		{ CTRL_BUTTON,  WS_VISIBLE | WS_TABSTOP | BS_CHECKBOX, WS_EX_NONE,
			DLG_OFFSET-5, DLG_OFFSET, 65, KEY_HEIGHT,
			IDC_PATIENT_RECALL_ALL_C, STR_DLG_PNT_RECALL_ALL, 0L, 0L },

		{ CTRL_BUTTON,  WS_VISIBLE | WS_TABSTOP | BS_CHECKBOX, WS_EX_NONE,
			DLG_OFFSET, DLG_OFFSET+KEY_HEIGHT*1,
			DLG_COLUMN1_W, KEY_HEIGHT,
			IDC_PATIENT_RECALL_ID1_C, 0, 0L, 0L },

		{ CTRL_BUTTON,  WS_VISIBLE | WS_TABSTOP | BS_CHECKBOX, WS_EX_NONE,
			DLG_OFFSET, DLG_OFFSET+KEY_HEIGHT*2,
			DLG_COLUMN1_W, KEY_HEIGHT,
			IDC_PATIENT_RECALL_ID2_C, 0, 0L, 0L },

		{ CTRL_BUTTON,  WS_VISIBLE | WS_TABSTOP | BS_CHECKBOX, WS_EX_NONE,
			DLG_OFFSET, DLG_OFFSET+KEY_HEIGHT*3,
			DLG_COLUMN1_W, KEY_HEIGHT,
			IDC_PATIENT_RECALL_ID3_C, 0, 0L, 0L },

		{ CTRL_BUTTON,  WS_VISIBLE | WS_TABSTOP | BS_CHECKBOX, WS_EX_NONE,
			DLG_OFFSET, DLG_OFFSET+KEY_HEIGHT*4,
			DLG_COLUMN1_W, KEY_HEIGHT,
			IDC_PATIENT_RECALL_ID4_C, 0, 0L, 0L },

		{ CTRL_BUTTON,  WS_VISIBLE | WS_TABSTOP | BS_CHECKBOX, WS_EX_NONE,
			DLG_OFFSET, DLG_OFFSET+KEY_HEIGHT*5,
			DLG_COLUMN1_W, KEY_HEIGHT,
			IDC_PATIENT_RECALL_ID5_C, 0, 0L, 0L },

		{ CTRL_BUTTON,  WS_VISIBLE | WS_TABSTOP | BS_CHECKBOX, WS_EX_NONE,
			DLG_OFFSET, DLG_OFFSET+KEY_HEIGHT*6,
			DLG_COLUMN1_W, KEY_HEIGHT,
			IDC_PATIENT_RECALL_ID6_C, 0, 0L, 0L },

		{ CTRL_BUTTON,  WS_VISIBLE | WS_TABSTOP | BS_CHECKBOX, WS_EX_NONE,
			DLG_OFFSET, DLG_OFFSET+KEY_HEIGHT*7,
			DLG_COLUMN1_W, KEY_HEIGHT,
			IDC_PATIENT_RECALL_ID7_C, 0, 0L, 0L },

		{ CTRL_BUTTON,  WS_VISIBLE | WS_TABSTOP | BS_CHECKBOX, WS_EX_NONE,
			DLG_OFFSET, DLG_OFFSET+KEY_HEIGHT*8,
			DLG_COLUMN1_W, KEY_HEIGHT,
			IDC_PATIENT_RECALL_ID8_C, 0, 0L, 0L },

		{ CTRL_BUTTON,  WS_VISIBLE | WS_TABSTOP | BS_ICON, WS_EX_NONE,
			DLG_WIDTH-DLG_OFFSET-24, DLG_OFFSET, 24, 21,
			IDC_PATIENT_RECALL_PGUP_B, 0, 0L, 0L },

		{ CTRL_BUTTON,  WS_VISIBLE | WS_TABSTOP | BS_ICON, WS_EX_NONE,
			DLG_WIDTH-DLG_OFFSET-24, DLG_OFFSET+KEY_HEIGHT*9-21, 24, 21,
			IDC_PATIENT_RECALL_PGDN_B, 0, 0L, 0L },

		{ CTRL_BUTTON,  WS_VISIBLE | WS_TABSTOP, WS_EX_NONE,
			DLG_OFFSET, DLG_HEIGHT-DLG_MENU_HIGHT-KEY_HEIGHT-DLG_OFFSET,
			DLG_COLUMN1_W, KEY_HEIGHT,
			IDC_PATIENT_RECALL_OPEN_B, STR_DLG_PNT_RECALL_OPEN, 0L, 0L },

		{ CTRL_BUTTON,  WS_VISIBLE | WS_TABSTOP, WS_EX_NONE,
			DLG_WIDTH-DLG_OFFSET-DLG_COLUMN2_W,
			DLG_HEIGHT-DLG_MENU_HIGHT-KEY_HEIGHT-DLG_OFFSET,
			DLG_COLUMN2_W, KEY_HEIGHT,
			IDC_PATIENT_RECALL_DELETE_B, STR_DLG_PNT_RECALL_DELETE, 0L, 0L }
	};
	DLGTEMPLATE dlg_data = {
	   WS_ABSSCRPOS | WS_CAPTION | WS_BORDER | WS_MODALDLG, WS_NONE, 
	   DLG_OFFSET, CTRL_HEIGHT, DLG_WIDTH, DLG_HEIGHT,
	   STR_DLG_PNT_RECALL_MANAGER, 0, NULL, 0L,
	};
	INT16 i, loops;
	loops = TABLESIZE(ctrl_data);
	WNDMEM   wndMem;
	
	wndMem.pMainWin = GetMainWndMem(IDD_PATIENT_RECALL);
	wndMem.pControl = GetCtrlWndMem(IDC_PATIENT_RECALL_FIRST);
	wndMem.ctrlNum  = TABLESIZE(ctrl_data);
	wndMem.task	 = SysGui_HTSK;
	
	dlg_data.controlnr = loops;
	dlg_data.controls  = ctrl_data;

	for(i = 0; i < 9; i++)
	{
		SetCtrlDataAddData2(ctrl_data, loops, IDC_PATIENT_RECALL_ALL_C + i, 
							(UINT32)&cbox[i]);
	}
	SetCtrlDataAddData2(ctrl_data, loops, IDC_PATIENT_RECALL_PGUP_B, 
						(UINT32)&btn_pgup);
	SetCtrlDataAddData2(ctrl_data, loops, IDC_PATIENT_RECALL_PGDN_B, 
						(UINT32)&btn_pgdn);
	SetCtrlDataAddData2(ctrl_data, loops, IDC_PATIENT_RECALL_OPEN_B, 
						(UINT32)&btn_open);
	SetCtrlDataAddData2(ctrl_data, loops, IDC_PATIENT_RECALL_DELETE_B, 
						(UINT32)&btn_del);
	SetCtrlDataAddData2(ctrl_data, loops, IDC_PATIENT_RECALL_EXIT_B, 
						(UINT32)&btn_exit);
	DialogBoxIndirectParam(&dlg_data, hOwner, IDD_PATIENT_RECALL, PtnRecallDlgProc, 0,
							&wndMem);
}
#endif
/**
 ** 如果可以处理,返回1;
 ** 否则返回0, 由默认对话框过程处理.
 **/
#include "keyboardDlg.h"

static UINT8 sPatientInfoEditFlag = FALSE;
static VOID EnbPatientInfoEditFlag(BOOL flag)
{
	HWND hWnd = (HWND)GetTopWndItem(IDD_PATIENT_SETUP);
	HWND hCtrl;
	INT32 i;
	if (hWnd == HWND_INVALID)
	{
		// 窗口未打开
		sPatientInfoEditFlag = FALSE;
		return;
	}
	hCtrl = GetDlgItem(hWnd, IDC_PATIENT_SETUP_EDIT_B);
	if (hCtrl)
	{
		if (flag)
		{
			SetWindowText(hCtrl, STR_DLG_EXIT);
		}
		else
		{
			SetWindowText(hCtrl, STR_DLG_PATIENT_EDIT);
		}
		if (FmsPtr->GetCurrSaveIndex(FmsPtr) < 0)
		{
			EnableWindow(hCtrl, FALSE);
			if (hCtrl = GetDlgItem(hWnd, IDC_PATIENT_SETUP_ANALY_B))
			{
				EnableWindow(hCtrl, FALSE);
			}
		}
		else
		{
			EnableWindow(hCtrl, TRUE);
			if (hCtrl = GetDlgItem(hWnd, IDC_PATIENT_SETUP_ANALY_B))
			{
				if (get_analysis_enable())
					EnableWindow(hCtrl, !flag);
				else
					EnableWindow(hCtrl, FALSE);
			}
		}
	}
	for (i = IDC_PATIENT_SETUP_NAME_EDIT; i <= IDC_PATIENT_SETUP_NOTE_EDIT; i++)
	{
		if (hCtrl = GetDlgItem(hWnd, i))
		{
			EnableWindow(hCtrl, flag);
		}
	}
	if (hCtrl = GetDlgItem(hWnd, IDC_PATIENT_SETUP_RECALL_B))
	{
		EnableWindow(hCtrl, !flag);
	}
	if (hCtrl = GetDlgItem(hWnd, IDC_PATIENT_SETUP_NEWPATIENT_B))
	{
		EnableWindow(hCtrl, !flag);
	}
	sPatientInfoEditFlag = flag;
}

VOID InsertNewPatientID(BOOL insert)
{
	if (insert == FALSE) return;

	ZeroMemory(&PatientInfo,sizeof(PatientInfo));
//	PatientInfo.year	= DateTime.year;
//	PatientInfo.month   = DateTime.month;
//	PatientInfo.day	 = DateTime.day;
//	PatientInfo.hour	= DateTime.hour;
//	PatientInfo.minute  = DateTime.minute;
//	PatientInfo.second  = DateTime.second;
//	memcpy(&PatientInfo, &(FmsPtr->savefile->sInfo[FmsPtr->infoCur]), sizeof(PatientInfo));
	sprintf(PatientInfo.patientID, "%04d%02d%02d%02d%02d", DateTime.year,
		DateTime.month, DateTime.day, DateTime.hour, DateTime.minute);
	SetEditText(IDD_PATIENT_SETUP, IDC_PATIENT_SETUP_ID_EDIT, PatientInfo.patientID);
	strcpy(LoadString(STR_MAIN_TOPBAR_ID_NUM), PatientInfo.patientID);
	FmsPtr->PutPtnInfo(FmsPtr, &PatientInfo);
//	prinfo("PatientInfo.name:%c%c%c%c%c%c%c%c\r\n",
//		PatientInfo.name[0], PatientInfo.name[1], PatientInfo.name[2], PatientInfo.name[3],
//		PatientInfo.name[4], PatientInfo.name[5], PatientInfo.name[6], PatientInfo.name[7]);
//	prinfo("PatientInfo.index	   :%d\r\n", PatientInfo.index);
//	prinfo("PatientInfo.no		  :%d\r\n", PatientInfo.no);
//	prinfo("PatientInfo.patientName :%s\r\n", PatientInfo.patientName);
//	prinfo("PatientInfo.patientID   :%s\r\n", PatientInfo.patientID);
//	prinfo("PatientInfo.patientAge  :%d\r\n", PatientInfo.patientAge);
//	prinfo("PatientInfo.gestationalWeeks:%d\r\n", PatientInfo.gestationalWeeks);
//	prinfo("PatientInfo.gestationalDay  :%d\r\n", PatientInfo.gestationalDay);
//	prinfo("PatientInfo.gestationalTimes:%d\r\n", PatientInfo.gestationalTimes);
//	prinfo("PatientInfo.height	  :%d\r\n", PatientInfo.height);
//	prinfo("PatientInfo.weight	  :%d\r\n", PatientInfo.weight);
//	prinfo("PatientInfo.sex		 :%d\r\n", PatientInfo.sex);
//	prinfo("PatientInfo.patientType :%d\r\n", PatientInfo.patientType);
//	prinfo("PatientInfo.bloodType   :%d\r\n", PatientInfo.bloodType);
//	prinfo("PatientInfo.note		:%d\r\n", PatientInfo.note);
//	prinfo("PatientInfo.hour		:%d\r\n", PatientInfo.hour);
}

VOID EndPatientFile(VOID)
{
	if (get_analysis_enable())
	{
		SetAnalySendFlag(TRUE);
		if (AnalySendData())
			SetAnalySendFlag(FALSE);
		PutAnalysisResultIntoFile();
	}
	FmsPtr->ClosePtnFile(FmsPtr);
	NewPatient();
	ShowPatinetInfo();
}

INT32 ConfirmNoAnalysis(HWND hParentWnd)
{
	printf("// 有效数据不足时不需要确认评分111\n");
	if (!get_analysis_enable())
		return TRUE;
	printf("// 有效数据不足时不需要确认评分222\n");
	// 有效数据不足时不需要确认评分
	if (AnalyConfig.nr_valid < 1190)
		return TRUE;
	printf("// 有效数据不足时不需要确认评分333333\n");
	return MessageBox(hParentWnd,
			STR_MSGBOX_PRO_CONFIRM_ANALYSIS1, STR_MSGBOX_PRO_CONFIRM_ANALYSIS2,
			STR_DLG_PATIENT_SAVE, MB_ALIGNCENTER | MB_YESNO, SysGui_HTSK);
}

static INT16   Patient_OnCommand (HWND hWnd, DWORD wParam, LPARAM lParam)
{
	INT16 ret = TRUE;
	switch(LOWORD(wParam))
	{
		case IDC_PATIENT_SETUP_EXIT_B:
			if (FhrStatus.initStatus)
			{
				FhrStatus.initStatus = FALSE;
			#if _ENB_REC_FUNC
				if (FhrConfig.autoPrint)
				{
					if (IDYES == MessageBox(hWnd, STR_MSGBOX_PRO_AUTOPRINT,
						STR_NULL, STR_MSGBOX_CAP_AUTOPRINT,
						MB_YESNO, SysGui_HTSK))
					{
						RecordService(REC_FETAL_RECALL);
					}
				}
			#endif
			}
			EndDialog (hWnd, IDOK);
			break;

		case IDC_PATIENT_SETUP_NEWPATIENT_B:
			if (FmsPtr->GetCurrSaveIndex(FmsPtr) < 0)//
			{
				printf("按下病人归档或新病人?111111\n");
				NewPatient();
				FmsPtr->NewPatient(FmsPtr);
				InsertNewPatientID(1);
				EnbPatientInfoEditFlag(TRUE);
				SetWindowText(GetDlgItem(hWnd, IDC_PATIENT_SETUP_NEWPATIENT_B),
					STR_DLG_PATIENT_SAVE);
				FmsPtr->PutPtnInfo(FmsPtr, &PatientInfo);
				ShowPatinetInfo();
				FhrStatus.initStatus = TRUE;
			}
			else
			{
				printf("按下病人归档或新病人?1222222\n");
				if (IDNO == ConfirmNoAnalysis(hWnd))
					break;
				printf("按下病人归档或新病人?4444444\n");
				EndPatientFile();
				printf("按下病人归档或新病人?5555555555\n");
				SetEditText(IDD_PATIENT_SETUP, IDC_PATIENT_SETUP_NAME_EDIT, "");
				SetEditText(IDD_PATIENT_SETUP, IDC_PATIENT_SETUP_ID_EDIT, "");
				SetEditText(IDD_PATIENT_SETUP, IDC_PATIENT_SETUP_NOTE_EDIT, "");
				SetEditText(IDD_PATIENT_SETUP, IDC_PATIENT_SETUP_AGE_EDIT, "");
				SetEditText(IDD_PATIENT_SETUP, IDC_PATIENT_SETUP_GESTATIONAL_EDIT, "");
				SetEditText(IDD_PATIENT_SETUP, IDC_PATIENT_SETUP_GESTATIONAL_DAY_EDIT, "");
				SetEditText(IDD_PATIENT_SETUP, IDC_PATIENT_SETUP_GTIMES_EDIT, "");
				strcpy(LoadString(STR_MAIN_TOPBAR_NAME_NAME), PatientInfo.patientName);
				strcpy(LoadString(STR_MAIN_TOPBAR_ID_NUM), PatientInfo.patientID);
				printf("按下病人归档或新病人?877777777\n");
				EnbPatientInfoEditFlag(FALSE);
				SetWindowText(GetDlgItem(hWnd, IDC_PATIENT_SETUP_NEWPATIENT_B),
					STR_MAIN_BOTTOM_NEWPATIENT);
				printf("按下病人归档或新病人?888888\n");
			}
			break;

		case IDC_PATIENT_SETUP_RECALL_B:
			PatientRecallDialog(hWnd);
			break;

		case IDC_PATIENT_SETUP_EDIT_B:
			//FmsPtr->PutPtnInfo(FmsPtr, &PatientInfo);
			if (sPatientInfoEditFlag)
			{
				EnbPatientInfoEditFlag(FALSE);
				FmsPtr->PutPtnInfo(FmsPtr, &PatientInfo);
			}
			else
			{
				EnbPatientInfoEditFlag(TRUE);
			}
			break;

		case IDC_PATIENT_SETUP_ANALY_B:
			AnalysisDialog(hWnd);
			SendMessage(hWnd, MSG_INITDIALOG, 0, 0);
			SendMessage(hWnd, MSG_SHOWWINDOW, 0, 0);
			break;

		case IDC_PATIENT_SETUP_NAME_EDIT:
			if (EN_CLICKED == HIWORD(wParam))
			{
				StrBuffer strbuff;
				NewStrBuffer(&strbuff, sizeof(PatientInfo.patientName));
				if (strlen(PatientInfo.patientName) > 0)
				{
					strcpy(strbuff.string, PatientInfo.patientName);
				}
				if (CHINESE == MonitorConfig.language)
				{
					SelectKeyboardType(KEYBOARD_CHINESE, 
						LoadString(STR_DLG_PATIENT_NAME),
						LoadString(STR_DLG_PATIENT_NAME));
				}
				else
				{
					SelectKeyboardType(KEYBOARD_LOWERCS, 
						LoadString(STR_DLG_PATIENT_NAME),
						LoadString(STR_DLG_PATIENT_NAME));
				}
				UseKeyboard(hWnd, LOWORD(wParam),(LPARAM)&strbuff);
				memset(PatientInfo.patientName, '\0', 
						sizeof(PatientInfo.patientName));
				strncpy(PatientInfo.patientName, strbuff.string, 
						sizeof(PatientInfo.patientName) - 1);
				TextDel(strbuff.string);
				SetEditText(IDD_PATIENT_SETUP, LOWORD(wParam), PatientInfo.patientName);
				strcpy(LoadString(STR_MAIN_TOPBAR_NAME_NAME), PatientInfo.patientName);
				ShowPatinetInfo();
				FmsPtr->PutPtnInfo(FmsPtr, &PatientInfo);
			}
			break;

		case IDC_PATIENT_SETUP_ID_EDIT:
			if (EN_CLICKED == HIWORD(wParam))
			{
				StrBuffer strbuff;
				NewStrBuffer(&strbuff, sizeof(PatientInfo.patientID));
				if (strlen(PatientInfo.patientID) > 0)
				{
					strcpy(strbuff.string, PatientInfo.patientID);
				}
				SelectKeyboardType(KEYBOARD_NUMMARKS, 
					LoadString(STR_DLG_PATIENT_ID), "");
				UseKeyboard(hWnd, LOWORD(wParam),(LPARAM)&strbuff);
				memset(PatientInfo.patientID, '\0', sizeof(PatientInfo.patientID));
				strncpy(PatientInfo.patientID, strbuff.string, 
						sizeof(PatientInfo.patientID) - 1);
				TextDel(strbuff.string);
				SetEditText(IDD_PATIENT_SETUP, LOWORD(wParam), PatientInfo.patientID);
				strcpy(LoadString(STR_MAIN_TOPBAR_ID_NUM), PatientInfo.patientID);
				ShowPatinetInfo();
				FmsPtr->PutPtnInfo(FmsPtr, &PatientInfo);
			}
			break;

		case IDC_PATIENT_SETUP_AGE_EDIT:
			if (EN_CLICKED == HIWORD(wParam))
			{
				INT32 value = PatientInfo.patientAge;
				char Info[32];
				sprintf(Info, "%s0~99", LoadString(STR_DLG_PATIENT_AGE));
				SelectKeyboardType(KEYBOARD_UNS_INT, Info, Info);
				UseKeyboard(hWnd, LOWORD(wParam),(LPARAM)&value);
				if (value != PatientInfo.patientAge)
				{
					if (value > 0)
					{
						if (value > 99)
						{
							value = 99;
						}
						PatientInfo.patientAge = (UINT8)value;
					}
					SetEditboxIntValue(IDD_PATIENT_SETUP,
										LOWORD(wParam), PatientInfo.patientAge);
					FmsPtr->PutPtnInfo(FmsPtr, &PatientInfo);
				}
			}
			break;

		case IDC_PATIENT_SETUP_GESTATIONAL_EDIT:
			if (EN_CLICKED == HIWORD(wParam))
			{
				INT32 value = PatientInfo.gestationalWeeks;
				char Info[32];
				sprintf(Info, "%s20~45",
					LoadString(STR_DLG_PATIENT_GESTATIONAL));
				SelectKeyboardType(KEYBOARD_UNS_INT, Info, Info);
				UseKeyboard(hWnd, LOWORD(wParam),(LPARAM)&value);
				if (value != PatientInfo.gestationalWeeks)
				{
					if (value >= 20 && value <= 45)
					{
						PatientInfo.gestationalWeeks = (UINT8)value;
					}
					SetEditboxIntValue(IDD_PATIENT_SETUP,
								LOWORD(wParam), PatientInfo.gestationalWeeks);
					FmsPtr->PutPtnInfo(FmsPtr, &PatientInfo);
				}
			}
			break;

		case IDC_PATIENT_SETUP_GESTATIONAL_DAY_EDIT:
			if (EN_CLICKED == HIWORD(wParam))
			{
				INT32 value = PatientInfo.gestationalDay;
				char Info[8];
				strcpy(Info, "0~6d");
				SelectKeyboardType(KEYBOARD_UNS_INT, Info, Info);
				UseKeyboard(hWnd, LOWORD(wParam),(LPARAM)&value);
				if (value != PatientInfo.gestationalDay)
				{
					if (value >= 0 && value < 7)
					{
						PatientInfo.gestationalDay= (UINT8)value;
					}
					SetEditboxIntValue(IDD_PATIENT_SETUP,
								LOWORD(wParam), PatientInfo.gestationalDay);
					FmsPtr->PutPtnInfo(FmsPtr, &PatientInfo);
				}
			}
			break;

		case IDC_PATIENT_SETUP_GTIMES_EDIT:
			if (EN_CLICKED == HIWORD(wParam))
			{
				INT32 value = PatientInfo.gestationalTimes;
				char Info[32];
				sprintf(Info, "%s1~99",
					LoadString(STR_DLG_PATIENT_GTIMES));
 				SelectKeyboardType(KEYBOARD_UNS_INT, Info, Info);
				UseKeyboard(hWnd, LOWORD(wParam),(LPARAM)&value);
				if (value != PatientInfo.gestationalTimes)
				{
					if (value > 0)
					{
						if (value > 99)
							value = 99;
						PatientInfo.gestationalTimes = (UINT8)value;
					}
					SetEditboxIntValue(IDD_PATIENT_SETUP,
								LOWORD(wParam), PatientInfo.gestationalTimes);
					FmsPtr->PutPtnInfo(FmsPtr, &PatientInfo);
				}
			}
			break;

		case IDC_PATIENT_SETUP_NOTE_EDIT:
			if (EN_CLICKED == HIWORD(wParam))
			{
				StrBuffer strbuff;
				NewStrBuffer(&strbuff, sizeof(PatientInfo.note));
				if (strlen(PatientInfo.note) > 0)
				{
					strcpy(strbuff.string, PatientInfo.note);
				}
				if (CHINESE == MonitorConfig.language)
				{
					SelectKeyboardType(KEYBOARD_CHINESE, 
						LoadString(STR_DLG_PATIENT_NOTE),
						LoadString(STR_DLG_PATIENT_NOTE));
				}
				else
				{
					SelectKeyboardType(KEYBOARD_LOWERCS, 
						LoadString(STR_DLG_PATIENT_NOTE),
						LoadString(STR_DLG_PATIENT_NOTE));
				}
				UseKeyboard(hWnd, LOWORD(wParam),(LPARAM)&strbuff);
				memset(PatientInfo.note, '\0', 
						sizeof(PatientInfo.note));
				strncpy(PatientInfo.note, strbuff.string, 
						sizeof(PatientInfo.note) - 1);
				TextDel(strbuff.string);
				SetEditText(IDD_PATIENT_SETUP, LOWORD(wParam), PatientInfo.note);
				FmsPtr->PutPtnInfo(FmsPtr, &PatientInfo);
			}
			break;

		default:
			break;
	}
	return ret;
}

static  VOID  PatientSetupInit (HWND hWnd, DWORD wParam, LPARAM lParam)
{
	char *txt;
	int i;
	HWND hCtrl;
	PWIN pWin = (PWIN)hWnd;
	hCtrl = GetDlgItem(hWnd, IDC_PATIENT_SETUP_NEWPATIENT_B);
	if (FmsPtr->GetCurrSaveIndex(FmsPtr) < 0)//
	{
		ZeroMemory(&PatientInfo, sizeof(PatientInfo));
		if (hCtrl)
			SetWindowText(hCtrl, STR_MAIN_BOTTOM_NEWPATIENT);
	}
	else
	{
		if (hCtrl)
			SetWindowText(hCtrl, STR_DLG_PATIENT_SAVE);
	}
	txt = LoadString(STR_DLG_PATIENT_NAME_NAME);
	if (strlen(PatientInfo.patientName) > 0)
	{
		strcpy(txt, PatientInfo.patientName);
	}
	else
	{
		*txt = '\0';
	}
	SetEditText(IDD_PATIENT_SETUP, IDC_PATIENT_SETUP_NAME_EDIT, txt);

	txt = LoadString(STR_DLG_PATIENT_ID_ID);
	if (strlen(PatientInfo.patientID) > 0)
	{
		strcpy(txt, PatientInfo.patientID);
	}
	else
	{
		*txt = '\0';
	}
	SetEditText(IDD_PATIENT_SETUP, IDC_PATIENT_SETUP_ID_EDIT, txt);

	txt = LoadString(STR_DLG_PATIENT_AGE_AGE);
	if (PatientInfo.patientAge > 0)
	{
		sprintf(txt, "%d", PatientInfo.patientAge);
	}
	else
	{
		*txt = '\0';
	}
	SetEditText(IDD_PATIENT_SETUP, IDC_PATIENT_SETUP_AGE_EDIT, txt);

	txt = LoadString(STR_DLG_PATIENT_GESTATIONAL_WEEK);
	if (PatientInfo.gestationalWeeks > 0)
	{
		sprintf(txt, "%d", PatientInfo.gestationalWeeks);
	}
	else
	{
		*txt = '\0';
	}
	SetEditText(IDD_PATIENT_SETUP, IDC_PATIENT_SETUP_GESTATIONAL_EDIT, txt);

	txt = LoadString(STR_DLG_PATIENT_GESTATIONAL_DAY);
	if (PatientInfo.gestationalWeeks > 0 && PatientInfo.gestationalDay < 7)
	{
		sprintf(txt, "%d", PatientInfo.gestationalDay);
	}
	else
	{
		*txt = '\0';
	}
	SetEditText(IDD_PATIENT_SETUP, IDC_PATIENT_SETUP_GESTATIONAL_DAY_EDIT, txt);

	txt = LoadString(STR_DLG_PATIENT_GTIMES_TIMES);
	if (PatientInfo.gestationalTimes > 0)
	{
		sprintf(txt, "%d", PatientInfo.gestationalTimes);
	}
	else
	{
		*txt = '\0';
	}
	SetEditText(IDD_PATIENT_SETUP, IDC_PATIENT_SETUP_GTIMES_EDIT, txt);

	txt = LoadString(STR_DLG_PATIENT_NOTE_PAD);
	if (strlen(PatientInfo.note) > 0)
	{
		strcpy(txt, PatientInfo.note);
	}
	else
	{
		*txt = '\0';
	}
	SetEditText(IDD_PATIENT_SETUP, IDC_PATIENT_SETUP_NOTE_EDIT, txt);

	for (i = IDC_PATIENT_SETUP_NAME_L; i < IDC_PATIENT_SETUP_NAME_EDIT; i++)
	{
		if (hCtrl = GetDlgItem(hWnd, i))
			SetWindowBkColor(hCtrl, pWin->iBkColor);
	}
	if (hCtrl = GetDlgItem(hWnd, IDC_PATIENT_SETUP_RECALL_B))
		SetWindowBkColor(hCtrl, pWin->iBkColor);
	if (hCtrl = GetDlgItem(hWnd, IDC_PATIENT_SETUP_NEWPATIENT_B))
		SetWindowBkColor(hCtrl, pWin->iBkColor);
	if (hCtrl = GetDlgItem(hWnd, IDC_PATIENT_SETUP_EDIT_B))
		SetWindowBkColor(hCtrl, pWin->iBkColor);
	
	EnbPatientInfoEditFlag(FALSE);
}

/**
	Patient设置菜单窗口过程.
**/
static  INT32  PatientSetupProc (HANDLE hWnd, INT32 message, DWORD wParam, LPARAM lParam)
{
	switch (message) {
		case MSG_INITDIALOG:
			PatientSetupInit(hWnd, wParam, lParam);
			break;

		case MSG_SHOWWINDOW:
			//DispList(hWnd,&Patientlist);
			break;

		case MSG_COMMAND:
			if (Patient_OnCommand(hWnd, wParam, lParam))
				return 0;
			break;

		default:
			break;
	}
	
	return DefaultDialogProc (hWnd, message, wParam, lParam);
}

/**
	Patient Manange 菜单.									//Change by Latrom_07-08-2011
**/
VOID  PatientSetupDialog (HWND parent)
{
	enum dialog_size{
		DLG_COLUMN1_W = 50,
		DLG_COLUMN2_W = 200,
		DLG_COLUMN3_W = 130,
		DLG_COLUMN4_W = DLG_COLUMN1_W + DLG_COLUMN2_W - DLG_COLUMN3_W,
		DLG_COLUMN1_X = DLG_OFFSET,
		DLG_COLUMN2_X = DLG_COLUMN1_X + DLG_COLUMN1_W + DLG_OFFSET,
		DLG_COLUMN3_X = DLG_COLUMN1_X + (DLG_COLUMN1_W + DLG_OFFSET + DLG_COLUMN2_W) / 2,
		DLG_COLUMN4_X = DLG_COLUMN1_X + (DLG_COLUMN1_W + DLG_OFFSET + DLG_COLUMN2_W) / 3 * 2,
			DLG_WIDTH = DLG_COLUMN2_X + DLG_COLUMN2_W + DLG_OFFSET,
		DLG_ROW_H	 = KEY_HEIGHT,
		DLG_ROW1_Y	= 10,
		DLG_ROW2_Y	= DLG_ROW1_Y + DLG_ROW_H,
		DLG_ROW3_Y	= DLG_ROW2_Y + DLG_ROW_H,
		DLG_ROW4_Y	= DLG_ROW3_Y + DLG_ROW_H,
		DLG_ROW5_Y	= DLG_ROW4_Y + DLG_ROW_H,
		DLG_ROW6_Y	= DLG_ROW5_Y + DLG_ROW_H,
		DLG_STATIC	= (DLG_ROW_H - STATIC_HEIGHT) / 2,
		DLG_FONT_HIGH = 12,
		DLG_NOTE_LINE = 5,
		DLG_ROW6_H	= DLG_NOTE_LINE * (DLG_FONT_HIGH + 2),
		DLG_ROW7_Y	= DLG_ROW6_Y + DLG_ROW6_H,
		DLG_ROW8_Y	= DLG_ROW7_Y + DLG_ROW_H,
			DLG_HIGH  = DLG_ROW8_Y + DLG_ROW_H + STATIC_OFFSET + DLG_MENU_HIGHT,
			DLG_XPOS  = (SCREEN_WIDTH - DLG_WIDTH) / 2,
			DLG_YPOS  = SCREEN_HIGH - DLG_HIGH - BOTTOMBAR_HEIGHT - DLG_OFFSET
	};

	DLGTEMPLATE dlg_data = {
	   WS_ABSSCRPOS | WS_CAPTION | WS_BORDER | WS_MODALDLG, WS_NONE, 
	   DLG_OFFSET, CTRL_HEIGHT, DLG_WIDTH, DLG_HIGH,  STR_DLG_PATIENT_INFO, 0, NULL, 0L,
	};

	BUTTONDATA  btn_exit = gBtn_Exit;
	BUTTONDATA  btn_old  = {0, 0, 0, 0 };
	BUTTONDATA  btn_new  = {0, 0, 0, 0 };
	BUTTONDATA  btn_edit = {0, 0, 0, 0 };
	BUTTONDATA  btn_anly = {0, 0, 0, 0 };

	EDITDATA	edt_name = {0};
	EDITDATA	edt_id   = {0};
	EDITDATA	edt_age  = {0};
	EDITDATA	edt_gWek = {0};
	EDITDATA	edt_gDay = {0};
	EDITDATA	edt_gtms = {0};
	EDITDATA	edt_note = {0};

	POINT ctrl_pos[] =
	{
		{ DLG_COLUMN1_X, DLG_ROW1_Y + DLG_STATIC },
		{ DLG_COLUMN1_X, DLG_ROW2_Y + DLG_STATIC },
		{ DLG_COLUMN1_X, DLG_ROW3_Y + DLG_STATIC },
		{ DLG_COLUMN1_X, DLG_ROW4_Y + DLG_STATIC },
		{ DLG_COLUMN1_X, DLG_ROW5_Y + DLG_STATIC },
		{ DLG_COLUMN1_X, DLG_ROW6_Y + DLG_STATIC },
			{ DLG_COLUMN2_X, DLG_ROW1_Y },
			{ DLG_COLUMN2_X, DLG_ROW2_Y },
			{ DLG_COLUMN2_X, DLG_ROW3_Y },
			{ DLG_COLUMN2_X, DLG_ROW4_Y },
			{ DLG_COLUMN4_X, DLG_ROW4_Y },//day
			{ DLG_COLUMN2_X, DLG_ROW5_Y },
			{ DLG_COLUMN2_X, DLG_ROW6_Y },
		{ DLG_COLUMN1_X, DLG_ROW7_Y },
		{ DLG_COLUMN1_X, DLG_ROW8_Y },
		{ DLG_COLUMN3_X, DLG_ROW7_Y },
		{ DLG_COLUMN3_X, DLG_ROW8_Y },
		{ DLG_WIDTH-EXIT_ICON_WIDTH - DLG_OFFSET,
			-(DLG_MENU_HIGHT + EXIT_ICON_HIGH) / 2 }
	};

	SIZE  ctrl_size[] = 
	{
		{ DLG_COLUMN1_W,	STATIC_HEIGHT   },
		{ DLG_COLUMN1_W,	STATIC_HEIGHT   },
		{ DLG_COLUMN1_W,	STATIC_HEIGHT   },
		{ DLG_COLUMN1_W,	STATIC_HEIGHT   },
		{ DLG_COLUMN1_W,	STATIC_HEIGHT   },
		{ DLG_COLUMN1_W,	STATIC_HEIGHT   },
			{ DLG_COLUMN2_W,	STATIC_HEIGHT   },
			{ DLG_COLUMN2_W,	STATIC_HEIGHT   },
			{ DLG_COLUMN2_W,	STATIC_HEIGHT   },
			{ 88,	STATIC_HEIGHT   },
			{ 88,	STATIC_HEIGHT   },
			{ DLG_COLUMN2_W,	STATIC_HEIGHT   },
			{ DLG_COLUMN2_W,	DLG_ROW6_H	  },
		{ DLG_COLUMN3_W, DLG_ROW_H },
		{ DLG_COLUMN3_W, DLG_ROW_H },
		{ DLG_COLUMN3_W, DLG_ROW_H },
		{ DLG_COLUMN3_W, DLG_ROW_H },
		{ EXIT_ICON_WIDTH,  EXIT_ICON_HIGH  } 
	};

	CTRLDATA ctrl_data [] =
	{
		{ CTRL_STATIC,  WS_VISIBLE | SS_SIMPLE, WS_EX_NONE, 0, 0, 0, 0,
			IDC_PATIENT_SETUP_NAME_L, STR_DLG_PATIENT_NAME, 0L, 0L},

		{ CTRL_STATIC,  WS_VISIBLE | SS_SIMPLE, WS_EX_NONE, 0, 0, 0, 0,
			IDC_PATIENT_SETUP_ID_L,  STR_DLG_PATIENT_ID, 0L, 0L},

		{ CTRL_STATIC,  WS_VISIBLE | SS_SIMPLE, WS_EX_NONE, 0, 0, 0, 0,
			IDC_PATIENT_SETUP_AGE_L, STR_DLG_PATIENT_AGE, 0L, 0L},

		{ CTRL_STATIC,  WS_VISIBLE | SS_SIMPLE, WS_EX_NONE, 0, 0, 0, 0,
			IDC_PATIENT_SETUP_GESTATIONAL_L, STR_DLG_PATIENT_GESTATIONAL, 0L, 0L},

		{ CTRL_STATIC,  WS_VISIBLE | SS_SIMPLE, WS_EX_NONE, 0, 0, 0, 0,
			IDC_PATIENT_SETUP_GTIMES_L, STR_DLG_PATIENT_GTIMES, 0L, 0L},

		{ CTRL_STATIC,  WS_VISIBLE | SS_SIMPLE, WS_EX_NONE, 0, 0, 0, 0,
			IDC_PATIENT_SETUP_NOTE_L, STR_DLG_PATIENT_NOTE, 0L, 0L},

		{ CTRL_EDIT,	WS_VISIBLE | WS_TABSTOP | ES_LEFT, WS_EX_NONE, 0, 0, 0, 0,
			IDC_PATIENT_SETUP_NAME_EDIT, STR_DLG_PATIENT_NAME_NAME, 0L, 0L},

		{ CTRL_EDIT,	WS_VISIBLE | WS_TABSTOP | ES_LEFT, WS_EX_NONE, 0, 0, 0, 0,
			IDC_PATIENT_SETUP_ID_EDIT, STR_DLG_PATIENT_ID_ID, 0L, 0L},

		{ CTRL_EDIT,	WS_VISIBLE | WS_TABSTOP | ES_LEFT, WS_EX_NONE, 0, 0, 0, 0,
			IDC_PATIENT_SETUP_AGE_EDIT, STR_DLG_PATIENT_AGE_AGE, 0L, 0L},

		{ CTRL_EDIT,	WS_VISIBLE | WS_TABSTOP | ES_LEFT, WS_EX_NONE, 0, 0, 0, 0,
			IDC_PATIENT_SETUP_GESTATIONAL_EDIT, STR_DLG_PATIENT_GESTATIONAL_WEEK, 0L, 0L},

		{ CTRL_EDIT,	WS_VISIBLE | WS_TABSTOP | ES_LEFT, WS_EX_NONE, 0, 0, 0, 0,
			IDC_PATIENT_SETUP_GESTATIONAL_DAY_EDIT, STR_DLG_PATIENT_GESTATIONAL_DAY, 0L, 0L},

		{ CTRL_EDIT,	WS_VISIBLE | WS_TABSTOP | ES_LEFT, WS_EX_NONE, 0, 0, 0, 0,
			IDC_PATIENT_SETUP_GTIMES_EDIT, STR_DLG_PATIENT_GTIMES_TIMES, 0L, 0L},

		{ CTRL_EDIT,	WS_VISIBLE | WS_TABSTOP | ES_AUTOWRAP, WS_EX_NONE, 0, 0, 0, 0,
			IDC_PATIENT_SETUP_NOTE_EDIT, STR_DLG_PATIENT_NOTE_PAD, 0L, 0L},

		{ CTRL_BUTTON,  WS_VISIBLE | WS_TABSTOP, WS_EX_NONE, 0, 0, 0, 0,
			IDC_PATIENT_SETUP_NEWPATIENT_B, STR_MAIN_BOTTOM_NEWPATIENT, 0L, 0L },

		{ CTRL_BUTTON,  WS_VISIBLE | WS_TABSTOP, WS_EX_NONE, 0, 0, 0, 0,
			IDC_PATIENT_SETUP_EDIT_B, STR_DLG_PATIENT_EDIT, 0L, 0L },

		{ CTRL_BUTTON,  WS_VISIBLE | WS_TABSTOP, WS_EX_NONE, 0, 0, 0, 0,
			IDC_PATIENT_SETUP_ANALY_B, STR_DLG_ANALY_FUNC, 0L, 0L },

		{ CTRL_BUTTON,  WS_VISIBLE | WS_TABSTOP, WS_EX_NONE, 0, 0, 0, 0,
			IDC_PATIENT_SETUP_RECALL_B, STR_MAIN_BOTTOM_RECALL, 0L, 0L },

		{ CTRL_BUTTON,  WS_VISIBLE | WS_TABSTOP | BS_ICON, WS_EX_NONE, 0, 0, 0, 0,
			IDC_PATIENT_SETUP_EXIT_B,   0, 0L, 0L} 
	};
	
	INT16 i, loops;
	loops = TABLESIZE(ctrl_data);
	WNDMEM   wndMem;
	
	wndMem.pMainWin = GetMainWndMem(IDD_PATIENT_SETUP);
	wndMem.pControl = GetCtrlWndMem(IDC_PATIENT_SETUP_FIRST);
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

	SetCtrlDataAddData2(ctrl_data, loops, IDC_PATIENT_SETUP_NAME_EDIT, 
						(UINT32)&edt_name);

	SetCtrlDataAddData2(ctrl_data, loops, IDC_PATIENT_SETUP_ID_EDIT, 
						(UINT32)&edt_id);

	SetCtrlDataAddData2(ctrl_data, loops, IDC_PATIENT_SETUP_AGE_EDIT, 
						(UINT32)&edt_age);

	SetCtrlDataAddData2(ctrl_data, loops, IDC_PATIENT_SETUP_GESTATIONAL_EDIT, 
						(UINT32)&edt_gWek);

	SetCtrlDataAddData2(ctrl_data, loops, IDC_PATIENT_SETUP_GESTATIONAL_DAY_EDIT, 
						(UINT32)&edt_gDay);

	SetCtrlDataAddData2(ctrl_data, loops, IDC_PATIENT_SETUP_GTIMES_EDIT, 
						(UINT32)&edt_gtms);

	SetCtrlDataAddData2(ctrl_data, loops, IDC_PATIENT_SETUP_NOTE_EDIT, 
						(UINT32)&edt_note);

	SetCtrlDataAddData2(ctrl_data, loops, IDC_PATIENT_SETUP_RECALL_B, 
						(UINT32)&btn_old);

	SetCtrlDataAddData2(ctrl_data, loops, IDC_PATIENT_SETUP_NEWPATIENT_B, 
						(UINT32)&btn_new);

	SetCtrlDataAddData2(ctrl_data, loops, IDC_PATIENT_SETUP_EDIT_B, 
						(UINT32)&btn_edit);

	SetCtrlDataAddData2(ctrl_data, loops, IDC_PATIENT_SETUP_ANALY_B, 
						(UINT32)&btn_anly);

	SetCtrlDataAddData2(ctrl_data, loops, IDC_PATIENT_SETUP_EXIT_B, 
						(UINT32)&btn_exit);

	DialogBoxIndirectParam(&dlg_data, parent, IDD_PATIENT_SETUP,
							PatientSetupProc, 0, &wndMem);
}


// For Net
VOID UpdateMenuPatientGender(VOID)
{}

VOID ChangePatientGender(INT16 gender)
{

}

VOID UpdateMenuPatientType(VOID)
{}

VOID NetChangePatientType(INT16 type)
{
  if (MonitorConfig.patientType == type)
	  return;

  MonitorConfig.patientType = type;
  Patient_ChangeType();

  // 刷新菜单
  UpdateMenuPatientType();
}


