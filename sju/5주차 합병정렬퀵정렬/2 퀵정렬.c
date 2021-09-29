#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int findPivot(int* L, int l, int r);	//pivot 위치 입력배열의 l과 r 사이의 1개로 무작위 선택
void inPlacePartition(int* L, int l, int r, int k, int* a, int* b);	//분할
void inPlaceQuickSort(int* L, int l, int r);	//제자리 퀵 정렬


int main() {
	int n;	//배열의 크기
	int* L;	//배열

	scanf("%d", &n);
	L = (int*)malloc(n * sizeof(int));	//배열 동적 할당

	for (int i = 0; i < n; i++) scanf("%d", &L[i]);	//배열에 정수 저장

	inPlaceQuickSort(L, 0, n - 1);
	for (int i = 0; i < n; i++) printf(" %d", L[i]);	//출력
	free(L);	//메모리 해제
}


int findPivot(int* L, int l, int r) {
	int pivot;
	srand(time(NULL));

	if (r == 1) return l;

	else {
		while (1) {
			pivot = (rand() % (r - l)) + l;
			if (pivot < r) {
				return pivot;
				break;
			}
		}
	}
}

void inPlacePartition(int* L, int l, int r, int k, int* a, int* b) {	//제자리 분할
	int p = L[k], temp, i, j;

	//hide pivot
	temp = L[k];
	L[k] = L[r];
	L[r] = temp;

	i = l;
	j = r - 1;

	while (i <= j) {
		while (i <= j && L[i] < p) i = i + 1;
		while (j >= i && L[j] >= p) j = j - 1;

		if (i < j) {
			temp = L[i];
			L[i] = L[j];
			L[j] = temp;
		}
	}

	//replace pivot
	temp = L[i];
	L[i] = L[r];
	L[r] = temp;

	//중복 값 처리
	*a = i;
	*b = *a + 1;
	while (1) {
		if (L[*a] != L[*b]) {
			(*b)--;
			break;
		}
		(*b)++;
	}
}

void inPlaceQuickSort(int* L, int l, int r) {
	int k, a, b;
	int* pa = &a, * pb = &b;

	if (l >= r) return;

	k = findPivot(L, l, r);	//pivot 저장
	inPlacePartition(L, l, r, k, pa, pb);	//분할

	inPlaceQuickSort(L, l, a - 1);
	inPlaceQuickSort(L, b + 1, r);
}