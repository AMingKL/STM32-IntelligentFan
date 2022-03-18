#ifndef __bsp_key_H
#define	__bsp_key_H

#include "stm32f10x.h"

#define KEY1  	GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_0)//��ȡ����1
#define KEY2 	 	GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_1)//��ȡ����2
#define KEY3  	GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_2)//��ȡ����3
#define KEY4 	 	GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_3)//��ȡ����4
#define KEY5 	 	GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_4)//��ȡ����5

#define KEY1_PRES	  1	//KEY1����
#define KEY2_PRES   2	//KEY2����
#define KEY3_PRES   3	//KEY3����
#define KEY4_PRES 	4	//KEY4����
#define KEY5_PRES 	5	//KEY5����

#define KEY1_GPIO_PORT    	GPIOA			              /* GPIO�˿� */
#define KEY1_GPIO_CLK 	    RCC_APB2Periph_GPIOA		/* GPIO�˿�ʱ�� */
#define KEY1_GPIO_PIN		    GPIO_Pin_0			        /* ���ӵ�SCLʱ���ߵ�GPIO */

#define KEY2_GPIO_PORT    	GPIOA			              /* GPIO�˿� */
#define KEY2_GPIO_CLK 	    RCC_APB2Periph_GPIOA		/* GPIO�˿�ʱ�� */
#define KEY2_GPIO_PIN		    GPIO_Pin_1			        /* ���ӵ�SCLʱ���ߵ�GPIO */

#define KEY3_GPIO_PORT    	GPIOA			              /* GPIO�˿� */
#define KEY3_GPIO_CLK 	    RCC_APB2Periph_GPIOA		/* GPIO�˿�ʱ�� */
#define KEY3_GPIO_PIN		    GPIO_Pin_2			        /* ���ӵ�SCLʱ���ߵ�GPIO */

#define KEY4_GPIO_PORT    	GPIOA			              /* GPIO�˿� */
#define KEY4_GPIO_CLK 	    RCC_APB2Periph_GPIOA		/* GPIO�˿�ʱ�� */
#define KEY4_GPIO_PIN		    GPIO_Pin_3			        /* ���ӵ�SCLʱ���ߵ�GPIO */

#define KEY5_GPIO_PORT    	GPIOA			              /* GPIO�˿� */
#define KEY5_GPIO_CLK 	    RCC_APB2Periph_GPIOA		/* GPIO�˿�ʱ�� */
#define KEY5_GPIO_PIN		    GPIO_Pin_4			        /* ���ӵ�SCLʱ���ߵ�GPIO */



u8 KEY_Scan(u8);  	//����ɨ�躯��	
void KEY_GPIO_Config(void);
void delay(uint32_t count);

#endif /* __bsp_key_H */

