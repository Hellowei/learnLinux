/******************************************************************************
***********
版权所有:			和心重典
版本号:				1.0.0
生成日期:			2010.05.11
文件名:				
作者:				ZONDAN
功能说明:			应用层主文件
其它说明:			
所属文件关系:		本文件为工程规约代码文件

修改记录:
记录1:
修改者:
修改日期:
修改内容:
修改原因:
*******************************************************************************
**********/
#ifndef _RECORD_H
#define _RECORD_H


#ifdef  RECORD_GLOBALS
#define RECORD_EXTERN
#else
#define RECORD_EXTERN   extern
#endif

#define  RECPAPERWIDTH_150			144
#define  RECPAPERWIDTH_110			100
#define  RECPAPERWIDTH_112			104
#define  RECPAPERWIDTH_MAX			RECPAPERWIDTH_150 // 
#define  RECPAPERWIDTH_SCREEN		(SCREEN_HIGH >> 3)
#define  BORDER_START_SCREEN		0
#define  RECORD_WIDTH_SCREEN		(SCREEN_HIGH - 1)
#define  BORDER_START_150			68
#define  RECORD_WIDTH_150			1025
#define  BORDER_START_110			0
#define  RECORD_WIDTH_110			799
#define  BORDER_START_112			0
#define  RECORD_WIDTH_112			832
#define  RECORD_112_ENDLEN			80 //
#if _ENB_MYFB_RECORD_DEBUG_FUNC
#define  RECPAPERWIDTH				RECPAPERWIDTH_SCREEN
#else
#define  RECPAPERWIDTH				RECPAPERWIDTH_MAX // 使用最大页宽,保证足够的内存
#endif
#define  RECGRAPHMAXLEN				9000//(SCREEN_WIDTH * 10)
#if _ENB_MYFB_RECORD_DEBUG_FUNC
#define  BORDER_START_PAPER			BORDER_START_SCREEN
#define  RECORD_WIDTH_PAPER			RECORD_WIDTH_SCREEN
#else
#define  BORDER_START_PAPER			BORDER_START_112	// 起始打印方格到边界之间的点数
#define  RECORD_WIDTH_PAPER			RECORD_WIDTH_112	// 允许打印的最大宽度所占点数
#endif
#define  RECORD_DELAYTICKS			10				// 最大速度50mm/s,要求每秒画8*50=400,即2.5ms/line
#define  FOR_110MM_REC_SEND_ONE		1				  //采用原本24位图形式发送给打印机数据，其命令为
															 //1、设置行距 {0x1b, 0x33, 0x00}
															 //2、设置图形打印模式 {0x1b, 0x2A, 0x21}
															 //3、设置图形大小 lByte，hByte
															 //4、发送2400字节图形封装数据
#define  FOR_110MM_REC_SEND_TWO		0				  //采用美松科技提供的另一个数据发送包，过渡期
															 //1、命令设置 {0x1d, 0x76, 0x30, 0x00}
															 //2、图形打印宽度设置 XL XH YL YH
#define  FOR_110MM_REC_SEND_THREE	0				  //采用美松科技提供的第三种数据发送包，其为单条数据打印

#define  REC_CHAR_CONVERT_MEM		1				  //字符字摸提取时采用的获取内存方式
															 //1:采用静态内存形式 0:采用malloc进行动态分配
// 由于在输出字体的时候每输出一个字都需要多次申请和释放内存,代码效率过低,故改为局部变量.
#if REC_CHAR_CONVERT_MEM
#define  MAX_RECORD_CHAR_W			128
#define  MAX_RECORD_CHAR_H			128
#endif

#define  EXTERNAL_PRINTERS_THREADS	0				 // 是否由外部线程启动打印,0:采用独立线程

extern const  UINT8 Byte_mask_150[8];
extern const  UINT8 RecMask_150[8];
extern const  UINT8 RecMask_110[8];
//RECORD_EXTERN UINT8 RecImageBuff[RECGRAPHMAXLEN][RECPAPERWIDTH];
RECORD_EXTERN UINT8 RecTempCache[RECPAPERWIDTH * 24];


typedef enum _paper_type
{
	PAPER_TYPE_110MM,
	PAPER_TYPE_112MM,
	PAPER_TYPE_150MM,
	PAPER_TYPE_PT1561P,
	PAPER_TYPE_MAX
}PAPERTYPE;

typedef enum _line_thick
{
	THICK_DEF,
	THICK_ONE,
	THICK_TWO,
	THICK_THREE,
	THICK_FOUR,
	THICK_FIVE,
	THICK_SIX,
	THICK_SEVEN,
	THICK_EIGHT,
	THICK_NINE,
	THICK_TEN,

	THICK_MAX
}LINETHICK;

typedef enum _rec_icon_id
{
	REC_ICON_EVENTFLAG1,
	REC_ICON_EVENTFLAG2,
	REC_ICON_EVENTFLAG3,
	REC_ICON_EVENTFLAG4,
	REC_ICON_TOCOZERO,
	REC_ICON_DOWNARROW,
	REC_ICON_UPARROW,
	REC_ICON_MAX
}RECICONID;

typedef struct _rec_bitmap {
	INT16   width;			/* pixels of width		 */
	INT16   height;		   /* pixels of height		*/
	INT16   bytesWidth;	   /* bytes of width		  */
	VOID	*bits;			/* address of bitmap data  */
}RECBITMAP, *PRECBITMAP;

typedef struct _rec_drv_class
{
	struct 
	{
		INT8   paperType;
		INT32  startPos;
		INT32  maxHeight;
		INT32  printHeadWidth;
	}RecPaperInfo;

	struct
	{
		INT32 headIndex;
		INT32 tailIndex;
		INT32 readIndex;
		INT32 writeIndex;
		UINT8 **imgbuff;
	}RecGraphInfo;
	
	INT32  lineThick;
	INT32  imgLineLen;
	INT32  imgBufferLen;
	INT32  uartPort;
	INT32  font_normal;
	INT32  font_cutter;
	
	//打印机底层驱动封装函数
	BOOL   (*RecInit)(struct _rec_drv_class *this);
	VOID   (*RecSetImgBuffPtr8)(struct _rec_drv_class *this, UINT8 *buf, INT32 bufLen, INT32 lineLen);
	BOOL   (*RecPreSetPixel)(struct _rec_drv_class *this, INT32 x, INT32 y);
	BOOL   (*RecSetPixel)(struct _rec_drv_class *this, INT32 x, INT32 y);
	BOOL   (*RecPreLine)(struct _rec_drv_class *this, INT32 x0, INT32 y0, INT32 x1, INT32 y1, INT32 thick);
	BOOL   (*RecLine)(struct _rec_drv_class *this, INT32 x0, INT32 y0, INT32 x1, INT32 y1, INT32 thick);
	BOOL   (*RecPrevline)(struct _rec_drv_class *this, INT32 y0, INT32 y1, INT32 x, INT32 thick);
	BOOL   (*Recvline)(struct _rec_drv_class *this, INT32 y0, INT32 y1, INT32 x, INT32 thick);	
	BOOL   (*RecPrehline)(struct _rec_drv_class *this, INT32 x0, INT32 x1, INT32 y, INT32 thick);
	BOOL   (*Rechline)(struct _rec_drv_class *this, INT32 x0, INT32 x1, INT32 y, INT32 thick);
	VOID   (*RecPreLVline)(struct _rec_drv_class *this, INT32 x, INT32 y0, INT32 y1, INT32 thick, INT32 weak);
	BOOL   (*RecPreShowChar)(struct _rec_drv_class *this, INT32 x, INT32 y, INT32 w, INT32 h, UCHAR * imgP);
	BOOL   (*RecShowChar)(struct _rec_drv_class *this, INT32 x, INT32 y, INT32 w, INT32 h, UCHAR * imgP);
	INT32  (*RecPreShowCharacter)(struct _rec_drv_class *this, INT32 x, INT32 y, PLOGFONT logfont, UINT8 direct, UINT8 conver, UINT8 *buff);
	INT32  (*RecShowCharacter)(struct _rec_drv_class *this, INT32 x, INT32 y, PLOGFONT logfont, UINT8 direct, UINT8 conver, UINT8 *buff);
	UINT8* (*RecHConverToV)(struct _rec_drv_class *this, UINT32 bitW, UINT32 bitH, UINT8 heading, UINT8 *databuf);
	VOID   (*RecClrGraphBuff)(struct _rec_drv_class *this, INT32 index);
	BOOL   (*RecPrintSend) (struct _rec_drv_class *this); 

	VOID   (*RecSetReadIndex)(struct _rec_drv_class *this, INT32 index);
	VOID   (*RecSetWriteIndex)(struct _rec_drv_class *this, INT32 index);
	VOID   (*RecSetHeadIndex)(struct _rec_drv_class *this, INT32 index);
	VOID   (*RecSetTailIndex)(struct _rec_drv_class *this, INT32 index);
	VOID   (*ResetRecImgBuff)(struct _rec_drv_class *this);
	INT32  (*RecGetReadIndex)(struct _rec_drv_class *this);
	INT32  (*RecGetWriteIndex)(struct _rec_drv_class *this);
	INT32  (*RecGetHeadIndex)(struct _rec_drv_class *this);
	INT32  (*RecGetTailIndex)(struct _rec_drv_class *this);
	INT32  (*RecWriteIndexADD)(struct _rec_drv_class *this, INT32 add);
	INT32  (*RecPrintCR)(struct _rec_drv_class *this, INT32 width);

	//以下函数用于显存调试
	VOID   (*RecFBDebugSetPixel)(struct _rec_drv_class *this);
	VOID   (*RecFBDebugLine)(struct _rec_drv_class *this);

	//set recoder font
	VOID   (*RecSetNormalFont)(struct _rec_drv_class *this, INT32 pfont);
	VOID   (*RecSetCutterFont)(struct _rec_drv_class *this, INT32 pfont);

	//draw icon
	INT32  (*RecDrawBitmap)(struct _rec_drv_class *this, INT32 x, INT32 y, RECICONID icon_id);
	/* 一个打印机事件只能启用一个托管,如果托管已启用,直接返回 */
	/* 该对象内绝对不能有耗时过长的代码,控制在一个时间片以内 */
	VOID	(*RecTrusteeship)(struct _rec_drv_class *this, INT32 *AddData);
	UINT32 AddData;		   //附加数据1
	UINT32 AddData2;		  //附加数据2
	VOID   *Data;			 //扩充数据指针
}RECDRVCLASS, *PRECDRVCLASS;

typedef struct _record_chain
{
	BOOL   isValid;
	UINT32 curve_w;
	UINT32 curve_h;
	PRECDRVCLASS curvePtr;
	struct _record_chain *next;
}RECORDCHAIN;


RECORD_EXTERN RECDRVCLASS	RecCurveClass[PAPER_TYPE_MAX]; 
RECORD_EXTERN PRECDRVCLASS	RecCurveClassPtr[PAPER_TYPE_MAX];

/*
#define  RecClass_110		(RecCurveClassPtr[PAPER_TYPE_110MM])
#define  RecClass_112		(RecCurveClassPtr[PAPER_TYPE_112MM])
#define  RecClass_150		(RecCurveClassPtr[PAPER_TYPE_150MM])
#define  RecClass_1561		(RecCurveClassPtr[PAPER_TYPE_PT1561P])
*/

RECORD_EXTERN VOID  RecRegisterOps(PRECDRVCLASS pRecord, INT8 paperType);
#endif

