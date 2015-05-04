#define TOUCH_GLOBALS
#include "includes.h"

#if _ENB_TOUCH
#ifndef UART_PORT_TOUCH
#define UART_PORT_TOUCH 				MonitorInfo.deviceInfo[DEV_TOUCH].port
#endif
#define TOUCH_PRESS_PACKET_HEADER		0x70
#define TOUCH_RELEASE_PACKET_HEADER		0x30

const int delayTicks = 5; //20;
static volatile TOUCHPOINT TouchPoint;
#define TOUCHCAL_PSIZE	5
#define TOUCHCAL_OFFSET	100
static const POINT CalPoints[5] = {
	{	TOUCHCAL_OFFSET,				TOUCHCAL_OFFSET					},
	{	SCREEN_WIDTH - TOUCHCAL_OFFSET,	TOUCHCAL_OFFSET					},
	{	SCREEN_WIDTH - TOUCHCAL_OFFSET,	SCREEN_HIGH - TOUCHCAL_OFFSET	},
	{	TOUCHCAL_OFFSET,				SCREEN_HIGH - TOUCHCAL_OFFSET	},
	{	SCREEN_WIDTH >> 1,				SCREEN_HIGH >> 1				}	};

BOOL CheckTouchPacket(UINT8 packet[6])
{
	int chk = 0;
	int i;
	for (i = 0; i < 6; i++)
		chk += packet[i];
	return (0xFF == LOBYTE(chk));
}

POINT *TouchMapScreenRect(POINT *pt)
{
	float x = 1.0 * pt->x;
	float y = 1.0 * pt->y;
	x = (x - MonitorConfig.offsetX) / MonitorConfig.scaleX;
	y = (y - MonitorConfig.offsetY) / MonitorConfig.scaleY;
//	printf("TouchMapScreenRect::MonitorConfig.offsetX...%d\n", MonitorConfig.offsetX);
//	printf("TouchMapScreenRect::MonitorConfig.offsetY...%d\n", MonitorConfig.offsetY);
//	printf("TouchMapScreenRect::MonitorConfig.scaleX...%f\n", MonitorConfig.scaleX);
//	printf("TouchMapScreenRect::MonitorConfig.scaleY...%f\n", MonitorConfig.scaleY);




//	printf("TouchMapScreenRect(%d, %d)\n", pt->x, pt->y);
	pt->x = (INT32)(x + 0.5);
	pt->y = (INT32)(y + 0.5);
//	printf("TouchMapScreenRect(%d, %d)\n", pt->x, pt->y);
	return pt;
}

VOID TouchCalibrationFillRect(UINT8 nr, CHAR r, CHAR g, CHAR b)
{
	nr = nr % TABLESIZE(CalPoints);
	GAL_COLOR c = {r,g,b,};
	DrewCircle(HDC_SCREEN, CalPoints[nr].x, CalPoints[nr].y, 10, &c);
	DrewCircle(HDC_SCREEN, CalPoints[nr].x, CalPoints[nr].y, 40, &c);
}

VOID TouchCalibrationInit(VOID)
{
    EnterStandby();
    MonitorInfo.touchCal = TRUE;
	TouchCalibrationFillRect(0, 0xFF, 0xFF, 0xFF);
}

VOID TouchCalibrationProcess(UINT8 pressed)
{
	static POINT CalPt[5] = {0};
	POINT pt = {TouchPoint.X, TouchPoint.Y};
	POINT *point = &pt;
	INT8	pointNum = MonitorInfo.touchCal - 1;
	INT16	 w = 5;
	INT16	 x1, y1;
	INT16	 x2, y2;
//	printf("TouchCalibrationProcess::MonitorInfo.touchCal:%d\n", MonitorInfo.touchCal);
	if (pressed)
	{
		return;
	}
	if (pointNum == 0)
	{
		CalPt[pointNum].x	= point->x;
		CalPt[pointNum].y = point->y;

		TouchCalibrationFillRect(pointNum, 255, 0, 0);
		TouchCalibrationFillRect(pointNum + 1, 255, 255, 255);

		MonitorInfo.touchCal++;
	}
	else if (pointNum < 5)
	{
//		printf("CalPt[pointNum - 1].x, point->x  %d, %d\n", CalPt[pointNum - 1].x, point->x);
//		printf("CalPt[pointNum - 1].y, point->y  %d, %d\n", CalPt[pointNum - 1].y, point->y);
		if (ABS(CalPt[pointNum - 1].x - point->x) < TOUCHCAL_OFFSET
			&& ABS(CalPt[pointNum - 1].y - point->y) < TOUCHCAL_OFFSET)
		{
			CalPt[pointNum - 1].x = point->x;
			CalPt[pointNum - 1].y = point->y;
			return;
		}
		else
		{
			CalPt[pointNum].x = point->x;
			CalPt[pointNum].y = point->y;

			TouchCalibrationFillRect(pointNum - 1, 0, 0, 0);
			TouchCalibrationFillRect(pointNum, 255, 0, 0);
			if (pointNum < 4)
			{
				TouchCalibrationFillRect(pointNum + 1, 255, 255, 255);
				MonitorInfo.touchCal++;
				return;
			}
		}
	}
	if (MonitorInfo.touchCal == 5)
	{
		MonitorConfig.scaleX  = (CalPt[2].x - CalPt[3].x);
		MonitorConfig.scaleX  /= (SCREEN_WIDTH - TOUCHCAL_OFFSET * 2);
		MonitorConfig.offsetX =
			(INT16)(CalPt[3].x - MonitorConfig.scaleX * 100);							
		MonitorConfig.scaleY  =
			(CalPt[3].y - CalPt[0].y) + (CalPt[2].y - CalPt[1].y);							
		MonitorConfig.scaleY  /= ((SCREEN_HIGH - TOUCHCAL_OFFSET * 2) * 2);
		MonitorConfig.offsetY =
			(INT16)((CalPt[0].y + CalPt[1].y) / 2 - MonitorConfig.scaleY * 100);
		TouchMapScreenRect(point);
		x1 = (INT16)point->x;
		y1 = (INT16)point->y;						
		fb_fillrect_ex(0, x1 - w, y1 - w, x1 + w, y1 + w, 255, 0, 0); 
		pointNum = -1;
		if ((ABS(CalPoints[4].x - x1) < 10)
			&& (ABS(CalPoints[4].y - y1) < 10))
		{
			if (!MonitorInfo.touchCalFlag)
			{
				MonitorInfo.touchCalFlag = TRUE;
				Save_Touch_Config();
			}
		}
		else
		{
			MonitorInfo.touchCalFlag = FALSE;
		}
		MonitorInfo.touchCal = 0;
		ExitStandby();
	}
}

VOID TouchProcess(VOID)
{
	if (MonitorInfo.touchCal)
	{
		TouchCalibrationProcess(TouchPoint.pressed);
		return;
	}
	if (MonitorInfo.touchCalFlag)
	{
		if (UpdateLocker != FALSE)
			return;

		PostMessage(SysGui_HTSK, MSG_USER_SYS_TOUCHMSG, (WPARAM)&TouchPoint, 0);

		return;
	}
	if (!TouchPoint.pressed)
	{
		if (_menu_lev > 0) {
			BacktoMainScreen();
		}
		else {
			INT32 ret = MessageBox(0, STR_MSGBOX_PRO_NOT_TOUCH_CALC,
				STR_MSGBOX_PRO_ENTER_TOUCH_CALC, STR_MSGBOX_SYSTEM_INFO,
				MB_YESNO, SysGui_HTSK);
			if (ret == IDYES)
			{
				TouchCalibrationInit();
			}
		}
	}
}

VOID TouchPackFound(UINT8 packet[6])
{
	static UINT8 count = 0;
	POINT pt;
	pt.x = MAKEWORD(packet[1], packet[2]);
	pt.y = MAKEWORD(packet[3], packet[4]);
	if (TOUCH_RELEASE_PACKET_HEADER == packet[0])
	{
		TouchPoint.pressed = 0;//!TouchPoint.pressed;
		count = 0;
		if (MonitorInfo.touchCalFlag)
		{
			TouchMapScreenRect(&pt);
			TouchPoint.Xs = pt.x;
			TouchPoint.Ys = pt.y;
		}
		TouchPoint.X = pt.x;
		TouchPoint.Y = pt.y;
		TouchProcess();
	}
	if (TOUCH_PRESS_PACKET_HEADER == packet[0])
	{
//		if (count < 10)
//			count++;
		TouchPoint.pressed++;
//		if (TouchPoint.pressed == FALSE && count > 2)
//			TouchPoint.pressed = TRUE;
		if (MonitorInfo.touchCalFlag)
		{
			TouchMapScreenRect(&pt);
		}
		TouchPoint.X = pt.x;
		TouchPoint.Y = pt.y;
//		if (count == 3)
		TouchProcess();
	}
}

BOOL InitTouchScreen(VOID)
{
	MonitorInfo.enableTouch = TRUE;
	MDL_UARTCFG ComCfg;
	ComCfg.baudRate = MapUartBPS(9600);
	ComCfg.parity   = PARITY_NO;
	ComCfg.dataBits = DBTS_8;
	ComCfg.stopBits = STOPBITS_1;
	MdlUartSetup(UART_PORT_TOUCH, &ComCfg);
	if (MdlUartOpen(UART_PORT_TOUCH))
	{
		return FALSE;
	}
	return TRUE;
}

void TouchServer(void *pdata)
{
	INT32 read = 0;
	UINT8 *pHead;
	UINT8 *pTail;
	UINT8 *pRead;
	UINT8 *pWrite;
	UINT8 *pTmp;
	UINT8 buffer[48];
	UINT8 cache[60];
	UINT8 packet[6];
	UINT8 diff = 0;
	INT8  i;
	INT8  j;
	INT8  count = 0;
	INT8  jitter = 0;
	pdata = pdata;
	pHead = &cache[0];
	pTail = &cache[sizeof(cache) - 1];
	pRead = pHead;
	pWrite = pRead;
	
	prinfo("TouchServer start!\n");
	while (TRUE)
	{
		UartRead(UART_PORT_TOUCH, buffer, sizeof(buffer), &read, 0);
		if (MonitorInfo.enableTouch)
		{
			if (read > 0)
			{
				for (i = 0; i < read; i++)
				{
//					printf("buffer[%02d] = %d\n", i, buffer[i]);
					*pWrite++ = buffer[i];
					if (pWrite > pTail)
						pWrite = pHead;
				}
				diff = (sizeof(cache) + pWrite - pRead) % sizeof(cache);
//				printf("diff = %d\n", diff);
				while (diff >= sizeof(packet))
				{
					if ((*pRead == TOUCH_PRESS_PACKET_HEADER)
						|| (*pRead == TOUCH_RELEASE_PACKET_HEADER))
					{
						// 可能找到包头了,尝试解包
//						printf("pRead:%p\n", pRead);
						pTmp = pRead;
						for (j = 0; j < 6; j++)
						{
							packet[j] = *pTmp++;
							if (pTmp > pTail)
								pTmp = pHead;
						}
						if (CheckTouchPacket(packet))
						{
							if (packet[0] == TOUCH_RELEASE_PACKET_HEADER)
							{
								if (jitter > 3 + 7)
								{
									TouchPackFound(packet);
									jitter = 0;
								}
								pTmp = pWrite;//clean cache;
								break;
							}
							else
							{
//								if (!TouchPoint.pressed)
									TouchPackFound(packet);
							}
							pRead = pTmp;
						}
						else if (++pRead > pTail)
							pRead = pHead;
					}
					else if (++pRead > pTail)
						pRead = pHead;

					diff = (sizeof(cache) + pWrite - pRead) % sizeof(cache);
				}
				count = 0;
			}			
			else
			{
				if (TouchPoint.pressed > 10)
				{
					count++;
					if (count > 5 + 5)
					{
						TouchPoint.pressed = FALSE;
						TouchPoint.Xs = TouchPoint.X;
						TouchPoint.Ys = TouchPoint.Y;
						TouchProcess();
						jitter = 0;
					}
				}
			}
		}
		if (jitter < 4 + 6)jitter++;
		ms_sleep(delayTicks);
		if (KillSignal)
		{
			KillSignal++;
			break;
		}
	}
	if (KillSignal > 1)
		KillSignal--;
	prinfo("the end\n");
}
#endif

