
#define _NETSRV_GLOBALS

#include "includes.h"
#include <netdb.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/ioctl.h>

#include   <netinet/in.h> 
#include   <sys/types.h> 
#include   <sys/socket.h> 
#include   <unistd.h> 
#include   <sys/select.h> 
#include   <sys/errno.h> 

UINT16 const crc16_table[256] = {
	0x0000, 0xC0C1, 0xC181, 0x0140, 0xC301, 0x03C0, 0x0280, 0xC241,
	0xC601, 0x06C0, 0x0780, 0xC741, 0x0500, 0xC5C1, 0xC481, 0x0440,
	0xCC01, 0x0CC0, 0x0D80, 0xCD41, 0x0F00, 0xCFC1, 0xCE81, 0x0E40,
	0x0A00, 0xCAC1, 0xCB81, 0x0B40, 0xC901, 0x09C0, 0x0880, 0xC841,
	0xD801, 0x18C0, 0x1980, 0xD941, 0x1B00, 0xDBC1, 0xDA81, 0x1A40,
	0x1E00, 0xDEC1, 0xDF81, 0x1F40, 0xDD01, 0x1DC0, 0x1C80, 0xDC41,
	0x1400, 0xD4C1, 0xD581, 0x1540, 0xD701, 0x17C0, 0x1680, 0xD641,
	0xD201, 0x12C0, 0x1380, 0xD341, 0x1100, 0xD1C1, 0xD081, 0x1040,
	0xF001, 0x30C0, 0x3180, 0xF141, 0x3300, 0xF3C1, 0xF281, 0x3240,
	0x3600, 0xF6C1, 0xF781, 0x3740, 0xF501, 0x35C0, 0x3480, 0xF441,
	0x3C00, 0xFCC1, 0xFD81, 0x3D40, 0xFF01, 0x3FC0, 0x3E80, 0xFE41,
	0xFA01, 0x3AC0, 0x3B80, 0xFB41, 0x3900, 0xF9C1, 0xF881, 0x3840,
	0x2800, 0xE8C1, 0xE981, 0x2940, 0xEB01, 0x2BC0, 0x2A80, 0xEA41,
	0xEE01, 0x2EC0, 0x2F80, 0xEF41, 0x2D00, 0xEDC1, 0xEC81, 0x2C40,
	0xE401, 0x24C0, 0x2580, 0xE541, 0x2700, 0xE7C1, 0xE681, 0x2640,
	0x2200, 0xE2C1, 0xE381, 0x2340, 0xE101, 0x21C0, 0x2080, 0xE041,
	0xA001, 0x60C0, 0x6180, 0xA141, 0x6300, 0xA3C1, 0xA281, 0x6240,
	0x6600, 0xA6C1, 0xA781, 0x6740, 0xA501, 0x65C0, 0x6480, 0xA441,
	0x6C00, 0xACC1, 0xAD81, 0x6D40, 0xAF01, 0x6FC0, 0x6E80, 0xAE41,
	0xAA01, 0x6AC0, 0x6B80, 0xAB41, 0x6900, 0xA9C1, 0xA881, 0x6840,
	0x7800, 0xB8C1, 0xB981, 0x7940, 0xBB01, 0x7BC0, 0x7A80, 0xBA41,
	0xBE01, 0x7EC0, 0x7F80, 0xBF41, 0x7D00, 0xBDC1, 0xBC81, 0x7C40,
	0xB401, 0x74C0, 0x7580, 0xB541, 0x7700, 0xB7C1, 0xB681, 0x7640,
	0x7200, 0xB2C1, 0xB381, 0x7340, 0xB101, 0x71C0, 0x7080, 0xB041,
	0x5000, 0x90C1, 0x9181, 0x5140, 0x9301, 0x53C0, 0x5280, 0x9241,
	0x9601, 0x56C0, 0x5780, 0x9741, 0x5500, 0x95C1, 0x9481, 0x5440,
	0x9C01, 0x5CC0, 0x5D80, 0x9D41, 0x5F00, 0x9FC1, 0x9E81, 0x5E40,
	0x5A00, 0x9AC1, 0x9B81, 0x5B40, 0x9901, 0x59C0, 0x5880, 0x9841,
	0x8801, 0x48C0, 0x4980, 0x8941, 0x4B00, 0x8BC1, 0x8A81, 0x4A40,
	0x4E00, 0x8EC1, 0x8F81, 0x4F40, 0x8D01, 0x4DC0, 0x4C80, 0x8C41,
	0x4400, 0x84C1, 0x8581, 0x4540, 0x8701, 0x47C0, 0x4680, 0x8641,
	0x8201, 0x42C0, 0x4380, 0x8341, 0x4100, 0x81C1, 0x8081, 0x4040
};

UINT16 crc16_uint8 (UINT16 crc, const UINT8 data)
{
	return (crc >> 8) ^ crc16_table[(crc ^ data) & 0xff];
}

UINT16 crc16(UINT16 crc, UINT8 const *buffer, size_t len)
{
	while (len--)
	{
		crc = crc16_uint8 (crc, *buffer++);
	}
	return crc;
}


static int sSockFd = INVALID_SOCKET;
static int sRecResetFlag = TRUE;
static int sTranConnectFalg = FALSE;
static UINT32 sMachineNumber = 0;
static UCHAR sNetSendBuffer[1024];
struct sockaddr_in sToAddr = { 0 };
struct sockaddr_in sFromAddr = { 0 };

static BOOL InitNetSocket(int *socket_fd)
{
    struct sockaddr_in local_addr;
	int Timeout = 1000; //1秒
    *socket_fd  = socket(AF_INET, SOCK_DGRAM, 0);
	//接收时限
	setsockopt(*socket_fd, SOL_SOCKET, SO_RCVTIMEO, (char*)&Timeout, sizeof(int));
	memset(&local_addr, 0, sizeof(local_addr));
    if (*socket_fd == INVALID_SOCKET)
    {
        return FALSE;
    }
    memset(&local_addr, 0, sizeof(struct sockaddr_in));
    local_addr.sin_family = AF_INET;
    local_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    local_addr.sin_port = htons(NetConfig.port);
    //绑定端口号
    bind(*socket_fd, (struct sockaddr*)&local_addr, sizeof(local_addr));
    return TRUE;
}

static void sResetNetSocket(int *socket_fd)
{

}

static int sNetBuildPacket (unsigned short packet_id,	// 包类型
						    unsigned char ack,			// 包状态,是否要应答
						    unsigned int  seq_pack_num,	// 包序号
						    unsigned char *data,		// 数据
						    int data_len,				// 数据长度
						    unsigned char *buffer)		// 返回
{
	unsigned short len = data_len + 17;
	if (NULL == data)
	{
		data_len = 0;
		len = 17;
	}
	#if 1//调试上送的胎心数据
			if (NULL != data && packet_id == 46)
			{
				int k;
				for(k = 0;k < data_len;k++)
					printf("d[%d]=%u,",k+1,data[k]);
				printf("\n");
			}
	#endif
	buffer[0] = 0x55;
	buffer[1] = 0xAA;

	// 包长度
	buffer[2] = LOBYTE(len);
	buffer[3] = HIBYTE(len);

	// 包序号
	buffer[4] = LOBYTE(LOWORD(seq_pack_num));
	buffer[5] = HIBYTE(LOWORD(seq_pack_num));
	buffer[6] = LOBYTE(HIWORD(seq_pack_num));
	buffer[7] = HIBYTE(HIWORD(seq_pack_num));
	
	//是否响应
	buffer[8] = ack;
	
	//包类型
	buffer[9] = LOBYTE(packet_id);
	buffer[10] = HIBYTE(packet_id);
	//机器编号
	buffer[11] = LOBYTE(LOWORD(sMachineNumber));
	buffer[12] = HIBYTE(LOWORD(sMachineNumber));
	buffer[13] = LOBYTE(HIWORD(sMachineNumber));
	buffer[14] = HIBYTE(HIWORD(sMachineNumber));

	// no data
	if (data != NULL)
		memcpy(buffer + 15, data, data_len);

	// 计算校验和
	len = data_len + 15;
	UINT16 crc = 0;
	crc = crc16(crc, buffer, len);

	buffer[data_len + 15] = LOBYTE(crc);
	buffer[data_len + 16] = 0x03;

	return (len + 2);
}

#define PKG_0x0A	0x0A	// 设备上线注册// 产品信息
#define PKG_0x10	0x10	// 产品信息，类型0x10
#define PKG_0x14	0x14	// 设备注销
#define PKG_0x13	0x13	// 设备网络探测包，每秒一次
							// 主要是探测服务器软件是否在运行
#define PKG_0x2E   	0x2E	// 胎监数据 
#define PKG_0x5C    0x5C    // 胎监病人信息

//产品信息，类型0x10
typedef  struct  __PRODUCTINFO{
	char product_name[51];	// 产品名称，必须有结束符
	char softversion[51];	// 软件版本，必须有结束符
	char hardversion[51];	// 硬件版本
	char coder[51];			// 序号
	char copyright[51];		// 版权
	char web[51];			// 网址
}PRODUCTINFO;

static PRODUCTINFO sProductInfo = {
	.softversion	=	VERSION " " VERSION_SVN,
	.hardversion	=	"2.0.0.0",
	.copyright		=	"ZONDAN",
	.web			=	"www.zondan.com"
};

void SetMachineNumber(void)
{
	UINT16 crc = 12345;
	crc = crc16(crc, gMonitorUUID, 36);
	sMachineNumber = crc;
	crc = crc16(crc, gMonitorUUID, 36);
	sMachineNumber = (sMachineNumber << 16) + crc;
	strcpy(sProductInfo.coder, gMonitorUUID);
}

UINT32 GetMachineNumber(void)
{
	return sMachineNumber;
}

void SetMachineName(char *name)
{
	strcpy(sProductInfo.product_name, name);
}

static int sNetRecTimer = 0;
int GetNetReceivePacketCount(void)
{
	int ret = 0;
	pthread_mutex_lock(&NetCenterRecSem);
	ret = sNetRecTimer;
	pthread_mutex_unlock(&NetCenterRecSem);
	return ret;
}

void SetNetReceivePacketCount(char flag)
{
	pthread_mutex_lock(&NetCenterRecSem);
	if (FALSE == flag)
		sNetRecTimer++;
	else
		sNetRecTimer = 0;
	pthread_mutex_unlock(&NetCenterRecSem);
}

static void sPostConnectPacket(BOOL flag)
{
	static UCHAR Packet0A[17];
	static UCHAR Packet13[17];
	UCHAR *pBuf;
	int ret;
	int sendlen;//prinfo("\n");
	pthread_mutex_lock(&NetCenterSem);
	if (AF_INET != sToAddr.sin_family)
	{
		pthread_mutex_unlock(&NetCenterSem);
		SendMessage(SysUdpT_HTSK, MSG_NET_UDP_RESET, 0, 0);
		//prinfo("\n");
		return;
	}
	struct sockaddr *addr = (struct sockaddr *)&sToAddr;
	if (flag) // 
	{
		pBuf = Packet13;
		
		ret = sNetBuildPacket(PKG_0x13, TRUE, 0, NULL, 0, Packet13);
	}
	else
	{
		pBuf = Packet0A;
		ret = sNetBuildPacket(PKG_0x0A, TRUE, 0, NULL, 0, Packet0A);
	}
	sendlen = sendto(sSockFd, pBuf, ret, 0, addr, sizeof(struct sockaddr));
	pthread_mutex_unlock(&NetCenterSem);//prinfo("\n");
}

static void sPostInformationPacket(void)
{
	pthread_mutex_lock(&NetCenterSem);
	if (AF_INET != sToAddr.sin_family)
	{
		pthread_mutex_unlock(&NetCenterSem);
		return;
	}
	struct sockaddr *addr = (struct sockaddr *)&sToAddr;
	unsigned char buff[17 + sizeof(PRODUCTINFO)];
	int ret = sNetBuildPacket(PKG_0x10, FALSE, 0, (UCHAR*)&sProductInfo,
		sizeof(PRODUCTINFO), buff);
	int sendlen = sendto(sSockFd, buff, ret, 0, addr, sizeof(struct sockaddr));
	pthread_mutex_unlock(&NetCenterSem);
}

static BOOL CheckServerName(const char *name)
{
	if (*name == '\0')
		return FALSE;
	int ip[4];
	if (4 == sscanf(name, "%d.%d.%d.%d", &ip[0], &ip[1], &ip[2], &ip[3]))
	{
		if (   (ip[0] & 0xFFFFFF00) || (ip[1] & 0xFFFFFF00)
			|| (ip[2] & 0xFFFFFF00) || (ip[3] & 0xFFFFFF00) )
		{
			return TRUE;
		}
		return FALSE;
	}
	return TRUE;
}

static BOOL CheckNetPacket(void *buffer, int len)
{
	UCHAR *pBuf = (UCHAR *)buffer;
	if (NULL == pBuf || len < 17)
		return FALSE;
	
	if (0x55 != pBuf[0] || 0xAA != pBuf[1])
		return FALSE;

	UINT16 crc = 0;
	crc = crc16(crc, pBuf, len - 2);
	if (LOBYTE(crc) != pBuf[len - 2])
		return FALSE;

	UINT32 number = MAKELPARAM2(pBuf[11], pBuf[12], pBuf[13], pBuf[14]);
	if (number != GetMachineNumber())
		return FALSE;

	return TRUE;
}

static void sSendUdpPacket(int len, void *buffer)
{
	static int packNum = 0;
	UINT16 packet_id = (len > 12)?PKG_0x5C:PKG_0x2E;//>12发病人信息 以@ptnifno开始
	int packlen = 
		sNetBuildPacket(packet_id, FALSE, packNum, buffer, len, sNetSendBuffer);

	int sendlen = sendto (sSockFd, sNetSendBuffer, packlen, 0,
		(struct sockaddr*)&sToAddr, sizeof(struct sockaddr));
	//for (; sendlen > 0; sendlen--)
	//	printf("sNetSendBuffer[%d] =%X\n", sendlen - 1, sNetSendBuffer[sendlen - 1]);
	packNum++;
}

static void sRecePacketProcess(int len, void *buffer)
{
	UCHAR *pBuf = (UCHAR *)buffer;
	if (MAKEWORD(pBuf[2], pBuf[3]) < 18)
		return;
	if (sTranConnectFalg == FALSE)
	{
		PostMessage(SysUdpT_HTSK, MSG_NET_UDP_CONNECT, 0, 0);
	}
	
	SetNetReceivePacketCount(TRUE);
	
}

static void sResetAddr(void)
{
	if (CheckServerName((char*)NetConfig.server))
	{
		struct hostent *host = NULL;
		host = gethostbyname((char*)NetConfig.server);
		if (NULL != host)
		{
			return;
		}
		char *addr = inet_ntoa(*((struct in_addr *)host->h_addr));
		if (addr == NULL)
		{
			return;
		}
		pthread_mutex_lock(&NetCenterSem);
		memset(&sFromAddr, 0, sizeof(struct sockaddr_in));
		sFromAddr.sin_addr.s_addr	= inet_addr(addr);
//		sFromAddr.sin_addr			= *((struct in_addr *)host->h_addr);
	}
	else
	{
		pthread_mutex_lock(&NetCenterSem);
		memset(&sFromAddr, 0, sizeof(struct sockaddr_in));
		sFromAddr.sin_addr.s_addr	= inet_addr(NetConfig.server);
	}
	sFromAddr.sin_family		= AF_INET;
	sFromAddr.sin_port			= htons(NetConfig.port);
	memcpy (&sToAddr, &sFromAddr, sizeof(sFromAddr));
	pthread_mutex_unlock(&NetCenterSem);
	sRecResetFlag = FALSE;
}

int SetNetStatus(VOID)
{
	if(GetNetworkStatus())
	{
		if (sTranConnectFalg)
		{
			pNetIcon = net_icon[MonitorConfig.nightModeOn];
			gNetStatus = 1;
			return 1;
		}
		else
		{
			pNetIcon = ulnet_icon[MonitorConfig.nightModeOn];
			gNetStatus = 0;
			return 0;
		}
	}
	else
	{
		pNetIcon = nonet_icon[MonitorConfig.nightModeOn];
		gNetStatus = -1;
		return -1;
	}
}


/*****************************************************************************
* Function    : NetTranTskProc
* Description : net work transport message process
* Input Para  : 
* Output Para : 
* Return Value: 
*****************************************************************************/
INT32 NetTranTskProc(HANDLE hdl, INT32 msg, UINT32 wParam, UINT32 lParam)
{
	switch (msg)
	{
		case MSG_NET_TCP_SETUP:
			break;

		case MSG_NET_TCP_CONNECT:
			break;

		case MSG_NET_TCP_SEND:
//			printf("NetTranTskProc::MSG_NET_TCP_SEND:\n\t");
//			printf("size %d, ptr %p\n", wParam, (int*)lParam);
			break;

		case MSG_NET_TCP_LISTEN:
			break;

		case MSG_NET_TCP_CLOSE:
			break;

		case MSG_NET_UDP_SETUP:
			SendMessage(SysUdpT_HTSK, MSG_NET_UDP_DISCONNECT, 0, 0);
			InitNetSocket(&sSockFd);
			break;

		case MSG_NET_UDP_RESET:
			sRecResetFlag = TRUE;
			SendMessage(SysUdpT_HTSK, MSG_NET_UDP_DISCONNECT, 0, 0);
			sResetAddr();
			break;

		case MSG_NET_UDP_QUERY:
			sPostConnectPacket (sTranConnectFalg);
			break;

		case MSG_NET_UDP_CONNECT:
			sTranConnectFalg = TRUE;
			sPostInformationPacket();
			sPostInformationPacket();
			sPostInformationPacket();
			break;

		case MSG_NET_UDP_SEND:
			if (sTranConnectFalg)
				sSendUdpPacket((int)wParam, (UCHAR*)lParam);
			//printf("NetTranTskProc::MSG_NET_UDP_SEND:\n\t");
			//printf("size %d, ptr %p\n", wParam, (int*)lParam);
			break;

		case MSG_NET_UDP_DISCONNECT:
			sTranConnectFalg = FALSE;
			break;

		case MSG_NET_UDP_COMMAND:
			sRecePacketProcess((int)wParam, (UCHAR*)lParam);
			break;

		default:
			break;
	}
	return DefaultTskProc(hdl, msg, wParam,lParam);
}

/*****************************************************************************
* Function    : TskNetRece
* Description : 
* Input Para  : 
* Output Para : 
* Return Value: 
*****************************************************************************/
void TskNetRece(void *pdata)
{
	pdata = pdata;

	int len;
	int addrlen = sizeof(struct sockaddr_in);
	struct sockaddr_in from_addr;
	char *recebuf = NULL;
	
	recebuf = (char *)malloc(1024);//1K
	
	ms_sleep(2000);
	
	while(TRUE)
	{
		// wait for sSockFd init
		if (INVALID_SOCKET < sSockFd)
		{
			break;
		}
		ms_sleep(1000);
	}
	
	while(TRUE)
	{
		// wait for NetCenterSem unlock
		pthread_mutex_lock(&NetCenterSem);
		if (KillSignal)
		{
			KillSignal++;
			break;
		}
		pthread_mutex_unlock(&NetCenterSem);
		// receive packet from server
		len = (int)recvfrom(sSockFd, recebuf, 1024, 0,
						(struct sockaddr *)&sFromAddr, (socklen_t *)&addrlen);
		if (len > 2)
		{
			if (CheckNetPacket(recebuf, len))
			{
				PostMessage(SysUdpT_HTSK, MSG_NET_UDP_COMMAND, 
					(WPARAM)len, (LPARAM)recebuf);
			}
		}
		ms_sleep(OS_TICK_TIME);
	}
	free(recebuf);
	if (KillSignal > 1)
		KillSignal--;
}

