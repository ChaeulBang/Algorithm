#include<stdio.h>
#include<stdlib.h>


int main() {
	int i, j, n, temp;
	int* arr;

	scanf("%d", &n);	//�迭 ũ��
	arr = (int*)malloc(sizeof(int) * n);

	for (i = 0; i < n; i++) scanf("%d", &arr[i]);	//���� �Է�

	for (i = 1; i < n; i++) {			//�� ��°���� n��°����
		for (j = i; j >= 1; j--) {		//�ε��� 0���� i������ ���ĵ� �迭
			if (arr[j] < arr[j - 1]) {	//�迭 �ڷᱸ�� - �ڷ� ���� ���� ������ ��ȯ ������ �ؾ� ��
				//���� ���ҿ� ��ȯ ������ �����ϸ� �ڸ� ã��
				temp = arr[j];
				arr[j] = arr[j - 1];
				arr[j - 1] = temp;
			}
			else break;	//�ڸ� ã���� ��� �ݺ��� ����
		}
	}

	for (i = 0; i < n; i++) printf(" %d", arr[i]);

	free(arr);
}