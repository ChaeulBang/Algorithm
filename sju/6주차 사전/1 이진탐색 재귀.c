#include<stdio.h>
#include<stdlib.h>

//이진탐색-재귀버전
//정렬되어 있는 n개의 정수 키와 탐색할 키 k를 입력받아 사전에서 k의 위치를 출력

int BSRecursive(int* arr, int left, int right, int key) {
	int mid = (left + right) / 2;	//탐색 범위의 가운데 인덱스

	if (left > right) return right;	//탐색 실패 시 k보다 작은 수 중 가장 큰 키의 인덱스 반환
	if (key == arr[mid]) return mid;	//탐색 성공
	else if (key < arr[mid]) return BSRecursive(arr, left, mid - 1, key);	//탐색 범위를 왼쪽으로 변경
	else return BSRecursive(arr, mid + 1, right, key);	//탐색 범위를 오른쪽으로 변경
}


int main() {
	int i, n, k, val = 0;
	int* dic;

	scanf("%d %d", &n, &k);
	dic = (int*)malloc(n * sizeof(int));	//크기 n인 배열 동적 할당
	for (i = 0; i < n; i++) scanf("%d", &dic[i]);	//사전의 키 저장 (중복 키 없음)

	/*
	val = BSRecursive(dic, 0, n - 1, k);	//이진탐색 수행

	if (val == -1) {	//탐색 실패 시
		for (i = 0; i < n && dic[i] < k; i++);	//k보다 작은 수 중 가장 큰 키의 위치 찾기
		val = i - 1;
	}
	*/

	printf(" %d", BSRecursive(dic, 0, n - 1, k));	//출력

	free(dic);	//메모리 해제
}