	#ifndef _ANALYSIS_H_
#define _ANALYSIS_H_

#define FHR_FIS_DIAG_RESULT_MAX_LEN 100

#define FHR_DIAGNOSE_SEND_FHR_NUM   2400	//20分钟经过抽样了之后的波形数据
#define FHR_DIAGNOSE_BUF_LEN		4804	//目前的诊断模块的数据为4084字节数据


typedef struct fischer_infoex{
	CHAR   major;			   // 0x02 加速 0x04 减速
	CHAR   type;				// 变化类型
	UINT16 point;			   // 所在位置(相对评分数据开头)
}FISCINFOEX;
	//宫压的加速(峰值、拐点)
	typedef struct {
		INT startPosX;//宫压开始加速位置
		INT endPosX;///加速结束位置
		INT maxPosX;//峰值位置
		INT maxValue;//加速峰值
		INT averageValue;//宫压基线。
	}TOCOADDSPEED;
	typedef struct _fastFhr{
		INT maxPosX;
		INT start;
		INT end;
		INT addValue;
	}FASTFHR;
	typedef struct _slowFhr{
		INT maxPosX;
		INT start;
		INT downValue;//下降的振幅 早期晚期小于50 变异大于70
		INT end;
	}SLOWFHR;

typedef struct _fhr_diagnose_ctrl
{
	DATETIME end;
	INT16   len;	// 600~1200, len < 600 || len > 1200 本结构体中数据无效
	INT16   nr_valid;

	UINT8   UsedFlag;
	//Fischer评分法报告单结果
	UINT8   accSum;				//加速的个数
	UINT8   littleAccSum;		//小加速的个数
	UINT8   fastigiaAccSum;		//稽留加速的个数
	UINT8   slowReduceSum;		//迟发减速的个数
	UINT8   heavyReduceSum;		//重变化减速的个数
	UINT8   lightReduceSum;		//轻变化减速的个数
	UINT8   earlyReduceSum;		//早期减速的个数
	UINT8   extendReduceSum;	//延长减速的个数
	UINT8   baselineVal;		//20分钟内基线的值
	UINT8   swingVal;			//振幅变异值（放大10倍）
	UINT8   periodVal;			//周期变异值（放大10倍）
	UINT8   baselinePoints;		//基线得分
	UINT8   swingPoints;		//振幅变异得分
	UINT8   periodPoints;		//周期变异得分
	UINT8   accPoints;			//加速得分
	UINT8   reducePoints;		//减速得分
	UINT8   totalPoints;		//总分

	//加速结果
	//加速标注位置
	//加速的类型 (1->加速, 2->小加速,  3->稽留加速)
	//减速结果
	//减速标注位置
	//减速的类型  1->迟发减速, 2->微小迟发减速,  3->迟发减速尾部延长，4->变化减速+迟发减速
	//5->重变化减速， 6->轻变化减速，7->早期减速， 8->延长减速， 9->早期减速+变化减速
	UINT8	   fisDiaPosSum;
	FISCINFOEX fiscInfo[FHR_FIS_DIAG_RESULT_MAX_LEN];

}__attribute__ ((packed, aligned(1)))FHRDIAGNOSECTRL;

typedef struct __tagAnalyConfig{
	UINT32 type		 :2;
	UINT32 autoFlag	 :1;
	UINT32 enbType	  :1;
	UINT32 enbAuto	  :1;
	UINT32 enbStart	 :1;
	UINT32 enbDone	  :1;
	UINT32 enbShow	  :1;
	UINT32 putFlag	  :1;	 // put data falg
	UINT32 sendFlag	 :1;	 // data send, waitting for result
	UINT32 waitCnt	  :5;	 // wait count 0~24
	UINT32 nr_valid	 :12;	// valid data number 0~2400
}ANALYCFG;

typedef struct __analysis_result_save{
	UINT32  len;
	UINT8   anls_type;  // 
	UINT8   data_pct;   // 评分数据
	UINT8   vld_pct;	// 有效数据
	UINT8   fm_nr;	  // 胎动次数
	
	int fhr_JX;	  //心率基线
	int fhr_QV;	  //周期变异
	int fhr_ZV;	  //振幅变异
	int fasttime;	//加速时上升时间 （平均值）
	int fasthigh;	//加速时上升幅度
	int tdfast;	  //心率加速次数
	int tdslow;	  //心率减速次数
	int fastType;		//加速类型
	int slowType;		//减速类型
	int LDTime;			//晚期减速
	int EDTime;			//早期减速
	int VDTime;			//vd数
	UINT32  endtime;
	UINT32  second;
}ARET_SAVE;


#ifdef ANALYSIS_GLOBALS
#define ANALY_EXT
#else
#define ANALY_EXT   extern
#endif

ANALY_EXT   ANALYCFG		AnalyConfig;
ANALY_EXT   ARET_SAVE	   AnlsRet;

ANALY_EXT   VOID AnalysisPacketFound (PACKETFRAME2 *pPack);
ANALY_EXT   VOID AnalySendPack(UCHAR *pack);
ANALY_EXT   VOID AnalyInSecond(VOID);
ANALY_EXT   char get_analysis_enable(void);
#endif /*_ANALYSIS_H_*/

