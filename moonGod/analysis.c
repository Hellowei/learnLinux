#define ANALYSIS_GLOBALS

#include "includes.h"
#include "analysis.h"

#if 1
typedef struct __tagAnalysisResult{
	int fhr_JX;	  //心率基线
	int fhr_QV;	  //周期变异
	int fhr_ZV;	  //振幅变异
	int fasttime;	//加速时上升时间 （平均值）
	int fasthigh;	//加速时上升幅度
	int tdfast;	  //心率加速次数
	int tdslow;	  //心率减速次数
	int fastType;		//加速类型 0没意义1周期性2散在性
	int slowType;		//减速类型 0没意义1晚期减速2早期减速
	int LDTime;			//晚期减速
	int EDTime;			//早期减速
	int VDTime;			//vd数*/
}NST_RESULT;

static NST_RESULT sNST;

static void InputData(unsigned char *fhr,unsigned char *toco, int len, NST_RESULT *pRet)
{
	time_t now;
	now = time(NULL);
	int fhr_JX = 0;	  //心率基线
	int fhr_QV = 0;	  //周期变异
	int fhr_ZV = 0;	  //振幅变异
	int fasttime = 0;	//加速时上升时间 （平均值）
	int fasthigh = 0;	//加速时上升幅度
	int tdfast = 0;	  //心率加速次数
	int tdslow = 0;	  //心率减速次数
	int slinetc = 0;
	int fastType=0;		//加速类型 0没意义1周期性2散在性
	int slowType=0;		//减速类型 0没意义1晚期减速2早期减速3变异减速4其他减速
	UCHAR EDTime = 0;//早期减速
	UCHAR LDTime = 0;//晚期减速
	UCHAR VDTime = 0;//变异减速
	typedef struct myCTG{
		unsigned char fhr;
		unsigned char toco;
		unsigned char fm; //0x02 - jiasu,0x08 - 减速
	}SLINE;
	typedef struct _fastFhr{
		INT maxPosX;
		INT start;
		INT end;
	}FASTFHR;
	typedef struct _slowFhr{
		INT maxPosX;
		INT start;
		INT downValue;//下降的振幅 早期晚期小于50 变异大于70
		INT end;
	}SLOWFHR;
	SLOWFHR slowFhr[100] = {{0}};
	FASTFHR fastFhr[100] = {{0}};
	SLINE sline[2400] = {{0}};
	
	int i, j, k;
	int loops, count, sum;
	int tdtc;

	loops = (len - 4);
	slinetc = 0;
	for(j = 0; j < loops; j ++)
	{
		i = j;
		//胎心率相关的
		if (i >= 2400)
			break;
		if(fhr[i]> 80 && fhr[i + 1] > 80 && fhr[i+2] > 80 && fhr[i+3] > 80)
		{
			fhr[i] =(unsigned char)(((int)fhr[i] + (int)fhr[i+1]
				+ (int)fhr[i+2] + (int)fhr[i+3]) >> 2);
		}
		else
		{
			fhr[i] = 0;
		}
		sline[i].fhr = fhr[i];
		if((toco[i] <= 0 || toco[i] >= 100) && i > 0)//丢弃异常值
			toco[i] = toco[i-1];
		slinetc++;
	}
	//  计算基线值 和宫压滤波
	{
		count = 0;
		sum = 0;
		for(i = 1; i < slinetc; i++)
		{
			if(sline[i].fhr > 110 && sline[i].fhr < 170)
			{
				sum += sline[i].fhr;
				count++;
			}
				//宫压相关的
			sline[i].toco = (unsigned char)(((int)toco[i]+(int)toco[i+1]+(int)toco[i+2]+(int)toco[i+3])
			>>2);//平滑滤波
		}
		if (count > 0)
			fhr_JX = sum / count;
	}
	//宫压的加速(峰值、拐点)
	typedef struct {
		INT startPosX;//宫压开始加速位置
		INT endPosX;///加速结束位置
		INT maxPosX;//峰值位置
		INT maxValue;//加速峰值
		INT averageValue;//宫压基线。
	}TOCOADDSPEED;
	TOCOADDSPEED tocoAddSpeed[100] = {{0}};
	{
		INT MINTIME = 60;//加速最短时间阈值
		INT MINDELTAVALUE = 20;//最小峰值阈值
		INT start,end,max,maxValue;
		INT addSpeedTime = 0;//宫压加速次数
		INT squreToco = 0;//宫压加速积分
		BOOL isAlwayUP = FALSE;
		//宫压加速分析思路参考胎心加速的,把出现上升趋的点作为起点开始试探
		//从而找出峰值，结束点
		INT AVERAGEADDSPEEDTIME = 200;//200find one addspeed
		for(i = 5; i < slinetc - AVERAGEADDSPEEDTIME; i++)
		{	
			start = i;
			squreToco = end=max=maxValue= 0;
			isAlwayUP = FALSE;
			printf("cur i=%d\n",i);
			//出现上升趋势 都和[i]比较避免锯齿带来的影响
			if(sline[i + 2].toco > sline[i].toco + 1
				&& sline[i + 1].toco > sline[i].toco
				&& sline[i + 3].toco > sline[i].toco + 2)
			{
				for(j=i;j <i + AVERAGEADDSPEEDTIME;j++)
				{
					if(maxValue <= sline[j].toco)//找峰值
					{
						maxValue = sline[j].toco;
						max = j;
					}
					printf("i=%d ,j=%d maxValue=%d\n",i,j,maxValue);
					squreToco += (sline[j].toco-sline[i].toco);
					if(sline[i].toco > sline[j].toco)//找到加速结束时间,忽略加速过程有宫压调零发生
					{
					printf("oooooooooK %d %d (%d %d) squreToco=%d\n",maxValue,sline[i].toco,j,i,squreToco);
						if((maxValue-sline[i].toco>MINDELTAVALUE)&&(j-i>MINTIME)
						 &&(squreToco>(j-i)*(maxValue-sline[i].toco)/2))
						 {
						 	tocoAddSpeed[addSpeedTime].startPosX = start;
						 	tocoAddSpeed[addSpeedTime].endPosX = j;
						 	tocoAddSpeed[addSpeedTime].maxPosX = max;
						 	tocoAddSpeed[addSpeedTime].maxValue= maxValue;
						 	tocoAddSpeed[addSpeedTime].averageValue = sline[i].toco;
						 	addSpeedTime++;
						 	if(addSpeedTime>=100)
						 	{
						 		addSpeedTime = 100;
						 	}
						 }
						 i = j;
						 break;
					}
					//一直在加速的情况
					if(j - i + 2 > AVERAGEADDSPEEDTIME)
						isAlwayUP = TRUE;
				}
			}
			if (isAlwayUP)
				 i = i+AVERAGEADDSPEEDTIME/3;//i = j;会导致跳过部分加速尾段仍高于开始的情况
		}
		#if 1
		for(i = 0 ;i < addSpeedTime;i++)
		{
			printf("宫压%d加速from (%d,%d)(%d,%d)  Max=(%d,%d)\n",i+1,tocoAddSpeed[i].startPosX,tocoAddSpeed[i].averageValue,tocoAddSpeed[i].endPosX
				,tocoAddSpeed[i].averageValue,tocoAddSpeed[i].maxPosX,tocoAddSpeed[i].maxValue);
		}
		printf("宫压加速次数%d \n",addSpeedTime);
		#endif
	}
	
	//  分析加速
	{
		int sta1,sta2;
		int start,end;
		int maxfhr,maxx,summ;
		int fasttime1[100];
		int fasthigh1[100];
		tdfast = 0;
		fasttime = 0;
		fasthigh = 0;
		tdtc = 0;
		sta1 = FALSE;
		sta2 = FALSE;
		start = 0;
		end = 0;
		for(i = 5; i < slinetc - 130; i++)//
		{
			maxfhr = 0;
			maxx = 0;
			summ = 0;
			if(sline[i + 2].fhr > sline[i].fhr + 1
				&& sline[i + 1].fhr > sline[i].fhr
				&& sline[i + 3].fhr > sline[i].fhr + 2)
			{
				for(j = i; j < i + 130;j++)//70
				{
					//求积分 
					if(sline[i].fhr+30 > sline[j].fhr //30 //20
						&& sline[j].fhr > sline[i].fhr+3)
					{
						summ += sline[j].fhr -sline[i].fhr;
						if(maxfhr < sline[j].fhr)
						{ 
							maxfhr = sline[j].fhr;
							maxx=j;
						}
					}
					if(sline[i].fhr >= sline[j].fhr)
					{
						if((summ > 380) && (maxfhr - fhr_JX > 15)//380,15
							&& (((summ * 10) >> 3) > (j - i) * 10)
							)
						{
							sline[maxx].fm |= 0x02;
							fasttime1[tdtc] = j - i;
							fasthigh1[tdtc] = maxfhr - sline[i].fhr;
							fastFhr[tdtc].start = i;
							fastFhr[tdtc].end   = j;
							fastFhr[tdtc].maxPosX = maxx;
							i = j;
							tdtc ++;
							break;
						}
					}
				}
			}
		}
		fasttime = 0;
		fasthigh = 0;
		for(i = 0; i < tdtc; i++)
		{
			fasttime += fasttime1[i];
			fasthigh += fasthigh1[i];
		}
		if(tdtc>0)
		{
			fasttime = (int)(fasttime / (tdtc)) * 0.5;// 0.5是时间/频率
			fasthigh = fasthigh / (tdtc);
		}
		tdfast = tdtc;
		for(i = 0;i < tdfast;i++)
		{
			printf("第%d加速胎心 (%d,maxPosx=%d ,%d)\n",i,fastFhr[i].start ,fastFhr[i].maxPosX,fastFhr[i].end);
		}
	}

	//  分析减速
	//  ansistdslow(this);
	{
		int lowpoint;
		unsigned long ucstarttime;
		int sta1,sta2;
		int start,end;
		tdtc=0;
		tdslow = 0;
		for(i = 55; i < slinetc - 75; i++)
		{
			if ((sline[i].fhr+30 < fhr_JX) && (sline[i].fhr > 60)
				&& (sline[i+1].fhr > 60) && (sline[i-1].fhr > 60))
			{
				sta1=TRUE;
				sta2=TRUE;
				for(j = 1; j < 35; j++)
				{
					if (sline[i].fhr > sline[i+j].fhr && sline[i+j].fhr>60)
						sta1=FALSE;
					if (sline[i].fhr > sline[i-j].fhr && sline[i-j].fhr>60)
						sta2=FALSE;
					if(FALSE == sta2 || FALSE == sta1 )
						break;
				}
				if (sta1 && sta2 && (sline[i].fhr > 60) && (sline[i-2].fhr > 60)
				&& (sline[i+2].fhr > 60))
				{
					sta1 = FALSE;
					sta2 = FALSE;
					for(j = 0; j < 60; j += 1)
					{
						if(sline[i - j].fhr > sline[i].fhr + 20 )
						{
							sta1 = TRUE;
							start = i - j;
							break;
						}
						if (i - j < 6)
							break;
						if (sline[i].fhr >= fhr_JX)
							break;
					}
					for(j = 0; j < 60; j++)
					{
						if(sline[i+j].fhr > sline[i].fhr+20)
						{
							sta2 = TRUE;
							end = i + j;
							break;
						}
						if ((i + j >= slinetc) || (sline[i].fhr >= fhr_JX))
							break;
					}
					for(j = i - 5; j< i + 5; j++)
					{
						if (sline[j].fhr < 60 )
							sta2 = FALSE;
					}
					for (j = start; j < end; j++)
						sum += fhr_JX - sline[j].fhr;
					if (sum < 190)
						sta2 = FALSE;
					if (sta1 && sta2 && start + 35 < end)
					{
						slowFhr[tdtc].start = start;
						slowFhr[tdtc].end   = end;
						slowFhr[tdtc].maxPosX = i;
						slowFhr[tdtc].downValue = fhr_JX - sline[i].fhr;//减速下降最大幅度
						tdtc++;
						sline[i].fm |= 0x08;
						i += 60;
					}
				}
			}
		}
		tdslow = tdtc;
		for(i = 0;i < tdslow;i++)
		{
			printf("第%d减速胎心 (%d,maxPosx =%d ,%d)\n",i,slowFhr[i].start ,slowFhr[i].maxPosX,slowFhr[i].end);
		}
	}
	printf("分析加速、减速和宫压的关系，得出其性质\n");
/////分析加速、减速和宫压的关系，得出其性质
	{
		UCHAR cycleTime = 0;
		for(i = 0 ;i < 100;i++)
		{
			if(tocoAddSpeed[i].maxValue == 0)
				break;
			for(j=0;j<tdfast;j++)//加速
			{
				if(fastFhr[j].maxPosX == 0)
					break;//已统计
				if(fastFhr[j].start > tocoAddSpeed[i].endPosX)
					break;//加速和当前的宫压不存在关系
				printf("是否周期性%d %d\n",(fastFhr[j].maxPosX>tocoAddSpeed[i].startPosX),(fastFhr[j].maxPosX<tocoAddSpeed[i].endPosX));
				if((fastFhr[j].maxPosX>tocoAddSpeed[i].startPosX)&&(fastFhr[j].maxPosX<tocoAddSpeed[i].endPosX))//两峰相对	
				{
					printf("是周期性%d %d %d\n",j,fastFhr[j].start,fastFhr[j].end);
					fastFhr[j].maxPosX = 0;
					cycleTime++;
					break;
				}
			}
			for(j=0;j<tdslow;j++)//减速
			{
				if(slowFhr[j].maxPosX == 0)
					break;//已统计
				if(slowFhr[j].start-tocoAddSpeed[i].endPosX > 40)
					break;//减速和当前的宫压不存在关系
				//变异减速:下降大于70，与宫压无相关关系
				if(slowFhr[j].downValue > 70 )
				{
					slowFhr[j].maxPosX = 0;
					VDTime++;
					break;
				}
				//早期减速:两峰两对，胎心下降不超50
printf("是否早期减速:%d %d %d\n",j,fastFhr[j].maxPosX>tocoAddSpeed[i].startPosX,fastFhr[j].maxPosX<tocoAddSpeed[i].endPosX);
			//	(slowFhr[j].maxPosX > tocoAddSpeed[i].startPosX)&&(slowFhr[j].maxPosX < tocoAddSpeed[i].endPosX
				if((slowFhr[j].maxPosX > tocoAddSpeed[i].startPosX)&&(slowFhr[j].maxPosX < tocoAddSpeed[i].endPosX)
					&& (slowFhr[j].downValue < 50))
				{
					slowFhr[j].maxPosX = 0;
					EDTime++;
					break;
				}
				//晚期减速:胎心下降在宫压峰值后，两峰相差30-60秒，胎心落后宫压，胎心下降不超50
				if((slowFhr[j].maxPosX > tocoAddSpeed[i].endPosX)&& (slowFhr[j].downValue < 50))
				{
					slowFhr[j].maxPosX = 0;
					LDTime++;
					break;
				}
	
			}
		}
		#if 1 
		INT c = tdslow-EDTime-LDTime-VDTime;
		printf("加速%d,周期加速%d 减速%d,早减%d,晚减%d,变减%d,其他%d\n",tdfast,cycleTime,
			tdslow,EDTime,LDTime,VDTime,c);
		//定义加速性质
		if(tdfast > 0)//加速
			fastType = (cycleTime*2 >= tdfast)?1:2;
		//定义减速性质
		if(tdslow> 0 && (EDTime*2 >= tdslow))//早减
			slowType = 2;
		else if(tdslow> 0 && (LDTime*2 >= tdslow))//晚减
			slowType = 1;
		else if(tdslow> 0 && (VDTime*2 >= tdslow))//变减
			slowType = 3;
		else if(tdslow> 0 && (c*2 >= tdslow))//其他
			slowType = 4;
		#endif
	}
	//  去掉加速减速,重新计算基线
	{
		count = 0;
		sum = 0;
		for (i = 0; i < slinetc; i++)
		{
			if (sline[i].fm & (0x08 | 0x02))
			{
				j = i - 20;
				for (; j < i + 20; j++)
				{
					if (j >= slinetc)
						break;

					if (j > 0 && sline[j].fm == 0)
						sline[j].fm = 0x01;
				}
				break;
			}
		}
		for(i = 0; i < slinetc; i++)
		{
			if(sline[i].fhr > 110 && sline[i].fhr < 170 && sline[i].fm == 0)
			{
				sum += sline[i].fhr;
				count++;
			}
		}
		if (count > 0)
		{
			fhr_JX = sum / count;
		}
	}
	//  分析减速与加速的关系
	
	//  分析细变异
	{
		int maxx, minx, upp, dww, www, maxzq, maxzf, mzq;
		BOOL nofind;
		fhr_QV = 4;
		fhr_ZV = 3;
		if( fhr_JX == 0)
		{
			fhr_QV = 0;
			fhr_ZV = 0;
			return;
		}
		maxzq = 0;
		maxzf = 0;
		for(i = 5; i < slinetc - 50; i += 2)
		{
			maxx = 0;
			minx = 250;
			upp  = 0;
			dww  = 0;
			www  = 0;
			mzq  = 0;
			nofind = FALSE;
			for(j = i; j < i + 50; j++)
			{
				if (maxx < sline[j].fhr)
					maxx = sline[j].fhr;
				if (minx > sline[j].fhr)
					minx = sline[j].fhr;
				if (sline[j].fhr > sline[i].fhr)
					upp++;
				if (sline[j].fhr < sline[i].fhr)
					dww++;
				if (sline[j].fhr == sline[i].fhr)
					www++;
				if (((sline[j+2].fhr > sline[i].fhr)
					&& sline[j].fhr < sline[i].fhr)
					||((sline[j+2].fhr < sline[i].fhr)
					&& sline[j].fhr > sline[i].fhr))
				{
					mzq++;
				}
				if(ABS(sline[i].fhr - sline[j].fhr) > 15)
				{
					nofind = TRUE;
					break;//原来为j = i + 50;
				}
			}
			i=j;//原来没有这句的,加上为了实现跳跃式统计
			if(nofind == FALSE && maxx - minx < 30
			&& upp > 5 && dww > 5 && www > 5)
			{
				if (upp>dww)
					j = dww;
				else
					j = upp;

				if (j > www)
					j = www;

				if (maxzq < j)
					maxzq = j * 0.7;

				j = maxx - minx;

				if (maxzf < j && maxzq > 2)
				{
					maxzf = j*0.8;
				}
			}
		}
		fhr_ZV = maxzf;
		fhr_QV = maxzq;
	}
	if (fhr_JX == 0)
	{
		// 计算不出基线,统计标准基线
		count = 0;
		sum = 0;
		for(i = 0; i < slinetc; i++)
		{
			sum += sline[i].fhr;
			count++;
		}
		fhr_JX = sum / count;
		count = 0;
		for(i = 0; i < slinetc; i++)
		{
			if (fhr_JX > sline[i].fhr)
				count++;
		}
		count = 0;//这里又为0?
		sum = 0;
		if (count > slinetc / 2)
		{
			for(i = 0; i < slinetc; i++)
			{
				if (fhr_JX > sline[i].fhr && sline[i].fhr > 60)
				{
					sum += sline[i].fhr;
					count++;
				}
			}
		}
		else
		{
			for(i = 0; i < slinetc; i++)
			{
				if (fhr_JX <= sline[i].fhr && sline[i].fhr < 210)
				{
					sum += sline[i].fhr;
					count++;
				}
			}
		}
		fhr_JX = sum / count;
	}
	pRet->fhr_JX	= fhr_JX;	  //心率基线
	pRet->fhr_QV	= fhr_QV;	  //周期变异
	pRet->fhr_ZV	= fhr_ZV;	  //振幅变异
	pRet->fasttime  = fasttime;	//加速时上升时间 （平均值）
	pRet->fasthigh  = fasthigh;	//加速时上升幅度
	pRet->tdfast	= tdfast;	  //心率加速次数
	pRet->tdslow	= tdslow;	  //心率减速次数
	pRet->fastType = fastType;	  ///加速类型 0没意义1周期性2散在性
	pRet->slowType = slowType;	  ///减速类型 0没意义1晚期减速2早期减速3变减4其他
	pRet->LDTime = LDTime;	  //晚期减速
	pRet->EDTime = EDTime;	  //早期减速
	pRet->VDTime = VDTime;	  //vd数
}		


#endif

typedef union _tagFETALDIAGNOSEDATA
{
	struct {
		unsigned char stx;
		unsigned char sync;
		unsigned char id;
		unsigned char fhr[FHR_DIAGNOSE_SEND_FHR_NUM];
		unsigned char toco[FHR_DIAGNOSE_SEND_FHR_NUM];
		unsigned char chksum;
	}frame;
	unsigned char buffer[FHR_DIAGNOSE_BUF_LEN];
}FETALDIAGNOSEDATA;

typedef enum __tagANLS_TYPE{
	ANLS_NULL,
	ANLS_CST
}ANLS_TYPE;


static FETALDIAGNOSEDATA	sFetalData;
static FHRDIAGNOSECTRL	  sFhrDiagnose;
static HWND				 shAnalyDlg = 0;


VOID SetAnalySendFlag(BOOL flag)
{
	if (AnalyConfig.sendFlag != flag)
	{
		AnalyConfig.sendFlag = flag;
	}
	AnalyConfig.enbType  = !flag;
	AnalyConfig.enbAuto  = !flag;
	AnalyConfig.enbStart = !flag;
	AnalyConfig.enbDone  = !flag;
	AnalyConfig.enbShow  = sFhrDiagnose.UsedFlag;
	AnalyConfig.waitCnt  = 0;
	if (FALSE == flag)
	{
		if (AnalyConfig.nr_valid < 1200)
			AnalyConfig.enbDone = FALSE;
	}
}

VOID ShowAnalysisMoudleNotExist(BOOL show)
{
	if (show)
	{
		
	}
	else
	{
		
	}
}

#include <linux/rtc.h>
#include <fcntl.h>
#include <sys/ioctl.h>

INT32 GetTimeBeforeFm(INT32 second)
{
	INT32 ndx = FetalDataPtr->info.index;
	INT32 i;
	INT32 count = 0;
	ndx -= second;
	if (ndx < 0)
		ndx = ndx + DATA_TEMP_LEN;
	for (i = 0; i < second; i++)
	{
		if (   (FetalDataPtr->data[ndx].wave[0].fmbits)
			|| (FetalDataPtr->data[ndx].wave[1].fmbits)
			|| (FetalDataPtr->data[ndx].wave[2].fmbits)
			|| (FetalDataPtr->data[ndx].wave[3].fmbits)
			|| (FetalDataPtr->data[ndx].wave[0].afmbits)
			|| (FetalDataPtr->data[ndx].wave[1].afmbits)
			|| (FetalDataPtr->data[ndx].wave[2].afmbits)
			|| (FetalDataPtr->data[ndx].wave[3].afmbits)	)
		{
			count++;
		}
		if (++ndx >= DATA_TEMP_LEN)
		{
			ndx = 0;
		}
	}
	return count;
}

BOOL CstAnalyInProc(VOID)
{
	InputData(sFetalData.frame.fhr,sFetalData.frame.toco,sFhrDiagnose.len, &sNST);
	time((time_t*)&AnlsRet.endtime);
	AnlsRet.data_pct = ABS(sFhrDiagnose.len) * 100 / FHR_DIAGNOSE_SEND_FHR_NUM;
	AnlsRet.vld_pct = AnalyConfig.nr_valid * 100 / FHR_DIAGNOSE_SEND_FHR_NUM;
	AnlsRet.second = sFhrDiagnose.len / 2;
	AnlsRet.len = sizeof(AnlsRet);
	AnlsRet.anls_type = ANLS_CST;
	AnlsRet.fm_nr = GetTimeBeforeFm(AnlsRet.second);//AllParams.fm;
	memcpy(&AnlsRet.fhr_JX, &sNST, sizeof(sNST));
	
	sFhrDiagnose.end = DateTime;
	AnalyConfig.putFlag = TRUE;
	sFhrDiagnose.len = -3;
	sFhrDiagnose.nr_valid = (INT16)AnalyConfig.nr_valid;
	AnalyConfig.putFlag = FALSE;
	sFhrDiagnose.UsedFlag = TRUE;
	printf("\n\t心率基线:\t%d\n\t周期变异:\t%d\n\t振幅变异:\t\%d",
		sNST.fhr_JX, sNST.fhr_QV, sNST.fhr_ZV);
	printf("\n\t加速时间:\t%d\n\t加速幅度:\t%d" , sNST.fasttime, sNST.fasthigh);
	printf("\n\t加速次数:\t%d\n\t减速次数:\t%d\n" , sNST.tdfast, sNST.tdslow);
	printf("AnlsRet.second...%d\r\n", AnlsRet.second);
	printf("加速类型=%d，减速类型=%d,晚期减速%d,早期减速%d vd数%d\n",
		sNST.fastType, sNST.slowType, sNST.LDTime, sNST.EDTime, sNST.VDTime);
	printf("打评分各个指标2015-05-25\n");
	return TRUE;
}


BOOL AnalySendData(VOID)
{
	return CstAnalyInProc();
	if (sFhrDiagnose.len < 600)
		return FALSE;
	return CstAnalyInProc();
	int i, chksum;
	chksum = 0;
	for (i = 0; i < FHR_DIAGNOSE_BUF_LEN - 1; i++)
	{
		chksum += sFetalData.buffer[i];
	}
	sFetalData.frame.chksum = LOBYTE(chksum);
#if _ENB_REC_FUNC
	PostMessage(SysRec_HTSK, MSG_PRTCL_ANALY, 0,
				(UINT32)&sFetalData.buffer[0]);
#endif
	sFhrDiagnose.end = DateTime;
	AnalyConfig.putFlag = TRUE;
	sFhrDiagnose.len = -3;
	sFhrDiagnose.nr_valid = (INT16)AnalyConfig.nr_valid;
	AnalyConfig.putFlag = FALSE;
	return TRUE;
}

VOID PushAnalysisInfoEx (PACKETFRAME2 *pPack)
{
	if ((0x02 == pPack->frame.id) || (0x04 == pPack->frame.id))
	{
		sFhrDiagnose.fiscInfo[sFhrDiagnose.fisDiaPosSum].major = 
			pPack->frame.id;
		sFhrDiagnose.fiscInfo[sFhrDiagnose.fisDiaPosSum].type  = 
			pPack->frame.data[2];
		sFhrDiagnose.fiscInfo[sFhrDiagnose.fisDiaPosSum].point = 
			MAKEWORD(pPack->frame.data[1], pPack->frame.data[0]);
		sFhrDiagnose.fisDiaPosSum++;
	}
}

VOID PushAnalysisResult (PACKETFRAME2 *pPack)
{
	if (0x05 == pPack->frame.id)
	{
		int i = 0;
		sFhrDiagnose.UsedFlag		= TRUE;
		sFhrDiagnose.accSum		  = pPack->frame.data[i++];
		sFhrDiagnose.littleAccSum	= pPack->frame.data[i++];
		sFhrDiagnose.fastigiaAccSum  = pPack->frame.data[i++];
		sFhrDiagnose.slowReduceSum   = pPack->frame.data[i++];
		sFhrDiagnose.heavyReduceSum  = pPack->frame.data[i++];
		sFhrDiagnose.lightReduceSum  = pPack->frame.data[i++];
		sFhrDiagnose.earlyReduceSum  = pPack->frame.data[i++];
		sFhrDiagnose.extendReduceSum = pPack->frame.data[i++];
		sFhrDiagnose.baselineVal	 = pPack->frame.data[i++];
		sFhrDiagnose.swingVal		= pPack->frame.data[i++];
		sFhrDiagnose.periodVal	   = pPack->frame.data[i++];
		sFhrDiagnose.baselinePoints  = pPack->frame.data[i++];
		sFhrDiagnose.swingPoints	 = pPack->frame.data[i++];
		sFhrDiagnose.periodPoints	= pPack->frame.data[i++];
		sFhrDiagnose.accPoints	   = pPack->frame.data[i++];
		sFhrDiagnose.reducePoints	= pPack->frame.data[i++];
		sFhrDiagnose.totalPoints	 = pPack->frame.data[i++];
	}
}

VOID AnalysisPacketFound (PACKETFRAME2 *pPack)
{
	switch (pPack->frame.id)
	{
		case 0x02:
			PushAnalysisInfoEx(pPack);
			break;

		case 0x04:
			PushAnalysisInfoEx(pPack);
			break;

		case 0x05:
			PushAnalysisResult(pPack);
			break;

		default:
			break;
	}
}

VOID AnalySendPack(UCHAR *pack)
{
	INT32 send = 0;
	if (pack[0] == 0x55 && pack[1] == 0xAA && pack[2] == 0x01)
	{
		MdlUartTran(UART_PORT_ANALY, pack, FHR_DIAGNOSE_BUF_LEN, &send);
		ShowAnalysisMoudleNotExist(send < FHR_DIAGNOSE_BUF_LEN);
	}
}

VOID DispAnalysisResult(HDC hdc)
{
	PDC pdc = dc_HDC2PDC(hdc);
	INT32 x = DLG_OFFSET;
	INT32 y = DLG_OFFSET;
	INT32 y1;
	UCHAR txt[64];
	RECT rc;
//	prinfo("AnlsRet::\r\n");
//	printf("\t.len	  :   %d\r\n", AnlsRet.len);
//	printf("\t.anls_type:   %d\r\n", AnlsRet.anls_type);
//	printf("\t.data_pct :   %d\r\n", AnlsRet.data_pct);
//	printf("\t.vld_pct  :   %d\r\n", AnlsRet.vld_pct);
//	printf("\t.fm_nr	:   %d\r\n", AnlsRet.fm_nr);
//	printf("\t.fhr_JX   :   %d\r\n", AnlsRet.fhr_JX);
//	printf("\t.fhr_QV   :   %d\r\n", AnlsRet.fhr_QV);
//	printf("\t.fhr_ZV   :   %d\r\n", AnlsRet.fhr_ZV);
//	printf("\t.fasttime :   %d\r\n", AnlsRet.fasttime);
//	printf("\t.fasthigh :   %d\r\n", AnlsRet.fasthigh);
//	printf("\t.tdfast   :   %d\r\n", AnlsRet.tdfast);
//	printf("\t.tdslow   :   %d\r\n", AnlsRet.tdslow);
	SetTextColor(hdc, GetWindowElementColor (FGC_CONTROL_DEF));
//	SetBkColor(hdc, GetWindowElementColor (BKC_CONTROL_DEF));
	SetPenColor(hdc, GetWindowElementColor (FGC_CONTROL_DEF));
	x += TextOut(hdc, x, y, LoadString(STR_PRINT_NAME));
	x += TextOut(hdc,x,y, LoadString(STR_MAIN_TOPBAR_NAME_NAME));
	x = 200;
	x += TextOut(hdc, x, y, LoadString(STR_PRINT_ID));
	x += TextOut(hdc,x,y, LoadString(STR_MAIN_TOPBAR_ID_NUM));
	x = 350;
	if (PatientInfo.patientAge > 1)
	{
		sprintf(txt, "%s %2d", LoadString(STR_PRINT_AGE), PatientInfo.patientAge);
	}
	else
	{
		sprintf(txt, "%s   ", LoadString(STR_PRINT_AGE), PatientInfo.patientAge);
	}
	x += TextOut(hdc, x, y, txt) + DLG_OFFSET * 2;
	if (PatientInfo.gestationalTimes < 1)
	{
		sprintf(txt, "%s  ", LoadString(STR_PRINT_TIMES));
	}
	else
	{
		sprintf(txt, "%s %d", LoadString(STR_PRINT_TIMES),
			PatientInfo.gestationalTimes);
	}
	x += TextOut(hdc, x, y, txt) + DLG_OFFSET * 2;
	if (PatientInfo.gestationalWeeks > 20)
	{
		sprintf(txt, "%s %2dw  %dd", LoadString(STR_PRINT_WEEK),
			PatientInfo.gestationalWeeks, PatientInfo.gestationalDay);
	}
	else
	{
		sprintf(txt, "%s   w   d", LoadString(STR_PRINT_WEEK),
			PatientInfo.gestationalWeeks, PatientInfo.gestationalDay);
	}
	x += TextOut(hdc, x, y, txt) + DLG_OFFSET;
	y += KEY_HEIGHT;
	Line(hdc, DLG_OFFSET, y, RECTW(pdc->DevRC) - DLG_OFFSET * 2, y);
	x = DLG_OFFSET;
	Rect(hdc, 1, 1, RECTW(pdc->DevRC) - 2, RECTH(pdc->DevRC) - 2);
	y += 5;


	Rect(hdc, x, y, x + 80 * 5, y + KEY_HEIGHT * 6);
	Line(hdc, x, y + KEY_HEIGHT * 1, x + 80 * 5, y + KEY_HEIGHT * 1);
	Line(hdc, x, y + KEY_HEIGHT * 2, x + 80 * 5, y + KEY_HEIGHT * 2);
	Line(hdc, x, y + KEY_HEIGHT * 3, x + 80 * 5, y + KEY_HEIGHT * 3);
	Line(hdc, x, y + KEY_HEIGHT * 4, x + 80 * 5, y + KEY_HEIGHT * 4);
	Line(hdc, x, y + KEY_HEIGHT * 5, x + 80 * 5, y + KEY_HEIGHT * 5);
	
	Line(hdc, x +  80 * 1, y, x +  80 * 1, y + KEY_HEIGHT * 6);
	Line(hdc, x +  80 * 2, y, x +  80 * 2, y + KEY_HEIGHT * 6);
	Line(hdc, x +  80 * 3, y, x +  80 * 3, y + KEY_HEIGHT * 6);
	Line(hdc, x +  80 * 4, y, x +  80 * 4, y + KEY_HEIGHT * 6);
//	Line(hdc, x +  80 * 5, y, x +  80 * 5, y + KEY_HEIGHT * 6);
//	prinfo("Line(%d, %d, %d, %d)\r\n", x, y, pdc->DevRC.right - DLG_OFFSET, y);
	SetRect(&rc, x, y , x + 80, y + KEY_HEIGHT);
	sprintf(txt, "%s", LoadString(STR_DLG_ANLS_ITEMS));
	TextOutCenterLen(hdc, &rc, txt, strlen(txt));
	SetRect(&rc, x, y + KEY_HEIGHT * 1, x + 80, y + KEY_HEIGHT * 2);
	sprintf(txt, "%s", LoadString(STR_DLG_ANLS_FHR_BASE));
	TextOutCenterLen(hdc, &rc, txt, strlen(txt));
	SetRect(&rc, x, y + KEY_HEIGHT * 2, x + 80, y + KEY_HEIGHT * 3);
	sprintf(txt, "%s", LoadString(STR_DLG_ANLS_AMPLITUDE));
	TextOutCenterLen(hdc, &rc, txt, strlen(txt));
	SetRect(&rc, x, y + KEY_HEIGHT * 3, x + 80, y + KEY_HEIGHT * 4);
	sprintf(txt, "%s", LoadString(STR_DLG_ANLS_FAST_TIME));
	TextOutCenterLen(hdc, &rc, txt, strlen(txt));
	SetRect(&rc, x, y + KEY_HEIGHT * 4, x + 80, y + KEY_HEIGHT * 5);
	sprintf(txt, "%s", LoadString(STR_DLG_ANLS_FAST_AMPL));
	TextOutCenterLen(hdc, &rc, txt, strlen(txt));
	SetRect(&rc, x, y + KEY_HEIGHT * 5, x + 80, y + KEY_HEIGHT * 6);
	sprintf(txt, "%s", LoadString(STR_DLG_ANLS_FM_TIMES));
	TextOutCenterLen(hdc, &rc, txt, strlen(txt));
	x += 80;
	SetRect(&rc, x, y , x + 80, y + KEY_HEIGHT);
	sprintf(txt, "0 '");
	TextOutCenterLen(hdc, &rc, txt, strlen(txt));
	SetRect(&rc, x, y + KEY_HEIGHT * 1, x + 80, y + KEY_HEIGHT * 2);
	sprintf(txt, "<100");
	TextOutCenterLen(hdc, &rc, txt, strlen(txt));
	SetRect(&rc, x, y + KEY_HEIGHT * 2, x + 80, y + KEY_HEIGHT * 3);
	sprintf(txt, "<5");
	TextOutCenterLen(hdc, &rc, txt, strlen(txt));
	SetRect(&rc, x, y + KEY_HEIGHT * 3, x + 80, y + KEY_HEIGHT * 4);
	sprintf(txt, "<10");
	TextOutCenterLen(hdc, &rc, txt, strlen(txt));
	SetRect(&rc, x, y + KEY_HEIGHT * 4, x + 80, y + KEY_HEIGHT * 5);
	sprintf(txt, "<10");
	TextOutCenterLen(hdc, &rc, txt, strlen(txt));
	SetRect(&rc, x, y + KEY_HEIGHT * 5, x + 80, y + KEY_HEIGHT * 6);
	sprintf(txt, "0");
	TextOutCenterLen(hdc, &rc, txt, strlen(txt));
	x += 80;
	SetRect(&rc, x, y , x + 80, y + KEY_HEIGHT);
	sprintf(txt, "1 '");
	TextOutCenterLen(hdc, &rc, txt, strlen(txt));
	SetRect(&rc, x + 4, y + KEY_HEIGHT * 1 + 2, x + 80 - 4, y + KEY_HEIGHT * 2);
	sprintf(txt, "100-199,>160");
	TextOutWrap(hdc, &rc, txt, strlen(txt));
	SetRect(&rc, x, y + KEY_HEIGHT * 2, x + 80, y + KEY_HEIGHT * 3);
	sprintf(txt, "5-9,>30");
	TextOutCenterLen(hdc, &rc, txt, strlen(txt));
	SetRect(&rc, x, y + KEY_HEIGHT * 3, x + 80, y + KEY_HEIGHT * 4);
	sprintf(txt, "10-14");
	TextOutCenterLen(hdc, &rc, txt, strlen(txt));
	SetRect(&rc, x, y + KEY_HEIGHT * 4, x + 80, y + KEY_HEIGHT * 5);
	sprintf(txt, "10-14");
	TextOutCenterLen(hdc, &rc, txt, strlen(txt));
	SetRect(&rc, x, y + KEY_HEIGHT * 5, x + 80, y + KEY_HEIGHT * 6);
	sprintf(txt, "1-2");
	TextOutCenterLen(hdc, &rc, txt, strlen(txt));
	x += 80;
	SetRect(&rc, x, y , x + 80, y + KEY_HEIGHT);
	sprintf(txt, "2 '");
	TextOutCenterLen(hdc, &rc, txt, strlen(txt));
	SetRect(&rc, x, y + KEY_HEIGHT * 1, x + 80, y + KEY_HEIGHT * 2);
	sprintf(txt, "120-160");
	TextOutCenterLen(hdc, &rc, txt, strlen(txt));
	SetRect(&rc, x, y + KEY_HEIGHT * 2, x + 80, y + KEY_HEIGHT * 3);
	sprintf(txt, "10-30");
	TextOutCenterLen(hdc, &rc, txt, strlen(txt));
	SetRect(&rc, x, y + KEY_HEIGHT * 3, x + 80, y + KEY_HEIGHT * 4);
	sprintf(txt, ">=15");
	TextOutCenterLen(hdc, &rc, txt, strlen(txt));
	SetRect(&rc, x, y + KEY_HEIGHT * 4, x + 80, y + KEY_HEIGHT * 5);
	sprintf(txt, ">=15");
	TextOutCenterLen(hdc, &rc, txt, strlen(txt));
	SetRect(&rc, x, y + KEY_HEIGHT * 5, x + 80, y + KEY_HEIGHT * 6);
	sprintf(txt, ">3");
	TextOutCenterLen(hdc, &rc, txt, strlen(txt));
	x += 80;
	SetRect(&rc, x, y , x + 80, y + KEY_HEIGHT);
	sprintf(txt, "%s", LoadString(STR_DLG_ANLS_RESULT));
	TextOutCenterLen(hdc, &rc, txt, strlen(txt));
	SetRect(&rc, x, y + KEY_HEIGHT * 1, x + 80, y + KEY_HEIGHT * 2);
	sprintf(txt, "%d", AnlsRet.fhr_JX);
	TextOutCenterLen(hdc, &rc, txt, strlen(txt));
	SetRect(&rc, x, y + KEY_HEIGHT * 2, x + 80, y + KEY_HEIGHT * 3);
	sprintf(txt, "%d", AnlsRet.fhr_ZV);
	TextOutCenterLen(hdc, &rc, txt, strlen(txt));
	SetRect(&rc, x, y + KEY_HEIGHT * 3, x + 80, y + KEY_HEIGHT * 4);
	sprintf(txt, "%d", AnlsRet.fasttime);
	TextOutCenterLen(hdc, &rc, txt, strlen(txt));
	SetRect(&rc, x, y + KEY_HEIGHT * 4, x + 80, y + KEY_HEIGHT * 5);
	sprintf(txt, "%d", AnlsRet.fasthigh);
	TextOutCenterLen(hdc, &rc, txt, strlen(txt));
	SetRect(&rc, x, y + KEY_HEIGHT * 5, x + 80, y + KEY_HEIGHT * 6);
	sprintf(txt, "%d", AnlsRet.fm_nr);
	TextOutCenterLen(hdc, &rc, txt, strlen(txt));
//	x += 80;
//	SetRect(&rc, x, y , x + 80, y + KEY_HEIGHT);
//	sprintf(txt, "%s", LoadString(STR_DLG_ANLS_SCORE));
//	TextOutCenterLen(hdc, &rc, txt, strlen(txt));

	x += 88;
	y1 = y + 8;
	y += KEY_HEIGHT * 6 + DLG_OFFSET;
	sprintf(txt, "%s", LoadString(STR_DLG_ANLS_NAME));
	TextOut(hdc, x, y1, txt);
	y1 += STATIC_HEIGHT;
	sprintf(txt, "%s %4d:%02d", LoadString(STR_DLG_ANLS_TIME),
		AnlsRet.second / 60, AnlsRet.second % 60);
	TextOut(hdc, x, y1, txt);
	y1 += STATIC_HEIGHT;
	sprintf(txt, "%s %d%%", LoadString(STR_DLG_ANLS_VALID), AnlsRet.vld_pct);
	TextOut(hdc, x, y1, txt);
	y1 += STATIC_HEIGHT;
	
	struct tm *plocal_time;
	UINT32 time = AnlsRet.endtime - AnlsRet.second;
	plocal_time = localtime((const time_t *)&time);
	sprintf(txt, "%s: %02d:%02d:%02d", LoadString(STR_PRINT_TIME_START), 
		plocal_time->tm_hour, plocal_time->tm_min, plocal_time->tm_sec);
	TextOut(hdc, x, y1, txt);
	y1 += STATIC_HEIGHT;
	
	plocal_time = localtime((const time_t *)&AnlsRet.endtime);
	sprintf(txt, "%s: %02d:%02d:%02d", LoadString(STR_PRINT_TIME_END), 
		plocal_time->tm_hour, plocal_time->tm_min, plocal_time->tm_sec);
	TextOut(hdc, x, y1, txt);
	y1 += STATIC_HEIGHT;
	sprintf(txt, "%s", LoadString(STR_DLG_ANLS_ANALYSIS_RESULT));
	TextOut(hdc, x, y1, txt);
	x = DLG_OFFSET;
	sprintf(txt, "%s", LoadString(STR_DLG_ANLS_DIAGNOSIS));
	TextOut(hdc, x, y, txt);
	x = RECTW(pdc->DevRC) * 2 / 4;
	y = RECTH(pdc->DevRC) - STATIC_HEIGHT;
	sprintf(txt, "%s", LoadString(STR_DLG_ANLS_SIGNATURE));
	TextOut(hdc, x, y, txt);
	x = RECTW(pdc->DevRC) * 3 / 4;
	sprintf(txt, "%s", LoadString(STR_DLG_ANLS_DATE));
	TextOut(hdc, x, y, txt);
}


INT32 AnalyResultDlgProc (HWND hWnd, INT32 message, WPARAM wParam, LPARAM lParam)
{
	HWND hCtrl;
	switch(message)
	{
		case MSG_INITDIALOG:
			if (hCtrl = GetDlgItem(hWnd, IDC_ANALYSIS_RESULT_INFO_L))
			{
				SetWindowBkColor(hCtrl, ((PCONTROL)hWnd)->iBkColor);
				SetWindowTextColor(hCtrl, PIXEL_black);
			}
			break;

		case MSG_SHOWWINDOW:
		{
			if (hCtrl = GetDlgItem(hWnd, IDC_ANALYSIS_RESULT_INFO_L))
			{
				SetWindowText(hCtrl, 0);
				HDC hdc = GetDC(hCtrl);
				SetBkColor(hdc, ((PWIN)hWnd)->iBkColor);
				DispAnalysisResult(hdc);
				ReleaseDC(hdc);
			}
		}
			break;

		case MSG_COMMAND:
			switch (LOWORD(wParam))
			{
				case IDC_ANALYSIS_RESULT_EXIT_B:
					EndDialog(hWnd, IDOK);
					return 0;
			}
			break;

		default:
			break;
	}
	return DefaultDialogProc (hWnd, message, wParam, lParam);
}

VOID AnalysisResultDialog(HANDLE hOwner)
{
	if (hOwner == MainScnHWnd)
		hOwner = 0;
	
	DLGTEMPLATE dlg_data = {
	   WS_ABSSCRPOS | WS_CAPTION | WS_BORDER | WS_MODALDLG, WS_NONE, 
	   0, 0, 700, 440,  STR_DLG_ANALY_RESULT, 0, NULL, 0L,
	};

	BUTTONDATA  btn_exit  = gBtn_Exit;


	CTRLDATA ctrl_data [] =
	{
		{ CTRL_STATIC,  WS_VISIBLE | SS_SIMPLE, WS_EX_NONE,
			DLG_OFFSET, DLG_OFFSET, 700 - DLG_OFFSET * 2, 350,
			IDC_ANALYSIS_RESULT_INFO_L, STR_NULL,	   0L, 0L},

		{ CTRL_BUTTON,  WS_VISIBLE | WS_TABSTOP | BS_ICON, WS_EX_NONE,
			700 - EXIT_ICON_WIDTH - DLG_OFFSET,
			-(DLG_MENU_HIGHT + EXIT_ICON_HIGH) / 2,
			EXIT_ICON_WIDTH,  EXIT_ICON_HIGH,
			IDC_ANALYSIS_RESULT_EXIT_B, 0, 0L, 0L} 
	};
	
	INT16 i, loops;
	loops = TABLESIZE(ctrl_data);
	WNDMEM   wndMem;
	
	wndMem.pMainWin = GetMainWndMem(IDD_ANALYSIS_RESULT);
	wndMem.pControl = GetCtrlWndMem(IDC_ANALYSIS_RESULT_FIRST);
	wndMem.ctrlNum  = TABLESIZE(ctrl_data);
	wndMem.task	 = SysGui_HTSK;
	
	dlg_data.controlnr = loops;
	dlg_data.controls  = ctrl_data;

//	SetCtrlDataAddData2(ctrl_data, loops,
//		IDC_ANALYSIS_RESULT_SAVE_B, (UINT32)&btn_save);
//	SetCtrlDataAddData2(ctrl_data, loops,
//		IDC_ANALYSIS_RESULT_PRNT_B, (UINT32)&btn_prnt);
	SetCtrlDataAddData2(ctrl_data, loops,
		IDC_ANALYSIS_RESULT_EXIT_B, (UINT32)&btn_exit);

	DialogBoxIndirectParam(&dlg_data, hOwner,
		IDD_ANALYSIS_RESULT, AnalyResultDlgProc, 0, &wndMem);
}

VOID SetAnalyDlgCtrlStatus(HWND hWnd)
{
	if (!get_analysis_enable())
		return;
	HWND hCtrl;
//	if (hCtrl = GetDlgItem(hWnd, IDC_ANALY_SETUP_COLLECT_LB))
//	{
//		EnableWindow(hCtrl, AnalyConfig.enbType);
//	}
//	if (hCtrl = GetDlgItem(hWnd, IDC_ANALY_SETUP_AUTO_LB))
//	{
//		EnableWindow(hCtrl, AnalyConfig.enbAuto);
//	}
	if (!hWnd) return;
	
	if (hCtrl = GetDlgItem(hWnd, IDC_ANALY_SETUP_START_B))
	{
		EnableWindow(hCtrl, AnalyConfig.enbStart);
	}
	if (hCtrl = GetDlgItem(hWnd, IDC_ANALY_SETUP_DONE_B))
	{
		EnableWindow(hCtrl, AnalyConfig.enbDone);
	}
//	if (hCtrl = GetDlgItem(hWnd, IDC_ANALY_SETUP_SHOW_B))
//	{
//		EnableWindow(hCtrl, AnalyConfig.enbShow);
//	}
}

VOID PutAnalysisResultIntoFile(VOID)
{
	if (!get_analysis_enable())
		return;
	FETAL_ANSIS result;
	ARET_SAVE *ptr = (ARET_SAVE*)result.buffer;
	memcpy(result.name, PTNT_ANSS_HEAD, strlen(PTNT_ANSS_HEAD));
	result.len = FIELD_OFFSET(FETAL_ANSIS, buffer[0]) + sizeof(ARET_SAVE);
	result.type = 1;
	memcpy(result.buffer, &AnlsRet, sizeof(ARET_SAVE));
	
	FmsPtr->PutAnsis(FmsPtr, &result);
}

VOID InitDiagnoseData(VOID)
{
	if (!get_analysis_enable())
		return;
	SetAnalySendFlag(FALSE);
	while(AnalyConfig.putFlag)ms_sleep(OS_TICK_TIME);
	sFhrDiagnose.len = 0;
}

VOID AnalyDlg_Init(HWND hWnd)
{
	HWND hCtrl;
	INT32 i;
	for (i = IDC_ANALY_SETUP_FIRST; i < IDC_ANALY_SETUP_EXIT_B; i++)
	{
		if (hCtrl = GetDlgItem(hWnd, i))
		{
			SetWindowBkColor(hCtrl, ((PCONTROL)hWnd)->iBkColor);
		}
	}
	SetAnalyDlgCtrlStatus(hWnd);
	shAnalyDlg = hWnd;
}

INT32 AnalyDlgProc (HWND hWnd, INT32 message, WPARAM wParam, LPARAM lParam)
{
	switch(message)
	{
		case MSG_INITDIALOG:
			AnalyDlg_Init(hWnd);
			break;

		case MSG_COMMAND:
			switch (LOWORD(wParam))
			{
				case IDC_ANALY_SETUP_START_B:
					InitDiagnoseData();
					SetAnalyDlgCtrlStatus(hWnd);
					return 0;

				case IDC_ANALY_SETUP_DONE_B:
					if (!AnalyConfig.sendFlag)
					{
						EndPatientFile();
						SetAnalyDlgCtrlStatus(hWnd);
						shAnalyDlg = 0;
						MessageBox(hWnd, STR_MSGBOX_PRO_ANALY, 0,
									((PWIN)hWnd)->caption, 
									MB_ALIGNCENTER | MB_OK, SysGui_HTSK);
						EndDialog(hWnd, IDOK);
					}
					return 0;

//				case IDC_ANALY_SETUP_SHOW_B:
//					if (!AnalyConfig.sendFlag)
//					{
//						shAnalyDlg = 0;
//						AnalysisResultDialog(hWnd);
//						shAnalyDlg = hWnd;
//					}
//					return 0;

				case IDC_ANALY_SETUP_EXIT_B:
					shAnalyDlg = 0;
					EndDialog(hWnd, IDOK);
					return 0;
			}
			break;

		default:
			break;
	}
	return DefaultDialogProc (hWnd, message, wParam, lParam);
}


VOID AnalysisDialog(HANDLE hOwner)
{
	if (!get_analysis_enable())
		return;
	if (hOwner == MainScnHWnd)
		hOwner = 0;

	enum __dialog_size{
		WIDTH1  = 120,
		WIDTH2  = 100,
		WIDTH3  = WIDTH1 + DLG_OFFSET + WIDTH2,
		HEIGHT  = KEY_HEIGHT,
		COLUMN1 = DLG_OFFSET,
		COLUMN2 = DLG_OFFSET * 2 + WIDTH1,
		LABLE_OFFSET = (HEIGHT - STATIC_HEIGHT) / 2,
		ROW_LINE1 = 1 * DLG_OFFSET + 0 * HEIGHT,
		ROW_LINE2 = 2 * DLG_OFFSET + 1 * HEIGHT,
		ROW_LINE3 = 3 * DLG_OFFSET + 2 * HEIGHT,
		ROW_LINE4 = 4 * DLG_OFFSET + 3 * HEIGHT,
		DLG_W = COLUMN2 + WIDTH2 + DLG_OFFSET,
		DLG_H = ROW_LINE4 + DLG_OFFSET + DLG_MENU_HIGHT + HEIGHT
	}DLGSIZE;
	
	DLGTEMPLATE dlg_data = {
	   WS_ABSSCRPOS | WS_CAPTION | WS_BORDER | WS_MODALDLG, WS_NONE, 
	   0, 0, DLG_W, DLG_H,  STR_DLG_ANALY_FUNC, 0, NULL, 0L,
	};

	BUTTONDATA  btn_start = { 0 };
	BUTTONDATA  btn_done  = { 0 };
	BUTTONDATA  btn_exit  = gBtn_Exit;

	CTRLDATA ctrl_data [] =
	{
		{ CTRL_STATIC,  WS_VISIBLE | SS_SIMPLE, WS_EX_NONE,
			COLUMN1, ROW_LINE1, WIDTH3, STATIC_HEIGHT,
			IDC_ANALY_SETUP_INFO_DATA_L, STR_NULL,   0L, 0L},
		{ CTRL_STATIC,  WS_VISIBLE | SS_SIMPLE, WS_EX_NONE,
			COLUMN1, ROW_LINE1 + STATIC_HEIGHT-2, WIDTH3, STATIC_HEIGHT,
			IDC_ANALY_SETUP_INFO_VALID_L, STR_NULL, 0L, 0L},

		{ CTRL_BUTTON,  WS_VISIBLE | WS_TABSTOP, WS_EX_NONE,
			COLUMN1, ROW_LINE3, WIDTH3, KEY_HEIGHT,
			IDC_ANALY_SETUP_START_B, STR_DLG_ANALY_RESTART, 0L, 0L},
		{ CTRL_BUTTON,  WS_VISIBLE | WS_TABSTOP, WS_EX_NONE,
			COLUMN1, ROW_LINE4, WIDTH3, KEY_HEIGHT,
			IDC_ANALY_SETUP_DONE_B, STR_DLG_ANALY_DONE, 0L, 0L},

		{ CTRL_BUTTON,  WS_VISIBLE | WS_TABSTOP | BS_ICON, WS_EX_NONE,
			DLG_W - EXIT_ICON_WIDTH - DLG_OFFSET,
			-(DLG_MENU_HIGHT + EXIT_ICON_HIGH) / 2,
			EXIT_ICON_WIDTH,  EXIT_ICON_HIGH,
			IDC_ANALY_SETUP_EXIT_B, STR_DLG_EXIT, 0L, 0L} 
	};
	
	INT16 i, loops;
	loops = TABLESIZE(ctrl_data);
	WNDMEM   wndMem;
	
	wndMem.pMainWin = GetMainWndMem(IDD_ANALY_SETUP);
	wndMem.pControl = GetCtrlWndMem(IDC_ANALY_SETUP_FIRST);
	wndMem.ctrlNum  = TABLESIZE(ctrl_data);
	wndMem.task	 = SysGui_HTSK;
	
	dlg_data.controlnr = loops;
	dlg_data.controls  = ctrl_data;

//	SetCtrlDataAddData2(ctrl_data, loops,
//		IDC_ANALY_SETUP_COLLECT_LB, (UINT32)&lb_type);
//	SetCtrlDataAddData2(ctrl_data, loops,
//		IDC_ANALY_SETUP_AUTO_LB, (UINT32)&lb_auto);
	SetCtrlDataAddData2(ctrl_data, loops,
		IDC_ANALY_SETUP_START_B,	(UINT32)&btn_start);
	SetCtrlDataAddData2(ctrl_data, loops,
		IDC_ANALY_SETUP_DONE_B,	 (UINT32)&btn_done);
//	SetCtrlDataAddData2(ctrl_data, loops,
//		IDC_ANALY_SETUP_SHOW_B,	 (UINT32)&btn_show);
	SetCtrlDataAddData2(ctrl_data, loops,
		IDC_ANALY_SETUP_EXIT_B,	 (UINT32)&btn_exit);

	DialogBoxIndirectParam(&dlg_data, hOwner,
		IDD_ANALY_SETUP, AnalyDlgProc, 0, &wndMem);
//	prinfo("set shAnalyDlg = 0\r\n");
	shAnalyDlg = 0;
}

VOID AnalyInfoUpdate(VOID)
{
	int dataPercent  = ABS(sFhrDiagnose.len) * 100 / FHR_DIAGNOSE_SEND_FHR_NUM;
	int validPercent = AnalyConfig.nr_valid * 100 / FHR_DIAGNOSE_SEND_FHR_NUM;
	
	if (!shAnalyDlg) return;
	if (!get_analysis_enable())
		return;

	HWND hCtrl;
	HDC  hdc;
	RECT rc;
	INT32 right;
	GAL_PIXEL brColor;
	UCHAR szInfo[32];
	if (hCtrl = GetDlgItem(shAnalyDlg, IDC_ANALY_SETUP_INFO_DATA_L))
	{
		SetWindowText(hCtrl, 0);
		if (dataPercent < 50)
		{
			brColor = PIXEL_cyan;
		}
		else if (dataPercent < 99)
		{
			brColor = PIXEL_yellow;
		}
		else if (dataPercent > 98)
		{
			brColor = PIXEL_green;
		}
		GetClientRect(hCtrl, &rc);
		right = (rc.right - 4) * dataPercent / 100;
		hdc = GetDC(hCtrl);
		SetPenColor(hdc, PIXEL_black);
		Rect(hdc, rc.left, rc.top, rc.right, rc.bottom);
		Rect(hdc, rc.left + 1, rc.top + 1, rc.right - 1, rc.bottom - 1);
		brColor = SetBrushColor(hdc, brColor);
		FillRect(hdc, rc.left + 2, rc.top + 2, right, rc.bottom - 4);
		SetBrushColor(hdc, brColor);
		SetBkColor(hdc, PIXEL_transparent);
		SetTextColor(hdc, PIXEL_black);
		sprintf(szInfo, "%s:%3d%%",
			LoadString(STR_DLG_ANALY_COLLECT), dataPercent);
		TextOut(hdc, 1, 4, szInfo);
		ReleaseDC(hdc);
	}
	if (hCtrl = GetDlgItem(shAnalyDlg, IDC_ANALY_SETUP_INFO_VALID_L))
	{
		SetWindowText(hCtrl, 0);
		if (validPercent < 50)
		{
			brColor = PIXEL_cyan;
		}
		else if (validPercent < 99)
		{
			brColor = PIXEL_yellow;
		}
		else if (validPercent > 98)
		{
			brColor = PIXEL_green;
		}
		GetClientRect(hCtrl, &rc);
		right = (rc.right - 4) * validPercent / 100;
		hdc = GetDC(hCtrl);
		SetPenColor(hdc, PIXEL_black);
		Rect(hdc, rc.left, rc.top, rc.right, rc.bottom);
		Rect(hdc, rc.left + 1, rc.top + 1, rc.right - 1, rc.bottom - 1);
		brColor = SetBrushColor(hdc, brColor);
		FillRect(hdc, rc.left + 2, rc.top + 2, right, rc.bottom - 4);
		SetBrushColor(hdc, brColor);
		SetBkColor(hdc, PIXEL_transparent);
		SetTextColor(hdc, PIXEL_black);
		sprintf(szInfo, "%s:%3d%%",
			LoadString(STR_DLG_ANALY_VALID), validPercent);
		TextOut(hdc, 1, 4, szInfo);
		ReleaseDC(hdc);
	}
	if (!AnalyConfig.sendFlag)
	{
		SetAnalySendFlag(FALSE);
		SetAnalyDlgCtrlStatus(shAnalyDlg);
	}
//	if (hCtrl = GetDlgItem(shAnalyDlg, IDC_ANALY_SETUP_INFO_HELP_L))
//	{
//		SetWindowText(hCtrl, 0);
//	}
}

VOID FetalAnalysisPutValue(FHR_PARAMS *params)
{
	if (!get_analysis_enable())
		return;
	int i = sFhrDiagnose.len;
	INT16 fhr = (FhrConfig.mode == 1) ? params->fhr2 : params->fhr1;
	if (i == 0)
	{
		AnalyConfig.putFlag = TRUE;
		sFhrDiagnose.len++;
		AnalyConfig.putFlag = FALSE;
		ZeroMemory(&sFetalData, sizeof(sFetalData));
		sFetalData.frame.stx  = 0x55;
		sFetalData.frame.sync = 0xAA;
		sFetalData.frame.id   = 0x01;
		sFetalData.frame.fhr[i] = (fhr > 0) ? fhr : 0;
		sFetalData.frame.toco[i] = params->toco;
		AnalyConfig.nr_valid = 0;
		SetAnalySendFlag(FALSE);
	}
	if (i > 0 && i < FHR_DIAGNOSE_SEND_FHR_NUM)
	{
		
		AnalyConfig.putFlag = TRUE;
		sFhrDiagnose.len++;
		AnalyConfig.putFlag = FALSE;
		sFetalData.frame.fhr[i] = 
			((FhrConfig.mode == 1) ? params->fhr2 : params->fhr1);
		sFetalData.frame.toco[i] = params->toco;
		if ((sFetalData.frame.fhr[i] > 30 - 1)
			&& (AnalyConfig.nr_valid < FHR_DIAGNOSE_SEND_FHR_NUM))
		{
			AnalyConfig.nr_valid++;
		}
	}
	if (i == FHR_DIAGNOSE_SEND_FHR_NUM)
	{
		if (sFetalData.frame.fhr[0] > 30 - 1 && AnalyConfig.nr_valid)
			AnalyConfig.nr_valid--;
		for (i = 1; i < FHR_DIAGNOSE_SEND_FHR_NUM; i++)
		{
			sFetalData.frame.fhr[i - 1] = sFetalData.frame.fhr[i];
			sFetalData.frame.toco[i - 1] = sFetalData.frame.toco[i];
		}
		sFetalData.frame.fhr[i - 1]  =
			(FhrConfig.mode == 1) ? params->fhr2 : params->fhr1;
		sFetalData.frame.toco[i - 1] = params->toco;
		if ((sFetalData.frame.fhr[i - 1] > 30 - 1)
			&& (AnalyConfig.nr_valid < FHR_DIAGNOSE_SEND_FHR_NUM))
		{
			AnalyConfig.nr_valid++;
		}
	}
	sFhrDiagnose.nr_valid = AnalyConfig.nr_valid;
	AnalyInfoUpdate();
}

VOID AnalyInSecond(VOID)
{
	if (!get_analysis_enable())
		return;
	if (AnalyConfig.sendFlag)
	{
		AnalyConfig.waitCnt++;
		if (AnalyConfig.waitCnt++ > 24)
		{
			SetAnalySendFlag(FALSE);
			if (shAnalyDlg)
				SetAnalyDlgCtrlStatus(shAnalyDlg);
		}
	}
	else if (AnalyConfig.waitCnt > 0)
	{
		SetAnalySendFlag(FALSE);
		if (shAnalyDlg)
			SetAnalyDlgCtrlStatus(shAnalyDlg);
	}
}

char get_analysis_enable2(void)
{
	static char key = 0;
	const short byte = 195;
	const char bits = 1;
	if (!key)
	{
		FILE *fp = fopen("zondan", "rb");
		if (fp)
		{
			if (fseek(fp, byte, SEEK_SET))
			{
				key = ~(0x01 << bits);
			}
			else
			{
				if (1 != fread(&key, 1, 1, fp))
				{
					key = ~(0x01 << bits);
				}
			}
			fclose(fp);
		}
		else
		{
			key = ~(0x01 << bits);
		}
	}
	return ((key >> bits) & 0x01);
}

static int sAnalyFlag = -1;
char get_analysis_enable(void)
{
	if (sAnalyFlag < 0)
	{
		FILE *fp = fopen("zondan", "rb");
		char flag;
		if (!fp)
			return FALSE;
		if (0 >= fread(&flag, sizeof(flag), 1, fp))
		{
			flag = 0;
		}
		fclose(fp);
		sAnalyFlag = (flag > 0);
	}
	return ((get_analysis_enable2()) && sAnalyFlag);
}

char set_analysis_enable(char enb)
{
	FILE *fp = fopen("zondan", "rb+");
	char flag = (enb > 0);
	char ret = FALSE;
	if (!fp)
		return ret;
	ret = (0 < fwrite(&flag, sizeof(flag), 1, fp));
	fclose(fp);
	if (ret)
	{
		sAnalyFlag = flag;
	}
	return ret;
}

