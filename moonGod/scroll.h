#ifndef _SCROLL_H_
#define _SCROLL_H_


#ifndef CTRL_SCROLL
#define CTRL_SCROLL	 "scroll"
#endif

typedef  int(*SCRPROC)(HWND, INT32, WPARAM, LPARAM);

// 个性化定制
typedef struct {
	GAL_PIXEL   blackColor;
	GAL_PIXEL   borderColor;
	GAL_PIXEL   normalForeColor;
	GAL_PIXEL   focusForeColor;
	GAL_PIXEL   pauseForeColor;
	SCRPROC	 proc;
	RESID	   help_id;
	STRINGID	help_str;
	DWORD	   addData;			// 附加数据
}SCROLLDATAEX, *PSCROLLDATAEX;

typedef struct {
	DWORD status;	   // 状态
	long  maxnum;	   // 范围元素的最大值
	long  minnum;	   // 范围元素的最小值
	long  value;		// 当前值
	long  step;		 // 步长
	WORD  border;	   // 控件的边框粗细
	WORD  minVisual;	// 最小可视对象的值
	DWORD addData;	  // 附加数据
}SCROLLDATA, *PSCROLLDATA;

#define SCROLL_STATUS(pCtrl)	(((PSCROLLDATA)(pCtrl->dwAddData2))->status)
#define SCROLL_MAXNUM(pCtrl)	(((PSCROLLDATA)(pCtrl->dwAddData2))->maxnum)
#define SCROLL_MINNUM(pCtrl)	(((PSCROLLDATA)(pCtrl->dwAddData2))->minnum)
#define SCROLL_VALUE(pCtrl)	 (((PSCROLLDATA)(pCtrl->dwAddData2))->value)
#define SCROLL_STEP(pCtrl)	  (((PSCROLLDATA)(pCtrl->dwAddData2))->step)
#define SCROLL_BORDER(pCtrl)	(((PSCROLLDATA)(pCtrl->dwAddData2))->border)
#define SCROLL_MINVS(pCtrl)	 (((PSCROLLDATA)(pCtrl->dwAddData2))->minVisual)
#define SCROLL_EX(pCtrl) \
				((PSCROLLDATAEX)(((PSCROLLDATA)(pCtrl->dwAddData2))->addData))

#define SCROLL_COUNT(pCtrl)	 (SCROLL_MAXNUM(pCtrl) - SCROLL_MINNUM(pCtrl))

#define SCROLL_EXBKC(pCtrl)	 ((SCROLL_EX(pCtrl))->blackColor)
#define SCROLL_EXBRC(pCtrl)	 ((SCROLL_EX(pCtrl))->borderColor)
#define SCROLL_EXNFC(pCtrl)	 ((SCROLL_EX(pCtrl))->normalForeColor)
#define SCROLL_EXFFC(pCtrl)	 ((SCROLL_EX(pCtrl))->focusForeColor)
#define SCROLL_EXPFC(pCtrl)	 ((SCROLL_EX(pCtrl))->pauseForeColor)
#define SCROLL_EXPRC(pCtrl)	 ((SCROLL_EX(pCtrl))->proc)
#define SCROLL_EXHID(pCtrl)	 ((SCROLL_EX(pCtrl))->help_id)
#define SCROLL_EXSTR(pCtrl)	 ((SCROLL_EX(pCtrl))->help_str)

#ifndef SCROLLBAR_GLOBALS
#define SCROLLBAR_EXTERN	extern
#else
#define SCROLLBAR_EXTERN
#endif

BOOL RegisterScrollBarControl (VOID);

SCROLLBAR_EXTERN	INT16  SetScrollBarValue(UINT16 parent_id, UINT16 ctrl_id, long  value);
SCROLLBAR_EXTERN	INT16  SetScrollBarMaxNum(UINT16 parent_id, UINT16 ctrl_id, long  max);
SCROLLBAR_EXTERN	INT16  SetScrollBarMinNum(UINT16 parent_id, UINT16 ctrl_id, long  min);
SCROLLBAR_EXTERN	INT16  SetScrollBarStep(UINT16 parent_id, UINT16 ctrl_id, DWORD step);
SCROLLBAR_EXTERN	INT16  SetScrollBarBorder(UINT16 parent_id, UINT16 ctrl_id, WORD border);
SCROLLBAR_EXTERN	INT16  SetScrollBarMinVisual(UINT16 parent_id, UINT16 ctrl_id, WORD minVisual);
SCROLLBAR_EXTERN	long   GetScrollBarValue(UINT16 parent_id, UINT16 ctrl_id);
SCROLLBAR_EXTERN	long   GetScrollBarMaxNum(UINT16 parent_id, UINT16 ctrl_id);
SCROLLBAR_EXTERN	long   GetScrollBarMinNum(UINT16 parent_id, UINT16 ctrl_id);
SCROLLBAR_EXTERN	DWORD  GetScrollBarStep(UINT16 parent_id, UINT16 ctrl_id);
SCROLLBAR_EXTERN	WORD   GetScrollBarBorder(UINT16 parent_id, UINT16 ctrl_id);
SCROLLBAR_EXTERN	WORD   GetScrollBarMinVisual(UINT16 parent_id, UINT16 ctrl_id);

#endif /*_SCROLL_H_*/

