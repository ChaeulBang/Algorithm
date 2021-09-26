#include<stdio.h>

int H[100];	//힙 선언
int n;		//힙의 크기(총 키 개수)

void insertItem(int key);	//n 위치에 key 삽입, upHeap(n) 호출 수행 후 n 갱신
int removeMax();			//downHeap 호출 수행 후 n 갱신, 삭제된 키 반환
void upHeap(int i);			//힙 내 위치 인덱스 i에 저장된 키를 크기에 맞는 위치로 상향 이동
void downHeap(int i);		//힙 내 위치 인덱스 i에 저장된 키를 크기에 맞는 위치로 하향 이동
void printHeap();			//힙에 저장된 키들을 레벨 순서로 인쇄


int main() {
	int key;

	while (1) {
		switch (getchar()) {
		case 'i':
			scanf("%d", &key);
			insertItem(key);
			printf("0\n");
			break;
		case 'd':
			key = removeMax();
			printf("%d\n", key);
			break;
		case 'p':
			printHeap();
			break;
		case 'q':
			goto QUIT;
		}
	}
QUIT:
	return 0;
}


void insertItem(int key) {	//힙 삽입
	n++;		//n 갱신
	H[n] = key;	//힙에 key값 삽입
	upHeap(n);	//힙 조정
}

int removeMax() {	//힙 삭제
	int key;

	key = H[1];		//루트 키(최댓값) 보관
	H[1] = H[n];	//힙의 마지막 키를 루트로 이동
	n--;			//n 갱신
	downHeap(1);	//힙 보정

	return key;		//삭제 키 반환
}

void upHeap(int i) {
	int temp;

	while (H[i] > H[i / 2]) {	//H[i]의 부모 노드 인덱스는 i / 2
		if (i == 1) break;		//루트까지 교체 연산이 이루어졌을 경우 반복문 종료

		//교체 연산
		temp = H[i];
		H[i] = H[i / 2];
		H[i / 2] = temp;

		i /= 2; //교체 연산 수행 후 다시 교체 연산을 수행해야 하는지 확인하기 위해 인덱스를 반으로 나눠줌 (부모노드의 자리로 이동)
	}
}

void downHeap(int i) {
	int temp, max;

	if (n >= i * 2) {					//왼쪽 자식 노드 존재
		max = i * 2;
		if (n >= i * 2 + 1)				//오른쪽 자식 노드 존재
			if (H[i * 2 + 1] > H[max])	//자식 노드 중 더 큰 키 값 저장
				max = i * 2 + 1;
		if (H[i] < H[max]) {			//부모와 자식 비교 후 교환
			temp = H[i];
			H[i] = H[max];
			H[max] = temp;
			downHeap(max);				//재귀호출
		}
	}
}

void printHeap() {
	int i;

	for (i = 1; i <= n; i++) printf(" %d", H[i]);
	printf("\n");
}