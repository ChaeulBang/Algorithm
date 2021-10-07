#include<stdio.h>
#include<stdlib.h>

//����Ž��-��͹���
//���ĵǾ� �ִ� n���� ���� Ű�� Ž���� Ű k�� �Է¹޾� �������� k�� ��ġ�� ���

int BSRecursive(int* arr, int left, int right, int key) {
	int mid = (left + right) / 2;	//Ž�� ������ ��� �ε���

	if (left > right) return right;	//Ž�� ���� �� k���� ���� �� �� ���� ū Ű�� �ε��� ��ȯ
	if (key == arr[mid]) return mid;	//Ž�� ����
	else if (key < arr[mid]) return BSRecursive(arr, left, mid - 1, key);	//Ž�� ������ �������� ����
	else return BSRecursive(arr, mid + 1, right, key);	//Ž�� ������ ���������� ����
}


int main() {
	int i, n, k, val = 0;
	int* dic;

	scanf("%d %d", &n, &k);
	dic = (int*)malloc(n * sizeof(int));	//ũ�� n�� �迭 ���� �Ҵ�
	for (i = 0; i < n; i++) scanf("%d", &dic[i]);	//������ Ű ���� (�ߺ� Ű ����)

	/*
	val = BSRecursive(dic, 0, n - 1, k);	//����Ž�� ����

	if (val == -1) {	//Ž�� ���� ��
		for (i = 0; i < n && dic[i] < k; i++);	//k���� ���� �� �� ���� ū Ű�� ��ġ ã��
		val = i - 1;
	}
	*/

	printf(" %d", BSRecursive(dic, 0, n - 1, k));	//���

	free(dic);	//�޸� ����
}