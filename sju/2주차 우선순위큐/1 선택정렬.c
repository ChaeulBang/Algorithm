#include<stdio.h>
#include<stdlib.h>


int main() {
	int i, j, n, max, maxPos, temp;
	int* arr;

	scanf("%d", &n);	//배열 크기
	arr = (int*)malloc(sizeof(int) * n);

	for (i = 0; i < n; ++i) scanf("%d", &arr[i]);	//정수 입력

	for (i = n - 1; i >= 1; i--) {	//맨 뒤에서부터 두 번째 정수까지
		//인덱스 0번의 원소는 인덱스 1번의 원소를 정렬하면서 이미 정렬
		max = arr[i];	//첫 번째를 최댓값이라 가정
		maxPos = i;		//최댓값의 인덱스

		for (j = 0; j < i; ++j) {
			if (max < arr[j]) {	//더 큰 값이 있을 경우 그 값을 최댓값으로 변경
				max = arr[j];
				maxPos = j;
			}
		}
		if (maxPos != i) {		//최댓값의 인덱스가 i가 아닐 경우 변경
			temp = arr[i];
			arr[i] = arr[maxPos];
			arr[maxPos] = temp;
		}
	}

	for (i = 0; i < n; i++) printf(" %d", arr[i]);

	free(arr);
}