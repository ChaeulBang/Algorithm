#include<stdio.h>
#include<stdlib.h>

typedef struct ListNode {	//����Ʈ�� �� ���
	char elem;
	struct ListNode* prev;
	struct ListNode* next;
} ListNode;

typedef struct ListType {
	int size;	//����Ʈ�� ũ��
	ListNode* header;
	ListNode* trailer;
} ListType;

void add(ListType* list, int r, char e) {
	if (list->size + 1 < r) {			//���� ����Ʈ�� ũ�� + 1 ���� ������ Ŭ ��
		printf("invalid position\n");	//���� ���� ��ȿ���� ����
	}
	else {
		ListNode* newNode = malloc(sizeof(ListNode));	//���ο� ��� ����
		newNode->elem = e;

		if (list->size == 0) {			//����ִ� ����Ʈ�� ���
			newNode->next = list->trailer;
			newNode->prev = list->header;
			list->header->next = newNode;
			list->trailer->prev = newNode;
		}
		else if (list->size + 1 == r) {	//����Ʈ�� ���� ��带 �߰��� �� trailer�� �̿��� ����
			newNode->next = list->trailer;
			newNode->prev = list->trailer->prev;
			list->trailer->prev->next = newNode;
			list->trailer->prev = newNode;
		}
		else {							//�� ���� ��쿡 header�� �̿��� ����
			int i;
			ListNode* visit = list->header;					//Ư�� ��� ã�� ����

			for (i = 0; i < r; i++) visit = visit->next;	//���� ��ġ ã��
			newNode->next = visit;
			newNode->prev = visit->prev;
			visit->prev->next = newNode;	
			visit->prev = newNode;
		}

		list->size++; //����Ʈ�� ��带 �߰������Ƿ� ũ�� + 1
	}
}

void delete(ListType* list, int r) {
	if (list->size < r) {				//���� ����Ʈ ũ�⺸�� ������ Ŭ ��
		printf("invalid position\n");	//���� ���� ��ȿ���� ����
	}
	else {
		int i;
		ListNode* visit = list->header;					//Ư�� ��� ã�� ����

		for (i = 0; i < r; i++) visit = visit->next;	//���� ��ġ ã��
		visit->prev->next = visit->next;
		visit->next->prev = visit->prev;
		free(visit);

		list->size--; //����Ʈ���� ��带 ���������Ƿ� ũ�� - 1
	}
}

void get(ListType* list, int r) {
	if (list->size < r) {				//���� ����Ʈ ũ�⺸�� ������ Ŭ ��
		printf("invalid position\n");	//���� ���� ��ȿ���� ����
	}
	else {
		int i;
		ListNode* visit = list->header;					//Ư�� ��� ã�� ����

		for (i = 0; i < r; i++) visit = visit->next;	//��ġ ã��
		printf("%c\n", visit->elem);
	}
}

void print(ListType* list) {
	if (list->size != 0) {
		ListNode* visit = list->header->next;

		while (visit != list->trailer) {
			printf("%c", visit->elem);
			visit = visit->next;
		}
		printf("\n");
	}
}


int main() {
	int i, num, rank;
	char ch, element;
	ListType* list;

	list = malloc(sizeof(ListType));			//����Ʈ ����
	list->size = 0;
	list->header = malloc(sizeof(ListNode));	//��� ����
	list->trailer = malloc(sizeof(ListNode));	//Ʈ���Ϸ� ����
	
	scanf("%d", &num);
	getchar();

	for (i = 0; i < num; i++) {
		scanf("%c", &ch);
		getchar();

		if (ch == 'A') {		//add()
			scanf("%d %c", &rank, &element);
			getchar();
			add(list, rank, element);
		}
		else if (ch == 'D') {	//delete()
			scanf("%d", &rank);
			getchar();
			delete(list, rank);
		}
		else if (ch == 'G') {	//get()
			scanf("%d", &rank);
			getchar();
			get(list, rank);
		}
		else if (ch == 'P') {	//print()
			print(list);
		}
	}
	free(list->trailer);
	free(list->header);
	free(list);
}