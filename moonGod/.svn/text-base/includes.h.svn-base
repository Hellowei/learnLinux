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

/*  A)首先是有全局影响的头文件 */
#include	"config.h"		   /* 应用程序环境的配置  */
#include	"version.h"		  /* 版本信息			*/
#include	"basetypes.h"		/* 基本类型定义		*/
#include	"externfile.h"	   /* 外部文件路径		*/
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
/* 通用模块 */
#include	"address.h"
#include	"msg.h"			   /* 消息功能					*/
#include	"chain.h"			 /* 双向链表功能				*/
#include	"uart.h"			  /* 串口功能					*/

/*  B)驱动层和各个通用功能模块的头文件 */

/* 文件部分  */
//#include	"fs.h"
/*  GUI部分的头文件  */
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
/*  SECTION -5-  用户应用程序的头文件							*/
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

