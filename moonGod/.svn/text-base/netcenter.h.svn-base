#ifndef NETCENTER_H__
#define NETCENTER_H__

#define PKG_0x0A			   0x0A		// 设备上线注册
#define PKG_0x13			0x13		// 设备网络在线标志，每5秒钟一次

#define PKG_ECG1			0x20		 // ECG1数据包, 每秒钟一次
#define PKG_ECG2			0x21		 // ECG2数据包, 每秒钟一次
#define PKG_RESP			0x22		// RESP数据包, 每秒钟一次
#define PKG_0x0C			   0x0C		// 血氧数据包，每秒钟一次
#define PKG_0x0D			   0x0D		// 血压数据包，每秒钟一次
#define PKG_0x0E			   0x0E		// 体温数据包，每秒钟一次

#define PKG_0x0F			   0x0F		// 病人类型(先发一次，以后有变化再发，无变化不需要发)

#define PKG_0x50			   0x50		// 切换ECG模式
#define PKG_0x51			   0x51		// 切换呼吸模式
#define PKG_0x52			   0x52		// 切换血氧模式
#define PKG_0x53			   0x53		// 改变病人模式
#define PKG_0x54			   0x54		// 启动/停止血压测量
#define PKG_0x55			   0x55		// 血压测量模式及周期



// 设备注册包(配置本设备的功能)，类型0x0A
typedef  struct  __PARAMERINFO{
	uint32  paramers;				// 错误代码(当erro=0时，值才有意义)
} PARAMER; 


// 病人信息，类型0x0F
typedef  struct  __PATIENT_INFO{
	uint8  name[32];		// 病人名字，必须有结束符
	uint8  medno[24];		// 病例本编号，必须有结束符
	uint8  age;				// 年龄
	uint8  gestationalweek; // 
	uint8  gestationalday;  // >=0,<7
	uint8  gestationaltimes;// 
	uint8  indemo;			// demo
	uint8  note[150];	   // 备注，必须有结束符
	// 以下暂时没有用到
	uint8  sex;				// 性别
	uint8  patientType ;	  // 病人类型
	uint16 no;				// 床号
	uint8  bloodType ;		// 血型--
	uint8  height;			 // 身高
	uint8  weight;			 // 体重
	uint8  doctor[24] ;		// 医生名字，必须有结束符
}PATIENT_INFO;


// 切换病人模式，类型0x53
typedef  struct  __PatientCTRLINFO{
	PATIENT_INFO patient;	// 病人
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
	net_FETAL_NO_ALM,				//无报警 
	net_FHR1_TOO_HI,				//FHR1胎心率过高
	net_FHR1_TOO_LO,				//FHR1胎心率过低
	net_FHR2_TOO_HI,				//FHR2胎心率过高
	net_FHR2_TOO_LO,				//FHR2胎心率过低
	net_FHR1_LOW_SIGNAL,			//第一胎心信号差
	net_FHR2_LOW_SIGNAL,			//第二胎心信号差
	net_FHR_ALM_LMT_ERR,			//FHR报警限错
	net_FHR1_SENSOR_OFF,			//FHR1传感器脱落
	net_FHR2_SENSOR_OFF,			//FHR2传感器脱落
	net_TOCO_SENSOR_OFF,			//TOCO传感器脱落
	net_FM_SENSOR_OFF,				//胎动打标器脱落
	net_KEYBOARD_COMM_ERR,			//键盘通讯错
	net_POWER_BATTERY_LOW,			//电池电压太低
	net_PRINTER_HEAD_HOT,			//打印头过热
	net_PRINTER_DOOR_NOT_CLOSED,	//打印门未关
	net_PRINTER_PAPER_OUT,			//打印机缺纸
	net_FETAL_MAX
} net_FETAL_ERR;


typedef  struct  __FETALINFO{
	UCHAR fhr1;                 //胎心率1
	UCHAR fhr2;                 //胎心率2
	CHAR  toco;                 //宫缩压
	UCHAR afm;	                //自动胎动曲线
	CHAR  fm;                   //胎动次数 
	UCHAR fm_mode;	            //胎监模式
	UCHAR fm_count_mode;	    //胎监计数模式
	UCHAR fhr_high;             //胎心率报警高限
	UCHAR fhr_low;              //胎心率报警高限
	
	CHAR  signal;				// 信号质量
	CHAR  event;				// 事件

	UCHAR error_code;           //错误代码
} FETALINFO; 

// 血型
typedef enum {
	net_BLOOD_TYPE_A,			// A型血
	net_BLOOD_TYPE_B,			 // B型血
	net_BLOOD_TYPE_O,			 // O型血
	net_BLOOD_TYPE_AB,			 // AB型血
	net_BLOOD_UNKNOW				// 未知血型
}net_BLOOD;
		
// 病人类型

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


