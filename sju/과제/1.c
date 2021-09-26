#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<windows.h>

void selectionSort(int n, int* arr);			//��������
void insertionSort(int n, int* arr);			//��������
void insertionSort_Reverse(int n, int* arr);	//���� ����


int main() {

	int i, n = 10000;
	int* a;
	LARGE_INTEGER ticksPerSec;
	LARGE_INTEGER start, end, diff;
	QueryPerformanceFrequency(&ticksPerSec);	//�� ��ǻ���� Ÿ�̸��� ���ļ��� ��� ticksPerSec�� ����
	srand(time(NULL));							//���� �Լ��� seed�� ���� �ð����� ����

	for (int j = 0; j < 10; j++, n += 10000) {
		a = (int*)malloc(sizeof(int) * n);

		for (i = 0; i < n; i++) a[i] = i;
		insertionSort_Reverse(n, a);

		QueryPerformanceCounter(&start);
		insertionSort(n, a);					//�������� �� insertionSort()
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

	scanf("%d", &n);	//�迭 ũ�� �Է�
	QueryPerformanceFrequency(&ticksPerSec);	//�� ��ǻ���� Ÿ�̸��� ���ļ��� ��� ticksPerSec�� ����
	srand(time(NULL));							//���� �Լ��� seed�� ���� �ð����� ����

	for (int j = 0; j < 10; j++) {
		a = (int*)malloc(sizeof(int) * n);		//�� �迭 �����Ҵ�
		b = (int*)malloc(sizeof(int) * n);

		for (i = 0; i < n; i++) a[i] = b[i] = rand();	//�� �迭�� ������ �������� ����

		//��������
		QueryPerformanceCounter(&start);				//���� ����
		selectionSort(n, a);
		QueryPerformanceCounter(&end);					//���� ��
		diff.QuadPart = end.QuadPart - start.QuadPart;	//���������κ��� ����ð� ���
		printf("%.5f\n", ((double)diff.QuadPart / (double)ticksPerSec.QuadPart) * 1000);

		//��������
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

	for (i = 0; i < n - 1; i++) {	//������ ��Ҵ� �ڵ����� ����
		least = i;

		for (j = i + 1; j < n; j++) {	//�ּڰ� Ž��
			if (arr[j] < arr[least])
				least = j;
		}

		if (i != least) {	//���õ� ��Ұ� �ּڰ��̸� �ڸ� ��ȯ���� ����
			temp = arr[i];
			arr[i] = arr[least];
			arr[least] = temp;
		}
	}
}

void insertionSort(int n, int* arr) {
	int i, j, temp;

	for (i = 1; i < n; i++) {	//ù ��Ҵ� �̹� ���ĵ�
		temp = arr[i];	//temp ������ ���� ��� �ӽ� ����
		for (j = i - 1; j >= 0 && arr[j] > temp; j--) {	//���� ��Һ��� ū ���̶�� �ڸ� ��ȯ
			arr[j + 1] = arr[j];
		}
		arr[j + 1] = temp;	//�ӽ� ����� ��� ����
	}
}

void insertionSort_Reverse(int n, int* arr) {
	int i, j, temp;

	for (i = 1; i < n; i++) {	//ù ��Ҵ� �̹� ���ĵ�
		temp = arr[i];	//temp ������ ���� ��� �ӽ� ����
		for (j = i - 1; j >= 0 && arr[j] < temp; j--) {	//	//���� ��Һ��� ���� ���̶�� �ڸ� ��ȯ
			arr[j + 1] = arr[j];
		}
		arr[j + 1] = temp;	//�ӽ� ����� ��� ����
	}
}