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
#ifndef   _DEVFONT_H
#define   _DEVFONT_H

CHARSETOPS* GetCharsetOps (const char* charset_name);
#define  BYTE_NUM_ONETIME_READ   61440   // 60K=60X1024,һ�ο��Զ�����������


DEVFONT * GetMatchedSBDevFont (LOGFONT* log_font);
DEVFONT * GetMatchedMBDevFont (LOGFONT* log_font);

BOOL  InitDeviceFonts(VOID);
VOID  TermDeviceFonts(VOID);

#endif

