#include "data_structure.h"
#ifndef _FUNCTION_H
#define _FUNCTION_H

//VS
#define gets gets_s

//三种请求：
//clockwise, counterclockwise, target 之一后面跟一个数字构成一种请求
#define clockwise 1
#define static 0
#define counterclockwise -1



//释放链表
void freelist(Linklist a); 





//struct Request* 类型的节点构成请求链表，将请求链表当中的每个节点称为“请求节点”
//寻找链表中是否有与位置 x 的请求类型相同的“请求节点”
//目的：完成请求
int findx1(Linklist* L, int x, char a[]);






//判断请求链表中是否有与新请求相同的节点，没有则插到请求链表的末尾
void Insert(Linklist* L, char a[], int x);





//完成一个请求后，每个请求节点向前移一位（完成一个请求后开始完成下一个）
void shijian(Linklist* L);





//更新链表，默认每个请求节点为上车请求的一种(clockwise / counterclockwise)
void gengxin(Linklist* L);



//判断车到站后，请求链表中是否有该站点的上车请求，有则返回1
//目的：接上车的乘客
int panm(Linklist* L);




//删除虚拟头节点的下一个节点（删除排在第一位的请求节点）
void Delete1(Linklist* L);



//公交车停靠顺便服务站点时，停一次车只能完成下车请求和同方向的上车请求。
//完成顺便服务的请求节点，完成后删除请求节点，对应题目要求（7）。
void Delete2(Linklist* L, char a[], int x);





//删除位置为x站点的请求节点，删除成功返回1，否则返回0
//目的：完成请求，删除该请求节点
int Delete3(Linklist* L, int x);




//文件读取函数，从题目规定的预设文件中读取默认参数
void FileUpdate(FILE* fp);




//检测当前站台有无请求
int Scan(struct Bus bus, Linklist L);




//根据车的行驶状态保证车辆环形行驶
void move(struct Bus* bus);




//检测公交是否在站台
int  Daozhan(struct Bus bus);




//改变方向（该函数必须在车行驶的时候使用）
int Changedir_SSTF(Linklist* L);





//选择方向，必须Bus.state == 0时用
void choosedir_SSTF(Linklist* L);




//输出公交当前状态
void Printf_SSTF(struct Bus bus, Linklist L);





//在请求链表中寻找是否存在位置为x的站点
int findx(Linklist* L, int x);






//改变方向，-1表示换方向， 1表示不换方向，0表示停下。（该函数必须在车行驶的时候使用）
int Changedir(Linklist* L, struct Bus bus);






//按最新请求变向
void ChooseFirstDir(Linklist* L);






//判断行驶方向，必须Bus.state == 0时用
void choosedir(Linklist* L);






// 输出公交当前状态
void Printf(struct Bus bus, Linklist L);






//去掉空格
void qukongge(char* p);






#endif