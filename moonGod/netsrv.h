/*****************************************************************************************
* FILE		: netsrv.h
* Description	: 
*			  
* Copyright (c) 2014 by XXX. All Rights Reserved.
* 
* History:
* Version		Name       		Date			Description
   0.1			XXX			2014/05/26		Initial Version
   
*****************************************************************************************/


#ifndef _NETSRV_H_
#define _NETSRV_H_


#ifndef _NETSRV_GLOBALS
#define _NETSRV_EXT		extern
#else
#define _NETSRV_EXT
#endif

_NETSRV_EXT STATUS gNetStatus;

_NETSRV_EXT void TskNetRece(void *pdata);
_NETSRV_EXT INT32 NetTranTskProc(HANDLE hdl, INT32 msg, UINT32 wParam, UINT32 lParam);
_NETSRV_EXT void SetMachineNumber(void);
_NETSRV_EXT UINT32 GetMachineNumber(void);
_NETSRV_EXT void SetMachineName(char *name);
_NETSRV_EXT int GetNetReceivePacketCount(void);
_NETSRV_EXT void SetNetReceivePacketCount(char flag);

#endif /*_NETSRV_H_*/

