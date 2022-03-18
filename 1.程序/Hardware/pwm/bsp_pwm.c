#include "bsp_pwm.h"

/**************************************************************************
�������ܣ�����������IO��ʼ��
��ڲ�������
����  ֵ����
**************************************************************************/	 
void MiniBalance_Motor_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStructure;
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE); //ʹ��PB�˿�ʱ��
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12|GPIO_Pin_13;	//�˿�����
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;      //�������
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;     //50M
  GPIO_Init(GPIOB, &GPIO_InitStructure);					      //�����趨������ʼ��GPIOB 
}

/* TIM3 CH1 A6  */
void PWM_TIM3_GPIO_Config(void) 
{
  GPIO_InitTypeDef GPIO_InitStructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	// ����Ƚ�ͨ��2 GPIO ��ʼ��
  GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_6;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOA, &GPIO_InitStructure);
	
}

/**
  * @brief  ��ʼ��Ϊ10KHz��ռ�ձ�Ϊ50%�ķ���
  * @param  ��
  * @retval ��
  */
void PWM_TIM3_MODE_Config(void) 
{
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;	
	TIM_OCInitTypeDef  TIM_OCInitStructure;
	// ������ʱ��ʱ��,���ڲ�ʱ��CK_INT=72M
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE);
	
	// �Զ���װ�ؼĴ�����ֵ���ۼ�TIM_Period+1��Ƶ�ʺ����һ�����»����ж�
	TIM_TimeBaseStructure.TIM_Period=(100 - 1);	
	// ����CNT��������ʱ�� = Fck_int/(psc+1)
	TIM_TimeBaseStructure.TIM_Prescaler= 71;	
	// ʱ�ӷ�Ƶ���� ����������ʱ��ʱ��Ҫ�õ�
	TIM_TimeBaseStructure.TIM_ClockDivision=TIM_CKD_DIV1;		
	// ����������ģʽ������Ϊ���ϼ���
	TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up;		
	// �ظ���������ֵ��û�õ����ù�
	TIM_TimeBaseStructure.TIM_RepetitionCounter=0;	
	// ��ʼ����ʱ��
	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure);
	
	// ����ΪPWMģʽ1
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
	// ���ʹ��
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
	// ���ͨ����ƽ��������	
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
	
		// ����Ƚ�ͨ�� 1
	TIM_OCInitStructure.TIM_Pulse = 50;
	TIM_OC1Init(TIM3, &TIM_OCInitStructure);
	TIM_OC1PreloadConfig(TIM3, TIM_OCPreload_Enable);
	
	
		// ʹ�ܼ�����
	TIM_Cmd(TIM3, ENABLE);
}

void PWM_TIM3_Init(void) 
{
	PWM_TIM3_GPIO_Config();
	PWM_TIM3_MODE_Config();
}

void PWM_Ch1_TIM3_Ste(u16 Duty_ch1,FunctionalState NewState) 
{
	TIM_OCInitTypeDef  TIM_OCInitStructure;
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_6 ;    //PWM_OUT

	 if (NewState != DISABLE)
  {
    /* Enable the */
	 GPIO_InitStructure.GPIO_Mode =  GPIO_Mode_AF_PP ;
	 GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	 GPIO_Init(GPIOA, &GPIO_InitStructure);  //��ת���	
		// ����ΪPWMģʽ1
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
	// ���ʹ��
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
	// ���ͨ����ƽ��������	
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;	
		// ����Ƚ�ͨ�� 1
	TIM_OCInitStructure.TIM_Pulse = Duty_ch1;
	TIM_OC1Init(TIM3, &TIM_OCInitStructure);
	TIM_OC1PreloadConfig(TIM3, TIM_OCPreload_Enable);
  }
  else
  {
    /* Disable the  */
	 TIM_OC1PreloadConfig(TIM3, TIM_OCPreload_Disable);
	 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	 GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	 GPIO_Init(GPIOA, &GPIO_InitStructure);
	 GPIOA->ODR &= ~GPIO_Pin_6 ;    //����͵�ƽ	
  }
}

/**************************************************************************
�������ܣ������������
��ڲ�����δ֪
����  ֵ����
**************************************************************************/
void Machinery_Go(void)
{
		AIN2 = 0;
		AIN1 = 1;
}
void Machinery_STOP(void)
{
		AIN2 = 1;
		AIN1 = 1;
}

