
#ifndef CMSPROCESS_H
#define CMSPROCESS_H

enum PROCESSRESULT
{
	P_OK,
	P_MODIFYING
};


typedef enum
{
	SET_SUCCEED,
	SETTING_SAME,
	SETTING_MODIFYING,
	SET_FAILED
} CHANGE_MODULE_SETTING;



typedef struct _cprocess_object
{
	//	0 -- 8S	 1 -- 16S	2 -- 32S
	BOOL (*SetAlarmStorageTime)( INT16 storage_time );
	// 0 -- off	 1 -- on
	BOOL (*SetAlarmSoundSwitch)( INT16 sound_switch );
	// 0 -- off	 1 -- on
	BOOL (*SetAlarmMuteSwitch)( INT16 mute_switch );
	// 0 -- off	 1 -- on
	BOOL (*SetAlarmPauseSwitch)( INT16 pause_switch );
	// 0 -- 1MIN	1 -- 2MIN	 3 -- 3MIN
	BOOL (*SetAlarmPauseTime)( INT16 pause_time );
	// 1 -- 10级
	BOOL (*SetAlarmVolumeLevel)( INT16 volume_level );

	BOOL (*SetAlarmTransferSwitch)( INT16 transfer_switch );
	
	BOOL (*AddSingleParaAlarm)( PARA_ALARM_INFO para_alarm );
	
	BOOL (*AddSingleTechAlarm)( TECH_ALARM_INFO tech_alarm );
	
	BOOL (*SetParaAlarmLevel)( PARA_ALARM_INFO para_alarm_info );

	BOOL (*SetParaAlarmLimitRange)( STU_PARA_ALARM_LIMIT_ADJUST_RANGE alm_limt_range );
	
	BOOL (*AppendWaveDataNull)();
	
	BOOL (*SetParaValidLimit)();

	BOOL (*AppendParaDataNULL)();

	// 0 -- off	 1 -- on
	BOOL (*SetArrAnalysisSwitch)( BOOL arr_enable );
	
	BOOL (*SetArrAlarmStorageTime)( INT16 arr_storage_time );
	
	// 0: ECG, 1: SPO2, 2: auto, 3: show both
	BOOL (*SetHeartRateSource)( INT16  hr_source );
	
	// 0~3: channel 1, channel 2, channel 3, auto select
	BOOL (*SetHrCalculateChannel)( INT hr_channel );
	
	// lead system)(0:3-lead system, 1: 5-lead system);
	BOOL (*SetEcgLeadSystem)( INT16	lead_system );
	
	// 0 -- 关闭陷波	1 -- 50HZ	2 -- 60HZ
	BOOL (*SetEcgBandStopFilter)( INT16 band_stop );
	
	BOOL (*SetEcgPaceAnalysisSwitch)( INT16 pace_switch );
	
	BOOL (*SetEcgNameRule)( INT16 name_rule );
	
	// 0 -- DIA ...
	BOOL (*SetEcgFilterMode)( INT16 filter_mode );
	
	// 0 -- not	 1 -- calibrate
	BOOL (*SetEcgCalibrateSwitch)( BOOL calib_switch );
	
	BOOL (*SetEcgArrRelearn)( BOOL arr_relearn );
	
	BOOL (*SetStIsoPoint)( INT16 st_iso );
	
	BOOL (*SetStStPoint)( INT16 st_st );
	
	BOOL (*SetStAnalysisLead)( INT16 lead );
	
	BOOL (*SetStAnalysisSwitch)( BOOL st_switch );
	
	BOOL (*SetEcgWaveGain)();
	
	BOOL (*AppendEcgPaceData)();

	// 0 -- SPO2_AVE_TIME_4SECS
	// 1 -- SPO2_AVE_TIME_8SECS
	// 2 -- SPO2_AVE_TIME_16SECS
	BOOL (*SetSpo2AverageTime)( INT16 average_time );
	
	// masimo spo2
	// 0 -- MAS_SPO2_SENSITIVITY_NORMAL
	// 1 -- MAS_SPO2_SENSITIVITY_HIGH
	BOOL (*SetSpo2SensitivityMode)( INT16 sensi_mode );
	
	// 0 -- IBP_FILTER_NORMAL
	// 1 -- IBP_FILTER_SMOOTH
	// 2 -- IBP_FILTER_OFF
	BOOL (*SetIBPFilterType)( INT16 filter_mode );
	
	BOOL (*SetIBPZeroStatus)();
	
	BOOL (*SetIBPCalibrateStatus)();
	
	BOOL (*SetIBPAmpAdjustType)();
	
	BOOL (*SetIBPWaveScale)();
	
	BOOL (*SetIBPWavePressureType)();
	
	BOOL (*SetRespWaveAmplitude)( INT16 wave_name, INT16 wave_gain );
	
	// 0 -- 自动
	// 1 -- 手动
	BOOL (*SetRespHoldType)( INT16 calculate_mode );
	
	BOOL (*SetNibpMeasureIntervalTime)( INT16 interval_time );
	
	BOOL (*SetNibpMeasureStatus)( INT16 command_id );
	
	BOOL (*AppendNibpParaData)();

	BOOL (*SetLanguage)( INT16 language );
	
	BOOL (*SetprotocolType)( INT16 protocol );
	
	BOOL (*SetArrDelay)( INT16 delay );
	
	BOOL (*SetNetworkConnectType)( INT16 connet_type );
	
	
	BOOL (*ModuleUnload)( INT16 module );
	
	BOOL (*SetParaAlarmSwitch)( PARA_NAME_TYPE para_name, BOOL alm_switch );

	BOOL (*SetIntParaAlarmLimit)( PARA_NAME_TYPE para_name, INT16 high_limit, INT16 low_limit );

	BOOL (*SetFloatParaAlarmLimit)( PARA_NAME_TYPE para_name, FLOAT high_limit, FLOAT low_limit );

	BOOL (*SetIbpParaAlarmLimit)( PARA_NAME_TYPE para_name, 
								INT16 pressure_name, INT16 high_limit, INT16 low_limit );

	BOOL (*SetParaAlarmLimit)( ALARM_LIMIT alarm_limit );
	
	BOOL (*SetWaveValueLimit)();

	BOOL (*SetWaveName)();

	BOOL (*ReplyDischargePatient)( BOOL reply_flag );

	BOOL (*BeginModuleLoad)();

	BOOL (*ModuleLoad)( INT16 module_id );

	BOOL (*EndModuleLoad)();

	BOOL (*SetParaAlarmLimitAdjustRange)( STU_PARA_ALARM_LIMIT_ADJUST_RANGE alm_limit_range );
	
	BOOL (*AdmitPatient)( PATIENT_INFO7* stuPatientInfo7 );

	
	BOOL (*SetPatientInfo)( PATIENT_INFO7 stuPatientInfo7 );

	BOOL (*AppendWaveData)( INT16 wave_name, INT16 sample_rate, INT16 data_type, UCHAR *data_index_ptr );

	BOOL (*SetParaVirtualLimit)( INT16 patient_type, STU_PARA_VIRTUAL_LIMIT para_virtual_limit );


	BOOL (*AppendParaData)( STU_REALTIME_PARA_DATA para_data );

	
	BOOL (*SetRespApneaAlarmTime)( INT16 apnea_time );

	BOOL (*SetSystemTime)( NET_DATE_TIME* net_date_time );

	BOOL (*SopNibpMeasure)();
	BOOL (*ReplyDefaultSetting)( INT16 module_name );
	BOOL (*SetArrParaAlarmSwitch)( ARR_ALARM_SWITCH alm_switch );
	BOOL (*SetAlarmLatch)( BOOL latch_switch );

}CProcessObject;

extern CProcessObject ProcessObject;
#endif




