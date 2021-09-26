#include<stdio.h>
#include<stdlib.h>


int main() {
	int i, j, n, temp;
	int* arr;

	scanf("%d", &n);	//배열 크기
	arr = (int*)malloc(sizeof(int) * n);

	for (i = 0; i < n; i++) scanf("%d", &arr[i]);	//정수 입력

	for (i = 1; i < n; i++) {			//두 번째부터 n번째까지
		for (j = i; j >= 1; j--) {		//인덱스 0부터 i까지가 정렬된 배열
			if (arr[j] < arr[j - 1]) {	//배열 자료구조 - 자료 삽입 위해 어차피 교환 연산을 해야 함
				//앞의 원소와 교환 연산을 수행하며 자리 찾기
				temp = arr[j];
				arr[j] = arr[j - 1];
				arr[j - 1] = temp;
			}
			else break;	//자리 찾았을 경우 반복문 종료
		}
	}

	for (i = 0; i < n; i++) printf(" %d", arr[i]);

	free(arr);
}