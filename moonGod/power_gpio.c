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
#define   POWER_GPIO_GLOBALS										
#include "includes.h"
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/fcntl.h>


//��ɫ�����ƿ���
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


//��ɫ�����ƿ���
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


//��ɫ�����ƿ���
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


//NIBPģ�黼��ģʽ���ơ��ߵ�ƽ������ģʽ���͵�ƽ��������ģʽ
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


//��Ƶ�Ŵ����رգ��ߵ�ƽ���ر���Ƶ�����
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


//LCD��Դ����ʹ�ܿ��ơ��ߵ�ƽ����LCD��Դ
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


//LCD��ʾ����ʹ�ܣ��ߵ�ƽ����LCD��ʾ
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


//VGA���ʹ�ܿ��ƣ��ߵ�ƽ��VGA���ʹ�ܡ�
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


//LCD���⿪�ء��ߵ�ƽ���򿪱��⣬�͵�ƽ������رա�
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


//��ʿ���й���������ߵ�ƽ�����������
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


//�������ȿ��ơ�
//������Ϊģ���źſ���ģʽ�£�GPK0��GPK3�ĸ�GPIO������ϳ�16�����ȣ�0b��0000������Ϊ�㣬0b��1111���������
//������Ϊ���ֿ���ģʽ�£�
//GPK0ΪPWM����������ܽŲ������ã�PWM����Ƶ��Ϊ10KHz��ռ�ձȴ�1%��100%���Կ��ơ�
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
