#ifndef _ST75320_H
#define	_ST75320_H
#define 		uint 			unsigned int
#define 		uchar 			unsigned char


#define 		setBL			TRISAbits.TRISA5
#define			BL				LATAbits.LATA5
#define			setRB5			TRISBbits.TRISB5
#define			rb				PORTBbits.RB5

#define			setCS 			TRISBbits.TRISB3//TRISCbits.TRISC5
#define			setRES			TRISEbits.TRISE2//TRISCbits.TRISC4
#define			setA0 			TRISCbits.TRISC2
#define			setWR1			TRISEbits.TRISE1//TRISCbits.TRISC1
#define			setRD1			TRISEbits.TRISE0//TRISCbits.TRISC0

#define			CS 				LATBbits.LATB3//LATCbits.LATC5
#define			RES				LATEbits.LATE2//LATCbits.LATC4
#define			A0 				LATCbits.LATC2
#define			WR1				LATEbits.LATE1//LATCbits.LATC1
#define			RD1				LATEbits.LATE0//LATCbits.LATC0

void ST75320_Init(void);
void com_write(uchar com);
void dat_write(uchar dat);
void init(void);
void Disp_dot(uchar dat1,uchar dat2);
void Disp_pic(uchar* pic);
void press(void);
void Disp_64x320_pic(uchar* pic);
void Disp_HZstr(uchar h,int c,uchar size,far rom const unsigned char *str,uchar color);
void Disp_CharStr(uchar h,int c,uchar size,far rom const unsigned char *str,uchar color);
void Disp_16x8_char(uchar h,int c,uchar num,uchar color);
void Disp_16x16_hz_1(uchar h,int c,uchar num,uchar color);
void Disp_32x32_hz(uchar h,int c,uchar num,uchar color);
//void Disp_64x64_hz(uchar h,int c,uchar num,uchar color);
void Disp_Num(uchar h,int c,int num,uchar color);
void Disp_clear(uchar h,int c,uchar color);
void Disp_32x16_char(uchar h,int c,uchar num,uchar color);
void Disp_16x8_Time_Num(uchar h,int c,uchar num,uchar color);
void Disp_3Num(uchar h,int c,int num,uchar color);
#endif



