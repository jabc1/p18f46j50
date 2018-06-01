#include "Includeh.h"

void C_74HC595(unsigned long data,unsigned char s) 
{ 
    unsigned char k,temp,Q1,Q2,Q3;
	Q3 = (data & 0xff0000) >> 16;
	Q2 = (data & 0xff00) >> 8;
	Q1 = data & 0xff;
    temp  = Q3;
    for(k=0;k<8;k++)   //QA,QB,QC,.......
    {   
	     SER_DS = (temp&0x80) >> 7;  //取最高位         
	     temp<<=1;         /*左移位*/   
	     SRCLK_SHCP=0;       /*产生上生沿*/  
		 delay_5us();  
		 SRCLK_SHCP=1; 
    } 
    temp = Q2;
    for(k=0;k<8;k++)   
    {   
	     SER_DS = (temp&0x80) >> 7;  //取最高位         
	     temp<<=1;         /*左移位*/   
	     SRCLK_SHCP=0;       /*产生上生沿*/  
		 delay_5us();  
		 SRCLK_SHCP=1; 
    } 
	
    temp = Q1;
    for(k=0;k<8;k++)   
    {   
	     SER_DS = (temp&0x80) >> 7;        
	     temp<<=1;         
	     SRCLK_SHCP=0;       
		 delay_5us();  
		 SRCLK_SHCP=1; 
    } 
    RCLK_STCP = 0;
	delay_5us();
    RCLK_STCP = 1;
	delay_5us();
    RCLK_STCP = 0;

	//OE_L = s;
}

void Light_Control()
{
	;
}













