#ifndef _MENU_H_
#define _MENU_H_

#include "stm32f10x.h"

//---�ض���ؼ���---//
#ifndef uchar
#define uchar unsigned char
#endif

#ifndef uint 
#define uint unsigned int
#endif

#define KEY_NULL 	0x05				//�������¼�
#define KEY_down 	0x07				//���°����¼���־
#define KEY_enter 0x08			  //���밴���¼���־
#define KEY_esc		0x09				//���ذ����¼���־
#define NUM_up 		0x0B				//��ֵ�Ӱ����¼���־
#define NUM_down 	0x0C				//��ֵ�������¼���־


typedef struct{
	uchar current_index;	//��ŵ�ǰ����������ţ�
	uchar down_index;		  //��Ű��¡�down�����£�����ʱ��Ҫ��ת���������ţ�
	uchar enter_index;		//��Ű��¡�enter�����룩����ʱ��Ҫ��ת�������ţ�
	uchar esc_index;		  //��Ű��¡�esc���˳�������ʱ��Ҫ��ת�������ţ�
	void (*operate)();	  //����ָ���������ŵ�ǰ����������Ҫִ�еĺ�������ڵ�ַ��
}Key_index_struct;

typedef enum// �˵�����
{
	home,
	temp_set,
	level_set,
	model_set,
	hightemp_set,
	lowtemp_set,
	chooselevel_set,
	choosemodel_set,
	MENU_NUM, // �˵�ҳ����
}MENU_INDEX_LIST;


void mainWindow(void);//������
void menu_temp_set(void);
void menu_level_set(void);
void menu_model_set(void);
void menu_hightemp_set(void);
void menu_lowtemp_set(void);
void menu_chooselevel_set(void);
void menu_choosemodel_set(void);
void menuEventHandle(void);
#endif /*_MENU_H_*/
