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

#ifndef _ALARM_H

#define _ALARM_H


#define INVALIDALARMLEVEL	3	 // this may be defined in other module.

#define ALARMPREHIBITSECONDS 30	// 模块加载后有多少秒不判断生理报警


// 由于报警中还会涉及到系统/网络/电源.所以为报警部分专门定义
// 如下“模块代号”
#define ALM_MID_SYSTEM	   100
#define ALM_MID_NET		  101
#define ALM_MID_POWER		102

//报警类型
typedef enum {
	ALM_TYPE_PHY	= 1,
	ALM_TYPE_TECH,
	ALM_TYPE_NIBP
} ALM_TYPE;

#define	ALM_FLAG_CLR				0		 /* 报警标志清除		*/
#define	ALM_FLAG_SET				0x0001	/* 报警标志设置		*/
#define	ALM_FLAG_NEW				0x8001	/* 新的报警			*/
#define	ALM_FLAG_CLR_LEADOFF_AUDIO  0x4000	/* 清除导联脱落报警音  */

// ALMPRESENT - 报警显示区域内的显示内容
typedef struct {
	 INT16		AlmIndex;	   // 报警的索引号。 如果为0, 不显示任何报警信息。
								  // 暂停提示信息的显示也包括在其中。保留不再使用。
	 CHAR		*AlmStr;		 // 将要引用的词条。
	 INT8		 AlmTimePrsnt;   // 报警词条之后是否应该显示报警发生的时间。
	 INT8		 BkGndColor;	 // 词条的底色。0: 红; 1,2:黄; 3: 标题栏的底色。
								  // 如果在NIBP测量区显示，则底色实际上是指提示字串的颜色，而非底色。
	 INT8		 AlmLev;		 // 该报警的级别。报警级别为无效时将显示区清除。
	 INT8		 Redraw;		 // 是否要重画该报警显示区。 TRUE-重画，FALSE - 保持。
	 DATETIME	 Time;		   // 将要显示的时间。
}ALM_PRESENT;

#define BLINK_MASK_BLINK	0x01   // 闪烁
#define BLINK_MASK_FLUSH	0x80   // 刷新

// bit0-测量参数是否闪烁。Bit1-高限是否闪烁。Bit2 - 低限是否闪烁。
// bit7-是否需要刷新，1-需要，0-不需要。
typedef struct {
	 UINT8 FHR1Blink;
	 UINT8 FHR2Blink;
	 UINT8 TOCOBlink;
	 UINT8 FMBlink;
}BLINK_FEATURE;


// ALMPRESENTINFO - 系统报警表示的内容
typedef struct {
	ALM_PRESENT	PhsAlm;			  // 生理报警区的显示内容
	ALM_PRESENT	TechAlm;			  // 技术报警区的显示内容
	BLINK_FEATURE  Blink;			   // 参数是否闪烁，以何种方式闪烁。
	INT8		   AudioLevel;		  // 是否需要向报警模块发送信息，-1，不发送，
									 // 0，静音，1-3，声音级别。
	INT8		   AlmLevel;			// -1，不发送，0-2，相应级别，3，无报警。
	INT16		  HighestNewPhsAlm;	// 当前一次判断后新发现的最高级别生理报警,如果发生
									 // 多个同一级别的新报警，则按照STRINGID中定义的
									 // 排列顺序来选取最先一个,不包括对ARR报警的处理。
	INT8		   HighestNewPhsAlmLevel;  
									 // 当前选取的报警级别。
	DATETIME	   Time;				// 这一次生理报警发生的时间。
	CHAR		   PauseMsg[40];		// 报警暂停信息的显示空间。
}ALM_PRESENTINFO;


// “ALARMINFOSTR”，各报警项的控制状态。
typedef struct {
	 
	 INT8	   *Effect;			// 指示该项报警开关是否有效，TRUE, 有效,FLASE，无效。与系统对报警开关的定义一致。
	 INT8		EffectLastTime;
									// 上一时刻的报警开关是否打开，
									// 因为需要在报警开关从关闭到打开时为正在trigger 
									// 状态的报警产生新报警的提示，所以需要判断。
									// 目前只为生理报警做考虑，因为技术报警是始终打开的。
	 INT8		Exist;			 // 相应的参数模块是否存在。
	 INT8		Trg;			   // 当前该报警项是否被触发。TRUE，触发。FALSE，清除。
	 INT8		Prsnt;			 // 指示该报警是否已经被显示过。根据需求，即便已经被清除的报警，只要没有显示过，就还需要进行显示。TRUE，已显示过。FALSE，未显示。
	 INT8		Clearable;		 // 该项的声光报警是否可以清除。TRUE，可以。FALSE，不可。
	 INT8		Cleared;		   // 表示目前的声光是否在清除状态。TRUE，在清除状态。FLASE，不在清除状态。
	 INT8		LeadOff;		   // 表示是否导联脱落，TRUE，是; FALSE, 不是。remedy bug 8.
	 UINT16	  SpecialLeadOff;	// 表示为非ECG/SPO2类的导联脱落报警。
	 CHAR	  **AlmStr;			// 报警显示的字串指针的指针。
	 INT8	   *AlmLevP;		   // 指向报警级别的指针。
	 INT8		Latch;			 // 指示该项目的报警是否被latch.
	 INT8		Critical;		  // 说明该种报警是否系统优先级最高，如果系统优先级最高，则首先显示。
	 DATETIME	Time;			  // 上一次从清除态向触发态转换的系统时间。
	 INT8		Module;			// 指明该报警与那一个模块相关。 
	 INT8		NewAlarm;		  // 如果是一次新发生的报警，该位将会被写为TRUE，如果不是，
									// 则该位将会被写为FALSE，目前只有生理报警中有用。
	 INT8		Hold;			  // 当该报警产生后尚未用于触发报警记录/存储的时候，Hold一直被
									// 保留为TRUE，当该报警被清除或者是被用于触发报警记录/存储后，
									// 被设置为FALSE。
	 INT8		AllClrable;		// 在按下Pause键后，是否需要将该项报警全部清除。
	 
}ALM_ITEM;


// “ALM_CTRL_BLOCK”， 关于报警的全局控制块
typedef struct {
	 INT8	   *LatchP;				   // 指向Latch方式字节的指针。
	 INT8		PrvLatchState;			// 上一次的latch状态
	 INT8		AlmSilent;				// 当前的Silence状态。（因为Silence的控制完全在该部分中实现，所以系统的其他软件部件无须再定义Silence和Pause状态）
	 INT16	   AlmSilenceRemain;		 // Silence状态还剩下多少秒。
	 INT16	   AlmPauseRemain;		   // Pause状态还剩下多少秒。
	 INT8		AlmPause;				 // 当前的Pause状态。
	 INT8		TechNew;				  // 是否有新的技术报警发生。（用于控制打断静音或者暂停状态）
	 INT8		PhsNew;				   // 是否有新的生理报警发生。
	 INT16	   PhsAlmDisFocusIndex;	  // 当前正在报出的一次生理报警，如果为0,则无报警发生
	 INT16	   TechAlmDisFocusIndex;	 // 当前正在报出的一次技术报警
	 
	 INT8		HighestAlmLev;			// 当前最高的报警级别
	 INT8		HighestAlmLevLastTime;	// 上一次判断时的最高报警级别。
	 
	 INT8	   *AlmSoundLevel;			// 指向一个全局数据区，说明系统报警音量级别的当前值。
	 INT8		AlmSoundLevelLastTime;	// 说明上一次判断时系统的音量级别。
	 INT8		AlmPauseLastTime;		 // 上一次的Pause状态
	 INT8		AlmSilentLastTime;		// 上一次的Silent状态。
	 INT8		LanChange;				// 语言是否发生变化。
	 INT8		KeyboardLoad;			 // 表示keyboard刚刚加载，需要再次
										   // 向其发送报警信息。
}ALM_CTRL_BLOCK;

#ifdef  ALARM_GLOBALS
#define ALARM_EXTERN  
#else
#define ALARM_EXTERN   extern
#endif


//----------------------------------------------------------------
// Global things defined in this source file.
// Global data to say how to display alarm information.
ALARM_EXTERN ALM_PRESENTINFO AlmPrsntInfo;  

// things only used in this file.
ALARM_EXTERN BLINK_FEATURE   BlinkFeature;
 
// Global controller of the alarm system.
ALARM_EXTERN ALM_CTRL_BLOCK AlmGlbCtlr;   

// Global, counter to fire alarm system.
ALARM_EXTERN CHAR  AlmTimerForModuleChange[MID_MAX];
ALARM_EXTERN INT16 Alm_PrompNdx4MdlLoad[MID_MAX];

// Physical alarm information.
// As "pause" state is displayed in the area where physiological 
// alarm is displayed, so, plus 1.
ALARM_EXTERN ALM_ITEM   PhsAlmInfo[STR_ALM_PHS_MAX - STR_ALM_PHS_FIRST + 2]; 

// Technical alarm information.
ALARM_EXTERN ALM_ITEM   TechAlmInfo[STR_ALM_TECH_MAX - STR_ALM_TECH_FIRST + 2]; 

// NIBP technical alarm information.
ALARM_EXTERN ALM_ITEM   NibpTechAlmInfo[1 + 1]; 


/* 对外提供的接口函数 */
VOID  TriggerAlarm(UINT16 trg, INT16 index); 
VOID  TriggerAlarm2(UINT16 trg, INT16 index); 
VOID  ChangeModuleInfoForAlmSystem(BOOL load, INT16 module_type);
VOID  OnSilence(VOID);
VOID  OnPause(VOID);
VOID  ChangeModuleInfoForAlmSystem2(BOOL load, INT16 module_type);
VOID  OnSilence2(VOID);
VOID  OnPause2(VOID);
BOOL  InitAlarmSystem(VOID);
VOID  TermAlarm(VOID);
VOID  ClearAllAlarm (INT16 module_id);
VOID  ProcessAlarmInfo (VOID);

INT32 AlarmProc (HANDLE task, INT32 msg, UINT32 wParam, UINT32 lParam);
VOID  AlarmProcess(VOID);
#endif

