/**
  *************************************************************************************************************************
  * @file    myconfig.c
  * @author  ������
  * @version V1.0
  * @date    2021-12-28
  * @brief   ���ú���
  *************************************************************************************************************************
  * @attention
  *
  * 
  *
  *************************************************************************************************************************
  */

/* Includes -------------------------------------------------------------------------------------------------------------*/
#include "myconfig.h"

/* �������� -----------------------------------------------------------------------------------------------------------------*/
int temperature;
unsigned char Timers[TIMERCOUNT];
extern volatile uchar menuEvent;
extern SYSTEM SYSTEM_Para;

/**
 * @brief  �����ʱ��
 * @param  xIndex-�¼�x��xTime-��ʱʱ��
 * @retval ��
 */
unsigned char xDelay(unsigned char xIndex,unsigned char xTime)
{
	unsigned char RetValue=TIMEISNOTUP;

	if(Timers[xIndex]==0)//�ж�ָ�������ʱ���ļ������Ƿ�Ϊ 0
	{
		Timers[xIndex]=xTime;//��װ��������ֵ
		RetValue=TIMEISUP;	 //��ֵ����ֵΪ��ʱ�䵽	
	}
	return(RetValue);
}

void SystemPara_Init(void)
{
 	SYSTEM_Para.HIGH_TEMP=35;
	SYSTEM_Para.LOW_TEMP=20;
	SYSTEM_Para.LEVEL=ONEGEAR;
	SYSTEM_Para.MODEL=MANUAL;
}

void DS18B20_Proc(void)
{
	temperature=DS18B20_Get_Temp();//����¶�
}

void Control_Proc(void)
{
	switch(SYSTEM_Para.MODEL)
	{
		case 0:FANMANUAL_PROC();break;//�ֶ�
		case 1:FANAUTO_PROC();break;//�Զ�
		case 2:FANVOICE_PROC();break;//����
		default:break;
	}
}

void FANMANUAL_PROC(void)
{
 	switch(SYSTEM_Para.LEVEL)
	{
		case 0:Machinery_STOP();PWM_Ch1_TIM3_Ste(50,DISABLE);break;//�ر�
		case 1:Machinery_Go();PWM_Ch1_TIM3_Ste(30,ENABLE);break;//һ��
		case 2:Machinery_Go();PWM_Ch1_TIM3_Ste(60,ENABLE);break;//����
		case 3:Machinery_Go();PWM_Ch1_TIM3_Ste(90,ENABLE);break;//����
		default:break;
	}
}



void FANAUTO_PROC(void)
{
  if(People_testing==1)//����
 {
  Machinery_Go();
	if(temperature<230)
	{
	 PWM_Ch1_TIM3_Ste(30,ENABLE);
	}
	else if((temperature>230)&&(temperature<300))
	{
		PWM_Ch1_TIM3_Ste(60,ENABLE);
	}
	else
	{
		PWM_Ch1_TIM3_Ste(90,ENABLE);
	}
 }
 else if(People_testing==0)//û����
 {
	Machinery_STOP();PWM_Ch1_TIM3_Ste(50,DISABLE);
 }
}

void FANVOICE_PROC(void)
{
  if(voice_ONEGEAR==1)
	{
	 Machinery_Go();PWM_Ch1_TIM3_Ste(30,ENABLE);
	}
	 else if(voice_TWOGEAR==1)
	{
	 Machinery_Go();PWM_Ch1_TIM3_Ste(60,ENABLE);
	}
   else if(voice_THREEGEAR==1)
	{
	 Machinery_Go();PWM_Ch1_TIM3_Ste(90,ENABLE);
	}
	 else  if(voice_ShutDOWN==1)
	{
	 Machinery_STOP();PWM_Ch1_TIM3_Ste(50,DISABLE);
	}
}

void Buzzer_Alarm(void)
{
  if(temperature>500)
	{
	 Buzzer_ON;
	}
	else
	{
	 Buzzer_OFF;
	}
}

void Key_Proc(void)
{
  switch(KEY_Scan(0))
	{
		case 1: menuEvent=KEY_enter;break;
		case 2: menuEvent=KEY_down;break;
		case 3: menuEvent=KEY_esc;break;
		case 4: menuEvent=NUM_up;break;
		case 5: menuEvent=NUM_down;break;
		default:break;
	}
}

/**
 * @brief  ��ʱ��4�жϷ�����-10ms�ж�
 * @param  ��
 * @retval ��
 */
void TIM4_IRQHandler(void)
{
	static uint8_t Index;
	
	if(TIM_GetITStatus(TIM4,TIM_IT_Update) == 1) 
	{
		TIM_ClearITPendingBit(TIM4,TIM_IT_Update);
		
		//Ϊÿһ�������ʱ���е��жϴ��������� 1��ֱ����ֵΪ 0
		for(Index=0;Index<TIMERCOUNT;Index++)
		if(Timers[Index]>0)
		Timers[Index]--;
	}
}
