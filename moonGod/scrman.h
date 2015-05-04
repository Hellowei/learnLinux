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

#ifndef _SCRMAN_H
#define _SCRMAN_H

#define SCREEN_LEFT		  0
#define	SCREEN_TOP		  0
#define SCREEN_WIDTH	800
#define	SCREEN_HIGH		480
#define DIMENSIONS_W	2220
#define DIMENSIONS_H	1322

#define  PARA_START_POS_Y		  29						// ״̬���ĸ߶�
#define  TOPBAR_HEIGHT			  PARA_START_POS_Y   //�������ĸ߶�
#define  BOTBAR_HEIGHT			  49				 //״̬���ĸ߶�
#define  MIDDLE_HEIGHT			  (SCREEN_HIGH - TOPBAR_HEIGHT - BOTBAR_HEIGHT - 2)

//������ʾ�Ļ�����Ϣ����
typedef struct {
	INT16  parameterRegionHeight;
	INT16  avgDispMaxRow;

} PARASCNBASEINFO;

#define WAVE_START			  5
#define WAVE_CX_CM			  18
#define WAVE_DIMENSIONS_W	   (WAVE_CX_CM * 100L) // 1800dmm = 180mm = 18cm
#define WAVE_WIDTH			  (SCREEN_WIDTH * WAVE_DIMENSIONS_W / DIMENSIONS_W) // Ҫ����180mm,��Ļ��ȵ�λΪmm x10
#define WAVE_HIGH			   MIDDLE_HEIGHT
#define PARAM_LEFT			  (WAVE_START * 2 + WAVE_WIDTH)
#define PARAM_WIDTH			 (SCREEN_WIDTH - PARAM_LEFT - 1)
#define PARAM_HIGH			  WAVE_HIGH //�벨��һ��
#define DIGIT_WIDTH			 (SCREEN_WIDTH - WAVE_START * 2)
#define DIGIT_HIGH			  MIDDLE_HEIGHT
#define TOPBAR_TOP			  4
#define BOTTOM_TOP			  (SCREEN_HIGH - BOTBAR_HEIGHT - 1)

#define ARTEMIS2_TOP_OFFSET		3
#define ARTEMIS2_BOTTOM_OFFSET	7

#define KEY_HEIGHT			  30
#define CTRL_HEIGHT			 45
#define DLG_MENU_HIGHT		  40
#define DLG_OFFSET			  15 // ���ڱ�Ե
#define DLG_ADD_W             70 // ���ڼӿ�,panhonghui

#define STATIC_OFFSET		   ((CTRL_HEIGHT - STATIC_HEIGHT) / 2)
#define EXIT_ICON_WIDTH		 30
#define EXIT_ICON_HIGH		  30
#define BIGFONT_PARA_WIDTH	  400
#define PARAM_START			 PARAM_LEFT

#define MAX_WAVE_BLOCK_NUM	  4  // ���Ĳ��ο�
#define MAX_PARA_BLOCK_NUM	  4  // ���Ĳ�����

#define PARAM_HEIGHT			80
#define PARAM_HEIGHT_MAX		160


// ��ʾ����������Ϣ
typedef struct _wave_blockinfo {
	INT8		name;		   // ��������
	UINT8	   color;		  // ����������ɫ

	// ������ʾ������Ϣ
	INT16	   x;
	INT16	   y;
	INT16	   width;
	INT16	   height;
} WAVEBLOCKINFO, *PWAVEBLOCKINFO;

// ������������Ϣ
typedef struct _param_blockinfo {
	INT32	   name;		   // �����������
	GAL_PIXEL   color;		  // ��ʾ��ɫ
	GAL_PIXEL   colorEx;		// ���ӵ���ʾ��ɫ
	
	// ������ʾ������Ϣ
	INT16   x;
	INT16   y;
	INT16   width;
	INT16   height;
} PARAMBLOCKINFO, *PPARAMBLOCKINFO;

// ��Ļ����������Ϣ
typedef struct _layout_blockinfo  {
	INT8   faceType;		   // ��������, ��MonitorConfig.faceType����һ�� 

	INT8   numOfWaveBlock;	 // ��ʾ���εĸ���
	INT8   numOfParamBlock;	// ��ʾ�����ĸ���
	INT8   numOfParamRow;	  // ��ʾ����������
	

	// ���մ��ϵ��£��������ҵ�˳������Ļ�����еĲ��ο����Ϣ
	WAVEBLOCKINFO   waveBlocksInfo[MAX_WAVE_BLOCK_NUM];

	// ���մ��ϵ��£��������ҵ�˳������Ļ�����еĲ��������Ϣ
	PARAMBLOCKINFO  paramBlocksInfo[MAX_PARA_BLOCK_NUM];

	// ָ���Ĳ�����waveBlocksInfo�����е�λ��
	INT8			indexOfwaveBlock[MAX_WAVE_BLOCK_NUM];

	// ָ���Ĳ�������paramBlocksInfo�����е�λ��
	INT8			indexOfParamBlock[MAX_PARA_BLOCK_NUM];
} LAYOUTLOCKINFO;


#ifdef SCRMAN_GLOBALS
#define SCRMAN_EXT 
#else 
#define SCRMAN_EXT extern 
#endif

// ��ģ�����Ľӿڱ���
SCRMAN_EXT   LAYOUTLOCKINFO   LayoutBlockInfo;
SCRMAN_EXT   PARASCNBASEINFO  ParaScnBaseInfo;
SCRMAN_EXT   HWND			 MainScnHWnd;
SCRMAN_EXT   INT16			LastHideWaveBlockNdx;

SCRMAN_EXT   INT8			 LayoutInProcess;  //�Ƿ��ڽ��н��沼��; TRUE, �ڲ���; FALSE, û��;

BOOL   InitScrBaseInfo(VOID);

INT32  LayoutScreen(VOID);
HWND   GetHWndFromWaveName(INT wave_name);

VOID   GUIAPI  StartLayoutSession(VOID);

INT16  GetDialogPos (PDLGTEMPLATE pTemplate, INT32 *x, INT32 *y);

VOID   EnterDialogLayout (INT16 top_ndx, INT16 wave_ndx);
VOID   ExitDialogLayout (INT16 top_ndx, INT16 wave_ndx);

VOID   InitWaveTypeInfo (VOID);


#endif
