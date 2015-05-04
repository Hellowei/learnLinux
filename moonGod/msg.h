/*****************************************************************************************
��Ȩ����:			�����ص�
�汾��:				1.0.0
��������:			2011.04.15
�ļ���:				
����:				�����ص�
����˵��:			
����˵��:			��
�����ļ���ϵ:		���ļ�Ϊ���̹�Լ�����ļ�

�޸ļ�¼:
��¼1:
�޸���:
�޸�����:
�޸�����:
�޸�ԭ��:
*****************************************************************************************/
#if !defined(_MSG_H)
#define	  _MSG_H

#include <semaphore.h>

// ������Ϣ�ṹ
typedef struct tagMSG
{  
	/** the handle to the window which receives this message. */
	HANDLE		   handle;
	/** the message identifier. ��Ϣֵ */
	INT32			id;
	/** The first parameter of the message (32-bit integer). */
	WPARAM		   wParam;
	/** The second parameter of the message (32-bit integer). */
	LPARAM		   lParam;
} MSG;

typedef struct tagMSG *MSGP;
#define ResetMsg(p)  memset((void*)(p),0,sizeof(MSG))

/**
 **  ��Ϣ�������ݽṹ.
**/
typedef struct _msgq_man {
	DWORD	dwState;	 /* ״̬				  */
	MSGP	 msg;		 /* ��Ϣ����ʵ��ַ.	   */
	INT16	writepos;	/* д���λ��. �����±�. */
	INT16	readpos;	 /* ������λ��. �����±�. */
	INT16	total;	   /* ��Ϣ������.		   */
	INT16	usedNum;	 /* �Ѿ�д��ĵ�Ԫ����.   */
	pthread_mutex_t *mutex;   /* �ź����ľ��.������д */
} MSGQ, *PMSGQ;

/* message manage; ��Ϣ������Ϣ�ṹ */
typedef struct _msg_man {
   MSGP	   start;   /* ��Ϣ�ṹ����Ŀ�ʼ��ַ   */
   MSGP	   curr;	/* ��ǰ�ѷ���ĵ�Ԫ��ַ	 */
   DWORD	  size;	/* ��Ϣ����Ĵ�С, ��λ:MSG */
   sem_t	 *sem;	 /* �����ٽ�εĴ�ȡ����	 */
} MSGMAN; 
typedef struct _msg_man *MSGMANP;

/* buffer manage; ������������Ϣ�ṹ */
typedef struct _buffer_man {
   VOID	  *start;   /* ��������ʼ��ַ			*/
   VOID	  *curr;	/* ��ǰ�ѷ�����ڴ��ַ	  */
   DWORD	  size;	/* ���鵥Ԫ�Ĵ�С, ��λ:byte */
   DWORD	  nr;	  /* ����Ĵ�С,	 ��λ:	 */
   sem_t	 *sem;	 /* �����ٽ�εĴ�ȡ����	  */
} BUFFERMAN; 
typedef struct _buffer_man *BUFFERMANP;

// ������Ϣ���нṹ (Task Message Queue)
#define  TMQ		OS_EVENT

// ����������Ϣ��TMΪTask Message����д�� (�ڴ�����û�������Ϣ)
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
* ���ƣ�TMQ_Create()
* ���ܣ�����������Ϣ���С�
*	  �꺯��������ԭ��ΪTMQ *TMQ_Create(void **buf, uint16 size)��
* ��ڲ�����buf		��Ϣ���д洢���׵�ַ
*		  size		��Ϣ���д洢����С
* ���ڲ������������ɹ���������Ϣ���еĵ�ַ�����򷵻�0��ַ��
****************************************************************************/
#define  TMQ_Create(buf, size)		OSQCreate(buf, size)


/****************************************************************************
* ���ƣ�SendMessage()
* ���ܣ�����һ����Ϣ������Ϣ���͹�������
*	  ����ʵ�����������Ϣ���ɵ���ͬ��������Ϣ�����С�
* ��ڲ�����msg		��Ҫ���͵���Ϣ(ָ��)
* ���ڲ����������ɹ�����TRUE�����򷵻�FALSE��
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
* ���ƣ�GetMessage()
* ���ܣ��ȴ�һ����Ϣ�������յ���Ϣʱ�ŷ��ء�
* ��ڲ�����tmq		�ȴ���������Ϣ����(ָ��)
* ���ڲ��������ؽ��յ�����Ϣ��
****************************************************************************/
extern  INT32  GUIAPI GetMessage(MSGP msg, HANDLE handle);

// extern  INT32 GUIAPI DispatchMessage (MSGP pMsg);
#define DispatchMessage(p)   SendMessage((p)->handle, (p)->id, (p)->wParam, (p)->lParam)

extern  INT32 GUIAPI PeekMessage(MSGP msg, HANDLE handle);

//#define  ResetMessage(msgP)	msgP->handle = 0
//MSGP  FindFreeMsg(MSGMANP manP);


#endif
