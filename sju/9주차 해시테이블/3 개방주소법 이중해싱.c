#include<stdio.h>
#include<stdlib.h>

//개방주소법 해시테이블 - 이중해싱

int rehash(int key, int q) {	//q는 M보다 조금 작은 소수
	return q - (key % q);
}

void insertData(int* h, int key, int size, int q) {	//키를 해시테이블에 삽입
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

void searchData(int* h, int key, int size) {	//키가 해시테이블에 존재하는지 탐색
	int flag = 0;

	for (int i = 0; i < size; i++)
		if (h[i] == key) {
			printf("%d %d\n", i, key);
			flag++;
		}
	if (flag == 0) printf("-1\n");
}

void printData(int* h, int size) {	//현재의 해시테이블 인쇄
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