#ifndef _KEY_H
#define _KEY_H
#define 	KEY_STATE_0 			0 //°´¼ü×´Ì¬
#define 	KEY_STATE_1 			1
#define 	KEY_STATE_2 			2
#define 	KEY1_STATE_2 			3
#define 	KEY2_STATE_2 			4
#define 	KEY3_STATE_2 			5
#define		KEY12_STATE_2			7
#define 	KEY_STATE_3 			6
#define 	KEY_Up_Confirm 			8
#define		KEY_Down_Confirm		9



#define		set_Key_1			TRISBbits.TRISB0
#define		set_Key_2			TRISBbits.TRISB1
#define		set_Key_3			TRISBbits.TRISB2

#define 	Key_1				PORTBbits.RB0
#define 	Key_2				PORTBbits.RB1
#define 	Key_3				PORTBbits.RB2


#define 	LONG_KEY_TIME 				180 //LONG_KEY_TIME*10MS = 3S
#define 	SINGLE_KEY_TIME 			3 	//SINGLE_KEY_TIME*10MS = 50MS
#define 	KEY_NONE 					0   //no click
#define 	KEY1_SHORT 					1   //single press
#define 	KEY1_LONG 					10  //long press
#define 	KEY2_SHORT 					2   //single press
#define 	KEY2_LONG 					20  //long press
#define 	KEY3_SHORT 					3   //single press
#define 	KEY3_LONG 					30  //long press
#define 	KEY12_SHORT 				4   //single press
#define 	KEY12_LONG 					40  //long press
#define		KEY_Up_Confirm_SHORT		5
#define		KEY_Up_Confirm_LONG			50
#define		KEY_Down_Confirm_SHORT		6
#define		KEY_Down_Confirm_LONG		60

#define		Key1_Vaule					0x06
#define		Key2_Vaule					0x05
#define		Key3_Vaule					0x03
#define 	Key12_Vaule					0x04
#define		KeyUp_Confirm_Value			0x01
#define		KeyDown_Confirm_Value		0x02	
#define		Key_TQ						0x07
#define		test_k_v					0
void Key_Init(void);
void Key_function(void);
unsigned char key_driver(void);
unsigned char test_key_driver(void);

#endif




