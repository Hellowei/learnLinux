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

/*  A)��������ȫ��Ӱ���ͷ�ļ� */
#include	"config.h"		   /* Ӧ�ó��򻷾�������  */
#include	"version.h"		  /* �汾��Ϣ			*/
#include	"basetypes.h"		/* �������Ͷ���		*/
#include	"externfile.h"	   /* �ⲿ�ļ�·��		*/
#include	"mycommon.h"

#include <stdio.h> 
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <sched.h>
#include <unistd.h>
#include <string.h>
#include <sys/time.h> 
#include <time.h>
#include <sys/stat.h>
#include <sys/types.h> 
#include <netinet/in.h> 
#include <sys/socket.h> 
#include <sys/wait.h> 
/* ͨ��ģ�� */
#include	"address.h"
#include	"msg.h"			   /* ��Ϣ����					*/
#include	"chain.h"			 /* ˫��������				*/
#include	"uart.h"			  /* ���ڹ���					*/

/*  B)������͸���ͨ�ù���ģ���ͷ�ļ� */

/* �ļ�����  */
//#include	"fs.h"
/*  GUI���ֵ�ͷ�ļ�  */
#include	"winstr.h"
#include	"text.h"
#include	"gdi.h"
#include	"ChoiceFont.h"	   //add by empty 2011/06/27
#include	"gui.h"
#include	"color.h"
#include	"control.h"
#include	"ctrlbas.h"
#include	"window.h"

#include	"fnmacro.h"
#include	"internal.h"
#include	"gal.h"
#include	"dc.h"
#include	"ctrlbas.h"
#include	"fontname.h"
#include	"icon.h"
#include	"resource.h"
#include	"fbmem.h"

#include	"static.h"
#include	"button.h"
#include	"listbox.h"
#include	"spinbox.h"
#include	"checkbox.h"
#include	"edit.h"
#include	"groupbox.h"
#include	"scroll.h"
#include	"keyboardDlg.h"
/*  SECTION -5-  �û�Ӧ�ó����ͷ�ļ�							*/
#include	"system.h"		   

#include	"object.h"
#include	"tasks.h"
#include	"systype.h"

#include	"protocol.h"
#include	"pm.h"

#include	"kb.h"

#include	"params.h"

#include	"filemanager.h"

#include	"almlist.h"
#include	"freeze.h"

#include	"alarm.h"
#include	"monitor.h"
#include	"scrman.h"
#include	"fhr.h"
#include	"timer.h"
#include	"appmain.h"
#include	"sysmenu.h"

#include	"record.h"
#include	"recmain.h"

#if _ENB_TOUCH
#include	"touch.h"
#endif

#if QVFB_DEBUG
#include	"qvfb.h"
#endif
#include	"myfb.h"

#include	"cmsplustype.h"
#include	"cmsprocess.h"
#include	"cmsprotocol.h"
#include	"cmsnnettask.h"
#include	"cmsplus_ver1.h"
#include	"modules.h"
#include	"netcenter.h"

#include	"pinyin.h"

#include	"kbcomm.h"
#include	"fhrcomm.h"
#include	"sound.h"
#include	"power_gpio.h"
#include	"analysis.h"
#include	"misc.h"
#include	"netsrv.h"

