#include "Includeh.h"
void high_isr(void); 
//config bit 配置
//#pragma config XINST=OFF
/*
#if 0
unsigned char CONFIG1L=0B10001110;
unsigned char CONFIG1H=0B11110111;
unsigned char CONFIG2L=0B00011000;
unsigned char CONFIG2H=0B11110000;
unsigned char CONFIG3L=0B01100000;
unsigned char CONFIG3H=0B11111001;
unsigned char CONFIG4L=0B01111111;
unsigned char CONFIG4H=0B11110000;
#else
#pragma romdata1 name1=0x300000  
const rom unsigned char CONFIG1L= 0B00000010;  
#pragma romdata1  
#pragma romdata2 name2=0x300001  
const rom unsigned char CONFIG1H= 0B11110111;  
#pragma romdata2
#pragma romdata3 name3=0x300002  
const rom unsigned char CONFIG2L= 0B10001110;  
#pragma romdata3  
#pragma romdata4 name4=0x300003  
const rom unsigned char CONFIG2H= 0B10001110;  
#pragma romdata4  
#pragma romdata5 name5=0x300004  
const rom unsigned char CONFIG3L= 0B10001110;  
#pragma romdata5 
#pragma romdata6 name6=0x300005  
const rom unsigned char CONFIG3H= 0B10001110;  
#pragma romdata6  
#pragma romdata7 name7=0x300006  
const rom unsigned char CONFIG4L= 0B10001110;  
#pragma romdata7  
#pragma romdata8 name8=0x300007  
const rom unsigned char CONFIG4H= 0B10001110;  
#pragma romdata8  
#endif
*/
//中断函数
#pragma code high_vecotr= 0x0008
void interrupt_high_vector (void)
{
	_asm  goto high_isr  _endasm
}
#pragma code


//==============变量定义区域
PDx_Time		Countflag;
PDx_Time		CountSec;
extern Sys_Temp	Sys_count;
extern unsigned char Key_temp_flag;
volatile RECEIVE_BUF Uart_recBuf;
extern int Uart1_rtimer;
//==================end


void main(void)
{
	static unsigned char Time_flag = 0x22;
	ST75320_Init();
	Init_Sys();
	Init_PDx();
	Init_IO();
	Init_Time1();
	Init_Uart1();
	Init_PDx_temp();
	delay_ms(1200);
	while(1){
		//TestIO = !TestIO;
		if(Time_flag==0x22){
			Time_flag = 0x00;
			U_transfer(Query_Systiem);
		}
		if(Uart1_rtimer-- > 0){
			if(Uart1_rtimer==0)
				U_Hand();
		}
		Key_function();
		PDx_function();
	}
}



//中断处理函数
#pragma interruptlow high_isr
void high_isr(void)
{
	static unsigned char ch = 0;
	//INTCONbits.GIE = 0;  
	if(PIR1bits.TMR1IF){//1ms 
      	PIR1bits.TMR1IF = 0;
		TMR1H = (65536-systemHZ)/256;     
		TMR1L = (65536-systemHZ)%256;
		//TestIO = !TestIO;
		if(Sys_count.ms ++ >= 999)
		{
			Sys_count.ms = 0;
			Sys_count.s_flag = 1;
			Init_PDx();
			if(Sys_count.s++ >=59){
				Sys_count.s = 0;
				Sys_count.min_flag = 1;
				Star_Time();//一分钟时间间隔
				if(Sys_count.min ++>=59){
					Sys_count.min = 0;
					Sys_count.hour_flag = 1;
					if(Sys_count.hour++>=23){
						Sys_count.hour = 0;
					}
				}	
			}
		}
		if(Sys_count.ms % 10 == 0)
			Key_temp_flag = 1;
		
		if(Sys_count.ms % 250 == 0)
			Time1_S_Flag();
	}
	
	if(PIR1bits.RC1IF){
		PIR1bits.RC1IF = 0;
		//TXREG1 = RCREG1; 		
		Uart1_rtimer = 40;
		ch = RCREG1;
		if(Uart_recBuf.length < 150){					
		    Uart_recBuf.Buffer[Uart_recBuf.length++] = ch;
			Uart_recBuf.Buffer[Uart_recBuf.length] = 0;
			if(Uart_recBuf.length >= 150){
				Uart_recBuf.length = 0;
			}
		}
	}

}









