#include<stdio.h>

int H[100];		//힙
int n, n2;		//힙의 크기(총 키 개수)

void inPlaceHeapSort();		//n개의 키로 구성된 무순배열을 제자리 힙 정렬
void printArray();			//배열에 저장된 키들을 차례로 인쇄

void downHeap(int i);		//힙 내 위치 인덱스 i에 저장된 키를 크기에 맞는 위치로 하향 이동
void insertItem(int key);	//n 위치에 key 삽입, upHeap(n) 호출 수행 후 n 갱신
void upHeap(int i);			//힙 내 위치 인덱스 i에 저장된 키를 크기에 맞는 위치로 상향 이동
void rBuildHeap(int i);		//재귀 방식으로 상향식 힙 생성(i는 부분 힙의 루트 인덱스)
void buildHeap();			//비재귀 방식으로 상향식 힙 생성


int main() {
	int temp, root, key;

	scanf("%d", &n);									//키 개수 입력
	n2 = n;
	for (int i = 0; i < n; i++) scanf("%d", &H[i + 1]);	//키 입력
	inPlaceHeapSort();
	printArray();		//인쇄
}


void inPlaceHeapSort() {
	rBuildHeap(1);					//1단계
	for (int i = n; i > 1; i--) {	//2단계 (removeMax)
		int temp = H[1];			//가장 마지막 키를 루트와 교환 (최댓값을 올려줌)
		H[1] = H[i];
		H[i] = temp;

		n--;			//n 조정
		downHeap(1);	//정렬
	}
}

void printArray() {
	int i;

	for (i = 1; i <= n2; i++) printf(" %d", H[i]);
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

void insertItem(int key) {	//힙 삽입
	n++;		//n 갱신
	H[n] = key;	//힙에 key값 삽입
	upHeap(n);	//힙 조정
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

//아래 노드부터 시작하여 위의 노드로 최댓값을 올려주는 정렬
void rBuildHeap(int i) {
	if (i <= n) {				//유효한 인덱스 번호일 경우
		rBuildHeap(i * 2);		//현재 부트리의 좌 부트리를 힙 생성
		rBuildHeap(i * 2 + 1);	//현재 부트리의 우 부트리를 힙 생성
		downHeap(i);			//현재 부트리의 루트와 좌우 부트리를 합친 힙 생성
	}
}

void buildHeap() {
	int i;

	//자식노드가 있을 때 수행하면 되므로 자식 노드가 존재하는 첫번째 노드인 n /2번 노드부터 거꾸로 올라가면서 정렬을 수행
	for (i = n / 2; i >= 1; i--) downHeap(i);
}