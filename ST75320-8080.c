#include "Includeh.h"
uchar vop1=0x23;
uchar vop2=0x00; //Vlcd 11.32V
uchar PAGE;
void Disp_Num(uchar h,int c,int num,uchar color)
{
	uchar buff[3];
	int i;
	//if(num >= 30)
		//num = num - 30;
	//num = num + 5;
	//if(num >= 970)
		//num = 50;
	//num = 123;
	buff[0] = num / 100 + 0x30;
	buff[0] = num % 100 / 10 + 0x30;
	buff[1] = num % 10 + 0x30;
	
	for(i=0;i<=1;i++){
		Disp_16x8_char(h,c + i*8,buff[i],color);
	}
}
void Disp_3Num(uchar h,int c,int num,uchar color)
{
	uchar buff[3];
	int i;
	buff[0] = num / 100 + 0x30;
	buff[1] = num % 100 / 10 + 0x30;
	buff[2] = num % 10 + 0x30;
	
	for(i=0;i<=2;i++){
		Disp_16x8_char(h,c + i*8,buff[i],color);
	}
}
void Disp_clear(uchar h,int c,uchar color)
{
	int page ; 
	int column,hc,lc; 
	uchar temp;
	c = 320 - 8 - c;
	hc = c / 256;
	lc = c & 0xff;
	for( page = 0 ; page< 2; page++)
	{
		com_write (0xb1) ; //Set Page Address
		dat_write (page+h) ; 
		com_write (0x13) ; //Set Column Address
		dat_write (hc) ;	
		dat_write (lc) ;
		com_write (0x1d) ; //Write Data
		for (column = 0 ;column < 8; column ++)
			dat_write(0x00);
	}
}
void Disp_HZstr(uchar h,int c,uchar size,far rom const unsigned char *str,uchar color)
{
	uchar i;
	far rom const uchar *temp;
	uchar len;//用于查找字库
	temp = str;
	i = 0;
	if(size == 16){
		while(len = *temp++)//结尾标志是0x00
		{
			Disp_16x16_hz_1(h,c+i*16,len,color);
			i++;
		}
	}else if(size == 32){
		while(len = *temp++)//结尾标志是0x00
		{
			Disp_32x32_hz(h,c+i*32,len,color);
			i++;
		}
	}else//防止字体调用错误
		return;
}
void Disp_CharStr(uchar h,int c,uchar size,far rom const unsigned char *str,uchar color)
{
	far rom const uchar *temp;
	uchar i;
	temp = str;
	i = 0;
	if(size == 8){
	    while((*str<='~')&&(*str>=' '))//判断是不是非法字符!
	    {       
	        Disp_16x8_char(h,c+i*8,*str,color);
	        str++;
			i++;
	    } 
	}else if(size == 16){
	    while((*str<='~')&&(*str>=' '))//判断是不是非法字符!
	    {       
	        Disp_32x16_char(h,c+i*16,*str,color);
			i++;			
	        str++;
	    } 
	}else//防止字体调用错误
		return;
}
void Disp_16x8_Time_Num(uchar h,int c,uchar num,uchar color)
{
	uchar buff[3],i;
	buff[0] = num / 100 + 0x30;
	buff[0] = num % 100 / 10 + 0x30;
	buff[1] = num % 10 + 0x30;
	for(i=0;i<=1;i++){
		Disp_16x8_char(h,c + i*8,buff[i],color);
	}

}
void Disp_16x8_char(uchar h,int c,uchar num,uchar color)
{
	int page ; 
	int column,hc,lc; 
	uchar temp;
	num = num - ' ';
	c = 320 - 8 - c;
	hc = c / 256;
	lc = c & 0xff;
	for( page = 0 ; page< 2; page++)
	{
		com_write (0xb1) ; //Set Page Address
		dat_write (page+h) ; 
		com_write (0x13) ; //Set Column Address
		dat_write (hc) ;	
		dat_write (lc) ;
		com_write (0x1d) ; //Write Data
		for (column = 0 ;column < 8; column ++)
		{
			temp = asc2_1608[num][column+page*8];
			if((color&0x01)==1)
				dat_write(temp);	
			else{
				temp = ~temp;
				dat_write(temp);
			}
		}
	}

}
void Disp_32x16_char(uchar h,int c,uchar num,uchar color)
{
	int page ; 
	int column,hc,lc; 
	uchar temp;
	num = num - ' ';
	c = 320 - 16 - c;
	hc = c / 256;
	lc = c & 0xff;
	for( page = 0 ; page< 4; page++)
	{
		com_write (0xb1) ; //Set Page Address
		dat_write (page+h) ; 
		com_write (0x13) ; //Set Column Address
		dat_write (hc) ;	
		dat_write (lc) ;
		com_write (0x1d) ; //Write Data
		for (column = 0 ;column < 16; column ++)
		{
			temp = asc2_3216[num][column+page*16];
			if(color)
				dat_write(temp);	
			else{
				temp = ~temp;
				dat_write(temp);
			}
		}
	}
}
/*
void Disp_64x64_hz(uchar h,int c,uchar num,uchar color)
{
	uint page ; 
	uint column,hc,lc; 
	uchar temp;
	c = 320 - 64 - c;
	hc = c / 256;
	lc = c % 256;
	for( page = 0 ; page< 8; page++)
	{
		com_write (0xb1) ; //Set Page Address
		dat_write (page) ; 
		com_write (0x13) ; //Set Column Address
		dat_write (hc) ;	
		dat_write (lc) ;
		com_write (0x1d) ; //Write Data
		for (column = 0 ;column < 64; column ++)
		{
			temp = ziku_64x64[num][column+ page*64];
			if((color&0x01)==1)
				dat_write(temp);	
			else{
				temp = ~temp;
				dat_write(temp);
			}
		}
	} 
}
*/
void Disp_32x32_hz(uchar h,int c,uchar num,uchar color)
{
	uint page ; 
	uint column,hc,lc; 
	uchar temp;
	c = 288 - c;
	hc = c / 256;
	lc = c % 256;
	for( page = 0 ; page<= 3; page++)
	{
		com_write (0xb1) ; //Set Page Address
		dat_write (page+h) ; 
		com_write (0x13) ; //Set Column Address
		dat_write (hc) ;	
		dat_write (lc) ;
		com_write (0x1d) ; //Write Data
		for (column = 0 ;column < 32; column ++)
		{
			temp = ziku_32x32[num][column+ page*32];
			if((color&0x01)==1)
				dat_write(temp);	
			else{
				temp = ~temp;
				dat_write(temp);
			}
		}
	} 
}
void Disp_16x16_hz_1(uchar h,int c,uchar num,uchar color)
{
	uint page ; 
	uint column,hc,lc; 
	uchar temp;
	c = 320 - c - 16;
	hc = c / 256;
	lc = c % 256;
	for( page = 0 ; page<= 1; page++)
	{
		com_write (0xb1) ; //Set Page Address
		dat_write (page+h) ; 
		com_write (0x13) ; //Set Column Address
		dat_write (hc) ;	
		dat_write (lc) ;
		com_write (0x1d) ; //Write Data
		for (column = 0 ;column < 16; column ++)
		{
			temp = ziku_16x16[num][column+ page*16];
			if((color&0x01)==1)
				dat_write(temp);	
			else{
				temp = ~temp;
				dat_write(temp);
			}
		}
	} 

}
/*
void Disp_16x16_hz(uchar h,uchar hc,uchar lc,uchar num,uchar color)
{
	uint page ; 
	uint column; 
	uchar temp;
	for( page = 0 ; page<= 1; page++)
	{
		com_write (0xb1) ; //Set Page Address
		dat_write (page+h) ; 
		com_write (0x13) ; //Set Column Address
		dat_write (hc) ;	
		dat_write (lc) ;
		com_write (0x1d) ; //Write Data
		for (column = 0 ;column < 16; column ++)
		{
			temp = ziku_16x16[num][column+ page*16];
			if((color&0x01)==1)
				dat_write(temp);	
			else{
				temp = ~temp;
				dat_write(temp);
			}
		}
	} 

}
*/
void Disp_64x320_pic(uchar* pic)
{
	far rom const uchar *str;
	uint page ; 
	uint column; 
	str = pic;
	for( page = 0 ; page< 8; page++)
	{
		com_write (0xb1); //Set Page Address
		dat_write (page) ; 
		com_write (0x13) ; //Set Column Address
		dat_write (0x00) ;	
		dat_write (0x00) ;
		com_write (0x1d) ; //Write Data
		for (column = 0 ;column < 320; column ++)
		{
			dat_write(*str++);
		}
	} 
}

void ST75320_Init()
{
	TRISD = 0x00;//setting out
	setBL = 0;
	setCS = 0;
	setRES = 0;
	setA0 = 0;
	setWR1 = 0;
	setRD1 = 0;
	PORTD = 0xff;
	CS = 1;
	RES = 1;
	A0 = 1;
	WR1 = 1;
	RD1 = 1;
	init();
	//delay_ms(20);
	BL = 0;
	delay_ms(20);
	BL = 1;
}

void com_write(uchar com)
{
	CS = 0;
	//delay_us(3);
	A0 = 0;
	//delay_us(3);
	RD1 = 1;
	//delay_us(3);
	
	//PORTD = com;
	LATD = com;
	
	WR1 = 0;
	//delay_us(3);
	//delay_us(3);
	//delay_us(3);
	WR1 = 1;
	//delay_us(3);
	CS = 1;
	//delay_us(3);
}
void dat_write(uchar dat)
{
	CS = 0;
	//delay_us(3);
	A0 = 1;
	//delay_us(3);
	RD1 = 1;
	//delay_us(3);
	
	//PORTD = dat;
	LATD = dat;
	
	WR1 = 0;
	//delay_us(3);
	//delay_us(3);
	//delay_us(3);
	WR1 = 1;
	//delay_us(3);
	CS = 1;
	//delay_us(3);
}
void init(void)
{  
	RES = 1;
	delay_ms(50);
	RES = 0;
	delay_ms(200);
	RES = 1;
	delay_ms(500);
    	
	com_write(0xAE);   //Display OFF
	com_write(0xEA);   //Power Discharge Control
	dat_write(0x00);  //Discharge OFF
	com_write(0xA8);   //sleep out

 ///////////////////////////////////////////////////////////////
		
	com_write(0xAB);   //OSC ON
	com_write(0x69);   //Temperature Detection ON
	com_write(0x4E);   //TC Setting
	dat_write(0x00);  //0mV/癈, should be adjusted by customer
	dat_write(0x00);  //0mV/癈, should be adjusted by customer
	dat_write(0x00);  //0mV/癈, should be adjusted by customer
	dat_write(0x00);  //0mV/癈, should be adjusted by customer
	dat_write(0x00);  //0mV/癈, should be adjusted by customer
	dat_write(0x00);  //0mV/癈, should be adjusted by customer
	dat_write(0x00);  //0mV/癈, should be adjusted by customer
	dat_write(0x00);  //0mV/癈, should be adjusted by customer
	
	com_write(0x39);   //TC Flag
	dat_write(0x00);  //
	dat_write(0x00);  //

	com_write(0x2B);   //Frame Rate Level
	dat_write(0x01);  //
	
	com_write(0x5F);   //Set Frame Frequency
	dat_write(0x00);  //fFR=80Hz in all temperature range
	dat_write(0x00);  //should be adjusted by customer

	com_write(0xEC);   //FR Compensation Temp. Range
	dat_write(0x19);  //TA = -15 degree, should be adjusted by customer
	dat_write(0x2D);  //TB = 5 degree, should be adjusted by customer
	dat_write(0x55);  //TC = 45 degree, should be adjusted by customer		
	
	com_write(0xED);   //Temp. Hysteresis Value (thermal sensitivity)
	dat_write(0x04);  //Vop threshold: +2癈
	dat_write(0x04);  //fFR threshold: +4癈
	
	com_write(0xA6);   //Display Inverse OFF
	com_write(0xA4);   //Disable Display All Pixel ON
	
	com_write(0xC4);   //COM Output Status
	dat_write(0x03);  //Interlace mode, MY=0
	
	com_write(0xA0);   //Column Address Direction: MX=0
	
	com_write(0x6D);   //Display Area
	dat_write(0x01);  //Duty = 1/64 duty
	dat_write(0x00);  //Start Group = 1
	
	com_write(0x84);   //Display Data Input Direction: Column
	
	com_write(0x36);   //Set N-Line
	dat_write(0x33);  //N-Line

	com_write(0xE4);   //N-Line On
	
	com_write(0xE7);   //LCD Drive Method
	dat_write(0x19);  //NLFR=1
		
	com_write(0x81);   //Set EV=64h
	dat_write(vop1);  //VOP=12v					
	dat_write(vop2);  //
	
	com_write(0xA2);   //BIAS
	dat_write(0x03);  //1/9 BIAS

	com_write(0x25);   //Power Control
	dat_write(0x20);  //AVDD ON
	delay_ms(50);

	com_write(0x25);   //Power Control
	dat_write(0x24);  //AVDD, MV3 & NAVDD ON		  26
	delay_ms(50);

	com_write(0x25);   //Power Control
	dat_write(0x64);  //AVDD, MV3, NAVDD & V3 ON      36
	delay_ms(50);

	com_write(0x25);   //Power Control
	dat_write(0x66);  //AVDD, MV3, NAVDD, V3 & VPF ON	3E
	delay_ms(50);


	com_write(0x25);   //Power Control
	dat_write(0x76);  //AVDD, MV3, NAVDD, V3, VPF & VNF ON			3E
	delay_ms(50);

	com_write(0x25);   //Power Control
	dat_write(0x7F);  //VOUT, AVDD, MV3, NAVDD, V3, VPF & VNF ON
	delay_ms(50);
	Disp_dot(0x00,0x00);	
	com_write(0xaf);  //Display ON
    	
}
void Disp_dot(uchar dat1,uchar dat2)
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
			if(column & 0x01)   
				dat_write(dat2);	  
			else   
				dat_write(dat1);	
		}
	} 
}


void Disp_pic(uchar* pic)
{
	uint page ; 
	uint column; 
	far rom const uchar *str;
	str = pic;
	for( page = 0 ; page< 8; page++)
	{
		com_write (0xb1); //Set Page Address
		dat_write (page) ; 
		com_write (0x13) ; //Set Column Address
		dat_write (0x00) ;	
		dat_write (0x00) ;
		com_write (0x1d) ; //Write Data

		for (column = 0 ;column < 320; column ++)
		{
			dat_write(str[column+page * 320]);	
		}
	} 
}

void press(void)
{	
	uint i=0;
	uchar DAT; 
	for (i=0;i<20000;i++)
	{
	  //DAT=P2;
	  delay_ms(80);
	  if (DAT==0xf7)
		{
		 i=20005;
		 vop1++;
		 if(vop1==0xff)
		 {
		 	vop1=0;
			vop2++;
			if(vop2==0x03)
			{
				vop1=0;
				vop2=0;
			}
		 }
	 	 com_write(0x81);   //Set EV=64h
	   dat_write(vop1);  //VOP=12v					
	   dat_write(vop2);  //
		}
	  if (DAT==0xfe)
		{
		 i=20005;
		 if(PAGE<6)
		 ++PAGE;
		 else PAGE=0;
		}
	  if(DAT==0xfb)
	    {
		 i=20005;
		 if(PAGE>0)	 
	     --PAGE;
		 else PAGE=6;
		}
 	  if(DAT==0xfd)
	    {
		 i=20005;
		 vop1--;
		 if(vop1==0)
		 {
		 	vop1=0x3f;
			vop2--;
			if(vop2==0x00)
			{
				vop1=0xff;
				vop2=0x03;
			}
		 }
		  com_write(0x81);   //Set EV=64h
	    dat_write(vop1);  //VOP=12v					
	    dat_write(vop2);  //
		}
	}
}


