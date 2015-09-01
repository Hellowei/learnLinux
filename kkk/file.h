#include "stdio.h"

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
}FILE_DATA,*P_FILE_DATA;

int set_file_size(int fd, long size);


