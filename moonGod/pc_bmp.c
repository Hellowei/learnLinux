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
#define   PCBMP_GLOBALS 


#include "includes.h"
#include "stdio.h"
#include "stdlib.h"
#include "string.h"



/****************************************************************
函数名称：  int Put24BmpFkle(HDC hdc, long x, long y, int mode, char *fpath);
功能描述：  将真彩24位的BMP文件读出，将图片存放在显存中，最大图片1024*768
			不支持压缩。
参数：	  图片的起始位置，图片存放的页，显示图片文件路径名称  
日期：	  
****************************************************************/
int Put24BmpFile (HDC hdc, long x, long y, int mode, char *fpath)
{
	//unsigned char	far *PBmp;			 //内存堆栈指针
	//unsigned int	 far *Mp;			   //显存指针
	//unsigned long	i, j;
	//unsigned char	temp;
	long			 linebytes;
	long			 Size = 0;			  //累加数据指针的长度
	BITMAPFILEHEADER BitHeader;			 //BMP文件结构的头
	BITMAPINFOHEADER BitInfoHeader;		 //BMP位图信息头
	FILE			*Fp;					//BMP文件指针
	long			 FOffset;			   //指针偏移量
	int			  h;					 //行循环计数变量
	int			  w;					 //列循环计数变量
	unsigned char	data[4] = {0};		 //临时保存象素的RGB数据；
	GAL_COLOR		rgb;
	GAL_PIXEL		color;
	PDC			  pdc;
	UINT8			err;

	mode = mode;//暂时用不上
	
	//打开需要显示的BMP文件
	Fp = fopen(fpath, "rb");
	if(Fp== NULL) {
		errprintf("can not open BMP files");
		return -1;
	}

	//打开BMP位图文件头
	fread(&BitHeader,sizeof(BitHeader),1,Fp);
	//读BMP文件信息，判断文件的合法性。
	if(BitHeader.bfType != 'M' * 256 + 'B') {
		errprintf("This Is Not A Bmp File.\n");
		fclose(Fp);
		return -1;
	}
	//打开BMP位图信息头
	fread(&BitInfoHeader,sizeof(BitInfoHeader),1,Fp);
	//24位色限定(只能识别真彩24位)
	if(BitInfoHeader.biBitCount != 24) {
		errprintf("This Programme Only For 24bit Colors Bitmap.\n");
		fclose(Fp);
		return -1;
	}
	//压缩限定（识别无压缩格式）
	if(BitInfoHeader.biCompress != 0) {
		errprintf("This Programme Only For no rar Bitmap.\n");
		fclose(Fp);
		return -1;
	}

	//图片大小限定最大1024*768
	if(BitInfoHeader.biWidth > 1024 || BitInfoHeader.biHeight > 768)
	{
		errprintf("Bitmap is too big.\n");
		fclose(Fp);
		return -1;
	}

	//定位到文件尾，扫描行由底向上存储，阵列中第一字节为左下角像素，最后一字节为右上角像素。
	fseek(Fp, 0, SEEK_END);
	
	//算出图片的首地址。
	linebytes = (((BitInfoHeader.biWidth * BitInfoHeader.biBitCount + 31) >> 5) << 2);
	Size = BitInfoHeader.biHeight * linebytes;
	fseek(Fp, 0 - FOffset, SEEK_END);//文件位置指针移到位图阵列的起始地址；
	pdc = dc_HDC2PDC(hdc);
	for(h = 0; h < BitInfoHeader.biHeight; h++)
	{
		RELEASE_GUI_PERMIT();//protect from block the Systime Task.
		GET_GUI_PERMIT();

		//将真彩24位的数据转换成8位，高位为0，R＝3，G＝2，B＝3。
		for (w = 0; w < BitInfoHeader.biWidth; w++)
		{
			//计算出指针的偏移量，指针从最后住前偏移。
			//地址为偶地址方式，所以采用了下面的偶地址对齐方式。
			//一行的宽度＝像素宽度＊色彩数＊32/4
			FOffset = Size - h * linebytes - w * 3;
			fseek(Fp, 0 - FOffset, SEEK_END);

			//读出一行的数据。
			fread((void  *)data, 3, 1, Fp);

			rgb.b = data[0];
			rgb.g = data[1];
			rgb.r = data[2];
			color = MapColor(pdc->scrdev, &rgb);
			
			PutPixel(hdc, x + w, 
					 y + BitInfoHeader.biHeight - h - 1, color);
		}
	}
	
	fclose(Fp);
	return 0;   
}


// 只能显示在同一段内的图像数据
INT8 Put24Bitmap (HDC hdc, INT32 x, INT32 y, INT16 mode, UCHAR  * bitmap)
{
	INT32  line_bytes;
	INT32  size = 0;			  //累加数据指针的长度
	BITMAPFILEHEADER BitHeader;			 //BMP文件结构的头
	BITMAPINFOHEADER BitInfoHeader;		 //BMP位图信息头

	INT16	   w, h;					 //行循环计数变量

	GAL_COLOR		rgb;
	GAL_PIXEL		color;
	PDC			  pdc;
	UINT8			err;
	UCHAR  * bits, *data;

	mode = mode;//暂时用不上
	memcpy(&BitHeader, bitmap, sizeof(BITMAPFILEHEADER));
	// 判断文件的合法性。
	if(BitHeader.bfType != 'M' * 256 + 'B')
	{
		errprintf("This Is Not A Bmp File.\n");
		return -1;
	}
	bits = bitmap + BitHeader.bfOffBits; // 保存图象数据的开始地址

	// 打开BMP位图信息头
	memcpy(&BitInfoHeader, bitmap + sizeof(BITMAPFILEHEADER), sizeof(BITMAPINFOHEADER));

	// 24位色限定(只能识别真彩24位)
	if (BitInfoHeader.biBitCount != 24) 
   {
		errprintf("This Programme Only For 24bit Colors Bitmap.\n");
		return -1;
	}

	// 压缩限定（识别无压缩格式）
	if (BitInfoHeader.biCompress != 0) 
	{
		errprintf("This Programme Only For no rar Bitmap.\n");
		return -1;
	}

	//图片大小限定最大1280*800
	if (BitInfoHeader.biWidth > 1280 || BitInfoHeader.biHeight > 800) 
	{
		errprintf("Bitmap is too big.\n");
		return -1;
	}

	//算出图片的每行数据的字节数
	line_bytes = (((BitInfoHeader.biWidth * BitInfoHeader.biBitCount + 31) >> 5 ) << 2);
	size = BitInfoHeader.biHeight * line_bytes;

	pdc = dc_HDC2PDC(hdc);
	coor_LP2SP(pdc, &x, &y);

	PMAINWIN pWin = (PMAINWIN)(pdc->hwnd);
	int fb_level = 0;
	if (pWin != NULL)
		fb_level = pWin->fblayer;

	fb_putmem(fb_level, x, y, BitInfoHeader.biWidth, BitInfoHeader.biHeight, bits, line_bytes, 1);
	return 0;   
}


// 只能显示在同一段内的图像数据
INT8 Put24BitmapEx (HDC hdc, INT32 x, INT32 y, INT16 mode, UCHAR  * bitmap)
{
	INT32  line_bytes;
	INT32  size = 0;			  //累加数据指针的长度
	BITMAPFILEHEADER BitHeader;			 //BMP文件结构的头
	BITMAPINFOHEADER BitInfoHeader;		 //BMP位图信息头
	INT16	   w, h;					 //行循环计数变量
	GAL_COLOR		rgb;
	GAL_PIXEL		color;
	PDC			  pdc;
	UINT8			err;
	UCHAR  * bits, *data;

	mode = mode;//暂时用不上
	memcpy(&BitHeader, bitmap, sizeof(BITMAPFILEHEADER));

	// 判断文件的合法性。
	if(BitHeader.bfType != 'M' * 256 + 'B')
	{
		errprintf("This Is Not A Bmp File.\n");
		return -1;
	}

	bits = bitmap + BitHeader.bfOffBits; // 保存图象数据的开始地址
	
	// 打开BMP位图信息头
	memcpy(&BitInfoHeader, bitmap + sizeof(BITMAPFILEHEADER), sizeof(BITMAPINFOHEADER));
	
	// 24位色限定(只能识别真彩24位)
	if (BitInfoHeader.biBitCount != 24) 
   {
		errprintf("This Programme Only For 24bit Colors Bitmap.\n");
		return -1;
	}
	
	// 压缩限定（识别无压缩格式）
	if (BitInfoHeader.biCompress != 0) 
	{
		errprintf("This Programme Only For no rar Bitmap.\n");
		return -1;
	}

	//图片大小限定最大1024*768
	if (BitInfoHeader.biWidth > 1024 || BitInfoHeader.biHeight > 768) 
	{
		errprintf("Bitmap is too big.\n");
		return -1;
	}
	
	//算出图片的每行数据的字节数
	line_bytes = (((BitInfoHeader.biWidth * BitInfoHeader.biBitCount + 31) >> 5 ) << 2);
	size = BitInfoHeader.biHeight * line_bytes;
	
	pdc = dc_HDC2PDC(hdc);
	coor_LP2SP(pdc, &x, &y);

	PMAINWIN pWin = (PMAINWIN)(pdc->hwnd);
	int fb_level = 0;
	if (pWin != NULL)
		fb_level = pWin->fblayer;

	fb_putmem_ex(fb_level, x, y, BitInfoHeader.biWidth, BitInfoHeader.biHeight, bits, line_bytes, 1);

	return 0;   
}

unsigned char * Get24BitmapInfo(UCHAR  * bitmap, INT16 * line_bytes)
{

	BITMAPFILEHEADER BitHeader;			 //BMP文件结构的头
	BITMAPINFOHEADER BitInfoHeader;		 //BMP位图信息头

	 INT16	   w, h;					 //行循环计数变量

	GAL_COLOR		rgb;
	GAL_PIXEL		color;
	PDC			  pdc;
	UINT8			err;
	UCHAR  * bits, *data;


	memcpy(&BitHeader, bitmap, sizeof(BITMAPFILEHEADER));

	// 判断文件的合法性。
	if(BitHeader.bfType != 'M' * 256 + 'B')
	{
		errprintf("This Is Not A Bmp File.\n");
		return NULL;
	}

	bits = bitmap + BitHeader.bfOffBits; // 保存图象数据的开始地址
	
	// 打开BMP位图信息头
	memcpy(&BitInfoHeader, bitmap + sizeof(BITMAPFILEHEADER), sizeof(BITMAPINFOHEADER));
	
	// 24位色限定(只能识别真彩24位)
	if (BitInfoHeader.biBitCount != 24) 
   {
		errprintf("This Programme Only For 24bit Colors Bitmap.\n");
		return NULL;
	}
	
	// 压缩限定（识别无压缩格式）
	if (BitInfoHeader.biCompress != 0) 
	{
		errprintf("This Programme Only For no rar Bitmap.\n");
		return NULL;
	}

	//图片大小限定最大1024*768
	if (BitInfoHeader.biWidth > 1024 || BitInfoHeader.biHeight > 768) 
	{
		errprintf("Bitmap is too big.\n");
		return NULL;
	}
	//算出图片的每行数据的字节数
	*line_bytes = (((BitInfoHeader.biWidth * BitInfoHeader.biBitCount + 31) >> 5 ) << 2);

	return bits;
}


