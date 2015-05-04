/*****************************************************************************************
版权所有:			和心重典
版本号:				1.0.0
生成日期:			2011.04.15
文件名:				
作者:				和心重典
功能说明:			
其它说明:			无
所属文件关系:		本文件为工程规约代码文件

修改记录:
记录1:
修改者:
修改日期:
修改内容:
修改原因:
*****************************************************************************************/
#ifndef _UART_H
#define _UART_H


/* 下面是一些编译开关 */
//#define  UART_EN_SEND_PROTECTED		1   /* 发送过程进行保护 */
//#define  UART_EN_RECEIVE_PROTECTED	 1   /* 接收过程进行保护 */

/* 串口modem线的状态 */
#define	UART_D_CTS		   0x0001	/*  值1 : 改变清除发送  */
#define	UART_D_DSR		   0x0002	/*  值1 : 改变数传机进入等待状态;  */
#define	UART_D_RI			0x0004	/*  值1 : 呼叫指示信号结束  */
#define	UART_D_DCD		   0x0008	/*  值1 : 载波信号检测出状态改变  */
#define	UART_CTS			 0x0010	/*  值1 : 清除发送  */
#define	UART_DSR			 0x0020	/*  值1 : 数传机进入等待状态  */
#define	UART_RI			  0x0040	/*  值1 : 检测到呼叫指示信号 */
#define	UART_DCD			 0x0080	/*  值1 : 检测到载波信号  */

/* 串口传送线的状态  */
#define UART_RCVED_D			0x0100	/*  值1 : 接收数据准备好了  */
#define UART_OVERFLOW		   0x0200	/*  值1 : 溢出错误  */
#define UART_PARITY_ERR		 0x0400	/*  值1 : 奇偶校验错  */
#define UART_FRAME_ERR		  0x0800	/*  值1 : 帧校验错  */
#define UART_BREAKDET		   0x1000	/*  值1 : 断开检出  */
#define UART_TX_BUF_EMPTY	   0x2000	/*  值1 : 发送用的保持移位寄存器是空的  */
#define	UART_TX_SHIFT_EMPTY  0x4000	/*  值1 : 发送用的移位寄存器是空的  */
#define	UART_TIMEOUT		 0x8000	/*  值1 : 超时  */

/* 下面是串口api的返回值定义 */
#define UART_OK				 0
#define UART_NO_OK			  -1
#define UART_ERR				-2
#define UART_NOAVAIL			-3
#define UART_ALLOC_MEM_FAIL	 -4

#define PWM_MAGIC			   0x91
#define PWM_IOC_SET_PARAMS	  _IO( PWM_MAGIC, 0x01 )
#define PWM_IOC_START		   _IO( PWM_MAGIC, 0x02 )
#define PWM_IOC_STOP			_IO( PWM_MAGIC, 0x03 )
#define INVALID_UART_DEV		-1


/** **************************************************************** **/

/* 对串口的操作 */
typedef	enum
{
  UART_OP_DISABLE,   /* 关闭 */
  UART_OP_ENABLE,	/* 打开 */
  UART_OP_PEEK,	  /* 没有延迟;无论是否完成操作,立即返回; */
  UART_OP_POLL,	  /* 查询方式; 一般要指定延迟的时间 */
}UART_OPERATION;


/* 端口号 */
typedef enum
{
	COM1,
	COM2,
	COM3,
	COM4,
	COM5,
	COM6,
	COM7,
	COM8,
	COM9,

	COMMAX
} UART_PORT;


/* 波特率 */
typedef enum
{
  BR_110,
  BR_150,
  BR_300,
  BR_600,
  BR_1200,
  BR_2400,   // 2400 BPS
  BR_4800,   // 4800 BPS
  BR_9600,   // 9600 BPS
  BR_19200,  // 19200 BPS  
  BR_38400,  // 38400 BPS
  BR_57600,  // 57600 BPS
  BR_76800,  // 76800 BPS
  BR_115200, // 115200 BPS
  BR_MAX
}UART_BAUDRATE;


/* 数据位 */
typedef enum
{
  DBTS_5,
  DBTS_6,
  DBTS_7,
  DBTS_8,
  DBTS_MAX
}UART_DATABITS;


/* 停止位 */
typedef enum
{
  STOPBITS_1,
  STOPBITS_1_5,
  STOPBITS_2,
  STOPBITS_MAX
}UART_STOPBITS;


/* 校验位 */
typedef enum
{
  PARITY_ODD,
  PARITY_EVEN,
  PARITY_NO,
  PARITY_MULTIDROP,
  PARITY_MAX
}UART_PARITY;


/*  串口驱动的信息 */
typedef struct
{
   UINT32   status;		  /*  串口线的当前状态						*/
   UINT32   receivedBytes;   /*  已经接收的数据长度					  */
   BOOL	 txBufRemained;   /*  发送缓冲区还剩多少数据				  */
}UART_INFO;


/* 串口的设置 */
typedef struct _uart_config
{
   UART_BAUDRATE	baudRate;
   UART_PARITY	  parity;
   UART_DATABITS	dataBits;
   UART_STOPBITS	stopBits;
}UART_CONFIG;


/* 串口驱动的接口 */
typedef struct _uart_drv
{
   STATUS  (*Init)(VOID);  /* 初始化；需要指定接收和发送缓冲区的大小；   */  
   VOID	(*Reset)(VOID);								   /* Reset									  */
   INT32   (*WriteString)(UINT8* dataP, INT32 toSend);	   /* 发送一组字节的数据						 */
   STATUS  (*WriteByte)(UINT8 data);						 /* 发送一个字节的数据						 */
   INT32   (*ReadString)(UINT8* bufP, INT32 toRead);		 /* 读取指定长度的数据；返回实际读取的数据长度 */
   STATUS  (*ReadByte)(UINT8* bufP);						 /* 读取一个字节数据						   */
   UINT32  (*GetStatus)(VOID);							   /* 读取串口线的状态						   */
   VOID	(*GetInfo)(UART_INFO *infoP);					 /* 读取串口接收、发送的信息				   */
   VOID	(*ReceiveControl)(UART_OPERATION operation);	  /* 接收器的控制							   */
   VOID	(*TransmitControl)(UART_OPERATION operation);	 /* 发送线的控制							   */
   VOID	(*Setup	  )(const UART_CONFIG* config );	   /* 设置串口								   */
   VOID	(*ISR)(VOID);									 /* 串口的中断处理函数						 */
   VOID	(*Term)(VOID);
}UART_DRV;

/* 
******************************************************************************** 
*										VARIABLES 
******************************************************************************** 
*/
#ifdef UART_GLOBALS
#define UART_EXT 
#else 
#define UART_EXT extern 
#endif

EXTERN  UART_DRV   Uart0_Driver;
EXTERN  UART_DRV   Uart1_Driver;
EXTERN  UART_DRV   Uart2_Driver;
EXTERN  UART_DRV   Uart3_Driver;
EXTERN  UART_DRV   Uart4_Driver;


/* 串口用户层的API */

/*
*********************************************************************************************************
* Function   :  打开串口					  
*
* Description:  对串口驱动和缓冲控制，作一些初始化工作；
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
STATUS   UartOpen  ( UART_PORT port );


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
* Calls	  :
*
* Called by  : 
*
* Returns	: 
*
* Note	   : 如果要使用串口；应该首先setup串口,以后再调用open；
*********************************************************************************************************
*/
VOID  UartSetup ( UART_PORT port, const UART_CONFIG* configP );

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

VOID   UartPurge ( UART_PORT port );

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
STATUS   UartRead ( UART_PORT port, UINT8 *bufP, INT32 toRead, INT32 *ReadP, OPTION opt );


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
STATUS   UartWrite ( UART_PORT port, UINT8 *bufP, INT32 toSend, INT32 *sendP, OPTION opt );

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
UINT32   UartStatus( UART_PORT port );

BOOL  InitUart(VOID);
VOID  TermUart(VOID);

VOID  UartRxTaskProc(VOID);
VOID  UartTxTaskProc(VOID);
INT32 MapUartBPS(unsigned int combps);

#endif
