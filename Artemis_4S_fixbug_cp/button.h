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
#if !defined(_BUTTON_H)
#define	  _BUTTON_H

//按钮状态包括:弹起(release),经过(pass),按下(down),单击(press)
typedef struct _button_bmp{
	unsigned char *release;
	unsigned char *pass;
	unsigned char *press;
	unsigned char *down;	
}BUTTONBMP, *PBUTTONBMP;

typedef struct tagBUTTONDATA {
	//BOOL	pressFlag;	  // 按钮是否需要按两次才能确认，TRUE：是
	INT32   data;			 // 数据; 用于bitmap, icon.
	DWORD   status;		   // button flags
	INT16   help_ctrl_id;
	INT16   help_str_id;
} BUTTONDATA, * BUTTONDATAP;

#define BUTTON_STATUS(pCtrl)  (((BUTTONDATAP)(pCtrl->dwAddData2))->status)
#define BUTTON_DATA(pCtrl)	(((BUTTONDATAP)(pCtrl->dwAddData2))->data)
#define BUTTON_HELPID(pCtrl)  (((BUTTONDATAP)(pCtrl->dwAddData2))->help_ctrl_id)
#define BUTTON_HELPSTR(pCtrl) (((BUTTONDATAP)(pCtrl->dwAddData2))->help_str_id)

BOOL RegisterButtonControl (void);

INT16  SetButtonStatus(UINT16 parent_id, UINT16 ctrl_id, UINT32 status);
INT16  GetButtonStatus(UINT16 parent_id, UINT16 ctrl_id, UINT32 * pstatus);

VOID   ShowHook (HDC hdc, INT32 x, INT32 y);
extern BUTTONDATA  gBtn_Exit;
#endif
