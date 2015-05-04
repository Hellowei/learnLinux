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
#define   SCRMAN_GLOBALS 
#include  "includes.h"

//在static控件上的客户区绘制波形.
static  INT16   Wave_CtrlId[WAVE_MAX] = {
	IDC_MAIN_GRAPH_FHR_L,
	IDC_MAIN_GRAPH_FHR_L,
	IDC_MAIN_GRAPH_TOCO_L,
	IDC_MAIN_GRAPH_TOCO_L,
};


/* 屏幕基本信息 */
BOOL  InitScrBaseInfo(VOID)
{
	ParaScnBaseInfo.avgDispMaxRow		   = 4;
	ParaScnBaseInfo.parameterRegionHeight   = MIDDLE_HEIGHT;
	return TRUE;
}


BOOL  CeateWaveCtrlGroup(VOID)
{
	return TRUE;
	PCONTROL  pCtrl;
	HWND	  hWnd;
	int	   i;
	int	   id;
	int	   wave_name;
	long	  x, y;
	
	for (i = 0; i < LayoutBlockInfo.numOfWaveBlock; i++) {
		 wave_name = LayoutBlockInfo.waveBlocksInfo[i].name;
		 id		= Wave_CtrlId[wave_name];
		 pCtrl	 = GetCtrlWndMem(id);
		 x		 = LayoutBlockInfo.waveBlocksInfo[i].x;
		 y		 = LayoutBlockInfo.waveBlocksInfo[i].y;
		 ScreenToClient(MainScnHWnd, &x, &y);
		 hWnd  = CreateWindowEx( CTRL_STATIC,
								 0, 
								 SS_OWNERDRAW | WS_VISIBLE | WS_ABSSCRPOS,
								 0,
								 id,
								 x,
								 y,
								 LayoutBlockInfo.waveBlocksInfo[i].width  - 1,
								 LayoutBlockInfo.waveBlocksInfo[i].height - 1,
								 MainScnHWnd,
								 0,
								 0,
								 pCtrl );


		 if (hWnd == HWND_INVALID)  
			 return FALSE;
			 
		 SetWindowTextColor(hWnd,PIXEL_white);
	}

	return TRUE;
}


INT  CreateSysMainWindow (VOID)
{
	MAINWINCREATE CreateInfo;
	HWND		  hFocus;
	
	CreateInfo.dwReserved   = 0;
	
	CreateInfo.dwStyle	  = WS_ABSSCRPOS & (~WS_VISIBLE);
	CreateInfo.dwExStyle	= 0;
	CreateInfo.caption	  = 0;
	CreateInfo.proc		 = MainScnProc;
	CreateInfo.lx		   = 0;
	CreateInfo.ty		   = 0;
	CreateInfo.rx		   = SCREEN_WIDTH;
	CreateInfo.by		   = SCREEN_HIGH;
	CreateInfo.id		   = IDM_MAIN;
	CreateInfo.iBkColor	 = PARAM_REGION_BKCOLOR;
	CreateInfo.textColor	= GetWindowElementColor (FGC_CONTROL_DEF);
	CreateInfo.dwAddData	= 0;
/** /
	if ((MonitorConfig.faceType == FACE_STD))
	{
		GetMainWndMem(IDM_MAIN)->pBackground = 
			Get24BitmapInfo(graph_background,
							&(GetMainWndMem(IDM_MAIN)->iLineBytes));
	}
	else
	{
		GetMainWndMem(IDM_MAIN)->pBackground = 
			Get24BitmapInfo(bigfn_background,
							&(GetMainWndMem(IDM_MAIN)->iLineBytes));
	}
/**/
	MainScnHWnd = CreateMainWindow (&CreateInfo, GetMainWndMem(IDM_MAIN), SysGui_HTSK);
	if (MainScnHWnd == HWND_INVALID)
		return -1;
	
	CreateParamGroup();
	CreateGroupsCtrlGroup();
	CreateInfobarBoard();
	if (MonitorConfig.faceType == FACE_STD || MonitorConfig.faceType == FACE_STD_SINGLE)
	{
		CreateGraphGroup();
	}
	else
	{
		CreateDemoLabel();
	}
	if (MonitorConfig.showHelp)
	{
		AddHelpString();
	}
	//CeateHotkeyCtrlGroup();

	SendMessage (MainScnHWnd, MSG_INITDIALOG, 0, 0);
	ShowWindow(MainScnHWnd, SW_SHOWNORMAL);
//	hFocus = GetNextDlgTabItem (MainScnHWnd, (HWND)0, FALSE);
//	if (hFocus) {
//		SetFocus(hFocus);
//	}
	{
		HWND hCtrl;
		PCONTROL pCtrl;
		HDC  hdc;
		PDC  pdc;
		hdc = GetDC(MainScnHWnd);
		pdc = dc_HDC2PDC(hdc);
		SetPenColor(hdc, PIXEL_black);
		if (hCtrl = GetDlgItem(MainScnHWnd, IDC_MAIN_PARAM_FHR1_G))
		{
			pCtrl = (PCONTROL)hCtrl;
			//Rect(hdc, pCtrl->cl, pCtrl->ct, pCtrl->cr, pCtrl->cb);
			Rect(hdc, pCtrl->cl+1, pCtrl->ct+1, pCtrl->cr-1, pCtrl->cb);
		}
		if (hCtrl = GetDlgItem(MainScnHWnd, IDC_MAIN_PARAM_FHR2_G))
		{
			pCtrl = (PCONTROL)hCtrl;
			//Rect(hdc, pCtrl->cl, pCtrl->ct, pCtrl->cr, pCtrl->cb);
			Rect(hdc, pCtrl->cl+1, pCtrl->ct+1, pCtrl->cr-1, pCtrl->cb);
		}
		if (hCtrl = GetDlgItem(MainScnHWnd, IDC_MAIN_PARAM_TOCO_G))
		{
			pCtrl = (PCONTROL)hCtrl;
			//Rect(hdc, pCtrl->cl, pCtrl->ct, pCtrl->cr, pCtrl->cb);
			Rect(hdc, pCtrl->cl+1, pCtrl->ct+1, pCtrl->cr-1, pCtrl->cb);
		}
		if (hCtrl = GetDlgItem(MainScnHWnd, IDC_MAIN_PARAM_FM_G))
		{
			pCtrl = (PCONTROL)hCtrl;
			//Rect(hdc, pCtrl->cl, pCtrl->ct, pCtrl->cr, pCtrl->cb);
			Rect(hdc, pCtrl->cl+1, pCtrl->ct+1, pCtrl->cr-1, pCtrl->cb);
		}
		
		ReleaseDC(hdc);
	}
	return 0;
}



/************************************************************************/
/*  函数名：InitWaveTypeInfo											*/
/*  描述：  初始化波形类型的值										  */
/*  参数：  无														  */
/*  返回值：无														  */
/************************************************************************/
VOID  InitWaveTypeInfo (VOID)
{
	INT16 i;

	MonitorInfo.waveTypeNum = 0;
	for ( i = 0; i < WAVE_TYPE_MAX; i ++ )
		MonitorInfo.waveTypeSeq[i] = -1;
	
	return;
};


VOID GetWaveBlockInfo(VOID)
{
	int no = 0;
	if (MonitorConfig.faceType == FACE_STD || MonitorConfig.faceType == FACE_STD_SINGLE)
	{
		if (FhrConfig.enbFhr1 == TRUE)
		{
			LayoutBlockInfo.waveBlocksInfo[no++].name = WAVE_FHR_CH1;
		}
		if (FhrConfig.enbFhr2 == TRUE)
		{
			LayoutBlockInfo.waveBlocksInfo[no++].name = WAVE_FHR_CH2;
		}
		if (FhrConfig.enbToco == TRUE)
		{
			LayoutBlockInfo.waveBlocksInfo[no++].name = WAVE_TOCO;
		}
		if (FhrConfig.enbAfm  == TRUE)
		{
			LayoutBlockInfo.waveBlocksInfo[no++].name = WAVE_AFM;
		}
	}
	LayoutBlockInfo.numOfWaveBlock = no;
}


VOID  PaintParamBlockFrame(VOID)
{
	long  x, y;
	int   i;
	int   w, h;
	
	SetPenColor(HDC_SCREEN, COLOR_white);
	for (i = 0; i < LayoutBlockInfo.numOfParamBlock; i++) {
		x = LayoutBlockInfo.paramBlocksInfo[i].x;
		y = LayoutBlockInfo.paramBlocksInfo[i].y;
		h = LayoutBlockInfo.paramBlocksInfo[i].height;
		if( FACE_BIGFONT == MonitorConfig.faceType )  //modified by empty 2011/01/18
		{
			w = LayoutBlockInfo.paramBlocksInfo[i].width + 2;
		}
		else
		{
			w = LayoutBlockInfo.paramBlocksInfo[i].width + 8;
		}
		Line(HDC_SCREEN, x,	 y,	 x,	 y + h);
		Line(HDC_SCREEN, x + w, y,	 x + w, y + h);
		Line(HDC_SCREEN, x,	 y,	 x + w, y	);
		Line(HDC_SCREEN, x,	 y + h, x + w, y + h);
	}
}

/**
 **  在建立对话框之前, 需要x和y的坐标.
 **  pTemplate, 对话框的消息.
 **/
INT16  GetDialogPos (PDLGTEMPLATE pTemplate, INT32 *x, INT32 *y)
{
  RECT	rc;
  
  GetWindowRect(MainScnHWnd, &rc);
  *x = (RECTW(rc) - pTemplate->w) / 2;
  *y = (RECTH(rc) - pTemplate->h) / 2;
  return 0;
}

/**
 ** 进入对话框布局管理.
 **
 **/
VOID  EnterDialogLayout (INT16 top_ndx, INT16 wave_ndx)
{
  BOOL override_flag; // TRUE, 覆盖; FALSE, 恢复
  INT16 i, wave_name, wave_num, start_pos;
 
  if (top_ndx < 0 && wave_ndx < 0) 
  {
	return; // 全部都不需要覆盖菜单.
  }
  
  if (top_ndx == wave_ndx)
  {
	return; // 本地菜单和上一级菜单占用相同的区域.
  }
  
  if (top_ndx < 0) 
  { 
	// 上一级菜单没有覆盖，本地菜单需要覆盖.
	start_pos = wave_ndx;
	wave_num  = LayoutBlockInfo.numOfWaveBlock - wave_ndx;
	override_flag = TRUE;
  } 
  else if (wave_ndx < 0) 
  {
	// 
	start_pos = top_ndx;
	wave_num  = LayoutBlockInfo.numOfWaveBlock - top_ndx;
	override_flag = FALSE;
  }
  else if (top_ndx > wave_ndx) 
  { 
	// 本地菜单需要覆盖比上一级菜单更多的波形区.
	start_pos = wave_ndx;
	wave_num = top_ndx - wave_ndx;
	override_flag = TRUE;
  }
  else 
  { 
	// top_ndx < wave_ndx, 本地菜单需要覆盖的波形区比上一级菜单少,恢复部分波形.
	start_pos = top_ndx;
	override_flag = FALSE;
	wave_num = wave_ndx - top_ndx;
  }
  
  if (override_flag) 
  { 
	// 覆盖操作.
	for (i = 0; i < wave_num; ++ i)
	{
	  wave_name = LayoutBlockInfo.waveBlocksInfo[start_pos].name;
	  start_pos ++;
	}
  } 
  else 
  {  
	// 恢复操作.
	for (i = 0; i < wave_num; ++ i) 
	{
	  wave_name = LayoutBlockInfo.waveBlocksInfo[start_pos].name;
	  start_pos ++;
	}
  }
}


/**
 ** 退出对话框布局管理.
 **
 **/
VOID  ExitDialogLayout (INT16 top_ndx, INT16 wave_ndx)
{
  BOOL override_flag; //TRUE, 覆盖; FALSE, 恢复
  INT16 i, wave_name, wave_num, start_pos;
  
  if (top_ndx < 0 && wave_ndx < 0) 
  {
	return; // 全部都不需要覆盖菜单.
  }
  
  if (top_ndx == wave_ndx) 
  {
	return; // 本地菜单和上一级菜单占用相同的区域.
  }
  
  if (top_ndx < 0)
  { 
	// 上一级菜单没有覆盖，本地菜单曾经覆盖的
	start_pos = wave_ndx;
	wave_num  = LayoutBlockInfo.numOfWaveBlock - wave_ndx;
	override_flag = FALSE;
  }
  else if (wave_ndx < 0) 
  { 
	// 
	start_pos = top_ndx;
	wave_num  = LayoutBlockInfo.numOfWaveBlock - top_ndx;
	override_flag = TRUE;
  } 
  else if (top_ndx > wave_ndx) 
  { 
	// 本地菜单需要覆盖比上一级菜单更多的波形区。退出前恢复
	start_pos = wave_ndx;
	wave_num = top_ndx - wave_ndx;
	override_flag = FALSE;
  }
  else 
  { 
	// top_ndx < wave_ndx, 本地菜单需要覆盖的波形区比上一级菜单少，重新覆盖它们
	start_pos = top_ndx;
	override_flag = TRUE;
	wave_num = wave_ndx - top_ndx;
  }
  
  if (override_flag)
  {  
	// 覆盖操作
	for (i = 0; i < wave_num; i ++)
	{
	  wave_name = LayoutBlockInfo.waveBlocksInfo[start_pos].name;
	  start_pos ++;
	}
  }
  else 
  { 
	// 恢复操作
	for (i = 0; i < wave_num; i ++) 
	{
	  wave_name = LayoutBlockInfo.waveBlocksInfo[start_pos].name;
	  start_pos ++;
	}
  }
  
  //ReInitWave();
}


/**
	开始一次布局调整.
	首先,应该设置好 界面参数: face type, ecg face, show_alarm_limits, etc.
	而后, 邮寄消息--回退主屏.
	最后, 邮寄消息--开始界面调整.
**/
VOID  GUIAPI  StartLayoutSession(VOID)
{
	PostMessage(SysGui_HTSK, MSG_SCRMAN, SM_START_LAYOUT, 0);
}

/**
	 本函数必须在GUI任务中调用.
	 重新划分屏幕. 
	 包括, 创建标题栏(topbar), 创建状态栏(bottombar), 系统主窗口(波形区,参数区,热键).
	 
**/
BOOL CreateMainGroups();
INT32  LayoutScreen(VOID)
{
	static int face = -1;
	LayoutInProcess = TRUE;
	MonitorInfo.faceChanged = TRUE;
    RESID LastCtrlID     = 0;
	HWND hCtrl = HWND_INVALID;
	if (face >= 0)
	{
		hCtrl = GetFocus(MainScnHWnd);
		if (HWND_INVALID != hCtrl)
			LastCtrlID = ((PWIN)hCtrl)->id;
		DestroyAllControls(MainScnHWnd);
		DestroyMainWindow(MainScnHWnd);
	}
	GetWaveBlockInfo();
	
	face = CreateSysMainWindow();
	
	LayoutInProcess = FALSE;
	ReInitFetalWave();
	InitLastParaValue();
	//ReinitWave();
	//CreateSysMenus();
	//CreateTopBar();
	//CreateBottomBar();
	//CreateMainGroups();
	DisplayAlarmSign();
	if (HWND_INVALID != hCtrl && LastCtrlID)
		hCtrl = GetDlgItem(MainScnHWnd, LastCtrlID);
	else
		hCtrl = GetNextDlgTabItem (MainScnHWnd, (HWND)0, FALSE);
	if (hCtrl && HWND_INVALID != hCtrl)
		SetFocus(hCtrl);
}

HWND   GetHWndFromWaveName(INT wave_name)
{
	INT16 ctrl_id;

	ASSERT_REPORT(wave_name < WAVE_MAX && wave_name >= 0 );
	
	ctrl_id = Wave_CtrlId[wave_name];

	return GetDlgItem(MainScnHWnd, ctrl_id);
}

/**
 ** 注意,只能在和desktop同一任务中调用.
 ** 否则, PostMessage(SysGui_HTSK, MSG_USER_SYS_KEYMSG, KEY_MAIN, 0);
 **/
VOID   GUIAPI  BacktoMainScreen(VOID)
{
	SendMessage(HWND_DESKTOP, MSG_SCRMAN, SM_BACKMAIN, 0);
}

