#ifndef _SHOW_FUNCTION_H
#define _SHOW_FUNCTION_H
typedef struct{
unsigned char Start_flag;
unsigned char Result_flag;
unsigned char End_flag;
}Show_flag;
typedef struct{
	unsigned char SysTimeflag;
	unsigned char timeflag;
	unsigned char modeflag;
	unsigned char beepflag;
	unsigned char firstpage;
}Set_flag;
typedef struct{
unsigned char PD1;
unsigned char PD2;
unsigned char PD3;
unsigned char PD4;
unsigned char PD5;
unsigned char PD6;
unsigned char PD7;
unsigned char PD8;
unsigned char PD9;
unsigned char PD10;
}ST_flag;
unsigned char decimal_bcd(unsigned char decimal);
void Disp_function_0_0_0(void);
void Disp_function_0_0_1(void);
void Disp_function_0_0_2(void);
void Disp_function_0_0_3(void);
void Disp_function_0_0_4(void);
void Disp_function_0_0_5(void);
void Disp_function_0_0_6(void);
void Disp_function_0_0_7(void);
void Disp_function_0_0_8(void);
void Disp_function_0_0_9(void);
void Disp_function_0_1_0(void);
void Disp_function_0_1_1(void);
void Disp_function_0_1_2(void);
void Disp_function_0_1_3(void);
void Disp_function_0_1_3_0(void);
void Disp_function_0_1_3_1(void);
void Disp_function_0_1_3_2(void);
void Disp_function_0_1_3_3(void);
void Disp_function_0_1_3_4(void);
void Disp_function_0_1_3_5(void);

void Disp_function_0_1_4(void);
void Disp_function_0_1_5(void);
void Disp_function_0_1_6(void);
void Disp_function_0_1_7(void);
void Disp_function_0_1_8(void);
void Disp_function_0_1_9(void);

void Disp_function_0_2_0(void);
void Disp_function_0_2_0_0(void);
void Disp_function_0_2_0_1(void);
void Disp_function_0_2_0_2(void);
void Disp_function_0_2_0_3(void);
void Disp_function_0_2_0_4(void);
void Disp_function_0_2_0_5(void);
void Disp_function_0_2_0_6(void);
void Disp_function_0_2_0_7(void);
void Disp_function_0_2_1(void);
void Disp_function_0_2_2(void);
void Disp_function_0_2_3(void);
void Disp_function_0_2_4(void);
void Disp_function_0_2_5(void);
void Disp_function_0_2_6(void);
void Disp_function_0_2_7(void);
void Disp_function_0_2_8(void);
void Disp_function_0_2_9(void);



void Disp_Qurey_info(void);
void Disp_PD_Time();
void Disp_clear_all(void);
void Disp_Time(char h,int c);
void U_transfer(unsigned char temp);
void onKeyUpFlag(void);
void onKeyDownFlag(void);
void onKeyOkFlag(void);
void onKey12Flag(void);
void onKey12(void);
void onKeyUp(void);
void onKeyDown(void);
void onKeyOk(void);
void KeyUp_Confirm(void);
void KeyDown_Confirm(void);
void key_scan(void);
void Disp_clear_xy(uchar h1,uchar h2,int c1,int c2,char color);
unsigned char increaceNumberMaxMin(unsigned char val, unsigned char max, unsigned char min);
unsigned char increaceNumberMax(unsigned char val, unsigned char max);
unsigned char decreaceNumberMaxMin(unsigned char val, unsigned char max, unsigned char min);
unsigned char decreaceNumberMax(unsigned char val, unsigned char max);
unsigned char getMaxDaysOfMonth(unsigned int year, unsigned char month);






#endif










