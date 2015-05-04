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
