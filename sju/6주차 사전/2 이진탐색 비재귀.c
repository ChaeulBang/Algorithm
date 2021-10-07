#include<stdio.h>
#include<stdlib.h>

//이진탐색-비재귀버전
//정렬되어 있는 n개의 정수 키와 탐색할 키 k를 입력받아 사전에서 k의 위치를 출력

int BinarySearch(int* arr, int size, int key) {
	int left = 0;
	int right = size - 1;
	int mid;	//탐색 범위의 가운데 인덱스

	while (left <= right) {
		mid = (left + right) / 2;

		if (key == arr[mid]) return mid;	//탐색 성공
		else if (key < arr[mid]) right = mid - 1;	//탐색 범위를 왼쪽으로 변경
		else left = mid + 1;	//탐색 범위를 오른쪽으로 변경
	}

	return left;	//탐색 실패 시 k보다 큰 수 중 가장 작은 키의 인덱스 반환
}


int main() {
	int i, n, k, val = 0;
	int* dic;

	scanf("%d %d", &n, &k);
	dic = (int*)malloc(n * sizeof(int));	//크기 n인 배열 동적 할당
	for (i = 0; i < n; i++) scanf("%d", &dic[i]);	//사전의 키 저장 (중복 키 없음)

	/*
	val = BinarySearch(dic, n, k);	//이진탐색 수행

	if (val == -1) {	//탐색 실패 시
		for (i = n - 1; i >= 0 && dic[i] > k; i--);	//k보다 큰 수 중 가장 작은 키의 위치 찾기
		val = i + 1;
	}
	*/

	printf(" %d", BinarySearch(dic, n, k));	//출력

	free(dic);	//메모리 해제
}