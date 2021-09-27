#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int findPivot(int* L, int l, int r) {
	int pivot;
	srand(time(NULL));

	if (r == 1) return l;

	else {
		while (1) {
			pivot = (rand() % (r - l)) + l;
			if (pivot < r) {
				return pivot;
				break;
			}
		}
	}
}

int inPlacePartition(int* L, int l, int r, int k) {	//���ڸ� ����
	int p = L[k], temp, i, j;

	//hide pivot
	temp = L[k];
	L[k] = L[r];
	L[r] = temp;

	i = l;
	j = r - 1;

	while (i <= j) {
		while (i <= j && L[i] < p) i = i + 1;
		while (j >= i && L[j] >= p) j = j - 1;

		if (i < j) {
			temp = L[i];
			L[i] = L[j];
			L[j] = temp;
		}
	}

	//replace pivot
	temp = L[i];
	L[i] = L[r];
	L[r] = temp;

	return i;
}

void inPlaceQuickSort(int* L, int l, int r) {
	int k, a, b;

	if (l >= r) return;

	k = findPivot(L, l, r);	//pivot ����
	a = inPlacePartition(L, l, r, k);
	b = a + 1;
	
	while (1) {
		if (L[a] != L[b]) {
			b--;
			break;
		}
		b++;
	}

	inPlaceQuickSort(L, l, a - 1);
	inPlaceQuickSort(L, b + 1, r);
}


int main() {
	int n;	//�迭�� ũ��
	int* L;	//�迭

	scanf("%d", &n);
	L = (int*)malloc(n * sizeof(int));	//�迭 ���� �Ҵ�

	for (int i = 0; i < n; i++) scanf("%d", &L[i]);	//�迭�� ���� ����

	inPlaceQuickSort(L, 0, n - 1);
	for (int i = 0; i < n; i++) printf(" %d", L[i]);	//���
	free(L);	//�޸� ����
}