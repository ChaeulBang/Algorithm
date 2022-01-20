#include<stdio.h>
#include<stdlib.h>

//AVL Ʈ�� ����
//����(i) : �Է� Ű�� ���� ��� ���� �� Ʈ�� ����
//Ž��(s) : �Է� Ű�� Ʈ���� �����ϸ� �ش� Ű�� ��� ������ X ���
//�μ�(p) : ���� Ʈ���� ������ȸ�� �μ�
//����(q)
//�ߺ� Ű ���� ������ ����

typedef struct Node {
	int key;
	int height;	//����
	struct Node* parent;
	struct Node* lChild;
	struct Node* rChild;
} Node;

int isExternal(Node* node);					//����� �ܺγ�� ���� ��ȯ
int isInternal(Node* node);					//����� ���γ�� ���� ��ȯ
Node* sibling(Node* node);					//����� ������� ��ȯ
Node* inOrderSucc(Node* node);				//����� ������ȸ �İ��ڸ� ��ȯ
Node* treeSearch(Node* node, int key);		//���� Ʈ������ Ű�� ������ ��� ��ȯ	, ������ ���� �־��ٸ� ��ġ�� �ܺ� ��� ��ȯ
void preorderPrintTree(Node* node);			//������ȸ �μ�

void insertItem(Node** node, int key);		//���� Ʈ���� Ű�� ������ ��� ����
void expandExternal(Node* node);			//�ܺ� ���� Ȯ��
void searchAndFixAfterInsertion(Node** root, Node* node);	//�����˻縦 �����ϰ� �ұ����� ������ ������ ���� ���̱��� �Ӽ� ȸ��
int updateHeight(Node* node);								//����� ���̸� (�ʿ��ϸ�) ���� �� ���� ���θ� ��ȯ
int isBalanced(Node* node);									//����� ���� ���� ���θ� ��ȯ
void restructure(Node** root, Node* x, Node* y, Node* z);	//3-��� ����
void freeAll(Node* node);									//���� �Ҵ� �޸� ����


int main() {
	int key, result = 0;
	Node* node = (Node*)malloc(sizeof(Node));	//��Ʈ ���
	node->key = 0;
	node->height = 0;
	node->parent = NULL;
	node->lChild = NULL;
	node->rChild = NULL;

	while (1) {
		switch (getchar()) {
		case 'i':
			scanf("%d", &key);
			insertItem(&node, key);
			break;
		case 's':
			scanf("%d", &key);
			if (treeSearch(node, key)->key != key) printf("X\n");
			else printf("%d\n", treeSearch(node, key)->key);
			break;
		case 'p':
			preorderPrintTree(node);
			printf("\n");
			break;
		case 'q':
			goto QUIT;
		}
	}
QUIT:
	return 0;
}


int isExternal(Node* w) {	
	if (w->lChild == NULL && w->rChild == NULL) return 1;	//�� �ڽ� ��尡 ��� NULL�� ��� �ܺγ��
	else return 0;
}

int isInternal(Node* w) {
	if (!isExternal(w)) return 1;
	else return 0;
}

Node* sibling(Node* w) {
	if (w->parent == NULL) return NULL;	//��Ʈ ����� ���

	if (w->parent->lChild == w) return w->parent->rChild;	//������ �θ��� ���� �ڽ��� ��� ������ �ڽ��� ��ȯ
	else return w->parent->lChild;	//�θ��� ������ �ڽ��� ��� ���� �ڽ��� ��ȯ
}

Node* inOrderSucc(Node* w) {
	w = w->rChild;	//������ �ڽ����� �̵� ��
	if (isExternal(w)) return NULL;
	while (isInternal(w->lChild)) w = w->lChild;	//���� �ڽ� ������ ������
	return w;
}

Node* treeSearch(Node* w, int k) {
	if (isExternal(w)) return w;

	if (w->key == k) return w;
	else if (k < w->key) return treeSearch(w->lChild, k);
	else return treeSearch(w->rChild, k);	//k > w->key �� ���
}

void preorderPrintTree(Node* w) {	//����->�����ڽ�->�������ڽ�
	if (isExternal(w)) return;
	else {
		printf(" %d", w->key);
		preorderPrintTree(w->lChild);
		preorderPrintTree(w->rChild);
	}
}


void insertItem(Node** root, int k) {
	Node* w = treeSearch(*root, k);	//���� Ʈ������ Ű ���� ã��
	if (isInternal(w)) return;	//�̹� �ִ� Ű��� ����
	else {	//�̹� �ִ� Ű�� �ƴ϶��
		w->key = k;
		expandExternal(w);	//�ܺ� ���� Ȯ���ϰ�
		searchAndFixAfterInsertion(root, w);	//���� ���� �Ӽ� ȸ�� �۾�
	}
}

void expandExternal(Node* w) {
	Node* l = (Node*)malloc(sizeof(Node));	//���� �ڽ�
	Node* r = (Node*)malloc(sizeof(Node));	//������ �ڽ�

	l->lChild = l->rChild = r->lChild = r->rChild = NULL;	//�ʱ�ȭ �� ���� ����
	l->parent = r->parent = w;
	l->height = r->height = 0;
	w->lChild = l;
	w->rChild = r;
	w->height = 1;
}

void searchAndFixAfterInsertion(Node** root, Node* w) {
	Node* x, * y, * z;

	if (w->parent == NULL) return;	//w�� ��Ʈ ����� ��� ����
	z = w->parent;	//w�� ��Ʈ ��尡 �ƴ� ��� z�� w�� �θ�� ����	
	updateHeight(z);	//���� ���� �Ӽ� ������Ʈ

	while (isBalanced(z)) {	//���� ���� �Ӽ��� ���� ������ �ݺ�
		if (z->parent == NULL) return;	//��Ʈ���� �Ž��� �ö�
		z = z->parent;
		updateHeight(z);
	}

	y = (z->lChild->height > z->rChild->height) ? z->lChild : z->rChild; //y�� z�� ���� �ڽ�
	x = (y->lChild->height > y->rChild->height) ? y->lChild : y->rChild;

	restructure(root, x, y, z);
}

int updateHeight(Node* w) {
	int h = 0;

	if (w->lChild->height > w->rChild->height) h = w->lChild->height + 1;	//�� ���� ���� ���̿� 1�� ������
	else if (w->lChild->height <= w->rChild->height) h = w->rChild->height + 1;
	if (h != w->height) {	//���� �� ���̰� ���� ���̿� �ٸ��ٸ�
		w->height = h;	//���̸� ����
		return 1;
	}
	else return 0;
}

int isBalanced(Node* w) {
	int dif = w->lChild->height - w->rChild->height;
	if ((dif >= -1 && dif <= 1)) return 1;	//���� �ڽ��� ���̿� ������ �ڽ��� ���̰� 0�̰ų� 1�̾�� ��
	else return 0;
}

void restructure(Node** root, Node* x, Node* y, Node* z) {
	Node* a, * b, * c;	//3���� ���� ��� x, y(x�� �θ�), z(y�� �θ�)�� ������ȸ ���� a < b < c
	Node* T0, * T1, * T2, * T3;	//��Ʈ�� ������ȸ ����

	a = b = c = T0 = T1 = T2 = T3 = NULL;

	if ((z->key < y->key) && (y->key < x->key)) {	//z<y<x ����ȸ��
		a = z;
		b = y;
		c = x;
		T0 = a->lChild;
		T1 = b->lChild;
		T2 = c->lChild;
		T3 = c->rChild;
	}

	else if ((x->key < y->key) && (y->key < z->key)) {	//x<y<z ����ȸ��
		a = x;
		b = y;
		c = z;
		T0 = a->lChild;
		T1 = a->rChild;
		T2 = b->rChild;
		T3 = c->rChild;
	}

	else if ((z->key < x->key) && (x->key < y->key)) {	//z<x<y ����ȸ��
		a = z;
		b = x;
		c = y;
		T0 = a->lChild;
		T1 = b->lChild;
		T2 = b->rChild;
		T3 = c->rChild;
	}

	else if ((y->key < x->key) && (x->key < z->key)) {	//y<x<z ����ȸ��
		a = y;
		b = x;
		c = z;
		T0 = a->lChild;
		T1 = b->lChild;
		T2 = b->rChild;
		T3 = c->rChild;
	}

	//z�� ��Ʈ�� �ϴ� ��Ʈ���� b�� ��Ʈ�� �ϴ� ��Ʈ���� ��ü
	if (z->parent == NULL) {	//z�� �θ� ��Ʈ���� ���
		*root = b;				//b�� ��Ʈ�� ��ü
		b->parent = NULL;
	}
	else if (z->parent->lChild == z) {	//z�� ���� �ڽ��̾��� ���
		z->parent->lChild = b;
		b->parent = z->parent;
	}
	else if (z->parent->rChild == z) {	//z�� ������ �ڽ��̾��� ���
		z->parent->rChild = b;
		b->parent = z->parent;
	}

	//T0�� T1�� ���� a�� ���� �� ������ ��Ʈ���� ����
	a->lChild = T0;
	a->rChild = T1;
	T0->parent = a;
	T1->parent = a;
	updateHeight(a);

	//T2�� T3�� ���� c�� ���� �� ������ ��Ʈ���� ����
	c->lChild = T2;	
	c->rChild = T3;
	T2->parent = c;
	T3->parent = c;
	updateHeight(c);

	//a�� c�� ���� b�� ���� �� ������ �ڽ����� ����
	b->lChild = a;
	b->rChild = c;
	a->parent = b;
	c->parent = b;
	updateHeight(b);
}

void freeAll(Node* w) {
	if (isExternal(w)) return;
	else {
		freeAll(w->lChild);
		freeAll(w->rChild);
		free(w);
	}
}