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

#ifndef __MY_SYSTEM_h
#define __MY_SYSTEM_h


/* 开头字母为小写的数据类型; 不建议在系统中使用了.主要是为了某些外部组件的代码兼容 */
typedef unsigned long	   unsigned32;
typedef unsigned int		unsigned16;
typedef unsigned char	   unsigned8;
typedef unsigned long	   boolean;

typedef unsigned char	   uint8;				   /* 无符号8位整型变量						*/
typedef signed   char	   int8;					/* 有符号8位整型变量						*/
typedef unsigned short	  uint16;				  /* 无符号16位整型变量					   */
typedef signed   short	  int16;				   /* 有符号16位整型变量					   */
typedef unsigned int		uint32;				  /* 无符号32位整型变量					   */
typedef signed   int		int32;				   /* 有符号32位整型变量					   */
typedef float			   fp32;					/* 单精度浮点数（32位长度）				 */
typedef double			  fp64;					/* 双精度浮点数（64位长度）				 */


/* 定义不同模块使用的串口端口号													*/
#if 0
#define	  UART_PORT_KB			 (Get_KeyBoard_com())	/* 按键板连接的端口						*/
#define	  UART_PORT_PM			 (Get_paramer_com())	 /* 多参数板连接的端口					  */
#define	  UART_PORT_REC			(Get_printer_com()) 
#define	  UART_PORT_FHR			(Get_Fetus_com())	 /* fetal模块								 */
//	#else
#define	  UART_PORT_KB		COM1	/* 按键板连接的端口						*/
#define	  UART_PORT_FETAL	COM3	/* 胎监板连接的端口						*/
#define	  UART_PORT_PRINTER	COM2	/* 打印机连接的端口						*/
#define	  UART_PORT_ANALY	COM4	/* 评分板连接的端口						*/
#else
#define	  UART_PORT_KB		MonitorInfo.deviceInfo[DEV_KB].port
#define	  UART_PORT_FETAL	MonitorInfo.deviceInfo[DEV_PM].port
#define	  UART_PORT_PRINTER	MonitorInfo.deviceInfo[DEV_REC].port
#define   UART_PORT_TOUCH	MonitorInfo.deviceInfo[DEV_TOUCH].port
#define   UART_PORT_ANALY   COM6
#endif

/* 设备的id */
typedef enum _device_id {
  DEV_PM,		/* 参数模块	*/
  DEV_KB,		/* 按键模块	*/
  DEV_REC,		/* 记录仪	*/
  DEV_NET,		/* 网络		*/
  DEV_TOUCH,	/* 触控		*/
  
  DEV_MAX
} DEVICEID;

//监护仪使用的设备类型
typedef  enum  _dev_type {
	DEVTYPE_UART,  //串口
	DEVTYPE_LPT,   //并口
	DEVTYPE_NET,   //网络
	DEVTYPE_E2PROM,//E2PROM
	DEVTYPE_I2C,   //
	DEVTYPE_CAN,
	DEVTYPE_USB,
	DEVTYPE_CF,
	
	DEVTYPE_MAX
} DEVTYPE;

// 设备初始化成功以后, online置为TRUE;
typedef struct  _device_info {
   INT8   id;
   INT8   online;  // Is this module in monitoring
   INT16  devType; // 设备类型;
   INT16  port;	// 设备端口;
   UINT8  version;
   UINT16 postResult;
   UINT16 state;
   UINT32 addData; // 附加数据.
   CHAR   name[10];// 模块的名称,id,或版本信息.
} DEVICEINFO;

/*  System Task info	   */
#if defined(X86) || defined(LANNRY)
/* To allow the task to use the Borland floating-point 
*  emulation , must allocate added memory space;
*  but, in P1861, it's not need.
*  16 Unit is for Alignment;(32 byte);
*  reference func: OSTaskStkInit_FPE_x86;
*/
#define  BC_FLOATEMU_STKSIZE	 192 + 16  /* Unit: OS_STK */
#else
#define  BC_FLOATEMU_STKSIZE	 0  /* Unit: OS_STK */

#endif

#define OS_TICKS_PER_SEC		200   /* Set the number of ticks in one second						*/

/**   堆栈的大小   **/
#define  TSK_SYSTIMER_STKSIZE		   1024*1	+ BC_FLOATEMU_STKSIZE
#define  TSK_SYSSERVER_STKSIZE		  1024*2	+ BC_FLOATEMU_STKSIZE
#define  TSK_WATCHDOG_STKSIZE		   1024*1	+ BC_FLOATEMU_STKSIZE
#define  TSK_MONITOR_STKSIZE			128	 + BC_FLOATEMU_STKSIZE 
#define  TSK_GUI_STKSIZE				1024*5 + BC_FLOATEMU_STKSIZE			  
#define  TSK_APP_STKSIZE				1024*2 + BC_FLOATEMU_STKSIZE
#define  TSK_DATAPROC_STKSIZE		   1024*10 + BC_FLOATEMU_STKSIZE
#define  TSK_IOSERVER_STKSIZE		   1024*10 + BC_FLOATEMU_STKSIZE
#define  TSK_COM1_STKSIZE			   512	 + BC_FLOATEMU_STKSIZE		 /* use for keyboard			 */
#define  TSK_COM2_STKSIZE			   512	 + BC_FLOATEMU_STKSIZE		 /* use for phisycal para module */
#define  TSK_COM3_STKSIZE			   512	 + BC_FLOATEMU_STKSIZE		 /* use for keyboard			 */
#define  TSK_COM4_STKSIZE			   512	 + BC_FLOATEMU_STKSIZE		 /* use for phisycal para module */
#define  TSK_REC_STKSIZE				1024*5 + BC_FLOATEMU_STKSIZE
#define  TSK_NET_STKSIZE				1024*5 + BC_FLOATEMU_STKSIZE
#if _ENB_TOUCH
#define  TSK_TCH_STKSIZE				256 + BC_FLOATEMU_STKSIZE
#endif
#define  TSK_REC_SENDDATA			   1024*5  + BC_FLOATEMU_STKSIZE
#if _ENB_AUTOUSB
#define	 TSK_AUSB_STKSIZE				512	+ BC_FLOATEMU_STKSIZE
#endif
/**   消息队列长度   **/
/**
   消息队列等于说明,任务不使用消息队列传递数据和同步.
   串口任务一般都会等待操作结束,所以队列长度较小;
   IO操作请求一般都会等待操作结束,所以队列长度较小;
   GUI,APP,DATAPROC任务处理频繁,所有设计的队列长度较大

**/
#define  TSK_SYSTIMER_MSGSIZE		   0
#define  TSK_SYSSERVER_MSGSIZE		  16
#define  TSK_WATCHDOG_MSGSIZE		   0
#define  TSK_MONITOR_MSGSIZE			0   
#define  TSK_GUI_MSGSIZE				128 // 32	TEST
#define  TSK_APP_MSGSIZE				64  // 16	TEST
#define  TSK_DATAPROC_MSGSIZE		   64
#define  TSK_IOSERVER_MSGSIZE		   32
#define  TSK_COM1_MSGSIZE			   10		 /* use for keyboard				*/
#define  TSK_COM2_MSGSIZE			   10		 /* use for phisycal para module	*/
#define  TSK_COM3_MSGSIZE			   10		 /* use for debug & download update */
#define  TSK_COM4_MSGSIZE			   10		 /* reserved						*/
#define  TSK_REC_MSGSIZE				16
#define  TSK_NET_MSGSIZE				10

/* 系统中总的消息数量; 可以估算. 如果系统中增加了消息队列的长度;注意更新它. */
#define  SYS_TSK_MSG_SUM   (300)


/* 系统热键的总数 */
#define  SYS_HOTKEY_NR	  (20)


/* 系统定义的用户消息ID */
typedef enum  _msg_userdef {

	MSG_USER_FIRST = MSG_USER+10,
	MSG_COMM_ERR,
	MSG_CMD_NOACK,						/* 命令没有应答	 */
	MSG_CMD_ACK,						  /* 命令应答了	   */
	MSG_PM_RESET,						 /* 生理参数模块复位 */
	
	MSG_SYS_FIRST  = MSG_USER + 0x20,
	MSG_SYS_UNPACK = MSG_SYS_FIRST,	   /* parse data packet		 */
	MSG_SYS_TIMERCHECK,				   /* timer check			   */
	MSG_SYS_DATA_CORRECTION,			  /* data correction		   */
	MSG_SYS_DATA_PROC,					/* data process			  */
	MSG_SYS_SET_PARAMS_STATUS,
	MSG_SYS_SET_SENSOR_STATUS,
	MSG_SYS_INIT_MDL_INFO,
   
	MSG_USER_IO_FIRSET = MSG_USER+0x30,			/* IO操作有关的消息 */
	MSG_IO_TX_REQ	  = MSG_USER_IO_FIRSET,
	MSG_IO_CMD_ACK,
	MSG_IO_CMD_NOACK,

	MSG_USER_SYS_FIRSET = MSG_USER+0x60,		   /* 系统管理的消息 */
	MSG_USER_SYS_TIMER  = MSG_USER_SYS_FIRSET,	 /* 用户定义的时钟 */
	MSG_USER_SYS_KEYMSG,						   /* 按键消息	   */
#if _ENB_TOUCH
	MSG_USER_SYS_TOUCHMSG,
#endif

	MSG_USER_ALM_FIRST   = MSG_USER+0x90,		  /* 报警管理消息 */
	MSG_USER_ALM_TRIGGER = MSG_USER_ALM_FIRST,	 /* 触发报警	 */
	MSG_USER_ALM_ONPAUSE,						  /* alarm  pause */
	MSG_USER_ALM_ONSILENCE,						/* alarm  silence */
	MSG_USER_ALM_CLRMDLALM,						/* clear alarm of module */
	MSG_USER_ALM_CHANGE_MDLALM,					/* change alarm info of module */
	
	MSG_USER_MMAN_FIRST  = MSG_USER+0xA0,		  /* 模块操作管理消息 */
 
	MSG_TOPBAR_FIRST  = MSG_USER+0xB0,
	MSG_TOPBAR_PHYALM = MSG_TOPBAR_FIRST,
	MSG_TOPBAR_TECHALM,
	MSG_TOPBAR_ALMICON,
	MSG_TOPBAR_DEMO,

	MSG_BOTBAR_FIRST	= MSG_USER+0xC0,
	MSG_BOTBAR_INFOITEM = MSG_BOTBAR_FIRST,
	MSG_BOTBAR_ICON,

	MSG_APP_FIRST = MSG_USER + 0xD0,
	MSG_APP_PM_CMD = MSG_APP_FIRST,				 /* send command packet to PM */
	MSG_APP_KB_CMD,								 /* send command packet to KB */
	MSG_APP_SOUND_CMD,

#if 1//_ENB_FHR_FUNC
	MSG_APP_FHR_CMD,
#endif

	MSG_APP_PM_SETUP,							   /* config func block of Param Module */
	MSG_APP_SAVE_CONFIG,							/* write config to E2PROM */
	MSG_APP_POWERON,
	
	MSG_GUI_FIRST = MSG_USER + 0xE0,
	MSG_GUI_PAINT_ECGGAIN = MSG_GUI_FIRST,
	MSG_GUI_LOAD_MODULE,
	MSG_GUI_DRAW_WAVE,
	MSG_GUI_NIBPSETUP,
	MSG_GUI_BLINK,
	MSG_GUI_PM_ACK,
	MSG_GUI_PM_NOACK,
	MSG_GUI_KB_ACK,
	MSG_GUI_KB_NOACK,
	MSG_GUI_LANG_CHANGE,

	MSG_USER_MAX
	
} MSGUSERDEF;

#if 0
typedef enum __tag_tcp_status
{
	/*侦听来自远方的TCP端口的连接请求*/
	NET_TCP_LISTEN,
	/*再发送连接请求后等待匹配的连接请求*/
	NET_TCP_SYN_SENT,
	/*再收到和发送一个连接请求后等待对方对连接请求的确认*/
	NET_TCP_SYN_RECEIVED,
	/*代表一个打开的连接*/
	NET_TCP_ESTABLISHED,
	/*等待远程TCP连接中断请求，或先前的连接中断请求的确认*/
	NET_TCP_FIN_WAIT_1,
	/*从远程TCP等待连接中断请求*/
	NET_TCP_FIN_WAIT_2,
	/*等待从本地用户发来的连接中断请求*/
	NET_TCP_CLOSE_WAIT,
	/*等待远程TCP对连接中断的确认*/
	NET_TCP_CLOSING,
	/*等待原来的发向远程TCP的连接中断请求的确认*/
	NET_TCP_LAST_ACK,
	/*等待足够的时间以确保远程TCP接收到连接中断请求的确认*/
	NET_TCP_TIME_WAIT,
	/*没有任何连接状态*/
	NET_TCP_CLOSED,
};
#endif

typedef enum __tag_message_net_trend
{
	MSG_NET_TCP_FIRST = 0,
	MSG_NET_TCP_SETUP,
	MSG_NET_TCP_CONNECT,
	MSG_NET_TCP_SEND,
	MSG_NET_TCP_LISTEN,
	MSG_NET_TCP_CLOSE,
	/**
		----------------------
		undefine other message
		----------------------
	**/
	MSG_NET_TCP_MAX,
	
	MSG_NET_UDP_FIRST = 0x80,
	MSG_NET_UDP_SETUP = MSG_NET_UDP_FIRST,/* initializate socket */
	MSG_NET_UDP_RESET,/* reset udp socket and bind */
	MSG_NET_UDP_QUERY,/* send register and sniff packet */
	MSG_NET_UDP_CONNECT,
	MSG_NET_UDP_SEND,
	MSG_NET_UDP_DISCONNECT,
	MSG_NET_UDP_COMMAND,/* for receive command */
	MSG_NET_UDP_MAX
}MSGNETDEF;

#define TICKS_OF_SECOND 1000
						

#ifndef  EXIT_PROC
#define  EXIT_PROC(func)				  0
#endif
#define  my_malloc(size_t)				malloc(size_t)
#define  my_free(p)					   free(p)
#define  my_calloc(nitem, size)		   calloc(nitem, size)

#define  ENTER_FILE_OP()		 pthread_mutex_lock(&FileAccessSem)
#define  EXIT_FILE_OP()		  pthread_mutex_unlock(&FileAccessSem)

#endif
