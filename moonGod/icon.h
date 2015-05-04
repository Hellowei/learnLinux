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
#if !defined(_ICON_H)
#define	  _ICON_H


#define  DISABLED_ALARM_BELL_FILE  "bell.bmp"
#define  HEART_FILE				"heart.bmp"
#define  PAUSE_FILE				"pause.bmp"
#define  SILENCE_FILE			  "silence.bmp"

typedef enum _icon_id
{
	IDI_NONE = -1,
	IDI_DISABLED_ALARM_BELL = 0,
	IDI_ENABLED_ALARM_BELL,
	IDI_PAUSE,	
	IDI_ENABLED_SPEAKER,
	IDI_DISABLED_SPEAKER,
	IDI_SOUNDOFF,
	IDI_HEART,
	IDI_ALARMBELL,
	IDI_EVE1,
	IDI_EVE2,
	IDI_EVE3,
	IDI_EVE4,
	IDI_NS,
	IDI_ND,
	IDI_NM,
	IDI_UPARROW,
	IDI_FROZE_UPARROW,
	IDI_DOWNARROW,
	IDI_LEFTARROW,
	IDI_RIGHTARROW,
	IDI_TRD_LEFTARROW,
	IDI_TRD_UPARROW,
	IDI_YELLOWBELL,
	IDI_REDBELL,

	IDI_FIRST_MONOBYTE_FORM,  //数据格式为单字节的icon;在以前的都是2个字节的数距.
	IDI_BATT_NONE = IDI_FIRST_MONOBYTE_FORM,
	IDI_BATT_FULL,
	IDI_BATT_0LEV,
	IDI_BATT_1LEV,
	IDI_BATT_2LEV,
	IDI_BATT_3LEV,
	IDI_PAGE_UP,
	IDI_PAGE_DN,
	IDI_EXIT,
	IDI_FHR_GPH,
	IDI_TOCO_GPH,
	IDI_COMPANY_MARK,
	IDI_MAX
} ICONID;

//位头文件头,共占用14个字节。
//位图文件头包含文件类型、文件大小、存放位置等信息。
typedef struct  {
	short bfType;				//表明位图文件的类型，该值必需是0x4D42('BM')
	long  bfSize;				//表明位图文件的大小，以字节为单位
	short bfReserved1;		   //属于保留字，必须为本0
	short bfReserved2;		   //也是保留字，必须为本0
	long bfOffBits;			 //表明从文件头开始到实际的图象数据之间的字节的偏移量
	//因为位图信息头和调色板的长度会根据不同情况而变化，
	//所以你可以用这个偏移值迅速的从文件中读取到位数据以字节为单位
}__attribute__ ((packed, aligned(2))) BITMAPFILEHEADER;


//位头信息由位头信息头和彩色表组成

//位头信息头，共占用40个字节。
//位图信息头包含位图的大小、压缩类型、和颜色格式
struct __tagBITMAPINFOHEADER {
	long  biSize;			   //指出本数据结构所需要的字节数
	long  biWidth;			  //以象素为单位，给出BMP图象的宽度
	long  biHeight;			 //以象素为单位，给出BMP图象的高度
	//同时也说明该图像是倒向还是正向的位图。如果该值是一个正数，说明图像是倒向的
	//如果该值是一个负数，则说明图像是正向的。(大多数的BMP文件都是倒向的位图)
	//当高度值是一个负数时（正向图像），图像将不能被压缩（也就是说biCompression成员将不能是BI_RLE8或BI_RLE4）
	short biPlanes;			 //输出设备的位平面数，必须置为1
	short biBitCount;		   //给出每个象素的位数，单色为1,256色为8,24位色为24
	long  biCompress;		   //给出位图的压缩类型
	//0:表示无压缩（BI_RGB)
	//1:表示８位RLE压缩（BI_RLE8）每个象素8比特的RLE压缩编码，压缩格式由2字节组成(重复象素计数和颜色索引)； 
	//2:表示４位RLE压缩（BI_RLE4）每个象素4比特的RLE压缩编码，压缩格式由2字节组成 
	//3:表示Bitfields-位域存放方式(BI_BITFIELDS)每个象素的比特由指定的掩码决定
	long  biSizeImage;		  //给出图象字节数的多少，无压缩为0
	long  biXPelsPerMeter;	  //图像的水平分辨率
	long  biYPelsPerMeter;	  //图象的垂直分辨率
	long  biClrUsed;			//調色板中图象实际使用的颜色素数
	long  biClrImportant;	   //给出重要颜色的索引值
} __attribute__((packed));

typedef struct __tagBITMAPINFOHEADER BITMAPINFOHEADER;

typedef struct __bmp_file_head{
	short bfType;				//表明位图文件的类型，该值必需是0x4D42('BM')
	long  bfSize;				//表明位图文件的大小，以字节为单位
	short bfReserved1;		   //属于保留字，必须为本0
	short bfReserved2;		   //也是保留字，必须为本0
	long bfOffBits;			 //表明从文件头开始到实际的图象数据之间的字节的偏移量
	//因为位图信息头和调色板的长度会根据不同情况而变化，
	//所以你可以用这个偏移值迅速的从文件中读取到位数据以字节为单位
	long  biSize;			   //指出本数据结构所需要的字节数
	long  biWidth;			  //以象素为单位，给出BMP图象的宽度
	long  biHeight;			 //以象素为单位，给出BMP图象的高度
	//同时也说明该图像是倒向还是正向的位图。如果该值是一个正数，说明图像是倒向的
	//如果该值是一个负数，则说明图像是正向的。(大多数的BMP文件都是倒向的位图)
	//当高度值是一个负数时（正向图像），图像将不能被压缩（也就是说biCompression成员将不能是BI_RLE8或BI_RLE4）
	short biPlanes;			 //输出设备的位平面数，必须置为1
	short biBitCount;		   //给出每个象素的位数，单色为1,256色为8,24位色为24
	long  biCompress;		   //给出位图的压缩类型
	//0:表示无压缩（BI_RGB)
	//1:表示８位RLE压缩（BI_RLE8）每个象素8比特的RLE压缩编码，压缩格式由2字节组成(重复象素计数和颜色索引)； 
	//2:表示４位RLE压缩（BI_RLE4）每个象素4比特的RLE压缩编码，压缩格式由2字节组成 
	//3:表示Bitfields-位域存放方式(BI_BITFIELDS)每个象素的比特由指定的掩码决定
	long  biSizeImage;		  //给出图象字节数的多少，无压缩为0
	long  biXPelsPerMeter;	  //图像的水平分辨率
	long  biYPelsPerMeter;	  //图象的垂直分辨率
	long  biClrUsed;			//調色板中图象实际使用的颜色素数
	long  biClrImportant;	   //给出重要颜色的索引值
}__attribute__ ((packed, aligned(2)))BMPFILEHEAD, *PBMPFILEHEAD;

//位图彩色表，点用4的倍的字字。
//彩色表包含的元素与位图所具有的颜色数目相同，
//像素颜色用结构RGBQUAD来表示
struct  __tagRGBQUAD {
	unsigned char   rgbBlue;		//兰色的强度
	unsigned char   rgbGreen;	   //绿色的强度
	unsigned char   rgbRed;		 //红色的强度
	unsigned char   rgbReserved;	//保留，设为0
} __attribute__((packed));

typedef  struct  __tagRGBQUAD RGBQUAD;
#if 0
struct _bitmap_memory{
	short		   bits;   //图像每像素位数
	short		   free;   //是否需要释放内存
	long			cx;	 //图像的水平分辨率
	long			cy;	 //图象的垂直分辨率
	unsigned char   *data;  //图像显存
}__attribute__((packed));

typedef  struct  _bitmap_memory BITMAPMEM;
typedef  struct  _bitmap_memory *PBITMAPMEM;
#endif

#if STANDBY // Change by Latrom_11-11-2011
extern unsigned char standby[];
extern unsigned char standby_en[];
extern unsigned char standby_ru[];
extern unsigned char standby_es[];
extern unsigned char standby_tr[];
#endif

extern unsigned char *pageup_24bmp[2];
extern unsigned char *pagedn_24bmp[2];
extern unsigned char *record_24bmp[2];
extern unsigned char *syscfg_24bmp[2];
extern unsigned char *face_24bmp[2];
extern unsigned char *ac_icon[2];
extern unsigned char *batt_icon[2][4];
extern unsigned char *net_icon[2];
extern unsigned char *nonet_icon[2];
extern unsigned char *ulnet_icon[2];
extern unsigned char *pNetIcon;
extern unsigned char *print_icon[2];
extern unsigned char *noprint_icon[2];
extern unsigned char *vol_icon[2][4];
extern unsigned char *full_icon[2];
extern unsigned char *alm_icon[2];
extern unsigned char *DisableAlarm_icon[2];

unsigned char *graph_background;
unsigned char *bigfn_background;

BOOL  InitIcon(VOID);
VOID  DrawIcon(HDC hdc, INT32 x, INT32 y, ICONID icon_id);
VOID  DrawAlmBell(UINT16 parent,UINT16 ctrl, BOOL clear_flag);
BITMAP GetSystemIcon(ICONID icon);
BOOL  BmpCopy(UCHAR *dest, UCHAR *src);
UCHAR *ChangeBatteryBmpEx(INT8 percent);
#endif

