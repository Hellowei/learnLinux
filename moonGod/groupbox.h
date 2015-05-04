#ifndef _GROUPBOX_H
#define _GROUPBOX_H


#ifdef  GROUPBOX_GLOBALS
#define GROUPBOX_EXTERN
#else
#define GROUPBOX_EXTERN   extern
#endif


typedef struct tagGROUPBOXDATA 
{
	DWORD   status;
	INT16   help_ctrl_id;
	INT16   help_str_id;
}GROUPBOXDATA, *PGROUPBOXDATA;

#define GROUPBOX_STATUS(pCtrl)   (((PGROUPBOXDATA)(pCtrl->dwAddData2))->status)
#define GROUPBOX_HELPID(pCtrl)   (((PGROUPBOXDATA)(pCtrl->dwAddData2))->help_ctrl_id)
#define GROUPBOX_HELPSTR(pCtrl)  (((PGROUPBOXDATA)(pCtrl->dwAddData2))->help_str_id)
GROUPBOX_EXTERN BOOL RegisterGroupBoxControl(VOID);
GROUPBOX_EXTERN VOID PaintGroupBox(PCONTROL pctrl);
#endif

