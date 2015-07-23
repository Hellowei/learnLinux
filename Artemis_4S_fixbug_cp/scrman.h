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

#ifndef _SCRMAN_H
#define _SCRMAN_H

#define SCREEN_LEFT		  0
#define	SCREEN_TOP		  0
#define SCREEN_WIDTH	800
#define	SCREEN_HIGH		480
#define DIMENSIONS_W	2220
#define DIMENSIONS_H	1322

#define  PARA_START_POS_Y		  29						// 状态条的高度
#define  TOPBAR_HEIGHT			  PARA_START_POS_Y   //标题栏的高度
#define  BOTBAR_HEIGHT			  49				 //状态栏的高度
#define  MIDDLE_HEIGHT			  (SCREEN_HIGH - TOPBAR_HEIGHT - BOTBAR_HEIGHT - 2)

//参数显示的基本信息定义
typedef struct {
	INT16  parameterRegionHeight;
	INT16  avgDispMaxRow;

} PARASCNBASEINFO;

#define WAVE_START			  5
#define WAVE_CX_CM			  18
#define WAVE_DIMENSIONS_W	   (WAVE_CX_CM * 100L) // 1800dmm = 180mm = 18cm
#define WAVE_WIDTH			  (SCREEN_WIDTH * WAVE_DIMENSIONS_W / DIMENSIONS_W) // 要求是180mm,屏幕宽度单位为mm x10
#define WAVE_HIGH			   MIDDLE_HEIGHT
#define PARAM_LEFT			  (WAVE_START * 2 + WAVE_WIDTH)
#define PARAM_WIDTH			 (SCREEN_WIDTH - PARAM_LEFT - 1)
#define PARAM_HIGH			  WAVE_HIGH //与波形一致
#define DIGIT_WIDTH			 (SCREEN_WIDTH - WAVE_START * 2)
#define DIGIT_HIGH			  MIDDLE_HEIGHT
#define TOPBAR_TOP			  4
#define BOTTOM_TOP			  (SCREEN_HIGH - BOTBAR_HEIGHT - 1)

#define ARTEMIS2_TOP_OFFSET		3
#define ARTEMIS2_BOTTOM_OFFSET	7

#define KEY_HEIGHT			  30
#define CTRL_HEIGHT			 45
#define DLG_MENU_HIGHT		  40
#define DLG_OFFSET			  15 // 窗口边缘
#define DLG_ADD_W             70 // 窗口加宽,panhonghui

#define STATIC_OFFSET		   ((CTRL_HEIGHT - STATIC_HEIGHT) / 2)
#define EXIT_ICON_WIDTH		 30
#define EXIT_ICON_HIGH		  30
#define BIGFONT_PARA_WIDTH	  400
#define PARAM_START			 PARAM_LEFT

#define MAX_WAVE_BLOCK_NUM	  4  // 最多的波形块
#define MAX_PARA_BLOCK_NUM	  4  // 最多的参数块

#define PARAM_HEIGHT			80
#define PARAM_HEIGHT_MAX		160


// 显示波形描述信息
typedef struct _wave_blockinfo {
	INT8		name;		   // 波形名称
	UINT8	   color;		  // 波形线条颜色

	// 波形显示区域信息
	INT16	   x;
	INT16	   y;
	INT16	   width;
	INT16	   height;
} WAVEBLOCKINFO, *PWAVEBLOCKINFO;

// 参数块描述信息
typedef struct _param_blockinfo {
	INT32	   name;		   // 参数块的名称
	GAL_PIXEL   color;		  // 显示颜色
	GAL_PIXEL   colorEx;		// 附加的显示颜色
	
	// 波形显示区域信息
	INT16   x;
	INT16   y;
	INT16   width;
	INT16   height;
} PARAMBLOCKINFO, *PPARAMBLOCKINFO;

// 屏幕布局描述信息
typedef struct _layout_blockinfo  {
	INT8   faceType;		   // 界面类型, 与MonitorConfig.faceType保持一致 

	INT8   numOfWaveBlock;	 // 显示波形的个数
	INT8   numOfParamBlock;	// 显示参数的个数
	INT8   numOfParamRow;	  // 显示参数的行数
	

	// 按照从上到下，从左至右的顺序在屏幕上排列的波形块的信息
	WAVEBLOCKINFO   waveBlocksInfo[MAX_WAVE_BLOCK_NUM];

	// 按照从上到下，从左至右的顺序在屏幕上排列的参数块的信息
	PARAMBLOCKINFO  paramBlocksInfo[MAX_PARA_BLOCK_NUM];

	// 指定的波形在waveBlocksInfo数组中的位置
	INT8			indexOfwaveBlock[MAX_WAVE_BLOCK_NUM];

	// 指定的参数块在paramBlocksInfo数组中的位置
	INT8			indexOfParamBlock[MAX_PARA_BLOCK_NUM];
} LAYOUTLOCKINFO;


#ifdef SCRMAN_GLOBALS
#define SCRMAN_EXT 
#else 
#define SCRMAN_EXT extern 
#endif

// 本模块对外的接口变量
SCRMAN_EXT   LAYOUTLOCKINFO   LayoutBlockInfo;
SCRMAN_EXT   PARASCNBASEINFO  ParaScnBaseInfo;
SCRMAN_EXT   HWND			 MainScnHWnd;
SCRMAN_EXT   INT16			LastHideWaveBlockNdx;

SCRMAN_EXT   INT8			 LayoutInProcess;  //是否在进行界面布局; TRUE, 在布局; FALSE, 没有;

BOOL   InitScrBaseInfo(VOID);

INT32  LayoutScreen(VOID);
HWND   GetHWndFromWaveName(INT wave_name);

VOID   GUIAPI  StartLayoutSession(VOID);

INT16  GetDialogPos (PDLGTEMPLATE pTemplate, INT32 *x, INT32 *y);

VOID   EnterDialogLayout (INT16 top_ndx, INT16 wave_ndx);
VOID   ExitDialogLayout (INT16 top_ndx, INT16 wave_ndx);

VOID   InitWaveTypeInfo (VOID);


#endif
