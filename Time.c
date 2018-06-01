#include "Includeh.h"
unsigned char test_flag111;
Sys_Temp		Sys_count;
Start_Time		Time_info;
void Init_Time1()
{
#if 0
	INTCON = 0x20;  //disable global and enable TMR0 interrupt   
	INTCON2 = 0x84; //TMR0 high priority   
	RCONbits.IPEN = 1;//enable priority levels   
	TMR0H = 0; //clear timer   
	TMR0L = 0;//clear timer    
	T0CON = 0x82;//set up timer0 - prescaler 1:8   
	INTCONbits.GIEH = 1;//enable interrupts   
#else
	T1CONbits.TMR1CS1 = 0;
	T1CONbits.TMR1CS0 = 1;
	T1CONbits.T1CKPS1 = 0;
	T1CONbits.T1CKPS0 = 0;
	T1CONbits.T1OSCEN = 1;
	T1CONbits.T1SYNC = 0;
	T1CONbits.RD16 = 1;
	TMR1H = (65536-systemHZ)/256;     
	TMR1L = (65536-systemHZ)%256;
	T1CONbits.TMR1ON = 1;

	IPR1bits.TMR1IP = 0;
	PIE1bits.TMR1IE = 1;//使能中断
	PIR1bits.TMR1IF = 1;//中断标志

	INTCONbits.GIEH  = 1;       //enable interrupts switch
	INTCONbits.PEIE  = 1;       //外设中断允许位
#endif
}




void delay_us(int us_25)
{
	int i;
	for(i=us_25;i>0;i--);
}


void delay_ms(int ms)
{
	int i,j;
	for(i=ms;i>0;i--)
		for(j=95;j>0;j--);
}
void Time1_S_Flag(){
	test_flag111 = 1;
}

void Star_Time()
{
	if(Time_info.min++>=59){
		Time_info.min = 0;
		if(Time_info.hour++>=23){
			Time_info.day++;
		}
	}
}


