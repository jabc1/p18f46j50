#include "Includeh.h"
extern volatile unsigned char Set_buff[6];
extern volatile unsigned char Show_buff[6];
extern volatile unsigned char SetTime_buff[6];
frist_page			Frist_Info;
extern Sys_Temp		Sys_count;
extern PDx_Time		CountSec;
extern PDx_Time		Countflag;
extern PDx_Time	PDx_result_flag;
extern PDx_Time	PDx_start;//用来缓存倒计时时间
extern Show_flag	Show;
extern PDx_Time		PDx_result;
extern ST_flag		T_Star;
extern volatile RECEIVE_BUF Uart_recBuf;
PDx_f		PDx_star;
unsigned char PDx_Result;
int Uart1_rtimer;
void Init_UartTemp()
{
	unsigned char jk;
	for(jk=0;jk<150;jk++)
		Uart_recBuf.Buffer[jk] = 0;
	Uart_recBuf.length = 0;
	
}
void Init_Uart1()
{
#if 0
	SPBRG=BRG;
	//串口工作方式使能 
	TXSTAbits.SYNC=0;
	TXSTAbits.BRGH=1; 
	TXSTAbits.TX9=0; 
	RCSTAbits.SPEN=1; 
	RCSTAbits.RX9=0; 
	//中断使能  
	INTCONbits.GIE=1;
	INTCONbits.PEIE=1;
	PIE1bits.RCIE=1; 
	PIE1bits.TXIE=0;
	//接收使能
	RCSTAbits.CREN=1;
	TRISCbits.TRISC7   = 1;            //RX - input 
	TRISCbits.TRISC6   = 0;            //Tx - output  
	PIR1bits.RC1IF     = 0;            //clear the receive interrupt flag

#else
	BAUDCON1 = 0b00001000; //配置波特率控制寄存器
	SPBRGH1  = 0x00;       //configure the baud register , SPBRGH1 is baud register high 8bits,SPBRG1 is baud register low 8bits	
	SPBRG1   = BRG;//38400  //0xcf   9600
	
	TXSTA1   = 0b00100100;	   //configure the mode register  发送状态和控制寄存器
	RCSTA1   = 0b10010000;	   //configure the mode register

	TRISCbits.TRISC7   = 1;            //RX - input 
	TRISCbits.TRISC6   = 0;            //Tx - output  

	PIR1bits.RC1IF  = 0;            //clear the receive interrupt flag
	//PIR1bits.TXIF	= 0;			//disable tx
	IPR1bits.TX1IP  = 1;               //set the receive is High priority level         
    IPR1bits.RC1IP  = 1;               //set the transmit is High priority level        
    PIE1bits.RC1IE  = 1;//0            //disable the receive interrupt       
    PIE1bits.TX1IE  = 0;               //disable the transmit interrupt
    //RCONbits.IPEN   = 0;               //enable priority levels
    INTCONbits.PEIE = 1;               //enable all peripheral equipment interrupt   
    INTCONbits.GIE  = 1;               //open all interrupt switch    
#endif
	Init_UartTemp();
}
void Uart_Init1()
{
	BAUDCON1bits.BRG16=1;//16位波特率
	TXSTA1bits.BRGH=1;//高速波特率
	SPBRG1=BRG;//115200波特率
	BAUDCON1bits.RXDTP=0;
	TXSTA1bits.TX9=0;
	TXSTA1bits.BRGH=0;
	TXSTA1bits.SYNC=0;//异步模式
	BAUDCON1bits.TXCKP=0;//空闲时TX为高电平
	TXSTA1bits.TXEN=1;//使能发送
	RCSTA1bits.CREN=1;//使能接收
	RCSTA1bits.SPEN=1;//使能串口
	PIE1bits.RC1IE=1;//允许接收中断
	PIR1bits.RC1IF=0;//清零接收中断
	IPR1bits.RC1IP=1;//高优先级
}
void UART1PutChar(unsigned char Ch)
{  
	uint i = 0;   
    while(TXSTAbits.TRMT == 0)//0 TSR 满
    {
    	if(i++>=20000)
     	{
       		Init_Uart1();
       		break; 
     	}  
    }
	TXSTAbits.TXEN=1;//发送使能  
    TXREG1 = Ch; 
    //Nop();
    //Nop();
    //Nop();
}

void Uart1_Send( unsigned char * pCmd )
{
	unsigned char ch;
    while ( ch = *pCmd++  )
	{
		UART1PutChar( ch );
	}	
}

void U_Hand()
{
/*
5c 5d 协议头 0-1
11 12 格式 2-3
0a 命令类型 4
a0 命令 5
00 00 00 00 00 00 00 ....内容 6-n
5e 结束 n+1
*/
	volatile unsigned char CMD_TYPE,CMD;
	unsigned char jk;

//测试命令 5c 5d 51 52 0a a0 13 13
	CMD_TYPE = Uart_recBuf.Buffer[4];
	CMD = Uart_recBuf.Buffer[5];
	switch(CMD_TYPE){
		case Testmain://5c 5d 51 52 0a xx
			Test_PDxfunction(CMD);
			break;
		case Clear_Result://5c 5d 51 52 0c 13 xx//5c 5d 51 52 0c 13 19
			Clear_PDxResult(CMD,Uart_recBuf.Buffer[6]);
			break;
		case Time_s://5c 5d 51 52 0d xx
			Start_time();
			break;
		case T_AD://5c 5d 51 52 0f xx
			show_t();
			break;
		case 0xac:
			frist_page_information();
			break;
		default:
			break;
	}
	//一次处理一次的数据重新接受数据
	Uart1_Send(Uart_recBuf.Buffer);	
	for(jk=0;jk<150;jk++)
		Uart_recBuf.Buffer[jk] = 0;
	Uart_recBuf.length = 0;

}
void frist_page_information()
{
	SetTime_buff[0] = Frist_Info.year = Uart_recBuf.Buffer[5];
	SetTime_buff[1] = Frist_Info.month = Uart_recBuf.Buffer[6];
	SetTime_buff[2] = Frist_Info.day = Uart_recBuf.Buffer[7];
	SetTime_buff[3] = Frist_Info.hour = Uart_recBuf.Buffer[8];
	SetTime_buff[4] = Frist_Info.min = Uart_recBuf.Buffer[9];
	SetTime_buff[5] = Frist_Info.sec = Uart_recBuf.Buffer[10];
	Frist_Info.week= Uart_recBuf.Buffer[11];
	Set_buff[0] = Frist_Info.mode = Uart_recBuf.Buffer[12];
	Set_buff[1] = Frist_Info.beep = Uart_recBuf.Buffer[13];
}
void show_t()
{
	Sys_count.T = Uart_recBuf.Buffer[5];
}
void Start_time()
{
	Sys_count.year = Uart_recBuf.Buffer[5];
	Sys_count.month = Uart_recBuf.Buffer[6];
	Sys_count.day = Uart_recBuf.Buffer[7];
	Sys_count.hour = Uart_recBuf.Buffer[8];
	Sys_count.min = Uart_recBuf.Buffer[9];
	Sys_count.s = Uart_recBuf.Buffer[10];
}
void Test_PDxfunction(unsigned char cmd)
{
	switch(cmd){
		case PDxStar://5c 5d 51 52 0a a0 11
			Test_PDxStar();//开始测试
			break;
		case PDxEnd://5c 5d 51 52 0a a1 12
			Test_PDxEnd();//测试结束
			break;
		case PDxRefuse://5c 5d 51 52 0a a2 xx
			Test_PDxRefuse();//测试中途拿出指示剂
			break;
		case PDxTestMode://5c 5d 51 52 0a a5 xx
			Test_PDxTestMode();//测试模式选择
			break;
		default:
			break;
	}
}

void Test_PDxStar()//只是用于开始标志位
{
	Show.Start_flag = Uart_recBuf.Buffer[6];//开始标志位
	//Uart_recBuf.Buffer[7];//通道选择
	//Uart_recBuf.Buffer[8];//倒计时时间
	if(Show.Start_flag == 0x11){//倒计时功能
		switch(Uart_recBuf.Buffer[7]){
			case 0x10:
				T_Star.PD1 = 0x21;//开始显示倒计时
				PDx_start.PD1 = Uart_recBuf.Buffer[8];
				Countflag.PD1 = 1;//开始进行记时
				CountSec.PD1 = 0;
				break;
			case 0x11:
				T_Star.PD2 = 0x21;//开始显示倒计时
				PDx_start.PD2 = Uart_recBuf.Buffer[8];
				Countflag.PD2 = 1;//开始进行记时
				CountSec.PD2 = 0;
				break;
			case 0x12:
				T_Star.PD3 = 0x21;//开始显示倒计时
				PDx_start.PD3 = Uart_recBuf.Buffer[8];
				Countflag.PD3 = 1;//开始进行记时
				CountSec.PD3 = 0;
				break;
			case 0x13:
				T_Star.PD4 = 0x21;//开始显示倒计时
				PDx_start.PD4 = Uart_recBuf.Buffer[8];
				Countflag.PD4 = 1;//开始进行记时
				CountSec.PD4 = 0;
				break;
			case 0x14:
				T_Star.PD5 = 0x21;//开始显示倒计时
				PDx_start.PD5 = Uart_recBuf.Buffer[8];
				Countflag.PD5 = 1;//开始进行记时
				CountSec.PD5 = 0;
				break;
			case 0x15:
				T_Star.PD6 = 0x21;//开始显示倒计时
				PDx_start.PD6 = Uart_recBuf.Buffer[8];
				Countflag.PD6 = 1;//开始进行记时
				CountSec.PD6 = 0;
				break;
			case 0x16:
				T_Star.PD7 = 0x21;//开始显示倒计时
				PDx_start.PD7 = Uart_recBuf.Buffer[8];
				Countflag.PD7 = 1;//开始进行记时
				CountSec.PD7 = 0;
				break;
			case 0x17:
				T_Star.PD8 = 0x21;//开始显示倒计时
				PDx_start.PD8 = Uart_recBuf.Buffer[8];
				Countflag.PD8 = 1;//开始进行记时
				CountSec.PD8 = 0;
				break;
			case 0x18:
				T_Star.PD9 = 0x21;//开始显示倒计时
				PDx_start.PD9 = Uart_recBuf.Buffer[8];
				Countflag.PD9 = 1;//开始进行记时
				CountSec.PD9 = 0;
				break;
			case 0x19:
				T_Star.PD10 = 0x21;//开始显示倒计时
				PDx_start.PD10 = Uart_recBuf.Buffer[8];
				Countflag.PD10 = 1;//开始进行记时
				CountSec.PD10 = 0;
				break;
			default:
				break;
		}
	}
}

void Test_PDxEnd()
{
//用于显示测试结果页面
//Uart_recBuf.Buffer[6]结束标志位
//Uart_recBuf.Buffer[7]通道选择
//Uart_recBuf.Buffer[8]结果阴性或阳性
//Uart_recBuf.Buffer[9]结果标志位
	Show.End_flag = Uart_recBuf.Buffer[6];
	if(Show.End_flag==0x12){
		switch(Uart_recBuf.Buffer[7]){
			case 0x10:
				PDx_result.PD1 = Uart_recBuf.Buffer[8];//测试结果标志位
				PDx_result_flag.PD1 = 0x10;//用于得到结果时间标志位
				T_Star.PD1 = 0;
				Countflag.PD1 = 0;
				break;
			case 0x11:
				PDx_result.PD2 = Uart_recBuf.Buffer[8];//测试结果标志位
				PDx_result_flag.PD2 = 0x11;
				T_Star.PD2 = 0;
				Countflag.PD2 = 0;
				break;
			case 0x12:
				PDx_result.PD3 = Uart_recBuf.Buffer[8];//测试结果标志位
				PDx_result_flag.PD3 = 0x12;
				T_Star.PD3 = 0;
				Countflag.PD3 = 0;
				break;
			case 0x13:
				PDx_result.PD4 = Uart_recBuf.Buffer[8];//测试结果标志位
				PDx_result_flag.PD4 = 0x13;
				T_Star.PD4 = 0;
				Countflag.PD4 = 0;
				break;
			case 0x14:
				PDx_result.PD5 = Uart_recBuf.Buffer[8];//测试结果标志位
				PDx_result_flag.PD5 = 0x14;
				T_Star.PD5 = 0;
				Countflag.PD1 = 0;
				break;
			case 0x15:
				PDx_result.PD6 = Uart_recBuf.Buffer[8];//测试结果标志位
				PDx_result_flag.PD6 = 0x15;
				T_Star.PD6 = 0;
				Countflag.PD5 = 0;
				break;
			case 0x16:
				PDx_result.PD7 = Uart_recBuf.Buffer[8];//测试结果标志位
				PDx_result_flag.PD7 = 0x16;
				T_Star.PD7 = 0;
				Countflag.PD1 = 0;
				break;
			case 0x17:
				PDx_result.PD8 = Uart_recBuf.Buffer[8];//测试结果标志位
				PDx_result_flag.PD8 = 0x17;
				T_Star.PD8 = 0;
				Countflag.PD6 = 0;
				break;
			case 0x18:
				PDx_result.PD9 = Uart_recBuf.Buffer[8];//测试结果标志位
				PDx_result_flag.PD9 = 0x18;
				T_Star.PD9 = 0;
				Countflag.PD1 = 0;
				break;
			case 0x19:
				PDx_result.PD10 = Uart_recBuf.Buffer[8];//测试结果标志位
				PDx_result_flag.PD10 = 0x19;
				T_Star.PD10 = 0;
				Countflag.PD1 = 0;
				break;
			default:
				break;
		}
	}
}
void Clear_PDxResult(unsigned char flag,unsigned char pdx)
{
//用于清除指定测试结果页面
//flag结束标志位
//pdx通道选择
	if(flag==0x13){
		switch(pdx){
			case 0x10:
				Disp_clear_xy(2,6,0,0+24,Black_word);	
				PDx_result_flag.PD1 = 0;
				break;
			case 0x11:
				Disp_clear_xy(2,6,32,32+24,Black_word);	
				PDx_result_flag.PD2 = 0;
				break;
			case 0x12:
				Disp_clear_xy(2,6,65,65+24,Black_word);	
				PDx_result_flag.PD3 = 0;
				break;
			case 0x13:
				Disp_clear_xy(2,6,98,98+24,Black_word);
				PDx_result_flag.PD4 = 0;
				break;
			case 0x14:
				Disp_clear_xy(2,6,131,131+24,Black_word);	
				PDx_result_flag.PD5 = 0;
				break;
			case 0x15:
				Disp_clear_xy(2,6,164,164+24,Black_word);	
				PDx_result_flag.PD6 = 0;
				break;
			case 0x16:
				Disp_clear_xy(2,6,197,197+24,Black_word);	
				PDx_result_flag.PD7 = 0;
				break;
			case 0x17:
				Disp_clear_xy(2,6,230,230+24,Black_word);	
				PDx_result_flag.PD8 = 0;
				break;
			case 0x18:
				Disp_clear_xy(2,6,263,263+24,Black_word);	
				PDx_result_flag.PD9 = 0;
				break;
			case 0x19:
				Disp_clear_xy(2,6,296,296+24,Black_word);	
				PDx_result_flag.PD10 = 0;
				break;
			default:
				break;
		}
	}
}
void Test_PDxRefuse()
{
	unsigned char PD_x_refuse,PD_x_refuse_flag;
	PD_x_refuse = Uart_recBuf.Buffer[6];//PDx接近传感器标志位
	PD_x_refuse_flag = Uart_recBuf.Buffer[7];//内容
	switch(PD_x_refuse){
		case 0x10:
			break;
		case 0x11:
			break;
		case 0x12:
			break;
		case 0x13:
			break;
		case 0x14:
			break;
		case 0x15:
			break;
		case 0x16:
			break;
		case 0x17:
			break;
		case 0x18:
			break;
		case 0x19:
			break;

		default:
			break;
	}
}
void Test_PDxTestMode()
{
	unsigned char PD_x_testmode,PD_x_testmode_flag;
	PD_x_testmode = Uart_recBuf.Buffer[6];//PDx接近传感器标志位
	PD_x_testmode_flag = Uart_recBuf.Buffer[7];//内容
	switch(PD_x_testmode){
		case 0x10:
			break;
		case 0x11:
			break;
		case 0x12:
			break;
		case 0x13:
			break;
		case 0x14:
			break;
		case 0x15:
			break;
		case 0x16:
			break;
		case 0x17:
			break;
		case 0x18:
			break;
		case 0x19:
			break;

		default:
			break;
	}
}







