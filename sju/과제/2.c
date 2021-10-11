#include<stdio.h>
#include<stdlib.h>

typedef struct Node {	//�ڽ� ��带 ����Ű�� �����Ϳ� ť�� �����ϱ� ���� ����ϴ� ���
	int data;
	struct Node* left;	//���� �ڽ�
	struct Node* right;	//������ �ڽ�
	struct Node* link;
} Node;

typedef struct {	//ť�� �����ϱ� ���� ������
	Node* front;
	Node* rear;
} Queue;

void enQueue(Queue* queue, Node* node) {	//Ʈ���� ��带 ť�� ����
	if (!queue->front) {
		queue->front = node;
		queue->rear = node;
	}
	else {
		queue->rear->link = node;
		queue->rear = node;
	}
}

Node* deQueue(Queue* queue) {	//���� ���� Ʈ�� ��带 ť���� ���� �� ��ȯ
	Node* temp;

	if (!queue->front) return NULL;

	temp = queue->front;
	queue->front = queue->front->link;

	return temp;
}

Node* peek(Queue* queue) {	//ť�� ���� ���� Ʈ�� ��带 ��ȯ
	if (!queue->front) return NULL;
	return queue->front;
}

void insertNode(Queue* queue, Node** root, int data) {	//��� ����
	Node* newNode = (Node*)malloc(sizeof(Node));
	newNode->data = data;
	newNode->left = NULL;
	newNode->right = NULL;
	newNode->link = NULL;

	//ť�� ������� ���
	if (!queue->front) {
		*root = newNode;
	}

	//ť�� ù��° ����� Ʈ���� ��尡 ���� á�� ��� (���� ���� ����� �ڽ� ��尡 �� �� ä���� �ִ����� Ȯ��)
	else if (peek(queue)->right != NULL) {	//������ �ڽı��� ä���� ���� ���
		deQueue(queue);	//ť���� ����
		peek(queue)->left = newNode;	//���ʿ� ��� ����
	}
	else if (peek(queue)->left != NULL) {	//���� �ڽĸ� ä���� ���� ���
		peek(queue)->right = newNode;	//�����ʿ� ��� ����
	}
	else {
		peek(queue)->left = newNode;
	}
	enQueue(queue, newNode);
}

void downHeap(Node* node) {	//Ű�� ũ�⿡ �´� ��ġ�� ���� �̵�
	Node* max;
	int temp;

	if (node->left != NULL) {							//���� �ڽ� ��� ����
		max = node->left;
		if (node->right != NULL)						//������ �ڽ� ��� ����
			if (node->right->data > node->left->data)	//�ڽ� ��� �� �� ū Ű �� ����
				max = node->right;
		if (node->data < max->data) {					//�θ�� �ڽ� �� �� �� ��ȯ (Ʈ���� ������ ������ �����Ƿ� ���� ����)
			temp = node->data;
			node->data = max->data;
			max->data = temp;
			downHeap(max);								//���ȣ��
		}
	}
}

void printHeap(Node* root) {	//���� ����� Ű���� ���� ������ �μ�
	Queue* queue;	//Ž���� ���� ť
	queue = (Queue*)malloc(sizeof(Queue));
	queue->front = NULL;
	queue->rear = NULL;
	enQueue(queue, root);

	while (queue->front) {
		Node* cur = deQueue(queue);

		if (cur->left) enQueue(queue, cur->left);
		if (cur->right) enQueue(queue, cur->right);
		printf(" %d", cur->data);
	}
	printf("\n");
}

void rBuildHeap(Node* root) {		//��� ������� ����� �� ����
	if (root) {						//��ȿ�� Ʈ���� ���
		rBuildHeap(root->left);		//���� ��Ʈ���� �� ��Ʈ���� �� ����
		rBuildHeap(root->right);	//���� ��Ʈ���� �� ��Ʈ���� �� ����
		downHeap(root);				//���� ��Ʈ���� ��Ʈ�� �¿� ��Ʈ���� ��ģ �� ����
	}
}


int main() {
	int n, input;
	Queue* queue;
	Node* root;

	queue = (Queue*)malloc(sizeof(Queue));
	queue->front = NULL;
	queue->rear = NULL;
	root = NULL;

	scanf("%d", &n);	//Ű ���� �Է�
	for (int i = 0; i < n; i++) {
		scanf("%d", &input);
		insertNode(queue, &root, input);
	}
	rBuildHeap(root);
	printHeap(root);
}