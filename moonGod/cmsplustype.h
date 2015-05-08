
#ifndef	CMSPLUSTYPE_H
#define	CMSPLUSTYPE_H
	
typedef short WCHAR;


	typedef struct  
	{
		unsigned char		iSize;
		short				iIsoPoint;
		short				iStPoint;
		short				iCalLead;
	}__attribute__ ((packed, aligned(1))) ECG_ST_SETTING_STRU;
	
	typedef struct 
	{
		unsigned char	   iWaveChannel;
		unsigned char	   iWaveGain;
	}__attribute__ ((packed, aligned(1))) STU_WAVE_GAIN;
	
	typedef struct 
	{
		unsigned char	   iWaveChannel;
		unsigned char	   iWaveFilter;
	}__attribute__ ((packed, aligned(1))) STU_WAVE_FILTER;


	
	typedef struct
	{
		UCHAR module_net_value;
		UCHAR module_ame;
	}__attribute__ ((packed, aligned(1))) MODULE_NAME_TO_NET_VALUE;

	typedef struct
	{
		UCHAR para_name_net_value;
		UCHAR para_name;
	}__attribute__ ((packed, aligned(1))) PARA_NAME_TO_NET_VALUE;
	
	typedef struct 
	{
		UCHAR wave_name_net_value;
		UCHAR wave_name;
	}__attribute__ ((packed, aligned(1))) WAVE_NAME_TO_NET_VALUE;

	typedef struct
	{
		UCHAR para_alarm_type;
		UCHAR para_name;
	}__attribute__ ((packed, aligned(1))) PARA_NAME_TO_ALARM_TYPE;

	typedef struct
	{
		UCHAR alarm_level_net_value;
		UCHAR alarm_level;
	}__attribute__ ((packed, aligned(1))) ALARM_LEVEL_TO_NET_VALUE;

	typedef enum 
	{
		//设备基本信息相关指令
		DEVICE_BASE_INFO								 = 1,
		DEVICE_UNIT_INUSE								= 2,
		DEVICE_MODULE_SWITCH_STATUS					  = 3,
		DEVICE_MODULE_INFO							   = 4,
		DEVICE_GENERAL_SETTING						   = 5,
		DEVICE_SYSTEM_TIME							   = 6,
		DEVICE_RECENT_EVENTS							 = 7,
		DEVICE_RECORD_SETTING							= 8,
		DEVICE_RECORD_STATUS							 = 9,
		DEVICE_RECORD_COMMAND							= 10,
		MODULE_LOAD_EVENTS							   = 11,
		MODULE_UNLOAD_EVENTS							 = 12,
		DEFAULT_DATA_REQUEST							 = 13,
		DEVICE_CMS_NAME								  = 14,

		//报警相关指令
		PARA_ALARM_LIMIT_SETTING						 = 51,
		ALARM_GENERAL_SETTING							= 53,
		CURRENT_PARA_ALARM_LIST						  = 54,
		TECH_ALARM_LEVEL_SETTING						 = 55,
		CURRENT_TECH_ALARM_LIST						  = 56,
		PARA_ALARM_RECORD_SETTING						= 57,
		PARA_ALARM_LEVEL_SETTING						 = 58,
		PARA_ALARM_LIMIT_ADJUST_RANGE					= 59,
		PARA_ALARM_SWITCH								= 60,

		//病人管理相关指令
		PATIENT_ONLINE_NOTIFY							= 101,
		VIEW_OTHER_NOTIFY								= 102,
		PATIENT_INFORMATION							  = 103,
		ADMIT_PATIENT									= 104,
		DISCHARGE_PATIENT								= 105,
		TCP_KEEP_PACKET								  = 106,

		//波形相关指令
		WAVE_GENERAL_SETTING							 = 151,
		WAVE_SPEED_SETTING							   = 152,
		WAVE_COLOR_SETTING							   = 153,
		MONITOR_DISPLAY_WAVE_LIST						= 154,
		TRANSMIT_REALTIME_WAVE_DATA_SWITCH			   = 156,
		REALTIME_WAVE_DATA							   = 157,
		WAVE_DATA_RANGE_SETTING						  = 158,
		WAVE_NAME_SETTING								= 159,

		//参数相关指令
		PARA_VIRTUAL_VALUE_LIMIT						 = 201,
		TRANSMIT_REALTIME_PARA_DATA_SWITCH			   = 203,
		REALTIME_PARA_DATA							   = 204,

		//心电模块相关指令
		ECG_GENERAL_SETTING							  = 251,
		ECG_ST_SETTING								   = 252,
		ECG_WAVE_GAIN									= 253,
		ECG_PACE_REALTIME_DATA						   = 254,
		ECG_MODULE_COMMAND							   = 255,
		ECG_WAVE_FILTER								  = 256,

		//血氧模块相关指令
		SPO2_GENERAL_SETTING							 = 301,


		//IBP模块相关指令
		IBP_GENERAL_SETTING							  = 401,
		//		IBP_CHANNEL_SETTING							  = 402,
		IBP_COMMAND_ZERO								 = 403,
		IBP_COMMAND_CALIBRATE							= 404,
		IBP_WAVE_AMP_ADJUST_MODE						 = 405,
		IBP_WAVE_SCALE								   = 406,
		IBP_WAVE_PRESSURE_TYPE						   = 407,
		IBP_EXPAND_PRESSURE							  = 408,
		IBP_WAVE_DATA_PARA							   = 402,
		//呼吸模块相关指令
		RESP_GENERAL_SETTING							 = 451,

		//NIBP模块相关指令
		NIBP_GENERAL_SETTING							 = 501,
		NIBP_MEASUREMENT_COMMAND						 = 502,
		NIBP_PARA_DATA								   = 503,


	}__attribute__ ((packed, aligned(1))) PACKET_CMD_ID;
	
	typedef enum 
	{
		//设备基本信息相关字段

		DEVICE_BASE_INFO_DEVICE_ID					   = 1,
		DEVICE_BASE_INFO_SYSTEM_SOFTWARE_ID			  = 2,
		DEVICE_BASE_INFO_MANUFACTURE_ID				  = 3,
		DEVICE_BASE_INFO_DEVICE_PART_NO				  = 4,
		DEVICE_BASE_INFO_DEVICE_SERIAL_NO				= 5,
		DEVICE_BASE_INFO_SOFTWARE_VERSION				= 6,

		DEVICE_UNIT_PARAS_WHICH_REQUIRED				 = 11,
		DEVICE_UNIT_SIZEOF_DEVICE_UNIT_STRUCT			= 15,
		DEVICE_UNIT_ARRAY								= 16,

		MODULE_SWITCH_MODULES_WHICH_REQUIRED			 = 21,
		MODULE_SWITCH_SIZEOF_MODULE_SWITCH_STRUCT		= 25,
		MODULE_SWITCH_ARRAY							  = 26,

		MODULE_INFO_MODULES_WHICH_REQUIRED			   = 30,
		MODULE_INFO_SIZEOF_MODULE_INFO_STRUCT			= 35,
		MODULE_INFO_ARRAY								= 36,

		DEVICE_SETTING_SETTINGS_WHICH_REQUIRED		   = 41,
		DEVICE_SETTING_SCREEN_TYPE					   = 45,
		DEVICE_SETTING_DISPLAY_FACE					  = 46,
		DEVICE_SETTING_LANGUAGE_TYPE					 = 47,
		DEVICE_SETTING_ALARM_LIMIT_DISPLAY_SWITCH		= 48,
		DEVICE_SETTING_HELP_DISPLAY_SWITCH			   = 49,
		DEVICE_SETTING_IN_DEMO_STATUS					= 50,
		DEVICE_SETTING_BATTERY_STATUS					= 54,
		DEVICE_SETTING_BATTERY_TYPE					  = 55,
		DEVICE_SETTING_BATTERY_CHARGE_PERCENT			= 56,
		DEVICE_SETTING_NETWORK_CONNECT_TYPE			  = 57,
		DEVICE_SETTING_KEYBOARD_VOLUME				   = 58,
		DEVICE_SETTING_TEMP_SENSOR_TYPE				  = 63,
		DEVICE_SETTING_ARR_DELAY						 = 64,
		DEVICE_SETTING_STRING_TRANSFER_TYPE			  = 65,
		DEVICE_SETTING_CODE_PAGE						 = 66,		

		DEVICE_SETTING_SYSTEM_TIME_STRUCT				= 81,
		DEVICE_SETTING_SIZE_OF_EVENTS_STRUCT			 = 85,
		DEVICE_SETTING_EVENTS_ARRAY					  = 86,

		DEVICE_SETTING_REALTIME_RECORD_TIME_LEN		  = 90,
		DEVICE_SETTING_REALTIME_RECORD_INTERVAL		  = 91,
		DEVICE_SETTING_RECORD_SPEED					  = 92,
		DEVICE_SETTING_RECORD_GRID_SWITCH				= 93,
		DEVICE_SETTING_RECORD_WAVE_ARRAY				 = 94,

		DEVICE_SETTING_RECORD_CONTROL_COMMAND			= 105,

		DEVICE_SETTING_MODULE_LOAD_LIST				  = 110,

		DEVICE_SETTING_MODULE_UNLOAD_LIST				= 115,

		DEVICE_SETTING_DEFAULT_DATA_REQUEST_MODULE_LIST  = 120,
		DEVICE_SETTING_CMS_NAME						  = 125,

		//报警相关字段
		PARAS_COUNT_WHICH_REQUIRED_ALARM_LIMIT		   = 200,
		PARAS_ARRAY_WHICH_REQUIRED_ALARM_LIMIT		   = 201,
		ALARM_SIZEOF_ALARM_LIMIT_STRUCT				  = 205,
		ALARM_LIMIT_ARRAY								= 206,

		ALARM_SETTINGS_WHICH_REQUERIED				   = 220,
		ALAMR_LATCH_SWITCH							   = 225,
		ALARM_STORAGE_TIME							   = 226,
		ALARM_SOUND_SWITCH							   = 227,
		ALARM_MUTE_SWITCH								= 228,
		ALARM_PAUSE_TIME								 = 229,
		ALARM_PAUSE_SWITCH							   = 230,
		ALARM_VOLUME_LEVEL							   = 231,
		ALAMR_TRANSFER_SWITCH							= 232,

		ALARM_SIZEOF_PARA_ALARM_INFO_STRUCT			  = 245,
		CURRENT_PARA_ALARM_ARRAY						 = 246,

		TECH_ALARM_COUNT_WHICH_REQUERIED_LEVEL		   = 250,
		TECH_ALARM_ARRAY_WHICH_REQUERIED_LEVEL		   = 251,
		ALARM_SIZEOF_TECH_ALARM_LEVEL_STRUCT			 = 255,
		TECH_ALARM_LEVEL_ARRAY						   = 256,

		ALARM_SIZEOF_TECH_ALARM_INFO_STRUCT			  = 260,
		CURRENT_TECH_ALARM_ARRAY						 = 261,

		ALARMS_COUNT_WHICH_REQUIRED_RECORD_SETTINGS	  = 265,
		ALARMS_ARRAY_WHICH_REQUIRED_RECORD_SETTINGS	  = 266,
		ALARM_SIZEOF_ALARM_RECORD_SETTING_STRUCT		 = 270,
		ALARM_RECORD_SETTING_ARRAY					   = 271,

		PARA_ALARM_COUNT_WHICH_REQUERIED_LEVEL		   = 275,
		PARA_ALARM_ARRAY_WHICH_REQUERIED_LEVEL		   = 276,
		ALARM_SIZEOF_PARA_ALARM_LEVEL_STRUCT			 = 280,
		PARA_ALARM_LEVEL_ARRAY						   = 281,

		PARA_COUNT_WHICH_QUERIED_ALARM_LIMIT_ADJUST_LIMIT		  = 285,
		PARA_ARRAY_WHICH_QUERIED_ALARM_LIMIT_ADJUST_LIMIT		  = 286,
		ALARM_SIZEOF_ALARM_LIMIT_ADJUST_LIMIT_STRUCT			   = 290,
		ALARM_LIMIT_ADJUST_LIMIT_ARRAY							 = 291,
		
		ALARM_COUNT_WHICH_QUERIED_ALARM_SWITCH					 = 295,
		ALARM_ARRAY_WHICH_QUERIED_ALARM_SWITCH					 = 296,
		ALARM_SIZEOF_ALARM_SWITCH_STRUCT						   = 300,
		ALARM_SWITCH_ARRAY										 = 301,

		//病人管理相关字段
		PATIENT_ONLINE_NOTIFY_MONITOR_IP						   = 360,
		PATIENT_ONLINE_NOTIFY_FLAG_HAVE_ADMITTED_PATIENT		   = 361,
		PATIENT_ONLINE_NOTIFY_FLAG_HAVE_ADMITTED_BY_CMS			= 362,
		PATIENT_ONLINE_NOTIFY_PATIENT_GUID						 = 363,
		PATIENT_ONLINE_NOTIFY_PATIENT_FIRST_NAME				   = 364,
		PATIENT_ONLINE_NOTIFY_PATIENT_LAST_NAME					= 365,
		PATIENT_ONLINE_NOTIFY_PATIENT_MEDICAL_NO				   = 366,
		PATIENT_ONLINE_NOTIFY_PATIENT_OFFICE					   = 367,
		PATIENT_ONLINE_NOTIFY_PATIENT_BEDNO						= 368,
		PATIENT_ONLINE_NOTIFY_CMS_IP							   = 369,
		PATIENT_ONLINE_NOTIFY_MONITOR_NAME						 = 370,
		PATIENT_ONLINE_NOTIFY_CMS_NAME							 = 371,

		VIEWOTHER_NOTIFY_REMOTE_IP								 = 380,
		VIEWOTHER_NOTIFY_LOCAL_IP								  = 381,
		VIEWOTHER_NOTIFY_COMMAND_FLAG							  = 382,

		PATIENT_INFO_LANGUAGE_TYPE								   = 384,
		PATIENT_INFO_PATIENT_GUID								  = 385,
		PATIENT_INFO_PATIENT_FRIST_NAME							= 386,
		PATIENT_INFO_PATIENT_LAST_NAME							 = 387,
		PATIENT_INFO_PATIENT_MEDICAL_NO							= 388,
		PATIENT_INFO_PATIENT_OFFICE								= 389,
		PATIENT_INFO_PATIENT_BEDNO								 = 390,
		PATIENT_INFO_PATIENT_TYPE								  = 391,
		PATIENT_INFO_PATIENT_PACE_SWITCH						   = 392,
		PATIENT_INFO_PATIENT_WEIGHT								= 393,
		PATIENT_INFO_PATIENT_HEIGHT								= 394,
		PATIENT_INFO_PATIENT_BIRTH_DATE							= 395,
		PATIENT_INFO_PATIENT_SEX								   = 396,
		PATIENT_INFO_PATIENT_BLOOD								 = 397,
		PATIENT_INFO_DOCTOR_FIRST_NAME							 = 398,
		PATIENT_INFO_DOCTOR_LAST_NAME							  = 399,
		PATIENT_INFO_PATIENT_ADMIT_DATE							= 400,
		PATIENT_INFO_PATIENT_ADDRESS							   = 401,
		PATIENT_INFO_PATIENT_ZIP								   = 402,
		PATIENT_INFO_PATIENT_TELEPHONE							 = 403,

		//波形相关字段
		WAVE_GENERAL_SETTINGS_WHICH_QUERIED						= 1300,
		WAVE_WAVE_DRAW_TYPE										= 1305,
		WAVE_WAVE_SCAN_TYPE										= 1306,

		WAVE_COUNT_WHICH_REQUERIED_SPEED						   = 1310,
		WAVE_ARRAY_WHICH_REQUERIED_SPEED						   = 1311,
		WAVE_SIZEOF_WAVE_SPEED_STRUCT							  = 1315,
		WAVE_SPEED_ARRAY										   = 1316,

		WAVE_COUNT_WHICH_REQUERIED_COLOR						   = 1320,
		WAVE_ARRAY_WHICH_REQUERIED_COLOR						   = 1321,
		WAVE_SIZEOF_WAVE_COLOR_STRUCT							  = 1325,
		WAVE_COLOR_ARRAY										   = 1326,

		WAVE_ARRAY_MONITOR_DISPLAYED							   = 1330,

		WAVE_COUNT_WHICH_REQUERIED_NAME							= 1370,
		WAVE_ARRAY_WHICH_REQUERIED_NAME							= 1371,
		WAVE_SIZEOF_WAVE_NAME_STRUCT							   = 1375,
		WAVE_NAME_ARRAY											= 1376,

		WAVE_COUNT_WHICH_REQUERIED_REALTIME_SWITCH				 = 1340,
		WAVE_ARRAY_WHICH_REQUERIED_REALTIME_SWITCH				 = 1341,
		WAVE_SIZEOF_WAVE_REALTIME_SWITCH_STRUCT					= 1345,
		WAVE_REALTIME_SWITCH_ARRAY								 = 1346,

		WAVE_COUNT_WHICH_REQUERIED_REALTIME_DATA				   = 1350,
		WAVE_ARRAY_WHICH_REQUERIED_REALTIME_DATA				   = 1351,
		WAVE_REALTIME_DATA_ARRAY								   = 1355,

		WAVE_COUNT_WHICH_REQUERIED_VALUE_LIMIT					 = 1360,
		WAVE_ARRAY_WHICH_REQUERIED_VALUE_LIMIT					 = 1361,
		WAVE_VALUE_LIMIT_ARRAY									 = 1365,

		//参数相关字段
		PATIENT_TYPE_WHICH_REQUERIED_PRAR_VIRTUAL_VALUE_LIMIT	  = 550,
		PARA_COUNT_WHICH_REQUERIED_PRAR_VIRTUAL_VALUE_LIMIT		= 551,
		PARA_ARRAY_WHICH_REQUERIED_PRAR_VIRTUAL_VALUE_LIMIT		= 552,
		PATIENT_TYPE_OF_VIRTUAL_VALUE_LIMIT						= 555,
		PARA_SIZEOF_PRAR_VIRTUAL_VALUE_LIMIT_STRUCT				= 556,
		PRAR_VIRTUAL_VALUE_LIMIT_ARRAY							 = 557,

		PARA_COUNT_WHICH_REQUERIED_REALTIME_SWITCH				 = 570,
		PARA_ARRAY_WHICH_REQUERIED_REALTIME_SWITCH				 = 571,
		PARA_SIZEOF_PARA_REALTIME_SWITCH_STRUCT					= 575,
		PARA_REALTIME_SWITCH_ARRAY								 = 576,

		PARA_COUNT_WHICH_REQUERIED_REALTIME_DATA				   = 580,
		PARA_ARRAY_WHICH_REQUERIED_REALTIME_DATA				   = 581,
		PARA_SIZEOF_PARA_REALTIME_DATA_STRUCT					  = 585,
		PARA_REALTIME_DATA_ARRAY								   = 586,

		//心电模块相关字段
		ECG_SETTINGS_WHICH_REQUERIED							   = 680,
		ECG_ARR_CALCULATE_SWITCH								   = 685,
		ECG_ARR_ALARM_STORAGE_TIME								 = 686,
		ECG_HR_RESOURCE											= 687,
		ECG_HR_CALCULATE_CHANNEL								   = 688,
		ECG_LEAD_TYPE											  = 689,
		ECG_HR_VOLUME_LEVEL										= 690,
		ECG_TRAP_WAVE_FREQUENCY									= 691,
		ECG_PACE_SWITCH											= 692,
		ECG_CALIBRATE_STATUS_SWITCH								= 693,
		ECG_ARR_RELEARN_SWITCH									 = 694,
		ECG_DISPLAY_MODE										   = 695,
		ECG_CASCADE_SWITCH										 = 696,
		ECG_WAVE_NAME_RULE										 = 698,
		ECG_ST_CALCULATE_SWITCH									= 699,
		ECG_ST_RELEARN_SWITCH									  = 700,
		
		ECG_ST_SETTING_FIELD									   = 710,

		ECG_CHANNEL_WHICH_REQUERIED_GAIN						   = 720,
		ECG_SIZEOF_WAVE_GAIN_STRUCT								= 725,
		ECG_WAVE_GAIN_ARRAY										= 726,

		ECG_PACE_DATA_WAVE_SAMPLE								  = 730,
		ECG_PACE_DATA											  = 731,

		ECG_MODULE_COMMAND_FIELD								   = 735,

		ECG_CHANNEL_WHICH_REQUERIED_FILTER						 = 740,
		ECG_SIZEOF_WAVE_FILTER_STRUCT							  = 745,
		ECG_WAVE_FILTER_ARRAY									  = 746,

		//血氧模块相关字段
		SPO2_SETTINGS_WHICH_REQUERIED							  = 835,
		SPO2_PR_VOLUME_LEVEL									   = 840,
		SPO2_AVERAGE_TIME										  = 841,
		SPO2_SENSITIVITY_MODE									  = 842,
		SPO2_NIBP_SIMULTANEOUS_SWITCH							  = 843,

		//IBP模块相关字段
		IBP_SETTINGS_WHICH_REQUERIED							   = 1001,
		IBP_WAVE_FILTER_TYPE									   = 1005,
		IBP_ZERO_STATUS_SWITCH									 = 1006,
		IBP_CALIBRATE_STATUS_SWITCH								= 1007,

		IBP_CHANNELS_WHICH_REQUERIED_PRESSURE_TYPE				 = 1011,
		IBP_SIZEOF_PRESSURE_TYPE_STRUCT							= 1015,
		IBP_PRESSURE_TYPE_ARRAY									= 1016,

		IBP_CHANNELS_WHICH_REQUERIED_ZERO						  = 1021,

		IBP_SIZEOF_CALIBRATE_STRUCT								= 1025,
		IBP_CALBRAITE_ARRAY										= 1026,

		IBP_CHANNELS_WHICH_REQUERIED_AMP_ADJUST_MODE			   = 1031,
		IBP_SIZEOF_WAVE_AMP_ADJUST_MODE_STRUCT					 = 1035,
		IBP_WAVE_AMP_ADJUST_MODE_ARRAY							 = 1036,

		IBP_CHANNELS_WHICH_REQUERIED_WAVE_SCALE					= 1041,
		IBP_SIZEOF_WAVE_SCALE_STRUCT							   = 1045,
		IBP_WAVE_SCALE_ARRAY									   = 1046,

		IBP_PARAS_WHICH_REQUERIED_ALARM_LIMIT					  = 1370,
		IBP_SIZEOF_PARA_ALARM_LIMIT_STRUCT						 = 1375,
		IBP_PARA_ALARM_LIMIT_ARRAY								 = 1376,

		IBP_CHANNELS_WHICH_REQUERIED_WAVE_DATA_PARA				= 1380,
		IBP_SIZEOF_WAVE_DATA_PARA_STRUCT						   = 1385,
		IBP_WAVE_DATA_PARA_ARRAY								   = 1386,

		IBP_SIZEOF_EXPAND_PRESSURE_STRUCT						  = 1395,
		IBP_EXPAND_PRESSURE_ARRAY								  = 1396,

		//呼吸模块相关字段
		RESP_SETTINGS_WHICH_REQUERIED							   = 1050,
		RESP_APNEA_ALARM_TIME									   = 1055,
		RESP_WAVE_AMPLITUDE										 = 1056,
		RESP_HOLD_TYPE_FIELD										= 1057,
		RESP_UPPER_SCALE											= 1058,
		RESP_LOWER_SCALE											= 1059,

		//NIBP模块相关字段
		NIBP_SETTINGS_WHICH_REQUERIED							   = 1100,
		NIBP_DISPLAY_MODE										   = 1105,								
		NIBP_MEASUREMENT_INTERVAL_TIME							  = 1106,								
		NIBP_MEASUREMENT_STATUS									 = 1107, 

		NIBP_MEASUREMENT_COMMAND_FIELD							  = 1115,

		NIBP_SIZEOF_MEASUREMENT_DATA_STRUCT						 = 1120,
		NIBP_MEASUREMENT_DATA									   = 1121,

	}__attribute__ ((packed, aligned(1))) PACKET_FIELD_ID;


	typedef struct
	{
		UCHAR		pMonitorAddress[6];
		BOOL		AdmittedPatient;
		BOOL		AdmittedByCenter;
		CHAR		pPatientGUID[30];
		CHAR		pPatientFirstName[30];
		CHAR		pPatientLastName[30];
		CHAR		pPatientID[20];
		CHAR		pDepartment[30];
		UCHAR		BedNo;
		UCHAR		pCenterAddress[6];
	}__attribute__ ((packed, aligned(1))) MONITOR_BASE_INFO;
	
	//床边机在线通知消息数据结构
	typedef struct 
	{
		long				   lMask;				//掩码，表示后面的哪些数据有效。
		unsigned char		   czBedIP[6];			 //床边机的IP地址	   0x0001
		unsigned char		   czBedName[32];		 //床边机的名字		0x0400
		unsigned char		   bHaveAdmittedPatient; //是否接收了病人	   0x0002
		unsigned char		   bHaveAdmittedByCMS;	 //是否保存有接收中央站的信息 0x0004
		unsigned char		   czGUID[32];			 //病人GUID	0x0008
		CHAR				   strFirstName[32];	 //病人的姓	0x0010
		CHAR				   strLastName[32];	  //病人的名	0x0020
		CHAR				   strMedicalNo[32];	 //病历号	   0x0040
		CHAR				   strOffice[32];		 //科室		0x0080
		unsigned char		   iBedNo;				  //床号		0x0100
		unsigned char		   czCMSIP[6];			 //中央站的IP地址	0x0200
		unsigned char		   czCMSName[32];		 //中央站名字   0x0800
		BOOL				   NetcardDroven;
		INT32				   PatientSequenceNumber;
	}__attribute__ ((packed, aligned(1))) STU_PATIENT_ONLINE_NOTIFY, MONITOR_ONLINE_NOTIFY;
 
	typedef struct  
	{
		unsigned char		 iChannel;	//通道号
		short				 iCoefficent;	 //量化系数
		short				 iZeroBase;	   //零基准值
	}__attribute__ ((packed, aligned(1))) STU_IBP_WAVE_DATA_PARA;

	//日期时间结构
	typedef struct 
	{
		unsigned short		  iYear;
		unsigned char		   iMonth;
		unsigned char		   iDay;
		unsigned char		   iHour;
		unsigned char		   iMinute;
		unsigned char		   iSecond;
	}__attribute__ ((packed, aligned(1))) NET_DATE_TIME;
	
	typedef struct  
	{
		unsigned char		   iParaType;
		unsigned char		   iMultiple;
		unsigned char		   iDataType;
		short					  iLowLimit;
		short					  iHighLimit;
		unsigned char		   iLowLimitOn;
		unsigned char		   iHighLimitOn;
	}__attribute__ ((packed, aligned(1))) ALARM_LIMIT;

	typedef enum 
	{
		bed_alarm_storage_record_time_unknown		   = 0,
		bed_alarm_storage_record_time_8s				= 1,
		bed_alarm_storage_record_time_16s			   = 2,
		bed_alarm_storage_record_time_32s			   = 3,
		bed_alarm_storage_record_time_64s			   = 4
	}__attribute__ ((packed, aligned(1))) BED_ALARM_STORAGE_RECORD_TIME;

	typedef struct 
	{
		unsigned char		   iAlarmType;
		unsigned char		   iLevel;
		unsigned char		   iExLevel;
	}__attribute__ ((packed, aligned(1))) PARA_ALARM_INFO;

	typedef struct 
	{
		BYTE iAlarmType;
		BYTE iAlarmOn;
	}__attribute__ ((packed, aligned(1))) ARR_ALARM_SWITCH;

	typedef struct 
	{
		unsigned short		  iAlarmType;
		unsigned char		   iLevel;
	}__attribute__ ((packed, aligned(1))) TECH_ALARM_INFO;
	
	typedef struct  
	{
		unsigned char		  iParaType;
		unsigned char		  iMultiple;
		unsigned char		  iDataType;
		short				  iLowLimitUpper;
		short				  iLowLimitLower;
		short				  iHighLimitUpper;
		short				  iHighLimitLower;
	}__attribute__ ((packed, aligned(1))) STU_PARA_ALARM_LIMIT_ADJUST_RANGE;
	
	typedef struct
	{
		unsigned short		 iYear;
		unsigned char		  iMonth;
		unsigned char		  iDay;
	}__attribute__ ((packed, aligned(1))) STU_DATE;
	
	typedef enum 
	{
		patient_info_type_get_reply	  = 0,
		patient_info_type_set_request	= 1,
		patient_info_type_set_reply	  = 2,
		patient_info_type_notify		 = 3,
		patient_info_type_admit_request  = 4,
		patient_info_type_admit_reply	= 5
	}__attribute__ ((packed, aligned(1))) PATIENT_INFO_TYPE;

	typedef struct 
	{
		unsigned char	  iWaveChannelName;
		unsigned char	  iWaveName;
	}__attribute__ ((packed, aligned(1))) STU_WAVE_NAME;
	
	//波形属性结构
	typedef struct  
	{
		unsigned char				   iWaveChannelName;	  //波形通道号
		unsigned char				   iWaveName;			  //波形名称
		unsigned short				   iSampleRate;		   //采样率
		unsigned char				   iDataType;			  //数据类型
	}__attribute__ ((packed, aligned(1))) WAVE_PROPERTY;
	
	//参数属性结构
	typedef struct  
	{
		unsigned char				   iParaType;	   //参数类型
		unsigned char				   iDataType;	   //数据类型
		unsigned char				   iMultiple;
	}__attribute__ ((packed, aligned(1))) PARA_PROPERTY;

	typedef struct _STU_PARA_VIRTUAL_LIMIT 
	{
		unsigned char	  iParaType;
		unsigned char	  iVirtualLimitType;
		unsigned char	  iMultiple;
		unsigned char	  iDataType;
		short			  iVirtualUpper;
		short			  iVirtualLower;
	}__attribute__ ((packed, aligned(1))) STU_PARA_VIRTUAL_LIMIT;
	
	typedef struct _STU_REALTIME_PARA_DATA
	{
		unsigned char	  iParaType;
		unsigned char	  iMultiple;
		unsigned char	  iDataType;
		short			  iParaData;
	}__attribute__ ((packed, aligned(1))) STU_REALTIME_PARA_DATA;

	typedef struct _STU_ECG_WAVE_GAIN
	{
		unsigned char	  iWaveChannel;
		unsigned char	  iWaveName;
		unsigned char	  iWaveGain;
	}__attribute__ ((packed, aligned(1))) STU_ECG_WAVE_GAIN;
	
	typedef struct _STU_NET_PARA_DATA 
	{
		unsigned char	  iMultiple;
		unsigned char	  iDataType;
		short			  iParaData;
	}__attribute__ ((packed, aligned(1))) STU_NET_PARA_DATA;

	typedef struct _STU_IBP_WAVE_AMP_ADJUST_MODE 
	{
		unsigned char	  iChannel;
		unsigned char	  iAdjustMode;
	}__attribute__ ((packed, aligned(1))) STU_IBP_WAVE_AMP_ADJUST_MODE;

	typedef struct _STU_IBP_WAVE_SCALE 
	{
		unsigned char	  iChannel;
		unsigned short	 iUpper;
		unsigned short	 iMiddle;
		unsigned short	 iLower;
	}__attribute__ ((packed, aligned(1))) STU_IBP_WAVE_SCALE;

	typedef struct _IBP_WAVE_GAIN
	{
		UCHAR iModule;
		UCHAR iAmpMode;
	}__attribute__ ((packed, aligned(1))) IBP_WAVE_GAIN;
	
	typedef struct _STU_IBP_WAVE_PRESSURE_TYPE 
	{
		unsigned char	  iChannel;
		unsigned char	  iPressureType;
	   // unsigned char	  iExpandType;
	}__attribute__ ((packed, aligned(1))) STU_IBP_WAVE_PRESSURE_TYPE;

	typedef struct
	{
		unsigned char	  iChannel;
		unsigned short	 iCalibrate;
	}__attribute__ ((packed, aligned(1))) STU_IBP_CALIBRATE;
	
	typedef struct _STU_NIBP_MEASURE_DATA
	{
		NET_DATE_TIME		   dtMeasureDateTime;
		unsigned char	   iMultiple;
		unsigned char	   iDataType;
		short			   iNIBP_S;
		short			   iNIBP_M;
		short			   iNIBP_D;
	}__attribute__ ((packed, aligned(1))) STU_NIBP_MEASURE_DATA;



enum CONFIG_VERSION
{
	config_express,
	config_super,
	config_standard,
	config_FDA
};

enum MACHINE_TYPE
{
	machine_unknown,
	machine_mec1000,
	machine_mec2000,
	machine_mec509B,
	machine_pm5000,
	machine_pm6000,
	machine_pm7000,
	machine_pm8000,
	machine_pm9000super,
	machine_pm9000express,
	machine_pm9000outport,
	machine_pm9300,
	machine_pm9303,
	machine_102b
};

enum PROTOCOL_TYPE
{
	protocol_unknown	= 0,
	protocol_hyperiii	=1,
	protocol_m3100		=2,
	protocol_cms		=3,
	protocol_cms2		=4,
	protocol_cmsplus	=5
};

enum SEX_TYPE	
{
	sex_unknown		= 0,
	sex_male		,
	sex_female		
};

enum DISTANCE_UNIT_TYPE	
{
	distance_unit_unknown	= 0,
	distance_unit_cm		,
	distance_unit_inch		
};

enum WEIGHT_UNIT_TYPE	
{
	weight_unit_unknown	= 0,
	weight_unit_kg		,
	weight_unit_lb		
};

enum PATIENT_TYPE	
{
	patient_unknown	= 0,
	patient_adu	,
	patient_ped	,
	patient_neo	
};

enum BLOOD_TYPE
{
	blood_unknown	= 0,
	blood_a			,
	blood_b			,
	blood_ab		,
	blood_o			,
	blood_na		
};

enum WAVE_DRAW_TYPE
{
	waveDraw_a		,
	waveDraw_b		
};

enum WAVE_REFRESH_TYPE
{
	waveRefresh_ClearWrite	,
	waveRefresh_Scroll	
};

enum WAVE_SPEED
{
	waveSpeed_625	,
	waveSpeed_125	,
	waveSpeed_250	,
	waveSpeed_500	
};

 typedef enum
 {
	ECG_SETTING_ARR_ANALYSIS = 0x0001,
	ECG_SETTING_ARR_ALM_STORAGE_TIME = 0x0002,
	ECG_SETTING_HR_SOURCE = 0x0004,
	ECG_SETTING_ANALYSIS_CHANNEL = 0x0008,
	ECG_SETTING_LEAD_TYPE = 0x0010,
	ECG_SETTING_BEAT_VOLUME = 0x0020,
	ECG_SETTING_BAND_FILTER = 0x0040,
	ECG_SETTING_ENABLE_PACEMAKER = 0x0080,
	ECG_SETTING_CALIBRATION = 0x0100,
	ECG_SETTING_ARR_RELEARN = 0x0200,
	ECG_SETTING_ST_RELEARN = 0x0400,
	ECG_SETTING_DISPLAY_MODE = 0x0800,
	ECG_SETTING_CASCADE = 0x1000,
	ECG_SETTING_WAVE_NAME_RULE = 0x4000,
	ECG_SETTING_ST_ANALYSIS = 0x8000,
	ECG_SETTING_ALL = 0xFFFFFFFF
 } ECG_MODULE_GENERAL_SETTING;

 
 typedef enum
 {
	SPO2_SETTING_BEAT_VOLUME = 0x0001,
	SPO2_SETTING_AVERAGE_TIME = 0x0002,
	SPO2_SETTING_SENSITIVITY_MODE = 0x0004,
	SPO2_SETTING_NIBP_SIMUL = 0x0008,
	SPO2_SETTING_MAS_AVERAGE_TIME = 0x0010,
	SPO2_SETTING_ALL = 0xFFFFFFFF
 } SPO2_MODULE_GENERAL_SETTING;


typedef enum
{
	CO_SETTING_CONST = 0x0001,
	CO_SETTING_INJECT_TEMP = 0x0002,
	CO_SETTING_TEMP_SOURCE = 0x0004,
	CO_SETTING_INTERVAL_TIME = 0x0008,
	CO_SETTING_MEASURE_STATUS = 0x0010,
	CO_SETTING_WAVE_DATA_LIMIT = 0x0020,
	CO_SETTING_ALL = 0xFFFFFFFF
} CO_MODULE_GENERAL_SETTING;

typedef enum
{
	RESP_SETTING_APNEA_THRESHOLD = 0x0001,
	RESP_SETTING_WAVE_GAIN = 0x0002,
	RESP_SETTING_CALCULATE_MODE = 0x0004,
	RESP_SETTING_MANUAL_CALC_HIGH_THRESHOLD = 0x0008,
	RESP_SETTING_MANUAL_CALC_LOW_THRESHOLD = 0x0010,
	RESP_SETTING_ALL = 0xFFFFFFFF
} RESP_MODULE_GENERAL_SETTING;

typedef enum
{
	NIBP_SETTING_DISPLAY_MODE = 0x0001,
	NIBP_SETTING_INTERVAL_TIME = 0x0002,
	NIBP_SETTING_MEASURE_STATUS = 0x0004,
	NIBP_SETTING_ALL = 0xFFFFFFFF

} NIBP_MODULE_GENERAL_SETTING;


typedef enum
{
	IBP_SETTING_MODULE_12 = 0x0001,
	IBP_SETTING_FILTER = 0x0100,
	IBP_SETTING_ZERO = 0x0200,
	IBP_SETTING_IN_CALIBRATION = 0x0400,
	IBP_SETTING_ALL = 0xFFFFFFFF
} IBP_MODULE_GENERAL_SETTING;

typedef enum
{
	GENERAL_SETTING_SCREEN_SIZE = 0x0001,
	GENERAL_SETTING_DISPLAY_MODE = 0x0002,
	GENERAL_SETTING_LANGUAGE = 0x0004,
	GENERAL_SETTING_SHOW_ALM_LIMIT = 0x0008,
	GENERAL_SETTING_SHOW_HELP_INFO = 0x0010,
	GENERAL_SETTING_IN_DEMO = 0x0020,
	GENERAL_SETTING_BATTERY_STATE = 0x0200,
	GENERAL_SETTING_BATTERY_TYPE = 0x0400,
	GENERAL_SETTING_BATTERY_CHARGE = 0x0800,
	GENERAL_SETTING_NET_TYPE = 0x1000,
	GENERAL_SETTING_KEY_VOLUME = 0x2000,
	GENERAL_SETTING_URSE_CALL_SIGNAL_TYPE = 0x8000,
	GENERAL_SETTING_NURSE_CALL_ALM_LEVEL = 0x010000,
	GENERAL_SETTING_TEMP_SENSER_TYPE = 0x020000,
	GENERAL_SETTING_ARR_DELAY = 0x040000,
	GENERAL_SETTING_STRING_TRANSFER_TYPE = 0x080000,
	GENERAL_SETTING_CODE_PAGE = 0x100000,
	GENERAL_SETTING_ALL = 0xFFFFFFFF
}	SYSTEM_GENERAL_SETTING;

typedef enum
{
	ALARM_SETTING_LATCH_SWITCH = 0x0001,
	ALARM_SETTING_ALARM_STORAGE_TIME = 0x0002,
	ALARM_SETTING_ALARM_SILENT_SWITCH = 0x0004,
	ALARM_SETTING_ALARM_MUTE_SWITCH = 0x0008,
	ALARM_SETTING_ALARM_PAUSE_TIME = 0x0010,
	ALARM_SETTING_ALARM_PAUSE_SWITCH = 0x0020,
	ALARM_SETTING_ALARM_VOLUME = 0x0040,
	ALARM_SETTING_ALARM_TRNSFER_SWITCH = 0x0080,
	ALARM_SETTING_ALL = 0xFFFFFFFF
}	ALARM_GENERAL_SETTING_ENUM;

#define MSDE_MAXSIZE_PATIENTGUID	28
#define MSDE_MAXSIZE_PERSON_SURNAME	  32
#define MSDE_MAXSIZE_PERSON_NAME		   32
#define MSDE_MAXSIZE_OFFICE				32
#define MSDE_MAXSIZE_BEDNO			 16
#define MSDE_MAXSIZE_MEDICALNO			 32
#define MSDE_MAXSIZE_DIAGNOSIS			256
#define MSDE_MAXSIZE_PHONE				32
#define MSDE_MAXSIZE_ADDRESS			 128
#define MSDE_MAXSIZE_POSTCODE			 16
#define MSDE_MAXSIZE_PATIENT_ADDITION	  256


enum ARR_ALARM_TYPE
{
	arr_alarm_NO			= 0,
	arr_alarm_ASYSTOLE,
	arr_alarm_VFIB_VTAC,
	arr_alarm_R_ON_T,
	arr_alarm_VT_GT_2,
	arr_alarm_COUPLET,
	arr_alarm_PVC,
	arr_alarm_BIGEMINY,
	arr_alarm_TRIGEMINY,
	arr_alarm_TACHY,
	arr_alarm_BRADY,
	arr_alarm_PNC,
	arr_alarm_PNP,
	arr_alarm_MISSED_BEATS
};

enum NETWORK_CONNECT_TYPE
{
   network_connect_type_unknown = 0,
   network_connect_type_wire,
   network_connect_type_wireless,
   network_connect_type_telemetry
};

enum ALARM_LEVEL
{
	alarmlevel_unknwon	=0,
	alarmlevel_high		=1,
	alarmlevel_mid		=2,
	alarmlevel_low		=3,
	alarmlevel_no		=4
};

typedef enum _ALARM_STATUS
{
	alarmstatus_unknown	= 0,
	alarmstatus_no		=1,
	alarmstatus_higher	=2,
	alarmstatus_lower	=3,
	alarmstatus_yes		=4
}ALARM_STATUS;

enum ALARM_LEVEL_EX
{
	alarmlevel_ex_unknown	=0,
	alarmlevel_ex_prompt	=1,
	alarmlevel_ex_priority  =2,
	alarmlevel_ex_no		=3
};

enum TECH_ALARM_LEVEL
{
	techalarmlevel_unknown=-1,
	techalarmlevel_invalid,
	techalarmlevel_high,
	techalarmlevel_mid,
	techalarmlevel_low,
	techalarmlevel_leedLost
};

enum SWITCH_TYPE
{
	switch_off	 = 0,
	switch_on	  = 1,
	switch_unknown = 2
};

enum TECH_ALARM_STATUS
{
	techalarmstatus_unknown = 0,
	techalarmstatus_off,
	techalarmstatus_normal,
	techalarmstatus_silence,
	techalarmstatus_pause
};

typedef enum
{	wave_name_Unknown=0,
	wave_name_ECG_CH1,
	wave_name_ECG_CH2,
	wave_name_ECG_CH3,
	wave_name_ECG_CH4,
	wave_name_ECG_CH5,
	wave_name_ECG_CH6,
	wave_name_ECG_CH7,
	wave_name_ECG_CH8,
	wave_name_ECG_CH9,
	wave_name_ECG_CH10,
	wave_name_ECG_CH11,
	wave_name_ECG_CH12,
	wave_name_ECG_i,wave_name_ECG_ii,wave_name_ECG_iii,wave_name_ECG_aVR,wave_name_ECG_aVL,wave_name_ECG_aVF,
	wave_name_ECG_V1,wave_name_ECG_V2,wave_name_ECG_V3,wave_name_ECG_V4,wave_name_ECG_V5,wave_name_ECG_V6,
	wave_name_ECG_CAL,
	wave_name_RESP,
	wave_name_PLETH,
	wave_name_IBP_CH1,
	wave_name_IBP_CH2,
	wave_name_IBP_CH3,
	wave_name_IBP_CH4,
	wave_name_IBP_ART,wave_name_IBP_PA,wave_name_IBP_CVP,wave_name_IBP_RAP,wave_name_IBP_LAP,wave_name_IBP_ICP,wave_name_IBP_P1,wave_name_IBP_P2,wave_name_IBP_P3,wave_name_IBP_P4,
	wave_name_IBP_ART2,wave_name_IBP_PA2,wave_name_IBP_CVP2,wave_name_IBP_RAP2,wave_name_IBP_LAP2,wave_name_IBP_ICP2,wave_name_IBP_P12,wave_name_IBP_P22,wave_name_IBP_P32,wave_name_IBP_P42,

	wave_name_GAS_CO2,wave_name_GAS_O2,wave_name_GAS_N2O,wave_name_GAS_AA,wave_name_GAS_HAL,wave_name_GAS_ENF,wave_name_GAS_ISO,wave_name_GAS_SEV,wave_name_GAS_DES,
	wave_name_Last=wave_name_GAS_DES
}WAVE_NAME_TYPE;

typedef enum 
{	
	para_name_Unknown	=0,
	para_name_HR		,
	para_name_ECG_LOST ,
	para_name_PVCs	,
	para_name_ST		,
	para_name_ST1		,
	para_name_ST2		,
	para_name_ST_I		,
	para_name_ST_II	,
	para_name_ST_III	,
	para_name_ST_aVR	,
	para_name_ST_aVL	,
	para_name_ST_aVF	,
	para_name_ST_V1	,
	para_name_ST_V2	,
	para_name_ST_V3	,
	para_name_ST_V4	,
	para_name_ST_V5	,
	para_name_ST_V6	,
	para_name_RR		,
	para_name_RESP_APNEA,
	para_name_RESP_ARTIFACT,
	para_name_SPO2		,
	para_name_PR		,
	para_name_NO_PULSE	,
	para_name_NIBP		,
	para_name_NIBP_S	,
	para_name_NIBP_M	,
	para_name_NIBP_D	,
	para_name_IBP1		,
	para_name_IBP1_M	,
	para_name_IBP1_S	,
	para_name_IBP1_D	,
	para_name_IBP2		,
	para_name_IBP2_M	,
	para_name_IBP2_S	,
	para_name_IBP2_D	,
	para_name_TEMP		,
	para_name_T1		,
	para_name_T2		,
	para_name_Td		,
	para_name_CO		,
	para_name_TI		,
	para_name_CI		,
	para_name_TB		,


	para_name_IBP3		,
	para_name_IBP3_M	,
	para_name_IBP3_S	,
	para_name_IBP3_D	,
	para_name_IBP4		,
	para_name_IBP4_M	,
	para_name_IBP4_S	,
	para_name_IBP4_D	,
	para_name_GAS_CO2	,
	para_name_CO2Et	,
	para_name_CO2Fi	,
	para_name_GAS_O2	,
	para_name_O2Et		,
	para_name_O2Fi		,
	para_name_GAS_N2O	,
	para_name_N2OEt	,
	para_name_N2OFi	,
	para_name_GAS_AA	,
	para_name_AAEt		,
	para_name_AAFi		,
	para_name_GAS_HAL	,
	para_name_HALEt	,
	para_name_HALFi	,
	para_name_GAS_ENF	,
	para_name_ENFEt	,
	para_name_ENFFi	,
	para_name_GAS_ISO	,
	para_name_ISOEt	,
	para_name_ISOFi	,
	para_name_GAS_SEV	,
	para_name_SEVEt	,
	para_name_SEVFi	,
	para_name_GAS_DES	,
	para_name_DESEt	,
	para_name_DESFi	,
	para_name_AgAwRR	,
	para_name_Mac		,
	para_name_GAS_APNEA,
	para_name_Alarm_Pause,
	
	para_name_LAST			=para_name_GAS_APNEA,

	para_name_ARR_First		=200,
	para_name_ASYSTOLE		=para_name_ARR_First,
	para_name_VFIB_VTAC,
	para_name_R_ON_T,
	para_name_VT_GT_2,
	para_name_COUPLET,
	para_name_PVC,
	para_name_BIGEMINY,
	para_name_TRIGEMINY,
	para_name_TACHY,
	para_name_BRADY,
	para_name_PNC,
	para_name_PNP,
	para_name_MISSED_BEATS,
	para_name_ARR_Last		=para_name_MISSED_BEATS
} PARA_NAME_TYPE;

enum GAIN_TYPE
{
	gain_unknown= 0,
	gain_auto,
	gain_x025,
	gain_x05,
	gain_x1,
	gain_x2,
	gain_x4,
};

enum FILTER_TYPE	
{
	filter_unknown= 0,
	filter_diagnostic,
	filter_monitor,
	filter_surgery
};

enum HR_SOURCE_TYPE
{
	hrSource_unknown= 0,
	hrSource_ecg,
	hrSource_spo2,
	hrSource_auto,
	hrSource_both
};

enum HR_CALCULATE_CHANNEL_TYPE
{
	hrCalculateChannel_unknown = 0,
	hrCalculateChannel_auto,
	hrCalculateChannel_CH1,
	hrCalculateChannel_CH2,
	hrCalculateChannel_CH3
};

enum ECG_LEED_TYPE
{
	ecgLeed_unknown= 0,
	ecgLeed_3,
	ecgLeed_5,
	ecgLeed_7,
	ecgLeed_12
};

enum ECG_TRAP_WAVE
{
	ecgtrapwave_unknown = 0,
	ecgtrapwave_50,
	ecgtrapwave_60
};




enum ECG_NAME_RULE
{
	ecgnamerule_unknown = 0,
	ecgnamerule_AHA,
	ecgnamerule_EURO
};

enum HR_CHANNEL_TYPE
{
	hrChannel_unknown= 0,
	hrChannel_1,
	hrChannel_2,
	hrChannel_Both
};

enum SPO2_TYPE
{
	spo2_unknown= 0,
	spo2_Mindray,
	spo2_Nellcor,
	spo2_Masimo
};

enum SPO2_SENSITIVITY_MODE
{
	spo2_sensitivity_mode_unknown = 0,
	spo2_sensitivity_mode_standard,
	spo2_sensitivity_mode_high
};

enum RESP_HOLD_TYPE
{
	respHold_unknown= 0,
	respHold_Auto,
	respHold_Manual
};

enum WAVE_AMPLITUDE
{
	wave_amplitude_unknown = 0,
	wave_amplitude_025,
	wave_amplitude_05,
	wave_amplitude_1,
	wave_amplitude_2,
	wave_amplitude_3,
	wave_amplitude_4,
	wave_amplitude_5
};

typedef enum
{
	nibp_measure_interval_time_unknown = 0,
	nibp_measure_interval_time_manual,
	nibp_measure_interval_time_1,
	nibp_measure_interval_time_2,
	nibp_measure_interval_time_3,
	nibp_measure_interval_time_4,
	nibp_measure_interval_time_5,
	nibp_measure_interval_time_10,
	nibp_measure_interval_time_15,
	nibp_measure_interval_time_30,
	nibp_measure_interval_time_60,
	nibp_measure_interval_time_90,
	nibp_measure_interval_time_120,
	nibp_measure_interval_time_180,
	nibp_measure_interval_time_240,
	nibp_measure_interval_time_480
}NIBP_MEASURE_INTERVAL_TIME;

enum NIBP_MEASURE_STATUS
{
	nibp_measure_status_unknown = 0,
	nibp_measure_status_measuring,
	nibp_measure_status_resetting,
	nibp_measure_status_continuingmeasure,
	nibp_measure_status_calibrating,
	nibp_measure_status_pumping
};


enum IBP_AMP_ADJUST_TYPE
{
	ibpAmpAdjust_unknown= 0,
	ibpAmpAdjust_Auto,
	ibpAmpAdjust_Manual
};

enum IBP_FILTER_TYPE
{
	ibpFilter_unknown= 0,
	ibpFilter_Normal,
	ibpFilter_Smooth,
	ibpFilter_NoFilter
};

enum IBP_WAVE_PRESSURE_TYPE
{
	ibpWavePressure_unknown = 0,
	ibpWavePressure_ART	 = 1,
	ibpWavePressure_PA	  = 2,
	ibpWavePressure_CVP	 = 3,
	ibpWavePressure_RAP	 = 4,
	ibpWavePressure_LAP	 = 5,
	ibpWavePressure_ICP	 = 6,
	ibpWavePressure_P1	  = 7,
	ibpWavePressure_P2	  = 8,
};

enum IBP_EXPAND_PRESSURE_TYPE
{
	ibpExpandPressure_unknown= 0,
	ibpExpandPressure_SysMeanDia,
	ibpExpandPressure_Mean
};

enum MODULE_STATUS
{
	module_unknown= 0,
	module_Measure,
	module_StandBy
};

enum TEMPRATURE_UNIT
{
	temprature_unit_Unknown= 0,
	temprature_unit_C,
	temprature_unit_F
};

enum PRESSURE_UNIT
{
	pressure_unit_Unknown= 0,
	pressure_unit_mmHg,
	pressure_unit_KPa,
	pressure_unit_Percent
};

enum RECORD_STATUS
{
	record_status_idle,
	record_status_pause,
	record_status_recording
};

enum RECORD_SOURCE
{
	record_source_alarmreview,
	record_source_coreview,
	record_source_drug,
	record_source_freeze,
	record_source_Hemod,
	record_source_nibpreview,
	record_source_nibpGraphreview,
	record_source_oxyCRG,
	record_source_patient,
	record_source_realalarm,
	record_source_real,
	record_source_realEndless,
	record_source_trendgraphreview,
	record_source_trendtablereview,
	record_source_wavereview
};

typedef enum 
{
	module_name_unknown = 0,
	module_ECG,
	module_RESP,
	module_SPO2,
	module_TEMP,
	module_NIBP,
	module_IBP12,
	module_IBP34,
	module_CO,

	module_AG,
	module_NecollSpo2,
	module_MasimoSpo2,

	//下面为了设置颜色,将这些波形作为了模块
	module_AG_N2O  =  50,
	module_AG_CO2,
	module_AG_O2,
	module_AG_HAL,
	module_AG_ISO,
	module_AG_ENF,
	module_AG_SEV,
	module_AG_DES,

	module_ST,			//在报警回顾中将ST,Arr,存储的报警单独列出
	module_Arr,
	module_Save_Alarm
} MODULE_NAME_TYPE;

enum UNIT_TYPE
{
	unit_TEMP = 0,
	unit_CO,
	unit_IBP,
	unit_NIBP,
	unit_GAS_CO2,
	unit_GAS_O2,
	unit_HEIGHT,
	unit_WEIGHT
};

enum EXPORT_TYPE
{
	export_SupportTrend	=0x00000001,
	export_SupportAlarm	=0x00000002,
	export_SupportWave	=0x00000004,
	export_SupportNIBP	=0x00000008,
	export_SupportDrug	=0x00000020,
	export_Support		=0x10000000
};

enum ScreenSize
{
	TFT15,
	CRT15,
	CRT17,
	TFT17,
	CRT19,
	TFT19,
	CRT21,
	TFT21
};

enum ALARM_FLAG
{
	ALARM_FLAG_Unknow,
	ALARM_FLAG_TooLow,
	ALARM_FLAG_TooHigh,
	ALARM_FLAG_END
};


enum HIGHEST_ALARM_TYPE
{
	highest_alarm_no,
	highest_alarm_Para,
	highest_alarm_Tech
};

enum REVIEW_TYPE
{
	review_unknown= 0,
	review_online,
	review_history,
	review_prs
};

enum DRUG_TYPE
{
	drug_Unknown= 0,
	drug_A,
	drug_B,
	drug_C,
	drug_D,
	drug_E,
	drug_AMINOPHYLLINE,
	drug_DOBUTAMINE,
	drug_DOPAMINE,
	drug_EPINEPHRINE,
	drug_HEPARIN,
	drug_ISUPREL,
	drug_LIDOCAINE,
	drug_NIPRIDE,
	drug_NITROGLYCERIN,
	drug_PITOCIN
};

enum COMM_ERROR
{
	ERROR_COMM_SUCCESS							=0x00000000,	//无错误
	ERROR_COMM_PT_NOT_FOUND						=0xA0000000,	//在某一次数据解析中，对数据包头无法进行解释
	ERROR_COMM_PACK_SIZE_CHECK					=0xA0000001,	//包长度错误,校验失败
	ERROR_COMM_ALLDATA_NOT_FOUND				=0xA0000002,	//alldata数据中，没有发现包类型
	ERROR_COMM_PROTOCOL_NOT_FOUND				=0xA0000003,	//在接收到Poweron时，协议版本未找到
	ERROR_COMM_PACK_SIZE_TOO_LONG				=0xA0000004,	//包长度过长
	ERROR_COMM_CREATE_SOCKET					=0xA0000005,	//create Socket
	ERROR_COMM_LISTEN_SOCKET					=0xA0000006,	//listen Socket
	ERROR_COMM_SIZE_NOT_MATCH_STRUCT			=0xA0000007,	//接收后计算到的包长度与结构大小不匹配
	ERROR_COMM_UNKNOWN_MODULE_LOADED			=0xA0000008,	//在模块装载时，接收到未知模块
	ERROR_COMM_0X30								=0xA0000009,	//在要求出现0x30的地方，不是0x30
	ERROR_COMM_UNKNOWN_MODULE_UNLOADED			=0xA000000A,	//在模块卸载时，接收到未知模块
	ERROR_COMM_ALLDATA_SIZE_NOT_MATCH_STRUCT	=0xA000000B,	//接收后计算到的包长度与结构大小不匹配
	ERROR_COMM_NO_PATIENT_INFO					=0xA000000C,	//没有接受到病人信息
	ERROR_COMM_FIND_MODULE_WHEN_APPEND_WAVE_DATA=0xA000000D,	//在追加波形数据时没有找到模块(在wave矢量中没有匹配的项目(bedno,slotno,muduleno,waveindex))
	ERROR_COMM_MODULEA_LOADED					=0xA000000E,	//模块已经加载
	ERROR_COMM_UNLOAD_NOT_EXIST_MODULE			=0xA000000F,	//卸载一个没有加载的模块
	ERROR_COMM_PACK_CHECKSUM_ERROR				=0xA0000010,	//包校验和不正确
	ERROR_COMM_PACK_VERSION_NOT_SUPPORT			=0xA0000011		//包协议版本不支持
};

enum TIP_ECG
{
	TIP_ECG_NONE	=0x00000000,
	TIP_ST_LEARN	=0x00000001,
	TIP_ARR_LEARN	=0x00000002
};

enum TIP_SPO2
{
	TIP_SPO2_NONE	=0x00000000,
	TIP_SPO2_SEARCH	=0x00000001
};


enum TIP_NIBP
{
	TIP_NIBP_NONE						=0x00000000,
	TIP_NIBP_MANUAL_MEASURE				=0x00000001,
	TIP_NIBP_CONTINUE_MEASURE			=0x00000002,
	TIP_NIBP_AUTO_MEASUREING			=0x00000004,
	TIP_NIBP_SOFTWARE_RESETTING			=0x00000008,
	TIP_NIBP_HARDWARE_RESETTING			=0x00000010,
	TIP_NIBP_PLEASE_START				=0x00000020,
	TIP_NIBP_CALIBRATING				=0x00000040,
	TIP_NIBP_CALIBRATING_STOPPED		=0x00000080,
	TIP_NIBP_PNEUMATIC_TESTING			=0x00000100,
	TIP_NIBP_PNEUMATIC_TESTING_STOPPED	=0x00000200,
	TIP_NIBP_MEASURING_STOPPED			=0x00000400,
	TIP_NIBP_RESET_FAILED				=0x00000800
};


typedef struct _ALARM_LEVEL_INFO
{
	UCHAR iAlarmType;
	UCHAR iLevel;
	UCHAR iExLevel;
	UCHAR iIsAlarming;
	NET_DATE_TIME time;
} __attribute__ ((packed, aligned(1))) ALARM_LEVEL_INFO;

typedef struct _TECH_ALARM_LEVEL_INFO
{
	UINT16 iAlarmType;
	UCHAR iLevel;
	UCHAR iExLevel;
} __attribute__ ((packed, aligned(1))) TECH_ALARM_LEVEL_INFO;

typedef struct _GUID 
{  
	DWORD Data1;  
	WORD Data2;  
	WORD Data3;  
	BYTE Data4[8];
} __attribute__ ((packed, aligned(1))) GUID;


typedef struct _PATIENT_INFO7
{
	long				m_lMask;				//掩码，表示后面那些数据有效
	GUID				m_oGuid;			   //GUID	  0x0001
	CHAR				m_szSurName[32];//MSDE_MAXSIZE_PERSON_SURNAME];		//姓		0x0002
	CHAR				m_szName[MSDE_MAXSIZE_PERSON_NAME];			//名		0x0004
	CHAR				m_szOffice[MSDE_MAXSIZE_OFFICE];			//科室		0x0008
	CHAR				m_BedNo;			//床号		0x0010
	CHAR				m_szMedicalNo[MSDE_MAXSIZE_MEDICALNO];		//病历号	0x0020

	DATETIME			m_dtAdmitDate;			//入院日期	0x0040
	DATETIME			m_dtBornDate;			//出生日期	0x0080

	CHAR				m_szDoctorSurName[MSDE_MAXSIZE_PERSON_SURNAME];	//主治医师姓	0x0100
	CHAR				m_szDoctorName[MSDE_MAXSIZE_PERSON_NAME];		//主治医师姓名	0x0200

	INT16				m_Sex;				//性别		0x0400	
	INT16				m_PatientType;		//病人类型	0x0800
	float				m_dHeight;				//身高		0x1000
	float				m_dWeight;				//体重		0x2000
	INT16				m_Blood;				//血型		0x4000

	INT16				m_Pace;				//PACE开关	0x8000
	CHAR				m_szTel[MSDE_MAXSIZE_PHONE];			//电话		0x10000
	CHAR				m_szAddress[MSDE_MAXSIZE_ADDRESS];		//住址		0x20000
	CHAR				m_szPostCode[MSDE_MAXSIZE_POSTCODE];		//邮政编码	0x40000
} __attribute__ ((packed, aligned(1)))  PATIENT_INFO7;


	typedef struct _DATE_TIME
	{
		unsigned short		  iYear;
		unsigned char		   iMonth;
		unsigned char		   iDay;
		unsigned char		   iHour;
		unsigned char		   iMinute;
		unsigned char		   iSecond;
	}__attribute__ ((packed, aligned(1))) DATE_TIME;

enum TECH_ALARM_TYPE
{
	tech_alarm_unknown = 0,
	//下面三个技术报警用于兼容旧版协议。
	tech_alarm_high,
	tech_alarm_mid,
	tech_alarm_low,
	tech_alarm_LeadOff,
	
	// 新版协议可以区分如下信息
	tech_alarm_ECG_First = 5,
	tech_alarm_ECGLEADOFF = tech_alarm_ECG_First, 
	tech_alarm_ECGVOFF,
	tech_alarm_ECGLLOFF,
	tech_alarm_ECGLAOFF,
	tech_alarm_ECGRAOFF,
	tech_alarm_ECGVOFF1,	 //下面的组1和组2用于实现不用的命名规则，一般不用。
	tech_alarm_ECGLLOFF1,
	tech_alarm_ECGLAOFF1,
	tech_alarm_ECGRAOFF1,
	tech_alarm_ECGVOFF2,
	tech_alarm_ECGLLOFF2,
	tech_alarm_ECGLAOFF2,
	tech_alarm_ECGRAOFF2,
	tech_alarm_STLEARN,
	tech_alarm_ARRLEARN,
	tech_alarm_ECGLEARN,
	tech_alarm_ECGINITERROR,
	tech_alarm_ECGINITERRCPU,
	tech_alarm_ECGINITERRWD,
	tech_alarm_ECGINITERRRAM,
	tech_alarm_ECGINITERRROM,
	tech_alarm_ECGINITERRCIR,
	tech_alarm_ECGINITERRAD,
	tech_alarm_ECGINITUD1,
	tech_alarm_ECGINITUD2,
	tech_alarm_ECG1SELFTESTERR,
	tech_alarm_ECG2SELFTESTERR,
	tech_alarm_ECGCOMSTOP,
	tech_alarm_ECGCOMERR,
	tech_alarm_HRALMERR,
	tech_alarm_PVCALMERR,
	tech_alarm_STALMERR,
	tech_alarm_ECGNOIS,
	tech_alarm_HREXD,
	tech_alarm_PVCEXD,
	tech_alarm_STEXD,
	tech_alarm_ST1EXD,
	tech_alarm_ST2EXD,
	tech_alarm_ST3EXD,
	tech_alarm_ST4EXD,
	tech_alarm_ST5EXD,
	tech_alarm_ST6EXD,
	tech_alarm_ST7EXD,
	tech_alarm_RRALMERR,
	tech_alarm_RREXD,
	tech_alarm_RESPDISTURBED,
	tech_alarm_ECG1SIGNALSATU,
	tech_alarm_ECG2SIGNALSATU,
	tech_alarm_DEFIB_SYN_INFO,

	tech_alarm_ECG_Last = 204,

	tech_alarm_SPO2_First = 205,
	tech_alarm_SPO2SNSOFF = tech_alarm_SPO2_First,
	tech_alarm_SPO2SEARCH,
	tech_alarm_SPO2INITERROR,
	tech_alarm_SPO2INITERRCPU,
	tech_alarm_SPO2INITERRWD,
	tech_alarm_SPO2INITERRRAM,
	tech_alarm_SPO2INITERRROM,
	tech_alarm_SPO2INITERRCIR,
	tech_alarm_SPO2INITERRAD,
	tech_alarm_SPO2INITERRUD1,
	tech_alarm_SPO2INITERRUD2,
	tech_alarm_SPO2COMMSTOP,
	tech_alarm_SPO2COMMERR,
	tech_alarm_SPO2ALMERR,
	tech_alarm_SPO2EXD,
	tech_alarm_PRALMERR,
	tech_alarm_PREXD,
	tech_alarm_SPO2WEAKPULSE,
	tech_alarm_SPO2WEAKSIGNAL,
	tech_alarm_SPO2CHECKSNS,
	tech_alarm_SPO2MOTION,
	tech_alarm_SPO2INTERF,
	tech_alarm_SPO2LOWPERF,
	tech_alarm_SPO2MUCHLIGHT,
	tech_alarm_SPO2UNRECOGSNS,
	tech_alarm_SPO2BOARDFAULT,
	tech_alarm_SPO2SNSFAULT,
	tech_alarm_SPO2NOSNS,
	tech_alarm_SPO2LOWIQ,
	tech_alarm_SPO2INCOMPSNS,

	tech_alarm_SPO2_Last = 404,

	tech_alarm_NIBP_First = 405,
	tech_alarm_NSALMERR = tech_alarm_NIBP_First,
	tech_alarm_NMALMERR,
	tech_alarm_NDALMERR,
	tech_alarm_NSEXD,
	tech_alarm_NMEXD,
	tech_alarm_NDEXD,
	tech_alarm_NIBP_Last = 454,

	tech_alarm_NIBP_INFO_First = 455,
	tech_alarm_NIBPINITERROR = tech_alarm_NIBP_INFO_First,
	tech_alarm_NIBPSELFERR,	
	tech_alarm_NIBPCOMMUERR,		 
	tech_alarm_NIBPLOOSECUF,		
	tech_alarm_NIBPAIRLEAK,		 
	tech_alarm_NIBPAIRERR,		 
	tech_alarm_NIBPWEAKSIG,		 
	tech_alarm_NIBPRANGEEXCE,		 
	tech_alarm_NIBPEXCESSIVE,		 
	tech_alarm_NIBPOVERPRE,		 
	tech_alarm_NIBPSIGNALSATU,	 
	tech_alarm_NIBPPNEUMATIC,		 
	tech_alarm_NIBPSYSFAIL,		 
	tech_alarm_NIBPTIMEOUT,		 
	tech_alarm_NIBPCUFFTYPE,		 
	tech_alarm_NIBPMEASUREFAIL,	  
	tech_alarm_NIBPRSTERR,
	tech_alarm_NIBP_INFO_Last = 604,

	tech_alarm_TEMP_First = 605,
	tech_alarm_T1SNOFF = tech_alarm_TEMP_First,
	tech_alarm_T2SNOFF,
	tech_alarm_TEMPBDFAILURE,
	tech_alarm_TEMPINITERROR,
	tech_alarm_TEMPINITERRCPU,
	tech_alarm_TEMPINITERRWD,
	tech_alarm_TEMPINITERRRAM,
	tech_alarm_TEMPINITERRROM,
	tech_alarm_TEMPINITERRCIR,
	tech_alarm_TEMPINITAD,
	tech_alarm_TEMPINITUD1,
	tech_alarm_TEMPINITUD2,
	tech_alarm_T1ALMERR,
	tech_alarm_T2ALMERR,
	tech_alarm_TDALMERR,
	tech_alarm_T1EXD,
	tech_alarm_T2EXD,
	tech_alarm_TDEXD,
	tech_alarm_TEMPCOMMERROR,
	tech_alarm_TEMPCOMMSTOP,
	tech_alarm_TEMPSELFTESTERR,
	tech_alarm_TEMPCALIBRATIONERR,
	tech_alarm_TEMP_Last = 804,

	tech_alarm_IBP_First = 805,
	tech_alarm_IBP1SNOFF = tech_alarm_IBP_First,
	tech_alarm_IBP2SNOFF,
	tech_alarm_IBP3SNOFF,
	tech_alarm_IBP4SNOFF,
	tech_alarm_IBP12INITERROR,
	tech_alarm_IBP12INITERRCPU,
	tech_alarm_IBP12INITERRWD,
	tech_alarm_IBP12INITERRRAM,
	tech_alarm_IBP12INITERRROM,
	tech_alarm_IBP12INITERRCIR,
	tech_alarm_IBP12INITERRAD,
	tech_alarm_IBP12INITERRUD1,
	tech_alarm_IBP12INITERRUD2,
	tech_alarm_IBP34INITERROR,
	tech_alarm_IBP34INITERRCPU,
	tech_alarm_IBP34INITERRWD,
	tech_alarm_IBP34INITERRRAM,
	tech_alarm_IBP34INITERRROM,
	tech_alarm_IBP34INITERRCIR,
	tech_alarm_IBP34INITERRAD,
	tech_alarm_IBP34INITERRUD1,
	tech_alarm_IBP34INITERRUD2,
	tech_alarm_IBP12COMMERROR,
	tech_alarm_IBP12COMMSTOP,
	tech_alarm_IBP34COMMERROR,
	tech_alarm_IBP34COMMSTOP,
	tech_alarm_IBP1ALMERR,
	tech_alarm_IBP2ALMERR,
	tech_alarm_IBP3ALMERR,
	tech_alarm_IBP4ALMERR,
	tech_alarm_IBP1NSEXD,
	tech_alarm_IBP1NDEXD,
	tech_alarm_IBP1NMEXD,
	tech_alarm_IBP2NSEXD,
	tech_alarm_IBP2NDEXD,
	tech_alarm_IBP2NMEXD,
	tech_alarm_IBP3NSEXD,
	tech_alarm_IBP3NDEXD,
	tech_alarm_IBP3NMEXD,
	tech_alarm_IBP4NSEXD,
	tech_alarm_IBP4NDEXD,
	tech_alarm_IBP4NMEXD,
	tech_alarm_IBP1NEEDCALZERO,
	tech_alarm_IBP2NEEDCALZERO,
	tech_alarm_IBP3NEEDCALZERO,
	tech_alarm_IBP4NEEDCALZERO,
	tech_alarm_IBP_Last = 1004,

	tech_alarm_SYS_First = 1605,
	tech_alarm_SYSWDFIRE = tech_alarm_SYS_First,
	tech_alarm_SYSTASKERR,   
	tech_alarm_SYSCMOSEXHAUSED,
	tech_alarm_SYSCMOSERR,
	tech_alarm_SYSFPGAERR,
	tech_alarm_SYSTIMELOST,
	tech_alarm_SYSREALTIMENOTEXIST,
	tech_alarm_SYSGERR2,
	tech_alarm_SYSGERR3,
	tech_alarm_SYSGERR4,
	tech_alarm_SYSGERR5,
	tech_alarm_SYSGERR6,
	tech_alarm_SYSGERR7,
	tech_alarm_SYSGERR8,
	tech_alarm_SYSGERR9,
	tech_alarm_SYSGERR10,
	tech_alarm_SYSGERR11,
	tech_alarm_SYSGERR12,
	tech_alarm_SYS_Last = 1804,

	tech_alarm_KEY_First = 1805,
	tech_alarm_KEYINITERROR = tech_alarm_KEY_First,
	tech_alarm_KEYINITERRCPU,
	tech_alarm_KEYINITERRWD,
	tech_alarm_KEYINITERRRAM,
	tech_alarm_KEYINITERRROM,
	tech_alarm_KEYINITERRUD1,
	tech_alarm_KEYINITERRUD2,
	tech_alarm_KEYNOTAVI,
	tech_alarm_KEYCOMMERR,
	tech_alarm_KEYPRESSERR,
	tech_alarm_KEYGERROR1,
	tech_alarm_KEYGERROR2,
	tech_alarm_KEYFAIL,
	tech_alarm_KEY_Last = 2004,

	tech_alarm_NET_First = 2005,
	tech_alarm_NETINITERROR = tech_alarm_NET_First,
	tech_alarm_NETINITERRRAM,
	tech_alarm_NETINITERRROM,
	tech_alarm_NETINITRUNERROR,
	tech_alarm_NETINITRUNERRUD1,
	tech_alarm_NETINITRUNERRUD2,
	tech_alarm_NETINITRUNERRUD3,
	tech_alarm_NETINITRUNERRUD4,
	tech_alarm_NET_Last = 2204,

	tech_alarm_POWER_First = 2205,
	tech_alarm_POWER5VTOOHIGH = tech_alarm_POWER_First,
	tech_alarm_POWER5VTOOLOW,
	tech_alarm_POWER1HIGH,
	tech_alarm_POWER1LOW,
	tech_alarm_POWER12VTOOHIGH,
	tech_alarm_POWER12VTOOLOW,
	tech_alarm_POWER2HIGH,
	tech_alarm_POWER2LOW,
	tech_alarm_POWERCELLVTOOHIGH,
	tech_alarm_POWERCELLVTOOLOW,
	tech_alarm_POWER33VTOOHIGH,
	tech_alarm_POWER33VTOOLOW,
	tech_alarm_POWERBATTERYLOW,
	tech_alarm_BATTREY_20_MINUTES,
	tech_alarm_BATTREY_10_MINUTES,
	tech_alarm_BATTERY_OVERTEMP,
	tech_alarm_BATTERY_OVERCHARGE,
	tech_alarm_BATTERY_VOLTOHIGH,
	tech_alarm_BATTERY_VOLTOLOW,
	tech_alarm_POWER_Last = 2404,
	
	tech_alarm_REC_First = 2405,
	tech_alarm_RECINITERROR = tech_alarm_REC_First,
	tech_alarm_RECINITERRCPU,
	tech_alarm_RECINITERRWD,
	tech_alarm_RECINITERRRAM,
	tech_alarm_RECINITERRROM,
	tech_alarm_RECINITERRUD1,
	tech_alarm_RECINITERRUD2,
	tech_alarm_RECSELFERR,
	tech_alarm_RECINITIALIZING, 
	tech_alarm_RECBUSY,	 
	tech_alarm_RECVOLTHIGH,
	tech_alarm_RECVOLTLOW,
	tech_alarm_RECHEADHOT,
	tech_alarm_RECHEADWRPOS,
	tech_alarm_RECPAPEROUT,
	tech_alarm_RECPAPERJAM,
	tech_alarm_RECCOMMERROR,
	tech_alarm_RECTOOMANYTASK,
	tech_alarm_RECPAPERWRPOS,
	tech_alarm_RECSERIALERR,
	tech_alarm_RECNONAVAI,
	tech_alarm_REC_Last = 2604,
	
	tech_alarm_Others_First = 2605,
	tech_alarm_PatientInfo_Conflict = tech_alarm_Others_First,
	tech_alarm_PatientInfo_Others_Last = 2804
};

typedef struct
{
	UINT16	 strid;
	UINT16	 netid;
} TECHNETVALUE;


#endif
