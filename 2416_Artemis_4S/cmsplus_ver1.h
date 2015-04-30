
#ifndef	CMSPLUS_VER1_H
#define	CMSPLUS_VER1_H

#define MAX_PACKET_LENGTH 1500

int ParsePacketBody( CProcessObject * pObj, UCHAR* pPacketBody, INT32 iPacketBodyLen, PACKETINFOHEADER *pPacketInfoHeader);

int ParseModuleLoadPacket( CProcessObject * pObj, UCHAR* pPacketBody, INT32 iPacketBodyLen);

int ParseAlarmGeneralSettingPacket( CProcessObject * pObj, UCHAR* pPacketBody, INT32 iPacketBodyLen);

int ParseCurrentAlarmListPacket( CProcessObject * pObj, UCHAR* pPacketBody, INT32 iPacketBodyLen, BOOL bIsParaAlarm);

int ParseAlarmLevelSettingPacket( CProcessObject * pObj, UCHAR* pPacketBody, INT32 iPacketBodyLen);

int ParseAlarmLimitAdjustRangePacket( CProcessObject * pObj, UCHAR* pPacketBody, INT32 iPacketBodyLen);

int ParsePatientOnlineNotifyPacket( CProcessObject * pObj, UCHAR* pPacketBody, INT32 iPacketBodyLen);

int ParsePatientInfoPacket( CProcessObject * pObj, UCHAR* pPacketBody, INT32 iPacketBodyLen );

BOOL GetAlarmParaAndStatusFromAlarmType( CProcessObject * pObj, PARA_NAME_TYPE *pAlarmPara, ALARM_STATUS *pAlarmStatus, UCHAR iAlarmType);

//对于参数报警，下面函数得到参数名称对应的第一个报警类型。返回值表示找到匹配的报警类型数目。
int GetAlarmTypeFromAlarmParaName( PARA_NAME_TYPE enAlarmPara, UCHAR* iAlarmType);

BOOL GetEnumParaTypeFromParaValue(UCHAR iParaType, PARA_NAME_TYPE *pParaType);

//bool GetParaValueFromEnumParaType(UCHAR* iParaType, enum PARA_NAME_TYPE enParaType );

BOOL GetEnumWaveTypeFromWaveValue(UCHAR iWaveType, WAVE_NAME_TYPE *pWaveType);

BOOL GetWaveValueFromEnumWaveType(UCHAR* iWaveType, WAVE_NAME_TYPE enWaveType);

int ParseRealtimeWaveData( CProcessObject * pObj, UCHAR* pPacketBody, INT32 iPacketBodyLen);

int ParseParaVirtualValueLimitPacket( CProcessObject * pObj, UCHAR* pPacketBody, INT32 iPacketBodyLen);

int ParseRealtimeParaDataPacket( CProcessObject * pObj, UCHAR* pPacketBody, INT32 iPacketBodyLen);

int ParseECGGeneralSettingPacket( CProcessObject * pObj, UCHAR* pPacketBody, INT32 iPacketBodyLen);

int ParseEcgStSettingPacket( CProcessObject * pObj, UCHAR* pPacketBody, INT32 iPacketBodyLen);

int ParseEcgWaveGainPacket( CProcessObject * pObj, UCHAR* pPacketBody, INT32 iPacketBodyLen);

int ParseEcgPaceDataPacket( CProcessObject * pObj, UCHAR* pPacketBody, INT32 iPacketBodyLen);

int ParseSpo2GeneralSettingPacket( CProcessObject * pObj, UCHAR* pPacketBody, INT32 iPacketBodyLen);

int ParseCoGeneralSettingPacket( CProcessObject * pObj, UCHAR* pPacketBody, INT32 iPacketBodyLen);

int ParseCoWaveDataPacket( CProcessObject * pObj, UCHAR* pPacketBody, INT32 iPacketBodyLen);

int ParseIBPGeneralSettingPacket( CProcessObject * pObj, UCHAR* pPacketBody, INT32 iPacketBodyLen);

int ParseIBPWaveAmpAdjustModePacket( CProcessObject * pObj, UCHAR* pPacketBody, INT32 iPacketBodyLen);

int ParseIBPWaveScalePacket( CProcessObject * pObj, UCHAR* pPacketBody, INT32 iPacketBodyLen);

int ParseIBPPressureTypePacket( CProcessObject * pObj, UCHAR* pPacketBody, INT32 iPacketBodyLen);

int ParseRespGeneralSettingPacket( CProcessObject * pObj, UCHAR* pPacketBody, INT32 iPacketBodyLen);

int ParseNibpGeneralSettingPacket( CProcessObject * pObj, UCHAR* pPacketBody, INT32 iPacketBodyLen);

int ParseNibpParaDataPacket( CProcessObject * pObj, UCHAR* pPacketBody, INT32 iPacketBodyLen);

int ParseAgGeneralSettingPacket( CProcessObject * pObj, UCHAR* pPacketBody, INT32 iPacketBodyLen);

int ParseDeviceGeneralSetting( CProcessObject * pObj, UCHAR* pPacketBody, INT32 iPacketBodyLen);

int ParseDeviceBaseInfoPacket( CProcessObject * pObj, UCHAR* pPacketBody, INT32 iPacketBodyLen);

int ParseDeviceSystemTimePacket( CProcessObject * pObj, UCHAR* pPacketBody, INT32 iPacketBodyLen);

int ParseModuleUnLoadPacket( CProcessObject * pObj, UCHAR* pPacketBody, INT32 iPacketBodyLen);

int ParseParaAlarmLimitSettingPacket( CProcessObject * pObj, UCHAR* pPacketBody, INT32 iPacketBodyLen);

int ParseWaveDataRangeSettingPacket( CProcessObject * pObj, UCHAR* pPacketBody, INT32 iPacketBodyLen);

int ParseWaveNameSettingPacket( CProcessObject * pObj, UCHAR* pPacketBody, INT32 iPacketBodyLen);

int ParseCMSSettingPacket( CProcessObject * pObj, UCHAR* packet_body, INT32 packet_body_len);

int DefaultDataRequest( MODULE_NAME_TYPE enModuleName);



int PackDischargePatient( UCHAR * pBuf, INT32 * nLen, INT16 cmd_key_type );

int PackAdmitPatient( UCHAR * pBuf, INT32 * nLen, PATIENT_INFO7 *pPatientInfo );

void AppendPatientInfo( UCHAR *pBuf, INT32 *nLen, PATIENT_INFO7 *pPatientInfo );

int PackSystemDateTime( UCHAR * pBuf, INT32 * nLen, DATETIME system_time, INT16 cmd_key_type );

int ParsefaultSettingPacket( CProcessObject * pObj, UCHAR* packet_body, INT32 packet_body_len);


int PackSetNibpAutoMeasure( UCHAR * pBuf, INT32 * nLen, NIBP_MEASURE_INTERVAL_TIME interval_time );

int PackSetNibpManualMeasure( UCHAR * pBuf, INT32 * nLen );

int PactOnlineNotifyPacket( UCHAR * pBuf, INT32 * nLen, STU_PATIENT_ONLINE_NOTIFY * pPatientOnlineNotify );

int PactStartViewBed( UCHAR * pBuf, INT32 * nLen, UCHAR local_ip[6], UCHAR otherbed_ip[6] );

int PactStopViewBed( UCHAR * pBuf, INT32 * nLen, UCHAR local_ip[6], UCHAR otherbed_ip[6] );

int PackModuleOnLoadPacket( UCHAR * pBuf, INT32 * nLen, INT16 mod_id );

int PactEcgModuleOnLoadField( UCHAR * pBuf, INT32 * nLen );

int PactSpo2ModuleOnLoadField( UCHAR * pBuf, INT32 * nLen );

int PactCoModuleOnLoadField( UCHAR * pBuf, INT32 * nLen );

int PactAgModuleOnLoadField( UCHAR * pBuf, INT32 * nLen );

int PactIbpaModuleOnLoadField( UCHAR * pBuf, INT32 * nLen );

int PactIbpbModuleOnLoadField( UCHAR * pBuf, INT32 * nLen );

int PactNibpModuleOnLoadField( UCHAR * pBuf, INT32 * nLen );

int PackModuleRealTimeData( INT16 module_name, UCHAR *pBuf, INT32 * nLen );

int PackTempModuleRealTimeData( UCHAR *pBuf, INT32 *nLen );

int PackRespModuleRealTimeData( UCHAR *pBuf, INT32 *nLen );

int PackAgModuleRealTimeData( UCHAR *pBuf, INT32 *nLen );

int PackSpo2ModuleRealTimeData( UCHAR *pBuf, INT32 *nLen );

int PackEcgModuleRealTimeData( UCHAR *pBuf, INT32 *nLen );

int PackCurrentAlarmInfo( UCHAR * pBuf, INT32 *nLen, 
							ALARM_LEVEL_INFO *phs_alm, INT16 phs_alm_count,
							TECH_ALARM_LEVEL_INFO *tech_alm, INT16 tech_alm_count );

int PackParaAlarmLimitAndSwitchInternal( UCHAR * pBuf, INT32 *nLen, ALARM_LIMIT *alarm_limit, INT16 limit_num );

int PackParaAlarmLimitAndSwitch( UCHAR * pBuf, INT32 *nLen, PARA_NAME_TYPE para_name );

int PackParaAlarmLevel( UCHAR * pBuf, INT32 *nLen, PARA_NAME_TYPE para_name );
int PackParaAlarmLevelInternal( UCHAR * pBuf, INT32 *nLen, PARA_ALARM_INFO *para_alarm_level, INT16 alarm_count );


int PackModuleInitSetting( INT16 module_name, UCHAR *buff, INT32 *data_len );

int PackNibpMeasureData( UCHAR *buff, INT32 *data_len );
int PackCoMeasureData( UCHAR *buff, INT32 *data_len );
int PackEcgModuleGeneralSetting( UCHAR * pBuf, INT32 * nLen, INT32 mask );
int PackCoModuleGeneralSetting( UCHAR * pBuf, INT32 * nLen, INT32 mask );
int PackNibpModuleGeneralSetting( UCHAR * pBuf, INT32 * nLen, INT32 mask );
int PackAgModuleGeneralSetting( UCHAR * pBuf, INT32 * nLen, INT32 mask );
int PackSpo2ModuleGeneralSetting( UCHAR * pBuf, INT32 * nLen, INT32 mask );

int PackRespModuleGeneralSetting( UCHAR *buff, INT32 *data_len, INT32 mask );
int PackEcgWaveFilter( UCHAR * pBuf, INT32 * nLen );

int PackEcgWaveGain( UCHAR * pBuf, INT32 * nLen );
int PackEcgWaveName( UCHAR * pBuf, INT32 * nLen );
INT16 GetParaAlarmLevel( PARA_NAME_TYPE para_name, PARA_ALARM_INFO *para_alarm_level );
int PackArrAlarmLevel( UCHAR * pBuf, INT32 *nLen );
int PackAllArrAlarmSwitch( UCHAR * pBuf, INT32 *nLen, INT16 cmd_key_type );
int PackParaAlarmLevel1( UCHAR * pBuf, INT32 *nLen, PARA_ALARM_INFO *para_alarm_level, INT16 alarm_count );

int PackArrAlarmSwitch( UCHAR * pBuf, INT32 *nLen, INT16 para_name, INT16 cmd_key_type );

int ParseArrParaAlarmSwitchPacket( CProcessObject * pObj, UCHAR* packet_body, INT32 packet_body_len);

int ParseNibpMeasurePacket( CProcessObject * pObj, UCHAR* packet_body, INT32 packet_body_len);
int PackIbpModuleGeneralSetting( UCHAR *buff, INT32 *data_len, INT32 mask );
int PackIbpaModuleGeneralSetting( UCHAR *buff, INT32 *data_len, INT32 mask );
int PackIbpbModuleGeneralSetting( UCHAR *buff, INT32 *data_len, INT32 mask );
int PackIbpModuleRequestZero( UCHAR *buff, INT32 *data_len, unsigned char channel_no );
int PackIbpModuleCalibrate( UCHAR *buff, INT32 *data_len, unsigned char channel_no, INT16 cal_val);

int PactModuleUnLoadPacket( UCHAR * pBuf, INT32 * nLen, INT16 module_name );
int PackPatientInformation( UCHAR * pBuf, INT32 * nLen, INT16 cmd_key_type);
int PackDeviceGeneralSetting( UCHAR * pBuf, INT32 * nLen, INT32 mask, INT16 cmd_key_type);
int PackAlarmGeneralSetting( UCHAR * pBuf, INT32 * nLen, INT32 mask, INT16 cmd_key_type);
int PackArrAlarmSwitch2( UCHAR * pBuf, INT32 *nLen, 
				ARR_ALARM_SWITCH* alarm_switch, INT16 switch_count, INT16 cmd_key_type);
int PackArrAlarmSwitch3( UCHAR * pBuf, INT32 *nLen, 
				PARA_NAME_TYPE para_name, INT16 cmd_key_type);

int PackIbpaPressureType( UCHAR * pBuf, INT32 * nLen, INT16 cmd_key_type);

int PackIbpExpandPressure( UCHAR * pBuf, INT32 * nLen);

int PackIbpaWaveGain( UCHAR * pBuf, INT32 * nLen, INT16 cmd_key_type);

int PackEcgPaceData( UCHAR *buff, INT32 *data_len, INT16 cmd_key_type);

int PackParaVirtualLimit( UCHAR * buff, INT32 *data_len, INT16 patient_type, PARA_NAME_TYPE para_name, INT16 cmd_key_type);
int PackParaAlarmLimitRange( UCHAR * buff, INT32 *data_len, PARA_NAME_TYPE para_name, INT16 cmd_key_type);
void DemoModeChangeSetting();

int PackIbpaWavePara( UCHAR *buff, INT32 *data_len, INT16 cmd_key_type);
INT16 GetTechAlmNetValueFromAlmIndex( INT16 str_id );

short FloatToShort(float f, int m);

#endif
