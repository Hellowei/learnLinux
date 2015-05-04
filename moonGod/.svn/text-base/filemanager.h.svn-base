#ifndef FILE_MANAGER_H
#define FILE_MANAGER_H

#define DATA_FOLDER		 FILEPATH_DATA
#define DATA_FILE		   FPD_FETAL
#define DATA_SAVE		   FPD_DATA
#define DATA_TEMP_LEN	   (3600 * 24)	 // 24小时
#define DATA_SAVE_LEN	   7200
#define DATA_SAVE_MAX	   300
// 文件名，固定为'A4S.data'
#define DATA_FILE_HEAD	  "A4S.data"
// 文件名，固定为'@ptndata'
#define PTNT_DATA_HEAD	  "@ptndata"
// 文件名，固定为'@f_ansis'
#define PTNT_ANSS_HEAD	  "@f_ansis"
// 文件名，固定为'@ptnifno'
#define PTNT_INFO_HEAD	  "@ptnifno"
// 
#define TABLES_HEAD		 "@tables"
#define SAVE_INFO_HEAD	  "@savinfo"
// 状态, del@已删除 sav@已保存 new@正在创建 chg@正在修改 nul@未使用
#define PTNT_INFO_DEL	   "@delete@"	  // 指向的文件/偏移已被标记为删除
#define PTNT_INFO_SAV	   "@save@@@"	  // 指向的文件/偏移已保存数据,可用
#define PTNT_INFO_NEW	   "@new@@@@"	  // 指向的文件/偏移正在创建,不可用
#define PTNT_INFO_CHG	   "@change@"	  // 指向的文件/偏移正在写入数据
#define PTNT_INFO_NUL	   "@null@@@"	  // 指向的文件/偏移为NULL,需要创建

#define CRC32_CALC_FIRST	0xffffffff

#define FILE_OK				0
#define FILE_NOT_EXIST		(-1)
#define FILE_CRC_ERROR		(-2)
#define FILE_INJURE			(-3)
#define FILE_CANNOT_DELETE	(-4)
#define FILE_CANNOT_CREATE	(-5)
#define FILE_OTHER_ERROR	(-6)

typedef int FILE_STATUS;

typedef enum _patient_information_status_index{
	PINFO_DEL,
	PINFO_SAV,
	PINFO_NEW,
	PINFO_CHG,
	PINFO_NUL,
	PINFO_MAX
}PTNT_INFO;

typedef struct _patient_info_file{
	char			name[8];	// 文件名，固定为'PTN_INFO'////@ptnifno
	short		   index;	  // 序号,与文件名一致
	short		   no;		 // 床号
	char			patientName[32];	// 必须有结束符'\0'
	char			patientID[32];	  // 必须有结束符'\0'
	char			patientAge;
	char			gestationalWeeks;   // 孕周
	char			gestationalDay;	 // 
	char			gestationalTimes;
	short		   height;			 // 身高:cm
	short		   weight;			 // 体重:kg
	char			sex;				// 性别:0 females,1 males
	char			patientType;		// 病人类型:0 adult,1 kids,0 neo
	char			bloodType;		  // 血型:0 O,1 A,2 B,3 AB
	char			reserve;
	char			note[160];		  // 备注，必须有结束符'\0'
	long			dataStart;		  // 数据起始位置
	long			createTime;		 // 创建时间
}PTNINFO_FILE, *PPTNINFO;

typedef struct {
	FETALWAVEDATA wave[4];
	UCHAR   fm;
	UCHAR   event;
	UCHAR   analysis;
	UCHAR   reserve1B;
	UINT32  time;
}FETALDATA, *PFETALDATA;

typedef struct data_save_info{
	UINT32		  index;
	UINT32		  indexchk;
	UINT32		  count;
	UINT32		  countchk;
}DATASAVEINFO;

typedef struct _fetal_data_file{
	CHAR			name[8];	// 文件名，固定为'@ptndata'
	UINT32		  index;
	DATASAVEINFO	info[2];
	FETALDATA	   data[DATA_SAVE_LEN];
}FETALDATA_FILE, *PFETALDATA_FILE;

typedef struct _fetal_temp_data{
	DATASAVEINFO	info;
	FETALDATA	   data[DATA_TEMP_LEN];
}FETAL_TD, *PFETAL_TD;


typedef struct _fetal_ansis_result{
	CHAR	name[8];	// 文件名，固定为'@f_ansis'
	UINT32  len;
	UINT32  type;
	UCHAR   buffer[1024 - 8 - 4 - 4];
}FETAL_ANSIS, *PTRANSIS;

typedef struct _patient_file{
	PTNINFO_FILE	info;
	FETAL_ANSIS	 ansis;
	FETALDATA_FILE  data;
}PATIENT_FILE, *PTRPARIENT;

typedef struct _save_info{
	char	name[8];// 
	UINT32  active;
	UINT32  checkA;
	short   index[DATA_SAVE_MAX];  // 本文件下标
}SAVEINFO, *PSAVINFO;

typedef struct _preview_tables{
	CHAR	name[7];//@tables
	CHAR	status;// 'S':save; 'D':delete; 'N' or other:new;
	CHAR	ptnName[32];
	CHAR	ptnID[32];
	//现在存储位置为/mnt/data下,一般文件路径为/mnt/data/data.xxx,占前20字节
	CHAR	fileName[32];
	// 创建时间,以数据文件为准
	UINT32  time;
}PRE_TABS;


typedef struct _save_file{
	CHAR		name[8];				// 文件名，固定为'A4S.data'
	INT32	   filelen;				// 本文件长度
	INT32	   saveNum;				// 保存病人个数 == DATA_SAVE_MAX
	SAVEINFO	sInfo;				  // 存储索引,为info排序
	PRE_TABS	info[DATA_SAVE_MAX];	// 索引数据,以具体文件为准
	SAVEINFO	backup;				 // 冗余数据,先修改sInfo,确认保存后更新
}SAVEFILE;

typedef struct _file_manager_system{
	BOOL(*Register)				(struct _file_manager_system *, const char *);
	BOOL(*UnRegister)			(struct _file_manager_system *				);
	BOOL(*RebuildSaveFile)		(struct _file_manager_system *				);
	VOID(*DeletePatient)		(struct _file_manager_system *, INT16 *, INT16);
	BOOL(*NewPatient)			(struct _file_manager_system *				);
	VOID(*PutPtnInfo)			(struct _file_manager_system *, PPTNINFO	);
	VOID(*PutData)				(struct _file_manager_system *, PFETALDATA	);
	VOID(*PutAnsis)				(struct _file_manager_system *, PTRANSIS	);
	BOOL(*ClosePtnFile)			(struct _file_manager_system *				);
	PATIENT_FILE *(*GetDataFile)(struct _file_manager_system *, INT16		);
	BOOL(*DestroyGetData)		(struct _file_manager_system *				);
	SAVEFILE *(*GetInfoFile)	(struct _file_manager_system *				);
	long(*GetSaveNum)			(struct _file_manager_system *				);
	long(*GetCurrSaveIndex)		(struct _file_manager_system *				);
}FILEMRSYS;

#ifndef FILEMANAGER_GLOBAL
#define FILE_MNGR_EXT extern
#else
#define FILE_MNGR_EXT
#endif

#ifndef BYTE_NUM_ONETIME_READ
#define BYTE_NUM_ONETIME_READ   61440
#endif

FILE_MNGR_EXT PTNINFO_FILE	  PatientInfo;
FILE_MNGR_EXT PFETAL_TD		 FetalDataPtr;

FILE_MNGR_EXT struct _file_manager_system fms;
FILE_MNGR_EXT FILEMRSYS* FmsPtr;
/*  */
FILE_MNGR_EXT BOOL InitSaveFileSystem(FILEMRSYS *this);
FILE_MNGR_EXT UCHAR *LoadSmallFile (const CHAR * name, UINT32 *len);
FILE_MNGR_EXT BOOL FileManagerRegister(FILEMRSYS *this);
FILE_MNGR_EXT BOOL CheckFileExist(const char * filename);
FILE_MNGR_EXT VOID flush(FILE *stream);

#endif

