
#define FHR_GLOBALS
#include "includes.h"


#define BRUSH_WIDTH     8

static UINT8  Fhr_DemoData[] =
#if 0
{
0x8b,0x88,0x8a,0x8c,0x8f,0x8e,0x8c,0x8a,0x88,0x8b,0x8c,0x8d,0x8f,0x91,0x92,0x94,
0x96,0x97,0x99,0x98,0x96,0x95,0x97,0x99,0x9a,0x9b,0x9c,0x9d,0x9e,0x9f,0x9c,0x99,
0x96,0x93,0x90,0x8c,0x8a,0x88,0x87,0x89,0x86,0x84,0x83,0x85,0x89,0x8b,0x88,0x8a,
0x8c,0x8f,0x8e,0x8c,0x8a,0x88,0x8b,0x8c,0x8d,0x8f,0x91,0x92,0x94,0x96,0x97,0x99,
0x98,0x96,0x95,0x97,0x99,0x9a,0x9b,0x9c,0x9d,0x9e,0x9f,0x9f,0x9d,0x9e,0x9d,0x9c,
0x9b,0x9a,0x9b,0x9a,0x98,0x95,0x96,0x94,0x92,0x90,0x8e,0x8c,0x8a,0x88,0x8b,0x8c,
0x8d,0x8f,0x91,0x93,0x95,0x95,0x97,0x95,0x97,0x94,0x96,0x95,0x97,0x95,0x95,0x94,
0x98,0x95,0x93,0x97,0x95,0x96,0x95,0x95,0x99,0x9a,0x9b,0x99,0x9a,0x9c,0x9e,0x9f,
0xa0,0x9e,0x9d,0x9b,0x9a,0x9b,0x98,0x96,0x93,0x91,0x92,0x92,0x91,0x91,0x92,0x90,
0x8f,0x92,0x94,0x91,0x8f,0x91,0x89,0x86,0x84,0x87,0x89,0x8b,0x8c,0x8d,0x8e,0x8c
};
#else
{
0x88,0x89,0x88,0x88,0x87,0x88,0x89,0x87,0x86,0x86,0x87,0x88,0x89,0x88,0x89,0x87,
0x88,0x89,0x88,0x88,0x87,0x88,0x89,0x87,0x86,0x86,0x87,0x88,0x89,0x88,0x89,0x87,
0x88,0x89,0x88,0x88,0x87,0x88,0x89,0x87,0x86,0x86,0x87,0x88,0x89,0x88,0x89,0x87,
0x86,0x87,0x86,0x87,0x88,0x89,0x87,0x88,0x89,0x87,0x86,0x86,0x87,0x89,0x8d,0x93,
0x92,0x95,0x97,0x99,0x9a,0x9b,0x9e,0x9f,0xa0,0xa2,0xa1,0xa0,0x9e,0x9c,0x9d,0x9b,
0x99,0x97,0x98,0x96,0x93,0x91,0x8e,0x8f,0x8d,0x8b,0x89,0x8a,0x88,0x87,0x86,0x87,
0x88,0x89,0x88,0x88,0x87,0x88,0x89,0x87,0x86,0x86,0x87,0x88,0x89,0x88,0x89,0x87,
0x88,0x89,0x88,0x88,0x87,0x88,0x89,0x87,0x86,0x86,0x87,0x88,0x89,0x88,0x89,0x87,
0x89,0x8a,0x8b,0x8e,0x8d,0x8b,0x8c,0x8a,0x8a,0x87,0x86,0x87,0x88,0x89,0x87,0x88
};
#endif

static UINT8  Toco_DemoData[] =
{
0x0a,0x10,0x13,0x14,0x17,0x1a,0x1a,0x1e,0x21,0x22,0x25,0x28,0x2d,0x2c,0x2f,0x31,
0x36,0x39,0x3a,0x3d,0x3c,0x41,0x42,0x44,0x45,0x47,0x45,0x4a,0x4a,0x4b,0x4d,0x4e,
0x4f,0x50,0x50,0x4f,0x4f,0x51,0x52,0x53,0x53,0x50,0x4f,0x50,0x4f,0x52,0x52,0x4e,
0x4f,0x4e,0x4e,0x4c,0x4c,0x4b,0x49,0x46,0x42,0x40,0x42,0x40,0x3e,0x3b,0x3b,0x38,
0x36,0x30,0x31,0x2f,0x29,0x28,0x27,0x23,0x23,0x20,0x1e,0x19,0x16,0x14,0x12,0x0e,
0x0d,0x0e,0x0a,0x0c,0x0d,0x0b,0x0a,0x0d,0x0b,0x0b,0x0c,0x0e,0x0c,0x0a,0x0d,0x0b,
0x0c,0x0b,0x0a,0x0d,0x0e,0x0c,0x0e,0x0b,0x0b,0x0d,0x0c,0x0b,0x0b,0x0e,0x0c,0x0b,
0x0c,0x0e,0x0a,0x0c,0x0a,0x0a,0x0d,0x0e,0x0b,0x0d,0x0b,0x0e,0x0a,0x0d,0x0c,0x0a,
0x0c,0x0a,0x0d,0x0b,0x0c,0x0c,0x0c,0x0c,0x0e,0x0e,0x0b,0x0e,0x0b,0x0e,0x0d,0x0c,
0x0a,0x0a,0x0e,0x0e,0x0b,0x0c,0x0a,0x0a,0x0d,0x0d,0x0e,0x0d,0x0e,0x0b,0x0c,0x0e
};

static UINT8 Afm_DemoData[] = {
    11,10,11,12,12,12,10,11,11,11,11,12,12,12,11,10,
    11,12,11,11,12,10,22,31,20,11,12,10,12,10,12,10,
    11,11,10,11,10,11,12,11,12,11,11,12,10,11,12,12,
    10,11,10,10,12,10,12,10,12,12,11,12,10,11,10,11,
    10,11,10,10,12,12,10,12,11,12,12,11,10,10,10,12,
    11,12,12,11,12,11,10,12,11,12,12,12,11,10,11,12,
    11,12,10,12,11,11,24,36,23,12,12,12,12,11,11,11,
    10,12,11,10,11,12,10,10,11,12,12,10,10,10,12,12,
    10,11,12,10,12,11,11,11,11,10,11,10,12,10,10,10,
    10,11,10,12,10,12,12,11,11,12,10,12,10,10,12,11
};

const UINT8*  Fhr_DemoHead    = Fhr_DemoData;
const UINT8*  Fhr_DemoTail    = Fhr_DemoData + sizeof(Fhr_DemoData) - 1;
const UINT8*  Fhr_DemoReadP   = Fhr_DemoData;

const UINT8*  Toco_DemoHead    = Toco_DemoData;
const UINT8*  Toco_DemoTail    = Toco_DemoData + sizeof(Toco_DemoData) - 1;
const UINT8*  Toco_DemoReadP   = Toco_DemoData;

const UINT8*  Afm_DemoHead    = Afm_DemoData;
const UINT8*  Afm_DemoTail    = Afm_DemoData + sizeof(Afm_DemoData) - 1;
const UINT8*  Afm_DemoReadP   = Afm_DemoData;

const UINT8 FiveSecondPoint[3] = {3, 6, 9};// 每五秒应该在屏幕上画几个点,对应速度
static UINT8 sStepDots[3][5 * 20];//收包速度为FETAL_SAMPL_RATE在第几个数据包时画点
static UINT8 sStepData[5 * 20];
static UINT32 FetalWavePageOffset[FETAL_WAVE_PAGE_MAX];
    
static INT16 DrawPos[18 * 60 * FETAL_SAMPLE_RATE + 1];

static BITMAPMEM FhrBitmapMemory   = {0, 0, 0L, 0L, NULL};
static BITMAPMEM TocoBitmapMemory  = {0, 0, 0L, 0L, NULL};

typedef struct _fetal_graph_color
{
    UCHAR brfhr;
    UCHAR bkfhr;
    UCHAR dwfhr;
    UCHAR brtoco;
    UCHAR bktoco;
    UCHAR dwtoco;
}FTL_GPH_CLR;

static const FTL_GPH_CLR sGphClr[3] = {
    //夜间模式颜色
    { WEC_EXCOLOR_BLACK3, WEC_EXCOLOR_BLACK,   WEC_EXCOLOR_BLACK2, 
      WEC_EXCOLOR_BLACK3, WEC_EXCOLOR_BLACK,   WEC_EXCOLOR_BLACK2  },
    //标准颜色配置
    { WEC_EXCOLOR_DARKOLIVEGREEN, WEC_EXCOLOR_BLACK1, WEC_EXCOLOR_NAVY, 
      WEC_EXCOLOR_NAVY, WEC_EXCOLOR_BLACK1, WEC_EXCOLOR_NAVY },
      
    { WEC_EXCOLOR_BLACK1, WEC_EXCOLOR_BLACK,   WEC_EXCOLOR_BLACK2, 
      WEC_EXCOLOR_BLACK3, WEC_EXCOLOR_BLACK,   WEC_EXCOLOR_BLACK2    },
};

STRINGID EventStrID[16] = {
    STR_NULL,
    STR_DLG_DRM_A,
    STR_DLG_DRM_B,
    STR_DLG_DRM_C,
    STR_DLG_DRM_D,
    STR_DLG_DRM_E,
    STR_DLG_DRM_F,
    STR_DLG_DRM_G,
    STR_DLG_DRM_H,
    STR_DLG_DRM_I,
    STR_DLG_DRM_J,
    STR_DLG_DRM_K,
    STR_DLG_DRM_L,
    STR_DLG_DRM_M,
    STR_DLG_DRM_N,
    STR_DLG_DRM_O
};
STRINGID AnalyStrID[12] = {
    STR_NULL,   //    STR_DLG_FHR_DIAG_ACC_NORMAL,
    STR_NULL,   //    STR_DLG_FHR_DIAG_ACC_LITTLE,
    STR_NULL,   //    STR_DLG_FHR_DIAG_ACC_FASTIGIA,
    STR_NULL,   //    STR_DLG_FHR_DIAG_REDUCE_SLOW,
    STR_NULL,   //    STR_DLG_FHR_DIAG_REDUCE_LITTLE,
    STR_NULL,   //    STR_DLG_FHR_DIAG_REDUCE_SLOW_TAIL,
    STR_NULL,   //    STR_DLG_FHR_DIAG_REDUCE_VARY_SLOW,
    STR_NULL,   //    STR_DLG_FHR_DIAG_REDUCE_HEAVY_VARY,
    STR_NULL,   //    STR_DLG_FHR_DIAG_REDUCE_LIGHT_VARY,
    STR_NULL,   //    STR_DLG_FHR_DIAG_REDUCE_EARLY,
    STR_NULL,   //    STR_DLG_FHR_DIAG_REDUCE_EXTEND,
    STR_NULL    //    STR_DLG_FHR_DIAG_REDUCE_EARLY_VARY,	
};

static char sDemoPacket[12] = 
    {0x55, 0x02, 0x83, 0x07, 0x00, 0x00, 0x00, 0x00, 0x8F, 0x80, 0x00, 0x03};
char *FetalIndemoPacket()
{
    if (MonitorInfo.inDemo) 
    {
        static UINT8 count = 0;
        sDemoPacket[5] = 10 + *Fhr_DemoReadP;
        sDemoPacket[6] = *Fhr_DemoReadP;
        sDemoPacket[7] = *Toco_DemoReadP;
        if ((++ count % 4) == 0)
        {
            count = 0;
            Fhr_DemoReadP ++;
            if (Fhr_DemoReadP > Fhr_DemoTail)
                Fhr_DemoReadP = Fhr_DemoHead;

            Toco_DemoReadP ++;
            if (Toco_DemoReadP > Toco_DemoTail)
                Toco_DemoReadP = Toco_DemoHead;
        }
    }
    return sDemoPacket;
}


FETALWAVEDATA *GetFetalDataPtr(FETALWAVEDATA *ptr, INT32 move)
{
    FETALWAVEDATA *tmpPtr;
    INT32       movPtr  = move;
    if (ABS(movPtr) >= MAX_FETAL_DATA_LEN)
        movPtr %= MAX_FETAL_DATA_LEN;

    tmpPtr = ptr + movPtr;
    if(tmpPtr > FetalWaveBuffTailPtr)
    {
        tmpPtr -= MAX_FETAL_DATA_LEN;
    }
    else if (tmpPtr < FetalWaveBuffHeadPtr)
    {
        tmpPtr += MAX_FETAL_DATA_LEN;
    }
    return tmpPtr;
}

static INT16 GetWavePos(INT32 height, INT16 value, INT16 max, INT16 min)
{
    if (value < min)
    {
        return -1;
    }
    else if (value > max)
    {
        return -1;
    }
	else if (value == max )
	{
		return 1;
	}
    else
    {
        return (INT16)(height - ((value - min) * height) / (max - min));
    }
}

static BOOL InitFetalModule(VOID)
{
    return InitFhrModule();
}



VOID ReInitFhrGphMem(UCHAR type)
{
    BITMAP  bmp;
    RECT    rc;
    INT32   x, y, w, h;
    PFBMEM  this = &FbMem;
    if (type >= TABLESIZE(sGphClr))
        return;
    if ((type == 0) && (MonitorConfig.MonitorName == MONITOR_TYPE_AR2))
        type = 2;  /* 针对Artemis2的屏幕不能很好区分WEC_EXCOLOR_BLACK3
        和WEC_EXCOLOR_BLACK2,将原填充颜色改为WEC_EXCOLOR_BLACK1 */
 
    bmp = GetSystemIcon(IDI_FHR_GPH);
    SetRect(&rc, 0, 0, bmp.width, bmp.height);
    this->SetMenory(this, &FhrBitmapMemory);
    this->SetBrushColor(this, GetWindowElementColor(sGphClr[type].bkfhr));
    this->FillRect(this, &rc);
    x = 0;
    y = bmp.height * (240 - 160) / (240 - 30);
    w = bmp.width;
    h = bmp.height * 40 / (240 - 30);
    SetRect(&rc, x, y, x+w, y+h);
    this->SetBrushColor(this, GetWindowElementColor(sGphClr[type].brfhr));
    this->FillRect(this, &rc);
    this->SetForeColor(this, GetWindowElementColor(sGphClr[type].dwfhr));
    this->SetBackColor(this, PIXEL_transparent);
    this->PutIcon(this, bmp.bits, 0, 0, bmp.width, bmp.height);

    bmp = GetSystemIcon(IDI_TOCO_GPH);
    this->SetMenory(this, &TocoBitmapMemory);
    SetRect(&rc, 0, 0, bmp.width, bmp.height);
    this->SetBrushColor(this, GetWindowElementColor(sGphClr[type].bktoco));
    this->FillRect(this, &rc);
    this->SetForeColor(this, GetWindowElementColor(sGphClr[type].dwtoco));
    this->SetBackColor(this, PIXEL_transparent);
    this->PutIcon(this, bmp.bits, 0, 0, bmp.width, bmp.height);
}

static VOID InitFhrGraphMem(VOID)
{
    BITMAP  bmp;
    PFBMEM  this = &FbMem;
    
    this->SetFont(this, GetSystemFont(SYSLOGFONT_YAHEI17_FONT));

    bmp = GetSystemIcon(IDI_FHR_GPH);
    this->SetMenory(this, &FhrBitmapMemory);
    this->New(this, bmp.width, bmp.height, 16);
    
    bmp = GetSystemIcon(IDI_TOCO_GPH);
    this->SetMenory(this, &TocoBitmapMemory);
    this->New(this, bmp.width, bmp.height, 16);
    
    ReInitFhrGphMem(!MonitorConfig.nightModeOn);
}

VOID InitFetal(VOID)
{
    if (InitFetalModule())
    {
        FhrConfig.enbFhr1   = TRUE;
        FhrConfig.enbFhr2   = TRUE;
        FhrConfig.enbToco   = TRUE;
        FhrConfig.enbAfm    = TRUE;
    }
    FetalWavePrint = (FHRWAVE *) malloc (sizeof(FHRWAVE));
    if (FetalWavePrint != NULL)
    {
        ZeroMemory(FetalWavePrint, sizeof(FHRWAVE));
    }
    else
    {
        prinfo("malloc error!\r\n");
        exit(0);
    }
    extern BITMAPMEM FhrBitmapMemory;
    extern BITMAPMEM TocoBitmapMemory;
    int i, j, k;
    PFHRWAVE this   = FetalWavePrint;
    this->fhr_back  = &FhrBitmapMemory;
    this->toco_back = &TocoBitmapMemory;
    this->pHead     = FetalWaveBuffHeadPtr;
    this->pTail     = FetalWaveBuffTailPtr;
    this->pPage     = FetalWaveBuffWritePtr;
    this->pCurr     = FetalWaveBuffWritePtr;
    this->xPos      = 0;
    
    for (i = 0; i < WAVE_MAX; i++)
    {
        for (j = 0; j < WAVE_WIDTH; j++)
        {
            this->yPos[i][j] = -1;
        }
    }
    for (i = 0; i < MAX_FETAL_DATA_LEN; i++)
    {
        (this->pCurr + i)->toco = -1;
    }
    // 为了减少刷波形时的计算量,先建立映射表
    ZeroMemory(sStepDots, sizeof(sStepDots));
    int loops;
    for (i = 0; i < TABLESIZE(sStepDots); i++)
    {
        loops = sizeof(sStepDots[i]);
        k = 0;
        for (j = 0; j < loops; j++)
        {
            if (j == loops * k / FiveSecondPoint[i])
            {
                sStepDots[i][j] = 1;
                if (++k == FiveSecondPoint[i])
                    break;
            }
        }
    }
    loops = sizeof(sStepData);
    k = 0;
    for (i = 0; i < loops; i++)
    {
		if (i == loops * k / (5 * FETAL_SAMPLE_RATE))
        {
            k++;
        }
        sStepData[i] = k;
    }
    for (i = 0; i < FETAL_WAVE_PAGE_MAX; i++)
    {
		FetalWavePageOffset[i] = FETAL_PAGE_TIME * 60 * FETAL_SAMPLE_RATE * i;
    }
    InitFhrGraphMem();
    SetFetalDetach(FhrConfig.detach);
    for (i = 0; i < WAVE_WIDTH; i++)
    {
        this->marks[i].event = 0xFF;
    }
}


static VOID FetalGraphDrawScrollBar(PFHRWAVE this)
{
    this->scrdata.maxnum = this->PgCnt;
    this->scrdata.minnum = 0;
    this->scrdata.value = this->scrdata.maxnum - this->PgNdx;
    SetScrollBarValue(IDM_MAIN,
        IDC_MAIN_GRAPH_SCROLL_BAR_SC, this->scrdata.value);
    return;
}


// 当前生理参数是否有超出报警限的报警
static UINT8 ParaIsAlarm(UINT16 STRHI, UINT16 STRLO)
{
    if(AlmGlbCtlr.AlmPause == FALSE)
    {
        if (((*(PhsAlmInfo[STRHI-STR_ALM_PHS_FIRST + 1].Effect) == TRUE)
            && (PhsAlmInfo[STRHI-STR_ALM_PHS_FIRST + 1].Exist == TRUE)
            && (PhsAlmInfo[STRHI-STR_ALM_PHS_FIRST + 1].Trg == TRUE))
            || ((*(PhsAlmInfo[STRLO-STR_ALM_PHS_FIRST + 1].Effect) == TRUE)
            && (PhsAlmInfo[STRLO-STR_ALM_PHS_FIRST + 1].Exist == TRUE)
            && (PhsAlmInfo[STRLO-STR_ALM_PHS_FIRST + 1].Trg == TRUE)))
        {
            return TRUE;
        }
        else
        {
            return FALSE;
        }
    } 
    else 
    {
        return FALSE;
    }
}

extern int get_curr_time(void);
VOID SaveFhrRealData(VOID)
{
    static FETALDATA data = {0};
    static UINT8 waveindex = 0;
    static UINT8 second = 0;
    static INT8 valid = -10;
    static INT8 flag = FALSE;
    FETALWAVEDATA *pParam = FetalWaveBuffWritePtr;
	if (waveindex++ >= FETAL_SAMPLE_RATE)
		waveindex = FETAL_SAMPLE_RATE - 1;
    if (second != DateTime.second)
    {
        second = DateTime.second;
        waveindex = 0;
        data.fm = FhrParams.fm;
        data.time = get_curr_time();
//        if (data.event)
//            prinfo("second...%d, event...%d\r\n", second, data.event);
        FmsPtr->PutData(FmsPtr, &data);

        ZeroMemory(&data, sizeof(data));
        if (FmsPtr->GetCurrSaveIndex(FmsPtr) < 0)
        {
            MonitorInfo.PatientTime = 0;
        }
        else
        {
            if (MonitorInfo.PatientTime < DATA_SAVE_LEN)
                MonitorInfo.PatientTime++;
            else
                MonitorInfo.PatientTime = DATA_SAVE_LEN;
        }
    }
    UINT8 i = waveindex;// 填充一秒的数据,防止一秒内接收到的数据不足
	for (i; i < FETAL_SAMPLE_RATE; i++)
    {
        data.wave[i].fhr1 = pParam->fhr1; 
        data.wave[i].fhr2 = pParam->fhr2; 
        data.wave[i].toco = pParam->toco; 
        data.wave[i].afm  = pParam->afm;
        data.wave[i].fhr1Eff = pParam->fhr1Eff; 
        data.wave[i].fhr2Eff = pParam->fhr2Eff; 
        data.wave[i].tocoEff = pParam->tocoEff; 
        if (FhrConfig.mode != 1)
            data.wave[i].fhr1Alm = pParam->fhr1Alm =
                ParaIsAlarm(STR_ALM_FHR1_TOO_HI, STR_ALM_FHR1_TOO_LO); 
        if (FhrConfig.mode > 0)
            data.wave[i].fhr2Alm = pParam->fhr2Alm =
                ParaIsAlarm(STR_ALM_FHR2_TOO_HI, STR_ALM_FHR2_TOO_LO);
    }


    if (pParam->event < 16 && pParam->event > 0)
    {
        data.event = pParam->event;
    }
    if (pParam->zerobits)
        data.wave[waveindex].zerobits = pParam->zerobits;
    if (pParam->fmbits)
        data.wave[waveindex].fmbits = pParam->fmbits;
    if (pParam->afmbits)
    {
        data.wave[waveindex].afmbits = pParam->afmbits;
    }
    return;
}
//2015-05-14@VinYin 修复胎心率曲线掉点问题，原因从缓冲池读数据的速度快于写数据，
//导致写数据下标呈跳跃式递增，从而缓冲池存在垃圾数据，解决方式,缓冲池跳跃部分用插值替换垃圾数据
static INT16 sg_curSavePosX = 0;//把串口数据写到缓冲池时的下标
static VOID SetWavePos(PFHRWAVE this, INT16 xpos, FETALWAVEDATA *ptr)
{
    INT16 fhr1, fhr2, toco, afm;
    fhr1 = (INT16)ptr->fhr1;
    fhr2 = (INT16)ptr->fhr2;
    toco = (INT16)ptr->toco;
    afm  = (INT16)ptr->afm;
    xpos = ABS(xpos) % WAVE_WIDTH;
    sg_curSavePosX = xpos;//更新写进缓冲池的下标进度
    this->yPos[WAVE_FHR_CH1][xpos] =
        GetWavePos(this->fhr_back->cy - 1,  fhr1, 240,  30);

    this->yPos[WAVE_FHR_CH2][xpos] =
        GetWavePos(this->fhr_back->cy - 1 ,  fhr2, 240,  30);

    this->yPos[WAVE_TOCO][xpos]    =
        GetWavePos(this->toco_back->cy - 2, toco, 100,   0);
	
    this->yPos[WAVE_AFM][xpos]     = 
        GetWavePos(this->toco_back->cy * 4 / 10, ptr->afm,   40,   0);

    //打点标志间隔作限制,丢掉过于频繁的点
   	static INT16 zeroPosX = 0;
    static INT16 fmbitsPosX = 0;
    static INT16 afmbitsPosX = 0;
    static INT16 eventPosX = 0;
    if (ABS(xpos)%((INT16)WAVE_WIDTH) > (WAVE_WIDTH - 2))//走完一圈,重设
    {
    	zeroPosX = 0;
      	fmbitsPosX = 0;
     	afmbitsPosX = 0;
     	eventPosX = 0;
    }
    ZeroMemory(&(this->marks[(xpos + 1) % WAVE_WIDTH]), sizeof(MARKEVENT));
    this->marks[xpos].zerobits  |= ptr->zerobits;
    if((ABS(xpos-zeroPosX) > 16 || (xpos == zeroPosX)) && this->marks[xpos].zerobits)
    	zeroPosX = xpos;
    else
    	this->marks[xpos].zerobits = 0;
    	
    this->marks[xpos].fmbits    |= ptr->fmbits;
    if((ABS(xpos-fmbitsPosX) > 8 || (xpos == fmbitsPosX)) && this->marks[xpos].fmbits)
    	fmbitsPosX = xpos;
    else
    	this->marks[xpos].fmbits = 0;
    	
    this->marks[xpos].afmbits   |= ptr->afmbits;
    if((ABS(xpos-afmbitsPosX) > 8 || (xpos == fmbitsPosX)) && this->marks[xpos].afmbits)
    	afmbitsPosX = xpos;
    else
    	this->marks[xpos].afmbits = 0;
    	
    if (ptr->event > 0 && ptr->event < 16)
    {	
        this->marks[xpos].eventbits = 1;
        this->marks[xpos].event = ptr->event;
    }
    if((ABS(xpos-eventPosX) > 16 || (xpos == eventPosX)) && this->marks[xpos].eventbits)
    	eventPosX = xpos;
    else
    	this->marks[xpos].eventbits = 0;
}

static VOID UpdateWavePos(PFHRWAVE this, int start, FETALWAVEDATA *pData)
{
    FETALWAVEDATA *pWavePtr = pData;
    int i, j, idata;
    MARKEVENT marks = {0};
    i = start;
    while (i < WAVE_WIDTH)
    {
        idata = -1;
        for (j = 0; j < sizeof(sStepData); j++)
        {
            if (pWavePtr == this->pCurr)
            {
                this->xPos = (WAVE_WIDTH + i - 2) % WAVE_WIDTH;
                i = WAVE_WIDTH;
                break;
            }
            if (idata != sStepData[j])
            {
                idata = sStepData[j];
                pWavePtr = GetFetalDataPtr(pWavePtr, 1);
                if (pWavePtr->event > 0 && pWavePtr->event < 16)
                {
                    marks.eventbits = 1;
                    marks.event = pWavePtr->event;
                }
                if (pWavePtr->zerobits)
                {
                    marks.zerobits = 1;
                }
                if (pWavePtr->fmbits)
                {
                    marks.fmbits = 1;
                }
                if (pWavePtr->afmbits)
                    marks.afmbits = 1;
            }
            if (sStepDots[FhrConfig.sweep][j])
            {
                this->marks[i] = marks;
                ZeroMemory(&marks,sizeof(marks));
                SetWavePos(this, i++, pWavePtr);
                if (i == WAVE_WIDTH)
                {
                    break;
                }
            }
        }
    }
}

VOID UpdateFetalWavePos(PFHRWAVE this,BOOL refresh)
{
    FETALWAVEDATA *pWavePtr;
    if (this == NULL)
    {
        this = FetalWavePrint;
    }
    if (refresh == TRUE)
    {
        INT32 offset, remainder;
        INT16 i, j;
        this->drawFlag = FALSE;
        offset = -FetalWavePageOffset[this->PgNdx];
        pWavePtr = this->pPage;
        if (this->PgNdx == 0)//当前实时刷新重绘,需要前页数据,并重定xPos
        {
            this->xPos = 0;
            UpdateWavePos(this, 0, pWavePtr);

            if (this->xPos < WAVE_WIDTH - BRUSH_WIDTH)
            {
				remainder = (WAVE_WIDTH - this->xPos - 2) * FETAL_SAMPLE_RATE * 5
                            / FiveSecondPoint[FhrConfig.sweep];
                pWavePtr = this->pPage;
                pWavePtr = GetFetalDataPtr(pWavePtr, - remainder);
                UpdateWavePos(this, this->xPos + BRUSH_WIDTH, pWavePtr);
            }
            this->drawFlag = TRUE;
        }
        else
        {
            pWavePtr = GetFetalDataPtr(pWavePtr, offset);
            UpdateWavePos(this, 0, pWavePtr);
        }
    }
    else
    {
        INT16 wpos;
        pWavePtr = this->pCurr;
        wpos = this->xPos+1;
        if (wpos >= WAVE_WIDTH)
        {
            wpos = 0;
        }
        SetWavePos(this, wpos, pWavePtr);
    }
    return;
}

VOID MoveFetalDataPtr(UINT32 move)
{
    FetalWaveBuffWritePtr = (FETALWAVEDATA*)
        PTR_ADD(FetalWaveBuffWritePtr, move * sizeof(FETALWAVEDATA));

    if(PTR_CPR(FetalWaveBuffTailPtr, FetalWaveBuffWritePtr))
    {
        FetalWaveBuffWritePtr = (FETALWAVEDATA*)(PTR2FLAT(FetalWaveBuffWritePtr)
                                        - PTR2FLAT(FetalWaveBuffTailPtr)
                                        + PTR2FLAT(FetalWaveBuffHeadPtr)
                                        - sizeof(FETALWAVEDATA));
    }
}

VOID FhrInitParams(VOID)
{
	ZeroMemory(&FhrParams, sizeof(FhrParams));
	PutFhrValue(&FhrParams);
}

static char FetalSampleInSecond = 0;
VOID  FhrDataCorrection (VOID)
{
	while (FetalSampleInSecond < FETAL_SAMPLE_RATE) {
		PutFhrValue(&FhrParams);
		PutFhrValue(&FhrParams);
		FetalSampleInSecond++;
	}
	FetalSampleInSecond = 0;
	TriggerAlarm(IsCommStoped(MID_FHR), STR_ALM_FETAL_COMM_STOP);
}

VOID PutFetalWave(VOID)
{

}

VOID PutFhrValue(FHR_PARAMS * params)
{ 
    UINT8 fhr1Eff, fhr2Eff, tocoEff, afmEff;
    INT16 fhr1, fhr2;
    INT16 toco, fm, afm;

    if (MonitorInfo.inDemo) 
    {
        params->fm   = 19;
    }
    fhr1 = params->fhr1;
    fhr2 = params->fhr2;
    toco = params->toco;
    fm   = params->fm;
    afm  = params->afm;
    fhr1Eff = CheckRangeExceed(PARAM_LMTS_FHR,  &fhr1);
    fhr2Eff = CheckRangeExceed(PARAM_LMTS_FHR,  &fhr2);
    tocoEff = CheckRangeExceed(PARAM_LMTS_TOCO, &toco);
    afmEff  = CheckRangeExceed(PARAM_LMTS_AFM,  &afm);

    FhrParams.fhr1 = fhr1;

    FhrParams.fhr2 = fhr2;

    FhrParams.toco = toco;

    FhrParams.afm  = afm;
    CheckRangeExceed(PARAM_LMTS_FM, &fm);
    FhrParams.fm  = fm;
    PFHRWAVE this			= FetalWavePrint;
    this->pCurr				= FetalWaveBuffWritePtr;
    this->pCurr->fhr1Eff	= (fhr1Eff == 0) & 0x01;
    this->pCurr->fhr2Eff	= (fhr2Eff == 0) & 0x01;
    this->pCurr->tocoEff	= (tocoEff == 0) & 0x01;
    this->pCurr->fhr1		= (fhr1 < 0) ? 0 : LOBYTE(fhr1);
    this->pCurr->fhr2		= (fhr2 < 0) ? 0 : LOBYTE(fhr2);
    this->pCurr->toco		= (char)toco;
    this->pCurr->afm		= (char)afm;
    this->pCurr->fmbits		= (FhrParams.mark & 0x01);
    this->pCurr->afmbits	= ((FhrParams.mark & 0x08) > 0) & 0x01;
    this->pCurr->zerobits	= ((FhrParams.mark & 0x02) > 0) & 0x01;
    
	FetalSampleInSecond++;
    if (this->drawFlag)
    {
        UpdateFetalWavePos(this, FALSE);
    }
    
    if ((this->pCurr - this->pHead) % FetalWavePageOffset[1] == 0)
    {
        if (this->PgCnt < FETAL_WAVE_PAGE_MAX)
        {
            this->PgCnt++;
        }
        this->pPage     = this->pCurr;
        this->currTime  = DateTime;
        FetalGraphDrawScrollBar(FetalWavePrint);
    }
#if _ENB_NET_THREAD
	#if _ENB_NET_SEND_ALARM_INFO < 1
	PostMessage(SysUdpT_HTSK, MSG_NET_UDP_SEND, sizeof(FETALWAVEDATA),(LPARAM)this->pCurr);
	PostMessage(SysTcpT_HTSK, MSG_NET_TCP_SEND, sizeof(FETALWAVEDATA),(LPARAM)this->pCurr);
	#endif
#endif
    SaveFhrRealData();
    MoveFetalDataPtr(1);
}

static VOID FetalModuleAlarm(SENSORINDEX id, STRINGID strid)
{
	if (0 > SensorStatus[id].recoveredSeconds)
	{
		SensorStatus[id].recoveredSeconds ++;
	}
	else
	{
		SensorStatus[id].recoveredSeconds = 0;
	}
	if (SensorStatus[id].recoveredSeconds < 0)
	{
		TriggerAlarm(PROMPT_ONLY | TRUE, strid);
	}
	else
	{
		TriggerAlarm(TRUE, strid);
	}
}

VOID PutFhrStatusByte(UINT8 status1,UINT8 status2)
{
    static UINT8 LastStat1, LastStat2;
    if (((status1 & 0x03) < 2 && FhrParams.fhr1 > 29) && (FhrConfig.mode != 1))
    {
        if ((LastStat1 & 0x03) != (status1 & 0x03))
        {
            TriggerAlarm(TRUE, STR_ALM_FHR1_LOW_SIGNAL);
        }
    }
    else
    {
        TriggerAlarm(FALSE, STR_ALM_FHR1_LOW_SIGNAL);
    }

    if (((status1 & 0x0C) >> 2) < 2 && (FhrParams.fhr2 > 29) && (FhrConfig.mode != 0))
    {
        if ((LastStat1 & 0x0C) != (status1 & 0x0C))
        {
            TriggerAlarm(TRUE, STR_ALM_FHR2_LOW_SIGNAL);
        }
    }
    else
    {
        TriggerAlarm(FALSE, STR_ALM_FHR2_LOW_SIGNAL);
    }

    if ((status2 & 0x01) != (LastStat2 & 0x01))
    {
		if (status2 & 0x01)
	        TriggerAlarm(FALSE, STR_ALM_FHR1_SENSOR_OFF);
		else
			FetalModuleAlarm(SENSOR_FHR_CH1, STR_ALM_FHR1_SENSOR_OFF);
    }
    if ((status2 & 0x08) != (LastStat2 & 0x08))
    {
		if (status2 & 0x08)
	        TriggerAlarm(FALSE, STR_ALM_FHR2_SENSOR_OFF);
		else
			FetalModuleAlarm(SENSOR_FHR_CH2, STR_ALM_FHR2_SENSOR_OFF);
    }
    if ((status2 & 0x02) != (LastStat2 & 0x02))
    {
		if (status2 & 0x02)
			TriggerAlarm(FALSE, STR_ALM_TOCO_SENSOR_OFF);
		else
			FetalModuleAlarm(SENSOR_TOCO, STR_ALM_TOCO_SENSOR_OFF);
    }
    if ((status2 & 0x04) != (LastStat2 & 0x04))
    {
		if (status2 & 0x04)
			TriggerAlarm(FALSE, STR_ALM_FM_SENSOR_OFF);
		else
		{
			FetalModuleAlarm(SENSOR_FM, STR_ALM_FM_SENSOR_OFF);
		}
    }
    LastStat1 = status1;
    LastStat2 = status2;
}

VOID ShowFetalGraph(VOID)
{
    PBITMAPMEM  pMem;
    INT32       w;
    INT32       h;
    RECT        rc;
    HWND        hCtrl;
    HDC         hdc;
    PDC         pdc;
    
    if (MonitorConfig.faceType != FACE_STD && MonitorConfig.faceType != FACE_STD_SINGLE) return;
    pMem = &FhrBitmapMemory;
    hCtrl = GetDlgItem(MainScnHWnd, IDC_MAIN_GRAPH_FHR_L);
    GetClientRect(hCtrl, &rc);
    w = pMem->cx;
    h = pMem->cy;
    SetRect(&rc, rc.left, rc.top, rc.left + w, rc.top + h);
    hdc = GetDC(hCtrl);
    FillRectEx(hdc, &rc, w, pMem->data);
    pdc = dc_HDC2PDC(hdc);
    ReleaseDC(hdc);
    
    pMem = &TocoBitmapMemory;
    hCtrl = GetDlgItem(MainScnHWnd, IDC_MAIN_GRAPH_TOCO_L);
    GetClientRect(hCtrl, &rc);
    w = pMem->cx;
    h = pMem->cy;
    SetRect(&rc, rc.left, rc.top, rc.left + w, rc.top + h);
    hdc = GetDC(hCtrl);
    FillRectEx(hdc, &rc, w, pMem->data);
    pdc = dc_HDC2PDC(hdc);
    ReleaseDC(hdc);
}

VOID SetFetalDetach(BOOL detach)
{
    if (MonitorConfig.faceType == FACE_STD 
        || MonitorConfig.faceType == FACE_STD_SINGLE)
    {
        ReInitFhrGphMem(!MonitorConfig.nightModeOn);
        if ((!detach) || (FhrConfig.mode < 2))
        {
            return;
        }
        PFBMEM  this = &FbMem;
        SIZE size;
        UCHAR *text = NULL;
        INT32 x, y;
        this->SetForeColor(this, GetWindowElementColor(WEC_EXCOLOR_ORANGE));
        this->SetMenory(this, &FhrBitmapMemory);
        text = LoadString(STR_DLG_FHR_DETACH_SPLINE);
        this->SetFont(this, GetSystemFont(SYSLOGFONT_SMAFONT));
        GetTextExtentEx(this->pLogfont, text, -1, &size);
        x = DLG_OFFSET;
        y = FhrBitmapMemory.cy / 2;
        this->TextOut(this, x, y, text);
    }
}

VOID SetFetalMonitorDemoStyle(BOOL isDemo)
{
    if (MonitorConfig.faceType == FACE_STD 
        || MonitorConfig.faceType == FACE_STD_SINGLE)
    {
        ReInitFhrGphMem(!MonitorConfig.nightModeOn);
        if (!isDemo)
        {
            ReDrawFetalWave(FetalWavePrint);
            return;
        }
        PFBMEM  this = &FbMem;
        SIZE size;
        UCHAR *text;
        INT32 x, y;
        this->SetForeColor(this, GetWindowElementColor(WEC_EXCOLOR_ORANGE));
        this->SetMenory(this, &FhrBitmapMemory);
        text = LoadString(STR_DLG_SETUP_DEMO);
        this->SetFont(this, GetSystemFont(SYSLOGFONT_BIGFONT));

        GetTextExtentEx(this->pLogfont, text, -1, &size);
        x = DLG_OFFSET;
        y = DLG_OFFSET;
        this->TextOut(this, x, y, text);
        x = this->mem->cx - size.cx - DLG_OFFSET;
        this->TextOut(this, x, y, text);
        y = this->mem->cy - size.cy - DLG_OFFSET;
        this->TextOut(this, x, y, text);
        x = DLG_OFFSET;
        this->TextOut(this, x, y, text);
        ReDrawFetalWave(FetalWavePrint);
    }
    else
    {
        int i;
        HWND hCtrl;
        for (i = IDC_DESKTOP_DEMO1_L; i <= IDC_DESKTOP_DEMO4_L; i++)
        {
            if (hCtrl = GetDlgItem(MainScnHWnd, i))
            {
                SetWindowText(hCtrl, isDemo ? STR_DLG_SETUP_DEMO : STR_NULL);
            }
        }
    }
}

static INT32 EraseWave(HDC hdc, INT32 xPos, PBITMAPMEM  pMem)
{
    INT32 x;
    if (pMem == NULL) return -1;

    if (xPos < pMem->cx - 1)
    {
        RECT rc;
        x = xPos + 0;
        if (x >= pMem->cx)
            x -= pMem->cx;
        SetRect(&rc, x, 0, x + 1, pMem->cy);
        FillRectEx(hdc, &rc, pMem->cx, pMem->data);
    }
    return x;
}

VOID BrushWave(HDC hdc, PBITMAPMEM  pMem, INT32 xPos, INT32 width, BOOL is3D)
{
    PDC     pdc;
    INT32   xEnd;
    INT32   xMax;
    INT32   top;
    INT32   bottom;
    INT32   x;
    pdc = dc_HDC2PDC(hdc);
    if (!pMem) return;
    xMax    = pMem->cx - 1;
    top     = 0;
    bottom  = pMem->cy;
    if (xPos >= xMax)
        xPos = -1;
    x = EraseWave(hdc, xPos, pMem) + 1;
    if (width > 2)//使用刷新线,由于会跳到开头，不能直接使用FillRect
    {
        GAL_PIXEL   brushcolor = GetBrushColor(hdc);
        INT32       i;
        INT32       loops;
        loops = width - 1;
        if (is3D == TRUE)
        {
            GAL_PIXEL tmpColor;
            GAL_PIXEL penColor;
            GAL_COLOR color;
            UCHAR   r, g, b;
            UnmapPixel(pdc->scrdev, brushcolor, &color);
            penColor = GetPenColor(hdc);
            for (i = 0; i < loops; i++)
            {
                if (++x >= xMax)
                    x = 0;
                r = (UCHAR)(color.r * i / loops);
                g = (UCHAR)(color.g * i / loops);
                b = (UCHAR)(color.b * i / loops);
                tmpColor = fb_color(r, g, b);
                SetPenColor(hdc, tmpColor);
                Line(hdc, x, top, x, bottom);
            }
            SetPenColor(hdc, penColor);
            
        }
        else
        {
            brushcolor = SetPenColor(hdc, brushcolor);
            for (i = 0; i < loops; i++)
            {
                if (++x >= xMax)
                    x = 0;
                Line(hdc, x, top, x, bottom);
            }
            SetPenColor(hdc, brushcolor);
        }
    }
}


UINT16 GetFetalPos (VOID)
{
    return 1;
}

VOID DateCalc(DATETIME *ptime, INT32 dayOffset)
{
    INT32 day = dayOffset;
    if (day > 0)
    {
        while (ABS(day) > 366)
        {
            day -= 365; 
            if (IsLeapYear(ptime->year) && ptime->month < 3)
                day --;
            ptime->year++;
        }
    }
    else if (day < 0)
    {
        while (ABS(day) > 366)
        {
            day += 365; 
            if (IsLeapYear(ptime->year+1) && ptime->month > 2)
                day ++;
            ptime->year--;
        }
    }
    
    if (day > 0)
    {
        while (day > DaysInThisMonth(ptime->year, ptime->month))
        {
            day -= DaysInThisMonth(ptime->year, ptime->month);
            ptime->month++;
            if (ptime->month > 12)
            {
                ptime->month = 1;
                ptime->year++;
            }
        }
    }
    else if (day < 0)
    {
        while(day < 0)
        {
            ptime->month--;
            if (ptime->month < 1)
            {
                ptime->month = 12;
                ptime->year--;
            }
            day += DaysInThisMonth(ptime->year, ptime->month);
        }
    }
    
    if (day == 0)
    {
        ptime->month--;
        ptime->day = DaysInThisMonth(ptime->year, ptime->month);
        return;
    }
}

VOID TimeCalc(DATETIME * ptime, INT32 offset, CHAR type)
{
    INT32 hour, minute, second;
    INT32 day;
    hour = ptime->hour;
    minute = ptime->minute;
    second = ptime->second;
    day = ptime->day;
    if (ABS(offset) > 0x0FFFFFFF)
        return;
    
    switch(type)
    {
        case 'h':
        case 'H':
            hour += offset;
            break;

        case 'm':
        case 'M':
            minute += offset;
            break;

        case 's':
        case 'S':
        default:
            second += offset;
            break;
    }
    if (ABS(second) > 59)
    {
        minute += second / 60;
        second %= 60;
    }
    if (second < 0)
    {
        second += 60;
        minute -= 1;
    }
    if (ABS(minute) > 59)
    {
        hour += minute / 60;
        minute %= 60;
    }
    if (minute < 0)
    {
        minute += 60;
        hour -= 1;
    }
    // 关于日期的计算没有用到，在hour处停止
    if (ABS(hour) > 23)
    {
        hour %= 24;
        day += hour / 24;
    }
    if (hour < 0)
    {
        hour += 24;
        day -= 1;
    }
    ptime->hour   = hour;
    ptime->minute = minute;
    ptime->second = second;
    DateCalc(ptime, day);
}

static VOID DrawBackground(PFHRWAVE this)
{
    RECT rc;
    HDC hdc;
    hdc = GetDC(this->hFhrGph);
    SetRect(&rc, 0, 0, this->fhr_back->cx, this->fhr_back->cy);
    FillRectEx(hdc, &rc, this->fhr_back->cx, this->fhr_back->data);
    ReleaseDC(hdc);
    
    hdc = GetDC(this->hTocoGph);
    SetRect(&rc, 0, 0, this->toco_back->cx, this->toco_back->cy);
    FillRectEx(hdc, &rc, this->toco_back->cx, this->toco_back->data);
    ReleaseDC(hdc);
    
}

static VOID ShowFetalTimeGraph(PFHRWAVE this)
{
    HWND hWnd = GetDlgItem(MainScnHWnd, IDC_MAIN_GRAPH_TIME_L);
    if (hWnd)
    {
        HDC hdc;
        PDC pdc;
        CHAR szTime[12];
        DATETIME time;
        SetWindowText(hWnd, STR_NULL);
        time = this->currTime;
        TimeCalc(&time, -1 *this->PgNdx * FETAL_PAGE_TIME, 'm');
        sprintf(szTime, "%02d:%02d:%02d", time.hour, time.minute, time.second);
        hdc = GetDC(hWnd);
        pdc = dc_HDC2PDC(hdc);
		if (MONITOR_TYPE_AR2 == MonitorConfig.MonitorName)
			TextOut(hdc, 0, 0, szTime);
		else
			TextOut(hdc, 0, (STATIC_HEIGHT - GetFontHeight(hdc)) / 2, szTime);
		
        ReleaseDC(hdc);
    }
}

static VOID PutFetalMark(HDC hdc, INT32 x, INT32 y, INT32 style, INT32 data)
{
	SetBkColor(hdc, PIXEL_transparent);
    if (SS_SIMPLE == style)
    {
        UCHAR *pStr = (UCHAR*)data;
		if (CHINESE == MonitorConfig.language)
		{
	        RECT rc;
	        SetRect(&rc, x, y, x + 18, y + 99);
	        TextOutWrap(hdc, &rc, pStr, -1);
		}
		else
		{
			TextOutEx(hdc, x, y, pStr, 1);
		}
    }
    if (SS_ICON == style)
    {
        DrawIcon(hdc, x, y, data);
    }
}

static VOID PrintMark(HDC hdc, PFHRWAVE this, UINT16 dLen, CHAR type)
{
    INT32 drPos;
    GAL_PIXEL drColor;
    GAL_PIXEL drColor2;
    INT32 style;
    ICONID icon_id;
    INT32 i, count;
    UCHAR *pStr;
    PDC pdc = dc_HDC2PDC(hdc);
    INT32 offset = (pdc->pLogFont->size + 1) / 2;
    INT32 ndx;
    switch (type)
    {
        case FETAL_MARK_ANALY:
            drPos = 150;
            drColor = PIXEL_white;// (MonitorConfig.nightModeOn) ? PIXEL_white : PIXEL_black;
            style = SS_SIMPLE;
            drColor = SetTextColor(hdc, drColor);
            for (i = this->xPos; i < dLen + this->xPos; i++)
            {
                ndx = i % WAVE_WIDTH;
                if(this->marks[ndx].analybits)
                {
                    if(this->marks[ndx].analy)
                    {
                        pStr = LoadString(AnalyStrID[this->marks[ndx].analy]);
                        PutFetalMark(hdc, ndx, drPos, style, (INT32)pStr);
                    }
                }
            }
            SetTextColor(hdc, drColor);
            break;

        case FETAL_MARK_EVENT:
            if (this->xPos < 12)
                return;
            drPos = 2;
            drColor  = PIXEL_white;// (MonitorConfig.nightModeOn) ? PIXEL_white : PIXEL_black;
            drColor2 = (MonitorConfig.nightModeOn) ? PIXEL_black : PIXEL_white;
            style = SS_SIMPLE;
            drColor = SetTextColor(hdc, drColor);
            drColor2 = SetBkColor(hdc, drColor2);
            for (i = this->xPos; i < dLen + this->xPos; i++)
            {
                ndx = i % WAVE_WIDTH;
                if((this->marks[ndx].eventbits) && (this->marks[ndx].event))
                {
                    if (this->marks[ndx].event < TABLESIZE(EventStrID))
                    {
                        pStr = LoadString(EventStrID[this->marks[ndx].event]);
                        PutFetalMark(hdc, ndx - 12, drPos, style, (INT32)pStr);
                    }
                }
            }
            SetBkColor(hdc, drColor2);
            SetTextColor(hdc, drColor);
            break;

        case FETAL_MARK_ZERO:
            if (this->xPos < 8)
                return;
            drPos = 108;
            drColor  = (MonitorConfig.nightModeOn) ? PIXEL_white : PIXEL_black;
            drColor2 = (MonitorConfig.nightModeOn) ? PIXEL_black : PIXEL_white;
            style = SS_ICON;
            icon_id = IDI_NM;
            drColor = SetPenColor(hdc, drColor);
            offset = (GetSystemIcon(icon_id).width + 1) / 2;
            for (i = this->xPos; i < dLen + this->xPos; i++)
            {
                ndx = i % WAVE_WIDTH;
				if (ndx < 16) ndx = WAVE_WIDTH;
                if(this->marks[ndx].zerobits)
                {
                    if (ndx < WAVE_WIDTH)
                    {
                        PutFetalMark(hdc, ndx - 16, drPos, style, icon_id);
                    }
                }
            }
            SetBkColor(hdc, drColor);
            SetBrushColor(hdc, drColor2);
            break;

        case FETAL_MARK_FM:
            if (this->xPos < 8)
                return;
            drPos = 2;
            drColor2 = PIXEL_white;//(MonitorConfig.nightModeOn) ? PIXEL_white : PIXEL_black;
            drColor  = (MonitorConfig.nightModeOn) ? PIXEL_black : PIXEL_white;
            style = SS_ICON;
            icon_id = IDI_UPARROW;
            drColor = SetBkColor(hdc, drColor);
            drColor = SetBrushColor(hdc, drColor2);
            offset = (GetSystemIcon(icon_id).width + 1) / 2;
            for (i = this->xPos; i < dLen + this->xPos; i++)
            {
                ndx = i % WAVE_WIDTH;
				if (ndx < 8) ndx = WAVE_WIDTH - 8;
                if(this->marks[ndx].fmbits)
                {
                    PutFetalMark(hdc, ndx - 8, drPos, style, icon_id);
                }
                if(this->marks[ndx].afmbits)
                {
                    PutFetalMark(hdc, ndx - 8, drPos + 48, style, icon_id);
                }
            }
            SetBkColor(hdc, drColor);
            SetBrushColor(hdc, drColor2);
            break;

        default:
            return;
    }
}

static VOID PrintFhrWave(HDC hdc, PFHRWAVE this, UINT16 dLen)
{
    INT16     i;
    INT16     thispos;
    INT16     lastpos;
    INT16     thisNdx;
    INT16     lastNdx;
    GAL_PIXEL color;
    if (dLen == 0)
    {
        dLen = WAVE_WIDTH - 2;
    }
    if (FhrConfig.mode != 1)
    {
        // fhr1 wave
        color = GetWindowElementColor(MonitorConfig.colorParam[PARA_BLOCK_FHR1]);
        SetPenColor(hdc, color);
        for (i = 0; i < dLen; i++)
        {
            if (dLen == WAVE_WIDTH - 2)
            {
                thisNdx = this->xPos + i + 3;
                lastNdx = this->xPos + i + 2;
                if (lastNdx >= WAVE_WIDTH)
                {
                    lastNdx -= WAVE_WIDTH;
                }
                if (thisNdx >= WAVE_WIDTH)
                {
                    thisNdx -= WAVE_WIDTH;
                }
            }
            else
            {
                thisNdx = this->xPos - i;
                lastNdx = this->xPos - i - 1;
                if (lastNdx < 0)
                {
                    lastNdx += WAVE_WIDTH;
                }
                if (thisNdx < 0)
                {
                    thisNdx += WAVE_WIDTH;
                }
                if (sg_curSavePosX < thisNdx)
            		this->yPos[WAVE_FHR_CH1][thisNdx] = this->yPos[WAVE_FHR_CH1][sg_curSavePosX];
            }
            thispos = this->yPos[WAVE_FHR_CH1][thisNdx];
            lastpos = this->yPos[WAVE_FHR_CH1][lastNdx];
            if (thispos > 0 &&  thisNdx > lastNdx)
            {
         
                if (lastpos > 0 && ABS(thispos - lastpos) < FHR_MAX_OFFSET)
                {
                    DrawLine(hdc, lastNdx, lastpos, thisNdx, thispos);
                }
                else
                {
                    DrawLine(hdc, thisNdx, thispos-1, thisNdx, thispos);
                }
            }
        
        }
    }
    if (FhrConfig.mode > 0)
    {
        // fhr2 wave
        color = GetWindowElementColor(MonitorConfig.colorParam[PARA_BLOCK_FHR2]);
        SetPenColor(hdc, color);
        for (i = 0; i < dLen; i++)
        {
            if (dLen == WAVE_WIDTH - 2)
            {
                thisNdx = this->xPos + i + 3;
                lastNdx = this->xPos + i + 2;
                if (lastNdx >= WAVE_WIDTH)
                {
                    lastNdx -= WAVE_WIDTH;
                }
                if (thisNdx >= WAVE_WIDTH)
                {
                    thisNdx -= WAVE_WIDTH;
                }
            }
            else
            {
                thisNdx = this->xPos - i;
                lastNdx = this->xPos - i - 1;
                if (lastNdx < 0)
                {
                    lastNdx += WAVE_WIDTH;
                }
                if (thisNdx < 0)
                {
                    thisNdx += WAVE_WIDTH;
                }
                if (sg_curSavePosX < thisNdx)
            		this->yPos[WAVE_FHR_CH2][thisNdx] = this->yPos[WAVE_FHR_CH2][sg_curSavePosX];
            }
          
           const INT16 deltaY = (FhrConfig.detach)?(23):(0);//实际23才对应屏幕20,有误差
           thispos = this->yPos[WAVE_FHR_CH2][thisNdx] + deltaY;
           lastpos = this->yPos[WAVE_FHR_CH2][lastNdx] + deltaY;
		   if (thispos > deltaY &&  thisNdx > lastNdx)
            {
                if (lastpos > deltaY && ABS(thispos - lastpos) < FHR_MAX_OFFSET)
                {
                    DrawLine(hdc, lastNdx, lastpos, thisNdx, thispos);
                }
                else
                {
                    DrawLine(hdc, thisNdx, thispos-1, thisNdx, thispos);
                }
            }
        }
    }
    PrintMark(hdc, this, dLen, FETAL_MARK_EVENT);
}

static VOID PrintTocoWave(HDC hdc, PFHRWAVE this, UINT16 dLen)
{
    INT16     i;
    INT16     thispos;
    INT16     lastpos;
    INT16     thisNdx;
    INT16     lastNdx;
    GAL_PIXEL color;
    if (dLen == 0)
    {
        dLen = WAVE_WIDTH - 2;
    }
    //宫压曲线
    color = GetWindowElementColor(MonitorConfig.colorParam[PARA_BLOCK_TOCO]);//PIXEL_green;
    color = SetPenColor(hdc, color);
    for (i = 0; i < dLen; i++)
    {
        if (dLen == WAVE_WIDTH - 2)
        {
            thisNdx = this->xPos + i + 3;
            lastNdx = this->xPos + i + 2;
            if (lastNdx >= WAVE_WIDTH)
            {
                lastNdx -= WAVE_WIDTH;
            }
            if (thisNdx >= WAVE_WIDTH)
            {
                thisNdx -= WAVE_WIDTH;
            }
        }
        else
        {
            thisNdx = this->xPos - i;
            lastNdx = this->xPos - i - 1;
            if (lastNdx < 0)
            {
                lastNdx += WAVE_WIDTH;
            }
            if (thisNdx < 0)
            {
                thisNdx += WAVE_WIDTH;
            }
            if (sg_curSavePosX < thisNdx)
            	this->yPos[WAVE_TOCO][thisNdx] = this->yPos[WAVE_TOCO][sg_curSavePosX];
        }
        
        thispos = this->yPos[WAVE_TOCO][thisNdx];
        lastpos = this->yPos[WAVE_TOCO][lastNdx];
        if (thispos > -1 && lastpos > -1)
        {
            if (thisNdx > lastNdx)
            {
                DrawLine(hdc, lastNdx, lastpos, thisNdx, thispos);
            }
        }
    }
    SetPenColor(hdc, color);
    // 显示胎动打标和宫压归零标记
    PrintMark(hdc, this, dLen, FETAL_MARK_ZERO);
    PrintMark(hdc, this, dLen, FETAL_MARK_FM);
	//胎动曲线
    color = GetWindowElementColor(MonitorConfig.colorParam[PARA_BLOCK_FM]);
    SetPenColor(hdc, color);
    for (i = 0; i < dLen; i++)
    {
        if (dLen == WAVE_WIDTH - 2)
        {
            thisNdx = this->xPos + i + 3;
            lastNdx = this->xPos + i + 2;
            if (lastNdx >= WAVE_WIDTH)
            {
                lastNdx -= WAVE_WIDTH;
            }
            if (thisNdx >= WAVE_WIDTH)
            {
                thisNdx -= WAVE_WIDTH;
            }
        }
        else
        {
            thisNdx = this->xPos - i;
            lastNdx = this->xPos - i - 1;
            if (lastNdx < 0)
            {
                lastNdx += WAVE_WIDTH;
            }
            if (thisNdx < 0)
            {
                thisNdx += WAVE_WIDTH;
            }
            if (sg_curSavePosX < thisNdx)
            	this->yPos[WAVE_AFM][thisNdx] = this->yPos[WAVE_AFM][sg_curSavePosX];
        }
        thispos = this->yPos[WAVE_AFM][thisNdx];
        lastpos = this->yPos[WAVE_AFM][lastNdx];
        if (thispos > -1 && lastpos > -1)
        {
            if (thisNdx > lastNdx)
            {
                DrawLine(hdc, lastNdx, lastpos, thisNdx, thispos);
            }
        }
    }
}

static RefreshWave(PFHRWAVE this)
{
    HDC hdc;
    DrawBackground(this);
    ShowFetalTimeGraph(this);
    hdc = GetDC(this->hFhrGph);
    PrintFhrWave(hdc, this, 0);
    ReleaseDC(hdc);
    hdc = GetDC(this->hTocoGph);
    PrintTocoWave(hdc, this, 0);
    ReleaseDC(hdc);
    this->redrawFlag = FALSE;
}

static PrintWave(PFHRWAVE this)
{
    UINT16 step;
    HDC hdc;
    step = GetFetalPos();
    this->xPos += step;
    if (this->xPos >= this->fhr_back->cx)
    {
        this->xPos = 0;
        ShowFetalTimeGraph(this);
        FetalGraphDrawScrollBar(this);
    }
    hdc = GetDC(this->hFhrGph);
    BrushWave(hdc, this->fhr_back, this->xPos + 1, BRUSH_WIDTH, TRUE);
    PrintFhrWave(hdc, this, step);
    ReleaseDC(hdc);
    hdc = GetDC(this->hTocoGph);
    BrushWave(hdc, this->toco_back, this->xPos + 1, BRUSH_WIDTH, TRUE);
    PrintTocoWave(hdc, this, step);
    ReleaseDC(hdc);
}

static int waveCount = 0;
VOID FhrDrawWave(VOID)
{
    PFHRWAVE this = FetalWavePrint;
    if (!this->hFhrGph || !this->hTocoGph)
        return;
    if (LayoutInProcess)
        return;
    if (FACE_STD_SINGLE != MonitorConfig.faceType
        && FACE_STD != MonitorConfig.faceType)
        return;
    if (sStepDots[FhrConfig.sweep][waveCount] > 0)
    {
        if (this->drawFlag)
        {
            PrintWave(this);
        }
        if (this->redrawFlag)
        {
            RefreshWave(this);
        }
    }
    if (++waveCount >= sizeof(sStepDots[FhrConfig.sweep]))
        waveCount = 0;
}

VOID ReInitFetalWave(VOID)
{
    PFHRWAVE this = FetalWavePrint;
    
    if (MonitorConfig.faceType == FACE_STD 
        || MonitorConfig.faceType == FACE_STD_SINGLE)
    {
        //ShowFetalGraph();
        this->redrawFlag = TRUE;
        this->drawFlag   = TRUE;
        this->PgNdx = 0;
        UpdateFetalWavePos(this, TRUE);
    }
    else
    {
        this->redrawFlag = FALSE;
        this->drawFlag   = FALSE;
    }
}

VOID ReDrawFetalWave(PFHRWAVE this)
{
    if (MonitorConfig.faceType == FACE_STD 
        || MonitorConfig.faceType == FACE_STD_SINGLE)
    {
		UpdateFetalWavePos(this, TRUE);
		RefreshWave(this);
	}
}

VOID WavePageUp(VOID)
{
    if (MonitorConfig.faceType == FACE_STD 
        || MonitorConfig.faceType == FACE_STD_SINGLE)
    {
        PFHRWAVE this = FetalWavePrint;
        if (this->PgNdx < FETAL_WAVE_PAGE_MAX - 1)
        {
            if (this->PgNdx < this->PgCnt - 1)
            {
                this->PgNdx++;
            }
            ReDrawFetalWave(this);
            FetalGraphDrawScrollBar(this);
        }
    }
    return;
}

VOID WavePageDown(VOID)
{
    if (MonitorConfig.faceType == FACE_STD 
        || MonitorConfig.faceType == FACE_STD_SINGLE)
    {
        PFHRWAVE this = FetalWavePrint;
        if (this->PgNdx > 0)
        {
            this->PgNdx--;
        }
        ReDrawFetalWave(this);
        FetalGraphDrawScrollBar(this);
    }
    return;
}

VOID ExitViewWaveModule(VOID)
{
    if (MonitorConfig.faceType == FACE_STD 
        || MonitorConfig.faceType == FACE_STD_SINGLE)
    {
        PFHRWAVE this = FetalWavePrint;
		this->PgNdx = 0;
        ReDrawFetalWave(this);
        FetalGraphDrawScrollBar(this);
    }
    return;
}

VOID WavePageChange(INT16 page)
{
    if (MonitorConfig.faceType == FACE_STD 
        || MonitorConfig.faceType == FACE_STD_SINGLE)
    {
        PFHRWAVE this = FetalWavePrint;
        if (page >= 0 && page < this->PgCnt)
        {
            this->PgNdx = page;
            ReDrawFetalWave(this);
            FetalGraphDrawScrollBar(this);
        }
    }
    return;
}

VOID EraseWavesBuffer(VOID)
{
    PFHRWAVE this = FetalWavePrint;
    INT8 flag = LayoutInProcess;
    if (!flag)
        LayoutInProcess = TRUE;
    this->drawFlag = FALSE;
    this->redrawFlag = FALSE;
    waveCount = 0;
    FetalWaveBuffWritePtr   = FetalWaveBuffPtr;
    ZeroMemory(FetalWaveBuffPtr, FETAL_DATA_BUFF_LEN);
	int i, j;
	for (i = WAVE_FHR_CH1; i < WAVE_MAX; i++)
	{
		for (j = 0; j < WAVE_WIDTH; j++)
		{
			this->yPos[i][j] = -1;
		}
	}
    this->pHead     = FetalWaveBuffHeadPtr;
    this->pTail     = FetalWaveBuffTailPtr;
    this->pPage     = FetalWaveBuffWritePtr;
    this->pCurr     = FetalWaveBuffWritePtr;
    this->xPos      = 0;
    LayoutInProcess = flag;
    this->redrawFlag = TRUE;
    this->drawFlag = TRUE;
}

