#include "data_structure.h"







//����������������������������������������������������������������������������������������������������������������������������������������
void freelist(Linklist a) { //�ͷ�����
	Linklist b = a, c;

	while (b != NULL) {
		c = b->link;
		free(b);
		b = c;
	}
	a = NULL;
}
//����������������������������������������������������������������������������������������������������������������������������������������








//����������������������������������������������������������������������������������������������������������������������������������������
//struct Request* ���͵Ľڵ㹹���������������������е�ÿ���ڵ��Ϊ������ڵ㡱
//Ѱ���������Ƿ�����λ�� x ������������ͬ�ġ�����ڵ㡱    
//Ŀ�ģ��������
int findx1(Linklist* L, int x, char a[]) {   //x��λ�ã� a[]������֮һ
	struct Request* temp = *L;				 
	struct Request* temp2 = temp->link;
	//��������������������������������������������������������������������������������
	int kk = 0;   //kk�������ã���ʾɾ���ڵ�ɹ�Ϊ1������Ϊ0����ϸ�������  int Delete3(Linklist* L, int x)��
	//��������������������������������������������������������������������������������
	while (temp2 != NULL) {
		if ((temp2->station - 1) * DISTANCE == x && strcmp(temp2->type, a) == 0) { 
			//���������ͷ��ʼ������x����λ�ñ�����վ����У�Ѱ����ýڵ�������ͬ��xվ�㣩
			//�ҵ��ˣ�����1
			return 1;
		}
		else {
			temp = temp->link;
			temp2 = temp2->link;
		}
	}
	//û�ҵ�������0
	return 0;
}
//����������������������������������������������������������������������������������������������������������������������������������������









//����������������������������������������������������������������������������������������������������������������������������������������
//����������뵽���������ĩβ
void Insert(Linklist* L, char a[], int x) {   
	//a[]��ʾĿ��˳ʱ����ʱ������֮һ��x��ʾվ��


	struct Request* temp1 = (struct Request*)malloc(sizeof(struct Request));
	temp1->link = NULL;
	temp1->station = x;  //������ʱ����������temp1


	//��ĿҪ��5���������ĳ������û�����ʱ������ͬ�������������ͺ�վ��ȫ����ͬ������ͬ�����������������������Ӱ�����ָ��ļ��㣬
	// �Ȳ�����ȴ����������ֲ���������������������������ɵ������ٴη���ʱӦ����������



	//�ж������������Ƿ�������������ͬ�Ľڵ㣬������Դ˴�������
	if (findx1(L, (x - 1) * DISTANCE, a)) return;



	//û����嵽�����ĩβ
	strcpy(temp1->type, a);
	temp1->t = 1; //��ʼ��ʱ��
	struct Request* temp2 = *L;

	while (temp2->link != NULL) {
		temp2 = temp2->link;
	}
	temp2->link = temp1;   //��temp1������������ӵ�����ĩ��
}
//����������������������������������������������������������������������������������������������������������������������������������������










//����������������������������������������������������������������������������������������������������������������������������������������
//���һ�������ÿ������ڵ���ǰ��һλ
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
//����������������������������������������������������������������������������������������������������������������������������������������









//����������������������������������������������������������������������������������������������������������������������������������������
//��������Ĭ��ÿ������ڵ�Ϊ�ϳ������һ��
void gengxin(Linklist* L) {
	struct Request* temp = (struct Request*)malloc(sizeof(struct Request));
	temp->link = NULL;
	struct Request* temp2 = *L;

	while (temp2->link != NULL) {

		temp2 = temp2->link;
		temp2->m = 1;   //temp2->mֵΪ1����ʾ������ΪĿ������Ҳ�����ϳ�����
	}
}
//����������������������������������������������������������������������������������������������������������������������������������������









//����������������������������������������������������������������������������������������������������������������������������������������
//�жϳ���վ�󣨶�Ӧ��Ŀ�е�Ŀ��վ���������������Ƿ��и�վ����ϳ��������򷵻�1�����򷵻�0
//Ŀ�ģ����ϳ��ĳ˿�
int panm(Linklist* L) {
	struct Request* temp = (struct Request*)malloc(sizeof(struct Request));
	temp->link = NULL;
	struct Request* temp2 = *L;

	while (temp2->link != NULL) {

		temp2 = temp2->link;

		if ((temp2->station - 1) * DISTANCE == bus.pos && temp2->m == 1) {//temp2->mֵΪ1����ʾ�ϳ�

			return 1;
		}
	}
	return 0;
}
//����������������������������������������������������������������������������������������������������������������������������������������










//����������������������������������������������������������������������������������������������������������������������������������������
//ɾ������ͷ�ڵ����һ���ڵ㣨ɾ�����ڵ�һλ������ڵ㣩
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
//����������������������������������������������������������������������������������������������������������������������������������������












//����������������������������������������������������������������������������������������������������������������������������������������
//������ͣ��˳�����վ��ʱ��ͣһ�γ�ֻ������³������ͬ������ϳ�����
//���˳����������ڵ㣬��ɺ�ɾ������ڵ㣬��Ӧ��ĿҪ��7����



/*
* ��ĿҪ��7�����������Ѱ��ʱ�����Ȳ��ԣ�Ϊ�˱��ⳤʱ�䲻��Ӧ��Զ���󣬼���˳�����
�����Ҫ���ֵ��ȵ�Ŀ��վ����ǰ��1������˳��վ��������ʻ��Ŀ��վ�����·���У�;��վ����³�����;��վ���ͬ�����ϳ����󣬿��ܶ������
���յ�������ֻҪ���Ⱥ�ȷ��ΪĿ�꣬����ɸ�Ŀ������֮ǰ��������ģ���ʹ;���յ��������ɵ�����Ҳ�����Ը���Ŀ�ֻ꣬������˳�����
����;��ʱͣ��˳�����ע�ⲻ������;��վ������󶼿�������˳����������뵱ǰ��ʻ�����෴��;��վ�ϳ�������˳�����
��������ͣ��˳�����վ��ʱ��ͣһ�γ�ֻ������³������ͬ������ϳ�����
������������Ŀ��վ��ͣ��ʱ������ͣһ�γ���ɸ�վ����ѽ����������󣬲��ؿ����ϳ�����ķ���������˳��վͣ������
*/


void Delete2(Linklist* L, char a[], int x) {
	struct Request* temp = *L;
	struct Request* temp2 = temp->link;
	char c[62];
	char d[50];
	int k = panm(L);  //����վ�������������Ƿ��и�վ����ϳ��������򷵻�1�����򷵻�0

	while (temp2 != NULL) {

		strcpy(d, temp2->type);


		//��ĿҪ��7�����������Ѱ��ʱ�����Ȳ��ԣ�Ϊ�˱��ⳤʱ�䲻��Ӧ��Զ���󣬼���˳�����
		// �����Ҫ���ֵ��ȵ�Ŀ��վ����ǰ��1������˳��վ
		// ��������ʻ��Ŀ��վ�����·���У�;��վ����³�����;��վ���ͬ�����ϳ����󣬿��ܶ����

		if (strcmp(temp2->type, "target") == 0) {			//��վ�³���˳�����
			if ((temp2->station - 1) * DISTANCE == bus.pos) {		
				temp->link = temp2->link;  //ɾ��˳����������ڵ�
				temp2 = temp2->link;
			}

			else {
				temp = temp->link;
				temp2 = temp2->link;
			}
		}


		if (strcmp(d, "target") != 0){						//�ϳ�
			if (bus.state == 1) {
				strcpy(c, "clockwise");
			}
			else {					
				strcpy(c, "counterclockwise");
			}


			 
			//������ͣ��˳�����վ��ʱ��ͣһ�γ�ֻ�����ͬ������ϳ�����
			//������������Ŀ��վ��ͣ��ʱ������ͣһ�γ���ɸ�վ����ѽ����������󣬲��ؿ����ϳ�����ķ���������˳��վͣ������
			if ((strcmp(c, temp2->type) == 0 && (temp2->station - 1) * DISTANCE == bus.pos)
				|| ((temp2->station - 1) * DISTANCE == bus.pos) && k == 1) {
				
				temp->link = temp2->link;   //ɾ�����������ڵ�
				temp2 = temp2->link;
			}
			else {
				temp = temp->link;
				temp2 = temp2->link;
			}
		}
	}
}
//������������������������������������������������������������������������������������������������������������������������������������������









//������������������������������������������������������������������������������������������������������������������������������������������
//ɾ��λ��Ϊxվ�������ڵ㣬ɾ���ɹ�����1�����򷵻�0
//Ŀ�ģ��������ɾ��������ڵ�
int Delete3(Linklist* L, int x) {
	struct Request* temp = *L;
	struct Request* temp2 = temp->link; //��ǰ�������һ������
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
//������������������������������������������������������������������������������������������������������������������������������������������










//������������������������������������������������������������������������������������������������������������������������������������������
//�ļ���ȡ����������Ŀ�涨��Ԥ���ļ��ж�ȡĬ�ϲ���

void FileUpdate(FILE* fp) {
	char buf[40];
	char a[20];
	char b[5];


	//char *fgets(char *str, int n, FILE *stream);
	//fgets() ��һ��C���Ա�׼���еĺ��������ڴӸ������������ж�ȡһ�����ݡ������ȡֱ�����з�'\n'���ļ�������EOF��
	// �����Ƕ�ȡ��n-1���ַ�Ϊֹ��n����ָ��Ҫ��ȡ������ַ��������Է�ֹ�������������ȡ���а������з������Կ��ַ�'\0'��β��


	while (fgets(buf, 100, fp) != NULL) {  //��fpָ����ļ��ж�ȡ���һ�ٸ��ַ����浽buf��
		if (buf[0] == '#') {
			continue;
		}

		sscanf(buf, "%s = %s", a, b);   //"%s = %s" �Ǹ�ʽ�ַ����������� sscanf ������ν��� buf �е����ݡ�
		//���������ʾ�� buf ����ȡ�����ַ������м��õȺŷָ���
		//��� buf �е������� "DISTANCE = 2"�� ���д���Ὣ "DISTANCE" �洢�� a �У��� "2" �洢�� b ��
		int b1;
		b1 = atoi(b);   //���ַ�����ʽ�ġ�2��ת��Ϊ2

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
//������������������������������������������������������������������������������������������������������������������������������������������








//������������������������������������������������������������������������������������������������������������������������������������������
//��⵱ǰվ̨��������
int Scan(struct Bus bus, Linklist L) { 
	Linklist a = L;   //��ȻLΪ����ͷ�ڵ�
	a = a->link;
	int sta = (bus.pos / DISTANCE) + 1;
	while (a != NULL) {
		if (sta == a->station)
			return 1;
		a = a->link;
	}
	return 0;
}
//������������������������������������������������������������������������������������������������������������������������������������������











//������������������������������������������������������������������������������������������������������������������������������������������
//���ݳ�����ʻ״̬��֤����������ʻ
void move(struct Bus* bus) {
	//	printf("move %d\n", bus->state);

	if (bus->state == 0) {		//��ֹͣ
		return;
	}
	//������ʻ
	if (bus->state == 1) {		//˳ʱ����ʻ
		if (bus->pos + 1 <= TOTAL_STATION * DISTANCE - 1)
			bus->pos += 1;
		else
			bus->pos = 0;
	}
	//������ʻ
	if (bus->state == -1) {		//��ʱ����ʻ
		if (bus->pos - 1 >= 0)
			bus->pos -= 1;
		else
			bus->pos = TOTAL_STATION * DISTANCE - 1;
	}

}
//������������������������������������������������������������������������������������������������������������������������������������������









//������������������������������������������������������������������������������������������������������������������������������������������
//��⹫���Ƿ���վ̨
int  Daozhan(struct Bus bus) { 
	if (bus.pos % DISTANCE == 0) {
		return 1;
	}
	else
		return 0;
}
//������������������������������������������������������������������������������������������������������������������������������������������














//������������������������������������������������������������������������������������������������������������������������������������������
//�ı䷽�򣨸ú��������ڳ���ʻ��ʱ��ʹ�ã�
int Changedir_SSTF(Linklist* L) {  //�³�����ͬ���ϳ���ʱ�򷵻�0�����򷵻�-1
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
//������������������������������������������������������������������������������������������������������������������������������������������












//������������������������������������������������������������������������������������������������������������������������������������������
//ѡ���򣬱���Bus.state == 0ʱ��
void choosedir_SSTF(Linklist* L) {
	struct Request* temp = *L;
	temp = temp->link;

	if (temp == NULL) {
		bus.state = 0;
		return;//������
	}

	int zheng = 0, fan = 0;
	int min = 100;
	int juu;
	int juli;
	int a[100];

	while (temp != NULL) {

		juu = (temp->station - 1) * DISTANCE - bus.pos;//���ļӵ�����  ���ļӵ�����

		if (juu > 0) {
			juli = juu;

		}
		else {
			juli = TOTAL_STATION * DISTANCE - abs(juu);
		}

		//�����ߵľ���   juli��������λ��0��ͷ���߷�����ʱ��������̾���
		int juli2 = TOTAL_STATION * DISTANCE - juli; //�����ߵľ���

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

		z = (temp->station - 1) * DISTANCE - bus.pos; //����վ����-������λ������

		if (z == 0) {
			bus.state = 0; //�������ڸ�վ������ͣ��
			return;
		}


		temp = temp->link;
	}

	if (fan == zheng) {
		bus.state = 1;//������һ��Ĭ������
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
//������������������������������������������������������������������������������������������������������������������������������������������












//������������������������������������������������������������������������������������������������������������������������������������������
//���������ǰ״̬
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
//������������������������������������������������������������������������������������������������������������������������������������������














//������������������������������������������������������������������������������������������������������������������������������������������
//������������Ѱ���Ƿ����λ��Ϊx��վ��
int findx(Linklist* L, int x) {
	struct Request* temp = *L;
	struct Request* temp2 = temp->link;
	int kk = 0;

	while (temp2 != NULL) {
		if ((temp2->station - 1) * DISTANCE == x) {  //��һ��������ڵ�ǰվ��

			return 1;
		}
		else {
			temp = temp->link;
			temp2 = temp2->link;
		}
	}

	return 0;

}
//������������������������������������������������������������������������������������������������������������������������������������������









//������������������������������������������������������������������������������������������������������������������������������������������
//����-1��ʾ������ 1��ʾ��������0��ʾͣ�¡����ú��������ڳ���ʻ��ʱ��ʹ�ã�
int Changedir(Linklist* L, struct Bus bus) { 
	int t = 0;
	//	printf("bus.pos  %d\n", bus.pos);
	int half = TOTAL_STATION * DISTANCE / 2;//���һ�����
	struct Request* temp = *L;
	temp = temp->link;
	int ab = TOTAL_STATION * DISTANCE;//���ȫ����

	if (temp == NULL) {
		return 0;
	}//��������

	while (temp != NULL) {
		int dis1 = (temp->station - 1) * DISTANCE - bus.pos;
		int dis2 = ab + (temp->station - 1) * DISTANCE - bus.pos;
		int dis3 = ab - (temp->station - 1) * DISTANCE + bus.pos;

		if (bus.state == 1 && (temp->station - 1) * DISTANCE - bus.pos >= 0 && dis1 <= half) {
			//����˳ʱ����ʻ��Ŀ��վ���ڵ�ǰλ��˳ʱ�뷽���Ҿ���С��һ�룬����Ҫ���ķ���
			t = 1;
			break;
		}

		if (bus.state == 1 && (temp->station - 1) * DISTANCE - bus.pos < 0 && dis2 <= half) {
			//����˳ʱ����ʻ��Ŀ��վ���ڵ�ǰλ����ʱ�뷽���Ҿ������һ�룬����Ҫ���ķ��򣨻ᾭ��λ��0��
			t = 1;
			break;
		}

		if (bus.state == -1 && (temp->station - 1) * DISTANCE - bus.pos >= 0 && dis3 <= half) {
			//������ʱ����ʻ��Ŀ��վ���ڵ�ǰλ����ʱ�뷽���Ҿ���С��һ�룬����Ҫ���ķ��򣨻ᾭ��λ��0��
			t = 1;
			break;
		}

		if (bus.state == -1 && (temp->station - 1) * DISTANCE - bus.pos < 0 && -1 * dis1 <= half) {
			//������ʱ����ʻ��Ŀ��վ���ڵ�ǰλ����ʱ�뷽���Ҿ���С��һ�룬����Ҫ���ķ��򣨲��ᾭ��λ��0��
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
//������������������������������������������������������������������������������������������������������������������������������������������










//������������������������������������������������������������������������������������������������������������������������������������������
//�������������
void ChooseFirstDir(Linklist* L) { //�������������
	//�ں����ڲ���ͨ�� *L ���Ի�ȡ��ָ�� Linklist ���͵�ָ�룬Ȼ�������в��������ֱ�Ӵ��� Linklist 
	//���͵�ָ�룬��ô�����ڲ���ָ����޸Ĳ���Ӱ�쵽�����ⲿ
	//����Ϊ�ں����ڲ��޸ĵ���ָ��Ŀ�������ͨ������ָ��ָ���ָ�룬�����ڲ�����ֱ���޸�ָ��ָ������ݣ��Ӷ��ں����ⲿ�ܹ�������Щ�޸ġ�
	struct Request* temp = *L; //*L��ȡһ��ָ��ָ������ݣ�L��ȡ����ָ��ָ�������
	temp = temp->link; //ԭ�������һ�����󣬼�������

	if (temp == NULL) {
		bus.state = 0;
		return;
	}

	int juli = abs((temp->station - 1) * DISTANCE - bus.pos);

	if (juli >= TOTAL_STATION * DISTANCE / 2) {
		juli = TOTAL_STATION * DISTANCE - juli;
	}

	int z = (temp->station - 1) * DISTANCE - bus.pos;  //���ã���ɾ

	if ((temp->station - 1) * DISTANCE > bus.pos) {
		if ((temp->station - 1) * DISTANCE - bus.pos <= TOTAL_STATION * DISTANCE / 2) {
			bus.state = 1;  //1����˳ʱ�룬-1������ʱ��
		}
		else {
			bus.state = -1;
		}
	}
	//�������վ�ڹ�����ǰ�����Ҿ��벻�����ܾ����һ�룬�� bus.state ��Ϊ 1��
	//�������վ�ڹ������󷽣��Ҿ��벻�����ܾ����һ�룬�� bus.state ��Ϊ -1��
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
//������������������������������������������������������������������������������������������������������������������������������������������







//������������������������������������������������������������������������������������������������������������������������������������������
//�ж���ʻ���򣬱���Bus.state == 0ʱ��
void choosedir(Linklist* L) { //����	Bus.state == 0ʱ��
	struct Request* temp = *L;
	temp = temp->link;

	if (temp == NULL) {
		bus.state = 0;
		return;//������
	}

	int min = 100;

	while (temp != NULL) {
		int juli = abs((temp->station - 1) * DISTANCE - bus.pos);

		if (juli >= TOTAL_STATION * DISTANCE / 2) {
			juli = TOTAL_STATION * DISTANCE - juli;
		}

		int z = (temp->station - 1) * DISTANCE - bus.pos; //����վ����-������λ������

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
				bus.state = 0; //�������ڸ�վ������ͣ��
			}
		}

		temp = temp->link;
	}
}
//������������������������������������������������������������������������������������������������������������������������������������������













//������������������������������������������������������������������������������������������������������������������������������������������
// ���������ǰ״̬
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
			if (now->station == i && strcmp(now->type, "target") == 0)  //�����и�վ�������
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
//������������������������������������������������������������������������������������������������������������������������������������������








//������������������������������������������������������������������������������������������������������������������������������������������
//ȥ�ո�
void qukongge(char* p) {
	int i;
	i = (int)strlen(p) - 1;

	while (p[i] == ' ' && i > 0)
		i--;
	p[i + 1] = '\0';

	return;

}
//������������������������������������������������������������������������������������������������������������������������������������������