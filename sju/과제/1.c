#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<windows.h>

void selectionSort(int n, int* arr);			//선택정렬
void insertionSort(int n, int* arr);			//삽입정렬
void insertionSort_Reverse(int n, int* arr);	//역순 정렬


int main() {

	int i, n = 10000;
	int* a;
	LARGE_INTEGER ticksPerSec;
	LARGE_INTEGER start, end, diff;
	QueryPerformanceFrequency(&ticksPerSec);	//내 컴퓨터의 타이머의 주파수를 얻어 ticksPerSec에 저장
	srand(time(NULL));							//랜덤 함수의 seed를 현재 시간으로 설정

	for (int j = 0; j < 10; j++, n += 10000) {
		a = (int*)malloc(sizeof(int) * n);

		for (i = 0; i < n; i++) a[i] = i;
		insertionSort_Reverse(n, a);

		QueryPerformanceCounter(&start);
		insertionSort(n, a);					//삽입정렬 시 insertionSort()
		QueryPerformanceCounter(&end);
		diff.QuadPart = end.QuadPart - start.QuadPart;
		printf("%.5f\n", ((double)diff.QuadPart / (double)ticksPerSec.QuadPart) * 1000);

		free(a);
	}

	/*
	int i, n;
	int* a, * b;
	LARGE_INTEGER ticksPerSec;
	LARGE_INTEGER start, end, diff;

	scanf("%d", &n);	//배열 크기 입력
	QueryPerformanceFrequency(&ticksPerSec);	//내 컴퓨터의 타이머의 주파수를 얻어 ticksPerSec에 저장
	srand(time(NULL));							//랜덤 함수의 seed를 현재 시간으로 설정

	for (int j = 0; j < 10; j++) {
		a = (int*)malloc(sizeof(int) * n);		//각 배열 동적할당
		b = (int*)malloc(sizeof(int) * n);

		for (i = 0; i < n; i++) a[i] = b[i] = rand();	//각 배열에 동일한 랜덤값을 대입

		//선택정렬
		QueryPerformanceCounter(&start);				//측정 시작
		selectionSort(n, a);
		QueryPerformanceCounter(&end);					//측정 끝
		diff.QuadPart = end.QuadPart - start.QuadPart;	//측정값으로부터 실행시간 계산
		printf("%.5f\n", ((double)diff.QuadPart / (double)ticksPerSec.QuadPart) * 1000);

		//삽입정렬
		QueryPerformanceCounter(&start);
		insertionSort(n, b);
		QueryPerformanceCounter(&end);
		diff.QuadPart = end.QuadPart - start.QuadPart;
		printf("%.5f\n", ((double)diff.QuadPart / (double)ticksPerSec.QuadPart) * 1000);

		printf("\n");

		free(b);
		free(a);
	}
	*/

	return 0;
}


void selectionSort(int n, int* arr) {
	int i, j, least, temp;

	for (i = 0; i < n - 1; i++) {	//마지막 요소는 자동으로 정렬
		least = i;

		for (j = i + 1; j < n; j++) {	//최솟값 탐색
			if (arr[j] < arr[least])
				least = j;
		}

		if (i != least) {	//선택된 요소가 최솟값이면 자리 교환하지 않음
			temp = arr[i];
			arr[i] = arr[least];
			arr[least] = temp;
		}
	}
}

void insertionSort(int n, int* arr) {
	int i, j, temp;

	for (i = 1; i < n; i++) {	//첫 요소는 이미 정렬됨
		temp = arr[i];	//temp 변수에 현재 요소 임시 저장
		for (j = i - 1; j >= 0 && arr[j] > temp; j--) {	//현재 요소보다 큰 값이라면 자리 교환
			arr[j + 1] = arr[j];
		}
		arr[j + 1] = temp;	//임시 저장된 요소 삽입
	}
}

void insertionSort_Reverse(int n, int* arr) {
	int i, j, temp;

	for (i = 1; i < n; i++) {	//첫 요소는 이미 정렬됨
		temp = arr[i];	//temp 변수에 현재 요소 임시 저장
		for (j = i - 1; j >= 0 && arr[j] < temp; j--) {	//	//현재 요소보다 작은 값이라면 자리 교환
			arr[j + 1] = arr[j];
		}
		arr[j + 1] = temp;	//임시 저장된 요소 삽입
	}
}