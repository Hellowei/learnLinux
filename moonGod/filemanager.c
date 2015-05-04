#define FILEMANAGER_GLOBAL
#include "includes.h"
#include <fcntl.h>
#include <sys/statfs.h>
#include <dirent.h>
#include <sys/mman.h>
#include <errno.h>

#if 0
// 32位crc
static unsigned int crc_table[256];
/*
**初始化crc表,生成32位大小的crc表
*/
static void init_crc32_table(void)
{
	unsigned int c;
	unsigned int i, j;
	for (i = 0; i < 256; i++)
	{
		c = (unsigned int)i;
		for (j = 0; j < 8; j++)
		{
			if (c & 1)
				c = 0xedb88320L ^ (c >> 1);
			else
				c = c >> 1;
		}
		crc_table[i] = c;
	}
}

/*计算buffer的crc校验码*/
static unsigned int crc32(unsigned int crc,unsigned char *buffer, unsigned int size)
{
	unsigned int i;
	for (i = 0; i < size; i++)
	{
		crc = crc_table[(crc ^ buffer[i]) & 0xff] ^ (crc >> 8);
	}
	return crc ;
}

#define CHK_CRC32(buf, crc, TYPE) (((TYPE*)buf)->crc == crc32(crc, buf, \
									sizeof(TYPE) - sizeof(((TYPE*)buf)->crc)))

#endif

//检查DATA_FOLDER文件夹可存储空间
INT32 GetDataFileStat(CHAR unit)
{
	struct statfs folderStat;
	if (statfs(DATA_FOLDER, &folderStat))
	{
		return 0;
	}
	switch (unit)
	{
		case 'K':   // KB
		case 'k':   // KB
			return (folderStat.f_bavail * folderStat.f_bsize / 1024);

		case 'M':   // MB
		case 'm':   // MB
			return (folderStat.f_bavail * folderStat.f_bsize / (1024 * 1024));

		default:	// total size byte
			return (folderStat.f_blocks * folderStat.f_bsize);
	}
}

INT32 GetUsbBlockStat(CHAR unit)
{
	struct statfs folderStat;
	if (statfs("/mnt/disk", &folderStat))
	{
		return 0;
	}
	switch (unit)
	{
		case 'K':   // KB
		case 'k':   // KB
			return (folderStat.f_bavail * folderStat.f_bsize / 1024);

		case 'M':   // MB
		case 'm':   // MB
			return (folderStat.f_bavail * folderStat.f_bsize / (1024 * 1024));

		default:	// total size byte
			return (folderStat.f_blocks * folderStat.f_bsize);
	}
}

static VOID CloseFlushFile(FILE *stream)
{
	if (fclose(stream))
		perror("close file error");
}

BOOL CheckFileExist(const char * filename)
{
	FILE * fp;
	BOOL ret = FALSE;
	
	fp = fopen(filename, "r");//以只读方式打开文件。

	ret = (fp != NULL);

	if (ret)
		CloseFlushFile(fp);

	return ret;
}

VOID flush(FILE *stream)
{
   INT16 duphandle;
   /* flush BC's internal buffer */
   fflush(stream);
   /* make a duplicate file handle */
   duphandle = dup(fileno(stream));
   /* close the duplicate handle to flush the DOS buffer */
   close(duphandle);
   fsync(fileno(stream));
}


VOID CleanFolder(char *path)
{
	DIR *pDir;
	struct dirent *entry;
	char filepath[128];

	//去掉多余的'/'
	while (*(path + strlen(path) - 2) == '/')
		*(path + strlen(path) - 2) = '\0';
	//打开文件夹
	if ((pDir = opendir(path)) != NULL)
	{
		while(entry = readdir(pDir))
		{
			if (0 == strcmp(entry->d_name, "." )) continue;
			if (0 == strcmp(entry->d_name, "..")) continue;
			sprintf(filepath, "%s/%s", path, entry->d_name);
			if(remove(filepath))
			{
				printf ("delete file %s\n", path);
				perror ("del err");
			}
		}
		closedir(pDir);
	}
}

INT32 get_file_size(FILE * fp)
{
  struct stat statbuf;  
  fstat(fileno(fp), &statbuf);
  return statbuf.st_size;
}

BOOL set_file_size(int fd, long size)
{
	if (fd < 0)
	{
		return FALSE;
	}
	
	if (size > 0)
	{
		short buf = 0;
		long offset;
		offset = lseek(fd, 0, SEEK_CUR);
		lseek(fd, size - 1, SEEK_SET);
		read(fd, &buf, 1);
		lseek(fd, size - 1, SEEK_SET);
		write(fd, &buf, 1);
		if (offset > 0)
		{
			lseek(fd, offset, SEEK_SET);
		}
		else
		{
			lseek(fd, 0, SEEK_SET);
		}
		buf = dup(fd);
		close(buf);
		fsync(fd);
		return TRUE;
	}
	
	return FALSE;
}

BOOL SetFileSize(FILE * fp, INT32 size)
{
	if (fp == NULL)
	{
		return FALSE;
	}
	
	return set_file_size(fileno(fp), size);
}


/**
*  根据输入的文件名,分配足够的内存,并把数据读入;
*  返回分配的内存地址;
*  文件不能过大,否则不能分配足够的内存空间
**/
#define SMALL_FILE_MAX_SIZE (1024 * 1024) // 1M
UCHAR *LoadSmallFile (const CHAR * name, UINT32 *len)
{
	FILE	*fp;
	UCHAR   *memP;
	//一次性分配所有内存，从文件读取所有数据；
	UCHAR   *p;
	long	 sum;
	long	 status;
	long	 loop, remain, to_read;
	int	  i;
	
	memP = NULL;
	p	= NULL;
	*len = 0;
	if (fp = fopen(name, "rb"))
	{ // 打开文件成功
		*len = get_file_size(fp);
		if (*len  > SMALL_FILE_MAX_SIZE)
		{
			return memP;
		}
		memP   = (UCHAR*)malloc(*len);
		p	  = memP;
		if (p)
		{
			if (status = fseek(fp, 0, SEEK_SET))
			{
				return memP;
			}
			loop	= *len / BYTE_NUM_ONETIME_READ;
			remain  = *len % BYTE_NUM_ONETIME_READ;
			to_read = BYTE_NUM_ONETIME_READ;
			sum	 = 0;

			for (i = 0; i < loop; i++)
			{
				status = fread(p, sizeof(char), to_read, fp);
				sum += status;
				p += to_read; 
			}
			to_read = remain;
			if (to_read > 0)
			{
				status = fread(p, sizeof(char), to_read, fp);
				sum += status;			 
			}
			if (*len != sum)
			{ // 读入的数据和要求的不符,出错
				free(memP);	 // 释放内存
				memP = NULL;	// 返回空指针,表示失败
			}
		}
		fclose(fp);	
	}
	return memP;  /* 返回指针. */
}


/**
*  根据输入的文件名和长度,分配指定长度的内存,并把数据读入;
*  返回分配的内存地址;
**/
UCHAR *LoadFileEx (const UCHAR * name, UINT32 len)
{
	FILE	*fp;
	UCHAR   *memP;
	UCHAR   *p;
	long	 sum;
	long	 status;
	long	 loop, remain, to_read;
	int	  i;
	
	memP = NULL;
	p	= NULL;
	if (fp = fopen(name, "rb"))
	{ // 打开文件成功
		memP   = (UCHAR*)malloc(len);
		p	  = memP;
		if (p)
		{
			if (status = fseek(fp, 0, SEEK_SET))
			{
				return memP;
			}
			loop	= len / BYTE_NUM_ONETIME_READ;
			remain  = len % BYTE_NUM_ONETIME_READ;
			to_read = BYTE_NUM_ONETIME_READ;
			sum	 = 0;

			for (i = 0; i < loop; i++)
			{
				status = fread(p, sizeof(char), to_read, fp);
				sum += status;
				p += to_read; 
			}
			to_read = remain;
			if (to_read > 0)
			{
				status = fread(p, sizeof(char), to_read, fp);
				sum += status;			 
			}
			if (len != sum)
			{ // 读入的数据和要求的不符,出错
				free(memP);	 // 释放内存
				memP = NULL;	// 返回空指针,表示失败
			}
		}
		fclose(fp);	
	}
	return memP;  /* 返回指针. */
}



#if 0//_ENB_FILE_SYSTEM > 0
/* 以下为文件管理模块私有函数 */
#define ACTIVE_MASK		 (MAKELPARAM2('A', 'c', 't', '.'))
#define CHECKA_MASK		 (~(ACTIVE_MASK))
#define CHECK_PROC(a, c)	( ( a | c ) == 0xFFFFFFFF && ( a & c ) == 0 )

// 文件管理模块私有数据
typedef struct __tagFMSDATA{
	CHAIN_NODE  node;
	FILEMRSYS  *this;
	SAVEFILE   *save;
	CHAR	   *filename;
	INT32	   curr;
}FMSDATA;

static UCHAR sPtnInfoStr[5][8];
static FMSDATA thisData;

#if UNUSED
static VOID ShowMapFile(FILEMRSYS *this)
{
	printf("ShowMapFile::show %s\n", this->filename);
	UCHAR *p;
	int i, j, k;
	k = 0;
	p = (UCHAR*)this->savefile;
	for (i = 0; i < (this->filelen + 15) / 16; i++)
	{
		printf("%08x: ", k);
		for (j = 0; j < 16; j++)
		{
			if (j % 4 == 0)
			{
				printf(" ");
			}
			printf("%02x ", *p++);
			k++;
			if (k == this->filelen)
			{
				printf("\n");
				return;
			}
		}
		printf("\n");
		if (i > 64)
			break;
	}
}

static INT32 GetSaveFileSize(FILEMRSYS *this)
{
	return get_file_size(this->fp);
}

static BOOL SetSaveFileSize(FILEMRSYS *this)
{
	this->filelen = GetSaveFileSize(this);
	prinfo("this->filelen is %d(%dK)\r\n", this->filelen, this->filelen / 1024);
	fseek(this->fp, FIELD_OFFSET(SAVEFILE, filelen), SEEK_SET);
	if (sizeof(this->filelen) > 
		fwrite(&this->filelen, 1, sizeof(this->filelen), this->fp))
	{
		perror("SetSaveFileSize error");
		return FALSE;
	}
	return TRUE;
}

static VOID MapSaveFile(FILEMRSYS *this)
{
	if (this->savefile || !this->fp 
		|| this->filelen < FIELD_OFFSET(SAVEFILE, sFile[0]))
	{
		return;
	}
	// 仅用于快速浏览文件,不修改文件
	this->savefile = (SAVEFILE*)mmap(NULL, this->filelen, PROT_READ,
										MAP_PRIVATE, fileno(this->fp), 0);
	if (-1 == (INT32)this->savefile)
	{
		perror("fail to map savefile");
	}
}

static BOOL UnMapSaveFile(FILEMRSYS *this)
{
	if (!this->savefile || this->filelen < FIELD_OFFSET(SAVEFILE, sFile[0]))
	{
		return FALSE;
	}
	if (munmap(this->savefile, this->filelen) == -1)
	{
		perror("fail to munmap savefile");
		return FALSE;
	}
	this->savefile = NULL;
	return TRUE;
}
#endif

static BOOL SetSaveCurrPatientStatus(FILEMRSYS *this, const UCHAR *stat)
{
	UCHAR status_str[4];
	if (!this->fp || this->infoCur < 0)
	{
		return FALSE;
	}
	memcpy(status_str, stat, 4);
	fseek(this->fp, FIELD_OFFSET(SAVEFILE, sInfo[this->infoCur]), SEEK_SET);
	if (sizeof(status_str) > fwrite(status_str, 1, sizeof(status_str), this->fp))
	{
		perror("Set Save Curr Patient Status error");
		return FALSE;
	}
	flush(this->fp);
	fseek(this->fp, FIELD_OFFSET(SAVEFILE, backup[0]), SEEK_SET);
	if (sizeof(status_str) > fwrite(this->savefile->sInfo, sizeof(SAVEINFO), 
		DATA_SAVE_MAX, this->fp))
	{
		perror("Save backup error");
	}
	return TRUE;
}

static INT32 GetNewPatientIndex(FILEMRSYS *this, BOOL delOldfile)
{
	int i;
	int index;
	PSAVINFO pInfo;
	pInfo = this->savefile->sInfo;

	for(i = 0; i < this->infoNum; i++)
	{
		if (memcmp(pInfo->name, sPtnInfoStr[PINFO_SAV],
			sizeof(sPtnInfoStr[PINFO_SAV])))
		{
			printf("GetNewPatientIndex......%d\n", i);
			return i;
		}
		pInfo++;
	}
	if (delOldfile)
	{
		this->DeletePatient(this, this->infoNum - 1);
		return GetNewPatientIndex(this, FALSE);
	}
	return -1;
}


/*****************************************************************************************
* Function	: CreateNewSaveFile
* Description : 这里创建两个文件,一个是信息文件fetal.bin,一个是数据文件data.000
				data.000是默认储存文件,自动存档
* Input Para  : 
* Output Para : 
* Return Value: 
*****************************************************************************************/
static BOOL CreateNewSaveFile(FILEMRSYS *this)
{
	UCHAR name[8], end = 0;
	INT32 len;
	INT32 num;
	SAVEINFO info;
	PRE_TABS ptninfo;
	int i, fd;
	
	i = creat(this->filename, 0664);
	
	if (i < 0)
	{
		printf("CreateNewSaveFile::create file error\n");
		return FALSE;
	}
	
	lseek(i, sizeof(SAVEFILE) - 1, SEEK_SET);
	write(i, &end, 1);
	close(i);
	
	this->fp = fopen(this->filename, "rb+");
	if (!this->fp)
	{
		printf("CreateNewSaveFile::open file error\n");
		return FALSE;
	}
	
	this->filelen = sizeof(SAVEFILE);

	len = this->filelen;
	num = this->infoNum;
	
	memcpy(name, DATA_FILE_HEAD, strlen(DATA_FILE_HEAD));
	
	fseek(this->fp, 0, SEEK_SET);
	
	if (sizeof(name) > fwrite(name, 1, sizeof(name), this->fp))
	{
		printf("CreateNewSaveFile::write file error:DATA_FILE_HEAD\n");
		return FALSE;
	}
	
	if (sizeof(len) > fwrite((UCHAR*)&len, 1, sizeof(len), this->fp))
	{
		printf("CreateNewSaveFile::write file error:len\n");
		return FALSE;
	}
	
	if (sizeof(num) > fwrite((UCHAR*)&num, 1, sizeof(num), this->fp))
	{
		printf("CreateNewSaveFile::write file error:num\n");
		return FALSE;
	}
	
	memcpy(info.name, sPtnInfoStr[PINFO_SAV], sizeof(sPtnInfoStr[PINFO_SAV]));
	
	info.active = ACTIVE_MASK;
	info.checkA = CHECKA_MASK;
	
	for (i = 0; i < num; i++)
	{
		info.index[i] = i + 1;
	}
	
	if (sizeof(info) > fwrite((UCHAR*)&info, sizeof(SAVEINFO), 1, this->fp))
	{
		printf("CreateNewSaveFile::write file error:info\n");
		return FALSE;
	}

	ZeroMemory(&ptninfo, sizeof(ptninfo));
	
	memcpy(ptninfo.name, PTNT_INFO_DEL, sizeof(ptninfo.name));
	
	memcpy(name, PTNT_INFO_HEAD, sizeof(name));
	
	end = 0;
	
	for (i = 1; i <= num; i++)
	{
		sprintf(ptninfo.fileName, "%s%03d", DATA_SAVE, i);
		fd = open(ptninfo.fileName, O_RDWR | O_CREATE);
		if (fd >= 0)
		{
			write(fd, name, sizeof(name));
			lseek(fd, sizeof(PATIENT_FILE) - 1, SEEK_SET);
			write(fd, &end, 1);
			close(fd);
			ptninfo.exist = 1;
			ptninfo.active = 1;
		}
		else
		{
			ptninfo.exist = 0;
			ptninfo.active = 0;
		}
		if (sizeof(ptninfo) > 
			fwrite((UCHAR*)&ptninfo, sizeof(ptninfo), 1, this->fp))
		{
			printf("CreateNewSaveFile::write file error:ptninfo\n");
			return FALSE;
		}
	}
	flush(this->fp);

	if (sizeof(info) > fwrite((UCHAR*)&info, sizeof(SAVEINFO), 1, this->fp))
	{
		printf("CreateNewSaveFile::write file error:info\n");
		return FALSE;
	}
	
	fclose(this->fp);
	this->fp = NULL;
	
	this->savefile = (SAVEFILE*)LoadSmallFile(this->filename, sizeof(SAVEFILE));
	if (!(this->savefile))
	{
		printf("read file error!\r\n");
		return FALSE;
	}
	
	return TRUE;
}

static BOOL GetSaveFile(FILEMRSYS *this)
{
	if (this->savefile)
	{
		free (this->savefile);
		this->savefile = NULL;
	}
	this->savefile = (SAVEFILE*)LoadSmallFile(this->filename, sizeof(SAVEFILE));
	if (this->savefile)
	{
		if (memcmp(this->savefile->name, DATA_FILE_HEAD, strlen(DATA_FILE_HEAD)))
		{
			printf("ReadSaveFile::DATA_FILE_HEAD error\n");
			return FALSE;
		}
		this->filelen = this->savefile->filelen;
		this->infoNum = this->savefile->saveNum;
		return TRUE;
	}
	return FALSE;
}


static INT32 CheckSaveFile(FILEMRSYS *this)
{
	PFETALDATA_FILE pData;
	PSAVINFO	pSaveInfo = this->savefile->sInfo;
	PTRPARIENT  pPnt;
	INT32	   loops = this->infoNum;
	INT32	   count = 0;
	INT32	   curr = this->infoCur;
	INT32	   i;

	if (memcmp(pSaveInfo->name, sPtnInfoStr[PINFO_SAV], 
		sizeof(sPtnInfoStr[PINFO_SAV])) == 0)

	for (i = 0; i < loops; i++)
	{
		if (memcmp(pSaveInfo->name, sPtnInfoStr[PINFO_SAV],
			sizeof(sPtnInfoStr[PINFO_SAV])) == 0)
		{
			count++;
		}
		else
		if (memcmp(pSaveInfo->name, sPtnInfoStr[PINFO_CHG],
			sizeof(sPtnInfoStr[PINFO_CHG])) == 0)
		{
			pPnt = (PTRPARIENT)(((UCHAR*)this->savefile) + pSaveInfo->offset);
			if((memcmp(pPnt->info.name, PTNT_INFO_HEAD, strlen(PTNT_INFO_HEAD)))
			|| (memcmp(pPnt->ansis.name, PTNT_ANSS_HEAD, strlen(PTNT_ANSS_HEAD)))
			|| (memcmp(pPnt->data.name, PTNT_DATA_HEAD, strlen(PTNT_DATA_HEAD)))
			)
			{
				// 头信息不符，设置该记录为空
				this->infoCur = i;
				SetSaveCurrPatientStatus(this, sPtnInfoStr[PINFO_NUL]);
				this->infoCur = curr;
			}
			else
			{
				pData = &pPnt->data;
				
				if (	(pData->info[0].countchk == 
							compute_checksum(pData->info[0].count))
					  &&(pData->info[0].indexchk == 
							compute_checksum(pData->info[0].index))	 )
				{
					count++;
				}
				else
					if ((pData->info[1].countchk == 
							compute_checksum(pData->info[1].count))
					  &&(pData->info[1].indexchk == 
							compute_checksum(pData->info[1].index))	 )
				{
					INT32 offset = (UCHAR*)pData->info - (UCHAR*)this->savefile;
					ENTER_FILE_OP();

					fseek(this->fp, offset, SEEK_SET);
					fwrite(&pData->info[1], 1, sizeof(DATASAVEINFO), this->fp);
					count++;
				}
				else
				{
					// 保存数据错误，删除该记录
					this->DeletePatient(this, i);
				}
			}
		}
		pSaveInfo++;
	}
	return count;
}


/*******************************************************************************
* Function	: DefragSaveFileInfo
* Description : 整理数据文件索引信息,删除病人后使用
* Input Para  : 
* Output Para : 
* Return Value: 
*******************************************************************************/
static FILE_STATUS DefragSaveFileInfo(FILEMRSYS *this)
{
	PSAVINFO buffer;
	PSAVINFO pNext;
	PSAVINFO pTmp;
	SAVEINFO Info;
	INT32	len;
	INT32	cnt;
	INT32	i;
	INT32	j;
	len = sizeof(SAVEINFO) * this->infoNum;
	buffer = (PSAVINFO)malloc(len * 2);
	if (!buffer)
	{
		perror("DefragSaveFileInfo malloc");
		return FILE_OTHER_ERROR;
	}
	pNext = buffer;
	pTmp = buffer + this->infoNum;
	memcpy(pTmp, this->savefile->sInfo, len);
	cnt = 0;
	for(i = 0; i < this->infoNum; i++)
	{
		if (0 == memcmp(pTmp->name, sPtnInfoStr[PINFO_SAV],
									sizeof(sPtnInfoStr[PINFO_SAV])))
		{
			memcpy(pNext++, pTmp, sizeof(SAVEINFO));
			cnt++;
		}
		pTmp++;
	}
	pTmp = buffer + this->infoNum;
	for(i = 0; i < this->infoNum; i++)
	{
		if (0 != memcmp(pTmp->name, sPtnInfoStr[PINFO_SAV],
									sizeof(sPtnInfoStr[PINFO_SAV])))
		{
			memcpy(pNext++, pTmp, sizeof(SAVEINFO));
		}
		pTmp++;
	}

	ENTER_FILE_OP();
	
	fseek(this->fp, FIELD_OFFSET(SAVEFILE, sInfo[0]), SEEK_SET);
	if (len > fwrite(buffer, 1, len, this->fp))
	{
		perror("DefragSaveFileInfo write file");
	}
	flush(this->fp);
	
	EXIT_FILE_OP();
	
	free(buffer);

	this->infoUse = cnt;
}

static BOOL CreateNewPatientFile(FILEMRSYS *this)
{
	PSAVINFO	pInfo;
	UCHAR	  *buffer;
	PTRPARIENT  p;
	
	if (this->infoFlag == FALSE || this->savefile == NULL || this->dataFlag == TRUE)
	{
		prinfo("this->infoFlag...%d\n", this->infoFlag);
		prinfo("this->savefile...%d\n", this->savefile);
		prinfo("this->dataFlag...%d\n", this->dataFlag);
		return FALSE;
	}
	if (this->infoCur >= 0)
	{
		return FALSE;
	}
	
	buffer = (UCHAR*)malloc(sizeof(PATIENT_FILE));
	if (!buffer)
	{
		return FALSE;
	}
	ZeroMemory(buffer, sizeof(PATIENT_FILE));
	p = (PTRPARIENT)buffer;
	
	this->infoCur = GetNewPatientIndex(this, TRUE);
	pInfo = &(this->savefile->sInfo[this->infoCur]);
	prinfo("pInfo::%c%c%c%c, 0x%X\r\n", pInfo->name[0], pInfo->name[1],
						pInfo->name[2], pInfo->name[3], pInfo->offset);
	//# PTNT_INFO_NUL
	if (memcmp(pInfo->name, sPtnInfoStr[PINFO_NUL],
		sizeof(sPtnInfoStr[PINFO_NUL])) == 0)
	{
		if (pInfo->offset > this->filelen)
		{
			// 文件太小,fseek无法执行,需要增大文件体积
			// 解除内存映射后pInfo不再可用,需先保存偏移量
			INT32 offset = pInfo->offset;

			ENTER_FILE_OP();
			
			UnMapSaveFile(this);
			SetSaveCurrPatientStatus(this, sPtnInfoStr[PINFO_NEW]);
			fseek(this->fp, 0, SEEK_END);
			while (GetSaveFileSize(this) < offset)
			{
				if (sizeof(PATIENT_FILE) >
					fwrite(p, 1, sizeof(PATIENT_FILE), this->fp))
				{
					printf("CreateNewSaveFile::write file error:patient\n");
					break;
				}
			}
			flush(this->fp);
			SetSaveFileSize(this);
			MapSaveFile(this);
			
			EXIT_FILE_OP();
			
			pInfo = &(this->savefile->sInfo[this->infoCur]);
			prinfo("pInfo::%c%c%c%c, 0x%X\r\n", pInfo->name[0], pInfo->name[1],
								pInfo->name[2], pInfo->name[3], pInfo->offset);
		}
		if (this->infoUse < this->infoNum)
		{
			this->infoUse++;
		}
	}

	if (fseek(this->fp, pInfo->offset, SEEK_SET))
	{
		free(buffer);
		return FALSE;
	}
	prinfo(" &info...%p\r\n", &(this->savefile->sInfo[this->infoCur]));
	memcpy(p->info.name,  PTNT_INFO_HEAD, sizeof(p->info.name));
//	memcpy(p->ansis.name, PTNT_ANSS_HEAD, sizeof(p->ansis.name));
//	memcpy(p->data.name,  PTNT_DATA_HEAD, sizeof(p->info.name));
//	p->info.year	= DateTime.year;
//	p->info.month   = DateTime.month;
//	p->info.day	 = DateTime.day;
//	p->info.hour	= DateTime.hour;
//	p->info.minute  = DateTime.minute;
//	p->info.second  = DateTime.second;
	ENTER_FILE_OP();
	
	if (sizeof(PATIENT_FILE) > fwrite(p, 1, sizeof(PATIENT_FILE), this->fp))
	{
		printf("CreateNewSaveFile::write file error:patient\n");
		free(buffer);
		return FALSE;
	}
	SetSaveCurrPatientStatus(this, sPtnInfoStr[PINFO_CHG]);
	flush(this->fp);
	
	UnMapSaveFile(this);
	SetSaveFileSize(this);
	MapSaveFile(this);
	
	EXIT_FILE_OP();

	free(buffer);
	return TRUE;
}

static VOID ChangePatientInformation(FILEMRSYS *this, PPTNINFO pInfo)
{
	UCHAR tmpname[4] = {0};
	// 只允许修改当前病人信息,不是当前病人不允许修改
	if (this->infoCur < 0)
		return;
	if (memcmp(this->savefile->sInfo[this->infoCur].name,
		sPtnInfoStr[PINFO_CHG], sizeof(sPtnInfoStr[PINFO_CHG])))
	{
		memcpy(tmpname, this->savefile->sInfo[this->infoCur].name, sizeof(tmpname));
		SetSaveCurrPatientStatus(this, sPtnInfoStr[PINFO_CHG]);
	}
	memcpy(pInfo->name,  PTNT_INFO_HEAD, sizeof(pInfo->name));
	PPTNINFO p = (PPTNINFO)((UCHAR*)(this->savefile)
								+ this->savefile->sInfo[this->infoCur].offset);
//	pInfo->hour = p->hour;
//	pInfo->minute = p->minute;
//	pInfo->second = p->second;
//	pInfo->month = p->month;
//	pInfo->day = p->day;
//	pInfo->year = p->year;
	fseek(this->fp, this->savefile->sInfo[this->infoCur].offset, SEEK_SET);
	if (sizeof(PTNINFO_FILE) > fwrite(pInfo, 1, sizeof(PTNINFO_FILE), this->fp))
	{
		perror("ChangePatientInformation");
	}
	if (tmpname[0])
	{
		SetSaveCurrPatientStatus(this, tmpname);
	}
	flush(this->fp);
}

static VOID WriteSaveFileData(FILEMRSYS *this, PFETALDATA pData)
{
	if (this->fp && this->infoCur >= 0)
	{
		INT32 offset, offset2;
		INT32 index, count;
		DATASAVEINFO info;
		offset = this->savefile->sInfo[this->infoCur].offset;
//		offset += FIELD_OFFSET(PATIENT_FILE, data);
//		index = this->savefile->sFile[this->infoCur].data.info[0].index;
//		count = this->savefile->sFile[this->infoCur].data.info[0].count;
//		prinfo("this(%p)->infoCur...%d, &fms...%p\r\n", this, this->infoCur, &fms);
		if (count == index)
			count++;
		if (++index >= DATA_SAVE_LEN)
		{
			index = 0;
		}
		if (count < DATA_SAVE_LEN)
		{
			count ++;
		}
		else
		{
			count = DATA_SAVE_LEN;
		}
//		info.time	 = DateTime;
		info.count	= count;
		info.countchk = compute_checksum(count);
		info.index	= index;
		info.indexchk = compute_checksum(index);
		
		ENTER_FILE_OP();

		// 写入数据
		offset2 = offset + FIELD_OFFSET(FETALDATA_FILE, data[index]);
		fseek(this->fp, offset2, SEEK_SET);

		if (sizeof(FETALDATA) > fwrite(pData, 1, sizeof(FETALDATA), this->fp))
		{
			prinfo("Can not write,offset2...%d\r\n", offset2);
		}

		// 写入索引
		offset2 = offset + FIELD_OFFSET(FETALDATA_FILE, info[1]);
		fseek(this->fp, offset2, SEEK_SET);
//		prinfo("write,offset, offset2...%d, %d\r\n", offset, offset2);
//		DATASAVEINFO *pinfo = &(this->savefile->sFile[this->infoCur].data.info[0]);
//		prinfo("pinfo::index, count, time...%d, %d, %02d:%02d:%02d\r\n",
//				pinfo->index, pinfo->count,
//				pinfo->time.hour, pinfo->time.minute, pinfo->time.second);
		if (sizeof(DATASAVEINFO) > fwrite
			(&info, 1, sizeof(DATASAVEINFO), this->fp))
//			(&(this->savefile->sFile[this->infoCur].data.info[0]), 1,
//				sizeof(DATASAVEINFO), this->fp))
		{
			prinfo("Can not write,offset2...%d\r\n", offset2);
		}
		offset2 = offset + FIELD_OFFSET(FETALDATA_FILE, info[0]);
//		prinfo("write,offset, offset2...%d, %d\r\n", offset, offset2);
//		prinfo("pinfo - this->savefile == %d\r\n", (UCHAR*)pinfo - (UCHAR*)this->savefile);
		fseek(this->fp, offset2, SEEK_SET);
//		fseek(this->fp, -2 * sizeof(DATASAVEINFO), SEEK_CUR);
		if (sizeof(DATASAVEINFO) > fwrite
			(&info, 1, sizeof(DATASAVEINFO), this->fp))
		{
			prinfo("Can not write,offset2...%d\r\n", offset2);
		}
		flush(this->fp);
		
		EXIT_FILE_OP();
	}
}

static VOID WriteSaveFileAnsis(FILEMRSYS *this, UCHAR *pAnsis)
{
	if (this->fp && this->infoCur > 0)
	{
		INT32 offset;
		INT32 index, count;
		DATASAVEINFO info;
		offset = this->savefile->sInfo[this->infoCur].offset;
//		offset += FIELD_OFFSET(PATIENT_FILE, ansis);
		
		ENTER_FILE_OP();

		// 写入数据
		fseek(this->fp, offset, SEEK_SET);
		fwrite(PTNT_ANSS_HEAD, 1, strlen(PTNT_ANSS_HEAD), this->fp);
		fwrite(pAnsis, 1, 1024-8, this->fp);
		flush(this->fp);
		
		EXIT_FILE_OP();
	}
}


static BOOL CloseCurrUserFile(FILEMRSYS *this)
{
	if (!this->fp)
	{
		return FALSE;
	}
	//ShowMapFile(this);
	if (this->infoCur >= 0)
	{
		BOOL ret;
		ret = SetSaveCurrPatientStatus(this, sPtnInfoStr[PINFO_SAV]);
	}
	flush(this->fp);
	this->infoCur = -1;//GetNewPatientIndex(this, TRUE);
	return TRUE;
}

// index 为saveinfo序号
static VOID DeleteSavePatient(FILEMRSYS *this, INT16 index)
{
	INT16 cur = this->infoCur;
	INT32 offset = 0;
	if (cur >= 0)
	{
		offset = this->savefile->sInfo[cur].offset;
	}
	this->infoCur = index;
	SetSaveCurrPatientStatus(this, sPtnInfoStr[PINFO_NUL]);
	if (offset)
	{
		int i;
		for (i = 0; i < this->infoNum; i++)
		{
			if (offset == this->savefile->sInfo[i].offset)
			{
				this->infoCur = i;
				break;
			}
		}
	}
	DefragSaveFileInfo(this);
}

/* 文件管理模块初始化函数 */
BOOL InitSaveFileSystem(FILEMRSYS *this, const char *filename)
{
	if (GetDataFileStat('M') == 0) // 磁盘写满
	{
		printf("The disk may be full or write protected!!\n");
		return FALSE;
	}
	else
	{
		this->filename = (char*)filename;
		this->dataFlag = FALSE;
		this->infoFlag = FALSE;
		this->infoNum  = DATA_SAVE_MAX;
		this->infoUse  = 0;
		this->infoRec  = -1;
		this->infoCur  = -1;
		this->savefile = NULL;
		memcpy(sPtnInfoStr[PINFO_DEL], PTNT_INFO_DEL, sizeof(sPtnInfoStr[0]));
		memcpy(sPtnInfoStr[PINFO_SAV], PTNT_INFO_SAV, sizeof(sPtnInfoStr[0]));
		memcpy(sPtnInfoStr[PINFO_NEW], PTNT_INFO_NEW, sizeof(sPtnInfoStr[0]));
		memcpy(sPtnInfoStr[PINFO_CHG], PTNT_INFO_CHG, sizeof(sPtnInfoStr[0]));
		memcpy(sPtnInfoStr[PINFO_NUL], PTNT_INFO_NUL, sizeof(sPtnInfoStr[0]));
		if (!CheckFileExist(this->filename))
		{
			if (TRUE == (this->infoFlag = CreateNewSaveFile(this)))
			{
				MapSaveFile(this);
			}
		}
		else
		{
			this->infoFlag = GetSaveFile(this);
			this->infoUse  = CheckSaveFile(this);
		}
//		ShowMapFile(this);
		return this->infoFlag;
	}
}

struct _file_manager_system fms = {
	NULL, NULL, 0, FALSE, FALSE, DATA_SAVE_MAX, 0, -1, -1, NULL,
	DeleteSavePatient,  CreateNewPatientFile,   ChangePatientInformation,
	WriteSaveFileData,  WriteSaveFileAnsis,	 CloseCurrUserFile
};
#else
/* 以下为文件管理模块私有函数 */
#define ACTIVE_MASK		 (MAKELPARAM2('A', 'c', 't', '.'))
#define CHECKA_MASK		 (~(ACTIVE_MASK))
#define CHECK_PROC(a, c)	( ( a | c ) == 0xFFFFFFFF && ( a & c ) == 0 )

// 文件管理模块私有数据
typedef struct __tagFMSDATA{
	CHAIN_NODE  node;
	FILEMRSYS  *this;
	SAVEFILE   *save;
	CHAR	   *filename;
	FILE	   *fp;		 // 指向数据文件的指针
	INT32	   curr;	   // 当前打开的数据文件
	PTRPARIENT  pData;	  // 读取病人数据文件缓存,使用完后释放
}FMSDATA;

static UCHAR sPtnInfoStr[5][8];
static FMSDATA *This = NULL;
static FILE *tmpFp = NULL;

static FMSDATA *gen_GetThisData(FILEMRSYS *this)
{
	FMSDATA *tmpThis = This;

	if (tmpThis->this == this)
		return tmpThis;
	
	while (!Chain_Is_last ((CHAIN_NODE *)tmpThis))
	{
		tmpThis = (FMSDATA *)tmpThis->node.next;
		
		if (tmpThis->this == this)
			return tmpThis;
	}
	
	return NULL;
}

static STATUS gen_InfoFileAdd(FMSDATA *this, char *name, int index)
{
	if (index < 0 || index >= DATA_SAVE_MAX)
		return FILE_CANNOT_CREATE;

	if (strlen(name) >= sizeof(this->save->info[index].fileName))
		return FILE_OTHER_ERROR;
	
	this->save->info[index].status = 'N';
	strcpy(this->save->info[index].fileName, name);
	PPTNINFO pInfo = (PPTNINFO)LoadFileEx((UCHAR*)name, sizeof(PTNINFO_FILE));

	if (!pInfo)
		return FILE_NOT_EXIST;

	if (memcmp(pInfo->name, PTNT_INFO_HEAD, sizeof(pInfo->name)))
	{
		return FILE_INJURE;
	}
	
	memcpy(this->save->info[index].name, TABLES_HEAD, strlen(TABLES_HEAD));
	memcpy(this->save->info[index].ptnName,
		pInfo->patientName, sizeof(pInfo->patientName));
	memcpy(this->save->info[index].ptnID,
		pInfo->patientID, sizeof(pInfo->patientID));
	this->save->info[index].time = pInfo->createTime;
	this->save->info[index].status = 'S';
	return FILE_OK;
}

static VOID gen_SaveInfoFile(FMSDATA *this)
{
	if (this->save == NULL)
		return;

	if (memcmp(this->save->name, DATA_FILE_HEAD, strlen(DATA_FILE_HEAD)))
	{
		memcpy(this->save->name, DATA_FILE_HEAD, strlen(DATA_FILE_HEAD));
	}

	if (this->save->filelen != sizeof(SAVEFILE))
	{
		this->save->filelen = sizeof(SAVEFILE);
	}

	if (this->save->saveNum != DATA_SAVE_MAX)
	{
		this->save->saveNum = DATA_SAVE_MAX;
	}

	memcpy(&(this->save->backup), &(this->save->sInfo), sizeof(SAVEINFO));

	CHAR name[64];
	sprintf(name, "%s~", this->filename);
	FILE *fp = fopen(name, "wb+");
//	prinfo("name:%s, fp:%p\r\n", name, fp);
	if (!fp)
	{
		perror("gen_SaveInfoFile");
		return;
	}

	fwrite(this->save, sizeof(SAVEFILE), 1, fp);
	fclose(fp);
	
	if (rename(name, this->filename))
		perror("rename");
}

static VOID gen_ResetSaveFile(FMSDATA *this)
{
	PSAVINFO p = &(this->save->sInfo);
	int i;
	for (i = 0; i < DATA_SAVE_MAX; i++)
	{
		p->index[i] = i;
	}
}

static VOID gen_ResetInfoFile(FMSDATA *this)
{
	PRE_TABS *p = this->save->info;
	CHAR	filename[32];
	int i;
	ZeroMemory(p, sizeof(PRE_TABS) * DATA_SAVE_MAX);
	sprintf(filename, "%s.d/data.", this->filename);
	if (strlen(filename) > sizeof(p->fileName) - 4)
		return;
	for (i = 0; i < DATA_SAVE_MAX; i++)
	{
		memcpy(p->name, TABLES_HEAD, 7);//strlen(TABLES_HEAD));
		p->status = 'N';
		sprintf(p->fileName, "%s%03d", filename, i);
		p++;
	}
	gen_ResetSaveFile(this);
	gen_SaveInfoFile(this);
}

// 整理索引文件,按时间排序
static VOID gen_DefragSaveFile(FMSDATA *this)
{
	int i, j, k;
	short swap;
	short buf[DATA_SAVE_MAX];
	SAVEFILE *p = this->save;

	j = 0;
	k = DATA_SAVE_MAX - 1;
	p->sInfo.active = 0;
	p->sInfo.checkA = 0;

	// 如果出现相同的序号,重新整理
	for (i = 1; i < DATA_SAVE_MAX; i++)
	{
		if (p->sInfo.index[i - 1] == p->sInfo.index[i])
		{
			gen_ResetSaveFile(this);
			break;
		}
	}
	for (i = 0; i < DATA_SAVE_MAX; i++)
	{
		if (p->info[p->sInfo.index[i]].status == 'S')
		{
			buf[j++] = p->sInfo.index[i];
			continue;
		}

		if (p->info[p->sInfo.index[i]].status == 'D')
		{
			buf[k--] = p->sInfo.index[i];
			continue;
		}

		p->info[p->sInfo.index[i]].status = 'N';
	}
	k = j;
	for (i = 0; i < DATA_SAVE_MAX; i++)
	{
		if (p->info[p->sInfo.index[i]].status == 'N')
		{
			buf[k++] = p->sInfo.index[i];
			continue;
		}
	}
	// 按创建时间排序(选择排序)
	for (i = 0; i < j - 1; i++)
	{
		for (k = i + 1; k < j; k++)
		{
			// 将最新的时间排在最前
			if (p->info[buf[i]].time < p->info[buf[k]].time)
			{
				swap = buf[k];
				buf[k] = buf[i];
				buf[i] = swap;
			}
		}
	}
	memcpy(p->sInfo.index, buf, sizeof(buf));
	memcpy(p->sInfo.name, SAVE_INFO_HEAD, strlen(SAVE_INFO_HEAD));
	p->sInfo.active = ACTIVE_MASK;
	p->sInfo.checkA = CHECKA_MASK;
//	memcpy(p->backup, p->sInfo, sizeof(SAVEINFO));
}

static short gen_GetNewSaveIndex(FMSDATA *this)
{
	short i;
	for (i = 1; i < DATA_SAVE_MAX; i++)
	{
		if (this->save->sInfo.index[i - 1] == this->save->sInfo.index[i])
		{
			gen_ResetSaveFile(this);
			gen_DefragSaveFile(this);
			gen_SaveInfoFile(this);
			break;
		}
	}

	for (i = 0; i < DATA_SAVE_MAX; i++)
	{
		if (this->save->info[this->save->sInfo.index[i]].status != 'S')
			return (this->save->sInfo.index[i]);
	}
	return i;
}

static VOID gen_InitializationPatientFile(FMSDATA *this)
{
	fseek(this->fp, 0, SEEK_SET);
	fwrite(PTNT_INFO_HEAD, strlen(PTNT_INFO_HEAD), 1, this->fp);
	fwrite(&(this->curr), sizeof(this->curr), 1, this->fp);
	fseek(this->fp, sizeof(PTNINFO_FILE), SEEK_SET);
	fwrite(PTNT_ANSS_HEAD, strlen(PTNT_ANSS_HEAD), 1, this->fp);
	fseek(this->fp, sizeof(PTNINFO_FILE) + sizeof(FETAL_ANSIS), SEEK_SET);
	fwrite(PTNT_DATA_HEAD, strlen(PTNT_DATA_HEAD), 1, this->fp);
	fwrite(&(this->curr), sizeof(this->curr), 1, this->fp);
}

static BOOL gen_CreateDataFile(char *name)
{
	if (*name > ' ' && strlen(name) < 32)
	{
		FILE *fp = fopen(name, "wb+");
		return SetFileSize(fp, sizeof(PATIENT_FILE));
	}
	printf("gen_CreateDataFile error, filename is %s\r\n", name);
	return FALSE;
}

static VOID gen_BuileDataFile(FMSDATA *this)
{
	int i;
	for (i = 0; i < this->save->saveNum; i++)
	{
		gen_CreateDataFile(this->save->info[i].fileName);
	}
}

static VOID gen_InitializationInfoFile(FILEMRSYS *this)
{
	FMSDATA *tmpThis;
	if (tmpThis = gen_GetThisData(this))
	{
		if (GetDataFileStat('M') < 65)
		{
			printf("Initialization File error, insufficient disk space\r\n");
			return;
		}
		
		gen_ResetInfoFile(tmpThis);
		gen_BuileDataFile(tmpThis);
	}
}

static VOID gen_SaveTempFile(PFETALDATA pData)
{
	if (NULL == FetalDataPtr)
		return;

	if (FetalDataPtr->info.count == FetalDataPtr->info.index)
	{
		FetalDataPtr->info.count = FetalDataPtr->info.index + 1;
	}
	
	if (++FetalDataPtr->info.index >= DATA_SAVE_LEN)
	{
		FetalDataPtr->info.index = 0;
	}
	
	if (FetalDataPtr->info.count < DATA_SAVE_LEN)
	{
		FetalDataPtr->info.count ++;
	}
	else if (FetalDataPtr->info.count > DATA_SAVE_LEN)
	{
		FetalDataPtr->info.count = DATA_SAVE_LEN;
	}
	PFETALDATA p = &(FetalDataPtr->data[FetalDataPtr->info.index]);
	memcpy(p, pData, sizeof(FETALDATA));
//	p --;
//	p --;
//	prinfo("fhr1, toco, afm\r\n");
//	printf("%d, %d, %d\r\n", p->wave[1].fhr1, p->wave[1].toco, p->wave[1].afm);
//	p++;
//	printf("%d, %d, %d\r\n", p->wave[1].fhr1, p->wave[1].toco, p->wave[1].afm);
//	p++;
//	printf("%d, %d, %d\r\n", p->wave[1].fhr1, p->wave[1].toco, p->wave[1].afm);
}

static INT32 gen_GetCurrSaveIndex(FILEMRSYS *this)
{
	FMSDATA *tmpThis;
	if (tmpThis = gen_GetThisData(this))
	{
		if (tmpThis->fp)
		{
			return (tmpThis->curr);
		}
	}
	return FILE_NOT_EXIST;
}

static INT32 gen_GetSaveNumber(FILEMRSYS *this)
{
	FMSDATA *tmpThis;
	if (tmpThis = gen_GetThisData(this))
	{
		if (! tmpThis->save)
		{
			this->GetInfoFile(this);
		}
		int i, cnt;
		cnt = 0;
		for (i = 0; i < tmpThis->save->saveNum; i++)
		{
			if (tmpThis->save->info[i].status == 'S')
			{
				cnt ++;
			}
		}
		return cnt;
	}
	return 0;
}

// 每次执行都会重新读取文件
static SAVEFILE *gen_GetInfoFile(FILEMRSYS *this)
{
	FMSDATA *tmpThis;

	if (tmpThis = gen_GetThisData(this))
	{
		if (tmpThis->filename && *tmpThis->filename != '\0')
		{
			if (tmpThis->save)
			{
				free(tmpThis->save);
				tmpThis->save = NULL;
			}

			tmpThis->save = 
				(SAVEFILE*)LoadFileEx(tmpThis->filename, sizeof(SAVEFILE));

			return (tmpThis->save);
		}
	}
	return NULL;
}

static BOOL gen_DestroyGetData(FILEMRSYS *this)
{
	FMSDATA *tmpThis;
	if (tmpThis = gen_GetThisData(this))
	{
		if (tmpThis->pData)
		{
			free(tmpThis->pData);
			tmpThis->pData = NULL;
			return TRUE;
		}
	}
	return FALSE;
}

static BOOL gen_check_data_file(PTRPARIENT pPrnt)
{
	if ((CHECK_PROC(pPrnt->data.info[0].index, pPrnt->data.info[0].indexchk))
	 && (CHECK_PROC(pPrnt->data.info[0].count, pPrnt->data.info[0].countchk)))
	{
		return TRUE;
	}

	if ((CHECK_PROC(pPrnt->data.info[1].index, pPrnt->data.info[1].indexchk))
	 && (CHECK_PROC(pPrnt->data.info[1].count, pPrnt->data.info[1].countchk)))
	{
		memcpy(&(pPrnt->data.info[0]),
				&(pPrnt->data.info[0]), sizeof(DATASAVEINFO));
		return TRUE;
	}
	return FALSE;
}

static PATIENT_FILE *gen_GetDataFile(FILEMRSYS *this, INT16 index)
{
	FMSDATA *tmpThis;
	if (tmpThis = gen_GetThisData(this))
	{
		UCHAR *name;
		name = tmpThis->save->info[tmpThis->save->sInfo.index[index]].fileName;
		if (*name == '\0')
		{
			sprintf(name, "%s.d/data.%03d", tmpThis->filename,
				tmpThis->save->sInfo.index[index]);
		}
		if (tmpThis->pData)
		{
			if (!this->DestroyGetData(this))
			{
				return NULL;
			}
		}
		tmpThis->pData = ((PTRPARIENT)LoadFileEx(name, sizeof(PATIENT_FILE)));
		gen_check_data_file(tmpThis->pData);
		return (tmpThis->pData);
	}
	return NULL;
}

static BOOL gen_ClosePatientFile(FILEMRSYS *this)
{
	FMSDATA *tmpThis;
	if (tmpThis = gen_GetThisData(this))
	{
		if (tmpThis->fp)
		{
			fclose(tmpThis->fp);
			tmpThis->fp = NULL;
			return TRUE;
		}
	}
	return FALSE;
}

static VOID gen_WriteFetalData(FILEMRSYS *this, PFETALDATA pData)
{
	FMSDATA *tmpThis;
	if (tmpThis = gen_GetThisData(this))
	{
		if (tmpThis->fp)
		{
			DATASAVEINFO infoNew, infoOld;
			UCHAR name[8];
			fseek(tmpThis->fp, FIELD_OFFSET(PATIENT_FILE, data), SEEK_SET);
			fread(name, sizeof(name), 1, tmpThis->fp);
			if (memcmp(name, PTNT_DATA_HEAD, strlen(PTNT_DATA_HEAD)))
			{
				memcpy(name, PTNT_DATA_HEAD, strlen(PTNT_DATA_HEAD));
				fseek(tmpThis->fp, FIELD_OFFSET(PATIENT_FILE, data), SEEK_SET);
				fwrite(name, sizeof(name), 1, tmpThis->fp);
			}
			fseek(tmpThis->fp, sizeof(INT32), SEEK_CUR);
			fread(&infoNew, sizeof(infoNew), 1, tmpThis->fp);
			fread(&infoOld, sizeof(infoOld), 1, tmpThis->fp);
			if (CHECK_PROC(infoNew.index, infoNew.indexchk))
			{
				infoOld = infoNew;
			}
			else if (CHECK_PROC(infoOld.index, infoOld.indexchk))
			{
				infoNew = infoOld;
			}
			else
			{
				infoNew.index = 0;
				infoNew.indexchk = ~(infoNew.index);
				infoNew.count = 1;
				infoNew.countchk = ~(infoNew.count);
				infoOld = infoNew;
			}
			if (infoNew.count == infoNew.index)
				infoNew.count++;
			if (++infoNew.index >= DATA_SAVE_LEN)
			{
				infoNew.index = 0;
			}
			if (infoNew.count < DATA_SAVE_LEN)
			{
				infoNew.count ++;
			}
			else
			{
				infoNew.count = DATA_SAVE_LEN;
			}
			infoNew.indexchk = ~(infoNew.index);
			infoNew.countchk = ~(infoNew.count);
			// 写入数据
			fseek(tmpThis->fp, sizeof(FETALDATA) * infoNew.index, SEEK_CUR);
			fwrite(pData, sizeof(FETALDATA), 1, tmpThis->fp);
			flush(tmpThis->fp);
			// 写入旧时间
			fseek(tmpThis->fp, FIELD_OFFSET(PATIENT_FILE, data)
							 + FIELD_OFFSET(FETALDATA_FILE, info[1]), SEEK_SET);
			fwrite(&infoOld, sizeof(infoOld), 1, tmpThis->fp);
			fseek(tmpThis->fp, -2 * sizeof(DATASAVEINFO), SEEK_CUR);
			flush(tmpThis->fp);
			// 写入新时间
			fwrite(&infoNew, sizeof(infoNew), 1, tmpThis->fp);
			flush(tmpThis->fp);
		}
		gen_SaveTempFile(pData);
	}
}

static VOID gen_WritePatientAnalysis(FILEMRSYS *this, PTRANSIS pAnsis)
{
	FMSDATA *tmpThis;
	if (tmpThis = gen_GetThisData(this))
	{
		if (tmpThis->fp)
		{
			if (memcmp(pAnsis->name, PTNT_ANSS_HEAD, strlen(PTNT_ANSS_HEAD)))
			{
				memcpy(pAnsis->name, PTNT_ANSS_HEAD, strlen(PTNT_ANSS_HEAD));
			}
			fseek(tmpThis->fp, FIELD_OFFSET(PATIENT_FILE, ansis), SEEK_SET);
			fwrite(pAnsis, sizeof(FETAL_ANSIS), 1, tmpThis->fp);
			flush(tmpThis->fp);
		}
	}
#if _ENB_NET_THREAD
	PostMessage(SysUdpT_HTSK, MSG_NET_UDP_SEND, sizeof(FETAL_ANSIS),(LPARAM)pAnsis);
	PostMessage(SysTcpT_HTSK, MSG_NET_TCP_SEND, sizeof(FETAL_ANSIS),(LPARAM)pAnsis);
#endif
}

static VOID gen_WritePatientInfo(FILEMRSYS *this, PPTNINFO pInfo)
{
	FMSDATA *tmpThis;
	if (tmpThis = gen_GetThisData(this))
	{
		if (tmpThis->fp)
		{
			if (memcmp(pInfo->name, PTNT_INFO_HEAD, strlen(PTNT_INFO_HEAD)))
			{
				memcpy(pInfo->name, PTNT_INFO_HEAD, strlen(PTNT_INFO_HEAD));
			}
			if (pInfo->index != tmpThis->curr)
			{
				pInfo->index = tmpThis->curr;
			}
			fseek(tmpThis->fp, FIELD_OFFSET(PATIENT_FILE, info), SEEK_SET);
			fwrite(pInfo, sizeof(PTNINFO_FILE), 1, tmpThis->fp);
			flush(tmpThis->fp);
			tmpThis->save->info[tmpThis->curr].status = 'S';
			strncpy(tmpThis->save->info[tmpThis->curr].ptnName,
					pInfo->patientName, 31);
			strncpy(tmpThis->save->info[tmpThis->curr].ptnID,
					pInfo->patientID, 31);
			gen_SaveInfoFile(tmpThis);
		}
	}
#if _ENB_NET_THREAD
	PostMessage(SysUdpT_HTSK, MSG_NET_UDP_SEND, sizeof(PTNINFO_FILE),(LPARAM)pInfo);
	PostMessage(SysTcpT_HTSK, MSG_NET_TCP_SEND, sizeof(PTNINFO_FILE),(LPARAM)pInfo);
#endif
}

extern int get_curr_time(void);
static BOOL gen_NewPatient(FILEMRSYS *this)
{
	FMSDATA *tmpThis;
	if (tmpThis = gen_GetThisData(this))
	{
		short ndx = 0;
		if (tmpThis->fp)
		{
			this->ClosePtnFile(this);
		}
		tmpThis->curr = gen_GetNewSaveIndex(tmpThis);
		if (tmpThis->curr >= DATA_SAVE_MAX)
		{
			this->DeletePatient(this, &ndx, 1);
			tmpThis->curr = gen_GetNewSaveIndex(tmpThis);
			if (tmpThis->curr >= DATA_SAVE_MAX)
				return FALSE;
		}
		tmpThis->fp = fopen(tmpThis->save->info[tmpThis->curr].fileName, "wb+");
		if (tmpThis->fp)
		{
			if (SetFileSize(tmpThis->fp, sizeof(PATIENT_FILE)))
			{
				gen_InitializationPatientFile(tmpThis);
				// 只要写入就认为已经保存
				tmpThis->save->info[tmpThis->curr].status = 'S';
				tmpThis->save->info[tmpThis->curr].time = get_curr_time();
				gen_DefragSaveFile(tmpThis);
				gen_SaveInfoFile(tmpThis);
				return TRUE;
			}
		}
	}
	return FALSE;
}

static VOID gen_DeletePatientFile(FILEMRSYS *this, INT16 *index, INT16 len)
{
	FMSDATA *tmpThis;
	int i;

	if (tmpThis = gen_GetThisData(this))
	{
		int i, ndx;
		if (len <= 0 ||len >= DATA_SAVE_MAX) return;
		for (i = 0; i < len; i++)
		{
			ndx = index[i];
			if (ndx < 0 || ndx >= DATA_SAVE_MAX)
				break;
			tmpThis->save->info[tmpThis->save->sInfo.index[ndx]].status = 'D';
		}
		
		gen_DefragSaveFile(tmpThis);
		gen_SaveInfoFile(tmpThis);
	}
}

// 用于索引文件丢失时重建索引文件
static BOOL gen_RebuildSaveFile(FILEMRSYS *this)
{
	FMSDATA *tmpThis;
	if (tmpThis = gen_GetThisData(this))
	{
		int i, cnt = 0;
		char filename[64];
		if (strlen(tmpThis->filename) > 20)// 32 - 12
		{
			prinfo("file name too long\r\n");
			return FALSE;
		}
		for (i = 0; i < DATA_SAVE_MAX; i++)
		{
			sprintf(filename, "%s.d/data.%03d", tmpThis->filename, i);
			
			if (CheckFileExist(filename))
			{
				if (gen_InfoFileAdd(tmpThis, filename, i))
				{
					return FALSE;
				}
				cnt ++;
			}
		}
		if (cnt == 0)
		{
			return FALSE;
		}

		gen_DefragSaveFile(tmpThis);
		gen_SaveInfoFile(tmpThis);

		return TRUE;
	}
	return FALSE;
}

static BOOL gen_UnRegister(FILEMRSYS *this)
{
	FMSDATA *tmpThis;
	if (tmpThis = gen_GetThisData(this))
	{
		CHAIN_NODE node = tmpThis->node;
		if (tmpThis->save)
		{
			free(tmpThis->save);
		}
		if (tmpThis->fp)
		{
			fclose(tmpThis->fp);
			tmpThis->fp = NULL;
		}
		if (node.next)
		{
			((FMSDATA*)node.next)->node.previous = node.previous;
		}
		if (node.previous)
		{
			((FMSDATA*)node.previous)->node.next = node.next;
		}
		free(tmpThis);
		return TRUE;
	}
	return FALSE;
}

// 必须先注册文件管理系统
static BOOL gen_Register(FILEMRSYS *this, const char *filename)
{
	// 其余初始化都在这里执行
	FMSDATA *tmpThis = This;
	
	if (NULL == tmpThis)
	{
		tmpThis = (FMSDATA *)malloc(sizeof(FMSDATA));
		if (NULL == tmpThis) return FALSE;
		ZeroMemory(tmpThis, sizeof(FMSDATA));
		This = tmpThis;
	}
	else
	{
		if (tmpThis->this == this)
			return FALSE;

		while (!Chain_Is_last ((CHAIN_NODE*)tmpThis))
		{
			tmpThis = (FMSDATA *)tmpThis->node.next;
			if (tmpThis->this == this)
				return FALSE;
		}
		tmpThis->node.next = (PCHAIN_NODE)malloc(sizeof(FMSDATA));
		if (!tmpThis->node.next)
			return FALSE;
		PCHAIN_NODE previous = (PCHAIN_NODE)tmpThis;
		tmpThis = (FMSDATA *)tmpThis->node.next;
		ZeroMemory(tmpThis, sizeof(FMSDATA));
		tmpThis->node.previous = previous;
	}
	tmpThis->filename = (CHAR *)filename;
	tmpThis->this = this;
	tmpThis->fp = NULL;
	tmpThis->curr = -1;
	tmpThis->pData = NULL;
	this->UnRegister = gen_UnRegister;
	this->RebuildSaveFile = gen_RebuildSaveFile;
	this->DeletePatient = gen_DeletePatientFile;
	this->NewPatient = gen_NewPatient;
	this->PutPtnInfo = gen_WritePatientInfo;
	this->PutAnsis = gen_WritePatientAnalysis;
	this->PutData = gen_WriteFetalData;
	this->ClosePtnFile = gen_ClosePatientFile;
	this->GetDataFile = gen_GetDataFile;
	this->DestroyGetData = gen_DestroyGetData;
	this->GetInfoFile = gen_GetInfoFile;
	this->GetSaveNum = gen_GetSaveNumber;
	this->GetCurrSaveIndex = gen_GetCurrSaveIndex;
	// 首先尝试加载索引文件
	if (! this->GetInfoFile(this))
	{
		// 索引文件不存在
		// 尝试重建索引
		if ((tmpThis->save = (SAVEFILE*)malloc(sizeof(SAVEFILE))) == NULL)
		{
			prinfo("malloc failure ?\n");
			return FALSE;
		}
		if (!this->RebuildSaveFile(this))
		{
			// 初始化整个数据文件区域
			// 检查数据文件夹
			struct statfs folderStat;
			UCHAR name[32];
			sprintf(name, "%s.d", tmpThis->filename);
			if (statfs(name, &folderStat))
			{
				mkdir(name, 0666);
			}
			gen_InitializationInfoFile(this);
		}
	}
	else
	{
		// 检查数据文件夹
		struct statfs folderStat;
		UCHAR name[32];
		sprintf(name, "%s.d", tmpThis->filename);
		if (statfs(DATA_FOLDER, &folderStat))
		{
			mkdir(name, 0666);
		}
	}
	return TRUE;
}

// 文件系统初始化
BOOL InitSaveFileSystem(FILEMRSYS *this)
{
	if (NULL == FetalDataPtr)
	{
		FetalDataPtr = (PFETAL_TD)malloc(sizeof(FETAL_TD));
		if (NULL == FetalDataPtr)
		{
			return FALSE;
		}
	}
	if (NULL == this)
		return FALSE;

	this->Register = gen_Register;
	return TRUE;
}
#endif

