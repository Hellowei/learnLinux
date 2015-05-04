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
#if !defined(_APPMAIN_H)
#define	  _APPMAIN_H

/**
 ** MSG_USER_MMAN_CMD消息下面的子类型号;
 ** MSG_USER_MMAN_CMD消息用于通知APP任务与参数模块发指令交互;
 **
**/
typedef  enum {
	MMAN_CODE_ECGGAIN,  // 改变ecg增益; WPARAM : code;  LPARAM, low:channel; high:gain;

	MMAN_CODE_ALMVOL,   // 改变报警音量.
	MMAN_CODE_ALMLEV,   // 改变报警级别.
	MMAN_CODE_BEATVOL,  // 改变心跳音量
	MMAN_CODE_MAX
} MMAN_CODE;

/* def{{{ in usercfg.c */

VOID ClearPatientInfo(VOID);


/***********************************************************************************
函数：	  Load_Dynamic_Config
函数功能：将FLASH中的系统配置信息读取到当前系统配置信息中
调用方式：在系统初始化期间，获取系统配置信息
***********************************************************************************/
VOID Load_Dynamic_Config();

/***********************************************************************************
函数：	  Save_Config
函数功能：将当前配置中的内容写入EPROM中
调用方式：在确认执行“保存设置”后调用
调用参数：
		  cfg_kid:
其他说明：
		  缺省配置不需要存储
***********************************************************************************/
VOID  Save_Config(INT16 cfg_kid);
VOID  Save_Config2(INT16 cfg_kid);

/***********************************************************************************
函数：	  Load_Default_Config
函数功能：用来读取缺省配置的各选项到当前配置数据结构中
调用方式：在确认执行“缺省设置”后调用
调用参数：type： 
		  ＝ 0 读取成人缺省配置
		  ＝ 1 读取小儿缺省配置
		  ＝ 2 读取新生儿缺省配置
***********************************************************************************/
VOID Load_Default_Config(VOID);

/***********************************************************************************
函数：	  Load_Default_Common_Config
函数功能：用来设置缺省厂家配置的共同选项(在成人，小儿，新生儿三种不同的病人类型下)
调用方式：在调用缺省设置时调用
调用参数：无
其他说明：缺省配置是预先定义的，所以不需要存储在EPROM中，而存储在程序内存中，因此，
			在初始化期间，需要读到结构变量中，方便以后使用。
***********************************************************************************/

VOID Load_Default_Common_Config(INT module_id ) ;


/***********************************************************************************
函数：	  Load_Default_Adult_Config
函数功能：用来设置缺省厂家成人配置的各选项
调用方式：在调用缺省设置时调用
调用参数：无
其他说明：缺省配置是预先定义的，所以不需要存储在EPROM中，而存储在程序内存中，因此，
			在初始化期间，需要读到结构变量中，方便以后使用。
***********************************************************************************/
VOID Load_Default_Adult_Config(INT module_id ) ;

/***********************************************************************************
函数：	  Load_Default_Ped_Config
函数功能：用来设置缺省厂家小儿配置的各选项
调用方式：在调用缺省设置时调用
调用参数：无
其他说明：缺省配置是预先定义的，所以不需要存储在EPROM中，而存储在程序内存中，因此，
			在初始化期间，需要读到结构变量中，方便以后使用。
***********************************************************************************/
VOID Load_Default_Ped_Config(INT module_id ) ;

/***********************************************************************************
函数：	  Load_Default_Neo_Config
函数功能：用来设置缺省厂家新生儿配置的各选项
调用方式：在调用缺省设置时调用
调用参数：无
其他说明：缺省配置是预先定义的，所以不需要存储在EPROM中，而存储在程序内存中，因此，
			在初始化期间，需要读到结构变量中，方便以后使用。
***********************************************************************************/
VOID Load_Default_Neo_Config(INT module_id ) ;


/***********************************************************************************
函数：	  Load_FHR_Config
函数功能：用来设置缺省厂家胎监配置的各选项
调用方式：在调用缺省设置时调用
调用参数：无
其他说明：缺省配置是预先定义的，所以不需要存储在EPROM中，而存储在程序内存中，因此，
			在初始化期间，需要读到结构变量中，方便以后使用。
***********************************************************************************/
#if _ENB_FHR 
STATUS Load_FHR_Config( INT8 type );
VOID  Save_FHR_Config(INT16 info_ndx, INT8 type);
STATUS  Save_FHR_Config2(INT16 info_ndx, INT8 type);
#endif


/***********************************************************************************
函数：	  InitRedundantStore
函数功能：存储所有模块的参数报警冗余数据
调用方式：在系统初始化期间，完成E2PROM数据读取后进行
调用参数：无
***********************************************************************************/
VOID InitRedundantStore(VOID);

/***********************************************************************************
函数：	  EcgRedundantStore
函数功能：存储ECG模块的参数报警冗余数据
调用方式：在完成E2PROM数据的写入后进行调用
调用参数：无
***********************************************************************************/
VOID EcgRedundantStore(VOID);

/***********************************************************************************
函数：	  RespRedundantStore
函数功能：存储RESP模块的参数报警冗余数据
调用方式：在完成E2PROM数据的写入后进行调用
调用参数：无
***********************************************************************************/
VOID RespRedundantStore(VOID);

/***********************************************************************************
函数：	  Spo2RedundantStore
函数功能：存储SPO2模块的参数报警冗余数据
调用方式：在完成E2PROM数据的写入后进行调用
调用参数：无
***********************************************************************************/
VOID Spo2RedundantStore(VOID);

/***********************************************************************************
函数：	  NibpRedundantStore
函数功能：存储NIBP模块的参数报警冗余数据
调用方式：在完成E2PROM数据的写入后进行调用
调用参数：无
***********************************************************************************/
VOID NibpRedundantStore(VOID);

/***********************************************************************************
函数：	  TempRedundantStore
函数功能：存储TEMP模块的参数报警冗余数据
调用方式：在完成E2PROM数据的写入后进行调用
调用参数：无
***********************************************************************************/
VOID TempRedundantStore(VOID);

/***********************************************************************************
函数：	  Ibp1RedundantStore
函数功能：存储IBP1模块的参数报警冗余数据
调用方式：在完成E2PROM数据的写入后进行调用
调用参数：无
***********************************************************************************/
VOID IbpRedundantStore(VOID);


/***********************************************************************************
函数：	  FhrRedundantStore
函数功能：存储IBP1模块的参数报警冗余数据
调用方式：在完成E2PROM数据的写入后进行调用
调用参数：无
***********************************************************************************/
#if _ENB_FHR
VOID  FhrRedundantStore (VOID);
#endif


/***********************************************************************************
函数：	  Set_Module_Alarm_OnLoad( INT16 moduleid )
函数功能：对模块参数报警进行相关设置
调用方式：在模块加载完毕
调用参数：
		  moduleid:
			表示 ECG, SPO2, NIBP, TEMP, FHR等模块
其他说明：RR参数此处包含在ECG模块中
***********************************************************************************/
VOID Set_Module_Alarm_OnLoad( INT16 moduleid );

/***********************************************************************************
函数：	  Set_Module_Alarm_OnUnLoad( INT16 moduleid )
函数功能：对模块参数报警进行相关设置
调用方式：在模块卸载完毕
调用参数：
		  moduleid:
			表示 ECG, SPO2, NIBP, TEMP, FHR等模块
其他说明：RR参数此处包含在ECG模块中
***********************************************************************************/
VOID Set_Module_Alarm_OnUnLoad( INT16 moduleid );

/**********************************************************************************
函数：	  Para_Alarm_Judge_Int()
函数功能：对模块整型参数进行报警判断
调用方式：在1s中断处理Para_Alarm_Judge函数中调用
调用参数：
		  paraid:		参数代码
		  alarm:		是否报警判断
		  high:			报警上限
		  low:			报警下限
		  level:		报警级别
		  paravalue:	参数值
返回：
		  TRUE			返回正确
		  FALSE			返回错误

***********************************************************************************/
STATUS Para_Alarm_Judge_Int(INT16 paraid, INT16 high, INT16 low, INT16 paravalue);

/**********************************************************************************
函数：	  Para_Alarm_Judge_Float()
函数功能：对模块浮点型参数进行报警判断
调用方式：在1s中断处理Para_Alarm_Judge函数中调用
调用参数：
		  paraid:		参数代码
		  alarm:		是否报警判断
		  high:			报警上限(浮点)
		  low:			报警下限(浮点)
		  level:		报警级别
		  paravalue:	参数值(浮点)
返回：
		  TRUE			返回正确
		  FALSE			返回错误

***********************************************************************************/
STATUS Para_Alarm_Judge_Float(INT16 paraid, FLOAT high, FLOAT low, FLOAT paravalue);

/**********************************************************************************
函数：	  Para_Alarm_Judge()
函数功能：对模块参数进行报警判断
调用方式：在1s中断中进行
调用参数：无
返回：
		  TRUE			返回正确
		  FALSE			返回错误
***********************************************************************************/
STATUS Para_Alarm_Judge(VOID);


/**********************************************************************************
函数：	InitUserConfig
函数功能：初始化系统配置，判断系统是否为第一次运行（EEPROM中没有标志），
		  如果是，保存3种厂家缺省配置为相应的用户缺省配置，初始化当前配置
		  为厂家缺省成人配置
调用方式：系统初始化时调用一次
调用参数：force_init -- 是否强行初始化所有配置而不判断系统是否已经初始化
返回：
		  TRUE	  系统是第一次运行
		  FALSE		系统不是第一次运行
***********************************************************************************/
BOOL InitUserConfig( BOOL force_init );

/**********************************************************************************
函数：	InitConfigWhoHasNoDefaultValue
函数功能：初始化没有缺省值的系统配置
调用方式：在InitConfig中调用
调用参数：无
返回：	无
***********************************************************************************/
VOID  InitConfigWhoHasNoDefaultValue( VOID );

BOOL  InitE2eprom(VOID);

/* }}}def in usercfg.c */

/* def{{{ in tskio.c */

BOOL  InitIoAckInfo(VOID);
BOOL  InitIoTsk (VOID);
VOID  TermIoTsk (VOID);

/* }}}def in tskio.c */

/* def{{{ in ecg.c */
BOOL  InitEcg(VOID);

/* }}}def in ecg.c */

/* def{{{ in resp.c */
BOOL  InitResp(VOID);

/* }}}def in resp.c */

/* def{{{ in temp.c */
BOOL  InitTemp(VOID);

/* }}}def in temp.c */

/* def{{{ in spo2.c */

/* }}}def in spo2.c */
BOOL  InitSpo2(VOID);

/* def{{{ in nibp.c */
BOOL  InitNibp(VOID);

/* }}}def in nibp.c */

/* def{{{ in ibp.c */
BOOL  InitIbp(VOID);

/* }}}def in ibp.c */

/* def{{{ in disppara.c */
VOID InitLastParaValue(VOID);

VOID CalcEcgAllParaPos( INT16 x, INT16 y, INT16 height, BOOL disp_almlimit_flag );
VOID CalcSpo2AllParaPos( INT16 x, INT16 y, INT16 height, BOOL disp_almlimit_flag );
VOID CalcNibpAllParaPos( INT16 x, INT16 y, INT16 height, BOOL disp_almlimit_flag );
VOID CalcIbpAllParaPos( INT16 x, INT16 y, INT16 height, BOOL disp_almlimit_flag );
VOID CalcRespAllParaPos( INT16 x, INT16 y, INT16 height, BOOL disp_almlimit_flag );
VOID CalcTempAllParaPos( INT16 x, INT16 y, INT16 height, BOOL disp_almlimit_flag );
VOID GetAllDispParaValue(VOID);

VOID ShowParaRegion(VOID);

VOID HrFromECG(VOID);
VOID HrFromPLETH(VOID);
VOID DispEcgParam(VOID);
VOID DispSpo2Param(VOID);
VOID DispNibpParam(VOID);
VOID DispIbpParam(VOID);
VOID DispRespParam(VOID);
VOID DispTempParam(VOID);

VOID FlushParamValue(VOID);
BOOL CeateSysParamRegionWnd(VOID);
VOID BlinkParamValue(VOID);

INT16  GetFloatText(CHAR *str, INT16 len, INT32 value, INT32 base, UINT8 format);

VOID   ReInitEcgCtrlGroupColor(VOID);
VOID   ReInitSpo2CtrlGroupColor(VOID);
VOID   ReInitRespCtrlGroupColor(VOID);
VOID   ReInitTempCtrlGroupColor(VOID);
VOID   ReInitNibpCtrlGroupColor(VOID);
VOID   ReInitIbpCtrlGroupColor(VOID);


/* }}}def in disppara.c */

/* def{{{ in appmain.c  */

BOOL   InitMonitor(VOID);
INT32  MainScnProc(HWND hWnd, INT32 message, WPARAM wParam, LPARAM lParam);
BOOL   ResetHotkeyCtrlId(VOID);
BOOL   CeateHotkeyCtrlGroup(VOID);
VOID   GUIAPI  BacktoMainScreen(VOID);
VOID   SwitchWaveOfParam(INT mod_id, BOOL on );
VOID   SetParamStatus( UINT8 module_id, BOOL can_using );
VOID   SetSensorStatus( UINT8 module_id, INT8 recovered_sec );
VOID   GetTimeStr( DATETIME *time, CHAR *str );
VOID   UpdateSysDatetime(DATETIME *datetime);
VOID   ProcAfterCreateTasks(VOID);
INT16  SelectBeepSource( VOID );
VOID   DataCorrection( VOID );
VOID   UpdateStatus(VOID);

VOID   LoadSysModule(VOID);

VOID   SetParamStatus2( UINT8 module_id, BOOL can_using );
VOID   SetSensorStatus2( UINT8 module_id, INT8 recovered_sec );

VOID   SetCtrlDataAddData2 (PCTRLDATA pData, INT16 ctrl_nr, INT16 id, UINT32 addData);

VOID   ShowNibpAlarmInfo(VOID);
VOID   BlinkNibpAlmInfo(VOID);
VOID   ShowPhsAlarmInfo (VOID);
VOID   ShowTechAlarmInfo (VOID);
VOID   ShowAlarmInfo (VOID);
VOID   ShowDateTime(VOID);

VOID   ShowDemo(VOID);
VOID   BlinkDemo(VOID);
VOID   SwitchOffDemoText(VOID);

VOID   InitHotkeyChoice (VOID);
VOID   SetSysDatetime (DATETIME *);


/*  }}}def in appmain.c  */

/* def{{{ in limits.c	*/

BOOL  CheckRangeExceed( PARAM_LMTS_ID param_index, INT16 *param_value );

/* }}}def in limits.c   */

/* def{{{ in infobar.c  */

BOOL  InitSysInfoItem(VOID);
VOID  TermSysInfoItem(VOID);
VOID  ShowSysInfoItem(VOID);
VOID  RemoveSysInfoItem(INT16 id);
INT16 RegisterSysInfoItem(const PHINT_INFO pHint);
VOID  ShowBattaryState(VOID);

/* }}}def in infobar.c */


/* def{{{ in sysevent.c  */

VOID  RegisterSysEvent(INT16 string_id );
BOOL  InitSysEvent(VOID);
VOID  TermSysEvent(VOID);
VOID  SysEventDialog (HANDLE hOwner);

/* }}}def in sysevent.c */

/* def{{{ in modulman.c  */

VOID  CheckPmRcvTimeout(INT32 read_num);
VOID  CheckKbRcvTimeout(INT32 read_num);
BOOL  InitModuleMan (VOID);
BOOL  IsCommStoped (UINT8 mid);
BOOL  CommError (UINT8 mid);


/* }}}def in modulman.c */


/* def{{{ in appproc.c  */

VOID  SetupFuncBlock(UINT8 mid);

/* }}}def in approc.c */


/* def{{{ in patient.c  */


VOID  ShowPatientType(VOID);
VOID  ShowPatientBedNo(VOID);


/* }}}def in patient.c */

/* def{{{ in sysfunc.c  */


VOID  InitNewPatientInfo (VOID);
VOID  ShowDemoScale (VOID);
VOID  ChangeSysSetup (VOID);
INT16 DaysInThisMonth (INT16 year, INT16 month);
BOOL  IsLeapYear (INT16 year);

VOID  DateToStr (char *string, DATETIME *date, INT style);
VOID  InitVersionInfo (VOID);
VOID  GetCompanyNameVersion (VOID);
VOID  EnterFrozen (VOID);
VOID  ExitFrozen (VOID);


/* }}}def in sysfunc.c */


/* def{{{ in recall.c  */


VOID  RecallSetupDialog (HANDLE hOwner);


/* }}}def in recall.c */

/* def{{{ in colordlg.c  */


VOID  ColorDialog (HANDLE hOwner);


/* }}}def in colordlg.c */
BOOL CreateMenuGroupsCtrlGroup(int index, STRINGID caption, DWORD dwStyle,
								DWORD dwAddData, DWORD dwAddData2, MSG_PFN proc);
BOOL CreateGraphGroup(VOID);


/* def{{{ in timedlg.c  */


VOID TimeSetupDialog(HWND parent);

VOID EventSetupDialog(HANDLE hOwner);
/* }}}def in timedlg.c */

/* def{{{ in setupdlg.c  */

VOID  PatientSetupDialog (HWND parent);

VOID  SysSetupDialog(HANDLE hOwner);


/* }}}def in setupdlg.c */

/* def{{{ in maintain.c  */


VOID  MaintainDialog (HANDLE hOwner);


/* }}}def in maintain.c */


/* def{{{ in drug.c  */


VOID  InitDrugValue(VOID);
VOID  DrugCalcDialog(HANDLE hOwner);
VOID  TitrationDialog(HANDLE hOwner);

VOID  SetA8SysDatetime (DATETIME *datep);

BOOL CreateDynTrendLabel(VOID);
BOOL CreateOxyCRGHotkey(VOID);

/* }}}def in drug.c */

#ifdef APPMAIN_GLOBALS
#define APPMAIN_EXT 
#else 
#define APPMAIN_EXT extern 
#endif

APPMAIN_EXT MONITORCONFIG   MonitorConfig;
APPMAIN_EXT VERINFO		 VerInfo[MID_MAX];
APPMAIN_EXT DATETIME		DateTime;
APPMAIN_EXT struct tm	   DateTimeEx;
APPMAIN_EXT MONITORINFO	 MonitorInfo;
APPMAIN_EXT MONITOR_FUNC	FuncConfig;
APPMAIN_EXT SENSOR_STATUS   SensorStatus[SENSOR_MAX];
APPMAIN_EXT PARAM_INFO	  ParamsInfo[PARAM_MAX];
APPMAIN_EXT STRINGID		WaveName[MAX_WAVE_BLOCK_NUM];
APPMAIN_EXT INT8			ParaName[PARA_BLOCK_MAX];
APPMAIN_EXT INT8			NoWavePara[PARA_BLOCK_MAX];


#if (_ENB_NV_MEM_FUNC > 0 )
APPMAIN_EXT REDUNDANT_INFO  ParaRedundantInfo[ALM_PARA_MAX]; 
#endif

APPMAIN_EXT CONFIG_BACKUP  ConfigBackup;


/**
 **  在gOnOff声明时,需要指定数组的长度.否则外部在调用它们时,使用TABLESIZE(gOnOff),会出错.
 **  这可能是borland编译器的问题.
 **  ERIC,  2006.04.19.
 **/
extern  STRINGID  gOnOff[2];
extern  STRINGID  gAlmLev[3];
extern  STRINGID  gPressureUnit[2];
extern  STRINGID  gTempUnit[2];

extern  BOOL	 gDefaultFlag;
extern  BOOL	 gChangeRecWaveFlag;
extern  BOOL	 gOpenAllConfig;
extern  INT8	 gOldPatientType, gOldFace, gOldScanMode, gOldShowLimits;
extern  VOID FhrSetupDialog (HWND parent);
extern  VOID TocoSetupDialog (HWND parent);
extern  VOID FmSetupDialog (HWND parent);
extern  VOID PutStatusInfoString(UINT8 index, UCHAR	  *str, PBUTTONBMP pbmp);
extern  VOID PutStatusInfoStr_ID(UINT8 index, STRINGID str_id, PBUTTONBMP pbmp);
extern  VOID ReInitFhrGphMem(UCHAR type);

APPMAIN_EXT VOID OnloadIbpModule(VOID);
APPMAIN_EXT VOID UnloadIbpModule(VOID);

APPMAIN_EXT VOID SetAllParamFont(VOID);					   //Change by Latrom_06-27-2011
APPMAIN_EXT VOID SetAllModuleSelect (VOID);					  //Change by Latrom_07-25-2011
APPMAIN_EXT VOID ReSetAllParamFont(VOID);
APPMAIN_EXT BOOL DealWithLangChange (UINT8 lang);			 //add by empty 2011/06/28
APPMAIN_EXT VOID IntoStandby (VOID);	// Change by Latrom_11-11-2011
APPMAIN_EXT VOID TestFlushWave(VOID);
APPMAIN_EXT VOID SelectKeyboardType(UINT8 kbType, UCHAR *caption, UCHAR *tips);
APPMAIN_EXT INT32 UseKeyboard(HANDLE hWnd, DWORD wParam, LPARAM lParam);
APPMAIN_EXT VOID ShowPatinetInfo(VOID);
APPMAIN_EXT VOID ScreenInfoOut(UCHAR *info);
APPMAIN_EXT INT32 OnClickPatientSetupDialog(HWND parent, HWND crtrl, LPARAM lParam);
APPMAIN_EXT UCHAR *GetFetalHearIcon(VOID);
APPMAIN_EXT VOID   EnterDemo(VOID);
APPMAIN_EXT VOID   ExitDemo(VOID);
#if _ENB_AUTOUSB
APPMAIN_EXT void AutoUsbTask(void *pdata);
#endif
APPMAIN_EXT int SetNetStatus(VOID);

#endif

