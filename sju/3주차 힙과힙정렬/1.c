#include<stdio.h>

int H[100];	//�� ����
int n;		//���� ũ��(�� Ű ����)

void insertItem(int key);	//n ��ġ�� key ����, upHeap(n) ȣ�� ���� �� n ����
int removeMax();			//downHeap ȣ�� ���� �� n ����, ������ Ű ��ȯ
void upHeap(int i);			//�� �� ��ġ �ε��� i�� ����� Ű�� ũ�⿡ �´� ��ġ�� ���� �̵�
void downHeap(int i);		//�� �� ��ġ �ε��� i�� ����� Ű�� ũ�⿡ �´� ��ġ�� ���� �̵�
void printHeap();			//���� ����� Ű���� ���� ������ �μ�


int main() {
	int key;

	while (1) {
		switch (getchar()) {
		case 'i':
			scanf("%d", &key);
			insertItem(key);
			printf("0\n");
			break;
		case 'd':
			key = removeMax();
			printf("%d\n", key);
			break;
		case 'p':
			printHeap();
			break;
		case 'q':
			goto QUIT;
		}
	}
QUIT:
	return 0;
}


void insertItem(int key) {	//�� ����
	n++;		//n ����
	H[n] = key;	//���� key�� ����
	upHeap(n);	//�� ����
}

int removeMax() {	//�� ����
	int key;

	key = H[1];		//��Ʈ Ű(�ִ�) ����
	H[1] = H[n];	//���� ������ Ű�� ��Ʈ�� �̵�
	n--;			//n ����
	downHeap(1);	//�� ����

	return key;		//���� Ű ��ȯ
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

void printHeap() {
	int i;

	for (i = 1; i <= n; i++) printf(" %d", H[i]);
	printf("\n");
}