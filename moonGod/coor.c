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

#define   COOR_GLOBALS 

#include "config.h"
#include "basetypes.h"
#include "mycommon.h"
#include "gal.h"
#include "gdi.h"
#include "dc.h"

/************************ Coordinate system transfer *************************/
VOID GUIAPI SPtoLP(HDC hdc, POINT* pPt)
{
	if (hdc == HDC_SCREEN) return;

	coor_SP2LP ((PDC)hdc, &pPt->x, &pPt->y);
}

VOID GUIAPI LPtoSP(HDC hdc, POINT* pPt)
{
	if (hdc == HDC_SCREEN) return;

	coor_LP2SP ((PDC)hdc, &pPt->x, &pPt->y);
}

VOID GUIAPI LPtoDP(HDC hdc, POINT* pPt)
{
	hdc = hdc;
	pPt = pPt;
}

VOID GUIAPI DPtoLP (HDC hdc, POINT* pPt)
{
	hdc = hdc;
	pPt = pPt;
}

