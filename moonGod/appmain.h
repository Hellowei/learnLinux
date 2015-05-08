/*****************************************************************************************
��Ȩ����:			�����ص�
�汾��:				1.0.0
��������:			2011.04.15
�ļ���:				
����:				�����ص�
����˵��:			
����˵��:			��
�����ļ���ϵ:		���ļ�Ϊ���̹�Լ�����ļ�

�޸ļ�¼:
��¼1:
�޸���:
�޸�����:
�޸�����:
�޸�ԭ��:
*****************************************************************************************/
#if !defined(_APPMAIN_H)
#define	  _APPMAIN_H

/**
 ** MSG_USER_MMAN_CMD��Ϣ����������ͺ�;
 ** MSG_USER_MMAN_CMD��Ϣ����֪ͨAPP���������ģ�鷢ָ���;
 **
**/
typedef  enum {
	MMAN_CODE_ECGGAIN,  // �ı�ecg����; WPARAM : code;  LPARAM, low:channel; high:gain;

	MMAN_CODE_ALMVOL,   // �ı䱨������.
	MMAN_CODE_ALMLEV,   // �ı䱨������.
	MMAN_CODE_BEATVOL,  // �ı���������
	MMAN_CODE_MAX
} MMAN_CODE;

/* def{{{ in usercfg.c */

VOID ClearPatientInfo(VOID);


/***********************************************************************************
������	  Load_Dynamic_Config
�������ܣ���FLASH�е�ϵͳ������Ϣ��ȡ����ǰϵͳ������Ϣ��
���÷�ʽ����ϵͳ��ʼ���ڼ䣬��ȡϵͳ������Ϣ
***********************************************************************************/
VOID Load_Dynamic_Config();

/***********************************************************************************
������	  Save_Config
�������ܣ�����ǰ�����е�����д��EPROM��
���÷�ʽ����ȷ��ִ�С��������á������
���ò�����
		  cfg_kid:
����˵����
		  ȱʡ���ò���Ҫ�洢
***********************************************************************************/
VOID  Save_Config(INT16 cfg_kid);
VOID  Save_Config2(INT16 cfg_kid);

/***********************************************************************************
������	  Load_Default_Config
�������ܣ�������ȡȱʡ���õĸ�ѡ���ǰ�������ݽṹ��
���÷�ʽ����ȷ��ִ�С�ȱʡ���á������
���ò�����type�� 
		  �� 0 ��ȡ����ȱʡ����
		  �� 1 ��ȡС��ȱʡ����
		  �� 2 ��ȡ������ȱʡ����
***********************************************************************************/
VOID Load_Default_Config(VOID);

/***********************************************************************************
������	  Load_Default_Common_Config
�������ܣ���������ȱʡ�������õĹ�ͬѡ��(�ڳ��ˣ�С�������������ֲ�ͬ�Ĳ���������)
���÷�ʽ���ڵ���ȱʡ����ʱ����
���ò�������
����˵����ȱʡ������Ԥ�ȶ���ģ����Բ���Ҫ�洢��EPROM�У����洢�ڳ����ڴ��У���ˣ�
			�ڳ�ʼ���ڼ䣬��Ҫ�����ṹ�����У������Ժ�ʹ�á�
***********************************************************************************/

VOID Load_Default_Common_Config(INT module_id ) ;


/***********************************************************************************
������	  Load_Default_Adult_Config
�������ܣ���������ȱʡ���ҳ������õĸ�ѡ��
���÷�ʽ���ڵ���ȱʡ����ʱ����
���ò�������
����˵����ȱʡ������Ԥ�ȶ���ģ����Բ���Ҫ�洢��EPROM�У����洢�ڳ����ڴ��У���ˣ�
			�ڳ�ʼ���ڼ䣬��Ҫ�����ṹ�����У������Ժ�ʹ�á�
***********************************************************************************/
VOID Load_Default_Adult_Config(INT module_id ) ;

/***********************************************************************************
������	  Load_Default_Ped_Config
�������ܣ���������ȱʡ����С�����õĸ�ѡ��
���÷�ʽ���ڵ���ȱʡ����ʱ����
���ò�������
����˵����ȱʡ������Ԥ�ȶ���ģ����Բ���Ҫ�洢��EPROM�У����洢�ڳ����ڴ��У���ˣ�
			�ڳ�ʼ���ڼ䣬��Ҫ�����ṹ�����У������Ժ�ʹ�á�
***********************************************************************************/
VOID Load_Default_Ped_Config(INT module_id ) ;

/***********************************************************************************
������	  Load_Default_Neo_Config
�������ܣ���������ȱʡ�������������õĸ�ѡ��
���÷�ʽ���ڵ���ȱʡ����ʱ����
���ò�������
����˵����ȱʡ������Ԥ�ȶ���ģ����Բ���Ҫ�洢��EPROM�У����洢�ڳ����ڴ��У���ˣ�
			�ڳ�ʼ���ڼ䣬��Ҫ�����ṹ�����У������Ժ�ʹ�á�
***********************************************************************************/
VOID Load_Default_Neo_Config(INT module_id ) ;


/***********************************************************************************
������	  Load_FHR_Config
�������ܣ���������ȱʡ����̥�����õĸ�ѡ��
���÷�ʽ���ڵ���ȱʡ����ʱ����
���ò�������
����˵����ȱʡ������Ԥ�ȶ���ģ����Բ���Ҫ�洢��EPROM�У����洢�ڳ����ڴ��У���ˣ�
			�ڳ�ʼ���ڼ䣬��Ҫ�����ṹ�����У������Ժ�ʹ�á�
***********************************************************************************/
#if _ENB_FHR 
STATUS Load_FHR_Config( INT8 type );
VOID  Save_FHR_Config(INT16 info_ndx, INT8 type);
STATUS  Save_FHR_Config2(INT16 info_ndx, INT8 type);
#endif


/***********************************************************************************
������	  InitRedundantStore
�������ܣ��洢����ģ��Ĳ���������������
���÷�ʽ����ϵͳ��ʼ���ڼ䣬���E2PROM���ݶ�ȡ�����
���ò�������
***********************************************************************************/
VOID InitRedundantStore(VOID);

/***********************************************************************************
������	  EcgRedundantStore
�������ܣ��洢ECGģ��Ĳ���������������
���÷�ʽ�������E2PROM���ݵ�д�����е���
���ò�������
***********************************************************************************/
VOID EcgRedundantStore(VOID);

/***********************************************************************************
������	  RespRedundantStore
�������ܣ��洢RESPģ��Ĳ���������������
���÷�ʽ�������E2PROM���ݵ�д�����е���
���ò�������
***********************************************************************************/
VOID RespRedundantStore(VOID);

/***********************************************************************************
������	  Spo2RedundantStore
�������ܣ��洢SPO2ģ��Ĳ���������������
���÷�ʽ�������E2PROM���ݵ�д�����е���
���ò�������
***********************************************************************************/
VOID Spo2RedundantStore(VOID);

/***********************************************************************************
������	  NibpRedundantStore
�������ܣ��洢NIBPģ��Ĳ���������������
���÷�ʽ�������E2PROM���ݵ�д�����е���
���ò�������
***********************************************************************************/
VOID NibpRedundantStore(VOID);

/***********************************************************************************
������	  TempRedundantStore
�������ܣ��洢TEMPģ��Ĳ���������������
���÷�ʽ�������E2PROM���ݵ�д�����е���
���ò�������
***********************************************************************************/
VOID TempRedundantStore(VOID);

/***********************************************************************************
������	  Ibp1RedundantStore
�������ܣ��洢IBP1ģ��Ĳ���������������
���÷�ʽ�������E2PROM���ݵ�д�����е���
���ò�������
***********************************************************************************/
VOID IbpRedundantStore(VOID);


/***********************************************************************************
������	  FhrRedundantStore
�������ܣ��洢IBP1ģ��Ĳ���������������
���÷�ʽ�������E2PROM���ݵ�д�����е���
���ò�������
***********************************************************************************/
#if _ENB_FHR
VOID  FhrRedundantStore (VOID);
#endif


/***********************************************************************************
������	  Set_Module_Alarm_OnLoad( INT16 moduleid )
�������ܣ���ģ��������������������
���÷�ʽ����ģ��������
���ò�����
		  moduleid:
			��ʾ ECG, SPO2, NIBP, TEMP, FHR��ģ��
����˵����RR�����˴�������ECGģ����
***********************************************************************************/
VOID Set_Module_Alarm_OnLoad( INT16 moduleid );

/***********************************************************************************
������	  Set_Module_Alarm_OnUnLoad( INT16 moduleid )
�������ܣ���ģ��������������������
���÷�ʽ����ģ��ж�����
���ò�����
		  moduleid:
			��ʾ ECG, SPO2, NIBP, TEMP, FHR��ģ��
����˵����RR�����˴�������ECGģ����
***********************************************************************************/
VOID Set_Module_Alarm_OnUnLoad( INT16 moduleid );

/**********************************************************************************
������	  Para_Alarm_Judge_Int()
�������ܣ���ģ�����Ͳ������б����ж�
���÷�ʽ����1s�жϴ���Para_Alarm_Judge�����е���
���ò�����
		  paraid:		��������
		  alarm:		�Ƿ񱨾��ж�
		  high:			��������
		  low:			��������
		  level:		��������
		  paravalue:	����ֵ
���أ�
		  TRUE			������ȷ
		  FALSE			���ش���

***********************************************************************************/
STATUS Para_Alarm_Judge_Int(INT16 paraid, INT16 high, INT16 low, INT16 paravalue);

/**********************************************************************************
������	  Para_Alarm_Judge_Float()
�������ܣ���ģ�鸡���Ͳ������б����ж�
���÷�ʽ����1s�жϴ���Para_Alarm_Judge�����е���
���ò�����
		  paraid:		��������
		  alarm:		�Ƿ񱨾��ж�
		  high:			��������(����)
		  low:			��������(����)
		  level:		��������
		  paravalue:	����ֵ(����)
���أ�
		  TRUE			������ȷ
		  FALSE			���ش���

***********************************************************************************/
STATUS Para_Alarm_Judge_Float(INT16 paraid, FLOAT high, FLOAT low, FLOAT paravalue);

/**********************************************************************************
������	  Para_Alarm_Judge()
�������ܣ���ģ��������б����ж�
���÷�ʽ����1s�ж��н���
���ò�������
���أ�
		  TRUE			������ȷ
		  FALSE			���ش���
***********************************************************************************/
STATUS Para_Alarm_Judge(VOID);


/**********************************************************************************
������	InitUserConfig
�������ܣ���ʼ��ϵͳ���ã��ж�ϵͳ�Ƿ�Ϊ��һ�����У�EEPROM��û�б�־����
		  ����ǣ�����3�ֳ���ȱʡ����Ϊ��Ӧ���û�ȱʡ���ã���ʼ����ǰ����
		  Ϊ����ȱʡ��������
���÷�ʽ��ϵͳ��ʼ��ʱ����һ��
���ò�����force_init -- �Ƿ�ǿ�г�ʼ���������ö����ж�ϵͳ�Ƿ��Ѿ���ʼ��
���أ�
		  TRUE	  ϵͳ�ǵ�һ������
		  FALSE		ϵͳ���ǵ�һ������
***********************************************************************************/
BOOL InitUserConfig( BOOL force_init );

/**********************************************************************************
������	InitConfigWhoHasNoDefaultValue
�������ܣ���ʼ��û��ȱʡֵ��ϵͳ����
���÷�ʽ����InitConfig�е���
���ò�������
���أ�	��
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
 **  ��gOnOff����ʱ,��Ҫָ������ĳ���.�����ⲿ�ڵ�������ʱ,ʹ��TABLESIZE(gOnOff),�����.
 **  �������borland������������.
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

