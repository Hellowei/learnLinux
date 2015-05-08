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
#define PARAMS_GLOBALS
#include "includes.h"

BOOL  InitParam(VOID)
{
	GlobalWndMem = malloc(1024 * sizeof(MAINWIN));
	memset(GlobalWndMem, 0, 1024 * sizeof(MAINWIN));

	FetalWaveBuffPtr		= (FETALWAVEDATA *) my_malloc (FETAL_DATA_BUFF_LEN);
	if (!FetalWaveBuffPtr)
		return FALSE;

	ZeroMemory(FetalWaveBuffPtr, FETAL_DATA_BUFF_LEN);
	FetalWaveBuffHeadPtr	= FetalWaveBuffPtr;
	FetalWaveBuffTailPtr	= FetalWaveBuffPtr + (MAX_FETAL_DATA_LEN - 1);
	FetalWaveBuffWritePtr   = FetalWaveBuffPtr;

	return TRUE;
}

/*
 Function Name: CollectParams
 Description:   copy all modules parameters to AllParams;
				在 data proc task 中采集.
				for it only read global, don't need protect.
				
 Parameters:	module_id -- collect which module's parameters,
				0: all modules, MID_ECG: ECG, MID_SPO2: spo2,
				MID_NIBP: nibp, MID_IBP: ibp,
				
 Return:		Nothing
 Output:		Nothing
 Test&Revision: Done
*/
VOID  CollectParams (INT module_id)
{
	AllParams.fhr1  = (FhrParams.fhr1 < 30) ? NOVALUE : FhrParams.fhr1;
	AllParams.fhr2  = (FhrParams.fhr2 < 30) ? NOVALUE : FhrParams.fhr2;
	AllParams.toco  = FhrParams.toco;
	AllParams.fm	= FhrParams.fm;
	AllParams.afm   = FhrParams.afm;
	AllParams.signal= FhrParams.signal;
}

