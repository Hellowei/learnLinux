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
#define   LIMITS_GLOBALS 
#include  "includes.h"


PARAM_LIMITS  ParamLimits[PARAM_LMTS_MAX] = {
/*   high,low,ripple,hasRangeExceedAlarm*/
	{ 240, 30,	0 , FALSE },	 //PARAM_LMTS_FHR
	{ 100,  0,	0 , FALSE },	 //PARAM_LMTS_TOCO
	{  40,  0,	0 , FALSE },	 //PARAM_LMTS_AFM
	{  99,  0,	0 , FALSE },	 //PARAM_LMTS_FM
};

BOOL CheckRangeExceed( PARAM_LMTS_ID param_index, INT16 *param_value )
{
	INT16*		  paramInt;
	PARAM_LIMITS*   param_limits;
	BOOL			exceed_range;
	UINT8		   tmp;
	if ((PARAM_LMTS_MIN  > param_index) || (PARAM_LMTS_MAX <= param_index))
		return FALSE;
	
	paramInt = param_value;

	param_limits = &ParamLimits[param_index];

	exceed_range = FALSE;

	if (param_limits->high >= *paramInt && param_limits->low <= *paramInt)
		return exceed_range;
	// Don't check range exceed if parameter has an invalid value
	if (param_limits->hasRangeExceedAlarm)
	{
		if (*paramInt < (param_limits->low - param_limits->ripple)) 
		{
		   *paramInt = INVALID_PARAM_INT;
		   exceed_range = TRUE;
		   return exceed_range;
		}
		else 
		{
		   *paramInt = param_limits->low;
		   return exceed_range;
		}
		if (*paramInt > (param_limits->high + param_limits->ripple)) 
		{
			*paramInt = param_limits->high;
			exceed_range = TRUE;
			return exceed_range;
		} 
		else
		{
			*paramInt = param_limits->high;
			return exceed_range;
		}
	}
	else
	{
		*paramInt = INVALID_PARAM_INT;
		return exceed_range;
	}
}


