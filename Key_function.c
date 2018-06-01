#include "Includeh.h"
unsigned char Key_temp_flag;

void Key_function()
{
	if(Key_temp_flag == 1){
		Key_temp_flag = 0 ;
		key_scan();
	}
}

unsigned char key_driver()
{
    static unsigned char key_state = KEY_STATE_0;    //����״̬����
    static unsigned int key1_time,key2_time,key3_time,key4_time,key5_time,key6_time; //������ʱ����
    unsigned char key_press, key_return;
    key_return = KEY_NONE;        //������ذ���ֵ
    key_press =  PORTB & 0x07;	
	switch (key_state)
	{
		case KEY_STATE_0://�Ƿ��а���������
			if(key_press == Key1_Vaule){
				key_state = KEY_STATE_1; 
			}else
			if(key_press == Key2_Vaule){
				key_state = KEY_STATE_1; 
			}else
			if(key_press == Key3_Vaule){
				key_state = KEY_STATE_1; 
			}else
			if(key_press == Key12_Vaule){
				key_state = KEY_STATE_1; 
			}else
			if(key_press == KeyUp_Confirm_Value){
				key_state = KEY_STATE_1; 
			}else
			if(key_press == KeyDown_Confirm_Value){
				key_state = KEY_STATE_1; 
			}else
			key1_time = 0;
			key2_time = 0;
			key3_time = 0;
			key4_time = 0;
			key5_time = 0;
			key6_time = 0;
			break;
		case KEY_STATE_1://�ж��ǲ�����
			if(key_press == Key1_Vaule){//�Ǳ�����
				if(key1_time++>=SINGLE_KEY_TIME){
					key_state = KEY1_STATE_2;
				}
			}else
			if(key_press == Key2_Vaule){
				if(key2_time++>=SINGLE_KEY_TIME){
					key_state = KEY2_STATE_2;
				}
			}else
			if(key_press == Key3_Vaule){
				if(key3_time++>=SINGLE_KEY_TIME){
					key_state = KEY3_STATE_2;
				}
			}else
			if(key_press == Key12_Vaule){
				if(key4_time++>=SINGLE_KEY_TIME){
					key_state = KEY12_STATE_2;
				}
			}else
			if(key_press == KeyUp_Confirm_Value){
				if(key5_time++>=SINGLE_KEY_TIME){
					key_state = KEY_Up_Confirm;
				}
			}else
			if(key_press == KeyDown_Confirm_Value){
				if(key6_time++>=SINGLE_KEY_TIME){
					key_state = KEY_Down_Confirm;
				}
			}
			else//��
				key_state = KEY_STATE_0;
			break;
			
		case KEY1_STATE_2:
			if(key_press == Key_TQ){//��������˵���Ƕ̰�
				key_return = KEY1_SHORT;//������������״̬
				key_state = KEY_STATE_0;//�������״̬
			}else{//˵����1����
				if (key1_time++ >= LONG_KEY_TIME){
					key_return = KEY1_LONG;
					key_state = KEY_STATE_3; 
				}
			}
			break;
		case KEY2_STATE_2:
			if(key_press == Key_TQ){//��������˵���Ƕ̰�
				key_return = KEY2_SHORT;//������������״̬
				key_state = KEY_STATE_0;//�������״̬
			}else{//˵����2����
				if (key1_time++ >= LONG_KEY_TIME){
					key_return = KEY2_LONG;
					key_state = KEY_STATE_3; 
				}
			}
			break;
		case KEY3_STATE_2:
			if(key_press == Key_TQ){//��������˵���Ƕ̰�
				key_return = KEY3_SHORT;//������������״̬
				key_state = KEY_STATE_0;//�������״̬
			}else{//˵����3����
				if (key1_time++ >= LONG_KEY_TIME){
					key_return = KEY3_LONG;
					key_state = KEY_STATE_3; 
				}
			}
			break;
		case KEY12_STATE_2:
			if(key_press == Key_TQ){
				key_return = KEY12_SHORT;//������������״̬
				key_state = KEY_STATE_0;//�������״̬
			}else{
				if (key4_time++ >= LONG_KEY_TIME){
					key_return = KEY12_LONG;
					key_state = KEY_STATE_3; 
				}
			}
			break;
		case KEY_Up_Confirm:
			if(key_press == Key_TQ){
				key_return = KEY_Up_Confirm_SHORT;//������������״̬
				key_state = KEY_STATE_0;//�������״̬
			}else{
				if (key5_time++ >= LONG_KEY_TIME){
					key_return = KEY_Up_Confirm_LONG;
					key_state = KEY_STATE_3; 
				}
			}
			break;
		case KEY_Down_Confirm:
			if(key_press == Key_TQ){
				key_return = KEY_Down_Confirm_SHORT;//������������״̬
				key_state = KEY_STATE_0;//�������״̬
			}else{
				if (key6_time++ >= LONG_KEY_TIME){
					key_return = KEY_Down_Confirm_LONG;
					key_state = KEY_STATE_3; 
				}
			}
			break;
		case KEY_STATE_3://�ȴ������ͷ�
			if (key_press == Key_TQ){
				key_state = KEY_STATE_0;
			}
			break;
			
		default:
			key_state = KEY_STATE_0;
			break;
		}
	return key_return;
}
unsigned char test_key_driver()
{
	static unsigned char key_state = KEY_STATE_0;    //����״̬����
    static unsigned int key1_time=0;      //������ʱ����
    unsigned char key_press, key_return;
	//key_press = 0;
    key_return = KEY_NONE;        // ��� ���ذ���ֵ
    key_press = (PORTB & 0x07) >> 1;
    //key_press = Key_2;
	switch (key_state)
	{
		case KEY_STATE_0://�Ƿ��а���������
			if(key_press == test_k_v)
			{
				key1_time = 0;
				key_state = KEY_STATE_1; 
			}
			break;
		case KEY_STATE_1://�ж��ǲ�����
			if(key_press == test_k_v){//�Ǳ�����
				if(key1_time++>=SINGLE_KEY_TIME){
					key_state = KEY1_STATE_2;
				}
			}
			else//��
				key_state = KEY_STATE_0;
			break;
		case KEY1_STATE_2:
			if(key_press != test_k_v){//��������˵���Ƕ̰�
				key_return = KEY1_SHORT;//������������״̬
				key_state = KEY_STATE_0;//�������״̬
			}else{//˵���ǳ���
				if (key1_time++ >= LONG_KEY_TIME){
					key_return = KEY1_LONG;
					key_state = KEY_STATE_3; 
				}
			}
			break;
		case KEY_STATE_3://�ȴ������ͷ�
			if (key_press != test_k_v){//�����ͷż�ֵ״̬
				key_state = KEY_STATE_0;
			}
			break;
			
		default:
			key_state = KEY_STATE_0;
			break;
		}
	return key_return;
}

#if 0//backup 
unsigned char test_key_driver()
{
	static unsigned char key_state = KEY_STATE_0;    //����״̬����
    static unsigned int key1_time=0;      //������ʱ����
    unsigned char key_press, key_return;
	//key_press = 0;
    key_return = KEY_NONE;        // ��� ���ذ���ֵ
    key_press = PORTB & 0x02;
    //key_press = Key_2;
	switch (key_state)
	{
		case KEY_STATE_0://�Ƿ��а���������
			if(key_press == test_k_v)
			{
				key1_time = 0;
				key_state = KEY_STATE_1; 
			}
			break;
		case KEY_STATE_1://�ж��ǲ�����
			if(key_press == test_k_v){//�Ǳ�����
				if(key1_time++>=SINGLE_KEY_TIME){
					key_state = KEY1_STATE_2;
				}
			}
			else//��
				key_state = KEY_STATE_0;
			break;
		case KEY1_STATE_2:
			if(key_press != test_k_v){//��������˵���Ƕ̰�
				key_return = KEY1_SHORT;//������������״̬
				key_state = KEY_STATE_0;//�������״̬
			}else{//˵���ǳ���
				if (key1_time++ >= LONG_KEY_TIME){
					key_return = KEY1_LONG;
					key_state = KEY_STATE_3; 
				}
			}
			break;
		case KEY_STATE_3://�ȴ������ͷ�
			if (key_press != test_k_v){//�����ͷż�ֵ״̬
				key_state = KEY_STATE_0;
			}
			break;
			
		default:
			key_state = KEY_STATE_0;
			break;
		}
	return key_return;
}


#endif





