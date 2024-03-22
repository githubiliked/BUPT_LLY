#include "function.h"
#include "data_structure.h"


int main() {
	FILE* fp = fopen("D:\\xx.txt", "w");  //ͨ����C�����У�����Ҫ�����ļ�����ʱ����ʹ��
	// FILE ���͵�ָ���������ʾ�򿪵��ļ���ͨ�����ָ����������Զ��ļ����ж�ȡ��д��Ȳ���������������£�fp ���Ա�����ָ��򿪵��ļ����Ա���ļ����в�����
	//fopen("D:\\\\xx.txt", "r")������һ���ļ��������������ڴ�һ���ļ�������һ��ָ����ļ��� FILE ����ָ�롣
	//��һ���������ļ�·�����ڶ��������Ǵ��ļ���ģʽ�������"D:\xx.txt" ��ʾ�ļ���·����"r" ��ʾֻ��ģʽ
//	FILE *fp = fopen("dict.dic", "w");
	FileUpdate(fp);
	Linklist L;
	L = (struct Request*)malloc(sizeof(struct Request));
	L->link = NULL;
	char line[100];
	int time = 0;
	bus.pos = 0;
	bus.state = 0;

	if (strcmp("FCFS", STRATEGY) == 0) {  //strcmp����С�ڷ��ظ��������ڷ������������ڷ���0
		printf("TIME:%d\n", time);
		Printf(bus, L);
		gets(line);   //���ڶ���һ���ı�������ʹ�ø���ȫ��getline()��������������س�ͣ�£����Զ���ո�
		int k = 0;

		while (strcmp(line, "end") != 0) {
			if (strcmp(line, "clock") == 0) {
				k = 0;

				if (bus.state == 0)  //����ֹͣ������������
					ChooseFirstDir(&L);

				if (L->link == NULL)
					bus.state = 0;

				if (Daozhan(bus) && L->link != NULL && L->link->station == bus.pos / DISTANCE + 1) {  //������������Ҳ�����ڴ�վ��
					//������ɵ�ǰ������������ʱ�������Ϻ�����һ��������������ǡ����ͬһվ�㣨��������ͬվ������λ����ͬ�����������Ͳ�ͬ����
					//��������������Щ������ͬվ������Ҳ����˵��������£�һ��ͣ������ɶ������
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
				sscanf(line, "%s %d", line2, &s); //��line�е����ݰ��յڶ�����������ʽ���浽line2��s�У�ע���βδ���ַ
				Insert(&L, line2, s);  //����������
			}

			gets(line); //������ȡ��һ��������
		}
	}

	if (strcmp("SCAN", STRATEGY) == 0) {  //˳�����
		printf("TIME:%d\n", time);
		Printf(bus, L);
		gets(line);
		//	qukongge(line);
		int zz = 0;

		while (strcmp(line, "end") != 0) {

			if (strcmp(line, "clock") == 0) {

				time++;

				if (zz == 1) {

					if (Delete3(&L, bus.pos)) {   //����������Ŀ������վ����ʻ�Ĺ����У�
						//����յ�;��վ������󣨲��۷��򣬵�����Υ����һ������ǰ1����򣩣��򲻹�������������һ��ͣ��վ�㣬��ɴ�����
						//����ΪDelete3����������������if����֮��ͣ����ɷ��񣬽���һ�����
						goto out;
					}
				}

				if (bus.state == 0) {
					choosedir(&L);
				}
				else if (bus.state != 0 && Changedir(&L, bus) == 0) {
					bus.state = 0;
				}

				else	if (bus.state != 0 && Changedir(&L, bus) == -1) {  //���ķ���
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
				zz = findx(&L, bus.pos);   //֮��ĳ��������ڵ�ǰվ�㣬����1�����򷵻�0
				//����� �о�����һ����zz�ٴα��0�Ĵ���


			}
			else {
				char line2[50];
				int s;
				sscanf(line, "%s %d", line2, &s);

				if (bus.state == 0 && (s - 1) * DISTANCE == bus.pos) {  //   ����ֹͣ���������������ڸ�վ��
					gets(line);
					qukongge(line);   //ȥ�ո���Щû��Ҫ
					continue;  //ֱ����������ѭ������Ϊ���������Ѿ����
				}

				Insert(&L, line2, s); //����������
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
				shijian(&L);   //�����������ʱ�䶼��һ

				if (bus.state == 0) {
					choosedir_SSTF(&L);

					if (z == 0) {   //if������ʾ��һ�����������ڸ�վ��
						Delete2(&L, line, bus.pos);
					}

					gengxin(&L); //�������ϱ��
				}
				else //��m��
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