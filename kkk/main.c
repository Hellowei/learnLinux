#include <stdio.h>
#include "file.h"
#include <time.h>
void get_id(char *str)
{
    time_t t;
    time (&t);
	struct tm *pTM = localtime(&t);
	sprintf(str,"%04d%02d%02d%02d%02d%02d",pTM->tm_year+1900,pTM->tm_mon+1,pTM->tm_mday,pTM->tm_hour,pTM->tm_min,pTM->tm_sec);
	return pTM;
}
void get_data(char *str)
{
    time_t t;
    time (&t);
	struct tm *pTM = localtime(&t);
	sprintf(str,"%02d:%02d:%02d",pTM->tm_hour,pTM->tm_min,pTM->tm_sec);
}
int main()
{
	FILE*	fp = fopen("data","wb+");
	/*if(fp)
		set_file_size(fileno(fp), sizeof(MY_FILE));
	else
		return 0;
	FILE_INFO file_info = {0};
	sprintf(file_info.name,"hellowei");
	file_info.age = 25;
	get_id(file_info.id);
	WriteFileInfo(fp,file_info);
	FILE_ONE_DATA file_data = {0};
	int i = 0;
	for(i = 0;i < 64; i++)
	{
		if (i%20 == 19)//更新信息头
		{	
			get_id(file_info.name);
			WriteFileInfo(fp,file_info);
		}
		//更新一个数据
		get_data(file_data.one_data);
		WriteFileData(fp, file_data);
		sleep(1);
	}*/
	 ReadFile(fp);
	return 0;
}
/*
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
}MY_FILE,*P_MY_FILE;*/