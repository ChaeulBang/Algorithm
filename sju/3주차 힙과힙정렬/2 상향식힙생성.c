#include<stdio.h>

int H[100];	//�� ����
int n;		//���� ũ��(�� Ű ����)

void rBuildHeap(int i);	//��� ������� ����� �� ����(i�� �κ� ���� ��Ʈ �ε���)
void buildHeap();		//����� ������� ����� �� ����
void downHeap(int i);	//�� �� ��ġ �ε��� i�� ����� Ű�� ũ�⿡ �´� ��ġ�� ���� �̵�
void printHeap();		//���� ����� Ű���� ���� ������ �μ�


int main() {
	scanf("%d", &n);									//Ű ���� �Է�
	for (int i = 0; i < n; i++) scanf("%d", &H[i + 1]);	//Ű���� �̸� �Ѳ����� �־���
	rBuildHeap(1);
	printHeap();
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