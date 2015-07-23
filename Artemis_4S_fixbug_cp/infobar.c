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
#define   INFOBAR_GLOBALS 
#include  "includes.h"

static  SYSINFO_MAN	SysInfo_Man;

BOOL   InitSysInfoItem (VOID)
{
   //VOID   *pBuf;
   INT	 i;

   ZeroMemory(&SysInfo_Man, sizeof(SYSINFO_MAN));
   
   for (i = 0; i < MAX_SYSINFO_ITEM_NUM; i ++) {
	   SysInfo_Man.items[i].id = i;
   }
   
   SysInfo_Man.total  = MAX_SYSINFO_ITEM_NUM;
   SysInfo_Man.curr   = 0;
   SysInfo_Man.inShow = 0;
   Chain_Initialize_empty(&SysInfo_Man.work);
   Chain_Initialize_empty(&SysInfo_Man.free);
   Chain_Initialize(&SysInfo_Man.free, SysInfo_Man.items, MAX_SYSINFO_ITEM_NUM, sizeof(SYSINFO_ITEM));
   SysInfo_Man.semaphore = (HANDLE)(&SysInfoItemSem); 

   return TRUE;
}

/* 以下是信息栏的操作实现 */

static BOOL  Item_IsInLink (PCHAIN_CONTROL pControl, PCHAIN_NODE pNode)
{
	PCHAIN_NODE pNext;

	if (Chain_Is_empty(pControl))
		return FALSE;
		
	pNext = Chain_Head(pControl);
	while (!Chain_Is_last(pNext)) {
	   if (_Addresses_Equal(pNext, pNode)) {
		   return TRUE;
	   }
	   pNext = pNext->next;
	}
	return FALSE;
}

static  PCHAIN_NODE  InfoId_IsInLink (PCHAIN_CONTROL pControl, INT16 str_id)
{
	PCHAIN_NODE pNext;

	if (Chain_Is_empty(pControl))
		return 0;
		
	pNext = Chain_Head(pControl);
	while (!Chain_Is_last(pNext))
	{
	   if (((PSYSINFO_ITEM)pNext)->infoId == str_id) 
	   {
		   return  pNext;
	   }
	   pNext = pNext->next;
	}
	return 0;
}


/**
 ** 注册信息栏的消息条显示  
 ** 注册时, 时间不能小于等于0;否则,在更新当前信息条由于一次仅处理一个单元;会
 ** 导致时间等于0的单元也有机会显示的.
 **/
INT16  RegisterSysInfoItem (const PHINT_INFO pHint)
{
	pthread_mutex_t *mutex;
	UINT8	 err;
	INT16	 result;
	PSYSINFO_ITEM pItem;

	ASSERT_REPORT(pHint->duration > 0);
	result = -1;
	
	if (SysInfo_Man.semaphore) 
	{
		mutex = (pthread_mutex_t *)(SysInfo_Man.semaphore);
		pthread_mutex_lock(mutex);
	}

	pItem = (PSYSINFO_ITEM)InfoId_IsInLink(&SysInfo_Man.work, pHint->infoId);
	if (pItem)  //原来已经注册过. 
	{ 
		pItem->color		 = pHint->color;
		pItem->duration	  = pHint->duration;
		pItem->exclusiveShow = pHint->exclusiveShow;
		result = pItem->id;
		goto exit;
	} 
	
	pItem = (PSYSINFO_ITEM)Chain_Get_unprotected(&SysInfo_Man.free);
	if (pItem) 
	{
		pItem->infoId		= pHint->infoId;
		pItem->color		 = pHint->color;
		pItem->duration	  = pHint->duration;
		pItem->exclusiveShow = pHint->exclusiveShow;
		Chain_Append_unprotected(&SysInfo_Man.work, (PCHAIN_NODE)pItem);
		
		result = pItem->id;
	} 
	else 
	{
		result = -1;
	}

exit:
	if (SysInfo_Man.semaphore)
	{
	  pthread_mutex_unlock(mutex);
	}

	return result;
}

static  PSYSINFO_ITEM  Update_CurrInfoItem (VOID)
{
	PSYSINFO_ITEM  pCurr;
	PSYSINFO_ITEM  pNext;

	if (Chain_Is_empty(&SysInfo_Man.work)) {
		return  0;
	}
	pCurr = SysInfo_Man.curr;
	
	pNext = (PSYSINFO_ITEM)pCurr->next;//取下一个;
	if (!Chain_Is_last((PCHAIN_NODE)pNext)) {
		return pNext;
	}

	//如果到了链表的最后; 则回绕到第一个单元.
	pNext = (PSYSINFO_ITEM)SysInfo_Man.work.first;
	if (!Chain_Is_first((PCHAIN_NODE)pNext)) {
		return pNext;
	}
	return 0;
}

/* 注销信息栏的消息条  */
VOID  RemoveSysInfoItem (INT16 id)
{
	pthread_mutex_t	*mutex;
	UINT8	 err;
	PSYSINFO_ITEM pItem;
	
	if (id < 0 || id >= MAX_SYSINFO_ITEM_NUM)
	   return;

	if (SysInfo_Man.semaphore) {
		mutex = (pthread_mutex_t *)SysInfo_Man.semaphore; 
		pthread_mutex_lock(mutex);
	}
	
	pItem = (PSYSINFO_ITEM)(SysInfo_Man.items + id);

	if (_Addresses_Equal(pItem, SysInfo_Man.curr)) { //如果是当前显示的信息条，则要更新找下一个。
		SysInfo_Man.curr = Update_CurrInfoItem();
	} 

	if (Item_IsInLink(&SysInfo_Man.work, (PCHAIN_NODE)pItem)) {
		Chain_Extract_unprotected((PCHAIN_NODE)pItem);
		Chain_Append_unprotected(&SysInfo_Man.free, (PCHAIN_NODE)pItem);
	}
	if (SysInfo_Man.semaphore) {
	  pthread_mutex_unlock(mutex);
	}
}

/**
 ** 注销信息条, 但是不要信号量保护
**/
VOID  Remove_SysInfoItemEx (INT16 id)
{
	PSYSINFO_ITEM pItem;

	if (id < 0 || id >= MAX_SYSINFO_ITEM_NUM)
	   return;
	   
	pItem = (PSYSINFO_ITEM)(SysInfo_Man.items + id);
	
	if (_Addresses_Equal(pItem, SysInfo_Man.curr)) {
		SysInfo_Man.curr = Update_CurrInfoItem();
	}

	if (Item_IsInLink(&SysInfo_Man.work, (PCHAIN_NODE)pItem)) {
		Chain_Extract_unprotected((PCHAIN_NODE)pItem);
		Chain_Append_unprotected(&SysInfo_Man.free, (PCHAIN_NODE)pItem);
	}
}

// 动态显示信息条
VOID  ShowSysInfoItem (VOID)
{}


// 保存最近一次电池电量和电源状态.
static UINT8  Power_State = 0;
static INT8   Batt_Volume = -1;

// Show battary box; 显示电池电量
VOID  ShowBattaryState (VOID)
{
	HWND hCtrl;
	HDC  hdc;
	CHAR szTxt[4];
	if (Batt_Volume < 0)
	{
		return;
	}
	sprintf(szTxt, "%3d", Batt_Volume);
	hCtrl = GetDlgItem(MainScnHWnd, IDC_TOPBAR_STATUS_BAT_L);
	if (!hCtrl)
		return;
	SetWindowItem(hCtrl, (DWORD)full_icon[MonitorConfig.nightModeOn]);
}

VOID ShowStatusIcon (VOID)
{
	SetStatusDlgItem();
	UpdateACIcon();
	UpdateBatteryIcon();
	UpdateNetworkIcon();
	UpdatePrinterIcon();
	UpdateFhrVolIcon();
	UpdateAlmVolIcon();
}

VOID SetStatus(UINT8 index, UCHAR *icon)
{
	HWND hCtrl;
	hCtrl = GetDlgItem(MainScnHWnd, IDC_TOPBAR_STATUS_AC_L + index);
	if (!hCtrl)
		return;
	SetWindowItem(hCtrl, (DWORD)icon);
}

VOID   InitTopbar(HANDLE hMainWin, UINT32 lParam)
{
	HWND   hwnd;

	lParam = lParam;
	SetWindowBkColor(hMainWin, GetWindowElementColor(BKC_CAPTION_NORMAL));

	hwnd = GetDlgItem(hMainWin, IDC_TOPBAR_ALARM_TECH_G);
	EnableWindow(hwnd, TRUE);
	SetWindowBkColor(hwnd, GetWindowElementColor(BKC_CAPTION_NORMAL));

	hwnd = GetDlgItem(hMainWin, IDC_TOPBAR_ALARM_PHYS_G);
	EnableWindow(hwnd, TRUE);
	SetWindowBkColor(hwnd, GetWindowElementColor(BKC_CAPTION_NORMAL));

	hwnd = GetDlgItem(hMainWin, IDC_TOPBAR_STATUS_G);
	EnableWindow(hwnd, TRUE);
	SetWindowBkColor(hwnd, GetWindowElementColor(BKC_CAPTION_NORMAL));

	hwnd = GetDlgItem(hMainWin, IDC_TOPBAR_ALM_LVL_L);
	SetWindowBkColor(hwnd, GetWindowElementColor(BKC_CAPTION_NORMAL));
	SetWindowTextColor(hwnd, GetWindowElementColor(FGC_CAPTION_NORMAL));
	SetWindowFont(hwnd, GetSystemFont(SYSLOGFONT_WCHAR_DEF));

	hwnd = GetDlgItem(hMainWin, IDC_TOPBAR_ALM_INFO_L);
	SetWindowBkColor(hwnd, GetWindowElementColor(BKC_CAPTION_NORMAL));
	SetWindowTextColor(hwnd, GetWindowElementColor(FGC_CAPTION_NORMAL));
	SetWindowFont(hwnd, GetSystemFont(SYSLOGFONT_FIXED));


	hwnd = GetDlgItem(hMainWin, IDC_TOPBAR_ALM_DATE_L);
	SetWindowBkColor(hwnd, GetWindowElementColor(BKC_CAPTION_NORMAL));
	SetWindowTextColor(hwnd, GetWindowElementColor(FGC_CAPTION_NORMAL));
	SetWindowFont(hwnd, GetSystemFont(SYSLOGFONT_DEFAULT));

	hwnd = GetDlgItem(hMainWin, IDC_TOPBAR_ALM_TIME_L);
	SetWindowBkColor(hwnd, GetWindowElementColor(BKC_CAPTION_NORMAL));
	SetWindowTextColor(hwnd, GetWindowElementColor(FGC_CAPTION_NORMAL));
	SetWindowFont(hwnd, GetSystemFont(SYSLOGFONT_DEFAULT));
}

VOID  ShowSysDatetime (DATETIME *datetime)
{}

INT32  TopbarProc (HANDLE hdl, INT32 msg, UINT32 wParam, UINT32 lParam)
{
	int	str_id;
	HWND   hwnd;
	
	switch (msg) 
		{
		case  MSG_INITDIALOG:
			InitTopbar(hdl, lParam);
			return 0;
						 
		default:
			break;
	}
	
	return DefaultMainWinProc(hdl, msg, wParam, lParam);
}



/**
 ** Top Bar's Height is 25; The Frame is 1 width; So the client is 23 height;
 ** Alarm Icon is 20 x 14 ( W x H );
 **/


/**
	对本主窗口所属的控件进行特定的设置;
	
	控件默认的颜色, 可能不符合标题栏的要求;重新设置颜色.
	控件默认的字体可能不适合, 需要重新设置.
	在winstr.cpp,定义全局字符缓冲区时, 定义了一些填充的字符:0123456789...,在第一次显示时会错误.
**/
VOID  InitBottombar (HANDLE hMainWin, UINT32 lParam)
{}


INT32  BottombarProc (HANDLE hdl, INT32 msg, UINT32 wParam, UINT32 lParam)
{
	HWND   hwnd;
	INT16  str_id;
	
	switch (msg) {
		case  MSG_INITDIALOG:
			InitBottombar(hdl, lParam);
			return 0;

		default:
			break;
	}
	
	return DefaultMainWinProc(hdl, msg, wParam, lParam);
}

/**
 **  Bottom Bar's height is 20. And It's frame is 1 width;So client range is 18 height;
 **  Battary icon is 32x16(w x h);
 **/
BOOL   CreateBottomBar (VOID)
{}

