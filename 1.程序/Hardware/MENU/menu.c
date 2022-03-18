/**
  *************************************************************************************************************************
  * @file    menu.c
  * @author  amkl
  * @version V2.0
  * @date    2022-03-17
  * @brief   �˵�ʵ���ļ�
  *************************************************************************************************************************
  * @attention
  * 
  * 
  * 
  *************************************************************************************************************************
***/

#include "menu.h"
#include "myconfig.h"

unsigned char volatile nowMenuIndex = 0;
extern int temperature;
volatile unsigned char menuEvent;
SYSTEM SYSTEM_Para;


/*
�ο�����
https://blog.csdn.net/embedded_guzi/article/details/35835755
https://blog.csdn.net/calmuse/article/details/79346742
*/
Key_index_struct Key_table[MENU_NUM]=
{
    //��ǰ�ַ������ţ�����������Ҫ��ת�������� �����½�����Ҫ��ת�������� ,������һ����
    {home,		       home,	         temp_set,	       home , 		 (*mainWindow)},		        //һ�������һ��
    {temp_set,		   level_set,	     hightemp_set,	   home , 		 (*menu_temp_set)},		      //���������һ��
		{level_set,		   model_set,	     chooselevel_set,	 home , 		 (*menu_level_set)},		    //��������ڶ���
		{model_set,		   temp_set,	     choosemodel_set,	 home , 		 (*menu_model_set)},		    //�������������
		{hightemp_set,	 lowtemp_set,    hightemp_set,     temp_set ,	 (*menu_hightemp_set)},		  //���������һ��
		{lowtemp_set,		 hightemp_set, 	 lowtemp_set, 		 temp_set ,	 (*menu_lowtemp_set)},		  //��������ڶ���
		{chooselevel_set,chooselevel_set,chooselevel_set,  level_set , (*menu_chooselevel_set)},  //�������������
		{choosemodel_set,choosemodel_set,choosemodel_set,  model_set , (*menu_choosemodel_set)},  //�������������
};

void OLED_display(void)
	{
	switch(menuEvent){
		case KEY_down: //����
			nowMenuIndex=Key_table[nowMenuIndex].down_index; 
			break;
		case KEY_enter://����
			nowMenuIndex=Key_table[nowMenuIndex].enter_index;
			break;
		case KEY_esc://����
			nowMenuIndex=Key_table[nowMenuIndex].esc_index;
			break;
		case NUM_down:
			break;
		case NUM_up:
			break;
		default: ;break;
	}
	Key_table[nowMenuIndex].operate();
}

//�˵��¼������������²˵����桢���ݴ���
void menuEventHandle(void)
{
	OLED_display();
	if(menuEvent==NUM_up)
	{	
		if(nowMenuIndex==hightemp_set)
		{
			(SYSTEM_Para.HIGH_TEMP>=60)?(SYSTEM_Para.HIGH_TEMP=60):(SYSTEM_Para.HIGH_TEMP++);
			menu_hightemp_set();
		}
		else if(nowMenuIndex==lowtemp_set)
		{
			(SYSTEM_Para.LOW_TEMP>=25)?(SYSTEM_Para.LOW_TEMP=25):(SYSTEM_Para.LOW_TEMP++);
			menu_lowtemp_set();
		}
		else if(nowMenuIndex==chooselevel_set)
		{	
			(SYSTEM_Para.LEVEL>=3)?(SYSTEM_Para.LEVEL=3):(SYSTEM_Para.LEVEL++);
			menu_chooselevel_set();
		}
		else if(nowMenuIndex==choosemodel_set)
		{	
			SYSTEM_Para.MODEL=(SYSTEM_Para.MODEL+1)%3;
    	menu_choosemodel_set();
		}
	}
	if(menuEvent==NUM_down)
	{
		if(nowMenuIndex==hightemp_set)
		{
			(SYSTEM_Para.HIGH_TEMP<=30)?(SYSTEM_Para.HIGH_TEMP=30):(SYSTEM_Para.HIGH_TEMP--);
			menu_hightemp_set();
		}
		else if(nowMenuIndex==lowtemp_set)
		{
			(SYSTEM_Para.LOW_TEMP<=10)?(SYSTEM_Para.LOW_TEMP=10):(SYSTEM_Para.LOW_TEMP--);
			menu_lowtemp_set();
		}
			else if(nowMenuIndex==chooselevel_set)
		{	
			(SYSTEM_Para.LEVEL<=0)?(SYSTEM_Para.LEVEL=0):(SYSTEM_Para.LEVEL--);
			menu_chooselevel_set();
		}
		else if(nowMenuIndex==choosemodel_set)
		{	
			SYSTEM_Para.MODEL=(SYSTEM_Para.MODEL+1)%3;
    	menu_choosemodel_set();
		}
	}
	menuEvent = KEY_NULL;
}

void mainWindow(void)
{
	OLED_ShowString(0,0,"      MAIN      ",16);
	OLED_ShowString(0,16,"TEMP:   . C",16);
	
	switch(SYSTEM_Para.LEVEL)
	{
		case 0:OLED_ShowString(0,32,"LEVEL:OFF      ",16);break;//�ر�
		case 1:OLED_ShowString(0,32,"LEVEL:ONEGEAR  ",16);break;//һ��
		case 2:OLED_ShowString(0,32,"LEVEL:TWOGEAR  ",16);break;//����
		case 3:OLED_ShowString(0,32,"LEVEL:THREEGEAR",16);break;//����
		default:break;
	}
	switch(SYSTEM_Para.MODEL)
	{
		case 0:OLED_ShowString(0,48,"MODEL:MANUAL   ",16);break;//�ֶ�
		case 1:OLED_ShowString(0,48,"MODEL:AUTO     ",16);break;//�Զ�
		case 2:OLED_ShowString(0,48,"MODEL:VOICE    ",16);break;//����
		default:break;
	}
	
	if(temperature<0)
	{
		OLED_ShowChar(40,16,'-',16);	           //��ʾ����
		temperature=-temperature;		           //תΪ����
	}
	else OLED_ShowChar(40,16,' ',16);             //ȥ������
	OLED_ShowNum(40+8,16,temperature/10,2,16);   //��ʾ����
	OLED_ShowNum(40+8+24,16,temperature%10,1,16);//��ʾС������	
	
	OLED_Refresh(); 
}


void menu_temp_set(void)
{
	OLED_ShowString(0,0,"    SET_PARA    ",16);
	OLED_ShowString(0,16,">>Temp         ",16);
	OLED_ShowString(0,32,"  LEVEL        ",16);
	OLED_ShowString(0,48,"  MODEL        ",16);
	
	OLED_Refresh(); 
}

void menu_level_set(void)
{
	OLED_ShowString(0,0,"    SET_PARA    ",16);
	OLED_ShowString(0,16,"  Temp         ",16);
	OLED_ShowString(0,32,">>LEVEL        ",16);
	OLED_ShowString(0,48,"  MODEL        ",16);
	
	OLED_Refresh(); 
}

void menu_model_set(void)
{
	OLED_ShowString(0,0,"    SET_PARA    ",16);
	OLED_ShowString(0,16,"  Temp         ",16);
	OLED_ShowString(0,32,"  LEVEL        ",16);
	OLED_ShowString(0,48,">>MODEL        ",16);
	
	OLED_Refresh(); 
}



void menu_hightemp_set(void)
{
	OLED_ShowString(0,0,"    SET_TEMP    ",16);
	OLED_ShowString(0,16,"               ",16);
	OLED_ShowString(0,32,">>HighTemp:   C",16);
	OLED_ShowString(0,48,"  LowTemp :   C",16);	
	OLED_ShowNum(92,32,SYSTEM_Para.HIGH_TEMP,2,16);
  OLED_ShowNum(92,48,SYSTEM_Para.LOW_TEMP,2,16);   //��ʾ����
	OLED_Refresh(); 
}

void menu_lowtemp_set(void)
{
	OLED_ShowString(0,0,"    SET_TEMP    ",16);
	OLED_ShowString(0,16,"               ",16);
	OLED_ShowString(0,32,"  HighTemp:   C",16);
	OLED_ShowString(0,48,">>LowTemp :   C",16);
	OLED_ShowNum(92,32,SYSTEM_Para.HIGH_TEMP,2,16);
  OLED_ShowNum(92,48,SYSTEM_Para.LOW_TEMP,2,16);   //��ʾ����
	OLED_Refresh(); 
}

void menu_chooselevel_set(void)
{
	OLED_ShowString(0,0,"    SET_LEVEL     ",16);
	OLED_ShowString(0,16,"               ",16);
	OLED_ShowString(0,48,"               ",16);
	switch(SYSTEM_Para.LEVEL)
	{
		case 0:OLED_ShowString(0,32,"LEVEL:OFF      ",16);break;//�ر�
		case 1:OLED_ShowString(0,32,"LEVEL:ONEGEAR  ",16);break;//һ��
		case 2:OLED_ShowString(0,32,"LEVEL:TWOGEAR  ",16);break;//����
		case 3:OLED_ShowString(0,32,"LEVEL:THREEGEAR",16);break;//����
		default:break;
	}	
	OLED_Refresh(); 
}

void menu_choosemodel_set(void)
{
	OLED_ShowString(0,0,"    SET_MODEL     ",16);
	switch(SYSTEM_Para.MODEL)
	{
		case 0:OLED_ShowString(0,32,"MODEL:MANUAL   ",16);break;//�ֶ�
		case 1:OLED_ShowString(0,32,"MODEL:AUTO     ",16);break;//�Զ�
		case 2:OLED_ShowString(0,32,"MODEL:VOICE    ",16);break;//����
		default:break;
	}	
	OLED_ShowString(0,16,"               ",16);
	OLED_ShowString(0,48,"               ",16);
	OLED_Refresh(); 
}


