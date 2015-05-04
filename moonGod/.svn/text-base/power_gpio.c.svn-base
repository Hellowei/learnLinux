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
#define   POWER_GPIO_GLOBALS										
#include "includes.h"
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/fcntl.h>


//红色报警灯控制
//GPK7 -- /sys/class/leds/led6/brightness
int Red_led_gpio_value(int pin)
{
#if QVFB_DEBUG
		return 0;
#endif
	int fd = open("/sys/class/leds/led6/brightness", O_WRONLY);
	if (fd < 0) 
	{
		perror("open red led failed\n");
		return -1;
	}
	if (pin == 1) 
	{
		write(fd, "255", 3);
	}
	else
	{
		write(fd, "0", 1);
	}
	close(fd);

	return 0;
}


//黄色报警灯控制
//GPK8 -- /sys/class/leds/led7/brightness
int Yellow_led_gpio_value(int pin)
{
	return Red_led_gpio_value(pin);
	int fd = open("/sys/class/leds/led7/brightness", O_WRONLY);
	if (fd < 0) 
	{
		perror("open yellow led failed\n");
		return -1;
	}

	if (pin == 1) 
	{
		write(fd, "255", 3);
	}
	else
	{
		write(fd, "0", 1);
	}
	close(fd);

	return 0;
}


//蓝色报警灯控制
//GPK9 -- /sys/class/leds/led8/brightness
int Blue_led_gpio_value(int pin)
{
#if QVFB_DEBUG
			return 0;
#endif
	int fd = open("/sys/class/leds/led8/brightness", O_WRONLY);
	
	if (fd < 0) 
	{
		perror("open blue led failed\n");
		return -1;
	}
	if (pin == 1) 
	{
		write(fd, "255", 3);
	}
	else
	{
		write(fd, "0", 1);
	}
	close(fd);
	return 0;
}


//NIBP模块患者模式控制。高电平，成人模式；低电平，新生儿模式
//GPB0 -- /sys/class/leds/led9/brightness
int NibpMode_ctrl_gpio_value(int pin)
{
#if QVFB_DEBUG
			return 0;
#endif
	int fd = open("/sys/class/leds/led9/brightness", O_WRONLY);

	if (fd < 0) 
	{
		perror("open nibp mode failed\n");
		return -1;
	}
	if (pin == 1) 
	{
		write(fd, "255", 3);
	}
	else
	{
		write(fd, "0", 1);
	}
	close(fd);
	return 0;
}


//音频放大器关闭，高电平，关闭音频输出。
//GPB4 -- /sys/class/leds/led3/brightness
int Speaker_ctrl_gpio_value(int pin)
{
#if QVFB_DEBUG
			return 0;
#endif
	int fd = open("/sys/class/leds/led3/brightness", O_WRONLY);

	if (fd < 0) 
	{
		perror("open speaker ctrl failed\n");
		return -1;
	}
	if (pin == 1) 
	{
		write(fd, "255", 3);
	}
	else
	{
		write(fd, "0", 1);
	}
	close(fd);
	return 0;	
}


//LCD电源控制使能控制、高电平，打开LCD电源
///GPA24 -- sys/class/leds/led5/brightness
int LcdPowerCtrl_ctrl_gpio_value(int pin)
{
#if QVFB_DEBUG
			return 0;
#endif
	int fd = open("sys/class/leds/led5/brightness", O_WRONLY);

	if (fd < 0)
	{
		perror("open lcd power ctrl failed\n");
		return -1;
	}
	if (pin == 1) 
	{
		write(fd, "255", 3);
	}
	else
	{
		write(fd, "0", 1);
	}
	close(fd);
	return 0;	
}


//LCD显示控制使能，高电平，打开LCD显示
//GPA23 -- /sys/class/leds/led10/brightness
int LcdDispEn_ctrl_gpio_value(int pin)
{
#if QVFB_DEBUG
			return 0;
#endif
	int fd = open("/sys/class/leds/led10/brightness", O_WRONLY);

	if (fd < 0) 
	{
		perror("open lcd disp ctrl failed\n");
		return -1;
	}
	if (pin == 1) 
	{
		write(fd, "255", 3);
	}
	else
	{
		write(fd, "0", 1);
	}
	close(fd);
	return 0;	
}


//VGA输出使能控制，高电平，VGA输出使能。
//GPM0 -- /sys/class/leds/led15/brightness
int VgaEn_ctrl_gpio_value(int pin)
{
#if QVFB_DEBUG
			return 0;
#endif
	int fd = open("/sys/class/leds/led15/brightness", O_WRONLY);

	if (fd < 0) 
	{
		perror("open vga ctrl failed\n");
		return -1;
	}
	if (pin == 1) 
	{
		write(fd, "255", 3);
	}
	else
	{
		write(fd, "0", 1);
	}
	close(fd);
	return 0;	
}


//LCD背光开关。高电平，打开背光，低电平，背光关闭。
//GPB1 -- /sys/class/leds/led1/brightness
int BacklightEn_ctrl_gpio_value(int pin)
{
#if QVFB_DEBUG
			return 0;
#endif
	int fd = open("/sys/class/leds/led1/brightness", O_WRONLY);

	if (fd < 0) 
	{
		perror("open backlight enable ctrl failed\n");
		return -1;
	}
	if (pin == 1) 
	{
		write(fd, "255", 3);
	}
	else
	{
		write(fd, "0", 1);
	}
	close(fd);
	return 0;	
}


//护士呼叫功能输出。高电平，呼叫输出。
//GPB3 -- /sys/class/leds/led2/brightness
int NurseCall_ctrl_gpio_value(int pin)
{
#if QVFB_DEBUG
			return 0;
#endif
	int fd = open("/sys/class/leds/led2/brightness", O_WRONLY);

	if (fd < 0) 
	{
		perror("open nurse call ctrl failed\n");
		return -1;
	}
	if (pin == 1)
	{
		write(fd, "255", 3);
	}
	else
	{
		write(fd, "0", 1);
	}
	close(fd);
	return 0;	
}


//背光亮度控制。
//当背光为模拟信号控制模式下：GPK0到GPK3四个GPIO可以组合成16种亮度，0b’0000，亮度为零，0b’1111，亮度最大。
//当背光为数字控制模式下：
//GPK0为PWM输出，其它管脚不起作用，PWM波形频率为10KHz，占空比从1%到100%可以控制。
//GPK0 -- /sys/class/leds/led11/brightness
//GPK1 -- /sys/class/leds/led12/brightness
//GPK2 -- /sys/class/leds/led13/brightness
//GPK3 -- /sys/class/leds/led14/brightness
int BacklightLevOnA_ctrl_gpio_value(int bright)
{
#if QVFB_DEBUG
			return 0;
#endif
	int   array_fd[4];
	int   i;

	array_fd[0] = open("/sys/class/leds/led11/brightness", O_WRONLY);
	array_fd[1] = open("/sys/class/leds/led12/brightness", O_WRONLY);
	array_fd[2] = open("/sys/class/leds/led13/brightness", O_WRONLY);
	array_fd[3] = open("/sys/class/leds/led14/brightness", O_WRONLY); 
	if ((array_fd[0] < 0) || (array_fd[1] < 0) || (array_fd[2] < 0) || (array_fd[3] < 0))
	{
		perror("open backlight Level ctrl failed\n");
		return -1;
	}
	for (i = 0; i < 4; i++)
	{
		if (bright & 0x01)
		{
			write(array_fd[i], "255", 3);
		}
		else
		{
			write(array_fd[i], "0", 1);
		}
		bright >>= 1;
	}
	for (i = 0; i < 4; i++)
	{
		close(array_fd[i]);
	}
	return 0;	
}


int BacklightLevOnD_ctrl_gpio_value(int bright)
{
#if QVFB_DEBUG
	return 0;
#endif
	int  fd = open("/sys/class/leds/led11/brightness", O_WRONLY);
	char szText[10];
	
	if (fd < 0) 
	{
		perror("open backlight Level ctrl failed\n");
		return -1;
	}
	sprintf(szText, "%d", bright);
	write(fd, szText, strlen(szText));
	close(fd);
	return 0;	
}
