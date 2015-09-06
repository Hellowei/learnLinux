#include "file.h"

BOOL set_file_size(int fd, long size)
{
	if (fd < 0)
	{
		return 0;
	}
	
	if (size > 0)
	{
		short buf = 0;
		long b = lseek(fd, size - 1, SEEK_SET);
		write(fd, &buf, 1);
		buf = dup(fd);
		close(buf);
		fsync(fd);
		return 1;
	}
	
	return 0;
}
int WriteFileInfo(FILE* fp,FILE_INFO file_info)
{
	if (fp)
	{
		fseek(fp, FIELD_OFFSET(MY_FILE, fileInfo), SEEK_SET);//从文件头开始 把文件定位到FIELD_OFFSET(MY_FILE, fileInfo)
		fwrite(&file_info, sizeof(FILE_INFO), 1, fp);//写文件到缓存
		fflush(fp);//缓存同步到文件上
	}
}
int WriteFileData(FILE* fp,FILE_ONE_DATA file_data)
{
	if (fp)
	{
		fseek(fp, FIELD_OFFSET(MY_FILE, fileData), SEEK_SET);
		int index,count;
		fread(&index,sizeof(int),1,fp);//读出来后位置指针后移了
		fread(&count,sizeof(int),1,fp);
		printf("cur index is %d count=%d\n",index,count);
		fseek(fp,sizeof(FILE_ONE_DATA)*index, SEEK_CUR);
		fwrite(&file_data, sizeof(FILE_ONE_DATA), 1, fp);//写文件到缓存
		fflush(fp);//缓存同步到文件上
		//
		if(++count > MAX_DATA_LEN)
			count = MAX_DATA_LEN;
		index = (index+1)%MAX_DATA_LEN;
		fseek(fp, FIELD_OFFSET(MY_FILE, fileData), SEEK_SET);
		fwrite(&index, sizeof(int), 1, fp);//更新下标
		fwrite(&count, sizeof(int), 1, fp);//更新总数
		fflush(fp);//缓存同步到文件上
	}
}

int ReadFile(FILE* fp)
{
	MY_FILE myFile;
	fseek(fp, 0, SEEK_SET);
	fread(&myFile,sizeof(MY_FILE),1,fp);
	printf("info %s %s %d\n",myFile.fileInfo.id,myFile.fileInfo.name,myFile.fileInfo.age);
	sleep(2);
	printf("index %d count %d\n",myFile.fileData.index,myFile.fileData.count);
	sleep(1);
	int i = 0;
	for(i = 0;i < MAX_DATA_LEN; i++)
		printf("%s\n",myFile.fileData.data[(myFile.fileData.index+i)%MAX_DATA_LEN].one_data);

}
	
