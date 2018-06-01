#ifndef _INIT_IO_H
#define _INIT_IO_H
#include "p18f46j50.h"

#define 	setRCLK_STCP 		TRISAbits.TRISA0
#define 	setSRCLK_SHCP		TRISAbits.TRISA1
#define 	setSER_DS			TRISAbits.TRISA2
#define 	setOE_L				TRISAbits.TRISA3
#define 	RCLK_STCP			LATAbits.LATA0
#define 	SRCLK_SHCP			LATAbits.LATA1
#define 	SER_DS				LATAbits.LATA2
#define		OE_L				LATAbits.LATA3

#define		ON					0
#define		OFF					1

#define		setTX				TRISCbits.TRISC6
#define		TX					PORTCbits.RC6
#define		setTestIO			TRISBbits.TRISB5//TRISDbits.TRISD4
#define 	TestIO				LATBbits.LATB5//PORTDbits.RD4//   

void delay_5us(void);
void Init_IO(void);
void Init_Sys(void);
void Init_PDx(void);
void PDx_function(void);
void Disp_time_main(void);
void Init_PDx_temp(void);

#endif







