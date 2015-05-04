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
#define  ALARM_GLOBALS
#include "includes.h"


extern  INT8  NoSuchAlarmLevel; 


// prototypes of function in this file, see the corresponding descriptions.
VOID  OnSilence(VOID);  
VOID  OnPause(VOID);   
VOID  ProcessAlarmInfo(VOID); 
VOID  ProcessAlarmCntl(VOID);
VOID  ProcessTechAlarm(VOID);
VOID  ProcessPhsAlarm(VOID);
VOID  ProcessNibpTechAlarm(VOID);
VOID  ProcessAVAlarm(VOID);
VOID  ProcessPauseState(VOID);
INT8  FindTheHigestLevel(VOID);
VOID  OnLatchToNonLatch(VOID);
VOID  OnNonLatchToLatch(VOID);
VOID  SearchAnAlarm( INT16 );
VOID  ProcessBlink(VOID);

#if _ENB_NET_SEND_ALARM_INFO
VOID NetSendAlmInfo(VOID)
{
	char err1 = net_FETAL_NO_ALM;
	char err2 = net_FETAL_NO_ALM;
	char *txt;

	txt = AlmPrsntInfo.PhsAlm.AlmStr;

	if (txt == LoadString(STR_ALM_FHR1_TOO_HI))
		err1 = net_FHR1_TOO_HI;
	else if (txt == LoadString(STR_ALM_FHR1_TOO_LO))
		err1 = net_FHR1_TOO_LO;
	else if (txt == LoadString(STR_ALM_FHR2_TOO_HI))
		err1 = net_FHR2_TOO_HI;
	else if (txt == LoadString(STR_ALM_FHR2_TOO_LO))
		err1 = net_FHR2_TOO_LO;

	txt = AlmPrsntInfo.TechAlm.AlmStr;

	if (txt == LoadString(STR_ALM_FHR1_LOW_SIGNAL))
		err2 = net_FHR1_LOW_SIGNAL;
	else if (txt == LoadString(STR_ALM_FHR2_LOW_SIGNAL))
		err2 = net_FHR2_LOW_SIGNAL;
	else if (txt == LoadString(STR_ALM_FHR_ALM_LMT_ERR))
		err2 = net_FHR_ALM_LMT_ERR;
	else if (txt == LoadString(STR_ALM_FHR1_SENSOR_OFF))
		err2 = net_FHR1_SENSOR_OFF;
	else if (txt == LoadString(STR_ALM_FHR2_SENSOR_OFF))
		err2 = net_FHR2_SENSOR_OFF;
	else if (txt == LoadString(STR_ALM_TOCO_SENSOR_OFF))
		err2 = net_TOCO_SENSOR_OFF;
	else if (txt == LoadString(STR_ALM_FM_SENSOR_OFF))
		err2 = net_FM_SENSOR_OFF;
	else if (txt == LoadString(STR_ALM_KEYBOARD_COMM_ERR))
		err2 = net_KEYBOARD_COMM_ERR;
	else if (txt == LoadString(STR_ALM_POWER_BATTERY_LOW))
		err2 = net_POWER_BATTERY_LOW;
	else if (txt == LoadString(STR_ALM_PRINTER_HEAD_HOT))
		err2 = net_PRINTER_HEAD_HOT;
	else if (txt == LoadString(STR_ALM_PRINTER_DOOR_NOT_CLOSED))
		err2 = net_PRINTER_DOOR_NOT_CLOSED;
	else if (txt == LoadString(STR_ALM_PRINTER_PAPER_OUT))
		err2 = net_PRINTER_PAPER_OUT;
	else if (txt == LoadString(STR_ALM_PRINTER_DOOR_NOT_CLOSED))
		err2 = net_PRINTER_DOOR_NOT_CLOSED;

	SetNetErrorCode(err1, err2);
}
#endif

VOID CollectAlmInfo(INT16 type, INT16 index)
{
	PALMLIST pList;
	INT16	infoID;
	
	if (ALM_TYPE_PHY  == type)
	{
		if (   (FALSE == PhsAlmInfo[index].Trg)
			|| (FALSE == PhsAlmInfo[index].NewAlarm)
			|| (*PhsAlmInfo[index].AlmLevP > 2)
			|| (*PhsAlmInfo[index].AlmLevP < 0)	)
		{
			return;
		}
		pList = &PhysAlmInfoList;
		infoID = index + STR_ALM_PHS_FIRST - 1;
	} else
	if (ALM_TYPE_TECH == type)
	{
		if (   (FALSE == TechAlmInfo[index].Trg)
			|| (FALSE == TechAlmInfo[index].NewAlarm)
			|| (*TechAlmInfo[index].AlmLevP > 2)
			|| (*TechAlmInfo[index].AlmLevP < 0)	)
		{
			return;
		}
		pList = &TechAlmInfoList;
		infoID = index + STR_ALM_TECH_FIRST - 1;
	}
	else
	{
		return;
	}
	if (pList->count < ALARM_INFO_LIST_MAX)
	{
		pList->count++;
	}
	pList->info[pList->index].id = infoID;
	pList->info[pList->index].time = DateTime;
	if (++pList->index == ALARM_INFO_LIST_MAX)
	{
		pList->index = 0;
	}
}



/*
Name:	 TriggerAlarm.

Description: 
		  No matter what kind of alarm is generated, this 
		  routines is called to notify the alarm control system.
		  used as:
		  "
		  if ( HR > HR.HiLev )
		  {
			 TriggerAlarm(0x0001,STR_ALM_HRHI);
			 TriggerAlarm(0x0000,STR_ALM_HRLO);
		  }
		  else if ( HR < HR.LowLev )
		  {
			 TriggerAlarm(0x0000,STR_ALM_HRHI);
			 TriggerAlarm(0x0001,STR_ALM_HRLO);
		  }
		  else
		  {
			 TriggerAlarm(0x0000,STR_ALM_HRHI);
			 TriggerAlarm(0x0000,STR_ALM_HRLO);
		  }
		  "
Parameters:
		  trg - 0x0000, clear;
				0x0001, set;
				0x8001, set new;
				0x4000, clear leadoff audio.
		  index - index to refer to alarm information table.
		  
Return:   None.

Test and revision:
		  Inspection, 
*/
VOID TriggerAlarm (UINT16 trg, INT16 index)
{
	//PostMessage(AlarmJobHdl, MSG_USER_ALM_TRIGGER, MAKEWPARAM(index, trg), 0 );
	TriggerAlarm2(trg, index);
}

/* 内部使用的报警触发函数;不用传递消息 */
VOID TriggerAlarm2 (UINT16 trg, INT16 index)
{
	INT16 type;

	if (index >= STR_ALM_PHS_FIRST && index <= STR_ALM_PHS_MAX) 
	{
		type = ALM_TYPE_PHY;
		index = index - STR_ALM_PHS_FIRST + 1;
	}
	else if (index >= STR_ALM_TECH_FIRST && index <= STR_ALM_TECH_MAX) 
	{
		type = ALM_TYPE_TECH;
		index = index - STR_ALM_TECH_FIRST + 1;
	}
	else 
	{
		return;
	}
	if (0x0001 == (trg & 0xbfff)) 
	{
		switch (type) 
		{
			case ALM_TYPE_PHY:
			if (FALSE == PhsAlmInfo[index].Trg
				&& TRUE == PhsAlmInfo[index].Exist
				&& TRUE == *(PhsAlmInfo[index].Effect)) 
			{
				AlmGlbCtlr.PhsNew  = TRUE;			  
				memcpy((CHAR *)(&(PhsAlmInfo[index].Time)),(CHAR *)(&(DateTime)),sizeof(DATETIME));
				PhsAlmInfo[index].NewAlarm = TRUE;
			}
			PhsAlmInfo[index].Trg   = TRUE;
			PhsAlmInfo[index].Prsnt = FALSE;
			break;

			case ALM_TYPE_TECH:   
				if (FALSE == TechAlmInfo[index].Trg
					&& TRUE == TechAlmInfo[index].Exist 
					&& TRUE == *(TechAlmInfo[index].Effect)
					&& TechAlmInfo[index].AlmLevP != &NoSuchAlarmLevel) 
				{
					if (!( TRUE == TechAlmInfo[index].LeadOff && (trg & 0x4000)))
					{
						AlmGlbCtlr.TechNew = TRUE;
					}   
					TechAlmInfo[index].Cleared = FALSE;
					memcpy((CHAR *)(&(TechAlmInfo[index].Time)),(CHAR *)(&(DateTime)),sizeof(DATETIME));
					TechAlmInfo[index].NewAlarm = TRUE;
				}
				TechAlmInfo[index].Trg = TRUE;
				TechAlmInfo[index].Prsnt = FALSE;
				break;

			default:
				return;
		} 
	}
	else if (0x0000 == trg) 
	{
		switch (type) 
		{
			case ALM_TYPE_PHY: 
				if (TRUE == PhsAlmInfo[index].Trg)
				{
					PhsAlmInfo[index].Latch = TRUE;
				}
				PhsAlmInfo[index].Trg = FALSE;
				PhsAlmInfo[index].Prsnt = TRUE;
				PhsAlmInfo[index].Hold = FALSE;
				break;

			case ALM_TYPE_TECH:
				TechAlmInfo[index].Trg = FALSE;
				TechAlmInfo[index].Prsnt = TRUE;
				TechAlmInfo[index].Hold = FALSE;
				break;

			default:
				return;// should never come here.
		}
	}
	else if (0x8001 == (trg & 0xbfff))
	{ 
		// SET new alarm
		switch( type )
		{
			case ALM_TYPE_PHY:
				AlmGlbCtlr.PhsNew  = TRUE;			  
				memcpy((CHAR *)(&(PhsAlmInfo[index].Time)),(CHAR *)(&(DateTime)),sizeof(DATETIME));
				PhsAlmInfo[index].NewAlarm = TRUE;
				PhsAlmInfo[index].Trg   = TRUE;
				PhsAlmInfo[index].Prsnt = FALSE;
				break;

			case ALM_TYPE_TECH:	 
				if (TRUE == TechAlmInfo[index].Exist 
					&& TRUE == *(TechAlmInfo[index].Effect)
					&& TechAlmInfo[index].AlmLevP != &NoSuchAlarmLevel) 
				{
					AlmGlbCtlr.TechNew = TRUE;
					TechAlmInfo[index].Cleared = FALSE;
					memcpy((CHAR *)(&(TechAlmInfo[index].Time)),(CHAR *)(&(DateTime)),sizeof(DATETIME));
				}

				TechAlmInfo[index].Trg = TRUE;
				TechAlmInfo[index].Prsnt = FALSE;
				break;

			default:
				return;
		} 
	}
	if (trg & 0x4000) 
	{  
		// clear leadoff audio
		if (ALM_TYPE_TECH == type) 
		{
			if (TRUE == TechAlmInfo[index].LeadOff && TRUE == TechAlmInfo[index].Trg)
			{
				TechAlmInfo[index].Cleared = TRUE;
			}
		}
	}
	CollectAlmInfo(type,index);
}


/*
Name:	ChangeModuleInfoForAlmSystem
Description:	
		 When module configuration changed, this routine must 
		 be called to notify the alarm system.
		 ATTENTION, only permitted from tasks with priority lower 
		 than or equal to context of "ProcessAlarmInfo".
Parameters:
		 load - TRUE, something load, FLASE, something unload.
		 module_type - module ID.
Return:  None.
Test and revision:
		 Inspection,
*/
VOID ChangeModuleInfoForAlmSystem (BOOL load, INT16 module_type)
{
	ChangeModuleInfoForAlmSystem2(load, module_type);
}

VOID ChangeModuleInfoForAlmSystem2 (BOOL load, INT16 module_type)
{}


/*
Name:	 ClearAllAlarm
Description: 
		  When this interface routines is called, all the alarms come along
		  with the input module will be cleared.
Parameters:
		  module_id - module id.
Return:   None.
Test and revision:
*/
VOID ClearAllAlarm2 (INT16 module_id)
{
	int i;
	module_id = module_id;
	for (i = STR_ALM_FIRST; i < STR_ALM_END; i++)
	{
		TriggerAlarm2(FALSE, i);
	}
}

VOID  ClearAllAlarm (INT16 module_id)
{
	//PostMessage(AlarmJobHdl, MSG_USER_ALM_CLRMDLALM, (WPARAM)module_id, 0);
	ClearAllAlarm2(module_id);
}

/*
Name:	NotifyAlarmSystemofLanguageChange
Desciption:
		 when system language option is set ( actually , not changed )
		 this function is called to set a flag in alarm control system.
Parameters:
		 none.
Return:  none.
Test and revision:
*/
VOID NotifyAlarmSystemofLanguageChange (VOID)
{
   AlmGlbCtlr.LanChange = TRUE;
}

/*
Name:	   EnableAlarmForModule.
Description: 
			Enalbe alarm controlling for certain kind of module.
Parameters: None. (use global of "AlmTimerForModuleChange")
Return:	 None.
Test and revision:
			Inspection. 
*/
VOID EnableAlarmForModule (VOID)
{
	INT16 i,j;

	for ( i = 0 ; i < MID_MAX; i++ )
	{
		if (AlmTimerForModuleChange[i] < ALARMPREHIBITSECONDS)
		{
			AlmTimerForModuleChange[i]++;
			if (AlmTimerForModuleChange[i] == ALARMPREHIBITSECONDS)
			{
				for (j = 1; j <= STR_ALM_PHS_MAX - STR_ALM_PHS_FIRST + 1; j++)
				{
					if (i == PhsAlmInfo[j].Module)
					{
						PhsAlmInfo[j].Exist = TRUE;
						if (TRUE == PhsAlmInfo[j].Trg 
						 && TRUE == *(PhsAlmInfo[j].Effect))
						{
							AlmGlbCtlr.PhsNew  = TRUE;			   
							PhsAlmInfo[j].Time = DateTime;
							PhsAlmInfo[j].NewAlarm = TRUE;
						}
					}
				}
				RemoveSysInfoItem(Alm_PrompNdx4MdlLoad[i]);
			}
		}
	}
}


VOID ClearPauseSilence(VOID)
{}
/*
Name:	  OnSilence
Description: 
		   When the "silece" button is pressed down by the user,
		   this callback runs. 
		   ATTENTION, only permitted from tasks with lower or
		   equal priority than "ProcessAlarmInfo"!!!
Parameters:None
Return:	None
Test and revision:
		   Inspection,
*/
VOID OnSilence (VOID)
{
	//PostMessage(AlarmJobHdl, MSG_USER_ALM_ONSILENCE, 0, 0);
//	OnSilence2();
	if (MonitorConfig.alarmSoundOn)
	{
		MonitorConfig.alarmSoundOn = OFF;
		AlmGlbCtlr.AlmSilent = TRUE;
	}
	else
	{
		MonitorConfig.alarmSoundOn = ON;
		AlmGlbCtlr.AlmSilent = FALSE;
	}
	UpdateAlmVolIcon();
	Save_Config(CFG_KEYID_ALARMSILENCE);
}

VOID OnSilence2 (VOID)
{
	if (FALSE == AlmGlbCtlr.AlmSilent)
	{
		AlmGlbCtlr.AlmSilent = TRUE;
	}
	else
	{
		AlmGlbCtlr.AlmSilent = FALSE;
	}
}

/*
Name:	  SayPrsnt
Description:	If there are some critical alarms latched,
				the other latched should be cleared through
				saying "it is already presented". 
Parameters:	 none.
Return:		 none.
Test and revision:
*/
VOID SayPrsnt (VOID)
{}
	   


/*
Name:	  OnPause
Description: 
		   When the "pause" button is pressed down by the user,
		   this callback runs. 
		   ATTENTION, only permitted from tasks with lower or
		   equal priority than context of "ProcessAlarmInfo"!!!
		   "OnPause" and "OnSilence" should not interrupt each other.
		   if this can not guaranteed by context, preemption must 
		   be used.
Parameters:None
Return:	None
Test and Revision:
		   Inspection,
*/
VOID OnPause (VOID)
{
   OnPause2();
}

VOID OnPause2 (VOID)
{
	return;
}


/*   
Name:	   ProcessBlink
Description: 
			Process blink features, find out which should be blinked.
			If the blink feature don't change, just clear the 
			MSB of flag, if the blink feature changes, set
			MSB of correspond flag and load in the new feature.
Parameters: None.
Returns:	None.
Test and revision: 
*/
VOID ProcessBlink (VOID)
{
	INT16 i,index;
	INT8  cdtn_alarm;

	// first of all, scan the physiological array 
	// and set blink.
	for (i = 1; i <= STR_ALM_PHS_MAX - STR_ALM_PHS_FIRST; i++) 
	{
	
		cdtn_alarm = TRUE == *( PhsAlmInfo[i].Effect ) 
					 && TRUE == PhsAlmInfo[i].Exist
					 && TRUE == PhsAlmInfo[i].Trg
					 && FALSE == AlmGlbCtlr.AlmPause;
		
		index = i + STR_ALM_FIRST;

		if ( cdtn_alarm ) 
		{
		
			
		}
		else
		{

		}
	}

	if ( 0 != (BlinkFeature.FHR1Blink & 0x06) )
		BlinkFeature.FHR1Blink |= 0x01; 
	else 
		BlinkFeature.FHR1Blink = 0x00;   

	// then, see if anything changed.
	if ( ( AlmPrsntInfo.Blink.FHR1Blink & 0x07 ) == BlinkFeature.FHR1Blink )
	  AlmPrsntInfo.Blink.FHR1Blink &= 0x07;
	else 
	  AlmPrsntInfo.Blink.FHR1Blink = BlinkFeature.FHR1Blink | 0x80;

	if ( 0 != (BlinkFeature.FHR2Blink & 0x06) )
		BlinkFeature.FHR2Blink |= 0x01; 
	else 
		BlinkFeature.FHR2Blink = 0x00;   

	// then, see if anything changed.
	if ( ( AlmPrsntInfo.Blink.FHR2Blink & 0x07 ) == BlinkFeature.FHR2Blink )
	  AlmPrsntInfo.Blink.FHR2Blink &= 0x07;
	else 
	  AlmPrsntInfo.Blink.FHR2Blink = BlinkFeature.FHR2Blink | 0x80;

	if ( 0 != (BlinkFeature.TOCOBlink & 0x06) )
		BlinkFeature.TOCOBlink |= 0x01; 
	else 
		BlinkFeature.TOCOBlink = 0x00;   

	// then, see if anything changed.
	if ( ( AlmPrsntInfo.Blink.TOCOBlink & 0x07 ) == BlinkFeature.TOCOBlink )
	  AlmPrsntInfo.Blink.TOCOBlink &= 0x07;
	else 
	  AlmPrsntInfo.Blink.TOCOBlink = BlinkFeature.TOCOBlink | 0x80;

	if ( 0 != (BlinkFeature.FMBlink & 0x06) )
		BlinkFeature.FMBlink |= 0x01; 
	else 
		BlinkFeature.FMBlink = 0x00;   

	// then, see if anything changed.
	if ( ( AlmPrsntInfo.Blink.FMBlink & 0x07 ) == BlinkFeature.FMBlink )
	  AlmPrsntInfo.Blink.FMBlink &= 0x07;
	else 
	  AlmPrsntInfo.Blink.FMBlink = BlinkFeature.FMBlink | 0x80;
}



/*		TriggerNewPhsAlarm
Description:
		  if the alarm switch is changed from off to on,
		  this routine will make the now-triggering alarm 
		  to announce a new alarm.
Parameters:
		  None.
Return:   None.
Test and revision:
*/
VOID TriggerNewPhsAlarm (VOID)
{
	INT16 i;

	for (i = 1; i <= STR_ALM_PHS_MAX - STR_ALM_PHS_FIRST + 1; i++)
	{
		if (TRUE  ==  *(PhsAlmInfo[i].Effect)
		 && FALSE == PhsAlmInfo[i].EffectLastTime
		 && TRUE  == PhsAlmInfo[i].Exist
		 && TRUE  == PhsAlmInfo[i].Trg)
		{
			AlmGlbCtlr.PhsNew  = TRUE;				
			PhsAlmInfo[i].Time = DateTime;
			PhsAlmInfo[i].NewAlarm = TRUE;
		}
	}

	for (i = 1; i <= STR_ALM_PHS_MAX - STR_ALM_PHS_FIRST + 1; i++)
		PhsAlmInfo[i].EffectLastTime = *(PhsAlmInfo[i].Effect);
}
	
/*		PickCriticalPhsAlarm
Description:
		  Use the "NewAlarm" mark to pick the critical physiological
		  alarm with the highest priority and generate following elements
		  in "AlmPrsntInfo": HighestNewPhsAlm,HighestNewPhsAlmLevel,Time.
Parameters:
		  None.
Returns:
		  None.
Test and revision:
*/
VOID PickCriticalPhsAlarm (VOID)
{
   INT16 i;
   INT16 alm_lvl = INVALIDALARMLEVEL;
   INT16 return_value = 0;


   // First of all, set Hold.
	for (i = 1; i <= STR_ALM_PHS_MAX - STR_ALM_PHS_FIRST + 1; i++ ) 
	{
		if (TRUE == PhsAlmInfo[i].NewAlarm)
		{
			PhsAlmInfo[i].Hold = TRUE;
		}
		if (TRUE == PhsAlmInfo[i].Hold)
		{
			if (alm_lvl > *(PhsAlmInfo[i].AlmLevP))
			{
				alm_lvl = *(PhsAlmInfo[i].AlmLevP);
			}
		}
	}

 
	if (INVALIDALARMLEVEL == alm_lvl)
	{
		return_value = 1;
	}

	if (!return_value)// found an alarm
	{
		for (i = 1; i <= STR_ALM_PHS_MAX - STR_ALM_PHS_FIRST + 1; i++)
		{
			if ( TRUE == PhsAlmInfo[i].Hold )
			{
				if (alm_lvl == *(PhsAlmInfo[i].AlmLevP))
				{
					PhsAlmInfo[i].Hold = FALSE;
					break;
				}
			}
		}
	}

	if ( 1 == return_value )
	{
		AlmPrsntInfo.HighestNewPhsAlm = 0;
		AlmPrsntInfo.HighestNewPhsAlmLevel = INVALIDALARMLEVEL;
		AlmPrsntInfo.Time.second = 60;   // invalidate it.
	}
	else
	{
		AlmPrsntInfo.HighestNewPhsAlm = i + STR_ALM_FIRST - 1;
		AlmPrsntInfo.HighestNewPhsAlmLevel = alm_lvl;
		AlmPrsntInfo.Time = DateTime;
	}

	for (i = 1; i <= STR_ALM_PHS_MAX - STR_ALM_PHS_FIRST + 1; i++)
	{
		PhsAlmInfo[i].NewAlarm = FALSE;
	}
}


/*
Name:	DealWithLanguage
Description: 
		 when language changed, the alarm display should be 
		 redraw.
Parameters:
		 none.
Return:  none.
Test and revision:
*/
VOID DealWithLanguage (VOID)
{
	if ( TRUE == AlmGlbCtlr.LanChange )
	{
		if ( 0 != AlmPrsntInfo.PhsAlm.AlmIndex 
			 && INVALIDALARMLEVEL != AlmPrsntInfo.PhsAlm.AlmLev 
			 && FALSE == AlmPrsntInfo.PhsAlm.Redraw ) 
		{
			AlmPrsntInfo.PhsAlm.AlmStr 
			  = *(PhsAlmInfo[AlmPrsntInfo.PhsAlm.AlmIndex].AlmStr);
			AlmPrsntInfo.PhsAlm.Redraw = TRUE; 
		}

		if ( 0 != AlmPrsntInfo.TechAlm.AlmIndex 
			 && INVALIDALARMLEVEL != AlmPrsntInfo.TechAlm.AlmLev 
			 && FALSE == AlmPrsntInfo.TechAlm.Redraw ) 
		{
			AlmPrsntInfo.TechAlm.AlmStr 
			  = *(TechAlmInfo[AlmPrsntInfo.TechAlm.AlmIndex].AlmStr);
			AlmPrsntInfo.TechAlm.Redraw = TRUE; 
		}

		AlmGlbCtlr.LanChange = FALSE;
	}
	
}


/*
Name:	 ProcessAlarmInfo
Description:
		  This is the key function for alarm processing.
		  it will use alarm information array to make an global output for
		  displaying or message sending to alarm module.
		  Attention, this should be called from the task
		  with the highest priority in the system, typically,
		  from "DataProcessTask"!!!
Parameters:
		  None.
Returns: 
		  None.
Test and revison:
*/
VOID ProcessAlarmInfo (VOID)
{
	EnableAlarmForModule();   //在模块init函数中设置了模块加载后30秒不判断生理报警，若30s已到，则打开生理报警 -- empty 2011/04/29
	TriggerNewPhsAlarm();	  //如果模块是从关闭到打开的过程，则PhsAlmInfo[i].EffectLastTime将起到作用 -- empty 2011/04/29
	ProcessAlarmCntl();		  //主要处理报警暂停和静音持续时间的一些处理 -- empty 2011/04/29
	ProcessTechAlarm();		  //检测技术报警并构造技术报警显示的相关内容 -- empty 2011/04/29
	ProcessPhsAlarm();		//如果为报警暂停，显示剩余时间，不是则寻找一个生理报警 -- empty 2011/04/29
	ProcessNibpTechAlarm();	  //对NIBP报警的特殊处理 -- empty 2011/04/29
	ProcessAVAlarm();		  //对报警声音的处理  -- empty 2011/04/29
	ProcessBlink();			  //闪烁处理:bit0:测量参数是否闪烁;bit1:高限是否闪烁;bit2:低限是否闪烁;
							  //bit7:是否需要刷新 ;1 ---- 需要,0 ---- 不需要 --empty 2011/04/29
	PickCriticalPhsAlarm();   //对多个同时最高优先级报警按照字符串的顺序排列后处理 -- empty 2011/04/29
	DealWithLanguage();		  //处理语言变更后的报警字符串，其实没做改动，只是重新载入而已 -- empty 2011/04/29
}


/*
Name:	   ProcessAlarmCntl
Description: 
			Process elements in "AlmGlbCtlr", this function 
			is connected with function "ProcessAVAlarm" a little,
			anyway, let it be.
Parameters: None.
Return:	 None.
Test and revision:
*/
VOID ProcessAlarmCntl (VOID)
{
	if (0 == *(AlmGlbCtlr.AlmSoundLevel) && 0 != AlmGlbCtlr.AlmSoundLevelLastTime)
	{
		// say, if the alarm sound turns from nonzero 
		// to zero. pause and silence should be terminated.
		AlmGlbCtlr.AlmSilent = FALSE;
		AlmGlbCtlr.AlmPauseRemain = 0;
		AlmGlbCtlr.AlmPause = FALSE;
	}
	else
	{
		// should not be both silent and pause, this is 
		// guarranteed by "OnPause" and "OnSilence".
		if (TRUE == AlmGlbCtlr.AlmSilent)
		{
			if (TRUE == AlmGlbCtlr.TechNew || TRUE == AlmGlbCtlr.PhsNew)
			{
				// if there are new alarms coming in.
				AlmGlbCtlr.AlmSilent = FALSE;
			}
		}
		else
		{
			if (TRUE == AlmGlbCtlr.AlmPause)
			{
				AlmGlbCtlr.AlmPauseRemain -= 1;
				if (0 == AlmGlbCtlr.AlmPauseRemain)
				{
					AlmGlbCtlr.AlmPause = FALSE;
				}
				else
				{
					if (TRUE == AlmGlbCtlr.TechNew)
					{
						// say, there are some new tech alarms.
						AlmGlbCtlr.AlmPauseRemain = 0;
						AlmGlbCtlr.AlmPause = FALSE;
					}
					else
					{
						// just modify something for display and deal with latch.
						ProcessPauseState();
					}
				}
			}
		}
	}

	// clear pause and silence.
	AlmGlbCtlr.TechNew = FALSE;
	AlmGlbCtlr.PhsNew = FALSE;

	// something must be done to latch.
	if (TRUE == AlmGlbCtlr.PrvLatchState && FALSE == *(AlmGlbCtlr.LatchP))
		OnLatchToNonLatch();

	if (FALSE == AlmGlbCtlr.PrvLatchState && TRUE == *(AlmGlbCtlr.LatchP))
		OnNonLatchToLatch();

	AlmGlbCtlr.PrvLatchState = *(AlmGlbCtlr.LatchP);
}


/*
Name:		   OnLatchToNonLatch();
Description:	Called when alarm system changed from latch
				to non latch.
Parameters:	 None.
Return:		 None.
Test and revision:
*/
VOID OnLatchToNonLatch (VOID)
{
	  // nothing will be done.
}

/*
Name:		   OnNonLatchToLatch();
Description:	Called when alarm system changed from non latch
				to latch.
				if an alarm is triggered now, nothing will be done.
				if an alarm is cleared, just clear its latch state too.
Parameters:	 None.
Return:		 None.
Test and revision:
				eric. 2005.10
				inspected.
*/
VOID OnNonLatchToLatch (VOID)
{
	INT16 i;
	// only physiological things can be set to latch mode.
	for ( i = 1; i <= STR_ALM_PHS_MAX - STR_ALM_PHS_FIRST + 1; i++ )
	   PhsAlmInfo[i].Latch = FALSE;
}

	  
/*
Name:		   ProcessPauseState
Description:	1. fill the remain "**"s string for displaying.
				2. set clear signal to tech alarms which is audiblely clearable.
Parameters:	 None.
Return:		 None.
Test and revision:
*/
VOID ProcessPauseState (VOID)
{}


/*
Name:	  ProcessPhsAlarm.
Description: 
		   Survey the physiological alarm information array and build
		   the elements for display.
Parameters:
		   None.
Return:	None.
Test and revision:

*/
VOID ProcessPhsAlarm (VOID)
{
	SearchAnAlarm(ALM_TYPE_PHY);
}


/*
Name:	  ProcessNibpTechAlarm.
Description: 
		   Survey the NIBP technical alarm information array and build
		   the elements for display.
Parameters:
		   None.
Return:	None.
Test and revision:
		   Inspection,

*/
VOID ProcessNibpTechAlarm (VOID)
{
	SearchAnAlarm(ALM_TYPE_NIBP);
}


/*
Name:	  PickLeadOffOut
Description:
		   If the leadoff alarm don't belong to ECG/SPO2, and now 
		   it is set and cleared, just set Trg = FALSE temperarily and 
		   make a sign in "SpecialLeadOff".
Parameters:
		   none.
Return:	none.
Test and revision:
*/
VOID PickLeadOffOut (VOID)
{
	INT16 i;

	for ( i = 1; i <= STR_ALM_TECH_MAX - STR_ALM_TECH_FIRST + 1; i++ )
	{
		if ( TRUE == *( TechAlmInfo[i].Effect ) 
			 && TRUE == TechAlmInfo[i].Exist 
			 && TRUE == TechAlmInfo[i].LeadOff 
			 && TRUE == TechAlmInfo[i].Cleared
			 && TRUE == TechAlmInfo[i].Clearable
			 && TRUE == TechAlmInfo[i].SpecialLeadOff
			 && TRUE == TechAlmInfo[i].Trg ) {
			TechAlmInfo[i].SpecialLeadOff |= 0x8000;
			TechAlmInfo[i].Trg = FALSE;
			TechAlmInfo[i].Prsnt = TRUE; // just say it is displayed.
		}
	}
}

/*
Name:		SetLeadOffIn
Descirption: When the proper technical alarm is picked out to display,
			 set those leadoff alarm which is cleared and masked in.
Parameters:  none.
Returns:	 none.
Test and revision:
*/
VOID SetLeadOffIn (VOID)
{
	INT16 i;

	for ( i = 1; i <= STR_ALM_TECH_MAX - STR_ALM_TECH_FIRST + 1; i++ )
	{
		if ( TRUE == *( TechAlmInfo[i].Effect )
		  && TRUE == TechAlmInfo[i].Exist 
		  && TRUE == TechAlmInfo[i].LeadOff 
		  && TRUE == TechAlmInfo[i].Cleared 
		  && TRUE == TechAlmInfo[i].Clearable 
		&& 0x8001 ==  TechAlmInfo[i].SpecialLeadOff )
		{
			TechAlmInfo[i].SpecialLeadOff = TRUE;
			TechAlmInfo[i].Trg = TRUE;
		}
	}
}
			

/*
Name:	  ProcessTechAlarm.
Description: 
		   Survey the technical alarm information array and build
		   the elements for display.
Parameters:
		   None.
Return:	None.
Test and revision:
		   Inspection,

*/
VOID ProcessTechAlarm (VOID)
{
	 PickLeadOffOut();  //对导联脱落报警做相关的处理  -- empty 2011/04/29
	 SearchAnAlarm(ALM_TYPE_TECH);
	 SetLeadOffIn();
}

/*
Name:	  SearchAnAlarm.
Description: 
		   Find an alarm by surveying the alarm array and 
		   fill in the elements for display
Parameters:
		   alarm_type, 1 - physiological; 2 - technical; 3 - NIBP technical
Return:	None.
Test and revision:
*/
VOID SearchAnAlarm ( INT16 alarm_type )
{
   INT16			i, j;
   INT16		   *index,index_start,index_end;
   ALM_ITEM		*alarm_array_p;
   ALM_PRESENT	 *alarm_prsnt_p;
   INT8			 cdtn_alarm, cdtn_latch, cdtn_remain;
   INT8			 critical = FALSE, first_round = TRUE;


   j = 0;
   switch( alarm_type ) 
	{
		case ALM_TYPE_PHY:  // physiological
			index = &(AlmGlbCtlr.PhsAlmDisFocusIndex);
			alarm_array_p = PhsAlmInfo;
			alarm_prsnt_p = &(AlmPrsntInfo.PhsAlm);
			index_start = 1;
			index_end = STR_ALM_PHS_MAX - STR_ALM_PHS_FIRST + 1;
			break;

		case ALM_TYPE_TECH:  // technical
			index = &(AlmGlbCtlr.TechAlmDisFocusIndex);
			alarm_array_p = TechAlmInfo;
			alarm_prsnt_p = &(AlmPrsntInfo.TechAlm);
			index_start = 1;
			index_end = STR_ALM_TECH_MAX - STR_ALM_TECH_FIRST;
			break;
/** /
		case ALM_TYPE_NIBP:  // NIBP technical
			index = &(AlmGlbCtlr.NibpTechAlmDisFocusIndex);
			alarm_array_p = NibpTechAlmInfo;
			alarm_prsnt_p = &(AlmPrsntInfo.NibpTechAlm);
			index_start = 1;
			index_end = STR_ALM_NIBPRSTERR - STR_ALM_NIBPINITERROR + 1;
			break;
**/
		default:
			return;
	}

   if ( 0 == *index )
	   *index = index_start;
   
   i = *index + 1;
   if ( i > index_end )
	  i = index_start;

   while( i != *index ) 
   {
	  // alarm triggered?
	  cdtn_alarm =  TRUE == *((alarm_array_p + i )->Effect) 
					&& TRUE == (alarm_array_p + i )->Exist
					&& TRUE == (alarm_array_p + i )->Trg;
	  // alarm cleared, but latched, and now system set to latch mode.
	  cdtn_latch =  TRUE == *((alarm_array_p + i )->Effect)
					&& TRUE == (alarm_array_p + i )->Exist 
					&& FALSE == (alarm_array_p + i )->Trg
					&& TRUE == (alarm_array_p + i )->Latch 
					&& TRUE == *(AlmGlbCtlr.LatchP );
	  // alarm cleared, but not show yet.
	  cdtn_remain = TRUE == *((alarm_array_p + i )->Effect)
					&& TRUE == (alarm_array_p + i )->Exist
					&& FALSE == (alarm_array_p + i)->Trg
					&& FALSE == (alarm_array_p + i)->Prsnt;
	  
	  if ( cdtn_alarm || cdtn_latch || cdtn_remain ) 
	  {
		  if ( TRUE == (alarm_array_p + i )->Critical )
		  {
			  break;
		  }
		  else 
		  {
			  // if this is not the critical thing, 
			  // there could be some critical things after this alarm, 
			  // continue searching... and, if critical things are 
			  // not found finally, just use this one, remembered in "j".
			  if ( TRUE == first_round ) 
			  {
				  first_round = FALSE;
				  j		   = i;
			  }
		  }
	  }
	  i++;
	  if ( i > index_end )
	  {
		  i = index_start;
	  }
   }

   // this two variables must be renewed now ,必须更新以下几个参数的值,
   // 因为有可能没有找到最高优先级的报警，i其实最后进行了一次++操作.	-- empty 2011/04/29
   cdtn_alarm  = TRUE == *((alarm_array_p + i )->Effect) 
				 && TRUE == (alarm_array_p + i )->Exist
				 && TRUE == (alarm_array_p + i )->Trg;
   cdtn_latch  = TRUE == *((alarm_array_p + i )->Effect)
				 && TRUE == (alarm_array_p + i )->Exist 
				 && FALSE == (alarm_array_p + i )->Trg
				 && TRUE == (alarm_array_p + i )->Latch 
				 && TRUE == *(AlmGlbCtlr.LatchP );
   cdtn_remain = TRUE == *((alarm_array_p + i )->Effect)
				 && TRUE == (alarm_array_p + i )->Exist
				 && FALSE == (alarm_array_p + i)->Trg
				 && FALSE == (alarm_array_p + i)->Prsnt;


   if ( TRUE == (alarm_array_p + i )->Critical 
		&& ( cdtn_alarm || cdtn_latch || cdtn_remain ) )
		critical = TRUE;

   if ( FALSE == critical ) 
   {
		if ( FALSE == first_round ) 
		{
			i = j;  // use the first non-critical one.
					// this two variables must be renewed.
			cdtn_alarm  = TRUE == *((alarm_array_p + i )->Effect) 
						  && TRUE == (alarm_array_p + i )->Exist
						  && TRUE == (alarm_array_p + i )->Trg;
			cdtn_latch  = TRUE == *((alarm_array_p + i )->Effect)
						  && TRUE == (alarm_array_p + i )->Exist 
						  && FALSE == (alarm_array_p + i )->Trg
						  && TRUE == (alarm_array_p + i )->Latch 
						  && TRUE == *(AlmGlbCtlr.LatchP );
			cdtn_remain = TRUE == *((alarm_array_p + i )->Effect)
						  && TRUE == (alarm_array_p + i )->Exist
						  && FALSE == (alarm_array_p + i)->Trg
						  && FALSE == (alarm_array_p + i)->Prsnt;
		}
   }
   
   if ( i == *index ) 
   {
	   // don't find a new one.
	   if ( !cdtn_alarm && !cdtn_latch && !cdtn_remain ) 
	   {
			 // loop around, and nothing is found, say,
			 // no alarm is generated in the system at all.
			 if ( 0 != alarm_prsnt_p->AlmIndex ) 
			 {
				   // previsouly, there is an alarm, and now, no alarm,
				   // must redraw.
				   alarm_prsnt_p->AlmLev = INVALIDALARMLEVEL;
				   alarm_prsnt_p->BkGndColor = INVALIDALARMLEVEL;
				   alarm_prsnt_p->AlmIndex = 0;		
				   alarm_prsnt_p->AlmStr = (CHAR *)NULL;
				   *index = 0;
				   alarm_prsnt_p->Redraw = TRUE;
			 } 
			 else 
			 {
				   // there is no alarm last time either.
				   *index = 0;
				   alarm_prsnt_p->Redraw = FALSE;
			 }
	   } 
	   else 
	   {
		  // say, the old one still exists and may be get new features.
		  // what could be the new features? this could be a new one either.
		  // 1. alarm level changed. ( new one )
		  // 2. from latch to nonlatch.
		  // 3. from nonlatch to latch.
		  // 4. Cleared.
		  // 5. new one.
		  alarm_prsnt_p->Redraw = FALSE;
		  if ( alarm_prsnt_p->AlmIndex != i ) 
		  {
			  // this is destined to be a new one
			  *index  = i;
			  alarm_prsnt_p->AlmIndex = i;		
			  alarm_prsnt_p->AlmStr = *(( alarm_array_p + i )->AlmStr);
			  alarm_prsnt_p->AlmLev = *((alarm_array_p + i )->AlmLevP);
			  if ( TRUE == ( alarm_array_p + i )->Clearable
				   && TRUE == ( alarm_array_p + i )->Cleared )
					 alarm_prsnt_p->BkGndColor = INVALIDALARMLEVEL;
			  else
					 alarm_prsnt_p->BkGndColor = *((alarm_array_p + i )->AlmLevP);
	   
			  alarm_prsnt_p->AlmTimePrsnt = FALSE;
			  if ( cdtn_latch ) {
				  memcpy((CHAR *)&(alarm_prsnt_p->Time), (CHAR *)&((alarm_array_p + i )->Time), sizeof(DATETIME));  
				  alarm_prsnt_p->AlmTimePrsnt = TRUE;
			  }
			  
			  alarm_prsnt_p->Redraw = TRUE;
		  }
		  
		  if ( alarm_prsnt_p->AlmLev != *((alarm_array_p + i)->AlmLevP) ) 
		  {
			  alarm_prsnt_p->AlmLev = *((alarm_array_p + i)->AlmLevP);
			  alarm_prsnt_p->BkGndColor = *((alarm_array_p + i)->AlmLevP);
			  alarm_prsnt_p->Redraw = TRUE;
		  }
		  
		  if ( FALSE == alarm_prsnt_p->AlmTimePrsnt && cdtn_latch ) 
		  {
			  memcpy((CHAR *)&(alarm_prsnt_p->Time), (CHAR *)&((alarm_array_p + i )->Time), sizeof(DATETIME));  
			  alarm_prsnt_p->AlmTimePrsnt = TRUE;
			  alarm_prsnt_p->Redraw = TRUE;
		  }
		  if ( TRUE == alarm_prsnt_p->AlmTimePrsnt && cdtn_alarm ) 
		  {
			  alarm_prsnt_p->AlmTimePrsnt = FALSE;
			  alarm_prsnt_p->Redraw = TRUE;
		  }
		  if ( TRUE == (alarm_array_p + i)->Clearable 
			   && TRUE == (alarm_array_p + i)->Cleared 
			   && INVALIDALARMLEVEL != alarm_prsnt_p->BkGndColor ) 
			   {
			  alarm_prsnt_p->BkGndColor = INVALIDALARMLEVEL;
			  alarm_prsnt_p->Redraw = TRUE;
		  }
		  if ( FALSE == (alarm_array_p + i)->Cleared 
			   && INVALIDALARMLEVEL == alarm_prsnt_p->BkGndColor ) 
		  {
			  alarm_prsnt_p->BkGndColor = *((alarm_array_p + i)->AlmLevP );
			  alarm_prsnt_p->Redraw = TRUE;
		  }
		  (alarm_array_p + i )->Prsnt = TRUE;
	   }
   }
   else
	{
	   //  a new one is found, must Redraw it. and this piece of 
	   //  code must be indentical with "this is destined to be a new one" piece.
	   *index  = i;
	   alarm_prsnt_p->AlmIndex = i;		
	   alarm_prsnt_p->AlmStr = *((alarm_array_p + i )->AlmStr);
	   alarm_prsnt_p->AlmLev = *((alarm_array_p + i )->AlmLevP);
	   if (   TRUE == ( alarm_array_p + i )->Clearable
		   && TRUE == ( alarm_array_p + i )->Cleared )
		   alarm_prsnt_p->BkGndColor = INVALIDALARMLEVEL;
	   else
		   alarm_prsnt_p->BkGndColor = *((alarm_array_p + i )->AlmLevP);
	   
	   alarm_prsnt_p->AlmTimePrsnt = FALSE;
	   if ( cdtn_latch ) 
	   {
		   memcpy((CHAR *)&(alarm_prsnt_p->Time), (CHAR *)&((alarm_array_p + i )->Time), sizeof(DATETIME));  
		   alarm_prsnt_p->AlmTimePrsnt = TRUE;
	   }

	   (alarm_array_p + i )->Prsnt = TRUE;
	   alarm_prsnt_p->Redraw = TRUE;
   }
}



/*
Name:	 ProcessAVAlarm
Description:
		  Prepare signals send to alarm module. When this 
		  function is called, something must done to 
		  send command to alarm module before the next
		  calling.
Parameters:
		  None.
Return:   None.
Test and revision:
		  Inspection, 
*/
//static INT8 Alm_PromptNdx;
VOID ProcessAVAlarm (VOID)
{
//	 HINT_INFO msg;
	 
	 if ( FALSE == AlmGlbCtlr.AlmPause ) 
	 {
	 
		 AlmGlbCtlr.HighestAlmLevLastTime = AlmGlbCtlr.HighestAlmLev;
		 AlmGlbCtlr.HighestAlmLev = FindTheHigestLevel();

		 if ( AlmGlbCtlr.HighestAlmLev != AlmGlbCtlr.HighestAlmLevLastTime ) {
			 // say, a new alarm level is found.
			 AlmPrsntInfo.AlmLevel = AlmGlbCtlr.HighestAlmLev;
		 } 
		 else 
		 {		 
			if ( TRUE == AlmGlbCtlr.KeyboardLoad )
				AlmPrsntInfo.AlmLevel = AlmGlbCtlr.HighestAlmLev;
			else
				AlmPrsntInfo.AlmLevel = -1;
				
		 }
	 } 
	 else 
	 {	 
		 if ( FALSE == AlmGlbCtlr.AlmPauseLastTime ) 
		 {
			AlmPrsntInfo.AlmLevel = INVALIDALARMLEVEL;
			// This is very important to generate alarm sound
			// when pause is terminated.
			AlmGlbCtlr.HighestAlmLev = INVALIDALARMLEVEL;
		 } 
		 else  
		 {		 
			if ( TRUE == AlmGlbCtlr.KeyboardLoad )
				AlmPrsntInfo.AlmLevel = INVALIDALARMLEVEL;
			else
				AlmPrsntInfo.AlmLevel = -1;
				
		 }
	 }
	 AlmGlbCtlr.AlmPauseLastTime = AlmGlbCtlr.AlmPause;

	 if ( FALSE == AlmGlbCtlr.AlmSilent ) 
	 {
	 
		if ( *(AlmGlbCtlr.AlmSoundLevel) != AlmGlbCtlr.AlmSoundLevelLastTime 
			 || TRUE == AlmGlbCtlr.AlmSilentLastTime ) 
		{
			 AlmPrsntInfo.AudioLevel = *(AlmGlbCtlr.AlmSoundLevel);
		}
		else 
		{
			 if ( TRUE == AlmGlbCtlr.KeyboardLoad )
				AlmPrsntInfo.AudioLevel = *(AlmGlbCtlr.AlmSoundLevel);
			 else
				AlmPrsntInfo.AudioLevel = -1;
		}
	 }
	 else 
	 {
		  if ( FALSE == AlmGlbCtlr.AlmSilentLastTime ) {
			  AlmPrsntInfo.AudioLevel = 0;
		  } else {
		  
			  if ( TRUE == AlmGlbCtlr.KeyboardLoad )
				  AlmPrsntInfo.AudioLevel = 0;
			  else
				  AlmPrsntInfo.AudioLevel = -1;
		  }
	 }
	 AlmGlbCtlr.AlmSilentLastTime = AlmGlbCtlr.AlmSilent;
	 AlmGlbCtlr.AlmSoundLevelLastTime = *(AlmGlbCtlr.AlmSoundLevel);

	 if ( TRUE == AlmGlbCtlr.KeyboardLoad )
		 AlmGlbCtlr.KeyboardLoad = FALSE;
}

/*
Name:		  FindTheHigestLevel
Description:   Find the higest alarm level in the three alarm information
			   arrays. The items taken into acount should be triggered, exist 
			   and effect and not cleared.
Parameters:	None.
Return:		.
Test and revision:
			   Inspection,
*/
INT8 FindTheHigestLevel (VOID)
{
   INT16 i;
   INT8  highest = INVALIDALARMLEVEL;

	// The auditory or the auditory and visual ALARM manifestations shall not cease
	// without activating the function SILENCE/RESET.
	// Find the alarm triggerd & latched . 
	if ( TRUE == *AlmGlbCtlr.LatchP )
	{
		for (i = 1; i <= STR_ALM_PHS_MAX - STR_ALM_PHS_FIRST; i++)
		{
			if ( TRUE == *(PhsAlmInfo[i].Effect) 
				 && FALSE == PhsAlmInfo[i].Trg 
				 && TRUE == PhsAlmInfo[i].Exist 
				 && TRUE == PhsAlmInfo[i].Latch
				 && FALSE == PhsAlmInfo[i].Cleared 
				 && highest > *(PhsAlmInfo[i].AlmLevP) )
			   highest = *(PhsAlmInfo[i].AlmLevP);
		}
	}

	for (i = 1; i <= STR_ALM_PHS_MAX - STR_ALM_PHS_FIRST; i++)
	{
		if ( TRUE == *(PhsAlmInfo[i].Effect) 
			 && TRUE == PhsAlmInfo[i].Trg 
			 && TRUE == PhsAlmInfo[i].Exist 
			 && FALSE == PhsAlmInfo[i].Cleared 
			 && highest > *(PhsAlmInfo[i].AlmLevP))
		   highest = *(PhsAlmInfo[i].AlmLevP);
	}

	for (i = 1; i <= STR_ALM_TECH_MAX - STR_ALM_TECH_FIRST; i++)
	{
		if ( TRUE == *(TechAlmInfo[i].Effect )
			 && TRUE == TechAlmInfo[i].Trg 
			 && TRUE == TechAlmInfo[i].Exist 
			 && FALSE == TechAlmInfo[i].Cleared
			 && highest > *(TechAlmInfo[i].AlmLevP))
		  highest = *(TechAlmInfo[i].AlmLevP);
	}
	/** /
	for (i = 1; i <= STR_ALM_END - STR_ALM_END; i++)
	{
		if ( TRUE == *(NibpTechAlmInfo[i].Effect )
			 && TRUE == NibpTechAlmInfo[i].Trg 
			 && TRUE == NibpTechAlmInfo[i].Exist 
			 && FALSE == NibpTechAlmInfo[i].Cleared
			 && highest > *(NibpTechAlmInfo[i].AlmLevP))
		   highest = *(NibpTechAlmInfo[i].AlmLevP);
   }
   **/
   return (highest);
}


INT32  AlarmProc (HANDLE task, INT32 msg, UINT32 wParam, UINT32 lParam)
{
	task   = task;
	msg	= msg;
	wParam = wParam;
	lParam = lParam;

	return DefaultTskProc(task, msg, wParam, lParam);
}

VOID AlarmProcess(VOID)
{
	EnableAlarmForModule();   //在模块init函数中设置了模块加载后30秒不判断生理报警，若30s已到，则打开生理报警 -- empty 2011/04/29
	Para_Alarm_Judge();
	TriggerNewPhsAlarm();	  //如果模块是从关闭到打开的过程，则PhsAlmInfo[i].EffectLastTime将起到作用 -- empty 2011/04/29
	ProcessAlarmCntl();		  //主要处理报警暂停和静音持续时间的一些处理 -- empty 2011/04/29
	ProcessTechAlarm();		  //检测技术报警并构造技术报警显示的相关内容 -- empty 2011/04/29
	ProcessPhsAlarm();		//如果为报警暂停，显示剩余时间，不是则寻找一个生理报警 -- empty 2011/04/29
	//ProcessNibpTechAlarm();	  //对NIBP报警的特殊处理 -- empty 2011/04/29
	ProcessAVAlarm();		  //对报警声音的处理  -- empty 2011/04/29
	ProcessBlink();			  //闪烁处理:bit0:测量参数是否闪烁;bit1:高限是否闪烁;bit2:低限是否闪烁;
							  //bit7:是否需要刷新 ;1 ---- 需要,0 ---- 不需要 --empty 2011/04/29
	PickCriticalPhsAlarm();   //对多个同时最高优先级报警按照字符串的顺序排列后处理 -- empty 2011/04/29
	DealWithLanguage();		  //处理语言变更后的报警字符串，其实没做改动，只是重新载入而已 -- empty 2011/04/29
	ShowAlarmInfo();
	#if _ENB_NET_SEND_ALARM_INFO
	NetSendAlmInfo();
	#endif
}

