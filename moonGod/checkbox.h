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
#if !defined(_CHECKBOX_H)
#define	  _CHECKBOX_H

typedef struct _tag_checkboxdata {

	BOOL	  isSingle;	// 标记是否为单选按钮  TRUE：单选  FALSE：多选
	short	 flag;		// 标记是否被选中  TRUE：选中  FALSE：未选中  UNAVAIL:无效  
	DWORD	 status;
} CHECKBOXDATA, *CHECKBOXDATAP;

#define CHECKBOX_STATUS(pCtrl)   (((CHECKBOXDATAP)(pCtrl->dwAddData2))->status)


BOOL RegisterCheckboxControl(VOID);

#endif
