#include<stdio.h>
#include<stdlib.h>

typedef struct Node {	//��������Ʈ���� ���� ��� ����
	int data;			//��� ��ȣ
	struct Node* left;	//���� �ڽ� ��ũ
	struct Node* right;	//������ �ڽ� ��ũ
} Node;

void processRoot(Node* root);
void processInput(Node* root);
Node* findNode(Node* root, int data);
void searchNode(Node* root);


int main() {
	int i, n, s;
	Node* root;

	root = (Node*)malloc(sizeof(Node));

	scanf("%d", &n);	//��� ����
	processRoot(root);

	for (i = 0; i < n - 1; i++) processInput(root);

	scanf("%d", &s);	//Ž�� Ƚ��

	for (i = 0; i < s; i++) {
		searchNode(root);
		printf("\n");
	}
}

void processRoot(Node* root) {	//��Ʈ ����� ������ �Է�
	int data, left, right;

	scanf("%d %d %d", &data, &left, &right);
	root->data = data;	//��� ��ȣ �Է�

	if (left != 0) {								//���� 0�� �ƴҶ�
		root->left = (Node*)malloc(sizeof(Node));	//�޸� �Ҵ�
		root->left->data = left;					//��� ��ȣ �Է�
	}
	if (right != 0) {
		root->right = (Node*)malloc(sizeof(Node));
		root->right->data = right;
	}
}

void processInput(Node* root) {	//��Ʈ ��带 ������ ������ ����� ������ �Է�
	int data, left, right;
	Node* node;

	scanf("%d %d %d", &data, &left, &right);
	node = findNode(root, data); //Ʈ���� Ž���Ͽ� ��� ��ȣ�� data�� ��� ��ȯ

	if (left != 0) {
		node->left = (Node*)malloc(sizeof(Node));
		node->left->data = left;
	}
	else node->left = NULL;	//�Է°��� 0�� �� = ��带 �������� ���� �� Ʈ�� �˻��� ���� �����Ϳ� NULL ����

	if (right != 0) {
		node->right = (Node*)malloc(sizeof(Node));
		node->right->data = right;
	}
	else node->right = NULL;
}

Node* findNode(Node* root, int data) {	//��� ��ȣ�� data�� ��� ��ȯ
	//������ȸ root-left-right
	Node* left;
	Node* right;

	if (root != NULL) {
		if (root->data == data) return root;	//��� ã��

		left = findNode(root->left, data);		//���� ��� ��Ʈ ���� ���� Ž��
		if (left != NULL) return left;

		right = findNode(root->right, data);	//���ʿ��� ���� ��� ��Ʈ ���� ������ Ž��
		if (right != NULL) return right;
	}

	return NULL; //���� ��带 ��Ʈ�� �ϴ� ����Ʈ������ ã�� ��尡 ���� ���
}

void searchNode(Node* root) {	//��� Ž�� �� ���
	int index = 0;
	char search[101];
	Node* cur = root;			//���� Ž�� ���

	scanf("%s", search);
	printf(" %d", cur->data);	//��Ʈ ����� ��ȣ ���

	while (search[index] != '\0') {
		if (search[index] == 'L') {
			cur = cur->left;	//��Ʈ�� �������� �̵�
			printf(" %d", cur->data);
		}
		else {
			cur = cur->right;
			printf(" %d", cur->data);
		}

		index++;				//���ڿ��� ���� ���ڷ� �̵�
	}
}