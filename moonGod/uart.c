/******************************************************************************
***********
版权所有:			和心重典
版本号:				1.0.0
生成日期:			2010.05.11
文件名:				
作者:				ZONDAN
功能说明:			应用层主文件
其它说明:			arm平台下异步串口驱动实现;
所属文件关系:		本文件为工程规约代码文件

修改记录:
记录1:
修改者:
修改日期:
修改内容:
修改原因:
*******************************************************************************
**********/
#define  UART_GLOBALS
#include "includes.h"
#include <stdio.h>		  /*标准输入输出定义*/
#include <stdlib.h>		 /*标准函数库定义*/
#include <string.h>
#include <unistd.h>		 /*Unix 标准函数定义*/
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>		  /*文件控制定义*/
#include <errno.h>		  /*错误号定义*/
#include <sys/ioctl.h>
#include <signal.h>
#include <termios.h>		/*PPSIX 终端控制定义*/

static const int Baud_Rate[BR_MAX] = 
{
	0,
	0,
	0,
	0,
	0,
	B2400,
	B4800,
	B9600,
	B19200,
	B38400,
	B57600,
	0,
	B115200
};


static const int Data_Bits[DBTS_MAX] = 
{
	0x00,
	0x00,
	DBTS_7,
	DBTS_8
};


static const int Stop_Bits[STOPBITS_MAX] = 
{
	STOPBITS_1,
	0,
	STOPBITS_2
};


static const int Parity_Mode[PARITY_MAX] = 
{
	PARITY_ODD,
	PARITY_EVEN,
	PARITY_NO
};


/**
*@brief  设置串口通信速率
*@param  fd	 类型 int  打开串口的文件句柄
*@param  speed  类型 int  串口速度
*@return  void
*/
void myinit_com(int fd, int baud_rate, int databits, int stopbits, int parity)
{
	struct termios options; 

	tcgetattr(fd, &options);
	tcflush(fd, TCIOFLUSH);
	cfsetispeed(&options, baud_rate);
	cfsetospeed(&options, baud_rate);
	options.c_cflag &= ~CSIZE;
	switch(8)
	{	
		case 7:
		options.c_cflag |= CS7;
		break;

		case 8:			
		options.c_cflag |= CS8;											// 8bit
		break;

		default:
		printf("Unsupported data size\n");
	}
	switch ('N')
	{
		case 'n':
		case 'N':
			options.c_cflag &= ~PARENB;										// Clear parity enable 
			options.c_iflag &= ~(ICRNL | IXON);
			break;

		case 'o':
		case 'O':
			options.c_cflag |= (PARODD | PARENB);							// Set parity 
			options.c_iflag |= INPCK;										// Disnable parity checking 
			options.c_iflag &= ~(ICRNL | IXON);
			break;

		case 'e':
		case 'E':
			options.c_cflag |= PARENB;										// Enable parity 
			options.c_cflag &= ~PARODD;										// Even parity  
			options.c_iflag |= INPCK;										// Disnable parity checking 
			options.c_iflag &= ~(ICRNL | IXON);
			break;

		case 'S':
		case 's':															// as no parity
			options.c_cflag &= ~PARENB;
			options.c_cflag &= ~CSTOPB;
			break;

		default:
			printf("Unsupported parity\n");
	}
	if (parity == PARITY_ODD)
	{
		options.c_cflag |= (PARODD | PARENB);	// Set parity
		options.c_iflag |= INPCK;				// Disnable parity checking
		options.c_iflag &= ~(ICRNL | IXON);
	}
	
	if (parity == PARITY_EVEN)
	{
		options.c_cflag |= PARENB;				// Enable parity
		options.c_cflag &= ~PARODD;				// Even parity
		options.c_iflag |= INPCK;				// Disnable parity checking
		options.c_iflag &= ~(ICRNL | IXON);
	}	 
	switch (1)
	{
		case 1:
			options.c_cflag &= ~CSTOPB;
			break;

		case 2:
			options.c_cflag |= CSTOPB;
			break;

		default:
			break;
	}
	options.c_cc[VTIME] = 6;												//15 seconds
	options.c_cc[VMIN] = 0;
	options.c_lflag &= ~(ICANON | ECHO | ECHOE | ISIG);
	options.c_oflag &= ~(OPOST);
	tcflush(fd,TCIFLUSH);													//Update the options and do it NOW
	if (tcsetattr(fd, TCSANOW, &options) != 0)
	{
		;
	} 
}

#if 0
static void set_baud_rate(int fd, int baud_rate)
{
	int	i; 
	int	status; 
	struct termios opt;
	
	tcgetattr(fd, &opt);
	tcflush(fd, TCIOFLUSH);	 
	cfsetispeed(&opt, baud_rate);  
	cfsetospeed(&opt, baud_rate);   
	if (status != 0) 
	{
		;
	}
}
#endif

/**
*@brief   设置串口数据位，停止位和效验位
*@param  fd	 类型  int  打开的串口文件句柄
*@param  databits 类型  int 数据位   取值为 7 或者8
*@param  stopbits 类型  int 停止位   取值为 1 或者2
*@param  parity  类型  int  效验类型 取值为N, E, O, , S
*/
int set_parity(int fd, int databits, int stopbits, int parity)
{
	struct termios options;
	
	if  (tcgetattr(fd, &options) != 0)
	{ 
		return 0;  
	}
	memset(&options, 0, sizeof(struct termios)); //特别重要！一定要将结构清0。   
	options.c_cflag &= ~CSIZE; 
	switch (databits) /* 设置数据位数 */
	{   
		case DBTS_7:
			options.c_cflag |= CS7;
			break;
		
		case DBTS_8:
			options.c_cflag |= CS8;
			break;   
		
		default:
			return 0;  
	}
	switch (parity) 
	{   
		case PARITY_NO:	
		options.c_cflag &= ~PARENB;			 /* Clear parity enable */
		options.c_iflag &= ~(ICRNL | IXON);
		break;  
		
		case PARITY_ODD:	 
		options.c_cflag |= (PARODD | PARENB);   /* 设置为奇效验*/  
		options.c_iflag |= INPCK;			   /* Disnable parity checking */ 
		options.c_iflag &= ~(ICRNL | IXON);
		break;  
		
		case PARITY_EVEN:   
			options.c_cflag |= PARENB;		  /* Enable parity */	
			options.c_cflag &= ~PARODD;		 /* 转换为偶效验*/	 
			options.c_iflag |= INPCK;		   /* Disnable parity checking */
			options.c_iflag &= ~(ICRNL | IXON);
			break;
		
		default:   
			printf("unsopport \n");
			return 0;  
	}
	options.c_iflag &= ~(BRKINT | ICRNL | INPCK | ISTRIP | IXON);
	/* 设置停止位*/  
	switch (stopbits)
	{
		case STOPBITS_1:
			options.c_cflag &= ~CSTOPB;  
			break;
		
		case STOPBITS_2:	
			options.c_cflag |= CSTOPB;  
			break;
		
		default:	
			return 0; 
	}
	tcflush(fd, TCIFLUSH);
	options.c_cc[VTIME] = 20; /* 设置超时1秒*/   
	options.c_cc[VMIN]  = 0; /* Update the options and do it NOW */
	options.c_lflag	 &= ~(ICANON | ECHO | ECHOE | ISIG); /*Input*/
	options.c_oflag	 &= ~OPOST; /*Output*/
	options.c_oflag	 = 0;   
	options.c_lflag	 = 0;
	if (tcsetattr(fd, TCSANOW, &options) != 0)   
	{ 
		return 0;  
	} 
	return 1;  
}


static int open_port(const char *ptDev)
{
	int	fd = open(ptDev, O_RDWR | O_NOCTTY);

	//printf ("open_port: fd, ptDev ... %d, %s\r\n", fd, ptDev); //pengyang
	if (-1 == fd)
	{
		traceout("Can't Open Serial Port \n");
		return -1;
	}	
	else	
	{
		return fd;
	}
}


static int Uart_Fd[COMMAX] =
{
	INVALID_UART_DEV,   //COM1
	INVALID_UART_DEV,   //COM2
	INVALID_UART_DEV,   //COM3
	INVALID_UART_DEV,   //COM4
	INVALID_UART_DEV,   //COM5
	INVALID_UART_DEV,   //COM6
	INVALID_UART_DEV,   //COM7
	INVALID_UART_DEV,   //COM8
	INVALID_UART_DEV,   //COM9
};


static STATUS common_init(INT port)
{
	int  rtn;
	char ptDev[32];

#if _ENB_UART_FOR_2416_DEBUG
	if (INVALID_UART_DEV != Uart_Fd[port])
	{
		//printf ("common_init: close Uart_Fd[%d] ... 0x%02x\r\n", port, Uart_Fd[port]); //pengyang
		close(Uart_Fd[port]);
		Uart_Fd[port] = INVALID_UART_DEV;
	}
#endif
	if (port == COM1)
	{
		sprintf(ptDev, "/dev/ttySAC1");
	}
	else if (port == COM2)
	{
		sprintf(ptDev, "/dev/ttySAC2");
	}
	else if (port == COM3)
	{
		//sprintf(ptDev, "/dev/ttySAC0");
		sprintf(ptDev, "/dev/ttySAC3"); // mark by gjl for debug printer 2013-09-10
	}
	else if (port == COM4)
	{
		sprintf(ptDev, "/dev/ttyS0");
	}
	else if (port == COM5)
	{
		sprintf(ptDev, "/dev/ttyS1");
	}
	else if (port == COM6)
	{
		sprintf(ptDev, "/dev/ttyS2");
	}
	else if (port == COM7)
	{
		sprintf(ptDev, "/dev/ttyS3");
	}
	else if (port == COM8)
	{
		sprintf(ptDev, "/dev/ttyS4");
	}
	else if (port == COM9)
	{
		sprintf(ptDev, "/dev/ttyS5");
	}
	{
//		prinfo("open uart port:%s(COM%d)\r\n", ptDev, port + 1);
		rtn = open_port(ptDev);
//		prinfo("open uart port:rtn %p\r\n", rtn);
		Uart_Fd[port] = rtn;
	}
	return UART_OK;
} 


/*********************************************************************************************************
** 函数名称: UART0_Setup
** 功能描述: 设置串口
** 输　入:   configP,  配置项;波特率,数据位,停止位,检验位
** 输　出:   
** 全局变量: 无
** 调用模块: bioscom
**
********************************************************************************************************/
static VOID common_setup(int port, const UART_CONFIG *configP)
{
	int		 br;
	int		 stop;
	int		 db;
	int		 parity;
	
	br		  = Baud_Rate[configP->baudRate];
	stop		= Stop_Bits[configP->stopBits];
	db		  = Data_Bits[configP->dataBits];
	parity	  = Parity_Mode[configP->parity];
	myinit_com(Uart_Fd[port], br, db, stop, parity);
} 


/*********************************************************************************************************
** 函数名称: UART0_PutCh
** 功能描述: 发送一个字节数据
** 输　入:   Data:发送数据
**		 
** 输　出:无
** 全局变量: 无
** 调用模块: bioscom
********************************************************************************************************/
static STATUS  common_putch (int port, UINT8 data)
{
	return UART_OK;//(rtn == 1) ? UART_OK : UART_NO_OK;
} 


/*********************************************************************************************************
** 函数名称: UART0_Getch
** 功能描述: 接收一个字节
** 输　入: 接收数据保存的地址
** 输　出: 接收到的数据
** 返回  : false, 没有收到;true, 收到
** 全局变量: 无
** 调用模块: 无
** 说明:   
********************************************************************************************************/
static STATUS  common_getch (int port, UINT8 *bufP)
{
	int rtn = read(Uart_Fd[port], bufP, 1);
	return (rtn == 1) ? UART_OK : UART_NO_OK;
} 


static INT32 common_putstr (int port, UINT8* dataP, INT32 toSend )
{
	int rtn =  write(Uart_Fd[port], dataP, toSend);
	if (rtn != 1)
	{
		;
	}
	return rtn;
}


static INT32 common_getstr (int port, UINT8* dataP, INT32 toRead )
{
	int available_bytes = 0;
	
	ioctl(Uart_Fd[port], FIONREAD, &available_bytes);  
	int rtn = 0;
	if (available_bytes > 0)
	{
		rtn = read(Uart_Fd[port], dataP, toRead);
	}
	return rtn;
}


/*********************************************************************************************************
** 函数名称: UART0_CheckStatus
** 功能描述: 取得UART0状态字
** 输　入: 无
**
** 输　出: 无
**		 
** 全局变量: 无
** 调用模块: bioscom
**
********************************************************************************************************/
static UINT32 common_checkstatus (int port)
{
	int status = 0;

	return (MAKELONG(status, 0));
}


static VOID common_reset(int port)
{
	int  rtn = 0;
	char buff[128];

	while((rtn = read(Uart_Fd[port], buff, 128)) > 0);
}


/*********************************************************************************************************
** 函数名称: UART0_Init
** 功能描述: 初始化UART0;创建了发送和接收的队列
** 输　入:   发送和接收队列的长度
**
** 输　出:
**		
** 全局变量: Uart0_SendQ, Uart0_RcvQ
** 调用模块: 
**
********************************************************************************************************/
STATUS Uart0_Init(void)
{
	return common_init(COM1);
} 


STATUS Uart1_Init(void)
{
	return common_init(COM2);
} 


STATUS Uart2_Init(void)
{
	return common_init(COM3);
} 


STATUS Uart3_Init(void)
{
	return common_init(COM4);
} 


STATUS Uart4_Init(void)
{
	return common_init(COM5);
} 


STATUS Uart5_Init(void)
{
	return common_init(COM6);
} 


STATUS Uart6_Init(void)
{
	return common_init(COM7);
} 


STATUS Uart7_Init(void)
{
	return common_init(COM8);
} 


STATUS Uart8_Init(void)
{
	return common_init(COM9);
}


/*********************************************************************************************************
** 函数名称: UART0_Setup
** 功能描述: 设置串口
** 输　入:   configP,  配置项;波特率,数据位,停止位,检验位
** 输　出:   
** 全局变量: 无
** 调用模块: bioscom
**
********************************************************************************************************/
VOID Uart0_Setup(const UART_CONFIG *configP)
{
	common_setup(COM1,configP);
} 


VOID Uart1_Setup(const UART_CONFIG *configP)
{
	common_setup(COM2,configP);
} 


VOID Uart2_Setup(const UART_CONFIG *configP)
{
	common_setup(COM3,configP);
} 


VOID Uart3_Setup(const UART_CONFIG *configP)
{
	common_setup(COM4,configP);
} 


VOID Uart4_Setup(const UART_CONFIG *configP)
{
	common_setup(COM5,configP);
} 


VOID Uart5_Setup(const UART_CONFIG *configP)
{
	common_setup(COM6,configP);
} 


VOID Uart6_Setup(const UART_CONFIG *configP)
{
	common_setup(COM7,configP);
} 


VOID Uart7_Setup(const UART_CONFIG *configP)
{
	common_setup(COM8,configP);
} 


VOID Uart8_Setup(const UART_CONFIG *configP)
{
	common_setup(COM9,configP);
} 


/*********************************************************************************************************
** 函数名称: UART0_PutCh
** 功能描述: 发送一个字节数据
** 输　入:   Data:发送数据
**		 
** 输　出:无
** 全局变量: 无
** 调用模块: bioscom
********************************************************************************************************/
STATUS Uart0_PutCh(UINT8 data)
{
	return common_putch(COM1, data);
} 


STATUS Uart1_PutCh(UINT8 data)
{
	return common_putch(COM2, data);
} 


STATUS Uart2_PutCh(UINT8 data)
{
	return common_putch(COM3, data);
} 


STATUS Uart3_PutCh(UINT8 data)
{
	return common_putch(COM4, data);
} 


STATUS Uart4_PutCh(UINT8 data)
{
	return common_putch(COM5, data);
} 


STATUS Uart5_PutCh(UINT8 data)
{
	return common_putch(COM6, data);
} 


STATUS Uart6_PutCh(UINT8 data)
{
	return common_putch(COM7, data);
} 


STATUS Uart7_PutCh(UINT8 data)
{
	return common_putch(COM8, data);
} 


STATUS Uart8_PutCh(UINT8 data)
{
	return common_putch(COM9, data);
} 


/*********************************************************************************************************
** 函数名称: UART0_Getch
** 功能描述: 接收一个字节
** 输　入: 接收数据保存的地址
** 输　出: 接收到的数据
** 返回  : false, 没有收到;true, 收到
** 全局变量: 无
** 调用模块: 无
** 说明:   
********************************************************************************************************/
STATUS Uart0_Getch(UINT8 *bufP)
{
	return common_getch(COM1,bufP);
} 


STATUS Uart1_Getch(UINT8 *bufP)
{
	return common_getch(COM2,bufP);
} 


STATUS Uart2_Getch(UINT8 *bufP)
{
	return common_getch(COM3,bufP);
} 


STATUS Uart3_Getch(UINT8 *bufP)
{
	return common_getch(COM4,bufP);
} 


STATUS Uart4_Getch(UINT8 *bufP)
{
	return common_getch(COM5,bufP);
} 


STATUS Uart5_Getch(UINT8 *bufP)
{
	return common_getch(COM6,bufP);
} 


STATUS Uart6_Getch(UINT8 *bufP)
{
	return common_getch(COM7,bufP);
} 


STATUS Uart7_Getch(UINT8 *bufP)
{
	return common_getch(COM8,bufP);
} 


STATUS Uart8_Getch(UINT8 *bufP)
{
	return common_getch(COM9,bufP);
} 


/*********************************************************************************************************
** 函数名称: UART0_CheckStatus
** 功能描述: 取得UART0状态字
** 输　入: 无
**
** 输　出: 无
**		 
** 全局变量: 无
** 调用模块: bioscom
**
********************************************************************************************************/
UINT32 Uart0_CheckStatus(VOID)
{
	return common_checkstatus(COM1);
}

UINT32 Uart1_CheckStatus(VOID)
{
	return common_checkstatus(COM2);
}

UINT32 Uart2_CheckStatus(VOID)
{
	return common_checkstatus(COM3);
}

UINT32 Uart3_CheckStatus(VOID)
{
	return common_checkstatus(COM4);
}

UINT32 Uart4_CheckStatus(VOID)
{
	return common_checkstatus(COM5);
}

UINT32 Uart5_CheckStatus(VOID)
{
	return common_checkstatus(COM6);
}

UINT32 Uart6_CheckStatus(VOID)
{
	return common_checkstatus(COM7);
}

UINT32 Uart7_CheckStatus(VOID)
{
	return common_checkstatus(COM8);
}

UINT32 Uart8_CheckStatus(VOID)
{
	return common_checkstatus(COM9);
}


VOID Uart0_Reset(VOID) 
{
	common_reset(COM1);
}


VOID Uart1_Reset(VOID) 
{
	common_reset(COM2);
}


VOID Uart2_Reset(VOID) 
{
	common_reset(COM3);
}


VOID Uart3_Reset(VOID) 
{
	common_reset(COM4);
}


VOID Uart4_Reset(VOID) 
{
	common_reset(COM5);
}


VOID Uart5_Reset(VOID) 
{
	common_reset(COM6);
}


VOID Uart6_Reset(VOID) 
{
	common_reset(COM7);
}


VOID Uart7_Reset(VOID) 
{
	common_reset(COM8);
}


VOID Uart8_Reset(VOID) 
{
	common_reset(COM9);
}


INT32 Uart0_PutStr(UINT8* dataP, INT32 toSend) 
{
	return common_putstr(COM1, dataP, toSend);
}


INT32 Uart0_GetStr(UINT8* dataP, INT32 toRead) 
{
	return common_getstr(COM1, dataP, toRead);
}


INT32 Uart1_PutStr(UINT8* dataP, INT32 toSend) 
{
	return common_putstr(COM2, dataP, toSend);
}


INT32 Uart1_GetStr(UINT8* dataP, INT32 toRead) 
{
	return common_getstr(COM2, dataP, toRead);
}


INT32 Uart2_PutStr(UINT8* dataP, INT32 toSend) 
{
	return common_putstr(COM3, dataP, toSend);
}


INT32 Uart2_GetStr(UINT8* dataP, INT32 toRead) 
{
	return common_getstr(COM3, dataP, toRead);
}


INT32 Uart3_PutStr(UINT8* dataP, INT32 toSend) 
{
	return common_putstr(COM4, dataP, toSend);
}


INT32 Uart3_GetStr(UINT8* dataP, INT32 toRead) 
{
	return common_getstr(COM4, dataP, toRead);
}


INT32  Uart4_PutStr (UINT8* dataP, INT32 toSend) 
{
	return common_putstr(COM5, dataP, toSend);
}


INT32  Uart4_GetStr (UINT8* dataP, INT32 toRead) 
{
	return common_getstr(COM5, dataP, toRead);
}


INT32  Uart5_PutStr (UINT8* dataP, INT32 toSend) 
{
	return common_putstr(COM6, dataP, toSend);
}


INT32  Uart5_GetStr (UINT8* dataP, INT32 toRead) 
{
	return common_getstr(COM6, dataP, toRead);
}


INT32  Uart6_PutStr (UINT8* dataP, INT32 toSend) 
{
	return common_putstr(COM7, dataP, toSend);
}


INT32  Uart6_GetStr (UINT8* dataP, INT32 toRead) 
{
	return common_getstr(COM7, dataP, toRead);
}


INT32  Uart7_PutStr (UINT8* dataP, INT32 toSend) 
{
	return common_putstr(COM8, dataP, toSend);
}


INT32  Uart7_GetStr (UINT8* dataP, INT32 toRead) 
{
	return common_getstr(COM8, dataP, toRead);
}


INT32  Uart8_PutStr (UINT8* dataP, INT32 toSend) 
{
	return common_putstr(COM9, dataP, toSend);
}


INT32  Uart8_GetStr (UINT8* dataP, INT32 toRead) 
{
	return common_getstr(COM9, dataP, toRead);
}


VOID Uart0_CheckInfo(UART_INFO *infoP)
{
	UNREFRENCED_PARAMETERS(infoP);   
}


VOID Uart0_TxCtrl(UART_OPERATION opr)
{
	UNREFRENCED_PARAMETERS(opr);   
}


VOID Uart0_RcvCtrl(UART_OPERATION opr)
{
	UNREFRENCED_PARAMETERS(opr);   
}


UART_DRV Uart0_Driver = 
{  
   Uart0_Init,											   /* 初始化；需要指定接收和发送缓冲区的大小；   */
   Uart0_Reset,											  /* Reset									  */
   Uart0_PutStr,											 /* 发送一组字节的数据						 */
   Uart0_PutCh,											  /* 发送一个字节的数据						 */
   Uart0_GetStr,											 /* 读取指定长度的数据；返回实际读取的数据长度 */
   Uart0_Getch,											  /* 读取一个字节数据						   */
   Uart0_CheckStatus,										/* 读取串口线的状态						   */
   Uart0_CheckInfo,										  /* 读取串口接收、发送的信息				   */
   Uart0_RcvCtrl,											/* 接收器的控制							   */
   Uart0_TxCtrl,											 /* 发送线的控制							   */
   Uart0_Setup,											  /* 设置串口								   */
   NULL,													 /* 串口的中断处理函数						 */
   NULL
};

UART_DRV Uart1_Driver = 
{  
   Uart1_Init,											   /* 初始化；需要指定接收和发送缓冲区的大小；   */
   Uart1_Reset,											  /* Reset									  */
   Uart1_PutStr,											 /* 发送一组字节的数据						 */
   Uart1_PutCh,											  /* 发送一个字节的数据						 */
   Uart1_GetStr,											 /* 读取指定长度的数据；返回实际读取的数据长度 */
   Uart1_Getch,											  /* 读取一个字节数据						   */
   Uart1_CheckStatus,										/* 读取串口线的状态						   */
   Uart0_CheckInfo,										  /* 读取串口接收、发送的信息				   */
   Uart0_RcvCtrl,											/* 接收器的控制							   */
   Uart0_TxCtrl,											 /* 发送线的控制							   */
   Uart1_Setup,											  /* 设置串口								   */
   NULL,													 /* 串口的中断处理函数						 */
   NULL
};

UART_DRV Uart2_Driver = 
{  
   Uart2_Init,											   /* 初始化；需要指定接收和发送缓冲区的大小；   */
   Uart2_Reset,											  /* Reset									  */
   Uart2_PutStr,											 /* 发送一组字节的数据						 */
   Uart2_PutCh,											  /* 发送一个字节的数据						 */
   Uart2_GetStr,											 /* 读取指定长度的数据；返回实际读取的数据长度 */
   Uart2_Getch,											  /* 读取一个字节数据						   */
   Uart2_CheckStatus,										/* 读取串口线的状态						   */
   Uart0_CheckInfo,										  /* 读取串口接收、发送的信息				   */
   Uart0_RcvCtrl,											/* 接收器的控制							   */
   Uart0_TxCtrl,											 /* 发送线的控制							   */
   Uart2_Setup,											  /* 设置串口								   */
   NULL,													 /* 串口的中断处理函数						 */
   NULL
};

UART_DRV Uart3_Driver = 
{  
   Uart3_Init,											   /* 初始化；需要指定接收和发送缓冲区的大小；   */
   Uart3_Reset,											  /* Reset									  */
   Uart3_PutStr,											 /* 发送一组字节的数据						 */
   Uart3_PutCh,											  /* 发送一个字节的数据						 */
   Uart3_GetStr,											 /* 读取指定长度的数据；返回实际读取的数据长度 */
   Uart3_Getch,											  /* 读取一个字节数据						   */
   Uart3_CheckStatus,										/* 读取串口线的状态						   */
   Uart0_CheckInfo,										  /* 读取串口接收、发送的信息				   */
   Uart0_RcvCtrl,											/* 接收器的控制							   */
   Uart0_TxCtrl,											 /* 发送线的控制							   */
   Uart3_Setup,											  /* 设置串口								   */
   NULL,													 /* 串口的中断处理函数						 */
   NULL
};

UART_DRV Uart4_Driver = 
{  
   Uart4_Init,											   /* 初始化；需要指定接收和发送缓冲区的大小；   */
   Uart4_Reset,											  /* Reset									  */
   Uart4_PutStr,											 /* 发送一组字节的数据						 */
   Uart4_PutCh,											  /* 发送一个字节的数据						 */
   Uart4_GetStr,											 /* 读取指定长度的数据；返回实际读取的数据长度 */
   Uart4_Getch,											  /* 读取一个字节数据						   */
   Uart4_CheckStatus,										/* 读取串口线的状态						   */
   Uart0_CheckInfo,										  /* 读取串口接收、发送的信息				   */
   Uart0_RcvCtrl,											/* 接收器的控制							   */
   Uart0_TxCtrl,											 /* 发送线的控制							   */
   Uart4_Setup,											  /* 设置串口								   */
   NULL,													 /* 串口的中断处理函数						 */
   NULL
};

UART_DRV Uart5_Driver = 
{  
   Uart5_Init,											   /* 初始化；需要指定接收和发送缓冲区的大小；   */
   Uart5_Reset,											  /* Reset									  */
   Uart5_PutStr,											 /* 发送一组字节的数据						 */
   Uart5_PutCh,											  /* 发送一个字节的数据						 */
   Uart5_GetStr,											 /* 读取指定长度的数据；返回实际读取的数据长度 */
   Uart5_Getch,											  /* 读取一个字节数据						   */
   Uart5_CheckStatus,										/* 读取串口线的状态						   */
   Uart0_CheckInfo,										  /* 读取串口接收、发送的信息				   */
   Uart0_RcvCtrl,											/* 接收器的控制							   */
   Uart0_TxCtrl,											 /* 发送线的控制							   */
   Uart5_Setup,											  /* 设置串口								   */
   NULL,													 /* 串口的中断处理函数						 */
   NULL
};

UART_DRV Uart6_Driver =
{  
   Uart6_Init,											   /* 初始化；需要指定接收和发送缓冲区的大小；   */
   Uart6_Reset,											  /* Reset									  */
   Uart6_PutStr,											 /* 发送一组字节的数据						 */
   Uart6_PutCh,											  /* 发送一个字节的数据						 */
   Uart6_GetStr,											 /* 读取指定长度的数据；返回实际读取的数据长度 */
   Uart6_Getch,											  /* 读取一个字节数据						   */
   Uart6_CheckStatus,										/* 读取串口线的状态						   */
   Uart0_CheckInfo,										  /* 读取串口接收、发送的信息				   */
   Uart0_RcvCtrl,											/* 接收器的控制							   */
   Uart0_TxCtrl,											 /* 发送线的控制							   */
   Uart6_Setup,											  /* 设置串口								   */
   NULL,													 /* 串口的中断处理函数						 */
   NULL
};

UART_DRV Uart7_Driver = 
{  
   Uart7_Init,											   /* 初始化；需要指定接收和发送缓冲区的大小；   */
   Uart7_Reset,											  /* Reset									  */
   Uart7_PutStr,											 /* 发送一组字节的数据						 */
   Uart7_PutCh,											  /* 发送一个字节的数据						 */
   Uart7_GetStr,											 /* 读取指定长度的数据；返回实际读取的数据长度 */
   Uart7_Getch,											  /* 读取一个字节数据						   */
   Uart7_CheckStatus,										/* 读取串口线的状态						   */
   Uart0_CheckInfo,										  /* 读取串口接收、发送的信息				   */
   Uart0_RcvCtrl,											/* 接收器的控制							   */
   Uart0_TxCtrl,											 /* 发送线的控制							   */
   Uart7_Setup,											  /* 设置串口								   */
   NULL,													 /* 串口的中断处理函数						 */
   NULL
};

UART_DRV Uart8_Driver =
{  
   Uart8_Init,											   /* 初始化；需要指定接收和发送缓冲区的大小；   */
   Uart8_Reset,											  /* Reset									  */
   Uart8_PutStr,											 /* 发送一组字节的数据						 */
   Uart8_PutCh,											  /* 发送一个字节的数据						 */
   Uart8_GetStr,											 /* 读取指定长度的数据；返回实际读取的数据长度 */
   Uart8_Getch,											  /* 读取一个字节数据						   */
   Uart8_CheckStatus,										/* 读取串口线的状态						   */
   Uart0_CheckInfo,										  /* 读取串口接收、发送的信息				   */
   Uart0_RcvCtrl,											/* 接收器的控制							   */
   Uart0_TxCtrl,											 /* 发送线的控制							   */
   Uart8_Setup,											  /* 设置串口								   */
   NULL,													 /* 串口的中断处理函数						 */
   NULL
};


/* 系统串口驱动数组 */
const  UART_DRV* UartDriver[COMMAX] = 
{
#if _ENB_COM1 > 0
	&Uart0_Driver,
#else
	0,
#endif

#if _ENB_COM2 > 0
	&Uart1_Driver,
#else
	0,
#endif

#if _ENB_COM3 > 0
	&Uart2_Driver,
#else
	0,
#endif

#if _ENB_COM4 > 0
	&Uart3_Driver,
#else
	0,
#endif

#if _ENB_COM5 > 0
	&Uart4_Driver,
#else
	0,
#endif

#if _ENB_COM6 > 0
	&Uart5_Driver,
#else
	0,
#endif

#if _ENB_COM7 > 0
	&Uart6_Driver,
#else
	0,
#endif

#if _ENB_COM8 > 0
	&Uart7_Driver,
#else
	0,
#endif

#if _ENB_COM9 > 0
	&Uart8_Driver,
#else
	0,
#endif
};
#define UartIsAvailabe(port)  (UartDriver[port])

/*
*********************************************************************************************************
* Function   :  打开串口					  
*
* Description:  对串口驱动和缓冲控制，作一些初始化工作＝⒒撼宥恿谢
*			  
* Input	  :  port,  端口号；
*
* Output	 :
*
* Calls	  :
*
* Called by  : 
*
* Returns	: 
*
* Note	   : 如果要使用串口；应该在setup串口以后再调用open；
*********************************************************************************************************
*/
STATUS UartOpen(UART_PORT port)
{
	STATUS   rtn;
	
	//prinfo("open port COM%d\n", port + 1);
	rtn = UART_NOAVAIL;
	if (UartIsAvailabe(port))
	{
		rtn = UartDriver[port]->Init();
	}
	ASSERT_REPORT(rtn==UART_OK);
	return rtn;
}


/*
*********************************************************************************************************
* Function   :  设置串口					  
*
* Description:  对串口驱动和缓冲控制，作一些初始化工作；
*			  
* Input	  :  port,	 端口号；
*			   configP,  设置的项目;
*
* Output	 :
*
* Calls	  :  UartDrvArray中驱动
*
* Called by  : 
*
* Returns	: 
*
* Note	   : 如果要使用串口；应该首先setup串口,以后再调用open；
*********************************************************************************************************
*/
VOID UartSetup(UART_PORT port, const UART_CONFIG* configP)
{
	if (UartIsAvailabe(port))
	{
		UartDriver[port]->Setup(configP);
	}
}


/*
*********************************************************************************************************
* Function   : 清除串口;
*
* Description: 清除所有错误信息;
*			  对串口进行重新设置;
*			  所有接收和未发送的数据全部丢失;
*			  
* Input	  : port, 端口
*			  
* Output	 :
*
* Calls	  :
*
* Called by  : 
*
* Returns	: 
*
* Note	   : 
*********************************************************************************************************
*/
VOID UartPurge(UART_PORT port)
{
	if (UartIsAvailabe(port)) 
	{
		UartDriver[port]->Reset();
	}
}

/*
*********************************************************************************************************
* Function   : 从串口读数据							 
*
* Description: 
*			  
* Input	  : port,	   端口
*			  bufP,	   用于保存数据的地址;
*			  toRead,	 指定要读取的数据长度;
*			  ReadP,	  实际读取的数据长度
*			  opt,		读取动作选项, 
* Output	 :
*
* Calls	  :
*
* Called by  : 
* Returns	: 
*
* Note	   : 
*********************************************************************************************************
*/
STATUS UartRead(UART_PORT port, UINT8 *bufP, INT32 toRead, INT32 *readP, OPTION opt)
{

//	long	  i;
//	UINT8	 data;
//	UINT8	*buffer;
//	STATUS	status;


//	buffer = bufP;
	opt	= opt;  /* prevent from compile warning  */
	
	if (!UartIsAvailabe(port))
	{
		*readP = 0;
		return UART_NO_OK; /* 指定端口没有驱动 */
	}
	*readP = UartDriver[port]->ReadString(bufP, toRead);
	return ((*readP == toRead) ? UART_OK: UART_NO_OK);
}


/*
*********************************************************************************************************
* Function   : 向串口写数据;发送数据;							 
*
* Description: 
*			  
* Input	  : port,	   端口
*			  bufP,	   发送数据的地址;
*			  toSend,	 指定要读取的数据长度;
*			  sendP,	  实际发送的数据长度
*			  opt,		发送动作选项, 
* Output	 :
*
* Calls	  :
*
* Called by  : 
* Returns	: 
*
* Note	   : 
*********************************************************************************************************
*/
STATUS UartWrite(UART_PORT port, UINT8 *bufP, INT32 toSend, INT32 *sendP, OPTION opt)
{
	if (!UartIsAvailabe(port)) 
	{
		return UART_NO_OK;
	}
	*sendP = UartDriver[port]->WriteString(bufP, toSend);
#if 0
	INT32 i;
	
	if (port == UART_PORT_KB)
	{
		for (i = 0; i < *sendP; i++)
		{
			printf ("UartWrite: UART_PORT_REC[%02d] ... 0x%02x\r\n", i, bufP[i]); //pengyang
		}
	}
#endif
	ASSERT_REPORT(i == toSend);
	return ((*sendP == toSend) ? UART_OK: UART_NO_OK);
}

#if 0
/*
*********************************************************************************************************
* Function   :  读取串口线的状态								
*
* Description: 
*			  
* Input	  : port,		 端口
*
* Output	 : 串口状态
*
* Calls	  :
*
* Called by  : 
*
* Returns	: 
*
* Note	   : 
*********************************************************************************************************
*/
UINT32 UartStatus(UART_PORT port)
{
	if (UartIsAvailabe(port))
	{
		return UartDriver[port]->GetStatus();
	}
	else
	{
		return 0;
	}
}

static int	RFID_serial_fd;
static struct termios Opt;


int InitRfidEnv(char  *pDeviceName)
{
	RFID_serial_fd = open( pDeviceName, O_RDWR);
	if (RFID_serial_fd==-1)
	{
		//printf("Open tty error\n");
	}
	Uart_Fd[COM3] = RFID_serial_fd;
	tcgetattr(RFID_serial_fd, &Opt);
	cfsetispeed(&Opt,B4800);
	cfsetospeed(&Opt,B4800);
	Opt.c_cflag &= ~CSTOPB;
	Opt.c_lflag  &= ~(ICANON | ECHO |IEXTEN|ECHOE | ISIG);  /*Input*/
	Opt.c_oflag  |= CS8;
	Opt.c_oflag  &= ~(OPOST|ONLCR|OCRNL);
	Opt.c_iflag  &=~(BRKINT|IXON|INLCR|IGNCR|ICRNL|ISTRIP);
}


void SetUart_2_NoParity()
{
	cfsetispeed(&Opt,B4800);
	cfsetospeed(&Opt,B4800);

	Opt.c_cflag &= ~PARENB;
	Opt.c_cflag &= ~CSTOPB;
	Opt.c_lflag  &= ~(ICANON | ECHO |IEXTEN|ECHOE | ISIG);
	Opt.c_oflag  |= CS8;
	Opt.c_oflag  &= ~(OPOST|ONLCR|OCRNL);
	Opt.c_iflag  &=~(BRKINT|IXON|INLCR|IGNCR|ICRNL|ISTRIP);

	tcflush(RFID_serial_fd,TCIFLUSH);
	tcflush(RFID_serial_fd,TCIOFLUSH);
	tcsetattr(RFID_serial_fd,TCSANOW,&Opt);
	usleep(1000);
}
#endif

/********************** 初始化 UART口********************/
BOOL InitUart(VOID)
{
	UART_CONFIG config;

#if _ENB_COM1 > 0
	config.baudRate = BR_4800; 
	config.parity   = PARITY_NO;
	config.dataBits = DBTS_8;
	config.stopBits = STOPBITS_1;
	if (UartOpen(COM1) < 0)
	{
		goto error;
	}
	UartSetup(COM1, &config);
#endif

#if _ENB_COM2 > 0
	config.baudRate = BR_4800;
	config.parity   = PARITY_NO;
	config.dataBits = DBTS_8;
	config.stopBits = STOPBITS_1;
	if (UartOpen(COM2) < 0)
	{
		goto error;
	}
	UartSetup(COM2, &config);
#endif

#if  _ENB_COM3 > 0
	config.baudRate = BR_4800;
	config.parity   = PARITY_NO;
	config.dataBits = DBTS_8;
	config.stopBits = STOPBITS_1;	
	if (UartOpen(COM3) < 0) 
	{
		goto error;
	}
	UartSetup(COM3, &config);
#endif

#if  _ENB_COM4 > 0
	config.baudRate = BR_4800;  
	config.parity   = PARITY_NO;
	config.dataBits = DBTS_8;
	config.stopBits = STOPBITS_1;
	if (UartOpen(COM4) < 0) 
	{
	   goto error;
	}
	UartSetup(COM4, &config);	
#endif

#if  _ENB_COM5 > 0		
	config.baudRate = BR_4800;
	config.parity   = PARITY_NO;
	config.dataBits = DBTS_8;
	config.stopBits = STOPBITS_1;
	if (UartOpen(COM5) < 0) 
	{
	   goto error;
	}
	UartSetup(COM5, &config);	
#endif

#if  _ENB_COM6 > 0
	config.baudRate = BR_4800;
	config.parity   = PARITY_NO;
	config.dataBits = DBTS_8;
	config.stopBits = STOPBITS_1;
	if (UartOpen(COM6) < 0)
	{
	   goto error;
	}
	UartSetup(COM6, &config);   
#endif

#if  _ENB_COM7 > 0				
	config.baudRate = BR_4800;
	config.parity   = PARITY_NO;
	config.dataBits = DBTS_8;
	config.stopBits = STOPBITS_1;
	if (UartOpen(COM7) < 0)
	{
	   goto error;
	}
	UartSetup(COM7, &config);
#endif

#if  _ENB_COM8 > 0
	config.baudRate = BR_4800;
	config.parity   = PARITY_NO;
	config.dataBits = DBTS_8;
	config.stopBits = STOPBITS_1;
	if (UartOpen(COM8) < 0)
	{
	   goto error;
	}
	UartSetup(COM8, &config);
#endif

#if  _ENB_COM9 > 0
	config.baudRate = BR_4800;
	config.parity   = PARITY_NO;
	config.dataBits = DBTS_8;
	config.stopBits = STOPBITS_1;
	if (UartOpen(COM9) < 0)
	{
	   goto error;
	}
	UartSetup(COM9, &config);
#endif

	return TRUE;
error:
	return FALSE;
 
}


INT32 MapUartBPS(unsigned int combps)
{
   switch(combps)
   {
		case 1200:
			return BR_1200;

		case 2400:
			return BR_2400;

		case 4800:
			return BR_4800;

		case 9600:
			return BR_9600;

		case 19200:
			return BR_19200;

		case 38400:
			return BR_38400;

		case 57600:
			return BR_57600;

		case 115200:
			return BR_115200;

		default:
			break;
   }
   return 0;
}

