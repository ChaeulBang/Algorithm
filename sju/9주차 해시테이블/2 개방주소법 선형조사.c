#include<stdio.h>
#include<stdlib.h>

//개방주소법 해시테이블 - 선형조사법

void insertData(int* h, int key, int size) {
	int i = 0;
	int _hash = key % size;
	int hash;


	while (i < size) {
		hash = (_hash + i) % size;

		if (h[hash] == 0) {
			h[hash] = key;
			for (int j = 0; j < i; j++) printf("C");
			printf("%d\n", hash);
			return;
		}
		else i++;
	}
}

void searchData(int* h, int key, int size) {
	int flag = 0;

	for (int i = 0; i < size; i++)
		if (h[i] == key) {
			printf("%d %d\n", i, key);
			flag++;
		}
	if (flag == 0) printf("-1\n");
}


int main() {
	int M, n, key, hash, cnt = 0, flag;

	scanf("%d %d", &M, &n);
	int* hashTable = (int*)malloc(sizeof(int) * M);

	for (int i = 0; i < M; i++) hashTable[i] = 0;

	while (1) {
		switch (getchar()) {
		case 'i':
			scanf("%d", &key);
			insertData(hashTable, key, M);
			break;
		case 's':
			scanf("%d", &key);
			searchData(hashTable, key, M);
			break;
		case 'e':
			goto QUIT;
		}
	}
QUIT:
	return 0;
}