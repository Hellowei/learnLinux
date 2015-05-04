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
#if !defined(_SYSMENU_H)
#define	  _SYSMENU_H

/* 用于显示对话框的屏幕区域的大小高度. */
#define DLG_REGION_X  0
#define DLG_REGION_Y  380
#define DLG_REGION_W  550
#define DLG_REGION_H  200

#define BOTTOMBAR_HEIGHT 50

#ifdef SYSMENU_GLOBALS
#define SYSMENU_EXT 
#else 
#define SYSMENU_EXT extern 
#endif


//SYSMENU_EXT   MAINWIN   GlobalWndMem1[600]; //全局窗口的内存区
//SYSMENU_EXT   MAINWIN   GlobalWndMem2[400];

SYSMENU_EXT   MAINWIN   * GlobalWndMem; //全局窗口的内存区

/* 波形窗口句柄 
SYSMENU_EXT  HWND  Ecg1WaveHwnd;
SYSMENU_EXT  HWND  Ecg2WaveHwnd;
SYSMENU_EXT  HWND  Ecg3WaveHwnd;
SYSMENU_EXT  HWND  Ecg4WaveHwnd;
SYSMENU_EXT  HWND  Ecg5WaveHwnd;
SYSMENU_EXT  HWND  Ecg6WaveHwnd;
SYSMENU_EXT  HWND  Ecg7WaveHwnd;
SYSMENU_EXT  HWND  Spo2WaveHwnd;
SYSMENU_EXT  HWND  RespWaveHwnd;
SYSMENU_EXT  HWND  Ibp1WaveHwnd;
SYSMENU_EXT  HWND  Ibp2WaveHwnd;
*/
SYSMENU_EXT  HWND  BottombarHWnd;
SYSMENU_EXT  HWND  TopbarHWnd;
SYSMENU_EXT  HWND  MainGroupsHWnd;

SYSMENU_EXT  STRINGID gOnOff[];
SYSMENU_EXT  STRINGID gAlmLev[];
SYSMENU_EXT  STRINGID gWeekName[];

//#define  GetMainWndMem(id)	 (PMAINWIN)(PTR_ADD(GlobalWndMem,  id * sizeof(WINDOW)))
//#define  GetCtrlWndMem(id)	 (PCONTROL)(PTR_ADD(GlobalWndMem, id * sizeof(WINDOW)))

PMAINWIN GetMainWndMem(INT16 id);
PCONTROL GetCtrlWndMem(INT16 id);

BOOL   CreateSysMenus(VOID);
BOOL   CreateTopBar(VOID);
BOOL   CreateBottomBar(VOID);
VOID   SystemDialog(HANDLE hOwner);


#endif
