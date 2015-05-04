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
#define   MODULMAN_GLOBALS 
#include  "includes.h"

static  INT32   Kb_RcvTimeoutNum = 0;
static  INT32   Fetal_RcvTimeoutNum = 0;

/**
 ** NOTE:
 **  what commErrAllowed is calculated.
 **   1. ECG, SPO2, IBP, : many data is sent to host, 1% of total
 **						bytes sent in one second is the error threshold.
 **	  ECG: ( 5*128 + 4*128 + 8 = 1160 ) * 1% = 10;
 **	  SPO2: ( 6 * 60 = 360) * 1% = 3;
 **	  IBP:  ( 3 + 4 * 128 = 515) * 1% = 5;
 **
 **   2. RECORDER: not mentioned here. 
 **   3. all module in one Board, so all configuaration is same with ECG.
 **  The moudles communcation alarm system configuration.
 **/
static COMMERRINFO Comm_ErrInfo[ MID_MAX ] =  {
	//hasCommStpAlm  hasCommErrAlm  timeForCommStp	  commErrAllowed
	{	 TRUE,	  TRUE,		  4000/OS_TICK_TIME,  1	  } // MID_KB
   ,{	 TRUE,	  TRUE,		  2000/OS_TICK_TIME,  1	  } // MID_FHR
   ,{	 FALSE,	FALSE,		  2000/OS_TICK_TIME,  1	  } // MID_RECODER
};

VOID  CheckKbRcvTimeout (INT32 read_num)
{
	if (read_num) {
		Kb_RcvTimeoutNum = 0;
	} else {
		if (Kb_RcvTimeoutNum < Comm_ErrInfo[MID_KB].timeForCommStp)
			Kb_RcvTimeoutNum ++;
	}
}

VOID  CheckFetalRcvTimeout (INT32 read_num)
{
	if (read_num) {
		Fetal_RcvTimeoutNum = 0;
	} else {
		if (Fetal_RcvTimeoutNum < Comm_ErrInfo[MID_FHR].timeForCommStp)
			Fetal_RcvTimeoutNum ++;
	}
}

/*
 Function Name: CommStopedTime
 Description:   the time that communication stoped for the given module
 Parameters:	module_id: which module
 Return:		time( in 20milliseconds).
 Test&Revision: Done
*/
INT32  CommStopedTime ( UINT8 mid )
{
	switch(mid)
	{
		case MID_KB:
			return Kb_RcvTimeoutNum;

		case MID_FHR:
			return Fetal_RcvTimeoutNum;

		default:
			return 0;
	}
}

/*
 Function Name: CommErrorNum
 Description:   return the number of communication errors, errors consist of:
				parity error, frame error and overrun error.
 Parameters:	module_id: which module
 Return:		the number of communication errors.
 Test&Revision: Done
*/
INT32  CommErrorNum ( INT32 module_id )
{
   module_id = module_id;
   return  0;  /* always == 0, for a while */
}

/*
 Function Name: IsCommStoped
 Description:   is communication to the given module stoped
 Parameters:	module_id: which module
 Return:		TRUE if communication stoped, FALSE if not or
				the given module is not plugged
 Test&Revision: Not yet
*/
BOOL  IsCommStoped (UINT8 mid)
{
   BOOL is_comm_stoped;

   is_comm_stoped = Comm_ErrInfo[mid].hasCommStpAlm
					&& (Comm_ErrInfo[mid].timeForCommStp <= CommStopedTime(mid));

   return is_comm_stoped;
}

/*
 Function Name: CommError
 Description:   is communication error found
 Parameters:	module_id: which module
 Return:		TRUE if communication error found, FALSE if not or
				the given module is not plugged
 Test&Revision: Done
*/
BOOL  CommError (UINT8 mid)
{
   BOOL comm_error;

   comm_error = Comm_ErrInfo[mid].hasCommErrAlm
				&& (Comm_ErrInfo[mid].commErrAllowed < CommErrorNum(mid));

   return comm_error;
}

BOOL  InitModuleMan (VOID)
{
	Kb_RcvTimeoutNum = 0;	
	return TRUE;
}
