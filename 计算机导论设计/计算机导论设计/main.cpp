#include "function.h"
#include "data_structure.h"


int main() {
	FILE* fp = fopen("D:\\xx.txt", "w");  //通常在C语言中，当需要进行文件操作时，会使用
	// FILE 类型的指针变量来表示打开的文件。通过这个指针变量，可以对文件进行读取、写入等操作。在这种情况下，fp 可以被用来指向打开的文件，以便对文件进行操作。
	//fopen("D:\\\\xx.txt", "r")：这是一个文件操作函数，用于打开一个文件并返回一个指向该文件的 FILE 类型指针。
	//第一个参数是文件路径，第二个参数是打开文件的模式。在这里，"D:\xx.txt" 表示文件的路径，"r" 表示只读模式
//	FILE *fp = fopen("dict.dic", "w");
	FileUpdate(fp);
	Linklist L;
	L = (struct Request*)malloc(sizeof(struct Request));
	L->link = NULL;
	char line[100];
	int time = 0;
	bus.pos = 0;
	bus.state = 0;

	if (strcmp("FCFS", STRATEGY) == 0) {  //strcmp函数小于返回负数，大于返回正数，等于返回0
		printf("TIME:%d\n", time);
		Printf(bus, L);
		gets(line);   //用于读入一行文本，建议使用更安全的getline()进行替代，遇到回车停下，可以读入空格
		int k = 0;

		while (strcmp(line, "end") != 0) {
			if (strcmp(line, "clock") == 0) {
				k = 0;

				if (bus.state == 0)  //公交停止，进行新请求
					ChooseFirstDir(&L);

				if (L->link == NULL)
					bus.state = 0;

				if (Daozhan(bus) && L->link != NULL && L->link->station == bus.pos / DISTANCE + 1) {  //接下来的请求也都是在此站点
					//但是完成当前请求后，如果发现时间序列上后续的一个或多个连续请求都恰好在同一站点（即连续的同站点请求，位置相同，但请求类型不同），
					//则可以立即完成这些连续的同站点请求。也就是说特殊情况下，一次停车可完成多个请求。
					Delete1(&L);

					if (bus.state != 0)
						k = 1;
					ChooseFirstDir(&L);
				}

				if (k == 0)
					move(&bus);
				time++;
				printf("TIME:%d\n", time);
				Printf(bus, L);
			}
			else {
				char line2[30];
				int s;
				sscanf(line, "%s %d", line2, &s); //将line中的数据按照第二个参数的形式储存到line2和s中，注意形参传地址
				Insert(&L, line2, s);  //插入新请求
			}

			gets(line); //继续读取下一行新请求
		}
	}

	if (strcmp("SCAN", STRATEGY) == 0) {  //顺便服务
		printf("TIME:%d\n", time);
		Printf(bus, L);
		gets(line);
		//	qukongge(line);
		int zz = 0;

		while (strcmp(line, "end") != 0) {

			if (strcmp(line, "clock") == 0) {

				time++;

				if (zz == 1) {

					if (Delete3(&L, bus.pos)) {   //公交车在向目标请求站点行驶的过程中，
						//如果收到途经站点的请求（不论方向，但不能违反下一条的提前1秒规则），则不管这个请求的类型一律停靠站点，完成此请求。
						//上述为Delete3函数成立的条件，if成立之后停车完成服务，进行一次输出
						goto out;
					}
				}

				if (bus.state == 0) {
					choosedir(&L);
				}
				else if (bus.state != 0 && Changedir(&L, bus) == 0) {
					bus.state = 0;
				}

				else	if (bus.state != 0 && Changedir(&L, bus) == -1) {  //更改方向
					if (bus.state == 1) {
						bus.state = -1;
					}

					else	if (bus.state == -1) {
						bus.state = 1;
					}
				}

				//	printf("%d\n", bus.state);
				move(&bus);

			out:
				printf("TIME:%d\n", time);
				Printf(bus, L);
				zz = findx(&L, bus.pos);   //之后某个请求就在当前站点，返回1，否则返回0
				//难理解 感觉少了一步将zz再次变成0的代码


			}
			else {
				char line2[50];
				int s;
				sscanf(line, "%s %d", line2, &s);

				if (bus.state == 0 && (s - 1) * DISTANCE == bus.pos) {  //   公交停止并且新请求正好在该站点
					gets(line);
					qukongge(line);   //去空格有些没必要
					continue;  //直接跳出本次循环，因为该新请求已经完成
				}

				Insert(&L, line2, s); //插入新请求
			}

			gets(line);
			qukongge(line);
		}
	}

	if (strcmp("SSTF", STRATEGY) == 0) {
		gets(line);
		qukongge(line);
		char line2[60];
		int s;

		while (strcmp(line, "end") != 0) {
			z = 1;

			if (strcmp(line, "clock") == 0) {
				printf("TIME:%d\n", time);
				Printf_SSTF(bus, L);
				shijian(&L);   //让所有请求的时间都减一

				if (bus.state == 0) {
					choosedir_SSTF(&L);

					if (z == 0) {   //if成立表示下一个请求正好在该站点
						Delete2(&L, line, bus.pos);
					}

					gengxin(&L); //给请求上标记
				}
				else //判m点
					if ((bus.state != 0 && Changedir_SSTF(&L) == 0) || (panm(&L))) {
						// printf("MMMMMMMMMMMMMMMMMMMMMMM\n");
						Delete2(&L, line, bus.pos);
						bus.state = 0;
						//	printf("                                  \n    %d                 \n                  ",bus.state);
					}

				move(&bus);
				time++;

			}
			else {
				sscanf(line, "%s %d", line2, &s);

				if (bus.state == 0 && (s - 1) * DISTANCE == bus.pos) {
					gets(line);
					qukongge(line);
					continue;
				}

				Insert(&L, line2, s);
			}

			gets(line);
			qukongge(line);
		}

		printf("TIME:%d\n", time);
		Printf_SSTF(bus, L);
	}

	printf("end\n");
	freelist(L);
	return 0;
}