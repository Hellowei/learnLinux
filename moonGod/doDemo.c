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
#define   DODEMO_GLOBALS 
#include  "includes.h"

static DEMO_SAVING  sDemoTempSaving;

VOID DemoTempSave(VOID)
{
	if (MonitorInfo.inDemo)
	{
		sDemoTempSaving.alarm = FhrConfig.alarm;
		sDemoTempSaving.alarmLevel = FhrConfig.alarmLevel;
		sDemoTempSaving.type = FhrConfig.mode;
		sDemoTempSaving.volume = FhrConfig.volume;
		sDemoTempSaving.source = FhrConfig.source;
		sDemoTempSaving.sweep = FhrConfig.sweep;
		sDemoTempSaving.zero = FhrConfig.zero;
		sDemoTempSaving.FhrAlarmLimitHi = FhrConfig.FhrAlarmLimitHi;
		sDemoTempSaving.FhrAlarmLimitLo = FhrConfig.FhrAlarmLimitLo;
		FhrConfig.alarm = TRUE;
		FhrConfig.alarmLevel = 1;
		FhrConfig.mode = 2;
		FhrConfig.volume = 0;
		FhrConfig.source = 0;
		FhrConfig.sweep = 2;
		FhrConfig.zero = 4;
		FhrConfig.FhrAlarmLimitHi = 160;
		FhrConfig.FhrAlarmLimitLo = 120;
	}
	else
	{
		FhrConfig.alarm = sDemoTempSaving.alarm;
		FhrConfig.alarmLevel = sDemoTempSaving.alarmLevel;
		FhrConfig.mode = sDemoTempSaving.type;
		FhrConfig.volume = sDemoTempSaving.volume;
		FhrConfig.source = sDemoTempSaving.source;
		FhrConfig.sweep = sDemoTempSaving.sweep;
		FhrConfig.zero = sDemoTempSaving.zero;
		FhrConfig.FhrAlarmLimitHi = sDemoTempSaving.FhrAlarmLimitHi;
		FhrConfig.FhrAlarmLimitLo = sDemoTempSaving.FhrAlarmLimitLo;
	}
}

VOID   EnterDemo(VOID)
{
	MonitorInfo.inDemo = TRUE;
	//Make sensor off is false
	if (FmsPtr->GetCurrSaveIndex(FmsPtr) >= 0)
	{
		EndPatientFile();
		strcpy(LoadString(STR_MAIN_TOPBAR_NAME_NAME), PatientInfo.patientName);
		strcpy(LoadString(STR_MAIN_TOPBAR_ID_NUM), PatientInfo.patientID);
		ShowPatinetInfo();
	}
	DemoTempSave();
	FetalSetMoudle(TRUE);;
	ClearAllAlarm(0);
	EraseWavesBuffer();
	SetFetalMonitorDemoStyle(TRUE);
	SetSensorStatus(0, -3);
	SetParamStatus(0, TRUE);

	StartLayoutSession();
}

VOID   ExitDemo(VOID)
{
	MonitorInfo.inDemo = FALSE;
	if (FmsPtr->GetCurrSaveIndex(FmsPtr) >= 0)
	{
		EndPatientFile();
		strcpy(LoadString(STR_MAIN_TOPBAR_NAME_NAME), PatientInfo.patientName);
		strcpy(LoadString(STR_MAIN_TOPBAR_ID_NUM), PatientInfo.patientID);
		ShowPatinetInfo();
	}
	DemoTempSave();
	FetalSetMoudle(TRUE);;
	ClearAllAlarm(0);
	// Make sensor off alarm being prompt only in three seconds after
	// leaving demo mode
	EraseWavesBuffer();
	SetFetalMonitorDemoStyle(FALSE);
	SetSensorStatus(0, -3);
	SetParamStatus(0, FALSE);
	StartLayoutSession();
	FhrInitParams();
}

