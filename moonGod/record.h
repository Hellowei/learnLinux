/******************************************************************************
***********
��Ȩ����:			�����ص�
�汾��:				1.0.0
��������:			2010.05.11
�ļ���:				
����:				ZONDAN
����˵��:			Ӧ�ò����ļ�
����˵��:			
�����ļ���ϵ:		���ļ�Ϊ���̹�Լ�����ļ�

�޸ļ�¼:
��¼1:
�޸���:
�޸�����:
�޸�����:
�޸�ԭ��:
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
#define  RECPAPERWIDTH				RECPAPERWIDTH_MAX // ʹ�����ҳ��,��֤�㹻���ڴ�
#endif
#define  RECGRAPHMAXLEN				9000//(SCREEN_WIDTH * 10)
#if _ENB_MYFB_RECORD_DEBUG_FUNC
#define  BORDER_START_PAPER			BORDER_START_SCREEN
#define  RECORD_WIDTH_PAPER			RECORD_WIDTH_SCREEN
#else
#define  BORDER_START_PAPER			BORDER_START_112	// ��ʼ��ӡ���񵽱߽�֮��ĵ���
#define  RECORD_WIDTH_PAPER			RECORD_WIDTH_112	// �����ӡ���������ռ����
#endif
#define  RECORD_DELAYTICKS			10				// ����ٶ�50mm/s,Ҫ��ÿ�뻭8*50=400,��2.5ms/line
#define  FOR_110MM_REC_SEND_ONE		1				  //����ԭ��24λͼ��ʽ���͸���ӡ�����ݣ�������Ϊ
															 //1�������о� {0x1b, 0x33, 0x00}
															 //2������ͼ�δ�ӡģʽ {0x1b, 0x2A, 0x21}
															 //3������ͼ�δ�С lByte��hByte
															 //4������2400�ֽ�ͼ�η�װ����
#define  FOR_110MM_REC_SEND_TWO		0				  //�������ɿƼ��ṩ����һ�����ݷ��Ͱ���������
															 //1���������� {0x1d, 0x76, 0x30, 0x00}
															 //2��ͼ�δ�ӡ������� XL XH YL YH
#define  FOR_110MM_REC_SEND_THREE	0				  //�������ɿƼ��ṩ�ĵ��������ݷ��Ͱ�����Ϊ�������ݴ�ӡ

#define  REC_CHAR_CONVERT_MEM		1				  //�ַ�������ȡʱ���õĻ�ȡ�ڴ淽ʽ
															 //1:���þ�̬�ڴ���ʽ 0:����malloc���ж�̬����
// ��������������ʱ��ÿ���һ���ֶ���Ҫ���������ͷ��ڴ�,����Ч�ʹ���,�ʸ�Ϊ�ֲ�����.
#if REC_CHAR_CONVERT_MEM
#define  MAX_RECORD_CHAR_W			128
#define  MAX_RECORD_CHAR_H			128
#endif

#define  EXTERNAL_PRINTERS_THREADS	0				 // �Ƿ����ⲿ�߳�������ӡ,0:���ö����߳�

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
	
	//��ӡ���ײ�������װ����
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

	//���º��������Դ����
	VOID   (*RecFBDebugSetPixel)(struct _rec_drv_class *this);
	VOID   (*RecFBDebugLine)(struct _rec_drv_class *this);

	//set recoder font
	VOID   (*RecSetNormalFont)(struct _rec_drv_class *this, INT32 pfont);
	VOID   (*RecSetCutterFont)(struct _rec_drv_class *this, INT32 pfont);

	//draw icon
	INT32  (*RecDrawBitmap)(struct _rec_drv_class *this, INT32 x, INT32 y, RECICONID icon_id);
	/* һ����ӡ���¼�ֻ������һ���й�,����й�������,ֱ�ӷ��� */
	/* �ö����ھ��Բ����к�ʱ�����Ĵ���,������һ��ʱ��Ƭ���� */
	VOID	(*RecTrusteeship)(struct _rec_drv_class *this, INT32 *AddData);
	UINT32 AddData;		   //��������1
	UINT32 AddData2;		  //��������2
	VOID   *Data;			 //��������ָ��
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

