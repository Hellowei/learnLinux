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
#if !defined(_CHECKBOX_H)
#define	  _CHECKBOX_H

typedef struct _tag_checkboxdata {

	BOOL	  isSingle;	// ����Ƿ�Ϊ��ѡ��ť  TRUE����ѡ  FALSE����ѡ
	short	 flag;		// ����Ƿ�ѡ��  TRUE��ѡ��  FALSE��δѡ��  UNAVAIL:��Ч  
	DWORD	 status;
} CHECKBOXDATA, *CHECKBOXDATAP;

#define CHECKBOX_STATUS(pCtrl)   (((CHECKBOXDATAP)(pCtrl->dwAddData2))->status)


BOOL RegisterCheckboxControl(VOID);

#endif
