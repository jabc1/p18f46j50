#ifndef _UART_H
#define _UART_H
//#define BTL_16
#ifdef BTL_16
#define 	Fosc 				27000000       
#define 	BAUD 				115200            
#define 	BRG 				((Fosc/BAUD)/16)-1   
#else
#define 	Fosc 				27000000       
#define 	BAUD 				38400            
#define 	BRG 				((Fosc/BAUD)/4)-1   
#endif


//�������
#define				Testmain			0x0a
#define				Infomation			0x0b
#define				Clear_Result		0x0c
#define				Time_s				0x0d
#define				T_AD				0x0f

//������������
#define				PDxStar				0xa0//��ָʾ��
#define 			PDxEnd				0xa1//���Խ���
#define				PDxRefuse			0xa2//�����н�ָʾ���ó�
#define				PDxTestTime			0xa3//����ģʽ
#define				SysTemperature		0xa4//�����¶�
#define				PDxTestMode			0xa5//����ģʽ
#define				PDxTestResult		0xa6//���Խ��
#define				SysTimeCrc			0xa7//ʱ�����
//#define				



void frist_page_information(void);
void Init_Uart1(void);
void UART1PutChar(unsigned char Ch);
void Uart1_Send( unsigned char * pCmd );
void U_Hand(void);
void Init_UartTemp(void);
void Test_PDxfunction(unsigned char cmd);
void Test_PDxStar(void);
void Test_PDxEnd(void);
void Test_PDxRefuse(void);
void Test_PDxTestMode(void);
void Clear_PDxResult(unsigned char flag,unsigned char pdx);
void Start_time(void);
void show_t(void);




#define MAX_RECEIVE_BUFFER 200
typedef struct  
{
	volatile char Buffer[MAX_RECEIVE_BUFFER];
	volatile unsigned char length;
} RECEIVE_BUF;

typedef struct{
	unsigned char PD1;
	unsigned char PD2;
	unsigned char PD3;
	unsigned char PD4;
	unsigned char PD5;
	unsigned char PD6;
	unsigned char PD7;
	unsigned char PD8;
	unsigned char PD9;
	unsigned char PD10;
}PDx_f;

#endif




