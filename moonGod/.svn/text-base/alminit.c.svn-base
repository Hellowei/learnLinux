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
#include "includes.h"


const CHAR   AlmStrActDefault[] = "SYSTEM ERROR: ALARM";
const CHAR  *AlmStrActDefaultP  = AlmStrActDefault;
const CHAR **AlmStrDefault	  = &AlmStrActDefaultP;

const INT8 CriticalAlarmLevel = 0;
const INT8 MediumAlarmLevel   = 1;
const INT8 SlightAlarmLevel   = 2;  
const INT8 NoSuchAlarmLevel   = INVALIDALARMLEVEL;
const INT8 AlarmSwitchOn	  = TRUE;
const INT8 AlarmSwitchOff	 = FALSE;


/*
Name:	  InitAlarmSystem
Description: 
		   initialize the fundamental elements for alarm system, 
		   all global things.
Parameters:None
Return:	None
Test and revision:
*/
BOOL  InitAlarmSystem(VOID)
{
	INT32 i;
	AlmPrsntInfo.PhsAlm.AlmIndex = 0;
	AlmPrsntInfo.PhsAlm.AlmStr = (CHAR *)NULL;
	AlmPrsntInfo.PhsAlm.AlmTimePrsnt = FALSE;
	AlmPrsntInfo.PhsAlm.BkGndColor = INVALIDALARMLEVEL;
	AlmPrsntInfo.PhsAlm.AlmLev = INVALIDALARMLEVEL;
	AlmPrsntInfo.PhsAlm.Redraw = FALSE;
	AlmPrsntInfo.PhsAlm.Time.year = 0;
	AlmPrsntInfo.PhsAlm.Time.month = 0;
	AlmPrsntInfo.PhsAlm.Time.day = 0;
	AlmPrsntInfo.PhsAlm.Time.hour = 0;
	AlmPrsntInfo.PhsAlm.Time.minute = 0;
	AlmPrsntInfo.PhsAlm.Time.second = 60;

	AlmPrsntInfo.TechAlm.AlmIndex = 0;
	AlmPrsntInfo.TechAlm.AlmStr = (CHAR *)NULL;
	AlmPrsntInfo.TechAlm.AlmTimePrsnt = FALSE;
	AlmPrsntInfo.TechAlm.BkGndColor = INVALIDALARMLEVEL;
	AlmPrsntInfo.TechAlm.AlmLev = INVALIDALARMLEVEL;
	AlmPrsntInfo.TechAlm.Redraw = FALSE;
	AlmPrsntInfo.TechAlm.Time.year = 0;
	AlmPrsntInfo.TechAlm.Time.month = 0;
	AlmPrsntInfo.TechAlm.Time.day = 0;
	AlmPrsntInfo.TechAlm.Time.hour = 0;
	AlmPrsntInfo.TechAlm.Time.minute = 0;
	AlmPrsntInfo.TechAlm.Time.second = 60;


	AlmPrsntInfo.AudioLevel = -1;		 
	AlmPrsntInfo.AlmLevel   = -1;

	AlmPrsntInfo.HighestNewPhsAlm	  = 0;
	AlmPrsntInfo.HighestNewPhsAlmLevel = INVALIDALARMLEVEL;
	AlmPrsntInfo.Time.second		   = 60;   // invalid.

	AlmPrsntInfo.Blink.FHR1Blink = 0x80;
	AlmPrsntInfo.Blink.FHR2Blink = 0x80;
	AlmPrsntInfo.Blink.TOCOBlink = 0x80;
	AlmPrsntInfo.Blink.FMBlink   = 0x80;

	// blink feature.
	BlinkFeature.FHR1Blink = 0x00;
	BlinkFeature.FHR2Blink = 0x00;
	BlinkFeature.TOCOBlink = 0x00;
	BlinkFeature.FMBlink   = 0x00;


	// elements of the global controller.
	AlmGlbCtlr.LatchP			   = &(MonitorConfig.alarmLatched);  
	AlmGlbCtlr.PrvLatchState		= FALSE;	   
	AlmGlbCtlr.AlmSilent			= FALSE;			  
	AlmGlbCtlr.AlmSilenceRemain	 = 0; 
	AlmGlbCtlr.AlmPauseRemain	   = 0; 
	AlmGlbCtlr.AlmPause			 = FALSE;
	AlmGlbCtlr.TechNew			  = FALSE; 
	AlmGlbCtlr.PhsNew			   = FALSE; 
	AlmGlbCtlr.PhsAlmDisFocusIndex  = 0; 
	AlmGlbCtlr.TechAlmDisFocusIndex = 0;
	AlmGlbCtlr.AlmPauseLastTime	 = FALSE;
	AlmGlbCtlr.AlmSilentLastTime	= FALSE;
	AlmGlbCtlr.LanChange			= FALSE;
	AlmGlbCtlr.KeyboardLoad		 = FALSE;

	AlmGlbCtlr.HighestAlmLev		 = INVALIDALARMLEVEL;
	AlmGlbCtlr.HighestAlmLevLastTime = INVALIDALARMLEVEL;
	AlmGlbCtlr.AlmSoundLevel		 = &(MonitorConfig.alarmVolume); 
	AlmGlbCtlr.AlmSoundLevelLastTime = -100;   // set to an invalid.  
	for (i = 0; i <= STR_ALM_PHS_MAX - STR_ALM_PHS_FIRST + 1; i++)
	{
		//PhsAlmInfo[i].Effect
		//PhsAlmInfo[i].EffectLastTime
		PhsAlmInfo[i].Exist			 = TRUE;
		PhsAlmInfo[i].Trg			   = FALSE;
		PhsAlmInfo[i].Prsnt			 = TRUE;
		PhsAlmInfo[i].Clearable		 = FALSE;
		PhsAlmInfo[i].Cleared		   = FALSE;
		PhsAlmInfo[i].LeadOff		   = FALSE;
		PhsAlmInfo[i].SpecialLeadOff	= 0;
		PhsAlmInfo[i].AlmStr			= (char**)AlmStrDefault;
		PhsAlmInfo[i].AlmLevP		   = (char*)&MediumAlarmLevel;//&(FhrConfig.alarmLevel);
		PhsAlmInfo[i].Latch			 = FALSE;
		PhsAlmInfo[i].Critical		  = FALSE;
		PhsAlmInfo[i].Time.second	   = 60;
		PhsAlmInfo[i].Module			= MID_FHR;
		PhsAlmInfo[i].NewAlarm		  = FALSE;
		PhsAlmInfo[i].Hold			  = FALSE;
		PhsAlmInfo[i].AllClrable		= FALSE;
	}
	
	PhsAlmInfo[0].Effect				= (char*)&AlarmSwitchOff;	   
	PhsAlmInfo[0].EffectLastTime		= *(PhsAlmInfo[0].Effect);
	PhsAlmInfo[0].Exist				 = FALSE;			   
	PhsAlmInfo[0].AlmLevP = (char*)&NoSuchAlarmLevel; 
	PhsAlmInfo[0].Module = MID_NULL;		   

	for (i = 0; i <= STR_ALM_PHS_MAX - STR_ALM_PHS_FIRST + 1; i++)
	{
		PhsAlmInfo[i].AlmStr			= &(LoadString(i + STR_ALM_PHS_FIRST - 1));
		PhsAlmInfo[i].Effect			= &(FhrConfig.alarm);
		PhsAlmInfo[i].EffectLastTime	= *(PhsAlmInfo[i].Effect);
	}
	for (i = 0; i <= STR_ALM_TECH_MAX - STR_ALM_TECH_FIRST + 1; i++) {
		TechAlmInfo[i].Effect		   = (char*)&AlarmSwitchOn;
		TechAlmInfo[i].EffectLastTime   = AlarmSwitchOn;
		TechAlmInfo[i].Exist			= TRUE;
		TechAlmInfo[i].Trg			  = FALSE;
		TechAlmInfo[i].Prsnt			= TRUE;
		TechAlmInfo[i].Clearable		= FALSE;
		TechAlmInfo[i].Cleared		  = FALSE;
		TechAlmInfo[i].LeadOff		  = FALSE;
		TechAlmInfo[i].SpecialLeadOff   = 0;
		TechAlmInfo[i].AlmStr		   = (char**)AlmStrDefault;
		TechAlmInfo[i].AlmLevP		  = (char*)&MediumAlarmLevel;
		TechAlmInfo[i].Latch			= FALSE;
		//TechAlmInfo[i].Critical
		TechAlmInfo[i].Time.second	  = 60;
		TechAlmInfo[i].Module		   = MID_FHR;
		TechAlmInfo[i].NewAlarm		 = FALSE;
		TechAlmInfo[i].Hold			 = FALSE;
		TechAlmInfo[i].AllClrable	   = FALSE;
	}

	TechAlmInfo[0].Effect			   = (char*)&AlarmSwitchOff;
	TechAlmInfo[0].EffectLastTime	   = AlarmSwitchOff;
	TechAlmInfo[0].Exist				= FALSE;
	TechAlmInfo[0].AlmLevP			  = (char*)&NoSuchAlarmLevel;
	TechAlmInfo[0].Module			   = MID_NULL;

	for (i = 1; i <= STR_ALM_TECH_MAX - STR_ALM_TECH_FIRST; i++)
	{
		TechAlmInfo[i].AlmStr = &(LoadString(i + STR_ALM_TECH_FIRST - 1));
	}
	return TRUE;
}
