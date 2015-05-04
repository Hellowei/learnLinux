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
#if !defined(_SPINBOX_H)
#define	  _SPINBOX_H


typedef  enum _spinbox_txt_mode {
   SBTXT_BLANK,   // 空白
   SBTXT_NUM,	 // 显示数字
   SBTXT_INT,	 // 显示整数
   SBTXT_FLOAT,   // 显示浮点书
   SBTXT_COLOR,   // 显示颜色画面.
} SBT_MODE;


/* 对spinbox进行操作时,指定的类型码. */
typedef enum  _spinbox_code {
	SBC_FMAX,
	SBC_FMIN,
	SBC_FCUR,
	SBC_IMAX,
	SBC_IMIN,
	SBC_ICUR,
	SBC_RATE,
	SBC_MODE,
	SBC_FORM
	
} SBCODE;


/* spinbox处理的核心数据. */
typedef struct _spinbox_coredata {
	struct  {
		FLOAT	 fMin, fMax, fCur;	 // 浮点型数值的下限、上限和当前值
		FLOAT	 fDef;				 // 浮点型数值的缺省值
		FLOAT	 fStep;				// 浮点型变化步长
	} fBlock;
	struct  {
		INT16	 iMin, iMax, iCur;	 // 整型数值的下限、上限和当前值
		INT16	 iStep;				 // 整型变化步长
	} iBlock;
} SB_COREDATA;

/**
 **  SPINBOX控件显示浮点数的说明:
 **  下面是关键的数据结构.
 **  rate放大了10倍,可以表示一位的小数; fStep都放大了100倍;可以最小表示2位的小数步长.
 **  iCur, iMax, iMin表示原始数据.不放大.
 **  fMin, fMax, fCur都放大100倍,这样控件最多可以显示2位的小数.
 **  例如, rate = 75(相当于7.5),  fStep = 75(相当于0.75); iCur = 120 mmHg;
 **  当要显示浮点时, fCur = ( iCur*1000 + fStep*10 ) / rate; 被除数放大了1000倍, 除数
 **  放大了10倍;这样, 结果值fCur就放大了100倍;在显示时,最多就可以显示2位小数.
 **  120mmHg, 转成KPA; 步长0.1kpa; (120x1000+750)/75 = 1610;
 **  fCur = 1610, 显示FORM_41F时, 可以得到16.1.
 **
 **  rate不等于0,表示要从iCur转成fCur,其格式只能是FORM_41F,加减的还是iCur值;
 **  如果控件是纯粹的浮点表示, 一般是52F格式,加减的就只是fCur值了.
 **  见 CalcNextSpinboxValue, CalcPreviousSpinboxValue.
 **/
typedef struct _tag_spinboxdata {
	INT16		format;			   // 旋转编辑框中数值的类型
	INT16		mode;				 // 模式
	/*
	FLOAT		fMin, fMax, fCur;	 // 浮点型数值的下限、上限和当前值
	FLOAT		fDef;				 // 浮点型数值的缺省值
	FLOAT		fStep;				// 浮点型变化步长
	*/
	INT32		fMin, fMax, fCur;	 // 浮点型数值的下限、上限和当前值
	//INT32		fDef;				 // 浮点型数值的缺省值
	INT16		fStep;				// 浮点型变化步长;为了可以用整数处理;放大了100倍;
	
	INT16		iMin, iMax, iCur;	 // 整型数值的下限、上限和当前值
	INT16		iStep;				// 整型变化步长
	
	INT16		rate;				 // 整型和浮点型相互转化的数率;和fStep放大100倍;
	DWORD		status;
	
	INT16   help_ctrl_id;
	INT16   help_str_id;	
} SPINBOXDATA, *SPINBOXDATAP;


#define SPINBOX_STATUS(pCtrl)   (((SPINBOXDATAP)(pCtrl->dwAddData2))->status)

#define SPINBOX_FMAX(pctrl)	 (((SPINBOXDATAP)(pctrl->dwAddData2))->fMax)
#define SPINBOX_FMIN(pctrl)	 (((SPINBOXDATAP)(pctrl->dwAddData2))->fMin)
#define SPINBOX_FCUR(pctrl)	 (((SPINBOXDATAP)(pctrl->dwAddData2))->fCur)
#define SPINBOX_FDEF(pctrl)	 (((SPINBOXDATAP)(pctrl->dwAddData2))->fDef)
#define SPINBOX_FSTEP(pctrl)	(((SPINBOXDATAP)(pctrl->dwAddData2))->fStep)

#define SPINBOX_IMAX(pctrl)	 (((SPINBOXDATAP)(pctrl->dwAddData2))->iMax)
#define SPINBOX_IMIN(pctrl)	 (((SPINBOXDATAP)(pctrl->dwAddData2))->iMin)
#define SPINBOX_ICUR(pctrl)	 (((SPINBOXDATAP)(pctrl->dwAddData2))->iCur)
#define SPINBOX_ISTEP(pctrl)	(((SPINBOXDATAP)(pctrl->dwAddData2))->iStep)

#define SPINBOX_MODE(pctrl)	 (((SPINBOXDATAP)(pctrl->dwAddData2))->mode)
#define SPINBOX_FORM(pctrl)	 (((SPINBOXDATAP)(pctrl->dwAddData2))->format)
#define SPINBOX_RATE(pctrl)	 (((SPINBOXDATAP)(pctrl->dwAddData2))->rate)
#define SPINBOX_HELPID(pctrl)   (((SPINBOXDATAP)(pctrl->dwAddData2))->help_ctrl_id)
#define SPINBOX_HELPSTR(pctrl)  (((SPINBOXDATAP)(pctrl->dwAddData2))->help_str_id)


BOOL  RegisterSpinboxControl (VOID);

/**
 **  由于要避免浮点运算,所以float的函数传入的是整数;
 **  为了无法避免的情况下,使用浮点数;所以引入了Ex后缀的函数;
 **  如果传入的是整数,那么都是放大了100倍的;
 **  如果传入的是浮点数,那么都是原始的真实的值;
 **/
INT16  SetSpinBoxType(UINT16 parent_id, UINT16 ctrl_id, FORMAT_TYPE type);
INT16  SetSpinBoxTextMode(UINT16 parent_id, UINT16 ctrl_id, SBT_MODE mode);
INT16  SetSpinBoxFloatValue(UINT16 parent_id, UINT16 ctrl_id, INT32 cur_val, INT32 max_val, INT32 min_val);
INT16  SetSpinBoxFloatValueEx(UINT16 parent_id, UINT16 ctrl_id, FLOAT cur_val, FLOAT max_val, FLOAT min_val);
INT16  SetSpinBoxFloatCurValue(UINT16 parent_id, UINT16 ctrl_id, INT32 cur_val);
INT16  SetSpinBoxFloatCurValueEx(UINT16 parent_id, UINT16 ctrl_id, FLOAT cur_val);
INT16  SetSpinBoxFloatMaxValue(UINT16 parent_id, UINT16 ctrl_id, INT32 max_val);
INT16  SetSpinBoxFloatMaxValueEx(UINT16 parent_id, UINT16 ctrl_id, FLOAT max_val);
INT16  SetSpinBoxFloatMinValue(UINT16 parent_id, UINT16 ctrl_id, INT32 min_val);
INT16  SetSpinBoxFloatMinValueEx(UINT16 parent_id, UINT16 ctrl_id, FLOAT min_val);
INT16  SetSpinBoxIntValue(UINT16 parent_id, UINT16 ctrl_id, INT16 cur_val, INT16 max_val, INT16 min_val);
INT16  SetSpinBoxIntCurValue(UINT16 parent_id, UINT16 ctrl_id, INT16 cur_val);
INT16  GetSpinBoxIntCurValue(UINT16 parent_id, UINT16 ctrl_id);
INT16  SetSpinBoxIntMaxValue(UINT16 parent_id, UINT16 ctrl_id, INT16 max_val);
INT16  SetSpinBoxIntMinValue(UINT16 parent_id, UINT16 ctrl_id, INT16 min_val);
INT16  SetSpinBoxRate(UINT16 parent_id, UINT16 ctrl_id, INT16 rate);
INT16  GetSpinBoxRate(UINT16 parent_id, UINT16 ctrl_id);

INT16  GetSpinBoxFloatCurValue(UINT16 parent_id, UINT16 ctrl_id, INT32 *value);
INT16  GetSpinBoxFloatCurValueEx(UINT16 parent_id, UINT16 ctrl_id, FLOAT *value);

INT16  SetSpinBoxDrugStatus(UINT16 parent_id, UINT16 ctrl_id, INT16 status);
INT16  SetSpinBoxDrugStatusEx(PCONTROL pCtrl, INT16 status);

#endif
