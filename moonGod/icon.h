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

	IDI_FIRST_MONOBYTE_FORM,  //���ݸ�ʽΪ���ֽڵ�icon;����ǰ�Ķ���2���ֽڵ�����.
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

//λͷ�ļ�ͷ,��ռ��14���ֽڡ�
//λͼ�ļ�ͷ�����ļ����͡��ļ���С�����λ�õ���Ϣ��
typedef struct  {
	short bfType;				//����λͼ�ļ������ͣ���ֵ������0x4D42('BM')
	long  bfSize;				//����λͼ�ļ��Ĵ�С�����ֽ�Ϊ��λ
	short bfReserved1;		   //���ڱ����֣�����Ϊ��0
	short bfReserved2;		   //Ҳ�Ǳ����֣�����Ϊ��0
	long bfOffBits;			 //�������ļ�ͷ��ʼ��ʵ�ʵ�ͼ������֮����ֽڵ�ƫ����
	//��Ϊλͼ��Ϣͷ�͵�ɫ��ĳ��Ȼ���ݲ�ͬ������仯��
	//��������������ƫ��ֵѸ�ٵĴ��ļ��ж�ȡ��λ�������ֽ�Ϊ��λ
}__attribute__ ((packed, aligned(2))) BITMAPFILEHEADER;


//λͷ��Ϣ��λͷ��Ϣͷ�Ͳ�ɫ�����

//λͷ��Ϣͷ����ռ��40���ֽڡ�
//λͼ��Ϣͷ����λͼ�Ĵ�С��ѹ�����͡�����ɫ��ʽ
struct __tagBITMAPINFOHEADER {
	long  biSize;			   //ָ�������ݽṹ����Ҫ���ֽ���
	long  biWidth;			  //������Ϊ��λ������BMPͼ��Ŀ��
	long  biHeight;			 //������Ϊ��λ������BMPͼ��ĸ߶�
	//ͬʱҲ˵����ͼ���ǵ����������λͼ�������ֵ��һ��������˵��ͼ���ǵ����
	//�����ֵ��һ����������˵��ͼ��������ġ�(�������BMP�ļ����ǵ����λͼ)
	//���߶�ֵ��һ������ʱ������ͼ�񣩣�ͼ�񽫲��ܱ�ѹ����Ҳ����˵biCompression��Ա��������BI_RLE8��BI_RLE4��
	short biPlanes;			 //����豸��λƽ������������Ϊ1
	short biBitCount;		   //����ÿ�����ص�λ������ɫΪ1,256ɫΪ8,24λɫΪ24
	long  biCompress;		   //����λͼ��ѹ������
	//0:��ʾ��ѹ����BI_RGB)
	//1:��ʾ��λRLEѹ����BI_RLE8��ÿ������8���ص�RLEѹ�����룬ѹ����ʽ��2�ֽ����(�ظ����ؼ�������ɫ����)�� 
	//2:��ʾ��λRLEѹ����BI_RLE4��ÿ������4���ص�RLEѹ�����룬ѹ����ʽ��2�ֽ���� 
	//3:��ʾBitfields-λ���ŷ�ʽ(BI_BITFIELDS)ÿ�����صı�����ָ�����������
	long  biSizeImage;		  //����ͼ���ֽ����Ķ��٣���ѹ��Ϊ0
	long  biXPelsPerMeter;	  //ͼ���ˮƽ�ֱ���
	long  biYPelsPerMeter;	  //ͼ��Ĵ�ֱ�ֱ���
	long  biClrUsed;			//�{ɫ����ͼ��ʵ��ʹ�õ���ɫ����
	long  biClrImportant;	   //������Ҫ��ɫ������ֵ
} __attribute__((packed));

typedef struct __tagBITMAPINFOHEADER BITMAPINFOHEADER;

typedef struct __bmp_file_head{
	short bfType;				//����λͼ�ļ������ͣ���ֵ������0x4D42('BM')
	long  bfSize;				//����λͼ�ļ��Ĵ�С�����ֽ�Ϊ��λ
	short bfReserved1;		   //���ڱ����֣�����Ϊ��0
	short bfReserved2;		   //Ҳ�Ǳ����֣�����Ϊ��0
	long bfOffBits;			 //�������ļ�ͷ��ʼ��ʵ�ʵ�ͼ������֮����ֽڵ�ƫ����
	//��Ϊλͼ��Ϣͷ�͵�ɫ��ĳ��Ȼ���ݲ�ͬ������仯��
	//��������������ƫ��ֵѸ�ٵĴ��ļ��ж�ȡ��λ�������ֽ�Ϊ��λ
	long  biSize;			   //ָ�������ݽṹ����Ҫ���ֽ���
	long  biWidth;			  //������Ϊ��λ������BMPͼ��Ŀ��
	long  biHeight;			 //������Ϊ��λ������BMPͼ��ĸ߶�
	//ͬʱҲ˵����ͼ���ǵ����������λͼ�������ֵ��һ��������˵��ͼ���ǵ����
	//�����ֵ��һ����������˵��ͼ��������ġ�(�������BMP�ļ����ǵ����λͼ)
	//���߶�ֵ��һ������ʱ������ͼ�񣩣�ͼ�񽫲��ܱ�ѹ����Ҳ����˵biCompression��Ա��������BI_RLE8��BI_RLE4��
	short biPlanes;			 //����豸��λƽ������������Ϊ1
	short biBitCount;		   //����ÿ�����ص�λ������ɫΪ1,256ɫΪ8,24λɫΪ24
	long  biCompress;		   //����λͼ��ѹ������
	//0:��ʾ��ѹ����BI_RGB)
	//1:��ʾ��λRLEѹ����BI_RLE8��ÿ������8���ص�RLEѹ�����룬ѹ����ʽ��2�ֽ����(�ظ����ؼ�������ɫ����)�� 
	//2:��ʾ��λRLEѹ����BI_RLE4��ÿ������4���ص�RLEѹ�����룬ѹ����ʽ��2�ֽ���� 
	//3:��ʾBitfields-λ���ŷ�ʽ(BI_BITFIELDS)ÿ�����صı�����ָ�����������
	long  biSizeImage;		  //����ͼ���ֽ����Ķ��٣���ѹ��Ϊ0
	long  biXPelsPerMeter;	  //ͼ���ˮƽ�ֱ���
	long  biYPelsPerMeter;	  //ͼ��Ĵ�ֱ�ֱ���
	long  biClrUsed;			//�{ɫ����ͼ��ʵ��ʹ�õ���ɫ����
	long  biClrImportant;	   //������Ҫ��ɫ������ֵ
}__attribute__ ((packed, aligned(2)))BMPFILEHEAD, *PBMPFILEHEAD;

//λͼ��ɫ������4�ı������֡�
//��ɫ�������Ԫ����λͼ�����е���ɫ��Ŀ��ͬ��
//������ɫ�ýṹRGBQUAD����ʾ
struct  __tagRGBQUAD {
	unsigned char   rgbBlue;		//��ɫ��ǿ��
	unsigned char   rgbGreen;	   //��ɫ��ǿ��
	unsigned char   rgbRed;		 //��ɫ��ǿ��
	unsigned char   rgbReserved;	//��������Ϊ0
} __attribute__((packed));

typedef  struct  __tagRGBQUAD RGBQUAD;
#if 0
struct _bitmap_memory{
	short		   bits;   //ͼ��ÿ����λ��
	short		   free;   //�Ƿ���Ҫ�ͷ��ڴ�
	long			cx;	 //ͼ���ˮƽ�ֱ���
	long			cy;	 //ͼ��Ĵ�ֱ�ֱ���
	unsigned char   *data;  //ͼ���Դ�
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

