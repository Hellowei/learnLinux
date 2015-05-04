#ifndef NETCENTER_H__
#define NETCENTER_H__

#define PKG_0x0A			   0x0A		// �豸����ע��
#define PKG_0x13			0x13		// �豸�������߱�־��ÿ5����һ��

#define PKG_ECG1			0x20		 // ECG1���ݰ�, ÿ����һ��
#define PKG_ECG2			0x21		 // ECG2���ݰ�, ÿ����һ��
#define PKG_RESP			0x22		// RESP���ݰ�, ÿ����һ��
#define PKG_0x0C			   0x0C		// Ѫ�����ݰ���ÿ����һ��
#define PKG_0x0D			   0x0D		// Ѫѹ���ݰ���ÿ����һ��
#define PKG_0x0E			   0x0E		// �������ݰ���ÿ����һ��

#define PKG_0x0F			   0x0F		// ��������(�ȷ�һ�Σ��Ժ��б仯�ٷ����ޱ仯����Ҫ��)

#define PKG_0x50			   0x50		// �л�ECGģʽ
#define PKG_0x51			   0x51		// �л�����ģʽ
#define PKG_0x52			   0x52		// �л�Ѫ��ģʽ
#define PKG_0x53			   0x53		// �ı䲡��ģʽ
#define PKG_0x54			   0x54		// ����/ֹͣѪѹ����
#define PKG_0x55			   0x55		// Ѫѹ����ģʽ������



// �豸ע���(���ñ��豸�Ĺ���)������0x0A
typedef  struct  __PARAMERINFO{
	uint32  paramers;				// �������(��erro=0ʱ��ֵ��������)
} PARAMER; 


// ������Ϣ������0x0F
typedef  struct  __PATIENT_INFO{
	uint8  name[32];		// �������֣������н�����
	uint8  medno[24];		// ��������ţ������н�����
	uint8  age;				// ����
	uint8  gestationalweek; // 
	uint8  gestationalday;  // >=0,<7
	uint8  gestationaltimes;// 
	uint8  indemo;			// demo
	uint8  note[150];	   // ��ע�������н�����
	// ������ʱû���õ�
	uint8  sex;				// �Ա�
	uint8  patientType ;	  // ��������
	uint16 no;				// ����
	uint8  bloodType ;		// Ѫ��--
	uint8  height;			 // ���
	uint8  weight;			 // ����
	uint8  doctor[24] ;		// ҽ�����֣������н�����
}PATIENT_INFO;


// �л�����ģʽ������0x53
typedef  struct  __PatientCTRLINFO{
	PATIENT_INFO patient;	// ����
} PatientCTRLINFO; 

typedef struct _network_configure{
	UCHAR  changeflag;
	UCHAR  CharE;
	UCHAR  enable;
	UCHAR  CharH;
	UCHAR  hwaddr[6];
	UCHAR  CharI;
	UCHAR  inet[4];
	UCHAR  CharM;
	UCHAR  mask[4];
	UCHAR  CharG;
	UCHAR  gate[4];
	UCHAR  CharP;
	UINT16 port;
	UCHAR  CharS;
	UCHAR  server[99];
}NETCFG;


typedef enum net_fetal_error{
	net_FETAL_NO_ALM,				//�ޱ��� 
	net_FHR1_TOO_HI,				//FHR1̥���ʹ���
	net_FHR1_TOO_LO,				//FHR1̥���ʹ���
	net_FHR2_TOO_HI,				//FHR2̥���ʹ���
	net_FHR2_TOO_LO,				//FHR2̥���ʹ���
	net_FHR1_LOW_SIGNAL,			//��һ̥���źŲ�
	net_FHR2_LOW_SIGNAL,			//�ڶ�̥���źŲ�
	net_FHR_ALM_LMT_ERR,			//FHR�����޴�
	net_FHR1_SENSOR_OFF,			//FHR1����������
	net_FHR2_SENSOR_OFF,			//FHR2����������
	net_TOCO_SENSOR_OFF,			//TOCO����������
	net_FM_SENSOR_OFF,				//̥�����������
	net_KEYBOARD_COMM_ERR,			//����ͨѶ��
	net_POWER_BATTERY_LOW,			//��ص�ѹ̫��
	net_PRINTER_HEAD_HOT,			//��ӡͷ����
	net_PRINTER_DOOR_NOT_CLOSED,	//��ӡ��δ��
	net_PRINTER_PAPER_OUT,			//��ӡ��ȱֽ
	net_FETAL_MAX
} net_FETAL_ERR;


typedef  struct  __FETALINFO{
	UCHAR fhr1;                 //̥����1
	UCHAR fhr2;                 //̥����2
	CHAR  toco;                 //����ѹ
	UCHAR afm;	                //�Զ�̥������
	CHAR  fm;                   //̥������ 
	UCHAR fm_mode;	            //̥��ģʽ
	UCHAR fm_count_mode;	    //̥�����ģʽ
	UCHAR fhr_high;             //̥���ʱ�������
	UCHAR fhr_low;              //̥���ʱ�������
	
	CHAR  signal;				// �ź�����
	CHAR  event;				// �¼�

	UCHAR error_code;           //�������
} FETALINFO; 

// Ѫ��
typedef enum {
	net_BLOOD_TYPE_A,			// A��Ѫ
	net_BLOOD_TYPE_B,			 // B��Ѫ
	net_BLOOD_TYPE_O,			 // O��Ѫ
	net_BLOOD_TYPE_AB,			 // AB��Ѫ
	net_BLOOD_UNKNOW				// δ֪Ѫ��
}net_BLOOD;
		
// ��������

VOID NetUdpSendTask ( UINT32 argc, void *argv );
VOID NetUdpRecvTask (UINT32 argc, void *argv );

#ifndef NETCENTER_GLOBALS
#define NET_EXT extern
#else
#define NET_EXT
#endif

#define NETWORK_CONFIG_FILE FPC_NETCFG

NET_EXT NETCFG NetConfig;

NET_EXT VOID GetHWaddr(UCHAR *HWaddr);

NET_EXT VOID NetworkSetupDialog(HANDLE hOwner);
#endif


