#include<stdio.h>
#include<stdlib.h>

//�и������ �ؽ����̺�

typedef struct Bucket {	//���� ����ü
	int data;
	struct Bucket* next;
}Bucket;

typedef struct HashTable {
	int size;
	Bucket** table;	//�ؽ����̺��� ù ��ҿ� ���� ������
}HashTable;

void insertNode(HashTable* h, int key) {	//Ű�� �ؽ����̺� ����
	int hash = key % (h->size);
	Bucket* b = h->table[hash];
	Bucket* tmp;

	while (b != NULL) {
		if (b->data == key) return;
		b = b->next;
	}

	tmp = (Bucket*)malloc(sizeof(Bucket));
	tmp->data = key;
	tmp->next = h->table[hash];
	h->table[hash] = tmp;
}

int searchNode(HashTable* h, int key) {	//Ű�� �ؽ����̺� �����ϴ��� Ž��
	int hash = key % (h->size);
	Bucket* b = h->table[hash];
	int rank = 1;

	while (b != NULL) {
		if (b->data == key) return rank;
		b = b->next;
		rank++;
	}

	return 0;
}

int deleteNode(HashTable* h, int key) {
	int hash = key % (h->size);
	Bucket* b = h->table[hash];
	Bucket** bp = &h->table[hash];
	int rank = 1;

	while (b != NULL) {
		if (b->data == key) {
			//h->table[hash] = b->next;
			*bp = b->next;
			free(b);
			return rank;
		}
		bp = &b->next;
		b = b->next;
		rank++;
	}

	return 0;
}

void printNode(HashTable* h) {	//����� Ű���� ������� �μ�
	for (int i = 0; i < h->size; i++) {
		Bucket* tmp = h->table[i];
		while (tmp != NULL) {
			printf(" %d", tmp->data);
			tmp = tmp->next;
		}
	}
	printf("\n");
}


int main() {
	int M, key;
	HashTable h;

	scanf("%d", &M);
	h.size = M;
	h.table = (Bucket**)malloc(sizeof(Bucket*) * M);

	for (int i = 0; i < M; i++) {
		h.table[i] = NULL;
	}

	while (1) {
		switch (getchar()) {
		case 'i':
			scanf("%d", &key);
			insertNode(&h, key);
			break;
		case 's':
			scanf("%d", &key);
			printf("%d\n", searchNode(&h, key));
			break;
		case 'd':
			scanf("%d", &key);
			printf("%d\n", deleteNode(&h, key));
			break;
		case 'p':
			printNode(&h);
			break;
		case 'e':
			goto QUIT;
		}
	}
QUIT:
	return 0;
}