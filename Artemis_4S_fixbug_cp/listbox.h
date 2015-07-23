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
#if !defined(_LISTBOX_H)
#define	  _LISTBOX_H

typedef  enum _listbox_code {
	LBC_CURRITEM,  //当前选择项的序号
	LBC_ITEMNUM,   //列表框共有多少项.
	LBC_ITEMLIST,  //列表框显示的STRINGID数组的起始地址.
	LBC_ITEM	   //指定序号的STRINGID值.
} LBCODE;

typedef struct tagLISTBOXDATA
{
	INT16	 itemNum;			  // 列表框中可选择项的个数
	INT16	 currItem;			 // 当前选择项的序号
	INT16	 dispNum;			  // 下拉框中显示的最大项数
	INT16	 topNdx;			   // 下拉框中最上面一项的序号
	INT16	 botNdx;			   // 下拉框中最下面一项的序号
	STRINGID *infoList;			 // 列表框中各项的ID
	DWORD	 status;
	INT16	 sroll_id;			 // 滚动条的ID,通常是list第一个控件ID
	INT16   help_ctrl_id;
	INT16   help_str_id;	
} LISTBOXDATA, * LISTBOXDATAP;

#define LISTBOX_STATUS(pCtrl)	   (((LISTBOXDATAP)(pCtrl->dwAddData2))->status)
#define LISTBOX_CURRITEM(pCtrl)	 (((LISTBOXDATAP)(pCtrl->dwAddData2))->currItem)
#define LISTBOX_ITEMNUM(pCtrl)	  (((LISTBOXDATAP)(pCtrl->dwAddData2))->itemNum)
#define LISTBOX_DISPNUM(pCtrl)	  (((LISTBOXDATAP)(pCtrl->dwAddData2))->dispNum)
#define LISTBOX_TOPNDX(pCtrl)	   (((LISTBOXDATAP)(pCtrl->dwAddData2))->topNdx)
#define LISTBOX_BOTNDX(pCtrl)	   (((LISTBOXDATAP)(pCtrl->dwAddData2))->botNdx)
#define LISTBOX_INFO(pCtrl)		 (((LISTBOXDATAP)(pCtrl->dwAddData2))->infoList)
#define LISTBOX_HELPID(pCtrl)	   (((LISTBOXDATAP)(pCtrl->dwAddData2))->help_ctrl_id)
#define LISTBOX_HELPSTR(pCtrl)	  (((LISTBOXDATAP)(pCtrl->dwAddData2))->help_str_id)

#   ifdef LISTBOX_GLOBALS
#	   define LISTBOX_EXT 
#   else 
#	   define LISTBOX_EXT extern 
#   endif

LISTBOX_EXT  VOID  *ListboxDropBuff;


BOOL RegisterListboxControl (VOID);

INT16  SetListBoxString(UINT16 parent_id, UINT16 ctrl_id, STRINGID* list_string_id,  INT16 string_count);
INT16  SetListBoxHelpString(UINT16 parent_id, UINT16 ctrl_id, STRINGID string_id);
INT16  SetListBoxCurChoi(UINT16 parent_id, UINT16 ctrl_id, INT16 cur_choice);
INT16  SetListBoxChoiNum(UINT16 parent_id, UINT16 ctrl_id, INT16 choi_num);
INT16  GetListBoxCurChoi(UINT16 parent_id, UINT16 ctrl_id);
INT16  GetListBoxChoiNum(UINT16 parent_id, UINT16 ctrl_id);


LISTBOX_EXT INT32 OnTouchListbox(HWND hWnd, RESID parent, RESID ctrl, STRINGID strid);

#endif
