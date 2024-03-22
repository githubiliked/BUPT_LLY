#define _CRT_SECURE_NO_WARNINGS 
//#ifndef _DATA_STRUCTURE_H
//#define _DATA_STRUCTURE_H
// -----------
// ��ֹͷ�ļ��������á������ظ�����
//#endif
#ifndef _DATA_STRUCTURE_H
#define _DATA_STRUCTURE_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>


//���ֲ��ԣ�
//FCFS  �����ȷ���
//SSTF  ���Ѱ��ʱ������
//SCAN  ˳�����


//����ʹ�� static ���α����� �������ʾ(*.obj)�ظ�����
static int z = 10;  //��
static int TOTAL_STATION = 5; //��վ��Ϊ5
static char STRATEGY[5] = "FCFS";  //strategy����
static int DISTANCE = 2;  //ÿվ֮��ľ���Ϊ2




//���ݽṹ Bus
static struct Bus {
	int pos;  //λ�� 
	int state; //״̬:1 ����˳ʱ����ʻ��-1 ������ʱ����ʻ�� 0 ��ʾ��ֹ
} bus;


typedef struct Request { //�����б�
	char type[30];  //type���˳ʱ����ʱ��ͳ����������³���
	int station;   //վ̨
	struct Request* link;
	int t;   //ʱ��
	int m;   // m = 1 �����ϳ�(clockwise/counterclockwise)����֮�³�(target)
} Request, * Linklist; // Linklist ��һ��ָ��


#endif
