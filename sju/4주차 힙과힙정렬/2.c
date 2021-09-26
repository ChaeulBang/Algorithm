#include<stdio.h>

int H[100];		//��
int n, n2;		//���� ũ��(�� Ű ����)

void inPlaceHeapSort();		//n���� Ű�� ������ �����迭�� ���ڸ� �� ����
void printArray();			//�迭�� ����� Ű���� ���ʷ� �μ�

void downHeap(int i);		//�� �� ��ġ �ε��� i�� ����� Ű�� ũ�⿡ �´� ��ġ�� ���� �̵�
void insertItem(int key);	//n ��ġ�� key ����, upHeap(n) ȣ�� ���� �� n ����
void upHeap(int i);			//�� �� ��ġ �ε��� i�� ����� Ű�� ũ�⿡ �´� ��ġ�� ���� �̵�
void rBuildHeap(int i);		//��� ������� ����� �� ����(i�� �κ� ���� ��Ʈ �ε���)
void buildHeap();			//����� ������� ����� �� ����


int main() {
	int temp, root, key;

	scanf("%d", &n);									//Ű ���� �Է�
	n2 = n;
	for (int i = 0; i < n; i++) scanf("%d", &H[i + 1]);	//Ű �Է�
	inPlaceHeapSort();
	printArray();		//�μ�
}


void inPlaceHeapSort() {
	rBuildHeap(1);					//1�ܰ�
	for (int i = n; i > 1; i--) {	//2�ܰ� (removeMax)
		int temp = H[1];			//���� ������ Ű�� ��Ʈ�� ��ȯ (�ִ��� �÷���)
		H[1] = H[i];
		H[i] = temp;

		n--;			//n ����
		downHeap(1);	//����
	}
}

void printArray() {
	int i;

	for (i = 1; i <= n2; i++) printf(" %d", H[i]);
}

void downHeap(int i) {
	int temp, max;

	if (n >= i * 2) {					//���� �ڽ� ��� ����
		max = i * 2;
		if (n >= i * 2 + 1)				//������ �ڽ� ��� ����
			if (H[i * 2 + 1] > H[max])	//�ڽ� ��� �� �� ū Ű �� ����
				max = i * 2 + 1;
		if (H[i] < H[max]) {			//�θ�� �ڽ� �� �� ��ȯ
			temp = H[i];
			H[i] = H[max];
			H[max] = temp;
			downHeap(max);				//���ȣ��
		}
	}
}

void insertItem(int key) {	//�� ����
	n++;		//n ����
	H[n] = key;	//���� key�� ����
	upHeap(n);	//�� ����
}

void upHeap(int i) {
	int temp;

	while (H[i] > H[i / 2]) {	//H[i]�� �θ� ��� �ε����� i / 2
		if (i == 1) break;		//��Ʈ���� ��ü ������ �̷������ ��� �ݺ��� ����

		//��ü ����
		temp = H[i];
		H[i] = H[i / 2];
		H[i / 2] = temp;

		i /= 2; //��ü ���� ���� �� �ٽ� ��ü ������ �����ؾ� �ϴ��� Ȯ���ϱ� ���� �ε����� ������ ������ (�θ����� �ڸ��� �̵�)
	}
}

//�Ʒ� ������ �����Ͽ� ���� ���� �ִ��� �÷��ִ� ����
void rBuildHeap(int i) {
	if (i <= n) {				//��ȿ�� �ε��� ��ȣ�� ���
		rBuildHeap(i * 2);		//���� ��Ʈ���� �� ��Ʈ���� �� ����
		rBuildHeap(i * 2 + 1);	//���� ��Ʈ���� �� ��Ʈ���� �� ����
		downHeap(i);			//���� ��Ʈ���� ��Ʈ�� �¿� ��Ʈ���� ��ģ �� ����
	}
}

void buildHeap() {
	int i;

	//�ڽĳ�尡 ���� �� �����ϸ� �ǹǷ� �ڽ� ��尡 �����ϴ� ù��° ����� n /2�� ������ �Ųٷ� �ö󰡸鼭 ������ ����
	for (i = n / 2; i >= 1; i--) downHeap(i);
}