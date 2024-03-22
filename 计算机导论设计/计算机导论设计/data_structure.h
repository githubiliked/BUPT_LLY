#define _CRT_SECURE_NO_WARNINGS 
//#ifndef _DATA_STRUCTURE_H
//#define _DATA_STRUCTURE_H
// -----------
// 防止头文件反复调用、变量重复定义
//#endif
#ifndef _DATA_STRUCTURE_H
#define _DATA_STRUCTURE_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>


//三种策略：
//FCFS  先来先服务
//SSTF  最短寻找时间优先
//SCAN  顺便服务


//必须使用 static 修饰变量， 否则会显示(*.obj)重复定义
static int z = 10;  //？
static int TOTAL_STATION = 5; //总站数为5
static char STRATEGY[5] = "FCFS";  //strategy策略
static int DISTANCE = 2;  //每站之间的距离为2




//数据结构 Bus
static struct Bus {
	int pos;  //位置 
	int state; //状态:1 代表顺时针行驶，-1 代表逆时针行驶， 0 表示静止
} bus;


typedef struct Request { //请求列表
	char type[30];  //type存放顺时针逆时针和车内请求（上下车）
	int station;   //站台
	struct Request* link;
	int t;   //时间
	int m;   // m = 1 代表上车(clockwise/counterclockwise)，反之下车(target)
} Request, * Linklist; // Linklist 是一级指针


#endif
