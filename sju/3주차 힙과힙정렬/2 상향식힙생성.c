#include<stdio.h>

int H[100];	//힙 선언
int n;		//힙의 크기(총 키 개수)

void rBuildHeap(int i);	//재귀 방식으로 상향식 힙 생성(i는 부분 힙의 루트 인덱스)
void buildHeap();		//비재귀 방식으로 상향식 힙 생성
void downHeap(int i);	//힙 내 위치 인덱스 i에 저장된 키를 크기에 맞는 위치로 하향 이동
void printHeap();		//힙에 저장된 키들을 레벨 순서로 인쇄


int main() {
	scanf("%d", &n);									//키 개수 입력
	for (int i = 0; i < n; i++) scanf("%d", &H[i + 1]);	//키들이 미리 한꺼번에 주어짐
	rBuildHeap(1);
	printHeap();
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