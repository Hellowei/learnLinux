/*****************************************************************************************
��Ȩ����:			�����ص�
�汾��:				1.0.0
��������:			2011.04.15
�ļ���:				
����:				�����ص�
����˵��:			
����˵��:			��
�����ļ���ϵ:		���ļ�Ϊ���̹�Լ�����ļ�

�޸ļ�¼:
��¼1:
�޸���:
�޸�����:
�޸�����:
�޸�ԭ��:
*****************************************************************************************/
#define   SCRMAN_GLOBALS 
#include  "includes.h"

//��static�ؼ��ϵĿͻ������Ʋ���.
static  INT16   Wave_CtrlId[WAVE_MAX] = {
	IDC_MAIN_GRAPH_FHR_L,
	IDC_MAIN_GRAPH_FHR_L,
	IDC_MAIN_GRAPH_TOCO_L,
	IDC_MAIN_GRAPH_TOCO_L,
};


/* ��Ļ������Ϣ */
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
/*  ��������InitWaveTypeInfo											*/
/*  ������  ��ʼ���������͵�ֵ										  */
/*  ������  ��														  */
/*  ����ֵ����														  */
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
 **  �ڽ����Ի���֮ǰ, ��Ҫx��y������.
 **  pTemplate, �Ի������Ϣ.
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
 ** ����Ի��򲼾ֹ���.
 **
 **/
VOID  EnterDialogLayout (INT16 top_ndx, INT16 wave_ndx)
{
  BOOL override_flag; // TRUE, ����; FALSE, �ָ�
  INT16 i, wave_name, wave_num, start_pos;
 
  if (top_ndx < 0 && wave_ndx < 0) 
  {
	return; // ȫ��������Ҫ���ǲ˵�.
  }
  
  if (top_ndx == wave_ndx)
  {
	return; // ���ز˵�����һ���˵�ռ����ͬ������.
  }
  
  if (top_ndx < 0) 
  { 
	// ��һ���˵�û�и��ǣ����ز˵���Ҫ����.
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
	// ���ز˵���Ҫ���Ǳ���һ���˵�����Ĳ�����.
	start_pos = wave_ndx;
	wave_num = top_ndx - wave_ndx;
	override_flag = TRUE;
  }
  else 
  { 
	// top_ndx < wave_ndx, ���ز˵���Ҫ���ǵĲ���������һ���˵���,�ָ����ֲ���.
	start_pos = top_ndx;
	override_flag = FALSE;
	wave_num = wave_ndx - top_ndx;
  }
  
  if (override_flag) 
  { 
	// ���ǲ���.
	for (i = 0; i < wave_num; ++ i)
	{
	  wave_name = LayoutBlockInfo.waveBlocksInfo[start_pos].name;
	  start_pos ++;
	}
  } 
  else 
  {  
	// �ָ�����.
	for (i = 0; i < wave_num; ++ i) 
	{
	  wave_name = LayoutBlockInfo.waveBlocksInfo[start_pos].name;
	  start_pos ++;
	}
  }
}


/**
 ** �˳��Ի��򲼾ֹ���.
 **
 **/
VOID  ExitDialogLayout (INT16 top_ndx, INT16 wave_ndx)
{
  BOOL override_flag; //TRUE, ����; FALSE, �ָ�
  INT16 i, wave_name, wave_num, start_pos;
  
  if (top_ndx < 0 && wave_ndx < 0) 
  {
	return; // ȫ��������Ҫ���ǲ˵�.
  }
  
  if (top_ndx == wave_ndx) 
  {
	return; // ���ز˵�����һ���˵�ռ����ͬ������.
  }
  
  if (top_ndx < 0)
  { 
	// ��һ���˵�û�и��ǣ����ز˵��������ǵ�
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
	// ���ز˵���Ҫ���Ǳ���һ���˵�����Ĳ��������˳�ǰ�ָ�
	start_pos = wave_ndx;
	wave_num = top_ndx - wave_ndx;
	override_flag = FALSE;
  }
  else 
  { 
	// top_ndx < wave_ndx, ���ز˵���Ҫ���ǵĲ���������һ���˵��٣����¸�������
	start_pos = top_ndx;
	override_flag = TRUE;
	wave_num = wave_ndx - top_ndx;
  }
  
  if (override_flag)
  {  
	// ���ǲ���
	for (i = 0; i < wave_num; i ++)
	{
	  wave_name = LayoutBlockInfo.waveBlocksInfo[start_pos].name;
	  start_pos ++;
	}
  }
  else 
  { 
	// �ָ�����
	for (i = 0; i < wave_num; i ++) 
	{
	  wave_name = LayoutBlockInfo.waveBlocksInfo[start_pos].name;
	  start_pos ++;
	}
  }
  
  //ReInitWave();
}


/**
	��ʼһ�β��ֵ���.
	����,Ӧ�����ú� �������: face type, ecg face, show_alarm_limits, etc.
	����, �ʼ���Ϣ--��������.
	���, �ʼ���Ϣ--��ʼ�������.
**/
VOID  GUIAPI  StartLayoutSession(VOID)
{
	PostMessage(SysGui_HTSK, MSG_SCRMAN, SM_START_LAYOUT, 0);
}

/**
	 ������������GUI�����е���.
	 ���»�����Ļ. 
	 ����, ����������(topbar), ����״̬��(bottombar), ϵͳ������(������,������,�ȼ�).
	 
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
 ** ע��,ֻ���ں�desktopͬһ�����е���.
 ** ����, PostMessage(SysGui_HTSK, MSG_USER_SYS_KEYMSG, KEY_MAIN, 0);
 **/
VOID   GUIAPI  BacktoMainScreen(VOID)
{
	SendMessage(HWND_DESKTOP, MSG_SCRMAN, SM_BACKMAIN, 0);
}

