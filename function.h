#include "data_structure.h"
#ifndef _FUNCTION_H
#define _FUNCTION_H

//VS
#define gets gets_s

//��������
//clockwise, counterclockwise, target ֮һ�����һ�����ֹ���һ������
#define clockwise 1
#define static 0
#define counterclockwise -1



//�ͷ�����
void freelist(Linklist a); 





//struct Request* ���͵Ľڵ㹹���������������������е�ÿ���ڵ��Ϊ������ڵ㡱
//Ѱ���������Ƿ�����λ�� x ������������ͬ�ġ�����ڵ㡱
//Ŀ�ģ��������
int findx1(Linklist* L, int x, char a[]);






//�ж������������Ƿ�������������ͬ�Ľڵ㣬û����嵽���������ĩβ
void Insert(Linklist* L, char a[], int x);





//���һ�������ÿ������ڵ���ǰ��һλ�����һ�������ʼ�����һ����
void shijian(Linklist* L);





//��������Ĭ��ÿ������ڵ�Ϊ�ϳ������һ��(clockwise / counterclockwise)
void gengxin(Linklist* L);



//�жϳ���վ�������������Ƿ��и�վ����ϳ��������򷵻�1
//Ŀ�ģ����ϳ��ĳ˿�
int panm(Linklist* L);




//ɾ������ͷ�ڵ����һ���ڵ㣨ɾ�����ڵ�һλ������ڵ㣩
void Delete1(Linklist* L);



//������ͣ��˳�����վ��ʱ��ͣһ�γ�ֻ������³������ͬ������ϳ�����
//���˳����������ڵ㣬��ɺ�ɾ������ڵ㣬��Ӧ��ĿҪ��7����
void Delete2(Linklist* L, char a[], int x);





//ɾ��λ��Ϊxվ�������ڵ㣬ɾ���ɹ�����1�����򷵻�0
//Ŀ�ģ��������ɾ��������ڵ�
int Delete3(Linklist* L, int x);




//�ļ���ȡ����������Ŀ�涨��Ԥ���ļ��ж�ȡĬ�ϲ���
void FileUpdate(FILE* fp);




//��⵱ǰվ̨��������
int Scan(struct Bus bus, Linklist L);




//���ݳ�����ʻ״̬��֤����������ʻ
void move(struct Bus* bus);




//��⹫���Ƿ���վ̨
int  Daozhan(struct Bus bus);




//�ı䷽�򣨸ú��������ڳ���ʻ��ʱ��ʹ�ã�
int Changedir_SSTF(Linklist* L);





//ѡ���򣬱���Bus.state == 0ʱ��
void choosedir_SSTF(Linklist* L);




//���������ǰ״̬
void Printf_SSTF(struct Bus bus, Linklist L);





//������������Ѱ���Ƿ����λ��Ϊx��վ��
int findx(Linklist* L, int x);






//�ı䷽��-1��ʾ������ 1��ʾ��������0��ʾͣ�¡����ú��������ڳ���ʻ��ʱ��ʹ�ã�
int Changedir(Linklist* L, struct Bus bus);






//�������������
void ChooseFirstDir(Linklist* L);






//�ж���ʻ���򣬱���Bus.state == 0ʱ��
void choosedir(Linklist* L);






// ���������ǰ״̬
void Printf(struct Bus bus, Linklist L);






//ȥ���ո�
void qukongge(char* p);






#endif