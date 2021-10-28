#include<stdio.h>
#include<stdlib.h>

//�����ּҹ� �ؽ����̺� - �����ؽ�

int rehash(int key, int q) {	//q�� M���� ���� ���� �Ҽ�
	return q - (key % q);
}

void insertData(int* h, int key, int size, int q) {	//Ű�� �ؽ����̺� ����
	int i = 1;
	int hash = key % size;
	int rhash = rehash(key, q);

	if (h[hash] == 0) {
		h[hash] = key;
		printf("%d\n", hash);
	}

	else {
		while (1) {
			hash = (hash + rhash) % size;

			if (h[hash] == 0) {
				h[hash] = key;
				for (int j = 0; j < i; j++) printf("C");
				printf("%d\n", hash);
				return;
			}
			else i++;
		}
	}
}

void searchData(int* h, int key, int size) {	//Ű�� �ؽ����̺� �����ϴ��� Ž��
	int flag = 0;

	for (int i = 0; i < size; i++)
		if (h[i] == key) {
			printf("%d %d\n", i, key);
			flag++;
		}
	if (flag == 0) printf("-1\n");
}

void printData(int* h, int size) {	//������ �ؽ����̺� �μ�
	for (int i = 0; i < size; i++) printf(" %d", h[i]);
	printf("\n");
}


int main() {
	int M, n, q, key, hash, cnt = 0, flag;

	scanf("%d %d %d", &M, &n, &q);
	int* hashTable = (int*)malloc(sizeof(int) * M);

	for (int i = 0; i < M; i++) hashTable[i] = 0;

	while (1) {
		switch (getchar()) {
		case 'i':
			scanf("%d", &key);
			insertData(hashTable, key, M, q);
			break;
		case 's':
			scanf("%d", &key);
			searchData(hashTable, key, M);
			break;
		case 'p':
			printData(hashTable, M);
			break;
		case 'e':
			printData(hashTable, M);
			goto QUIT;
		}
	}
QUIT:
	return 0;
}