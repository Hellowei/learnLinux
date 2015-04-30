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

/* ��������Ϣ���Ĳ���ʵ�� */

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
 ** ע����Ϣ������Ϣ����ʾ  
 ** ע��ʱ, ʱ�䲻��С�ڵ���0;����,�ڸ��µ�ǰ��Ϣ������һ�ν�����һ����Ԫ;��
 ** ����ʱ�����0�ĵ�ԪҲ�л�����ʾ��.
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
	if (pItem)  //ԭ���Ѿ�ע���. 
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
	
	pNext = (PSYSINFO_ITEM)pCurr->next;//ȡ��һ��;
	if (!Chain_Is_last((PCHAIN_NODE)pNext)) {
		return pNext;
	}

	//���������������; ����Ƶ���һ����Ԫ.
	pNext = (PSYSINFO_ITEM)SysInfo_Man.work.first;
	if (!Chain_Is_first((PCHAIN_NODE)pNext)) {
		return pNext;
	}
	return 0;
}

/* ע����Ϣ������Ϣ��  */
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

	if (_Addresses_Equal(pItem, SysInfo_Man.curr)) { //����ǵ�ǰ��ʾ����Ϣ������Ҫ��������һ����
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
 ** ע����Ϣ��, ���ǲ�Ҫ�ź�������
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

// ��̬��ʾ��Ϣ��
VOID  ShowSysInfoItem (VOID)
{}


// �������һ�ε�ص����͵�Դ״̬.
static UINT8  Power_State = 0;
static INT8   Batt_Volume = -1;

// Show battary box; ��ʾ��ص���
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
	�Ա������������Ŀؼ������ض�������;
	
	�ؼ�Ĭ�ϵ���ɫ, ���ܲ����ϱ�������Ҫ��;����������ɫ.
	�ؼ�Ĭ�ϵ�������ܲ��ʺ�, ��Ҫ��������.
	��winstr.cpp,����ȫ���ַ�������ʱ, ������һЩ�����ַ�:0123456789...,�ڵ�һ����ʾʱ�����.
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

