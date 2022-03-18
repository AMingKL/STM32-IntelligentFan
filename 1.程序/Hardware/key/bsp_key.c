#include "bsp_key.h" 
#include "delay.h"



void KEY_GPIO_Config(void)
{		
		/*����һ��GPIO_InitTypeDef���͵Ľṹ��*/
		GPIO_InitTypeDef GPIO_InitStructure;
		/*����LED��ص�GPIO����ʱ��*/
		RCC_APB2PeriphClockCmd(KEY1_GPIO_CLK, ENABLE);
		/*ѡ��Ҫ���Ƶ�GPIO����*/
		GPIO_InitStructure.GPIO_Pin = KEY1_GPIO_PIN|KEY2_GPIO_PIN|KEY3_GPIO_PIN|KEY4_GPIO_PIN|KEY5_GPIO_PIN;	
		/*��������ģʽΪ��������*/
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;   
		/*���ÿ⺯������ʼ��GPIO*/
		GPIO_Init(KEY1_GPIO_PORT, &GPIO_InitStructure);	

}
//����������
//���ذ���ֵ
//mode:0,��֧��������;1,֧��������;
//0��û���κΰ�������
//1��KEY1����
//2��KEY2����
//3��KEY3����
//4��KEY4����
//5��KEY5����
//ע��˺�������Ӧ���ȼ�,KEY1>KEY2>KEY3>KEY4>KEY5!!

uint8_t KEY_Scan(uint8_t mode)
{	 
	static uint8_t key_up=1;//�������ɿ���־
	if(mode)key_up=1;  //֧������		  
	if(key_up&&(KEY1==0||KEY2==0||KEY3==0||KEY4==0||KEY5==0))
	{
		delay_ms(10);//ȥ���� 
		key_up=0;
		if(KEY1==0)   return       KEY1_PRES;
		else if(KEY2==0)return     KEY2_PRES;
		else if(KEY3==0)return     KEY3_PRES;
		else if(KEY4==0)return     KEY4_PRES;
		else if(KEY5==0)return     KEY5_PRES;
	}else if (KEY1==1&&KEY2==1&&KEY3==1&&KEY4==1&&KEY5==1)key_up=1; 	    
 	return 0;// �ް�������
}

