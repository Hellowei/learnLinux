#include "stdio.h"

#define FIELD_OFFSET(type, field)	((int)&(((type *)0)->field))
#define BOOL int
#define MAX_DATA_LEN 64
typedef struct _file_info
{
	char id[14];//20150901240000
	char name[32];
	int age;
	char other_buff[512-14-32-4];
}FILE_INFO,*P_FILE_INFO;
typedef struct _file_one_data
{
	char one_data[8];//24:00:00
	char other_buff[16-8];	
}FILE_ONE_DATA,*P_FILE_ONE_DATA;
typedef struct _file_data
{
	int index;//当前数据下标
	int count;//当前有效数据
	FILE_ONE_DATA data[MAX_DATA_LEN];	
}FILE_DATA,*P_FILE_DATA;
typedef struct _file
{
	FILE_INFO fileInfo;
	FILE_DATA fileData;
}MY_FILE,*P_MY_FILE;

int set_file_size(int fd, long size);
int WriteFileInfo(FILE* fp,FILE_INFO file_info);
int WriteFileData(FILE* fp,FILE_ONE_DATA file_data);

