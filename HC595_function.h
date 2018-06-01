#ifndef _HC595_H
#define _HC595_H
#define 		PD1_Red				0xFFFFFE
#define			PD1_Green			0xFFFFFD
#define 		PD2_Red				0xFFFFFB
#define			PD2_Green			0xFFFFF7
#define 		PD3_Red				0xFFFFEF
#define			PD3_Green			0xFFFFDF
#define 		PD4_Red				0xFFFFBF
#define			PD4_Green			0xFFFF7F
#define 		PD5_Red				0xFFFEFF
#define			PD5_Green			0xFFFDFF
#define 		PD6_Red				0xFFFBFF
#define			PD6_Green			0xFFF7FF
#define 		PD7_Red				0xFFEFFF
#define			PD7_Green			0xFFDFFF
#define 		PD8_Red				0xFFBFFF
#define			PD8_Green			0xFF7FFF
#define 		PD9_Red				0xFEFFFF
#define			PD9_Green			0xFDFFFF
#define 		PD10_Red			0xFBFFFF
#define			PD10_Green			0xF7FFFF
#define			PD_all				0xffffff
void C_74HC595(unsigned long data,unsigned char s) ;
void Light_Control();




#endif





