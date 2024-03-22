#include "data_structure.h"







//————————————————————————————————————————————————————————————————————
void freelist(Linklist a) { //释放链表
	Linklist b = a, c;

	while (b != NULL) {
		c = b->link;
		free(b);
		b = c;
	}
	a = NULL;
}
//————————————————————————————————————————————————————————————————————








//————————————————————————————————————————————————————————————————————
//struct Request* 类型的节点构成请求链表，将请求链表当中的每个节点称为“请求节点”
//寻找链表中是否有与位置 x 的请求类型相同的“请求节点”    
//目的：完成请求
int findx1(Linklist* L, int x, char a[]) {   //x是位置， a[]是请求之一
	struct Request* temp = *L;				 
	struct Request* temp2 = temp->link;
	//————————————————————————————————————————
	int kk = 0;   //kk起标记作用，表示删除节点成功为1，否则为0。详细请见函数  int Delete3(Linklist* L, int x)；
	//————————————————————————————————————————
	while (temp2 != NULL) {
		if ((temp2->station - 1) * DISTANCE == x && strcmp(temp2->type, a) == 0) { 
			//请求链表从头开始遍历，x所在位置必须是站点才行（寻找与该节点请求相同的x站点）
			//找到了，返回1
			return 1;
		}
		else {
			temp = temp->link;
			temp2 = temp2->link;
		}
	}
	//没找到，返回0
	return 0;
}
//————————————————————————————————————————————————————————————————————









//————————————————————————————————————————————————————————————————————
//将新请求插入到请求链表的末尾
void Insert(Linklist* L, char a[], int x) {   
	//a[]表示目标顺时针逆时针三者之一，x表示站点


	struct Request* temp1 = (struct Request*)malloc(sizeof(struct Request));
	temp1->link = NULL;
	temp1->station = x;  //创建临时存放新请求的temp1


	//题目要求（5）：如果在某个请求没有完成时再有相同的请求（请求类型和站点全部相同才是相同）发生，则该请求被抛弃（不影响策略指标的计算，
	// 既不计入等待请求数，又不计入已完成请求数）。如果已完成的请求再次发生时应按新请求处理。



	//判断请求链表中是否有与新请求相同的节点，有则忽略此次新请求
	if (findx1(L, (x - 1) * DISTANCE, a)) return;



	//没有则插到链表的末尾
	strcpy(temp1->type, a);
	temp1->t = 1; //初始化时间
	struct Request* temp2 = *L;

	while (temp2->link != NULL) {
		temp2 = temp2->link;
	}
	temp2->link = temp1;   //将temp1的请求数据添加到链表末端
}
//————————————————————————————————————————————————————————————————————










//————————————————————————————————————————————————————————————————————
//完成一个请求后，每个请求节点向前移一位
void shijian(Linklist* L) {
	struct Request* temp = (struct Request*)malloc(sizeof(struct Request));
	temp->link = NULL;
	struct Request* temp2 = *L;

	while (temp2->link != NULL) {

		temp2 = temp2->link;
		temp2->t -= 1;
		//	printf(" %d\n\n",temp2->t);
	}
}
//————————————————————————————————————————————————————————————————————









//————————————————————————————————————————————————————————————————————
//更新链表，默认每个请求节点为上车请求的一种
void gengxin(Linklist* L) {
	struct Request* temp = (struct Request*)malloc(sizeof(struct Request));
	temp->link = NULL;
	struct Request* temp2 = *L;

	while (temp2->link != NULL) {

		temp2 = temp2->link;
		temp2->m = 1;   //temp2->m值为1即表示该请求不为目标请求（也就是上车请求）
	}
}
//————————————————————————————————————————————————————————————————————









//————————————————————————————————————————————————————————————————————
//判断车到站后（对应题目中的目标站），请求链表中是否有该站点的上车请求，有则返回1，否则返回0
//目的：接上车的乘客
int panm(Linklist* L) {
	struct Request* temp = (struct Request*)malloc(sizeof(struct Request));
	temp->link = NULL;
	struct Request* temp2 = *L;

	while (temp2->link != NULL) {

		temp2 = temp2->link;

		if ((temp2->station - 1) * DISTANCE == bus.pos && temp2->m == 1) {//temp2->m值为1即表示上车

			return 1;
		}
	}
	return 0;
}
//————————————————————————————————————————————————————————————————————










//————————————————————————————————————————————————————————————————————
//删除虚拟头节点的下一个节点（删除排在第一位的请求节点）
void Delete1(Linklist* L) {
	struct Request* temp = *L;
	struct Request* temp2 = temp->link;
	int m = temp2->station;

	while (temp2 != NULL) {
		if (m == temp2->station) {
			temp->link = temp2->link;
			temp2 = temp2->link;
		}
		else {
			return;
		}
	}
}
//————————————————————————————————————————————————————————————————————












//————————————————————————————————————————————————————————————————————
//公交车停靠顺便服务站点时，停一次车只能完成下车请求和同方向的上车请求。
//完成顺便服务的请求节点，完成后删除请求节点，对应题目要求（7）。



/*
* 题目要求（7）：对于最短寻找时间优先策略，为了避免长时间不响应较远请求，加入顺便服务，
因此需要区分调度的目标站（当前仅1个）和顺便站（公交车驶往目标站的最短路程中，途经站点的下车请求、途经站点的同方向上车请求，可能多个）。
先收到的请求只要调度后确定为目标，在完成该目标请求之前不允许更改，即使途中收到更快可完成的请求也不可以更改目标，只能算作顺便服务，
允许途经时停靠顺便服务。注意不是所有途径站点的请求都可以算作顺便服务请求，与当前行驶方向相反的途经站上车请求不能顺便服务。
即公交车停靠顺便服务站点时，停一次车只能完成下车请求和同方向的上车请求。
而公交车到达目标站点停靠时，可以停一次车完成该站点的已接收所有请求，不必考虑上车请求的方向（区别于顺便站停靠）。
*/


void Delete2(Linklist* L, char a[], int x) {
	struct Request* temp = *L;
	struct Request* temp2 = temp->link;
	char c[62];
	char d[50];
	int k = panm(L);  //车到站后，请求链表中是否有该站点的上车请求，有则返回1，否则返回0

	while (temp2 != NULL) {

		strcpy(d, temp2->type);


		//题目要求（7）：对于最短寻找时间优先策略，为了避免长时间不响应较远请求，加入顺便服务，
		// 因此需要区分调度的目标站（当前仅1个）和顺便站
		// （公交车驶往目标站的最短路程中，途经站点的下车请求、途经站点的同方向上车请求，可能多个）

		if (strcmp(temp2->type, "target") == 0) {			//到站下车，顺便服务
			if ((temp2->station - 1) * DISTANCE == bus.pos) {		
				temp->link = temp2->link;  //删除顺便服务的请求节点
				temp2 = temp2->link;
			}

			else {
				temp = temp->link;
				temp2 = temp2->link;
			}
		}


		if (strcmp(d, "target") != 0){						//上车
			if (bus.state == 1) {
				strcpy(c, "clockwise");
			}
			else {					
				strcpy(c, "counterclockwise");
			}


			 
			//公交车停靠顺便服务站点时，停一次车只能完成同方向的上车请求。
			//而公交车到达目标站点停靠时，可以停一次车完成该站点的已接收所有请求，不必考虑上车请求的方向（区别于顺便站停靠）。
			if ((strcmp(c, temp2->type) == 0 && (temp2->station - 1) * DISTANCE == bus.pos)
				|| ((temp2->station - 1) * DISTANCE == bus.pos) && k == 1) {
				
				temp->link = temp2->link;   //删除已完成请求节点
				temp2 = temp2->link;
			}
			else {
				temp = temp->link;
				temp2 = temp2->link;
			}
		}
	}
}
//—————————————————————————————————————————————————————————————————————









//—————————————————————————————————————————————————————————————————————
//删除位置为x站点的请求节点，删除成功返回1，否则返回0
//目的：完成请求，删除该请求节点
int Delete3(Linklist* L, int x) {
	struct Request* temp = *L;
	struct Request* temp2 = temp->link; //当前请求的下一个请求
	int kk = 0;

	while (temp2 != NULL) {
		if ((temp2->station - 1) * DISTANCE == x) {
			temp->link = temp2->link;
			temp2 = temp2->link;
			kk = 1;
		}
		else {
			temp = temp->link;
			temp2 = temp2->link;
		}
	}

	if (kk == 1) {
		return 1;
	}

	return 0;
}
//—————————————————————————————————————————————————————————————————————










//—————————————————————————————————————————————————————————————————————
//文件读取函数，从题目规定的预设文件中读取默认参数

void FileUpdate(FILE* fp) {
	char buf[40];
	char a[20];
	char b[5];


	//char *fgets(char *str, int n, FILE *stream);
	//fgets() 是一个C语言标准库中的函数，用于从给定的输入流中读取一行数据。它会读取直到换行符'\n'、文件结束符EOF，
	// 或者是读取了n-1个字符为止（n是你指定要读取的最大字符数），以防止缓冲区溢出。读取的行包括换行符，并以空字符'\0'结尾。


	while (fgets(buf, 100, fp) != NULL) {  //从fp指向的文件中读取最多一百个字符储存到buf中
		if (buf[0] == '#') {
			continue;
		}

		sscanf(buf, "%s = %s", a, b);   //"%s = %s" 是格式字符串，它告诉 sscanf 函数如何解析 buf 中的数据。
		//在这里，它表示从 buf 中提取两个字符串，中间用等号分隔。
		//如果 buf 中的内容是 "DISTANCE = 2"， 这行代码会将 "DISTANCE" 存储在 a 中，将 "2" 存储在 b 中
		int b1;
		b1 = atoi(b);   //将字符串形式的“2”转换为2

		if (strcmp(a, "DISTANCE") == 0) {
			DISTANCE = b1;
		}

		if (strcmp(a, "TOTAL_STATION") == 0) {
			TOTAL_STATION = b1;
		}

		if (strcmp(a, "STRATEGY") == 0)
			strcpy(STRATEGY, b);
	}
}
//—————————————————————————————————————————————————————————————————————








//—————————————————————————————————————————————————————————————————————
//检测当前站台有无请求
int Scan(struct Bus bus, Linklist L) { 
	Linklist a = L;   //显然L为虚拟头节点
	a = a->link;
	int sta = (bus.pos / DISTANCE) + 1;
	while (a != NULL) {
		if (sta == a->station)
			return 1;
		a = a->link;
	}
	return 0;
}
//—————————————————————————————————————————————————————————————————————











//—————————————————————————————————————————————————————————————————————
//根据车的行驶状态保证车辆环形行驶
void move(struct Bus* bus) {
	//	printf("move %d\n", bus->state);

	if (bus->state == 0) {		//车停止
		return;
	}
	//环形行驶
	if (bus->state == 1) {		//顺时针行驶
		if (bus->pos + 1 <= TOTAL_STATION * DISTANCE - 1)
			bus->pos += 1;
		else
			bus->pos = 0;
	}
	//环形行驶
	if (bus->state == -1) {		//逆时针行驶
		if (bus->pos - 1 >= 0)
			bus->pos -= 1;
		else
			bus->pos = TOTAL_STATION * DISTANCE - 1;
	}

}
//—————————————————————————————————————————————————————————————————————









//—————————————————————————————————————————————————————————————————————
//检测公交是否在站台
int  Daozhan(struct Bus bus) { 
	if (bus.pos % DISTANCE == 0) {
		return 1;
	}
	else
		return 0;
}
//—————————————————————————————————————————————————————————————————————














//—————————————————————————————————————————————————————————————————————
//改变方向（该函数必须在车行驶的时候使用）
int Changedir_SSTF(Linklist* L) {  //下车或者同向上车的时候返回0，否则返回-1
	struct Request* temp = *L;
	struct Request* temp2 = temp->link;
	char c[62];
	char d[52];

	while (temp2 != NULL) {
		strcpy(d, temp2->type);

		//	printf("%d    %d\n",temp2->station,bus.pos);
		if (strcmp(temp2->type, "target") == 0) {

			if ((temp2->station - 1) * DISTANCE == bus.pos && temp2->t < 0) {
				return 0;
			}
			else {

				temp = temp->link;
				temp2 = temp2->link;
			}
		}

		//	printf("daisdjoaidsjiosajdi");
		if (strcmp(d, "target") != 0) {
			if (bus.state == 1) {
				strcpy(c, "clockwise");
			}
			else {
				strcpy(c, "counterclockwise");
			}

			if (strcmp(c, temp2->type) == 0 && (temp2->station - 1) * DISTANCE == bus.pos && temp2->t < 0) {

				return 0;
			}
			else {
				temp = temp->link;
				temp2 = temp2->link;
			}
		}

	}

	return -1;
}
//—————————————————————————————————————————————————————————————————————












//—————————————————————————————————————————————————————————————————————
//选择方向，必须Bus.state == 0时用
void choosedir_SSTF(Linklist* L) {
	struct Request* temp = *L;
	temp = temp->link;

	if (temp == NULL) {
		bus.state = 0;
		return;//无需求
	}

	int zheng = 0, fan = 0;
	int min = 100;
	int juu;
	int juli;
	int a[100];

	while (temp != NULL) {

		juu = (temp->station - 1) * DISTANCE - bus.pos;//正的加到正向  负的加到反向

		if (juu > 0) {
			juli = juu;

		}
		else {
			juli = TOTAL_STATION * DISTANCE - abs(juu);
		}

		//正向走的距离   juli即不经过位置0的头铁走法，暂时不考虑最短距离
		int juli2 = TOTAL_STATION * DISTANCE - juli; //反向走的距离

		for (int mip = 1; mip <= TOTAL_STATION; mip++) {

			if (a[mip] == juli) {
				juli = 0;
				juli2 = 0;
			}
		}

		for (int mip = 1; mip <= TOTAL_STATION; mip++) {

			if (a[mip] == 0) {
				a[mip] = juli;
			}
		}

		zheng += juli;
		fan += juli2;

		z = (temp->station - 1) * DISTANCE - bus.pos; //需求车站坐标-公交车位置坐标

		if (z == 0) {
			bus.state = 0; //有需求在该站，继续停。
			return;
		}


		temp = temp->link;
	}

	if (fan == zheng) {
		bus.state = 1;//当正反一样默认正向
	}

	if (zheng < fan) {
		bus.state = 1;
	}

	if (zheng > fan) {
		bus.state = -1;
	}

	if (zheng == 0 && fan == 0) {
		bus.state = 0;
	}
}
//—————————————————————————————————————————————————————————————————————












//—————————————————————————————————————————————————————————————————————
//输出公交当前状态
void Printf_SSTF(struct Bus bus, Linklist L) 
{ 
	Linklist now = L;
	now = now->link;
	printf("BUS:\n");
	printf("position:%d\n", bus.pos);
	printf("target:");

	for (int i = 1; i <= TOTAL_STATION; i++) {

		int p = 0;
		now = L;
		now = now->link;

		while (now != NULL) {
			if (now->station == i && strcmp(now->type, "target") == 0 && now->t <= 0)
				p = 1;
			now = now->link;
		}

		if (p == 0)
			printf("0");
		else
			printf("1");
	}

	now = L;
	now = now->link;
	printf("\n");
	printf("STATION:\n");
	printf("clockwise:");

	for (int i = 1; i <= TOTAL_STATION; i++) {

		int p = 0;
		now = L;
		now = now->link;

		while (now != NULL) {
			if (now->station == i && strcmp(now->type, "clockwise") == 0 && now->t <= 0)
				p = 1;
			now = now->link;
		}

		if (p == 0)
			printf("0");
		else
			printf("1");
	}

	now = L;
	now = now->link;
	printf("\n");
	printf("counterclockwise:");

	for (int i = 1; i <= TOTAL_STATION; i++) {

		int p = 0;
		now = L;
		now = now->link;

		while (now != NULL) {
			if (now->station == i && strcmp(now->type, "counterclockwise") == 0 && now->t <= 0)
				p = 1;
			now = now->link;
		}

		if (p == 0)
			printf("0");
		else
			printf("1");
	}

	printf("\n");
}
//—————————————————————————————————————————————————————————————————————














//—————————————————————————————————————————————————————————————————————
//在请求链表中寻找是否存在位置为x的站点
int findx(Linklist* L, int x) {
	struct Request* temp = *L;
	struct Request* temp2 = temp->link;
	int kk = 0;

	while (temp2 != NULL) {
		if ((temp2->station - 1) * DISTANCE == x) {  //下一个请求就在当前站点

			return 1;
		}
		else {
			temp = temp->link;
			temp2 = temp2->link;
		}
	}

	return 0;

}
//—————————————————————————————————————————————————————————————————————









//—————————————————————————————————————————————————————————————————————
//返回-1表示换方向， 1表示不换方向，0表示停下。（该函数必须在车行驶的时候使用）
int Changedir(Linklist* L, struct Bus bus) { 
	int t = 0;
	//	printf("bus.pos  %d\n", bus.pos);
	int half = TOTAL_STATION * DISTANCE / 2;//轨道一半距离
	struct Request* temp = *L;
	temp = temp->link;
	int ab = TOTAL_STATION * DISTANCE;//轨道全距离

	if (temp == NULL) {
		return 0;
	}//无需求了

	while (temp != NULL) {
		int dis1 = (temp->station - 1) * DISTANCE - bus.pos;
		int dis2 = ab + (temp->station - 1) * DISTANCE - bus.pos;
		int dis3 = ab - (temp->station - 1) * DISTANCE + bus.pos;

		if (bus.state == 1 && (temp->station - 1) * DISTANCE - bus.pos >= 0 && dis1 <= half) {
			//公交顺时针行驶，目标站点在当前位置顺时针方向且距离小于一半，不需要更改方向
			t = 1;
			break;
		}

		if (bus.state == 1 && (temp->station - 1) * DISTANCE - bus.pos < 0 && dis2 <= half) {
			//公交顺时针行驶，目标站点在当前位置逆时针方向且距离大于一半，不需要更改方向（会经过位置0）
			t = 1;
			break;
		}

		if (bus.state == -1 && (temp->station - 1) * DISTANCE - bus.pos >= 0 && dis3 <= half) {
			//公交逆时针行驶，目标站点在当前位置逆时针方向且距离小于一半，不需要更改方向（会经过位置0）
			t = 1;
			break;
		}

		if (bus.state == -1 && (temp->station - 1) * DISTANCE - bus.pos < 0 && -1 * dis1 <= half) {
			//公交逆时针行驶，目标站点在当前位置逆时针方向且距离小于一半，不需要更改方向（不会经过位置0）
			t = 1;
			break;
		}

		temp = temp->link;
	}

	if (t == 1) {
		return 1;
	}

	if (t == 0) {
		return -1;
	}

}
//—————————————————————————————————————————————————————————————————————










//—————————————————————————————————————————————————————————————————————
//按最新请求变向
void ChooseFirstDir(Linklist* L) { //按最新请求变向
	//在函数内部，通过 *L 可以获取到指向 Linklist 类型的指针，然后对其进行操作。如果直接传递 Linklist 
	//类型的指针，那么函数内部对指针的修改不会影响到函数外部
	//，因为在函数内部修改的是指针的拷贝。而通过传递指向指针的指针，函数内部可以直接修改指针指向的内容，从而在函数外部能够看到这些修改。
	struct Request* temp = *L; //*L获取一级指针指向的内容，L获取二级指针指向的内容
	temp = temp->link; //原请求的下一个请求，即新请求

	if (temp == NULL) {
		bus.state = 0;
		return;
	}

	int juli = abs((temp->station - 1) * DISTANCE - bus.pos);

	if (juli >= TOTAL_STATION * DISTANCE / 2) {
		juli = TOTAL_STATION * DISTANCE - juli;
	}

	int z = (temp->station - 1) * DISTANCE - bus.pos;  //无用，可删

	if ((temp->station - 1) * DISTANCE > bus.pos) {
		if ((temp->station - 1) * DISTANCE - bus.pos <= TOTAL_STATION * DISTANCE / 2) {
			bus.state = 1;  //1代表顺时针，-1代表逆时针
		}
		else {
			bus.state = -1;
		}
	}
	//如果请求车站在公交车前方，且距离不超过总距离的一半，则 bus.state 设为 1。
	//如果请求车站在公交车后方，且距离不超过总距离的一半，则 bus.state 设为 -1。
	if ((temp->station - 1) * DISTANCE < bus.pos) {
		if (bus.pos - (temp->station - 1) * DISTANCE >= TOTAL_STATION * DISTANCE / 2) {
			bus.state = 1;
		}
		else {
			bus.state = -1;
		}
	}

	return;
}
//—————————————————————————————————————————————————————————————————————







//—————————————————————————————————————————————————————————————————————
//判断行驶方向，必须Bus.state == 0时用
void choosedir(Linklist* L) { //必须	Bus.state == 0时用
	struct Request* temp = *L;
	temp = temp->link;

	if (temp == NULL) {
		bus.state = 0;
		return;//无需求
	}

	int min = 100;

	while (temp != NULL) {
		int juli = abs((temp->station - 1) * DISTANCE - bus.pos);

		if (juli >= TOTAL_STATION * DISTANCE / 2) {
			juli = TOTAL_STATION * DISTANCE - juli;
		}

		int z = (temp->station - 1) * DISTANCE - bus.pos; //需求车站坐标-公交车位置坐标

		if (juli <= min) {
			min = juli;

			if ((temp->station - 1) * DISTANCE > bus.pos) {
				if ((temp->station - 1) * DISTANCE - bus.pos <= TOTAL_STATION * DISTANCE / 2) {
					bus.state = 1;
				}
				else {
					bus.state = -1;
				}
			}

			if ((temp->station - 1) * DISTANCE < bus.pos) {
				if (bus.pos - (temp->station - 1) * DISTANCE >= TOTAL_STATION * DISTANCE / 2) {
					bus.state = 1;
				}
				else {
					bus.state = -1;
				}
			}

			if (z == 0) {
				bus.state = 0; //有需求在该站，继续停。
			}
		}

		temp = temp->link;
	}
}
//—————————————————————————————————————————————————————————————————————













//—————————————————————————————————————————————————————————————————————
// 输出公交当前状态
void Printf(struct Bus bus, Linklist L) { 
	Linklist now = L;
	now = now->link;
	printf("BUS:\n");
	printf("position:%d\n", bus.pos);
	printf("target:");

	for (int i = 1; i <= TOTAL_STATION; i++) {

		int p = 0;
		now = L;
		now = now->link;

		while (now != NULL) {
			if (now->station == i && strcmp(now->type, "target") == 0)  //车内有该站点的请求
				p = 1;
			now = now->link;
		}

		if (p == 0)
			printf("0");
		else
			printf("1");
	}

	now = L;
	now = now->link;
	printf("\n");
	printf("STATION:\n");
	printf("clockwise:");

	for (int i = 1; i <= TOTAL_STATION; i++) {

		int p = 0;
		now = L;
		now = now->link;

		while (now != NULL) {
			if (now->station == i && strcmp(now->type, "clockwise") == 0)
				p = 1;
			now = now->link;
		}

		if (p == 0)
			printf("0");
		else
			printf("1");
	}

	now = L;
	now = now->link;
	printf("\n");
	printf("counterclockwise:");

	for (int i = 1; i <= TOTAL_STATION; i++) {

		int p = 0;
		now = L;
		now = now->link;

		while (now != NULL) {
			if (now->station == i && strcmp(now->type, "counterclockwise") == 0)
				p = 1;
			now = now->link;
		}

		if (p == 0)
			printf("0");
		else
			printf("1");
	}

	printf("\n");
}
//—————————————————————————————————————————————————————————————————————








//—————————————————————————————————————————————————————————————————————
//去空格
void qukongge(char* p) {
	int i;
	i = (int)strlen(p) - 1;

	while (p[i] == ' ' && i > 0)
		i--;
	p[i + 1] = '\0';

	return;

}
//—————————————————————————————————————————————————————————————————————