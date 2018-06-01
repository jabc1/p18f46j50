#ifndef _TEST_FUNCTION_H
#define _TEST_FUNCTION_H
#define 	SettingTiem			0xb0
#define		SettingMode			0xb1
#define		SettingBeep			0xb2
#define		Query_fristpage		0xc1
#define		Query_Systiem		0xc2
void Test_Uart(void);
void Test_Show(void);
void Test_74HC595(void);
void Test_show_7(int temp,char PDx);
#endif



