//힙을 전역변수로 선언하지 않고 구현
//힙을 인자로 주고받음

#include<stdio.h>
#include<stdlib.h>

int n, n2;

int* inPlaceHeapSort(int H[]);
void printArray(int H[]);
int* downHeap(int i, int H[]);
int* rBuildHeap(int i, int H[]);
int* buildHeap(int H[]);


int main() {
	int temp, root, key;

	scanf("%d", &n);
	int* H = (int*)malloc(n * sizeof(int));
	n2 = n;
	for (int i = 0; i < n; i++) scanf("%d", &H[i + 1]);
	H = inPlaceHeapSort(H);
	printArray(H);
}


int* inPlaceHeapSort(int H[]) {
	H = rBuildHeap(1, H);
	for (int i = n; i > 1; i--) {
		int temp = H[1];
		H[1] = H[i];
		H[i] = temp;

		n--;
		H = downHeap(1, H);
	}
	return H;
}

void printArray(int H[]) {
	int i;

	for (i = 1; i <= n2; i++) printf(" %d", H[i]);
}

int* downHeap(int i, int H[]) {
	int temp, max;

	if (n >= i * 2) {
		max = i * 2;
		if (n >= i * 2 + 1)
			if (H[i * 2 + 1] > H[max])
				max = i * 2 + 1;
		if (H[i] < H[max]) {
			temp = H[i];
			H[i] = H[max];
			H[max] = temp;
			H = downHeap(max, H);
		}
	}

	return H;
}

int* rBuildHeap(int i, int H[]) {
	if (i <= n) {
		H = rBuildHeap(i * 2, H);
		H = rBuildHeap(i * 2 + 1, H);
		H = downHeap(i, H);
	}

	return H;
}

int* buildHeap(int H[]) {
	int i;

	for (i = n / 2; i >= 1; i--) downHeap(i, H);

	return H;
}