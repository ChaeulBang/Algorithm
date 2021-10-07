#include<stdio.h>
#include<stdlib.h>

//����Ž��-����͹���
//���ĵǾ� �ִ� n���� ���� Ű�� Ž���� Ű k�� �Է¹޾� �������� k�� ��ġ�� ���

int BinarySearch(int* arr, int size, int key) {
	int left = 0;
	int right = size - 1;
	int mid;	//Ž�� ������ ��� �ε���

	while (left <= right) {
		mid = (left + right) / 2;

		if (key == arr[mid]) return mid;	//Ž�� ����
		else if (key < arr[mid]) right = mid - 1;	//Ž�� ������ �������� ����
		else left = mid + 1;	//Ž�� ������ ���������� ����
	}

	return left;	//Ž�� ���� �� k���� ū �� �� ���� ���� Ű�� �ε��� ��ȯ
}


int main() {
	int i, n, k, val = 0;
	int* dic;

	scanf("%d %d", &n, &k);
	dic = (int*)malloc(n * sizeof(int));	//ũ�� n�� �迭 ���� �Ҵ�
	for (i = 0; i < n; i++) scanf("%d", &dic[i]);	//������ Ű ���� (�ߺ� Ű ����)

	/*
	val = BinarySearch(dic, n, k);	//����Ž�� ����

	if (val == -1) {	//Ž�� ���� ��
		for (i = n - 1; i >= 0 && dic[i] > k; i--);	//k���� ū �� �� ���� ���� Ű�� ��ġ ã��
		val = i + 1;
	}
	*/

	printf(" %d", BinarySearch(dic, n, k));	//���

	free(dic);	//�޸� ����
}