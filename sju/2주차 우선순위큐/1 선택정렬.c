#include<stdio.h>
#include<stdlib.h>


int main() {
	int i, j, n, max, maxPos, temp;
	int* arr;

	scanf("%d", &n);	//�迭 ũ��
	arr = (int*)malloc(sizeof(int) * n);

	for (i = 0; i < n; ++i) scanf("%d", &arr[i]);	//���� �Է�

	for (i = n - 1; i >= 1; i--) {	//�� �ڿ������� �� ��° ��������
		//�ε��� 0���� ���Ҵ� �ε��� 1���� ���Ҹ� �����ϸ鼭 �̹� ����
		max = arr[i];	//ù ��°�� �ִ��̶� ����
		maxPos = i;		//�ִ��� �ε���

		for (j = 0; j < i; ++j) {
			if (max < arr[j]) {	//�� ū ���� ���� ��� �� ���� �ִ����� ����
				max = arr[j];
				maxPos = j;
			}
		}
		if (maxPos != i) {		//�ִ��� �ε����� i�� �ƴ� ��� ����
			temp = arr[i];
			arr[i] = arr[maxPos];
			arr[maxPos] = temp;
		}
	}

	for (i = 0; i < n; i++) printf(" %d", arr[i]);

	free(arr);
}