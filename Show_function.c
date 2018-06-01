#include "Includeh.h"
extern frist_page			Frist_Info;
extern PDx_Time	PDx_result_flag;
extern PDx_Time		PDx_result;
extern unsigned char test_flag111;
extern Start_Time		Time_info;
extern Sys_Temp		Sys_count;
extern PDx_Time		PDx_start;
extern PDx_Time		PDx_end;
extern PDx_Time		PDx_flag;
extern volatile RECEIVE_BUF Uart_recBuf;
Set_flag			Set;
Show_flag			Show;
ST_flag				T_Star;
volatile unsigned char KeyFuncIndex = 1,test_flag=0;//主要用于索引页面编号
volatile unsigned char KeyUpFlag=0,KeyDownFlag=0,KeyOkFlag=0,Key12Flag=0,KeyUp_Confirm_Flag=0,KeyDown_Confirm_Flag=0;
volatile unsigned char SetTime_buff[6] = {0,0,0,0,0,0};
volatile unsigned char Set_buff[6] = {0,0,0,0,0,0};
volatile unsigned char Show_buff[6] = {0,0,0,0,0,0};

void (*KeyFuncPtr)(void);    //按键功能指针
typedef struct {
	unsigned char KeyStateIndex;//当前状态索引号
	unsigned char KeyDnState;//Down 
	unsigned char KeyUpState;//Up 	
	unsigned char KeyOkState;//确认键时转向的状态索引号
	void (*CurrentOperation)();//当前状态所做的事情
}KbdTabStruct;
far rom KbdTabStruct const KeyTab[]={//结构体数组

	{ 0, 0, 0, 0, ( * Disp_clear_all) },
	{ 1, 1, 1, 1, ( * Disp_function_0_0_8) },//开机主界面
	
	{ 2, 2, 2, 2, ( * Disp_clear_all) },//清除界面
	{ 3, 4, 2, 3, ( * Disp_function_0_2_4) },//系统信息主界面
	{ 4, 4, 4, 4, ( * Disp_clear_all) },
	{ 5, 0, 4, 5, ( * Disp_function_0_0_7) },//系统信息第二页
	
	{ 6, 7, 5, 8, ( * Disp_function_0_1_0) },
	{ 7, 8, 6, 5, ( * Disp_function_0_1_1) },
	{ 8, 5, 7, 6, ( * Disp_function_0_1_2) },
	
	{ 9, 5, 7, 10, ( * Disp_function_0_1_3) },//年
	
	{ 10, 10, 10,11,( * Disp_function_0_1_3_0) },//设置年
	{ 11, 11, 11,12, ( * Disp_function_0_1_3_1) },//月
	{ 12, 12, 12,13, ( * Disp_function_0_1_3_2) },//日
	{ 13, 13, 13,14, ( * Disp_function_0_1_3_3) },//时
	{ 14, 14, 14,15, ( * Disp_function_0_1_3_4) },//分
	{ 15, 15, 15,6, ( * Disp_function_0_1_3_5) },//秒

	{ 16, 17, 0, 19, ( * Disp_function_0_2_0) },//设置主界面时间
	{ 17, 18, 16,25, ( * Disp_function_0_2_2) },//设置测试模式
	{ 18, 0, 17, 27, ( * Disp_function_0_2_3) },//设置蜂鸣器
	//设置系统时间
	{ 19, 19, 19, 20, ( * Disp_function_0_2_0_0) },
	{ 20, 20, 20, 21, ( * Disp_function_0_2_0_1) },
	{ 21, 21, 21, 22, ( * Disp_function_0_2_0_2) },
	{ 22, 22, 22, 23, ( * Disp_function_0_2_0_3) },
	{ 23, 23, 23, 24, ( * Disp_function_0_2_0_4) },
	{ 24, 24, 24, 17, ( * Disp_function_0_2_0_5) },
	
	{ 25, 26, 26, 18, ( * Disp_function_0_2_5) },//测试模式设置
	{ 26, 25, 25, 18, ( * Disp_function_0_2_6) },
	
	{ 27, 28, 28, 16, ( * Disp_function_0_2_7) },//蜂鸣器设置
	{ 28, 27, 27, 16, ( * Disp_function_0_2_8) },
	
	{ 29, 8, 8, 8, ( * Disp_clear_all) },
	{ 30, 8, 8, 8, ( * Disp_clear_all) },
	{ 31, 8, 8, 8, ( * Disp_clear_all) },
	{ 32, 8, 8, 8, ( * Disp_clear_all) },
	{ 33, 8, 8, 8, ( * Disp_clear_all) },
	{ 34, 8, 8, 8, ( * Disp_clear_all) },
	{ 35, 8, 8, 8, ( * Disp_clear_all) },
	{ 36, 8, 8, 8, ( * Disp_clear_all) },
	{ 37, 8, 8, 8, ( * Disp_clear_all) },
	{ 38, 8, 8, 8, ( * Disp_clear_all) },
	{ 39, 8, 8, 8, ( * Disp_clear_all) },
	{ 40, 8, 8, 8, ( * Disp_clear_all) },
	{ 41, 8, 8, 8, ( * Disp_clear_all) },
	{ 42, 8, 8, 8, ( * Disp_clear_all) },
	{ 43, 8, 8, 8, ( * Disp_clear_all) },
	{ 44, 8, 8, 8, ( * Disp_clear_all) },
	{ 45, 8, 8, 8, ( * Disp_clear_all) },
	{ 46, 8, 8, 8, ( * Disp_clear_all) },
	{ 47, 8, 8, 8, ( * Disp_clear_all) },
	{ 48, 8, 8, 8, ( * Disp_clear_all) },
	{ 49, 8, 8, 8, ( * Disp_clear_all) },
	{ 50, 8, 8, 8, ( * Disp_clear_all) },
	{ 51, 8, 8, 8, ( * Disp_clear_all) },
	{ 52, 8, 8, 8, ( * Disp_clear_all) },
	{ 53, 8, 8, 8, ( * Disp_clear_all) },
	{ 54, 8, 8, 8, ( * Disp_clear_all) },
	{ 55, 8, 8, 8, ( * Disp_clear_all) },
	{ 56, 8, 8, 8, ( * Disp_clear_all) },
	{ 57, 8, 8, 8, ( * Disp_clear_all) },
	{ 58, 8, 8, 8, ( * Disp_clear_all) },
	{ 60, 8, 8, 8, ( * Disp_clear_all) },
	{ 61, 8, 8, 8, ( * Disp_clear_all) },
	{ 62, 8, 8, 8, ( * Disp_clear_all) },
	{ 63, 8, 8, 8, ( * Disp_clear_all) },
};

void key_scan()
{
	static unsigned char temp1=0,temp2=0,temp3=0,temp4=0,temp5=0,temp6=0;
	unsigned char Key;
	static unsigned char start_flag = 0;
	Key = key_driver();
	switch(Key){
		case KEY1_SHORT://下键
			onKeyUp();
			KeyDownFlag = 1;
			break;
		case KEY1_LONG:
			temp2 = !temp2;
			C_74HC595(PD1_Green, temp2);
			break;
		case KEY2_SHORT://上键
			onKeyDown();	
			KeyUpFlag = 1;
			break;
		case KEY2_LONG:
			temp4 = !temp4;
			C_74HC595(PD3_Red, temp4);
			break;
		case KEY3_SHORT://确认按键
			onKeyOk();
			KeyOkFlag = 1;
			break;
		case KEY3_LONG:
			temp6 = !temp6;
			C_74HC595(PD6_Green, temp6);
			break;
		case KEY12_SHORT:
			Key12Flag = 1;
			temp6 = !temp6;
			C_74HC595(PD8_Green, temp6);
			break;
		case KEY12_LONG:
			C_74HC595(PD8_Green, ON);
			break;
		case KEY_Up_Confirm_SHORT://跳转到系统信息界面
			KeyUp_Confirm_Flag = 1;
			temp2 = !temp2;
			C_74HC595(PD6_Red, temp2);
			break;
		case KEY_Up_Confirm_LONG:
			break;
		case KEY_Down_Confirm_SHORT://跳转到系统设置界面
			Set.SysTimeflag = 0x22;
			KeyDown_Confirm_Flag = 1;
			Set.firstpage = 0x11;
			temp4 = !temp4;
			C_74HC595(PD7_Green, temp4);
			break;
		case KEY_Down_Confirm_LONG:
			break;
		default:
			break;
	}
	if(KeyUpFlag==1){
		KeyUpFlag = 0;
		onKeyUpFlag();
	}
	if(KeyDownFlag==1){
		KeyDownFlag = 0;
		onKeyDownFlag();
	}
	if(KeyOkFlag==1){
		KeyOkFlag = 0;
		onKeyUpFlag();
	}
	/*
	if(Key12Flag==1){
		Key12Flag = 0;
		onKey12();
	}
	*/
	if(KeyUp_Confirm_Flag==1){
		KeyUp_Confirm_Flag = 0;
		KeyUp_Confirm();
	}
	if(KeyDown_Confirm_Flag==1){
		KeyDown_Confirm_Flag = 0;
		KeyDown_Confirm();
	}
	if(test_flag111==1){
		test_flag111 = 0;
		KeyFuncPtr = KeyTab[KeyFuncIndex].CurrentOperation;				
		( *KeyFuncPtr)(); //执行当前按键的操作
	}

}
void KeyUp_Confirm()
{
	switch(KeyFuncIndex)
	{
		case 0:
			break;
		case 1:
			Disp_clear_all();
			KeyFuncIndex = 3;
			break;
		case 2:
			break;
		case 3:
			break;
		case 4:
			break;
		case 5:
			break;
		case 8:
			break;
		default :
			break;
	}
}
void KeyDown_Confirm()
{
	switch(KeyFuncIndex)
	{
		case 0:
			break;
		case 1:
			Disp_clear_all();
			KeyFuncIndex = 16;
			break;
		case 2:
			break;
		case 3:
			break;
		case 4:
			break;
		case 5:
			break;
		case 8:
			break;
		default :
			break;
	}
}
void onKeyDownFlag()
{
	switch(KeyFuncIndex)
	{
		case 0:
			Disp_clear_all();
			KeyFuncIndex = 1;			
			break;
		case 1:
			break;
		case 2:
			break;
		case 3:
			break;
		case 4:
			Disp_clear_all();
			KeyFuncIndex = 5;
			break;
		case 5:
			break;
		case 8:
			break;
		default :
			break;
	}
}
void onKeyUpFlag()
{
	switch(KeyFuncIndex)
	{
		case 0:
			Disp_clear_all();
			KeyFuncIndex = 1;
			break;
		case 1:
			break;
		case 2:
			Disp_clear_all();
			KeyFuncIndex = 1;
			break;
		case 3:
			break;
		case 4:
			Disp_clear_all();
			KeyFuncIndex = 3;
			break;
		case 5:
			break;
		default :
			break;
	}
}
void onKeyOkFlag()
{
	switch(KeyFuncIndex)
	{
		case 0:
			break;
		case 1:
			break;
		case 2:
			break;
		case 3:
			break;
		case 4:
			break;
		case 5:
			break;
		default :
			break;
	}
}
void onKey12Flag()
{
	switch(KeyFuncIndex){
		case 0:
			break;
		default:
			break;
	}
}
void onKey12()
{
//	Disp_clear_all();
	KeyFuncIndex = 16;
	KeyFuncPtr = KeyTab[KeyFuncIndex].CurrentOperation;				
	( *KeyFuncPtr)(); //执行当前按键的操作	
}
void onKeyUp()
{
	unsigned char  max;
	switch(KeyFuncIndex)
	{
		case 0:
			break;
		case 1:
			break;
		case 2:
			break;
		case 3:
			break;
		case 4:
			break;
		case 5:
			break;
		case 10:
			SetTime_buff[0] = decreaceNumberMaxMin(Frist_Info.year,99,0);
			break;
		case 11:
			SetTime_buff[1] = decreaceNumberMaxMin(Frist_Info.month,12,1);
			break;
		case 12:
			max = getMaxDaysOfMonth(Frist_Info.year+2000, SetTime_buff[1]);
			SetTime_buff[2] = decreaceNumberMaxMin(Frist_Info.day, max, 1);
			break;
		case 13:
			SetTime_buff[3] = decreaceNumberMaxMin(Frist_Info.hour,23,0);
			break;
		case 14:
			SetTime_buff[4] = decreaceNumberMaxMin(Frist_Info.min,59,0);
			break;
		case 15:
			SetTime_buff[5] = decreaceNumberMaxMin(Frist_Info.sec,59,0);
			break;
		case 19:
			SetTime_buff[0] = decreaceNumberMaxMin(SetTime_buff[0],99,0);
			break;
		case 20:
			SetTime_buff[1] = decreaceNumberMaxMin(SetTime_buff[1],12,1);
			break;
		case 21:
			max = getMaxDaysOfMonth(SetTime_buff[0]+2000, SetTime_buff[1]);
			SetTime_buff[2] = decreaceNumberMaxMin(SetTime_buff[2], max, 1);
			break;
		case 22:
			SetTime_buff[3] = decreaceNumberMaxMin(SetTime_buff[3],23,0);
			break;
		case 23:
			SetTime_buff[4] = decreaceNumberMaxMin(SetTime_buff[4],59,0);
			break;
		case 24:
			SetTime_buff[5] = decreaceNumberMaxMin(SetTime_buff[5],59,0);
			break;
		case 25:
			Show_buff[0] = decreaceNumberMaxMin(Show_buff[0],1,0);
			break;
		case 26:
			Show_buff[0] = decreaceNumberMaxMin(Show_buff[0],1,0);
			break;
		case 27:
			Set_buff[1] = decreaceNumberMaxMin(Set_buff[0],23,22);
			break;
		case 28:
			Set_buff[1] = decreaceNumberMaxMin(Set_buff[0],23,22);
			break;
			
		default :
			break;
	}
	KeyFuncIndex = KeyTab[ KeyFuncIndex ].KeyDnState ; 
}
void onKeyDown()
{
	unsigned char  max;
	switch(KeyFuncIndex)
	{
		case 0:
			break;
		case 1:
			break;
		case 2:
			break;
		case 3:
			break;
		case 4:
			break;
		case 5:
			break;
		case 10:
			SetTime_buff[0] = increaceNumberMaxMin(Frist_Info.year,99,0);
			break;
		case 11:
			SetTime_buff[1] = increaceNumberMaxMin(Frist_Info.month,12,1);
			break;
		case 12:
			max = getMaxDaysOfMonth(Frist_Info.year+2000, SetTime_buff[1]);
			SetTime_buff[2] = increaceNumberMaxMin(Frist_Info.day, max, 1);
			break;
		case 13:
			SetTime_buff[3] = increaceNumberMaxMin(Frist_Info.hour,23,0);
			break;
		case 14:
			SetTime_buff[4] = increaceNumberMaxMin(Frist_Info.min,59,0);
			break;
		case 15:
			SetTime_buff[5] = increaceNumberMaxMin(Frist_Info.sec,59,0);
			break;
		case 19:
			SetTime_buff[0] = increaceNumberMaxMin(SetTime_buff[0],99,0);
			break;
		case 20:
			SetTime_buff[1] = increaceNumberMaxMin(SetTime_buff[1],12,1);
			break;
		case 21:
			max = getMaxDaysOfMonth(SetTime_buff[0]+2000, SetTime_buff[1]);
			SetTime_buff[2] = increaceNumberMaxMin(SetTime_buff[2], max, 1);
			break;
		case 22:
			SetTime_buff[3] = increaceNumberMaxMin(SetTime_buff[3],23,0);
			break;
		case 23:
			SetTime_buff[4] = increaceNumberMaxMin(SetTime_buff[4],59,0);
			break;
		case 24:
			SetTime_buff[5] = increaceNumberMaxMin(SetTime_buff[5],59,0);
			break;
		case 25:
			Show_buff[0] = increaceNumberMaxMin(Show_buff[0],1,0);
			break;
		case 26:
			Show_buff[0] = increaceNumberMaxMin(Show_buff[0],1,0);
			break;		
		case 27:
			Set_buff[1] = increaceNumberMaxMin(Set_buff[0],23,22);
			break;
		case 28:
			Set_buff[1] = increaceNumberMaxMin(Set_buff[0],23,22);
			break;
		default :
			break;
	}
	
	KeyFuncIndex = KeyTab[ KeyFuncIndex ].KeyUpState ; 
}
void onKeyOk()
{
	switch(KeyFuncIndex)
	{
		case 0:
			break;
		case 1:
			break;
		case 2:
			break;
		case 3:
			break;
		case 4:
			break;
		case 5:
			break;
		default :
			break;
	}
	KeyFuncIndex = KeyTab[ KeyFuncIndex ].KeyOkState ; 

}



//设置界面
void Disp_clear_all()
{
	uint page ; 
	uint column; 
	for( page = 0 ; page<8; page++)
	{
		com_write (0xb1) ; //Set Page Address
		dat_write (page) ; 
		com_write (0x13) ; //Set Column Address
		dat_write (0x00) ;	
		dat_write (0x00) ;
		com_write (0x1d) ; //Write Data

		for (column = 0 ;column <320; column ++)
		{
			dat_write(0x00);	
		}
	} 

}
void Disp_clear_xy(uchar h1,uchar h2,int c1,int c2,char color)
{
	uchar page ; 
	int column,temp,hc,lc,c3,c4;
	c3 = 320 - c1;
	c4 = 320 - c2;
	hc = c4 / 256;
	lc = c4 & 0xff;
	for( page = h1 ; page < h2; page++)
	{
		com_write (0xb1) ; //Set Page Address
		dat_write (page) ; 
		com_write (0x13) ; //Set Column Address
		dat_write (hc) ;	
		dat_write (lc) ;
		com_write (0x1d) ; //Write Data

		for (column = c4 ;column < c3 ; column ++)
		{
			if(color)
				dat_write(0xff);	
			else{
				dat_write(0x00);
			}
	
		}
	} 
}
void Disp_PD_Time()
{
	;
}

void Disp_function_0_0_0()
{
	;
}
void Disp_function_0_0_1()
{
	;
}
void Disp_function_0_0_2()
{
	;
}
void Disp_function_0_0_3()
{
	if(T_Star.PD1){//显示倒计时
		Disp_3Num(4,0,PDx_start.PD1,White_word);
	}else{
		;
	}
	if(T_Star.PD2){//显示倒计时
		Disp_3Num(4,32,PDx_start.PD2,White_word);
	}else{
		;
	}
	if(T_Star.PD3){//显示倒计时
		Disp_3Num(4,65,PDx_start.PD3,White_word);
	}else{
		;
	}
	if(T_Star.PD4){//显示倒计时
		Disp_3Num(4,98,PDx_start.PD4,White_word);
	}else{
		;
	}
	if(T_Star.PD5){//显示倒计时
		Disp_3Num(4,131,PDx_start.PD5,White_word);
	}else{
		;
	}
	if(T_Star.PD6){//显示倒计时
		Disp_3Num(4,164,PDx_start.PD6,White_word);
	}else{
		;
	}
	if(T_Star.PD7){//显示倒计时
		Disp_3Num(4,197,PDx_start.PD7,White_word);
	}else{
		;
	}
	if(T_Star.PD8){//显示倒计时
		Disp_3Num(4,230,PDx_start.PD8,White_word);
	}else{
		;
	}
	if(T_Star.PD9){//显示倒计时
		Disp_3Num(4,263,PDx_start.PD9,White_word);
	}else{
		;
	}
	if(T_Star.PD10){//显示倒计时
		Disp_3Num(4,296,PDx_start.PD10,White_word);
	}else{
		;
	}
}
void Disp_function_0_0_4()
{//显示结果页面信息information
	if(PDx_result_flag.PD1 == 0x10){
		Disp_3Num(4,0,PDx_end.PD1,White_word);
		if(PDx_result.PD1==0x10){//阴性
			Disp_16x8_char(2,7,'-',White_word);
		}else if(PDx_result.PD1==0x11){//阳性
			Disp_16x8_char(2,7,'+',White_word);
		}
	}else{
		;
	}
	if(PDx_result_flag.PD2 == 0x11){
		Disp_3Num(4,32,PDx_end.PD2,White_word);
		if(PDx_result.PD2==0x10){//阴性
			Disp_16x8_char(2,40,'-',White_word);
		}else if(PDx_result.PD1==0x11){//阳性
			Disp_16x8_char(2,40,'+',White_word);
		}
	}else{
		;
	}
	if(PDx_result_flag.PD3 == 0x12){
		Disp_3Num(4,65,PDx_end.PD3,White_word);
		if(PDx_result.PD3==0x10){//阴性
			Disp_16x8_char(2,73,'-',White_word);
		}else if(PDx_result.PD1==0x11){//阳性
			Disp_16x8_char(2,73,'+',White_word);
		}
	}else{
		;
	}
	if(PDx_result_flag.PD4 == 0x13){
		Disp_3Num(4,98,PDx_end.PD4,White_word);
		if(PDx_result.PD4==0x10){//阴性
			Disp_16x8_char(2,106,'-',White_word);
		}else if(PDx_result.PD1==0x11){//阳性
			Disp_16x8_char(2,106,'+',White_word);
		}
	}else{
		;
	}
	if(PDx_result_flag.PD5 == 0x14){
		Disp_3Num(4,131,PDx_end.PD5,White_word);
		if(PDx_result.PD5==0x10){//阴性
			Disp_16x8_char(2,139,'-',White_word);
		}else if(PDx_result.PD1==0x11){//阳性
			Disp_16x8_char(2,139,'+',White_word);
		}
	}else{
		;
	}
	if(PDx_result_flag.PD6 == 0x15){
		Disp_3Num(4,164,PDx_end.PD6,White_word);
		if(PDx_result.PD6==0x10){//阴性
			Disp_16x8_char(2,172,'-',White_word);
		}else if(PDx_result.PD1==0x11){//阳性
			Disp_16x8_char(2,172,'+',White_word);
		}
	}else{
		;
	}
	if(PDx_result_flag.PD7 == 0x16){
		Disp_3Num(4,197,PDx_end.PD7,White_word);
		if(PDx_result.PD7==0x10){//阴性
			Disp_16x8_char(2,205,'-',White_word);
		}else if(PDx_result.PD1==0x11){//阳性
			Disp_16x8_char(2,205,'+',White_word);
		}
	}else{
		;
	}
	if(PDx_result_flag.PD8 == 0x17){
		Disp_3Num(4,230,PDx_end.PD8,White_word);
		if(PDx_result.PD8==0x10){//阴性
			Disp_16x8_char(2,238,'-',White_word);
		}else if(PDx_result.PD1==0x11){//阳性
			Disp_16x8_char(2,238,'+',White_word);
		}
	}else{
		;
	}
	if(PDx_result_flag.PD9 == 0x18){
		Disp_3Num(4,263,PDx_end.PD9,White_word);
		if(PDx_result.PD9==0x10){//阴性
			Disp_16x8_char(2,271,'-',White_word);
		}else if(PDx_result.PD1==0x11){//阳性
			Disp_16x8_char(2,271,'+',White_word);
		}
	}else{
		;
	}
	if(PDx_result_flag.PD10 == 0x19){
		Disp_3Num(4,296,PDx_end.PD10,White_word);
		if(PDx_result.PD10==0x10){//阴性
			Disp_16x8_char(2,304,'-',White_word);
		}else if(PDx_result.PD1==0x11){//阳性
			Disp_16x8_char(2,304,'+',White_word);
		}
	}else{
		;
	}




}
void Disp_function_0_0_5()
{
;
}
void Disp_function_0_0_6()
{
;
}
void Disp_function_0_0_7()//系统信息第二页
{
	Disp_HZstr(6,0,16,Setting4,White_word);		
	Disp_HZstr(4,0,16,SoftVerStr,White_word);	
	Disp_CharStr(4,100,8,VerStr,White_word);
	Disp_HZstr(2,0,16,Setting6,White_word);		
	Disp_HZstr(0,0,16,Setting7,White_word);		
}
void Disp_function_0_0_8()//开机主界面
{
	//Disp_PD_Time();//选择那个通道进行倒计时
//5C 5D 11 12 0C C2
	if(Set.SysTimeflag == 0x22){
		Set.SysTimeflag = 0;
		U_transfer(Query_Systiem);
	}
	Disp_function_0_0_3();//显示倒计时
	Disp_function_0_0_4();//显示结果
	Disp_time_main();//显示时间和通道号
}
void Disp_function_0_0_9()
{
	Disp_HZstr(6,0,16,TimrStr,Black_word);
	Disp_Time(6,100);
	Disp_HZstr(4,0,16,PowerStr,White_word);
	Disp_Time(4,100);
	Disp_HZstr(2,0,16,RunTimeStr,White_word);
	Disp_HZstr(0,0,16,WenduStr1,White_word);
	Disp_Num(0,100,60,White_word);
	Disp_HZstr(0,116,16,TUnitStr,White_word);
	Disp_HZstr(0,156,16,BeepStr,White_word);
	Disp_16x8_char(0,220,':',White_word);
	Disp_HZstr(0,230,16,OffStr,White_word);
}

void Disp_function_0_1_0()
{
	
	Disp_HZstr(6,0,16,TimrStr,White_word);
	Disp_Time(6,100);
	Disp_HZstr(4,0,16,PowerStr,Black_word);
	Disp_Time(4,100);
	Disp_HZstr(2,0,16,RunTimeStr,White_word);
	Disp_HZstr(0,0,16,WenduStr1,White_word);
	Disp_Num(0,100,60,White_word);
	Disp_HZstr(0,116,16,TUnitStr,White_word);
	Disp_HZstr(0,156,16,BeepStr,White_word);
	Disp_16x8_char(0,220,':',White_word);
	Disp_HZstr(0,230,16,OffStr,White_word);	
}
void Disp_function_0_1_1()
{
	Disp_HZstr(6,0,16,TimrStr,White_word);
	Disp_Time(6,100);
	Disp_HZstr(4,0,16,PowerStr,White_word);
	Disp_Time(4,100);
	Disp_HZstr(2,0,16,RunTimeStr,Black_word);
	Disp_HZstr(0,0,16,WenduStr1,White_word);
	Disp_Num(0,100,60,White_word);
	Disp_HZstr(0,116,16,TUnitStr,White_word);
	Disp_HZstr(0,156,16,BeepStr,White_word);
	Disp_16x8_char(0,220,':',White_word);
	Disp_HZstr(0,230,16,OffStr,White_word);		
}
void Disp_function_0_1_2()
{
	Disp_HZstr(6,0,16,TimrStr,White_word);
	Disp_Time(6,100);
	Disp_HZstr(4,0,16,PowerStr,White_word);
	Disp_Time(4,100);
	Disp_HZstr(2,0,16,RunTimeStr,White_word);
	Disp_HZstr(0,0,16,WenduStr1,Black_word);
	Disp_Num(0,100,60,White_word);
	Disp_HZstr(0,116,16,TUnitStr,White_word);
	Disp_HZstr(0,156,16,BeepStr,White_word);
	Disp_16x8_char(0,220,':',White_word);
	Disp_HZstr(0,230,16,OffStr,White_word);		
}
void Disp_function_0_1_3()
{
	Disp_HZstr(6,0,16,TimrStr,White_word);
	Disp_16x8_Time_Num(6,100,20,White_word);//年
	Disp_16x8_Time_Num(6,116,17,Black_word);//年
	Disp_16x8_char(6,132,'-',White_word);
	Disp_16x8_Time_Num(6,140,12,White_word);//月
	Disp_16x8_char(6,156,'-',White_word);
	Disp_16x8_Time_Num(6,164,25,White_word);//日
	Disp_16x8_char(6,180,' ',White_word);
	Disp_16x8_Time_Num(6,188,8,White_word);//时
	Disp_16x8_char(6,204,':',White_word);
	Disp_16x8_Time_Num(6,212,38,White_word);//分
	Disp_16x8_char(6,228,':',White_word);
	Disp_16x8_Time_Num(6,236,38,White_word);//秒
}
void Disp_function_0_1_3_0()
{
	Disp_HZstr(6,0,16,TimrStr,White_word);
	Disp_16x8_Time_Num(6,116,SetTime_buff[0],Black_word);//年
}
void Disp_function_0_1_3_1()
{
	Disp_16x8_Time_Num(6,116,SetTime_buff[0],White_word);//年
	Disp_16x8_Time_Num(6,140,SetTime_buff[1],Black_word);//月
	//SetTime_buff[0] = decimal_bcd(SetTime_buff[0]);
}
void Disp_function_0_1_3_2()
{
	unsigned char  max = getMaxDaysOfMonth(SetTime_buff[0]+2000, SetTime_buff[1]);
	if (SetTime_buff[2] > max){
		SetTime_buff[2] = max;
	}
	Disp_16x8_Time_Num(6,116,SetTime_buff[0],White_word);//年
	Disp_16x8_Time_Num(6,140,SetTime_buff[1],White_word);//月
	Disp_16x8_Time_Num(6,164,SetTime_buff[2],Black_word);//日
	//SetTime_buff[1] = decimal_bcd(SetTime_buff[1]);
}
void Disp_function_0_1_3_3()
{
	Disp_16x8_Time_Num(6,116,SetTime_buff[0],White_word);//年
	Disp_16x8_Time_Num(6,140,SetTime_buff[1],White_word);//月
	Disp_16x8_Time_Num(6,164,SetTime_buff[2],White_word);//日
	Disp_16x8_Time_Num(6,188,SetTime_buff[3],Black_word);//时
	//SetTime_buff[2] = decimal_bcd(SetTime_buff[2]);

}
void Disp_function_0_1_3_4()
{
	Disp_16x8_Time_Num(6,116,SetTime_buff[0],White_word);//年
	Disp_16x8_Time_Num(6,140,SetTime_buff[1],White_word);//月
	Disp_16x8_Time_Num(6,164,SetTime_buff[2],White_word);//日
	Disp_16x8_Time_Num(6,188,SetTime_buff[3],White_word);//时
	Disp_16x8_Time_Num(6,212,SetTime_buff[4],Black_word);//分
	//SetTime_buff[3] = decimal_bcd(SetTime_buff[3]);
}
void Disp_function_0_1_3_5()
{
	Disp_16x8_Time_Num(6,116,SetTime_buff[0],White_word);//年
	Disp_16x8_Time_Num(6,140,SetTime_buff[1],White_word);//月
	Disp_16x8_Time_Num(6,164,SetTime_buff[2],White_word);//日
	Disp_16x8_Time_Num(6,188,SetTime_buff[3],White_word);//时
	Disp_16x8_Time_Num(6,212,SetTime_buff[4],White_word);//分
	Disp_16x8_Time_Num(6,236,SetTime_buff[5],Black_word);//秒
	//SetTime_buff[4] = decimal_bcd(SetTime_buff[4]);

}
unsigned char decimal_bcd(unsigned char decimal)
{
return (unsigned char) (decimal+(decimal / 10)*6);
}
void Disp_function_0_1_4()
{
	;
}
void U_transfer(unsigned char temp)
{//5C 5D 11 12 0b b0 xx xx 
	unsigned char buff[20];
	buff[0] = 0x5c;
	buff[1] = 0x5d;
	buff[2] = 0x11;
	buff[3] = 0x12;
	switch(temp){
		case SettingTiem:
			//SetTime_buff[5] = decimal_bcd(SetTime_buff[5]);
			buff[4] = 0x0b;	
			buff[5] = 0xb0;
			buff[6] = SetTime_buff[5];//sec
			buff[7] = SetTime_buff[4];//min
			buff[8] = SetTime_buff[3];//hour
			buff[9] = SetTime_buff[2];//day
			buff[10] = SetTime_buff[1];//month
			buff[11] = SetTime_buff[0];//year
			buff[12] = 0x00;
			Uart1_Send(buff);
			break;
		case SettingMode:
			buff[5] = 0xb1;
			break;
		case SettingBeep:
			buff[5] = 0xb2;
			break;
		case Query_fristpage:
			buff[4] = 0x0c;
			buff[5] = 0xc1;
			buff[6] = 0x00;
			Uart1_Send(buff);
			break;
		case Query_Systiem:
			buff[4] = 0x0c;
			buff[5] = 0xc2;
			buff[6] = 0;
			Uart1_Send(buff);
			break;
		default:
			break;
	}
}
void Disp_function_0_1_5()
{
	;
}
void Disp_function_0_1_6()
{
	;
}
void Disp_function_0_1_7()
{
	;
}
void Disp_function_0_1_8()
{
	;
}
void Disp_function_0_1_9()
{
	;
}
//设置主界面
void Disp_function_0_2_0()
{
	unsigned char buff[7];
	if(Set.firstpage==0x11){
		Set.firstpage = 0x00;
		U_transfer(Query_fristpage);
	}
	Disp_Qurey_info();
	Disp_16x8_Time_Num(4,236,SetTime_buff[5],White_word);//秒
	Disp_HZstr(6,128,16,SysSettingStr,White_word);
	Disp_HZstr(4,0,16,TimrStr,Black_word);//设置系统时间
	Disp_HZstr(2,0,16,TestModeStr,White_word);
	Disp_HZstr(0,0,16,BeepStr,White_word);
	if(Set_buff[0] == 18){//jk1202
		Show_buff[0] = 0;
		Disp_16x8_Time_Num(2,100,Show_buff[0],White_word);
	}else if(Set_buff[0] == 24){//jk1301
		Show_buff[0] = 1;
		Disp_16x8_Time_Num(2,100,Show_buff[0],White_word);
	}
	if(Set_buff[1] == 0x22){
		Show_buff[1] = 0;
		Disp_16x8_Time_Num(0,100,Show_buff[1],White_word);
	}else if(Set_buff[1] == 0x23){
		Show_buff[1] = 1;
		Disp_16x8_Time_Num(0,100,Show_buff[1],White_word);
	}
/*	
	if(Set_buff[0] == 18)
		Disp_CharStr(2,100,8,Mode1Str,White_word);
	else if(Set_buff[0] == 24)
		Disp_CharStr(2,100,8,Mode2Str,White_word);
	
	if(Set_buff[1] == 0x22)
		Disp_HZstr(0,100,16,OffStr,White_word);
	else if(Set_buff[1] == 0x23)
		Disp_HZstr(0,100,16,OnStr,White_word);
*/
}
void Disp_function_0_2_0_0()
{
	Disp_HZstr(4,0,16,TimrStr,White_word);
	Disp_16x8_Time_Num(4,116,SetTime_buff[0],Black_word);//年

}
void Disp_function_0_2_0_1()
{
	Disp_16x8_Time_Num(4,116,SetTime_buff[0],White_word);//年
	Disp_16x8_Time_Num(4,140,SetTime_buff[1],Black_word);//月

}
void Disp_function_0_2_0_2()
{
	unsigned char  max = getMaxDaysOfMonth(SetTime_buff[0]+2000, SetTime_buff[1]);
	if (SetTime_buff[2] > max){
		SetTime_buff[2] = max;
	}
	Disp_16x8_Time_Num(4,116,SetTime_buff[0],White_word);//年
	Disp_16x8_Time_Num(4,140,SetTime_buff[1],White_word);//月
	Disp_16x8_Time_Num(4,164,SetTime_buff[2],Black_word);//日

}
void Disp_function_0_2_0_3()
{
	Disp_16x8_Time_Num(4,116,SetTime_buff[0],White_word);//年
	Disp_16x8_Time_Num(4,140,SetTime_buff[1],White_word);//月
	Disp_16x8_Time_Num(4,164,SetTime_buff[2],White_word);//日
	Disp_16x8_Time_Num(4,188,SetTime_buff[3],Black_word);//时
}
void Disp_function_0_2_0_4()
{
	Disp_16x8_Time_Num(4,116,SetTime_buff[0],White_word);//年
	Disp_16x8_Time_Num(4,140,SetTime_buff[1],White_word);//月
	Disp_16x8_Time_Num(4,164,SetTime_buff[2],White_word);//日
	Disp_16x8_Time_Num(4,188,SetTime_buff[3],White_word);//时
	Disp_16x8_Time_Num(4,212,SetTime_buff[4],Black_word);//分
}
void Disp_function_0_2_0_5()
{
	Disp_16x8_Time_Num(4,116,SetTime_buff[0],White_word);//年
	Disp_16x8_Time_Num(4,140,SetTime_buff[1],White_word);//月
	Disp_16x8_Time_Num(4,164,SetTime_buff[2],White_word);//日
	Disp_16x8_Time_Num(4,188,SetTime_buff[3],White_word);//时
	Disp_16x8_Time_Num(4,212,SetTime_buff[4],White_word);//分
	Disp_16x8_Time_Num(4,236,SetTime_buff[5],Black_word);//秒
	Set.timeflag = 0x11;
}
void Disp_function_0_2_0_6()
{
	;
}
void Disp_function_0_2_0_7()
{
	;
}

void Disp_function_0_2_1()
{
//设置选项预留界面
	Disp_HZstr(6,0,16,Setting4,White_word);		
	Disp_HZstr(4,0,16,Setting5,White_word);		
	Disp_HZstr(2,0,16,Setting6,White_word);		
	Disp_HZstr(0,0,16,Setting7,White_word);		
}
void Disp_function_0_2_2()
{
	//Disp_16x8_Time_Num(4,236,SetTime_buff[5],White_word);
	if(Set.timeflag == 0x11){
		Set.timeflag = 0x00;
		U_transfer(SettingTiem);
	}
	Set.SysTimeflag = 0x22;
	Disp_16x8_Time_Num(4,236,SetTime_buff[5],White_word);//秒
	Disp_HZstr(4,0,16,TimrStr,White_word);
	Disp_HZstr(2,0,16,TestModeStr,Black_word);//设置测试模式
	Disp_HZstr(0,0,16,BeepStr,White_word);
}
void Disp_function_0_2_3()
{
	Disp_CharStr(2,100,8,Mode2Str,White_word);//设置蜂鸣器
	
	Disp_HZstr(4,0,16,TimrStr,White_word);
	Disp_HZstr(2,0,16,TestModeStr,White_word);
	Disp_HZstr(0,0,16,BeepStr,Black_word);//设置蜂鸣器
}
void Disp_function_0_2_4()//系统信息主界面
{
	Disp_HZstr(6,128,16,SysInfoStr,White_word);;
	Disp_HZstr(4,0,16,TimrStr,White_word);
	//Disp_Time(4,100);
	Disp_HZstr(2,0,16,PowerStr,White_word);
	//Disp_Time(2,100);
	Disp_HZstr(0,0,16,RunTimeStr,White_word);

	Disp_3Num(0,100,Time_info.day,White_word);
	Disp_CharStr(0,124,8,"day",White_word);
	Disp_Num(0,148,Time_info.hour,White_word);
	Disp_CharStr(0,164,8,"hour",White_word);
	Disp_Num(0,196,Time_info.min,White_word);
	Disp_CharStr(0,212,8,"min",White_word);
}
void Disp_function_0_2_5()
{
	Disp_HZstr(2,0,16,TestModeStr,White_word);//设置测试模式
	//Disp_16x8_Time_Num(2,100,Show_buff[0],Black_word);
	//Disp_CharStr(2,100,8,Mode1Str,Black_word);
	if(Show_buff[0] == 0)
		Disp_CharStr(2,100,8,Mode1Str,Black_word);
	else if(Show_buff[0] == 1)
		Disp_CharStr(2,100,8,Mode2Str,Black_word);
}
void Disp_function_0_2_6()
{
	//Disp_CharStr(2,100,8,Mode2Str,Black_word);
	//Disp_16x8_Time_Num(2,100,Show_buff[0],White_word);
	if(Show_buff[0] == 0)
		Disp_CharStr(2,100,8,Mode1Str,Black_word);
	else if(Show_buff[0] == 1)
		Disp_CharStr(2,100,8,Mode2Str,Black_word);
}
void Disp_function_0_2_7()
{
	Disp_HZstr(0,0,16,BeepStr,White_word);//设置蜂鸣器
	Disp_HZstr(0,100,16,OffStr,Black_word);		
}
void Disp_function_0_2_8()
{
	Disp_HZstr(0,100,16,OnStr,Black_word);		
}
void Disp_function_0_2_9()
{
	;
}
void Disp_Qurey_info()
{
	Disp_Num(4,40+60,20,White_word);
	Disp_Num(4,56+60,SetTime_buff[0],White_word);
	Disp_16x8_char(4,132,'-',White_word);
	Disp_Num(4,140,SetTime_buff[1],White_word);
	Disp_16x8_char(4,156,'-',White_word);
	Disp_Num(4,164,SetTime_buff[2],White_word);
	Disp_16x8_char(4,180,' ',White_word);
	Disp_Num(4,188,SetTime_buff[3],White_word);
	Disp_16x8_char(4,204,':',White_word);
	Disp_Num(4,212,SetTime_buff[4],White_word);
	Disp_16x8_char(4,228,':',White_word);
	Disp_Num(4,236,SetTime_buff[5],White_word);
}
void Disp_Time(char h,int c)
{
	Disp_Num(4,40+60,20,White_word);
	Disp_Num(4,56+60,Sys_count.year,White_word);
	Disp_16x8_char(4,72+60,'-',White_word);
	Disp_Num(4,80+60,Sys_count.month,White_word);
	Disp_16x8_char(4,96+60,'-',White_word);
	Disp_Num(4,104+60,Sys_count.day,White_word);
	Disp_16x8_char(4,120+60,' ',White_word);
	Disp_Num(4,128+60,Sys_count.hour,White_word);
	Disp_16x8_char(4,144+60,':',White_word);
	Disp_Num(4,152+60,Sys_count.min,White_word);
	Disp_16x8_char(4,168+60,':',White_word);
	Disp_Num(4,176+60,Sys_count.s,White_word);
}


unsigned char getMaxDaysOfMonth(unsigned int year, unsigned char month)
{//获取每月天数
	unsigned char max_days = 31;
	if (month == 4 || month == 6 || month == 9 || month == 11){
		max_days = 30;
	}else if (month == 2){
		max_days = 28;
		if ((((year % 4) == 0) && ((year % 100) != 0)) || 
			((year % 400) == 0)){
			max_days = 29;
		}
	}

	return max_days;
}
unsigned char increaceNumberMaxMin(unsigned char val, unsigned char max, unsigned char min){
//递增函数功能，适用于向上按键	
	if (val >= max)
		return min;
	else
		return (val + 1);
}

unsigned char increaceNumberMax(unsigned char val, unsigned char max){
//递增函数
	return increaceNumberMaxMin(val, max, 0);
}

unsigned char decreaceNumberMaxMin(unsigned char val, unsigned char max, unsigned char min){
//递减函数功能，适用于向下按键
	if (val <= min){
		return max;
	}else{
		return (val-1);
	}
}

unsigned char decreaceNumberMax(unsigned char val, unsigned char max){
//递减函数
	return decreaceNumberMaxMin(val, max, 0);
}







