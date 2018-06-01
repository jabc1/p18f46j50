#ifndef _TIME_H
#define _TIME_H
#include "p18f46j50.h"
#define		systemHZ 		27000
#define 	uchar 		unsigned char
#define		uint		unsigned int
typedef struct{
unsigned char year;
unsigned char month;
unsigned char day;
unsigned char hour;
unsigned char min;
unsigned char sec;
unsigned char week;
unsigned char mode;
unsigned char beep;
}frist_page;
typedef  struct{
	uchar flag_0;
	uchar flag_1;
	uchar flag_2;	
	uchar flag_3;
	uchar flag_4;
	uchar flag_5;
	uchar flag_6;
	uchar flag_7;
	uchar flag_8;
	uchar flag_9;
}Disp_flag;
typedef  struct{
	uint  ms;
	uchar s;
	uchar min;
	uchar hour;
	uchar s_flag;
	uchar min_flag;
	uchar hour_flag;
	uchar day;
	uchar month;
	uchar year;
	uchar T;
}Sys_Temp;
typedef struct{
	uint  day;
	uchar min;
	uchar hour;
}Start_Time;
typedef struct{
	uchar PD1;
	uchar PD2;
	uchar PD3;
	uchar PD4;
	uchar PD5;
	uchar PD6;
	uchar PD7;
	uchar PD8;
	uchar PD9;
	uchar PD10;
}PDx_Time;
typedef struct{
	uchar PD1Red;
	uchar PD1Green;
	uchar PD2Red;
	uchar PD2Green;
	uchar PD3Red;
	uchar PD3Green;
	uchar PD4Red;
	uchar PD4Green;
	uchar PD5Red;
	uchar PD5Green;
	uchar PD6Red;
	uchar PD6Green;
	uchar PD7Red;
	uchar PD7Green;
	uchar PD8Red;
	uchar PD8Green;
	uchar PD9Red;
	uchar PD9Green;
	uchar PD10Red;
	uchar PD10Green;
}PDx_Light;
void Init_Time1(void);
void delay_ms(int ms);
void delay_us(int us_25);
void Time1_S_Flag(void);



#endif

