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

#ifndef _TIMER_h
#define _TIMER_h

#ifdef TIMER_GLOBALS
#define TIMER_EXT
#else
#define TIMER_EXT extern
#endif

#define MAX_TIMERS	  16


typedef struct _timer {
	HANDLE  hdl;
	UINT8   id;
	UINT8   status; // 7~2 reserved|cycle:TRUE;once:FALSE|run:TRUE;pause:FALSE
	INT32   elapsed;
	INT32   count;
}TIMER;
typedef TIMER* PTIMER;

TIMER_EXT BOOL	InitTimer (VOID);

TIMER_EXT VOID	TerminateTimer (HANDLE hdl, UINT8 id);
TIMER_EXT INT	 PauseTimer(HANDLE hdl, UINT8 id, UINT8 pause);

TIMER_EXT INT	 AddTimer (HANDLE hdl, UINT8 id, UINT8 status, long elapsed);
TIMER_EXT INT	 RemoveTimer (HANDLE hdl, UINT8 id);
TIMER_EXT VOID	SysTimerProc(VOID);

#endif
