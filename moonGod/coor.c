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

