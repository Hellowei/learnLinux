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

#ifndef _ALMLIST_H
   #define _ALMLIST_H

#define ALARM_INFO_LIST_MAX 100
#define ALARM_INFO_ITEM_NUM 10
#define ALARM_INFO_PAGE_MAX (ALARM_INFO_LIST_MAX / ALARM_INFO_ITEM_NUM)
typedef struct alarm_info_LIST{
	INT16 index;
	INT16 count;
	INT16 page;
	struct{
		STRINGID	id;
		DATETIME	time;
	}info[ALARM_INFO_LIST_MAX];
}ALM_INFO_LIST;

typedef ALM_INFO_LIST *PALMLIST;

#ifdef  ALMLIST_GLOBALS
#define ALMLIST_EXTERN  
#else
#define ALMLIST_EXTERN  extern
#endif

ALMLIST_EXTERN  ALM_INFO_LIST TechAlmInfoList;
ALMLIST_EXTERN  ALM_INFO_LIST PhysAlmInfoList;
#endif
