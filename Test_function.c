#include "Includeh.h"
extern Sys_Temp	Sys_count;
extern volatile RECEIVE_BUF Uart_recBuf;
void Test_Uart(void)
{
	unsigned char ji,jk,Buff[20];
	if(Sys_count.s_flag == 1){
		Sys_count.s_flag = 0;
		
		//for(ji=0;ji<18;ji++)
			//Buff[ji] = 'a'+ji;
		//Buff[18] = '\n';
		//Buff[19] = 0;
		

	}

		Uart1_Send(Uart_recBuf.Buffer);
		for(jk=0;jk<150;jk++)
			Uart_recBuf.Buffer[jk] = 0;
		Uart_recBuf.length = 0;
	
}

void Test_show_7(int temp,char PDx)
{
#if 0
	int temp1 ;
	temp1 =0;
	temp1 = PDx*33;
	if(temp1 > 296)
		temp1 = 296;
	Disp_clear(0,temp1,0x00);
	//delay_ms(10);
	Disp_Num(0,temp1,temp,0);
#else
	if(PDx==0){
		Disp_clear(6,0,0XFF);
		//delay_ms(10);
		Disp_Num(6,0,temp,1);
	}
	if(PDx==1){
		Disp_clear(6,33,0XFF);
		//delay_ms(10);
		Disp_Num(6,33,temp,1);
	}
	if(PDx==2){
		Disp_clear(6,2*33,0XFF);
		//delay_ms(10);
		Disp_Num(6,2*33,temp,1);
	}

	if(PDx==3){
		Disp_clear(6,3*33,0XFF);
		//delay_ms(10);
		Disp_Num(6,3*33,temp,1);
	}
	if(PDx==4){
		Disp_clear(6,132,0XFF);
		//delay_ms(10);
		Disp_Num(6,132,temp,1);
	}	
	if(PDx==5){
		Disp_clear(6,165,0XFF);
		//delay_ms(10);
		Disp_Num(6,165,temp,1);
	}
	if(PDx==6){
		Disp_clear(6,198,0XFF);
		//delay_ms(10);
		Disp_Num(6,198,temp,1);
	}
	if(PDx==7){
		Disp_clear(6,231,0XFF);
		//delay_ms(10);
		Disp_Num(6,231,temp,1);
	}
	if(PDx==8){
		Disp_clear(6,264,0XFF);
		//delay_ms(10);
		Disp_Num(6,264,temp,1);
	}
	if(PDx==9){
		Disp_clear(6,296,0XFF);
		//delay_ms(10);
		Disp_Num(6,296,temp,1);
	}
#endif

}
void Test_Show(void)
{
	delay_ms(1000);
	delay_ms(500);
	C_74HC595(0XAAAAAA, ON);
	delay_ms(1000);
	C_74HC595(PD_all, OFF);	
	delay_ms(1000);
	C_74HC595(0X555555, ON);
	delay_ms(1000);
	C_74HC595(PD_all, OFF);
	delay_ms(1000);
	Disp_dot(0xff,0xff);
	delay_ms(1000);
	Disp_32x32_hz(0,210,0,1);
	Disp_32x32_hz(0,210+32,1,0);
		
	delay_ms(1000);
	Disp_16x8_char(2,0+0*8,11,0);
	Disp_16x8_char(2,0+1*8,12,0);
	Disp_16x8_char(2,0+2*8,6,0);
	Disp_16x8_char(2,0+3*8,37,0);
	Disp_16x8_char(2,0+4*8,38,0);
	Disp_16x8_char(2,0+5*8,10,0);
		
	Disp_16x8_char(4,0+0*8,11,1);
	Disp_16x8_char(4,0+1*8,12,1);
	Disp_16x8_char(4,0+2*8,6,1);
	Disp_16x8_char(4,0+3*8,37,1);
	Disp_16x8_char(4,0+4*8,38,1);
	Disp_16x8_char(4,0+5*8,10,1);
	Disp_dot(0xff,0xff);
	delay_ms(1000);

}
void Test_74HC595(void)
{
	static char temp = 0;
	static unsigned long test = 0xfffffe;
	if(Sys_count.s_flag == 1){
		Sys_count.s_flag = 0;
		if((temp++ % 2)== 0){
			//TXREG1 = 'a'; 
			test = ((test << 1 | 0x01)& 0xffffff);
			C_74HC595(test , ON);
			if(temp >= 40){
				temp = 0;
				test = 0xfffffe;
			}
		}
		else{
			C_74HC595(test , OFF);
		}
	}
}















