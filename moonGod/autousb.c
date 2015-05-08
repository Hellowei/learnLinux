
#include "includes.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/mount.h>


#define AUTOUSB_OUT 0
#if AUTOUSB_OUT
#define AUTOUSB_P	printf
#else
#define AUTOUSB_P
#endif

char buffer[1024];
char *usb_mount_dir = "/mnt/disk";
char *usb_storage_file = "/proc/bus/usb/devices";
char *fsType = "vfat";
char *scsiType = "Direct-Access";

char CheckUsbStorage(void)
{
	static int fd = -1;
	static char status = 0;
	fd_set fdset;
	if (fd < 0) {
		fd = open(usb_storage_file, O_RDONLY);
		if (fd < 0) {
			AUTOUSB_P("No usb devices support");
			exit(0);
		}
	}
	FD_ZERO(&fdset);
	FD_SET(fd, &fdset);
	select(fd + 1, &fdset, 0, 0, 0);
	if (FD_ISSET(fd, &fdset)) {
		lseek(fd, 0, SEEK_SET);
		memset(buffer, 0, sizeof(buffer));
		read(fd, buffer, sizeof(buffer));
		char *info = strstr(buffer, "Driver=usb-storage");
		status = !(info == NULL);
	}
	return status;
}

void UmountDisk(char *dir, char *type)
{
	FILE *fp;
	sprintf(buffer, "mount | grep %s", type);
	if (fp = popen(buffer, "r")) {
		memset(buffer, 0, sizeof(buffer));
		while(fgets(buffer, sizeof(buffer), fp)) {
			if (strstr(buffer, dir)) {
				if (umount(dir))
					perror("UmountDisk");
				else
					AUTOUSB_P(dir);
				break;
			}
		}
		pclose(fp);
	}
	else
		AUTOUSB_P("error!");
}

void MountDisk(char *devName, char *dir)
{
	char *p = devName;
	char name[16];
	if (p && strlen(p) >= 8) { /* /dev/sda* */
		while(*p != '\0') {
			if (*p == ':') {
				*p = '\0';
				break;
			}
			p++;
		}
		strcpy(name, devName);
		UmountDisk(dir, fsType);
		if (mount(name, dir, fsType, MS_SYNCHRONOUS, NULL))
			perror("MountDisk");
	}
}

char *GetMountTable(void)
{
	static char MountTable[1024];
	FILE *fp;
	if (fp = popen("mount|grep /dev/sd", "r"))
	{
		fread(MountTable, sizeof(MountTable), 1, fp);
		fclose(fp);
	}
	else
	{
		MountTable[0] = '\0';
	}
	return MountTable;
}

void TryToReadFromDev(char *buff)
{
	char *temp;
	char *p;
	char tmpbuf[16];
	char foo[16] = {0};
	char *mtable = GetMountTable() ;
	FILE *fp = popen("ls /dev/sd*", "r");
	if (fp)
	{
		while (temp = fgets(tmpbuf, sizeof(tmpbuf), fp)) {
			p = &tmpbuf[strlen(temp) - 1];
			while(*p == '\r' || *p == '\n') {
				*p = '\0';
				p--;
			};
			if (strlen(temp) >= 8)
			{
				strcpy(buff, temp);//get the last one
				if (strstr(mtable, temp) == NULL)
				{
					strcpy(foo, temp);
				}
			}
		}
		pclose(fp);
		if (strlen(foo) >= 8)
			strcpy(buff, foo);
	}
}

char MountUsbStorage(void)
{
	int times = 10;
	char ret = 0;
	FILE *fp = NULL;
	fp = fopen("/proc/scsi/scsi", "r");
	while (times > 0) {
		sleep(1);
		fseek(fp, 0, SEEK_SET);
		fread(buffer, 32, 32, fp);
		if (strstr(buffer, scsiType))
			break;
		else
			times--;
	}
	if (times == 0) {
		AUTOUSB_P("scsi error");
	}
	else if (fp = popen("blkid", "r")) {
		memset(buffer, 0, sizeof(buffer));
		fgets(buffer, sizeof(buffer), fp);
		pclose(fp);
		fp = NULL;
		if (strlen(buffer) > 6) {
			MountDisk(buffer, usb_mount_dir);
			ret = 1;
		} else {
			memset(buffer, 0, sizeof(buffer));
			TryToReadFromDev(buffer);
			if (strlen(buffer) > 6) {
				MountDisk(buffer, usb_mount_dir);
				ret = 1;
			}
		}
	}
	return ret;
}

#if _ENB_AUTOUSB < 1
#define WRITE_FILE_STRING(file, str)			\
	do{											\
		FILE *fp = fopen(file, "wb");			\
		if(fp) { fputs(str, fp); fclose(fp); }	\
	}while(0)
#else
#define WRITE_FILE_STRING(file, str)	SetUsbStorageStatus(str[0])
#endif

void AutoUsbTask(void *pdata)
{
	char usbflag = 2;
	char st;
	char buf[2] = " ";
	char usbFileName[] = "/tmp/usb";
	WRITE_FILE_STRING(usbFileName, buf);
	while (1) {
		st = CheckUsbStorage();
		if (usbflag == st) {
			continue;
		}
		usbflag = st;
		if (usbflag) {
			AUTOUSB_P("usb devices on\n");
			buf[0] = '0';
			WRITE_FILE_STRING(usbFileName, buf);
			usbflag = MountUsbStorage();
			buf[0] += usbflag;
			WRITE_FILE_STRING(usbFileName, buf);
		}
		else {
			AUTOUSB_P("usb devices off");
			UmountDisk(usb_mount_dir, fsType);
			buf[0] = ' ';
			WRITE_FILE_STRING(usbFileName, buf);
		}
	}
	return;
}

