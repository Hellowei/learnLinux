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
#define  RECORD_GLOBALS
#include "includes.h"

#if _ENB_REC_FUNC

const UINT8 RecMask_150[8]   = {0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x80};
const UINT8 Byte_mask_150[8] = {0x80, 0x40, 0x20, 0x10, 0x08, 0x04, 0x02, 0x01};

extern UINT8  Batt_2LevIcon[];
RECDRVCLASS   RecCurveClass[PAPER_TYPE_MAX];

static  UINT8 NM_SIGN[] =
#if 0
{
	________,________,________,________,
	_X______,________,________,______X_,
	_XX_____,________,________,_____XX_,
	_XXX____,________,________,____XXX_,
	_XXXX___,________,________,___XXXX_,
	_XXXXX__,________,________,__XXXXX_,
	_XXXXXX_,________,________,_XXXXXX_,
	_XXXXXXX,________,________,XXXXXXX_,
	_XXXXXXX,X_______,_______X,XXXXXXX_,
	_XXXXXXX,XX______,______XX,XXXXXXX_,
	_XXXXXXX,XXX_____,_____XXX,XXXXXXX_,
	_XXXXXXX,XXXX____,____XXXX,XXXXXXX_,
	_XXXXXXX,XXXXX___,___XXXXX,XXXXXXX_,
	_XXXXXXX,XXXXXX__,__XXXXXX,XXXXXXX_,
	_XXXXXXX,XXXXXXX_,_XXXXXXX,XXXXXXX_,
	_XXXXXXX,XXXXXXXX,XXXXXXXX,XXXXXXX_,
	_XXXXXXX,XXXXXXXX,XXXXXXXX,XXXXXXX_,
	_XXXXXXX,XXXXXXX_,_XXXXXXX,XXXXXXX_,
	_XXXXXXX,XXXXXX__,__XXXXXX,XXXXXXX_,
	_XXXXXXX,XXXXX___,___XXXXX,XXXXXXX_,
	_XXXXXXX,XXXX____,____XXXX,XXXXXXX_,
	_XXXXXXX,XXX_____,_____XXX,XXXXXXX_,
	_XXXXXXX,XX______,______XX,XXXXXXX_,
	_XXXXXXX,X_______,_______X,XXXXXXX_,
	_XXXXXXX,________,________,XXXXXXX_,
	_XXXXXX_,________,________,_XXXXXX_,
	_XXXXX__,________,________,__XXXXX_,
	_XXXX___,________,________,___XXXX_,
	_XXX____,________,________,____XXX_,
	_XX_____,________,________,_____XX_,
	_X______,________,________,______X_,
	________,________,________,________,
};
#else
{
	________,________,________,________,
	________,________,________,________,
	________,________,________,________,
	________,________,________,________,
	________,______XX,XX______,________,
	________,_____XXX,XXX_____,________,
	________,_____XX_,_XX_____,________,
	________,____XX__,__XX____,________,
	________,____XX__,__XX____,________,
	____XX__,___XX___,___XX___,__XX____,
	____XX__,___XX___,___XX___,__XX____,
	_____XX_,___XX___,___XX___,_XX_____,
	______XX,___XX___,___XX___,XX______,
	_______X,X__XX___,___XX__X,X_______,
	________,XX_XX___,___XX_XX,________,
	_XXXXXXX,XXXXX___,___XXXXX,XXXXXXX_,
	_XXXXXXX,XXXXX___,___XXXXX,XXXXXXX_,
	________,XX_XX___,___XX_XX,________,
	_______X,X__XX___,___XX__X,X_______,
	______XX,___XX___,___XX___,XX______,
	____XXX_,___XX___,___XX___,_XXX____,
	____XX__,___XX___,___XX___,__XX____,
	________,___XX___,___XX___,________,
	________,____XX__,__XX____,________,
	________,____XX__,__XX____,________,
	________,_____XX_,_XX_____,________,
	________,_____XXX,XXX_____,________,
	________,______XX,XX______,________,
	________,________,________,________,
	________,________,________,________,
	________,________,________,________,
	________,________,________,________,
};
#endif

static  UINT8 UP_ARROW[] =
{
	________,________,________,________,
	________,_______X,X_______,________,
	________,______XX,XX______,________,
	________,_____XXX,XXX_____,________,
	________,____XXXX,XXXX____,________,
	________,___XXXXX,XXXXX___,________,
	________,__XXXXXX,XXXXXX__,________,
	________,_XXXXXXX,XXXXXXX_,________,
	________,XXXXXXXX,XXXXXXXX,________,
	_______X,XXXXXXXX,XXXXXXXX,X_______,
	______XX,XXXXXXXX,XXXXXXXX,XX______,
	_____XXX,XXXXXXXX,XXXXXXXX,XXX_____,
	____XXXX,XXXXXXXX,XXXXXXXX,XXXX____,
	___XXXXX,XXXXXXXX,XXXXXXXX,XXXXX___,
	__XXXXXX,XXXXXXXX,XXXXXXXX,XXXXXX__,
	_XXXXXXX,XXXXXXXX,XXXXXXXX,XXXXXXX_,
	________,__XXXXXX,XXXXXX__,________,
	________,__XXXXXX,XXXXXX__,________,
	________,__XXXXXX,XXXXXX__,________,
	________,__XXXXXX,XXXXXX__,________,
	________,__XXXXXX,XXXXXX__,________,
	________,__XXXXXX,XXXXXX__,________,
	________,__XXXXXX,XXXXXX__,________,
	________,__XXXXXX,XXXXXX__,________,
	________,__XXXXXX,XXXXXX__,________,
	________,__XXXXXX,XXXXXX__,________,
	________,__XXXXXX,XXXXXX__,________,
	________,__XXXXXX,XXXXXX__,________,
	________,__XXXXXX,XXXXXX__,________,
	________,__XXXXXX,XXXXXX__,________,
	________,__XXXXXX,XXXXXX__,________,
	________,________,________,________,
};

static RECBITMAP sRecIcon[REC_ICON_MAX] = 
{
	/*width*/ /*height*/ /*bytesWidth*/ /*bits*/
	{0},//	REC_ICON_EVENTFLAG1,
	{0},//	REC_ICON_EVENTFLAG2,
	{0},//	REC_ICON_EVENTFLAG3,
	{0},//	REC_ICON_EVENTFLAG4,
	{32, 32,  1,  (VOID*)NM_SIGN},//	REC_ICON_TOCOZERO,
	{0},//	REC_ICON_DOWNARROW,
	{32, 32,  1,  (VOID*)UP_ARROW}//	REC_ICON_UPARROW,
};

static VOID gen_ResetRecImgBuff(PRECDRVCLASS this)
{
	memset (this->RecGraphInfo.imgbuff[0], 0, this->imgBufferLen);
	this->RecSetReadIndex (this, 0);
	this->RecSetWriteIndex(this, 0);
}

/*****************************************************************************************
��������:	VOID gen_RecSetImgBuffPtr8(PRECDRVCLASS this, UINT8 *buf, INT32 bufLen, INT32 lineLen)
�汾��:		1.0.0
��������:	2011.11.07
����:		zondan
����˵��:	���ñ����ʹ�ӡ����ͼ�ι��컺��������Ϣ
�������:	
�������:	
����˵��:	
*****************************************************************************************/
static VOID gen_RecSetImgBuffPtr8(PRECDRVCLASS this, UINT8 *buf, INT32 bufLen, INT32 lineLen)
{
	INT32  len;
	INT32  i;
	
	this->imgLineLen   = lineLen;
	this->imgBufferLen = bufLen;
	len  = bufLen / lineLen;

	if (len > 0)
	{
		this->RecGraphInfo.imgbuff = (UINT8 **)malloc(sizeof(UINT8 *) * len);
	}
	else
	{
		printf ("gen_RecSetImgBuffPtr8 Error !\r\n");
		return ;
	}
	if (NULL == buf)
	{
		buf = (UINT8 *)malloc(sizeof(UINT8) * bufLen);
	}
	if (NULL == this->RecGraphInfo.imgbuff || NULL == buf)
	{
		perror("gen_RecSetImgBuffPtr8 Error!");
		return;
	}
	memset(buf, 0, (sizeof(UINT8) * bufLen));
	for (i = 0; i < len; i++)
	{
		this->RecGraphInfo.imgbuff[i] = buf + i * lineLen;
	}
	this->RecSetHeadIndex (this, 0);
	this->RecSetTailIndex (this, len - 1);
	this->ResetRecImgBuff(this);
}

static BOOL gen_InitPt1561p(PRECDRVCLASS this)
{
	this->RecPaperInfo.paperType		= PAPER_TYPE_PT1561P;
	this->RecPaperInfo.startPos			= 1;
	this->RecPaperInfo.maxHeight		= 1152;
	this->RecPaperInfo.printHeadWidth	= 8;

	this->uartPort	= UART_PORT_PRINTER;
	this->lineThick	= THICK_DEF;
	this->RecSetImgBuffPtr8(this, NULL, RECGRAPHMAXLEN * RECPAPERWIDTH_150,	RECPAPERWIDTH_150);
	this->Data = RecTempCache;
	PrinterInitFunc(this);
}

static BOOL gen_PreSetPixel_Pt1561p(PRECDRVCLASS this, INT32 x, INT32 y)
{
	INT32  quotient;
	INT32  remainder;
	UINT8  bits = 8;
	INT32  i;

	if (y >= this->imgLineLen * bits)
	{
		y = this->imgLineLen * bits - 1;
	}
	else if (y < 0)
	{
		y = 0;
	}
	if (x < 0)
	{
		x = 0;
	}	
	else if (x >= 0)
	{
		if (x + this->RecGraphInfo.writeIndex > this->RecGraphInfo.tailIndex)
		{
			x += this->RecGraphInfo.writeIndex + this->RecGraphInfo.headIndex
				- this->RecGraphInfo.tailIndex - 1;
		}
		else
		{
			x += this->RecGraphInfo.writeIndex;
		}
	}
	quotient  = (y / bits) % this->imgLineLen;
	remainder = y % bits;
#if _ENB_MYFB_RECORD_DEBUG_FUNC
	this->RecGraphInfo.imgbuff[x][quotient] |= Byte_mask_150[remainder];
#else
	this->RecGraphInfo.imgbuff[x][this->imgLineLen - 1 - quotient] |=
	RecMask_150[remainder];	
#endif

	return	TRUE;
}

static BOOL gen_RecPrintSend_Pt1561p(PRECDRVCLASS this)
{
#if _ENB_MYFB_RECORD_DEBUG_FUNC
	this->RecFBDebugLine(this);
#else
	BOOL  ret = TRUE;
	INT32 toSend;
	INT32 Send = 0;
	INT32 i = this->RecGraphInfo.readIndex;
	UCHAR *pImage = this->RecGraphInfo.imgbuff[i];
	union{
		struct{
		char gs;
		char v;
		char zero;
		char p;
		unsigned short width;
		unsigned short height;
		char image[RECPAPERWIDTH];
		}buff_struct;
		char buffer[8 + RECPAPERWIDTH];
	}buff;
	buff.buff_struct.gs		= ASCII_GS;
	buff.buff_struct.v		= 'v';
	buff.buff_struct.zero	= '0';
	buff.buff_struct.p		= 0;
	buff.buff_struct.width	= LOWORD(this->imgLineLen);
	buff.buff_struct.height	= 1;
	memcpy(buff.buff_struct.image, pImage, this->imgLineLen);
	toSend = 8 + this->imgLineLen;
	//MdlUartTran(this->uartPort, &buff, toSend, &Send);
	Pt1561SendPacket(&buff, toSend);
	//if (toSend > Send)
	//{
	//	printf("Send data to recorder error, toSend:%d, Send:%d\n", toSend, Send);
	//	ret = FALSE;
	//}
	//toSend = this->imgLineLen;
	//Pt1561SendPacket(pImage, toSend);
	//MdlUartTran(this->uartPort, pImage, toSend, &Send);
	//if (toSend > Send)
	//{
	//	printf("Send data to recorder error, toSend:%d, Send:%d\n", toSend, Send);
	//	ret = FALSE;
	//}
	//char page = 0x0A;
	//Pt1561SendPacket(&page, 1);
	//char movepaper[3] = { 0x1B, 0x4A, 0x01 };
	//Pt1561SendPacket(movepaper, sizeof(movepaper));
#endif
	this->RecClrGraphBuff(this, this->RecGraphInfo.readIndex);
	return ret;
}

/*****************************************************************************************
��������:	BOOL gen_Init_150(PRECDRVCLASS this)
�汾��:		1.0.0
��������:	2011.11.07
����:		zondan
����˵��:	��ʼ����ӡ���������Ϣ�����ú���治��Ҫ�仯
�������:	
�������:	
����˵��:	ע��:��ͬ���͵Ĵ�ӡ�������޸Ĵ˺���������ֻ���150mm��ӡ������ʽ
*****************************************************************************************/
static BOOL gen_Init_150(PRECDRVCLASS this)
{
	INT16  len; 
	INT16  i;
	
	this->RecPaperInfo.paperType	  = PAPER_TYPE_150MM;
	this->RecPaperInfo.startPos	   = BORDER_START_PAPER;
	this->RecPaperInfo.maxHeight	  = RECORD_WIDTH_PAPER;
	this->RecPaperInfo.printHeadWidth = 8;

	this->uartPort					= UART_PORT_PRINTER;
	this->lineThick				   = THICK_DEF;
	this->RecSetImgBuffPtr8(this, NULL, RECGRAPHMAXLEN * RECPAPERWIDTH_150,	RECPAPERWIDTH_150);
	this->Data = RecTempCache;
}


/*****************************************************************************************
��������:	BOOL gen_Init_110(PRECDRVCLASS this)
�汾��:		1.0.0
��������:	2011.11.07
����:		zondan
����˵��:	��ʼ����ӡ���������Ϣ�����ú���治��Ҫ�仯
�������:	
�������:	
����˵��:	ע��:��ͬ���͵Ĵ�ӡ�������޸Ĵ˺���������ֻ���110mm��ӡ������ʽ
*****************************************************************************************/
static BOOL gen_Init_110(PRECDRVCLASS this)
{
	INT16  len; 
	INT16  i;
	
	this->RecPaperInfo.paperType	  = PAPER_TYPE_110MM;
	this->RecPaperInfo.startPos	   = BORDER_START_PAPER;
	this->RecPaperInfo.maxHeight	  = RECORD_WIDTH_PAPER;
	this->RecPaperInfo.printHeadWidth = 8;

	this->uartPort					= UART_PORT_PRINTER;
	this->lineThick				   = THICK_DEF;
	this->RecSetImgBuffPtr8(this, NULL, RECGRAPHMAXLEN * RECPAPERWIDTH_110, RECPAPERWIDTH_110);
	this->Data = RecTempCache;
	//InitPrinter_110 ();  //����Э��Դ�ӡ�����б�Ҫ�ĳ�ʼ��
}


/*****************************************************************************************
��������:	BOOL gen_Init_112(PRECDRVCLASS this)
�汾��:		1.0.0
��������:	2011.11.07
����:		zondan
����˵��:	��ʼ����ӡ���������Ϣ�����ú���治��Ҫ�仯
�������:	
�������:	
����˵��:	ע��:��ͬ���͵Ĵ�ӡ�������޸Ĵ˺���������ֻ���110mm��ӡ������ʽ
*****************************************************************************************/
static BOOL gen_Init_112(PRECDRVCLASS this)
{
	INT16  len; 
	INT16  i;
	
	this->RecPaperInfo.paperType	  = PAPER_TYPE_112MM;
	this->RecPaperInfo.startPos	   = BORDER_START_PAPER;
	this->RecPaperInfo.maxHeight	  = RECORD_WIDTH_PAPER;
	this->RecPaperInfo.printHeadWidth = 8;

	this->uartPort					= UART_PORT_PRINTER;
	this->lineThick				   = THICK_DEF;
	this->RecSetImgBuffPtr8(this, NULL, RECGRAPHMAXLEN * RECPAPERWIDTH_112,	RECPAPERWIDTH_112);
	this->Data = RecTempCache;
	PrinterInitFunc(this);
	PrinterSetChroma(this);
}


/*****************************************************************************************
��������:	BOOL gen_PreSetPixel_150 (INT32 x, INT32 y)
�汾��:		1.0.0
��������:	2011.11.07
����:		zondan
����˵��:	�ڴ�ӡ�����й�����ӡ��
�������:	
�������:	
����˵��:	�����������ظ����á�
			ע��:��ͬ���͵Ĵ�ӡ�������޸Ĵ˺���������ֻ���150mm��ӡ������ʽ
*****************************************************************************************/
static BOOL gen_PreSetPixel_150(PRECDRVCLASS this, INT32 x, INT32 y)
{
	INT32  quotient;
	INT32  remainder;
	UINT8  bits = 8;
	INT32  i;

	if (y >= this->imgLineLen * bits)
	{
		y = this->imgLineLen * bits - 1;
	}
	else if (y < 0)
	{
		y = 0;
	}
	if (x < 0)
	{
		x = 0;
	}	
	else if (x >= 0)
	{
		if (x + this->RecGraphInfo.writeIndex > this->RecGraphInfo.tailIndex)
		{
			x = x + this->RecGraphInfo.writeIndex - this->RecGraphInfo.tailIndex - 1
														+ this->RecGraphInfo.headIndex;
		}
		else
		{
			x += this->RecGraphInfo.writeIndex;
		}
	}
	quotient  = y / bits;
	remainder = y % bits;
#if _ENB_MYFB_RECORD_DEBUG_FUNC
	this->RecGraphInfo.imgbuff[x][quotient] |= Byte_mask_150[remainder];
#else
	this->RecGraphInfo.imgbuff[x][this->imgLineLen - 1 - quotient] |= RecMask_150[remainder];	
#endif

	return  TRUE;
}


/*****************************************************************************************
��������:	BOOL gen_PreSetPixel_110 (INT32 x, INT32 y)
�汾��:		1.0.0
��������:	2011.11.07
����:		zondan
����˵��:	�ڴ�ӡ�����й�����ӡ��
�������:	
�������:	
����˵��:	�����������ظ����á�
			ע��:��ͬ���͵Ĵ�ӡ�������޸Ĵ˺���������ֻ���110mm��ӡ������ʽ
*****************************************************************************************/
static BOOL gen_PreSetPixel_110(PRECDRVCLASS this, INT32 x, INT32 y)
{
	INT32  quotient;
	INT32  remainder;
	UINT8  bits = 8;
	INT32  i;

	if (y >= this->imgLineLen * bits)
	{
		y = this->imgLineLen * bits - 1;
	}
	else if (y < 0)
	{
		y = 0;
	}
	if (x < 0)
	{
		x = 0;
	}	
	else if (x >= 0)
	{
		if (x + this->RecGraphInfo.writeIndex > this->RecGraphInfo.tailIndex)
		{
			x = x + this->RecGraphInfo.writeIndex - this->RecGraphInfo.tailIndex - 1
														+ this->RecGraphInfo.headIndex;
		}
		else
		{
			x += this->RecGraphInfo.writeIndex;
		}
	}
	quotient  = y / bits;
	remainder = y % bits;
#if _ENB_MYFB_RECORD_DEBUG_FUNC
	this->RecGraphInfo.imgbuff[x][quotient] |= Byte_mask_150[remainder];
#else
	this->RecGraphInfo.imgbuff[x][this->imgLineLen - 1 - quotient] |= RecMask_150[remainder];	
#endif

	return  TRUE;
}


/*****************************************************************************************
��������:	BOOL gen_PreSetPixel_112(INT32 x, INT32 y)
�汾��:		1.0.0
��������:	2011.11.07
����:		zondan
����˵��:	�ڴ�ӡ�����й�����ӡ��
�������:	
�������:	
����˵��:	�����������ظ����á�
			ע��:��ͬ���͵Ĵ�ӡ�������޸Ĵ˺���������ֻ���110mm��ӡ������ʽ
*****************************************************************************************/
static BOOL gen_PreSetPixel_112(PRECDRVCLASS this, INT32 x, INT32 y)
{
	INT32  quotient;
	INT32  remainder;
	UINT8  bits = 8;
	INT32  i;

	//printf ("gen_PreSetPixel_112: this->RecGraphInfo.imgbuff ... 0x%x\r\n", this->RecGraphInfo.imgbuff); //pengyang
	if (y >= this->imgLineLen * bits)
	{
		y = this->imgLineLen * bits - 1;
	}
	else if (y < 0)
	{
		y = 0;
	}
	if (x < 0)
	{
		x = 0;
	}	
	else if (x >= 0)
	{
		if (x + this->RecGraphInfo.writeIndex > this->RecGraphInfo.tailIndex)
		{
			x = x + this->RecGraphInfo.writeIndex - this->RecGraphInfo.tailIndex - 1
														+ this->RecGraphInfo.headIndex;
		}
		else
		{
			x += this->RecGraphInfo.writeIndex;
		}
	}
	quotient  = y / bits;
	remainder = y % bits;
#if _ENB_MYFB_RECORD_DEBUG_FUNC
	this->RecGraphInfo.imgbuff[x][quotient] |= RecMask_150[remainder];
#else
	this->RecGraphInfo.imgbuff[x][this->imgLineLen - 1 - quotient] |= Byte_mask_150[remainder];	
#endif

	return  TRUE;
}


/*****************************************************************************************
��������:	BOOL gen_SetPixel (INT32 x, INT32 y)
�汾��:		1.0.0
��������:	2011.11.07
����:		zondan
����˵��:	������ӡ����������������ӡ�����е���Ĵ�ӡ
�������:	
�������:	
����˵��:	�����ڲ�ͬ���ʹ�ӡ������
*****************************************************************************************/
static BOOL gen_SetPixel(PRECDRVCLASS this, INT32 x, INT32 y)
{
	this->RecPreSetPixel (this, x, y);
	this->RecWriteIndexADD (this, x + 1);
	return  TRUE;
}


static BOOL gen_RecPrevline(PRECDRVCLASS this, INT32 y0, INT32 y1, INT32 x, INT32 thick)
{
	int tmp;
	int y;
	int i;

	if (y0 > y1)
	{
		tmp = y1;
		y1 = y0;
		y0 = tmp;
	}
	for (y = y0; y < y1; y++)
	{
		if (thick > 0)
		{
			i = 1;
			for (; i <= thick / 2; i++)
			{
				if (x >= i)
				{
					this->RecPreSetPixel (this, x - i, y);
				}
				this->RecPreSetPixel (this, x + i, y);
			}
			if (thick % 2)
			{
				this->RecPreSetPixel (this, x + i, y);
			}
		}
		this->RecPreSetPixel (this, x, y);
	}
	return TRUE;
}


static BOOL gen_Recvline(PRECDRVCLASS this, INT32 y0, INT32 y1, INT32 x, INT32 thick)
{
	this->RecPrevline (this, y0, y1, x, thick);
	this->RecWriteIndexADD (this, x + 1);
}


static BOOL gen_RecPrehline(PRECDRVCLASS this, INT32 x0, INT32 x1, INT32 y, INT32 thick)
{
	int tmp;
	int x;
	int i;

	if (x0 > x1)
	{
		tmp = x1;
		x1 = x0;
		x0 = tmp;
	}
	for (x = x0; x <= x1; x++)
	{
		if (thick > 0)
		{
			i = 1;
			for (; i <= thick / 2; i++)
			{
				if (y >= i)
				{
					this->RecPreSetPixel (this, x, y - i);
				}
				this->RecPreSetPixel (this, x, y + i);
			}
			if (thick % 2)
			{
				this->RecPreSetPixel (this, x, y + i);
			}
		}
		this->RecPreSetPixel (this, x, y);
	}
	return TRUE;
}


static BOOL gen_Rechline(PRECDRVCLASS this, INT32 x0, INT32 x1, INT32 y, INT32 thick)
{
	INT32  diff;

	this->RecPrehline (this, x0, x1, y, thick);
	if (x1 > x0)
	{
		diff = x1 - x0;
	}
	else
	{
		diff = x0 - x1;
	}
	this->RecWriteIndexADD (this, diff);	
}


/*****************************************************************************************
��������:	BOOL gen_RecPreLine (INT32 x0, INT32 y0, INT32 x1, INT32 y1, INT32 thick)
�汾��:		1.0.0
��������:	2011.11.07
����:		zondan
����˵��:	�ڴ�ӡ�����й�����ӡֱ��
�������:	thick: ��ӡ��ֱ�ߵĿ�����ã�Ϊ�Ӵִ�ӡ��ƣ�Ĭ��Ϊ0
�������:	
����˵��:	�����ڲ�ͬ���ʹ�ӡ������
*****************************************************************************************/
static BOOL gen_RecPreLine(PRECDRVCLASS this, INT32 x0, INT32 y0, INT32 x1, INT32 y1, INT32 thick)
{
	INT32  dx;
	INT32  dy;
	INT32  tmp;
	INT32  h;
	INT32  t;
	INT32  x, y;
	INT32  i;

	if(x0 > x1)
	{
		tmp = x0;
		x0 = x1;
		x1 = tmp;

		tmp = y0;
		y0 = y1;
		y1 = tmp;
	}
	dx = x1 - x0;
	dy = y1 - y0;
	x = x0;
	y = y0;

	if (thick > 0)
	{
		i = 1;
		for (; i <= thick / 2; i++)
		{
			if (y >= i)
				this->RecPreSetPixel (this, x, y - i);
			this->RecPreSetPixel (this, x, y + i);
		}
		if (thick % 2)
		{
			this->RecPreSetPixel (this, x, y + i);
		}
	}
	this->RecPreSetPixel (this, x, y);
	
	if (dx == 0)
	{
		this->RecPrevline (this, y0, y1, x, thick);
		return TRUE;
	}
	if (dy == 0)
	{
		this->RecPrehline (this, x0, x1, y, thick);
		return TRUE;
	}	
	if (dy > 0)
	{
		if (dy <= dx)
		{
			h = 2 * dy - dx;
			while (x != x1)
			{
				if (h < 0)
				{
					h += 2 * dy;
				}
				else
				{
					y ++;
					h += 2 * (dy - dx);
				}
				if (thick > 0)
				{
					i = 1;
					for (; i <= thick / 2; i++)
					{
						if (y >= i)
							this->RecPreSetPixel (this, x, y - i);
						this->RecPreSetPixel (this, x, y + i);
					}
					if (thick % 2)
					{
						this->RecPreSetPixel (this, x, y + i);
					}
				}
				this->RecPreSetPixel (this, x, y);
				x ++;
			}
		}
		else
		{
			h = 2 * dx - dy;
			while (y != y1)
			{
				if(h < 0)
				{
					h += 2 * dx;
				}
				else
				{
					++ x;
					h += 2 * (dx - dy);
				}
				if (thick > 0)
				{
					i = 1;
					for (; i <= thick / 2; i++)
					{
						if (x >= i)
							this->RecPreSetPixel (this, x - i, y);
						this->RecPreSetPixel (this, x + i, y);
					}
					if (thick % 2)
					{
						this->RecPreSetPixel (this, x + i, y);
					}
				}
				this->RecPreSetPixel (this, x, y);
				y ++;
			}
		}
	}
	else
	{
		t = -dy;
		if (t <= dx)
		{
			h = 2 * dy + dx;
			while (x != x1)
			{
				if (h < 0)
				{
					h += 2 * (dy + dx);
					y --;
				}
				else
				{
					h += 2 * dy;
				}
				if (thick > 0)
				{
					i = 1;
					for (; i <= thick / 2; i++)
					{
						if (y >= i)
							this->RecPreSetPixel (this, x, y - i);
						this->RecPreSetPixel (this, x, y + i);
					}
					if (thick % 2)
					{
						this->RecPreSetPixel (this, x, y + i);
					}
				}
				this->RecPreSetPixel (this, x, y);
				x ++;
			}
		}
		else
		{
			h = -(2 * dx * dy) - (dy * dy);
			while (y != y1)
			{
				if (h < 0)
				{
					h += -(2 * dx * dy);
				}
				else
				{
					h += -(2 * dx * dy) - (2 * dy * dy);
					x ++;
				}
				if (thick > 0)
				{
					i = 1;
					for (; i <= thick / 2; i++)
					{
						if (x >= i)
							this->RecPreSetPixel (this, x - i, y);
						this->RecPreSetPixel (this, x + i, y);
					}
					if (thick % 2)
					{
						this->RecPreSetPixel (this, x + i, y);
					}
				}
				this->RecPreSetPixel (this, x, y);
				y --;
			}
		}
	}
	return TRUE;
}


/*****************************************************************************************
* Function	: gen_RecPreLongVertiLine
* Description : ��Ϊ��ӡ��������������,�������Ĵ�ֱ����Ҫ���⴦��
* Input Para  : 
* Output Para : 
* Return Value: 
*****************************************************************************************/
static VOID gen_RecPreLongVertiLine
	(PRECDRVCLASS this, INT32 x, INT32 y0, INT32 y1, INT32 thick, INT32 weak)
{
	INT32 i, pos;
	
	if (weak < 1)
		return;
	
	if (thick < 1)
		return;
	
	if (y0 > y1)
	{
		pos = y1;
		y1 = y0;
		y0 = pos;
	}
	
	for (i = 0; i < thick; i++)
	{
		pos = y0 + i % 2;
		while (pos < y1)
		{
			this->RecPreSetPixel (this, x, pos);
			pos += weak;
		}
	}
}

/*****************************************************************************************
��������:	BOOL gen_RecLine (PRECDRVCLASS this, INT32 x0, INT32 y0, INT32 x1, INT32 y1, INT32 thick)
�汾��:		1.0.0
��������:	2011.11.07
����:		zondan
����˵��:	������ӡ����������������ӡ������ֱ�ߵĴ�ӡ
�������:	
�������:	
����˵��:	�����ڲ�ͬ���ʹ�ӡ������
*****************************************************************************************/
static BOOL gen_RecLine(PRECDRVCLASS this, INT32 x0, INT32 y0, INT32 x1, INT32 y1, INT32 thick)
{
	INT32  diff;
	
	this->RecPreLine (this, x0, y0, x1, y1, thick);
	if (x1 > x0)
	{
		diff = x1 - x0;
	}
	else
	{
		diff = x0 - x1;
	}
	this->RecWriteIndexADD (this, diff);
}


static BOOL gen_RecPreShowChar(PRECDRVCLASS this, INT32 x, INT32 y, INT32 w, INT32 h, UCHAR *imgP)
{
	INT32		nr_bytes;
	INT32		remained;
	UCHAR		 *p;
	INT32		 i;
	INT32		j;
	INT32		m;
	INT32		index;
	INT32		iy;
	INT32		ix;

	p		= imgP;
	nr_bytes = w >> 3;
	remained = w & 0x07;
	ix	   = x;
	iy	   = y;

	for (i = 0; i < h; i ++)
	{
		index = 0;
		for (j = 0; j < nr_bytes; j++)
		{
			for (m = 0; m < 8; m ++)
			{				
				if ((*p) & Byte_mask_150[m])
				{
					this->RecPreSetPixel (this, ix, iy);
				}
				iy ++;
			}
			p++;
		}
		for (j = 0; j < remained; j++)
		{
			if ((*p) & Byte_mask_150[j])
			{
				this->RecPreSetPixel (this, ix, iy);
			}
			iy ++;
		}
		if (remained)
			p++;

		ix ++;
		iy = y;
	}
}


/*****************************************************************************************
��������:	BOOL gen_RecShowChar (PRECDRVCLASS this, INT32 x, INT32 y, INT32 w, INT32 h, UCHAR * imgP)
�汾��:		1.0.0
��������:	2011.11.07
����:		zondan
����˵��:	��������ӡ�����ַ�
�������:	
�������:	
����˵��:	
*****************************************************************************************/
static BOOL gen_RecShowChar(PRECDRVCLASS this, INT32 x, INT32 y, INT32 w, INT32 h, UCHAR * imgP)
{
	this->RecPreShowChar (this, x, y, w, h, imgP);
	this->RecWriteIndexADD (this, w);
}


/*****************************************************************************************
��������:	UINT8*  RecHConverToV (PRECDRVCLASS this, UINT32 bitW, UINT32 bitH, UINT8 heading, UINT8 *data)
�汾��:		1.0.0
��������:	2011.11.07
����:		zondan
����˵��:	���ݲ�ͬ�Ĵ�ӡ���ԣ�����ȡ�Ĵ�ӡ��ģ���ݽ�����ת����ת�Ƕȸ���heading�趨
�������:	
�������:	������ת��Ĵ�ӡ��ģ����
����˵��:	RecConverCache_150�����޶��˴�ӡ�ַ���w��h���ɸ�����Ҫ�����޸ģ�Ŀǰ���֧��100*100
			����ʹ��malloc���䶯̬�ڴ�ʱ��ӡ�����Ǵ�ӡ�հף�(�������ڴ���ִ��ʱ�����)������
			��̬�ڴ�������΢�õ���ת���������ڸ�Ϊ��̬�ڴ���ʽ��
*****************************************************************************************/
#if REC_CHAR_CONVERT_MEM
static UINT8  RecHConverToVBuf[MAX_RECORD_CHAR_W][MAX_RECORD_CHAR_H];
#endif
static UINT8* gen_RecHConverToV(PRECDRVCLASS this, UINT32 bitW, UINT32 bitH, UINT8 heading, UINT8 *databuf)
{
	UINT32  i;
	UINT32  j;
	UINT32  nr_bytes;
	UINT32  w = bitW;
	UINT32  h = bitH;
	UINT32  index;
	UINT32  len;
	UINT32  tmp;
#if REC_CHAR_CONVERT_MEM	
	UINT8   *bitflag[MAX_RECORD_CHAR_H];
#else
	UINT8   **bitflag;  //ʹ�ö�̬�����ڴ�
#endif
	UINT8   *p = (UINT8 *)this->Data;
	UINT8   buff[100];
	UINT8   *pp;

	if ((bitW <= 0) || (bitH <= 0))
		return NULL;

	nr_bytes = (w + 7) >> 3;
	w = nr_bytes * 8;

	memset (buff, 0, sizeof (buff));
	memset (this->Data, 0, 400);
	memcpy (this->Data, databuf, bitH * nr_bytes);

	nr_bytes = (h + 7) >> 3;
	h = nr_bytes * 8;

#if REC_CHAR_CONVERT_MEM
	for (i = 0; i < MAX_RECORD_CHAR_H; i++)
	{
		bitflag[i] = RecHConverToVBuf[i];
		memset (RecHConverToVBuf[i], 0, sizeof(RecHConverToVBuf[i]));
	}
#else	
	//ʹ�ö�̬�����ڴ�
	bitflag = (CHAR **) malloc(sizeof(CHAR *) * h);
	for (i = 0; i < h; i++)
	{
		bitflag[i] = (UINT8 *)malloc (w);
		memset (bitflag[i], 0, w);
	}
#endif	
	len = w * h / 8;
	for (i = 0; i < len; i++)
	{
		for (j = 0; j < 8; j++)
		{
			if (*p & Byte_mask_150[j])
			{
				tmp = i * 8 + j;
				bitflag[tmp / w][tmp % w] = 1;
			}
		}
		*p ++;
	}
	memset (this->Data, 0, len);
	p	   = (UINT8 *)this->Data;
	index   = 0;
	tmp	 = 0;

	if (heading == 1)	// �ı���ģ��ȡ����, headingΪ1��������; headingΪ0��������, Ĭ��Ϊ0
	{
		for (i = 0; i < bitH / 2; i++)
		{
			memcpy (buff, bitflag[i], w);
			memcpy (bitflag[i], bitflag[bitH - i - 1], w);
			memcpy (bitflag[bitH - i - 1], buff, w);
		}
		for (i = 0; i < bitW; i++)
		{
			for (j = 0; j < h; j++)
			{
				if (bitflag[j][i])
					tmp |= Byte_mask_150[index];
		
				if (++index >= 8)
				{
					*p ++ = tmp;
					tmp   = 0;
					index = 0;
				}
			}
		}
	}
	else if (heading == 3)// ��ת90
	{
		for (i = 0; i < bitH / 2; i++)
		{
			memcpy (buff, bitflag[i], w);
			memcpy (bitflag[i], bitflag[bitH - i - 1], w);
			memcpy (bitflag[bitH - i - 1], buff, w);
		}
		for (i = 0; i < bitW; i++)
		{
			for (j = 0; j < h; j++)
			{
				if (bitflag[i][j])
					tmp |= Byte_mask_150[index];
		
				if (++index >= 8)
				{
					*p ++ = tmp;
					tmp   = 0;
					index = 0;
				}
			}
		}
	}
	else
	{
		for (i = 0; i < bitW; i++)
		{
			for (j = 0; j < h; j++)
			{
				if (bitflag[j][i])
					tmp |= Byte_mask_150[index];
		
				if (++index >= 8)
				{
					*p ++ = tmp;
					tmp   = 0;
					index = 0;
				}
			}
		}
	}

#if (!REC_CHAR_CONVERT_MEM)	
	 //ʹ�ö�̬�����ڴ�
	for (i = 0; i < h; i++)
	{
		free (bitflag[i]);
	}

	free (bitflag);
#endif
	p = (UINT8 *)this->Data;
	return  p;
}


/*****************************************************************************************
��������:	UINT8 gen_RecPreShowCharacter (PRECDRVCLASS this, INT32 x, INT32 y, PLOGFONT font, UINT8 direct, UINT8 *buff)
�汾��:		1.0.0
��������:	2011.11.07
����:		zondan
����˵��:	��ȡ��������ӡ�ַ����Ĵ�ӡ������
�������:	
�������:	
����˵��:	directΪ��ӡ�ַ����ķ��򣬸��ݲ�ͬ�Ĵ�ӡ���趨�˲�����Ĭ��Ϊ0
*****************************************************************************************/
static INT32 gen_RecPreShowCharacter(PRECDRVCLASS this, INT32 x, INT32 y, PLOGFONT logfont, UINT8 direct, UINT8 conver, UINT8 *buff)
{
	if (NULL == logfont)
	{
		// Ĭ�ϴ�ӡ����
		logfont = (PLOGFONT)this->font_normal;
	}
	DEVFONT * sbc_devfont = logfont->sbc_devfont;
	DEVFONT * mbc_devfont = logfont->mbc_devfont;
	INT32	 sbc_height  = (*sbc_devfont->font_ops->get_font_height)(logfont, sbc_devfont);;
	INT32	 mbc_height  = 0;
	INT32	 sbc_width   = 0;
	INT32	 mbc_width   = 0;
	INT32	 left_bytes  = 0;
	INT32	 len_cur_char;
	UCHAR	 *string;
	UCHAR	 *printData;
	UINT8	 i, j;
	INT32	 len, width;
	PLOGFONT  tmp_font;

	len		= strlen (buff);
	left_bytes = len;
	width	  = 0;
	if (mbc_devfont)
		mbc_height = (*mbc_devfont->font_ops->get_font_height)(logfont, mbc_devfont);

	while (left_bytes)
	{
		if (mbc_devfont != NULL)
		{
			len_cur_char = (*mbc_devfont->charset_ops->len_first_char)(buff, left_bytes);
			if (len_cur_char != 0)
			{
				mbc_width = (*mbc_devfont->font_ops->get_char_width)
							(logfont, mbc_devfont, buff, len_cur_char);
				string	= (UCHAR *)(*mbc_devfont->font_ops->get_char_bitmap)
							(logfont, mbc_devfont, buff, len_cur_char);
				printData = this->RecHConverToV(this, mbc_width, mbc_height, conver, string);
				this->RecPreShowChar(this, x, y, mbc_height, mbc_width, printData);
				if (direct)
				{
					width += mbc_width;
					x	 += mbc_width;
				}
				else
				{
					width = mbc_width;
					y	+= mbc_height + 2;
				}
				
				left_bytes -= len_cur_char;
				buff	   += len_cur_char;
				continue;
			}
		}

		len_cur_char = (*sbc_devfont->charset_ops->len_first_char)(buff, left_bytes);
		if (len_cur_char != 0)
		{
			sbc_width = (*sbc_devfont->font_ops->get_char_width)
						(logfont,sbc_devfont, buff, len_cur_char);
			string	= (UCHAR *)(*sbc_devfont->font_ops->get_char_bitmap)
						(logfont,sbc_devfont, buff, len_cur_char);
			printData = this->RecHConverToV(this, sbc_width, sbc_height, conver, string);
			this->RecPreShowChar(this, x, y, sbc_height, sbc_width, printData);
		}
		else
		{
			break;
		}

		if (direct)
		{
			width += sbc_width;
			x	 += sbc_width;
		}
		else
		{
			if (width < sbc_width)
				width  = sbc_width;
				
			y += sbc_height;
		}
		
		left_bytes -= len_cur_char;
		buff	   += len_cur_char;
	}
	return  width;
}


static INT32 gen_RecShowCharacter(PRECDRVCLASS this, INT32 x, INT32 y, PLOGFONT logfont, UINT8 direct, UINT8 conver, UINT8 *buff)	//direct 1Ϊ����, 0Ϊ����, Ĭ��Ϊ0
{
	INT32 width = 0;
	
	width = this->RecPreShowCharacter (this, x, y, logfont, direct, conver, buff);
	this->RecWriteIndexADD (this, width);	
	
	return width;
}


/*****************************************************************************************
��������:	INT32 RecPrintCoder_150 (CHAR *input)
�汾��:		1.0.0
��������:	2011.11.07
����:		zondan
����˵��:	����150mm��ӡ����ͨ��Э�飬�Դ�ӡ�����ݰ�����ѹ������
�������:	
�������:	
����˵��:	
			����һ�����ݵ�ѹ���㷨����:
			���ڴ�ӡ�ĵ������ݵ��Ƿ�0��1����ĳ����Ҫ��ӡ����õ�Ϊ1���粻��Ҫ��ӡ���õ�Ϊ0��
			һ�д�ӡ����λ144 ���ֽڣ���144*8 = 1152 ���㡣
			��ѹ�������򵥡�ʵ�ã�ԭ�����£�����144���ֽڣ��������еĲ���ӡ���ֽڣ�����0x00��
			��ȫ��ӡ���ֽڣ�����0xff������ѹ�����������ִ�ӡ���ֽ����ݲ��䣬���ǵ�ʵ�ʴ�ӡʱ��
			һ�е����ݵ���󲿷��ǲ���ӡ�ģ������ܹ������ؽ�����������
			����0x00 ��0xff �ֽڣ�����һ���ֽڱ�ʾ0x00 ��0xff ���ظ�������
			���磺0x00 0x20 0x1f 0x1a 0xff 0x05  ���ʾ��32��0x00 + 0x1f + 0x1a + 5��0xff.
*****************************************************************************************/
static INT32 RecPrintCoder_150(UINT8 *input)
{
	INT16 i;
	INT16 ct00 = 0;
	INT16 ctff = 0;
	INT16 ser  = 5;
	INT16 sum;
	uint8 outdata[150];
	int16 datlen;		 //ѹ�������ڴ��ڷ��͵�һ�������ܳ��ȣ�������ͷ��У���
	INT32 sent = 0;

	i = 0;
	while(i < 144)
	{
		if (input[i] == 0x00)
		{
			if( ctff >0)
		{
				outdata[ser] = ctff;
				ser++;
				ctff = 0;
			}
			ct00++;
			if (ct00 == 1)
			{
				outdata[ser] = 0x00;
				ser++;
			}
			if (i == 143)
			{
				outdata[ser] = ct00;
				ser++;
			}
		}
		else
			if (input[i] == 0xff)
			{
				if (ct00 >0 )
				{
					outdata[ser] = ct00;
					ser++;
					ct00 = 0;
				}
				ctff++;
				if (ctff == 1)
				{
					outdata[ser] = 0xff;
					ser++;
				}
				if (i == 143)
				{
					outdata[ser] = ctff;
					ser++;
				}
			}
			else
			{
				if (ctff >0)
				{
				  outdata[ser] = ctff;
				  ser++;
				  ctff = 0;
				}
				if (ct00 >0)
				{
					outdata[ser] = ct00;
					ser++;
					ct00 = 0;
				}
				outdata[ser] = input[i];
				ser ++;
			}
		i++;
	}
	outdata[0] = 0x55;
	outdata[1] = 0xaa;
	outdata[2] = 0x03;
	outdata[3] = (ser -5) >> 8;
	outdata[4] = (ser -5) % 256;
	sum = outdata[3] + outdata[4];
	for (i = 0; i < ser - 5; i++)
	{
	  sum = sum + outdata[i + 5];
	}
	outdata[ser] = sum;
	datlen = ser + 1;
	UartWrite(UART_PORT_PRINTER, &outdata[0], datlen, &sent, 0);
}


/*****************************************************************************************
��������:	INT32 RecPrintCoder_112(CHAR *input)
�汾��:		1.0.0
��������:	2011.11.07
����:		zondan
����˵��:	����150mm��ӡ����ͨ��Э�飬�Դ�ӡ�����ݰ�����ѹ������
�������:	
�������:	
����˵��:	
			����һ�����ݵ�ѹ���㷨����:
			���ڴ�ӡ�ĵ������ݵ��Ƿ�0��1����ĳ����Ҫ��ӡ����õ�Ϊ1���粻��Ҫ��ӡ���õ�Ϊ0��
			һ�д�ӡ����λ144 ���ֽڣ���144*8 = 1152 ���㡣
			��ѹ�������򵥡�ʵ�ã�ԭ�����£�����144���ֽڣ��������еĲ���ӡ���ֽڣ�����0x00��
			��ȫ��ӡ���ֽڣ�����0xff������ѹ�����������ִ�ӡ���ֽ����ݲ��䣬���ǵ�ʵ�ʴ�ӡʱ��
			һ�е����ݵ���󲿷��ǲ���ӡ�ģ������ܹ������ؽ�����������
			����0x00 ��0xff �ֽڣ�����һ���ֽڱ�ʾ0x00 ��0xff ���ظ�������
			���磺0x00 0x20 0x1f 0x1a 0xff 0x05  ���ʾ��32��0x00 + 0x1f + 0x1a + 5��0xff.
*****************************************************************************************/
static INT32 RecPrintCoder_112(PRECDRVCLASS this)
{
	//PrinterTestFunc();
	PrintLine_112mm(this);
}


/*****************************************************************************************
��������:	VOID gen_RecClrGraphBuff (PRECDRVCLASS *this, INT32 index)
�汾��:		1.0.0
��������:	2011.11.07
����:		zondan
����˵��:	Ϊ��ʵ�ִ�ӡ���������ظ����ã����벻����մ�ӡ������
�������:	
�������:	
����˵��:	
*****************************************************************************************/
static VOID gen_RecClrGraphBuff(PRECDRVCLASS this, INT32 index)
{
	memset (this->RecGraphInfo.imgbuff[index], 0, this->imgLineLen);
}


/*****************************************************************************************
��������:	BOOL gen_RecPrintSend_150 (PRECDRVCLASS *this, CHAR rec_type)
�汾��:		1.0.0
��������:	2011.11.07
����:		zondan
����˵��:	�ϲ���ã���ʼ��ӡ�Ѿ���װ�õĴ�ӡ����������
�������:	
�������:	
����˵��:	myfb_debug_line:�򿪺�󣬿����Դ��н��е��ԣ�Ҫ�ڲ�ͬ�ķֱ����½��е��ԣ�����
			�����޸Ķ�Ӧ����.
*****************************************************************************************/
static BOOL gen_RecPrintSend_150(PRECDRVCLASS this)
{
#if _ENB_MYFB_RECORD_DEBUG_FUNC
	this->RecFBDebugLine(this);
#else
	RecPrintCoder_150(this->RecGraphInfo.imgbuff[this->RecGraphInfo.readIndex]);
#endif
	this->RecClrGraphBuff(this, this->RecGraphInfo.readIndex);
	return TRUE;
}

static VOID PutPrintBmpToBmpFile(PRECDRVCLASS this)
{
	static FILE *fp = NULL;
	static UCHAR bmpHead[] = {
		0x42, 0x4D, 0x3E, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x3E, 0x00, 0x00, 0x00, 0x28, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x01, 0x00, 0x01, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0xFF, 0xFF, 0xFF, 0x00};
	static PBMPFILEHEAD pHead = (PBMPFILEHEAD)bmpHead;
	static UCHAR LineBuff[RECPAPERWIDTH_MAX];
	UCHAR tmp;
	int i, j;
	if (fp == NULL)
	{
		fp = fopen("/mnt/data/record.bmp", "wb+");
		pHead->biSizeImage = 0;
		pHead->bfSize = pHead->biSize + pHead->biSizeImage;
		pHead->biWidth = (RECPAPERWIDTH_MAX << 3);
		pHead->biHeight = 0;
		fwrite(bmpHead, sizeof(bmpHead), 1, fp);
	}
	if (fp)
	{
		pHead->biHeight++;
		pHead->biSizeImage += RECPAPERWIDTH_MAX;
		pHead->bfSize = pHead->biSize + pHead->biSizeImage;
		fseek(fp, 0, SEEK_SET);
		fwrite(pHead, 40, 1, fp);
		fseek(fp, 0, SEEK_END);
		memcpy(LineBuff,
				this->RecGraphInfo.imgbuff[this->RecGraphInfo.readIndex],
				sizeof(LineBuff));
		for (i = 0; i < RECPAPERWIDTH_MAX; i++)
		{
			if (LineBuff[i] == 0 || LineBuff[i] == 0xFF)
				continue;
			tmp = 0;
			for (j = 0; j < 8; j++)
			{
				if (LineBuff[i] & RecMask_150[j])
				{
					tmp |= Byte_mask_150[j];
				}
			}
			LineBuff[i] = tmp;
		}
		fwrite(LineBuff, sizeof(LineBuff), 1, fp);
		flush(fp);
	}
}

/*****************************************************************************************
��������:	BOOL gen_RecPrintSend_112(PRECDRVCLASS *this, CHAR rec_type)
�汾��:		1.0.0
��������:	2011.11.07
����:		zondan
����˵��:	�ϲ���ã���ʼ��ӡ�Ѿ���װ�õĴ�ӡ����������
�������:	
�������:	
����˵��:	myfb_debug_line:�򿪺�󣬿����Դ��н��е��ԣ�Ҫ�ڲ�ͬ�ķֱ����½��е��ԣ�����
			�����޸Ķ�Ӧ����.
*****************************************************************************************/
static BOOL gen_RecPrintSend_112(PRECDRVCLASS this)
{
	static int count = 0;
	static char second = 0;
	count++;
#if _ENB_MYFB_RECORD_DEBUG_FUNC
	this->RecFBDebugLine (this);
#else
	RecPrintCoder_112(this);
#endif
//	PutPrintBmpToBmpFile(this);
	this->RecClrGraphBuff(this, this->RecGraphInfo.readIndex);
//	if (second != DateTime.second)
//	{
//		second = DateTime.second;
//		printf("second %d::%d\n", second, count);
//		count = 0;
//	}
	return TRUE;
}


static VOID RecImgConver_110(PRECDRVCLASS this)
{
	this = this;
}


static BOOL gen_RecPrintSend_110(PRECDRVCLASS this)
{
#if _ENB_MYFB_RECORD_DEBUG_FUNC
	this->RecFBDebugLine (this);
#else
	RecImgConver_110 (this);
#endif
}


static VOID gen_RecSetReadIndex(PRECDRVCLASS this, INT32 index)
{
	this->RecGraphInfo.readIndex = index;
}


static VOID gen_RecSetWriteIndex(PRECDRVCLASS this, INT32 index)
{
	this->RecGraphInfo.writeIndex = index;
}


static VOID gen_RecSetHeadIndex(PRECDRVCLASS this, INT32 index)
{
	this->RecGraphInfo.headIndex = index;
}


static VOID gen_RecSetTailIndex(PRECDRVCLASS this, INT32 index)
{
	this->RecGraphInfo.tailIndex = index;
}


static INT32 gen_RecGetReadIndex(PRECDRVCLASS this)
{
	return this->RecGraphInfo.readIndex;
}


static INT32 gen_RecGetWriteIndex(PRECDRVCLASS this)
{
	return this->RecGraphInfo.writeIndex;
}


static INT32 gen_RecGetHeadIndex(PRECDRVCLASS this)
{
	return this->RecGraphInfo.headIndex;
}


static INT32 gen_RecGetTailIndex(PRECDRVCLASS this)
{
	return this->RecGraphInfo.tailIndex;
}


static INT32 gen_RecWriteIndexADD(PRECDRVCLASS this, INT32 add)
{
	if (this->RecGraphInfo.writeIndex + add > this->RecGraphInfo.tailIndex)
	{
		this->RecGraphInfo.writeIndex = this->RecGraphInfo.headIndex + this->RecGraphInfo.writeIndex
													+ add - 1 - this->RecGraphInfo.tailIndex;
	}
	else
	{
		this->RecGraphInfo.writeIndex += add;
	}

	return this->RecGraphInfo.writeIndex;
}


static INT32 gen_RecPrintCR(PRECDRVCLASS this, INT32 width)
{
	INT32  i;
	INT32  w_index = this->RecGetWriteIndex (this);
	INT32  t_index = this->RecGetTailIndex (this);

	for (i = 0; i < width; i++)
	{
		this->RecClrGraphBuff(this, w_index);
		if (++ w_index > t_index)
		{
			w_index = this->RecGetHeadIndex(this);
		}
	}
	this->RecWriteIndexADD(this, width);
}


static VOID gen_RecFBDebugSetPixel_150(PRECDRVCLASS this)
{
#if _ENB_MYFB_RECORD_DEBUG_FUNC
	myfb_debug_pixel (&this->RecGraphInfo.imgbuff[0][0], this->RecGraphInfo.readIndex);
#endif	
}


static VOID gen_RecFBDebugLine_150(PRECDRVCLASS this)
{
#if _ENB_MYFB_RECORD_DEBUG_FUNC
	myfb_debug_line (&this->RecGraphInfo.imgbuff[0][0], this->RecGraphInfo.readIndex, this->RecGraphInfo.readIndex);
#endif
}


static VOID gen_RecFBDebugSetPixel_112(PRECDRVCLASS this)
{
#if _ENB_MYFB_RECORD_DEBUG_FUNC
	myfb_debug_pixel(&this->RecGraphInfo.imgbuff[0][0], this->RecGraphInfo.readIndex);
#endif	
}


static VOID gen_RecFBDebugLine_112(PRECDRVCLASS this)
{
#if _ENB_MYFB_RECORD_DEBUG_FUNC
	myfb_debug_line(&this->RecGraphInfo.imgbuff[0][0], this->RecGraphInfo.readIndex, this->RecGraphInfo.readIndex);
#endif
}


static VOID gen_RecFBDebugSetPixel_110(PRECDRVCLASS this)
{
#if _ENB_MYFB_RECORD_DEBUG_FUNC
	INT32  tmp_read = this->RecGetReadIndex (this);
	INT32  tmp_tail = this->RecGetTailIndex (this);
	INT32  tmp_head = this->RecGetHeadIndex (this);
	INT32  i;

	for (i = 0; i < 24; i++)
	{
		myfb_debug_pixel (&this->RecGraphInfo.imgbuff[0][0], tmp_read);
		this->RecClrGraphBuff (this, tmp_read);
		if (++tmp_read > tmp_tail)
		{
			tmp_read = tmp_head;
		}
	}
#endif	
}


static VOID gen_RecFBDebugLine_110(PRECDRVCLASS this)
{
#if _ENB_MYFB_RECORD_DEBUG_FUNC
	INT32  tmp_read = this->RecGetReadIndex (this);
	INT32  tmp_tail = this->RecGetTailIndex (this);
	INT32  tmp_head = this->RecGetHeadIndex (this);
	INT32  i;

	for (i = 0; i < 24; i++)
	{
		myfb_debug_line (&this->RecGraphInfo.imgbuff[0][0], tmp_read, tmp_read);
		this->RecClrGraphBuff (this, tmp_read);
		if (++tmp_read > tmp_tail)
		{
			tmp_read = tmp_head;
		}
	}
#endif	
}


static VOID gen_RecSetNormalFont(PRECDRVCLASS this, INT32 font_id)
{
	this->font_normal = font_id;
}


static VOID gen_RecSetCutterFont(PRECDRVCLASS this, INT32 font_id)
{
	this->font_cutter = font_id;
}


static INT32 gen_RecDrawBitmap(PRECDRVCLASS this, INT32 x, INT32 y, RECICONID icon_id)
{
	UINT8	  *imgPtr;
	PRECBITMAP imgdata;

	imgdata = &sRecIcon[icon_id];
	imgPtr  = this->RecHConverToV (this, imgdata->width, imgdata->height, 0, (UINT8 *)imgdata->bits);
	this->RecPreShowChar (this, x, y, imgdata->height, imgdata->width, imgPtr);

	return imgdata->width;
}


static VOID DoNothing(PRECDRVCLASS this)
{
	this = this;
}

static VOID gen_RecTrusteeship(PRECDRVCLASS this, INT32 *AddData)
{
	static INT32 *pp = NULL;// �����й����ݶ�������������ڴ���,����һ����̬����
	if (this != NULL)
	{
		if (AddData)
		{
			// ִ�г�ʼ��,������Դ
		}
		// �������
		/*
			Process.....
		*/
		// �ж��Ƿ����
		/*
			if (Process complete)
			{
			*/
				// �Զ��˳�
				AddData = (INT32*)this;
				this = NULL;
			/*
			
			}
			else
			{
				//���й����ݴ���������ڴ���
			}
		*/
	}
	if (this == NULL)
	{
		// �ͷ���Դ
		if (pp)
			free(pp);
		pp = NULL;
		if (AddData)
		{
			this = (PRECDRVCLASS)AddData;
			this->RecTrusteeship = NULL;
		}
	}
}


VOID RecRegisterOps(PRECDRVCLASS pRecord, INT8 paperType)
{
	pRecord->RecSetPixel			= gen_SetPixel;
	pRecord->RecPreLine				= gen_RecPreLine;
	pRecord->RecLine				= gen_RecLine;
	pRecord->RecPrevline			= gen_RecPrevline;
	pRecord->Recvline				= gen_Recvline;
	pRecord->RecPrehline			= gen_RecPrehline;
	pRecord->Rechline				= gen_Rechline;
	pRecord->RecPreLVline			= gen_RecPreLongVertiLine;
	pRecord->RecPreShowChar			= gen_RecPreShowChar;
	pRecord->RecShowChar			= gen_RecShowChar;
	pRecord->RecHConverToV			= gen_RecHConverToV;
	pRecord->RecPreShowCharacter	= gen_RecPreShowCharacter;	
	pRecord->RecShowCharacter		= gen_RecShowCharacter;
	pRecord->RecSetImgBuffPtr8		= gen_RecSetImgBuffPtr8;
	pRecord->RecClrGraphBuff		= gen_RecClrGraphBuff;
	pRecord->RecSetReadIndex		= gen_RecSetReadIndex;
	pRecord->RecSetWriteIndex		= gen_RecSetWriteIndex;
	pRecord->RecSetHeadIndex		= gen_RecSetHeadIndex;
	pRecord->RecSetTailIndex		= gen_RecSetTailIndex;
	pRecord->ResetRecImgBuff		= gen_ResetRecImgBuff;
	pRecord->RecGetReadIndex		= gen_RecGetReadIndex;
	pRecord->RecGetWriteIndex		= gen_RecGetWriteIndex;
	pRecord->RecGetHeadIndex		= gen_RecGetHeadIndex;
	pRecord->RecGetTailIndex		= gen_RecGetTailIndex;
	pRecord->RecWriteIndexADD		= gen_RecWriteIndexADD;
	pRecord->RecPrintCR				= gen_RecPrintCR;
	pRecord->RecSetNormalFont		= gen_RecSetNormalFont;
	pRecord->RecSetCutterFont		= gen_RecSetCutterFont;
	pRecord->RecDrawBitmap			= gen_RecDrawBitmap;  
	pRecord->RecTrusteeship			= gen_RecTrusteeship;
	switch (paperType)
	{
		case PAPER_TYPE_150MM:
			pRecord->RecInit			= gen_Init_150;
			pRecord->RecPreSetPixel	 = gen_PreSetPixel_150;
			pRecord->RecPrintSend	   = gen_RecPrintSend_150;
			pRecord->RecFBDebugSetPixel = gen_RecFBDebugSetPixel_150;
			pRecord->RecFBDebugLine	 = gen_RecFBDebugLine_150;
			break;

		case PAPER_TYPE_110MM:
			pRecord->RecInit			= gen_Init_110;
			pRecord->RecPreSetPixel	 = gen_PreSetPixel_110;
			pRecord->RecPrintSend	   = gen_RecPrintSend_110;
			pRecord->RecFBDebugSetPixel = gen_RecFBDebugSetPixel_110;
			pRecord->RecFBDebugLine	 = gen_RecFBDebugLine_110;			
			break;

		case PAPER_TYPE_112MM:
			pRecord->RecInit			= gen_Init_112;
			pRecord->RecPreSetPixel	 = gen_PreSetPixel_112;
			pRecord->RecPrintSend	   = gen_RecPrintSend_112;
			pRecord->RecFBDebugSetPixel = gen_RecFBDebugSetPixel_112;
			pRecord->RecFBDebugLine	 = gen_RecFBDebugLine_112;
			break;

		case PAPER_TYPE_PT1561P:
			pRecord->RecInit			= gen_InitPt1561p;
			pRecord->RecPreSetPixel		= gen_PreSetPixel_Pt1561p;
			pRecord->RecPrintSend		= gen_RecPrintSend_Pt1561p;
			pRecord->RecFBDebugSetPixel	= gen_RecFBDebugSetPixel_112;
			pRecord->RecFBDebugLine		= gen_RecFBDebugLine_112;
			break;

		default:
			break;
	}
}
#endif

