/*******************************************************************************
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
*******************************************************************************/
#if !defined(_CONFIG_H)
#define	  _CONFIG_H


#define _ENB_CO2				   0  // remove CO2 lookingout
#define _RM_PVC					0  // remove PVCr
#define _RM_T2D					0  // remove t2, td
#define _RM_IBP					1  // remove ibp
#define _ENB_FHR				   1
#if _ENB_FHR
#define _ENB_FHR_FUNC			  1  // add fhr
#define _ENB_FHR_STR			   1  // add fhr string
#define _ENB_FHR_STR_A			 1  // FHR phsAlm
#define _ENB_FHR_FUNC_PARAM		1  // add fhr param
#define _ENB_FHR_FUNC_FACE		 0  // add fhr face
#define _ENB_FHR_FUNC_ALARM		1  // add fhr alarm system
#define _ENB_FHR_FUNC_SAVE		 1  // 
#define _ENB_FHR_FUNC_RECORD	   1  // add fhr record
#define _ENB_FHR_RECPAPER		  0  // if use Special printing paper
#endif
#define _ENB_WAVE_DRIVE			0

#define _ENB_OTHER_RECORD		  0  // to remove other record type


#define MYFB_RECORD_DEBUG		  0

/* Define if support GB2312 charset */
#define _GB_SUPPORT				1

/* Define if support Russian charset*/
#define  _RUS_SUPPORT			  1  //Change by Latrom_06-21-2011

/* enable RUS8x12 font*/
#define  _ENB_RUS8X12_FONT		 1  //Change by Latrom_06-21-2011

/* enable RUS8x16 font */
#define  _ENB_RUS8X16_FONT		 1  //Change by Latrom_06-21-2011

/* enable printer 16X18 font*/
#define  _ENB_PRT16X18_FONT		1  //16x18��ӡר������

/* enable 80X120 big font */
#define  _ENB_80X120_FONT		  1

/* enable 56X84 big font */
#define  _ENB_56X84_FONT		   0

/* enable 48X72 big font */
#define  _ENB_48X72_FONT		   0

#define  _ENB_GB12X12_FONT		 1

/* enable GB16x16 font   */
#define  _ENB_GB16X16_FONT		 1

/* enable "΢���ź�" 17pt font */
#define  _ENB_YAHEI17_FONT		 1

/* Define if include STATIC control */
#define _CTRL_STATIC			   1

/* Define if include BUTTON control */
#define _CTRL_BUTTON			   1

/* Define if include EDIT control */
#define _CTRL_EDIT				 1

/* Define if include SPINBOX control */
#define _CTRL_SPINBOX			  1

/* Define if include LISTBOX control */
#define _CTRL_LISTBOX			  1

/* Define if include CHECKBOX control */
#define _CTRL_CHECKBOX			 1

/* Define if include HOTKEY control */
#define _CTRL_HOTKEY			   0 //ȡ��ʹ��HOTKEY,������ͬһʹ��GROUPBOX,

/* Define if include GROUPBOX control */
#define _CTRL_GROUPBOX			 1 //���������пؼ�(��STATIC��)������GROUPBOX�д���

#define _CTRL_SCROLLBAR			1

#ifdef  _CTRL_GROUPBOX
#define _ENB_3D_FRAME			  1
#endif

#define _ENB_PASSWORD_DIALOG	   1

/* Define if include EEPROM function control */
#define _ENB_NV_MEM_FUNC		   1

#define _ENB_MONITOREVENT_FUNC	 1

/* ϵͳ��������� */
#define  NUMBER_OF_LANGUAGE		2  /* ϵͳ�����ʾ�ʹ�ӡ֧�ֵ��������� */

/* ����ͬʱ�򿪵��ļ���Ŀ */
#ifndef MAX_OPEN_FILES
#define MAX_OPEN_FILES			 5		  
#endif


#define  Debug_PORT_KB			 1  /* ���������ӵĶ˿�		 */
#define  Debug_PORT_REC			2

#define  Debug_PORT_TOUCH		  3
#define  Debug_PORT_CONFIG		 4
#define  Debug_PORT_FHR			5


extern  char DebugSupportDevice;

#define TEST_UART				  0
#define _ENB_COM_TEST			  0
#define PIXEL_BIT_8				0
#define PIXEL_BIT_16			   1
#define PIXEL_BIT_24			   0
#define KERNEL_10MS				0

#define	_ENB_NET_THREAD		   1
	#if	_ENB_NET_THREAD
		#define _ENB_NET_SEND_ALARM_INFO	1//�޸�����һ��Ҫ������վЭ���Ӧ����
	#endif

// how long one time Tick is ?  unit: ms
#define  MSECOND_OF_TICK		   (1000/OS_TICKS_PER_SEC)

#define  _ENB_COM1				 1
#define  _ENB_COM2				 1
#define  _ENB_COM3				 1
#define  _ENB_COM4				 1
#define  _ENB_COM5				 1
#define  _ENB_COM6				 1
#define  _ENB_COM7				 1
#define  _ENB_COM8				 1
#define  _ENB_COM9				 1

#define  _ENB_REC_FUNC				1
#define  _ENB_WATCHDOG				1  /* ����ʽ�ķ����汾�У�����򿪿��Ź� */
#define  _ENB_TOUCH					1

#define  _ENB_FILE_SYSTEM			1

#define  _ENB_SYS_KEYBOARD_FUNC		1
#define  _ENB_SYS_KEYBOARD_DEBUG	(!_ENB_WATCHDOG)//1

/**
���Թ��ܵĿ���;
	��Ŀ��ΪP1861,��������ʱӦ�����ε�tcc,tasm,tlink�ĵ�����Ϣ;����exe�ļ��Ĵ�С;
���Ǵ�ʱ,��Ȼ�п�������Ҫ���Ե�;����Ŀ��ؾ�����������;��;
   ��Ŀ����X86, DOSƽ̨ʱ.������borland������������ʶ��ĺ꿪��NDEBUG,�Լ�_DEBUG
(microsoftʹ�õ�).���������ṩ�ĵ����ֶ��㹻��.����,ϵͳ�ڲ������ṩ���Կ���;
   �������ģ��ĵ��Դ�������ڸ���Դ�ļ���ʹ�ö���.
**/
#define  _ENB_GB_READ_FILE		0
#define  IOKB					 0  //����IO��UART��ѡ�� lookingout 0 -> 1

#define STANDBY				   1  // Add for Turkish StandBy, Change by Latrom_11-11-2011

#define DebugInfo (printf("%s:in function'%s',line:%d\r\n",\
					__FILE__, __FUNCTION__, __LINE__),printf)
#define _ENB_UART_FOR_2416_DEBUG  1
#define QVFB_DEBUG				0

#define _ENB_MYFB_RECORD_DEBUG_FUNC 0

#define _ENB_TELNET_DEBUG		0 // ����ʽ�ķ����汾�У���ر�������Խӿ�
#define _ENB_USB_UPDATE		  	1 // USB�������װ�,��U���з���ָ������ѹ�����ļ���������
#define _ENB_AUTOUSB			1
#define _ENB_VIRTUAL_FB			0 // Enable virtual frambuffer,for rotate fb
//#define	_ENB_LCSYS				1
#endif

