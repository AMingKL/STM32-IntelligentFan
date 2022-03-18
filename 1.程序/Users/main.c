/**
  *************************************************************************************************************************
  * @file    main.c
  * @author  AMINGKL
  * @version V1.0
  * @date    2022-03-17
  * @brief   ����stm32-�๦�ܷ���
  *************************************************************************************************************************
  * @attention
	Ӳ������
  L298N:
	AIN1-PB13
	AIN1-PB14
	ENA-PA6
	
	OLED:
	SCL:PB6
	CLK:PB7
	
	����:
	KEY1��PA0
	KEY2-PA1
	KEY3��PA2
	KEY4-PA3
	KEY5��PA4
	
	DS18B20:
	DATA-PB12
	
	����
	infrared-PA5
	
	����ģ��
	ONEGEAR-PA8
	TWOGEAR-PA9
	THREEGEAR-PA10
	ShutDOWN-PA11
	
  ������
  PB0	
  *************************************************************************************************************************
  */
/* Includes -------------------------------------------------------------------------------------------------------------*/
#include "myconfig.h"
/* �������� -----------------------------------------------------------------------------------------------------------------*/
void All_Init(void);

 

int main(void)
{	
	All_Init();
	while(1)
	{	
		/*10ms��ȡһ�ΰ����������д���*/
		if(xDelay(TIMERINDEX1,1)  == TIMEISUP)
		{
			Key_Proc();
			menuEventHandle();
		}
		/*1s��ȡһ���¶�*/ 		
		if(xDelay(TIMERINDEX2,100)  == TIMEISUP)
		{
			DS18B20_Proc();
			Buzzer_Alarm();
		} 
		Control_Proc();
	}
}


void All_Init(void)
{
 	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	delay_init();	
	KEY_GPIO_Config();
	OLED_Init();
	Tim4_Init();
	PWM_TIM3_Init();	
	while(DS18B20_Init())//����¶ȴ�����
	{
		OLED_ShowString(64,45,"Error",16);//�¶ȴ�����������
	}
	SystemPara_Init();
	Infrared_GPIO_Config();
	BUZZER_GPIO_Config();
	Voice_GPIO_Config();
	PWM_Ch1_TIM3_Ste(30,ENABLE);
	OLED_Clear();
}


/*****************************************************END OF FILE*********************************************************/	

