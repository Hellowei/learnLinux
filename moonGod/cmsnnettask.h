#ifndef CMSNETTASK_H
#define CMSNETTASK_H

typedef struct
{
	INT32		BuffSize;
	INT32		FreeBuffSize;
	UCHAR *		BuffHead;
	UCHAR *		BuffTail;
	UCHAR *		ReadPtr;
	UCHAR *		WritePtr;
}	NETBUFFER;

typedef struct
{
	UCHAR		pMonitorAddress[6];		// 床边机的地址，现在是后四个byte存放地址
	BOOL		 NetcardDroven;			// MAC层是否驱动
	BOOL		AdmittedPatient;		// 本床边机是否接收了病人 
	INT32		PatientSequenceNumber;
	UCHAR		pPatientGUID[30];	
	BOOL		AdmittedByCenter;		// 说明本床是否被中央站连接
	UCHAR		pCenterAddress[6];		// 中央站的地址，现在是后四个byte存放地址
}	MONITORNETINFO;


#define	 INVALID_SOCKET				-1
#define		MAX_UDP_PACKET_LEN			1500
#define		CMSN_RCVTASK_SLEEP_TICKS	250

#define		NET_SEND_BUFFER_SIZE			10240 // 10K
#define		NET_RECV_BUFFER_SIZE			10240 // 10K

#define		TCP_SEND_BUFFER_SIZE			10240 // 10K
#define		TCP_RECIEVE_BUFFER_SIZE			1024 // 1K

#define		MULTI_SEND_BUFFER_SIZE		10240 // 10k

#define		BROAD_SEND_BUFFER_SIZE		 512

VOID InitNetBuffer( NETBUFFER *buff, UCHAR * data_buff, INT32 buff_size );
INT32 GetBufferSize( NETBUFFER *buff );
INT32 GetFreeBufferSize( NETBUFFER *buff );
VOID ClearBuffer( NETBUFFER *buff );
BOOL SaveDataToBuffer( NETBUFFER *buff, UCHAR * data_buff, INT32 data_size );
INT32 GetCurrentDataSize( NETBUFFER *buff );
INT32 GetCurrentData( NETBUFFER *buff, UCHAR * data_buff );


VOID InitTcpSendBuffer();


VOID InitMultiSendBuffer();
INT32 GetMultiSendBufferSize();
INT32 GetMultiSendFreeBufferSize();
VOID ClearMultiSendBuffer();
BOOL SaveDataToMultiSendBuffer( UCHAR * data_buff, INT32 data_size );
INT32 GetMultiSendBufferCurrentDataSize();
INT32 GetMultiSendBufferCurrentData( UCHAR * data_buff );



void CMSNNetConnectTask( UINT32 argc, void *argv );
void NetSendTcpDataTask( UINT32 argc, void *argv );
void NetSendUdpDataTask( UINT32 argc, void *argv );
void NetReceiveTCPTask(UINT32 argc, void *argv);
void NetReceiveMultiTask(UINT32 argc, void *argv);
void NetReceiveBroadTask(UINT32 argc, void *argv);
BOOL GetCmsPlusNetOnOff();
void SetCmsPlusModeNormal();
void SetCmsPlusModeInit();
VOID SetMonitorIpAddrNetInfo( UCHAR *ip_addr );


VOID DisconnectWithCms(VOID);
VOID SetAdmitPatientNetInfo( BOOL admit );
void ObtainOnePatientGUID( UCHAR *patient_guid );
VOID SetPatientGuidNetInfo( UCHAR * patient_guid, BOOL admit );

void StartDischargePatientTimer( INT16 seconds );




MONITOR_ONLINE_NOTIFY gHyp6NetInfo;

 INT16 gCmsOnline;
 INT16 gBroadcastSocket;


#endif

