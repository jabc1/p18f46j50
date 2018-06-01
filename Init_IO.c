#include "Includeh.h"
extern Set_flag			Set;
extern Start_Time		Time_info;
extern PDx_Time		CountSec;
extern PDx_Time		Countflag;
extern Sys_Temp		Sys_count;
extern ST_flag		T_Star;
PDx_Time	PDx_start;//用来缓存倒计时时间
PDx_Time	PDx_end;
PDx_Time	PDx_flag;
PDx_Time	PDx_result;
PDx_Time	PDx_result_flag;
PDx_Time	PDx_Temp;
void delay_5us()
{
	Nop();Nop();Nop();Nop();Nop();
	Nop();Nop();Nop();Nop();Nop();
}
void Init_IO()
{
	setSER_DS =0;

	setRCLK_STCP =0;
	setSRCLK_SHCP =0;
	setOE_L =0;
	
	RCLK_STCP = 1;
	SRCLK_SHCP = 1;
	SER_DS = 1;
	OE_L = 1;
	setTestIO = 0;

	ANCON1 = 0b00011111;
	set_Key_1 = 1;//set input
	set_Key_2 = 1;
	set_Key_3 = 1;
	TRISB = 0x0f;
	
	OE_L = 1;//shutdown double light

}

void Init_Sys()
{
	//Sys_count.hour = 0;
	Sys_count.hour_flag = 0;
	//Sys_count.min = 0;
	Sys_count.min_flag = 0;
	//Sys_count.s = 0;
	Sys_count.s_flag = 0;
	Sys_count.ms = 0;

	
	Time_info.day = 0;
	Time_info.hour = 0;
	Time_info.min = 0;

	Set.firstpage = 0;
}
void Init_PDx_temp()
{
	PDx_start.PD1 = 0x00;//缓存时间变量
	PDx_start.PD2 = 0x00;
	PDx_start.PD3 = 0x00;
	PDx_start.PD4 = 0x00;
	PDx_start.PD5 = 0x00;
	PDx_start.PD6 = 0x00;
	PDx_start.PD7 = 0x00;
	PDx_start.PD8 = 0x00;
	PDx_start.PD9 = 0x00;
	PDx_start.PD10 = 0x00;

	T_Star.PD1 = 0x00;//显示倒计时标志位
	T_Star.PD2 = 0x00;
	T_Star.PD3 = 0x00;
	T_Star.PD4 = 0x00;
	T_Star.PD5 = 0x00;
	T_Star.PD6 = 0x00;
	T_Star.PD7 = 0x00;
	T_Star.PD8 = 0x00;
	T_Star.PD9 = 0x00;
	T_Star.PD10 = 0x00;
	
	Countflag.PD1 = 0;
	Countflag.PD2 = 0;
	Countflag.PD3 = 0;
	Countflag.PD4 = 0;
	Countflag.PD5 = 0;
	Countflag.PD6 = 0;
	Countflag.PD7 = 0;
	Countflag.PD8 = 0;
	Countflag.PD9 = 0;
	Countflag.PD10 = 0;
	
	CountSec.PD1 = 0;
	CountSec.PD2 = 0;
	CountSec.PD3 = 0;
	CountSec.PD4 = 0;
	CountSec.PD5 = 0;
	CountSec.PD6 = 0;
	CountSec.PD7 = 0;
	CountSec.PD8 = 0;
	CountSec.PD9 = 0;
	CountSec.PD10 = 0;
}
void Init_PDx()
{
	if(CountSec.PD1++>=59){
		CountSec.PD1 = 0;
		Countflag.PD1= 1;
	}else{
		;
	}
	if(CountSec.PD2++>=59){
		CountSec.PD2 = 0;
		Countflag.PD2= 1;
	}else{
		;
	}
	if(CountSec.PD3++>=59){
		CountSec.PD3 = 0;
		Countflag.PD3= 1;
	}else{
		;
	}
	if(CountSec.PD4++>=59){
		CountSec.PD4 = 0;
		Countflag.PD4= 1;
	}else{
		;
	}
	if(CountSec.PD5++>=59){
		CountSec.PD5 = 0;
		Countflag.PD5= 1;
	}else{
		;
	}
	if(CountSec.PD6++>=59){
		CountSec.PD6 = 0;
		Countflag.PD6= 1;
	}else{
		;
	}
	if(CountSec.PD7++>=59){
		CountSec.PD7 = 0;
		Countflag.PD7= 1;
	}else{
		;
	}
	if(CountSec.PD8++>=59){
		CountSec.PD8 = 0;
		Countflag.PD8= 1;
	}else{
		;
	}
	if(CountSec.PD9++>=59){
		CountSec.PD9 = 0;
		Countflag.PD9= 1;
	}else{
		;
	}
	if(CountSec.PD10++>=59){
		CountSec.PD10 = 0;
		Countflag.PD10= 1;
	}else{
		;
	}

	
}

void PDx_function()
{
	if(PDx_result_flag.PD1==0x10)
		PDx_end.PD1 = PDx_Temp.PD1;
	if(PDx_result_flag.PD2==0x11)
		PDx_end.PD2 = PDx_Temp.PD2;
	if(PDx_result_flag.PD3==0x12)
		PDx_end.PD3 = PDx_Temp.PD3;
	if(PDx_result_flag.PD4==0x13)
		PDx_end.PD4 = PDx_Temp.PD4;
	if(PDx_result_flag.PD5==0x14)
		PDx_end.PD5 = PDx_Temp.PD5;
	if(PDx_result_flag.PD6==0x15)
		PDx_end.PD6 = PDx_Temp.PD6;
	if(PDx_result_flag.PD7==0x16)
		PDx_end.PD7 = PDx_Temp.PD7;
	if(PDx_result_flag.PD8==0x17)
		PDx_end.PD8 = PDx_Temp.PD8;
	if(PDx_result_flag.PD9==0x18)
		PDx_end.PD9 = PDx_Temp.PD9;
	if(PDx_result_flag.PD10==0x19)
		PDx_end.PD10 = PDx_Temp.PD10;
	
	//if(Sys_count.min_flag == 1){
		//Sys_count.min_flag = 0;
if(Countflag.PD1==1){
	Countflag.PD1 = 0;
		if(T_Star.PD1 == 0x21){//开始进行倒计时显示
			PDx_start.PD1--;
			if(PDx_start.PD1==0){//强制读报测试结果
				PDx_result_flag.PD1==0x10;
				T_Star.PD1 = 0x00;
				PDx_start.PD1 = 0x00;
			}
			PDx_Temp.PD1 = PDx_start.PD1;
		}else{
			;
		}
}
if(Countflag.PD2==1){
	Countflag.PD2 = 0;
		if(T_Star.PD2 == 0x21){//开始进行倒计时显示
			PDx_start.PD2--;
			if(PDx_start.PD2==0){//强制读报测试结果
				PDx_result_flag.PD2==0x11;
				T_Star.PD2 = 0x00;
				PDx_start.PD2 = 0x00;
			}
			PDx_Temp.PD2 = PDx_start.PD2;
		}else{
			;
		}
}
if(Countflag.PD3==1){
	Countflag.PD3 = 0;
		if(T_Star.PD3 == 0x21){//开始进行倒计时显示
			PDx_start.PD3--;
			if(PDx_start.PD3==0){//强制读报测试结果
				PDx_result_flag.PD3==0x12;
				T_Star.PD3 = 0x00;
				PDx_start.PD3 = 0x00;
			}
			PDx_Temp.PD3 = PDx_start.PD3;
		}else{
			;
		}
}
if(Countflag.PD4==1){
	Countflag.PD4 = 0;
		if(T_Star.PD4 == 0x21){//开始进行倒计时显示
			PDx_start.PD4--;
			if(PDx_start.PD4==0){//强制读报测试结果
				PDx_result_flag.PD4==0x13;
				T_Star.PD4 = 0x00;
				PDx_start.PD4 = 0x00;
			}
			PDx_Temp.PD4 = PDx_start.PD4;
		}else{
			;
		}
}
if(Countflag.PD5==1){
	Countflag.PD5 = 0;
		if(T_Star.PD5 == 0x21){//开始进行倒计时显示
			PDx_start.PD5--;
			if(PDx_start.PD5==0){//强制读报测试结果
				PDx_result_flag.PD5==0x14;
				T_Star.PD5 = 0x00;
				PDx_start.PD5 = 0x00;
			}
			PDx_Temp.PD5 = PDx_start.PD5;
		}else{
			;
		}
}
if(Countflag.PD6==1){
	Countflag.PD6 = 0;
		if(T_Star.PD6 == 0x21){//开始进行倒计时显示
			PDx_start.PD6--;
			if(PDx_start.PD6==0){//强制读报测试结果
				PDx_result_flag.PD6==0x15;
				T_Star.PD6 = 0x00;
				PDx_start.PD6 = 0x00;
			}
			PDx_Temp.PD6 = PDx_start.PD6;
		}else{
			;
		}
}
if(Countflag.PD7==1){
	Countflag.PD7 = 0;
		if(T_Star.PD7 == 0x21){//开始进行倒计时显示
			PDx_start.PD7--;
			if(PDx_start.PD7==0){//强制读报测试结果
				PDx_result_flag.PD7==0x16;
				T_Star.PD7 = 0x00;
				PDx_start.PD7 = 0x00;
			}
			PDx_Temp.PD7 = PDx_start.PD7;
		}else{
			;
		}
}
if(Countflag.PD8==1){
	Countflag.PD8 = 0;
		if(T_Star.PD8 == 0x21){//开始进行倒计时显示
			PDx_start.PD8--;
			if(PDx_start.PD8==0){//强制读报测试结果
				PDx_result_flag.PD8==0x17;
				T_Star.PD8 = 0x00;
				PDx_start.PD8 = 0x00;
			}
			PDx_Temp.PD8 = PDx_start.PD8;
		}else{
			;
		}
}
if(Countflag.PD9==1){
	Countflag.PD9 = 0;
		if(T_Star.PD9 == 0x21){//开始进行倒计时显示
			PDx_start.PD9--;
			if(PDx_start.PD9==0){//强制读报测试结果
				PDx_result_flag.PD9==0x18;
				T_Star.PD9 = 0x00;
				PDx_start.PD9 = 0x00;
			}
			PDx_Temp.PD9 = PDx_start.PD9;
		}else{
			;
		}
}
if(Countflag.PD10==1){
	Countflag.PD10 = 0;
		if(T_Star.PD10 == 0x21){//开始进行倒计时显示
			PDx_start.PD10--;
			if(PDx_start.PD10==0){//强制读报测试结果
				PDx_result_flag.PD10 == 0x19;
				T_Star.PD10 = 0x00;
				PDx_start.PD10 = 0x00;
			}
			PDx_Temp.PD10 = PDx_start.PD10;
		}else{
			;
		}
}
	//}
}

void Disp_time_main()
{
	unsigned int i,temp_c;
	
	for(i=0;i<=9;i++){
		temp_c = i * 33 + 7;
		Disp_16x8_char(6,temp_c,i+0x30,1);
	}
	Disp_HZstr(0,215+32,16,WenduStr,White_word);
	Disp_16x8_char(0,279,':',White_word);
	Disp_Num(0,286,Sys_count.T,White_word);
	Disp_16x16_hz_1(0,304,15,White_word);

	Disp_HZstr(0,0,16,TimeStr,White_word);
	Disp_16x8_char(0,32,':',White_word);
/*	
	Disp_Num(0,40,Sys_count.hour,White_word);
	Disp_16x8_char(0,56,':',White_word);
	Disp_Num(0,64,Sys_count.min,White_word);
	Disp_16x8_char(0,80,':',White_word);
	Disp_Num(0,88,Sys_count.s,White_word);
	Disp_16x8_char(0,96+8,' ',White_word);
	
	Disp_Num(0,112,20,White_word);
	Disp_Num(0,128,17,White_word);
	Disp_16x8_char(0,128+8+8,'-',White_word);
	Disp_Num(0,136+8+8,12,White_word);
	Disp_16x8_char(0,152+8+8,'-',White_word);
	Disp_Num(0,160+8+8,28,White_word);
*/	
	Disp_Num(0,40,20,White_word);
	Disp_Num(0,56,Sys_count.year,White_word);
	Disp_16x8_char(0,72,'-',White_word);
	Disp_Num(0,80,Sys_count.month,White_word);
	Disp_16x8_char(0,96,'-',White_word);
	Disp_Num(0,104,Sys_count.day,White_word);
	
	Disp_16x8_char(0,120,' ',White_word);
	Disp_Num(0,128,Sys_count.hour,White_word);
	Disp_16x8_char(0,144,':',White_word);
	Disp_Num(0,152,Sys_count.min,White_word);
	Disp_16x8_char(0,168,':',White_word);
	Disp_Num(0,176,Sys_count.s,White_word);

}


