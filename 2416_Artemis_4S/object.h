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
#if !defined(_OBJECT_H)
#define	  _OBJECT_H

#define	OBJ_TASK
#define	OBJ_WIN
#define	OBJ_FUNC

#define	OBJ_NAMESIZE	13  /* 12 char +  NULL */

/**
  系统对象的头结构 
  系统对象: 任务对象task obj，窗口对象win obj，功能模块 func obj；
**/
typedef struct _object_head {
	CHAIN_NODE	  node;
	INT16		   type;			/* the obj type. */
	INT16		   subType;		/* the sub type. */
} OBJHEAD;
typedef struct _object_head * OBJHEADP;

typedef  INT32 (*MSGPROC)(HANDLE, INT32, UINT32, UINT32);

typedef struct _job_object {

	/* 下面三个项和OBJECTHEAD相同；不要改变它；*/
	CHAIN_NODE	  node;
	INT16		   type;			/* the obj type. */
	INT16		   subType;		/* the sub type. */
	
	/*  以下是用于面向应用的定义   */
	CHAR		   *name;
	MSGPROC		 proc;
	HANDLE		  task;
	UINT32		  extData;		/* 扩展数据接口  */
} JOB, *PJOB;
typedef struct _job_object *JOBP;


#endif
