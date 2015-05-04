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
#if !defined(_MSG_H)
#define	  _MSG_H

#include <semaphore.h>

// 定义消息结构
typedef struct tagMSG
{  
	/** the handle to the window which receives this message. */
	HANDLE		   handle;
	/** the message identifier. 消息值 */
	INT32			id;
	/** The first parameter of the message (32-bit integer). */
	WPARAM		   wParam;
	/** The second parameter of the message (32-bit integer). */
	LPARAM		   lParam;
} MSG;

typedef struct tagMSG *MSGP;
#define ResetMsg(p)  memset((void*)(p),0,sizeof(MSG))

/**
 **  消息队列数据结构.
**/
typedef struct _msgq_man {
	DWORD	dwState;	 /* 状态				  */
	MSGP	 msg;		 /* 消息的其实地址.	   */
	INT16	writepos;	/* 写入的位置. 数组下标. */
	INT16	readpos;	 /* 读出的位置. 数组下标. */
	INT16	total;	   /* 消息的总数.		   */
	INT16	usedNum;	 /* 已经写入的单元数量.   */
	pthread_mutex_t *mutex;   /* 信号量的句柄.保护读写 */
} MSGQ, *PMSGQ;

/* message manage; 消息管理信息结构 */
typedef struct _msg_man {
   MSGP	   start;   /* 消息结构数组的开始地址   */
   MSGP	   curr;	/* 当前已分配的单元地址	 */
   DWORD	  size;	/* 消息数组的大小, 单位:MSG */
   sem_t	 *sem;	 /* 保护临界段的存取操作	 */
} MSGMAN; 
typedef struct _msg_man *MSGMANP;

/* buffer manage; 缓冲区管理信息结构 */
typedef struct _buffer_man {
   VOID	  *start;   /* 缓冲区开始地址			*/
   VOID	  *curr;	/* 当前已分配的内存地址	  */
   DWORD	  size;	/* 数组单元的大小, 单位:byte */
   DWORD	  nr;	  /* 数组的大小,	 单位:	 */
   sem_t	 *sem;	 /* 保护临界段的存取操作	  */
} BUFFERMAN; 
typedef struct _buffer_man *BUFFERMANP;

// 任务消息队列结构 (Task Message Queue)
#define  TMQ		OS_EVENT

// 定义任务消息，TM为Task Message的缩写。 (在此添加用户任务消息)
#define  TM_KEY				5762
#define  TM_KEYDOWN			5763
#define  TM_KEYUP			5764

#define  TM_UART0RCV		8974

#define QS_NOTIFYMSG		0x10000000L
#define QS_DESKTIMER		0x20000000L
#define QS_POSTMSG		  0x40000000L
#define QS_QUIT			 0x80000000UL
#define QS_INPUT			0x01000000L
#define QS_PAINT			0x02000000L
#define QS_TIMER			0x0000FFFFL
#define QS_EMPTY			0x00000000L

/****************************************************************************
* 名称：TMQ_Create()
* 功能：建立任务消息队列。
*	  宏函数，函数原型为TMQ *TMQ_Create(void **buf, uint16 size)。
* 入口参数：buf		消息队列存储区首地址
*		  size		消息队列存储区大小
* 出口参数：若建立成功，返回消息队列的地址，否则返回0地址。
****************************************************************************/
#define  TMQ_Create(buf, size)		OSQCreate(buf, size)


/****************************************************************************
* 名称：SendMessage()
* 功能：发送一个消息，即消息发送管理器。
*	  根据实际情况，将消息分派到不同的任务消息队列中。
* 入口参数：msg		所要发送的消息(指针)
* 出口参数：操作成功返回TRUE，否则返回FALSE。
****************************************************************************/
extern  INT32 GUIAPI SendMessage2(MSG *msg);
INT32  SendMessage (HANDLE hdl, INT32 iMsg, WPARAM wParam, LPARAM lParam);
INT32  PostMessage (HANDLE hdl, INT32 iMsg, WPARAM wParam, LPARAM lParam);

/**
 * \fn int ThrowAwayMessages (HWND pMainWnd)
 * \brief Removes all messages in the message queue associated with a window or sys object. 
 *
 * This function removes all messages which are associated with 
 * the specified window or sys object \a handle.
 *
 * \param handle The handle to the window or object.
 * \return The number of thrown messages.
 *
 * \sa EmptyMessageQueue
 */
long  GUIAPI ThrowAwayMessages (HANDLE handle);

INT32  GUIAPI  ThrowAwayTaskMessages (HANDLE htsk);

/**
 * \fn int PostQuitMessage (HWND hWnd)
 * \brief Puts a MSG_QUIT message into the message queue of a main window.
 *
 * This function puts a MSG_QUIT message into the message queue of the
 * main window \a hWnd. The next call to \a GetMessage will return 0.
 *
 * \param hWnd The handle to the main window.
 * \return 0 if all OK, < 0 on error.
 *
 * \sa GetMessage
 */
INT32 GUIAPI PostQuitMessage (HWND hWnd);

/****************************************************************************
* 名称：GetMessage()
* 功能：等待一个消息。当接收到消息时才返回。
* 入口参数：tmq		等待的任务消息队列(指针)
* 出口参数：返回接收到的消息。
****************************************************************************/
extern  INT32  GUIAPI GetMessage(MSGP msg, HANDLE handle);

// extern  INT32 GUIAPI DispatchMessage (MSGP pMsg);
#define DispatchMessage(p)   SendMessage((p)->handle, (p)->id, (p)->wParam, (p)->lParam)

extern  INT32 GUIAPI PeekMessage(MSGP msg, HANDLE handle);

//#define  ResetMessage(msgP)	msgP->handle = 0
//MSGP  FindFreeMsg(MSGMANP manP);


#endif
