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

#define   ATTR_GLOBALS 

#include "config.h"
#include "basetypes.h"
#include "mycommon.h"
#include "gal.h"
#include "gdi.h"
#include "dc.h"


/******************* General drawing attributes *******************************/
GAL_PIXEL GUIAPI GetBkColor (HDC hdc)
{
	PDC pdc;

	pdc = dc_HDC2PDC (hdc);
	return pdc->bkcolor;
}

GAL_PIXEL GUIAPI GetTextColor(HDC hdc)
{
	PDC pdc;

	pdc = dc_HDC2PDC(hdc);

	return pdc->textcolor;
}

GAL_PIXEL GUIAPI SetBkColor (HDC hdc, GAL_PIXEL color)
{
	GAL_PIXEL oldcolor;
	PDC	   pdc;

	pdc = dc_HDC2PDC (hdc);

	oldcolor = pdc->bkcolor;

	pdc->bkcolor = color;

	return oldcolor;
} 

#if  0
GAL_PIXEL GUIAPI GetTextBkColor(HDC hdc)
{
	PDC pdc;

	pdc = dc_HDC2PDC(hdc);

	return pdc->textbkcolor;
}
GAL_PIXEL GUIAPI SetTextBkColor (HDC hdc, GAL_PIXEL color)
{
	GAL_PIXEL oldcolor;
	PDC	   pdc;

	pdc = dc_HDC2PDC (hdc);

	oldcolor = pdc->textbkcolor;

	pdc->textbkcolor = color;

	return oldcolor;
}
#endif

GAL_PIXEL GUIAPI SetTextColor (HDC hdc, GAL_PIXEL color)
{
	GAL_PIXEL oldcolor;
	PDC	   pdc;

	pdc = dc_HDC2PDC (hdc);

	oldcolor = pdc->textcolor;

	pdc->textcolor = color;

	return oldcolor;
}



/************************** Pen and brush support ****************************/
GAL_PIXEL GUIAPI GetPenColor (HDC hdc)
{
	PDC pdc;

	pdc = dc_HDC2PDC (hdc);

	return pdc->pencolor;
}

GAL_PIXEL GUIAPI GetBrushColor (HDC hdc)
{
	PDC pdc;

	pdc = dc_HDC2PDC (hdc);

	return pdc->brushcolor;
}

GAL_PIXEL GUIAPI SetPenColor (HDC hdc, GAL_PIXEL color)
{
	GAL_PIXEL oldvalue;
	PDC	   pdc;

	pdc = dc_HDC2PDC (hdc);

	oldvalue = pdc->pencolor;
	pdc->pencolor = color;

	return oldvalue;
}

GAL_PIXEL GUIAPI SetBrushColor (HDC hdc, GAL_PIXEL color)
{
	GAL_PIXEL oldvalue;
	PDC	   pdc;

	pdc = dc_HDC2PDC (hdc);

	oldvalue = pdc->brushcolor;
	pdc->brushcolor = color;

	return oldvalue;
}

INT32 GUIAPI SetBrushType (HDC hdc, INT32 brushtype)
{
	INT32 oldvalue;
	PDC   pdc;

	pdc = dc_HDC2PDC (hdc);

	oldvalue = pdc->brushtype;
	pdc->brushtype = brushtype;

	return oldvalue;
}




