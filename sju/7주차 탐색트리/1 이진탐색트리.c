#include<stdio.h>
#include<stdlib.h>

//����Ž��Ʈ�� ����
//����(i) : �Է� Ű�� ���� ��� ���� �� Ʈ�� ����
//����(d) : �Է� Ű�� Ʈ���� �����ϸ� �ش� ��� ���� �� ������ Ű ��� ������ X ���
//Ž��(s) : �Է� Ű�� Ʈ���� �����ϸ� �ش� Ű�� ��� ������ X ���
//�μ�(p) : ���� Ʈ���� ������ȸ�� �μ�
//����(q)
//�ߺ� Ű ���� ������ ����

typedef struct Node {
	int key;
	struct Node* parent;
	struct Node* lChild;
	struct Node* rChild;
} Node;

int isExternal(Node* node); //����� �ܺγ�� ���� ��ȯ
int isInternal(Node* node); //����� ���γ�� ���� ��ȯ
Node* sibling(Node* node);
Node* inOrderSucc(Node* node); //����� ������ȸ �İ��ڸ� ��ȯ
Node* reduceExternal(Node** rootNode, Node* node);
Node* treeSearch(Node* node, int key);	//���� Ʈ������ Ű�� ������ ��� ��ȯ	, ������ ���� �־��ٸ� ��ġ�� �ܺ� ��� ��ȯ
void insertItem(Node* node, int key);	//���� Ʈ���� Ű�� ������ ��� ����
int removeElement(Node** node, int key);	//���� Ʈ������ Ű�� ������ ��带 ���� �� Ű ��ȯ
void preorderPrintTree(Node* node);	//������ȸ �μ�


int main() {
	int key, result = 0;
	Node* node = (Node*)malloc(sizeof(Node));
	node->key = 0;
	node->parent = NULL;
	node->lChild = NULL;
	node->rChild = NULL;

	while (1) {
		switch (getchar()) {
		case 'i':
			scanf("%d", &key);
			insertItem(node, key);
			break;
		case 'd':
			scanf("%d", &key);
			result = removeElement(&node, key);
			if (!result) printf("X\n");
			else printf("%d\n", result);
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
	if (w->lChild == NULL && w->rChild == NULL) return 1;
	else return 0;
}

int isInternal(Node* w) {
	if (w->lChild != NULL || w->rChild != NULL) return 1;
	else return 0;
}

Node* sibling(Node* w) {
	if (w->parent == NULL) return NULL;

	if (w->parent->lChild == w) return w->parent->rChild;
	else return w->parent->lChild;
}

Node* inOrderSucc(Node* w) {
	w = w->rChild;
	if (isExternal(w)) return NULL;
	while (isInternal(w->lChild)) w = w->lChild;
	return w;
}

Node* reduceExternal(Node** root, Node* z) {
	Node* w, * zs, * g;
	w = z->parent;
	zs = sibling(z);

	if (w->parent == NULL) {
		*root = zs;
		zs->parent = NULL;
	}

	else {
		g = w->parent;
		zs->parent = g;
		if (w == g->lChild) g->lChild = zs;
		else g->rChild = zs;
	}

	free(z);
	free(w);
	return zs;
}

Node* treeSearch(Node* w, int k) {
	if (isExternal(w)) return w;

	if (w->key == k) return w;
	else if (k < w->key) return treeSearch(w->lChild, k);
	else return treeSearch(w->rChild, k);	//k > w->key �� ���
}

void insertItem(Node* root, int k) {
	Node* w = treeSearch(root, k);
	Node* l = (Node*)malloc(sizeof(Node));
	Node* r = (Node*)malloc(sizeof(Node));

	l->lChild = l->rChild = r->lChild = r->rChild = NULL;

	if (isInternal(w)) return;	//�̹� �ִ� Ű
	else {
		l->parent = w;
		r->parent = w;
		w->lChild = l;
		w->rChild = r;
		w->key = k;
	}
}

int removeElement(Node** root, int k) {
	Node* w = treeSearch(*root, k);
	Node* z = w->lChild;
	Node* y;
	int e = w->key;

	if (isExternal(w)) return 0;

	if (!isExternal(z)) z = w->rChild;
	if (isExternal(z)) reduceExternal(root, z);
	else {
		y = inOrderSucc(w);
		z = y->lChild;
		w->key = y->key;
		reduceExternal(root, z);
	}

	return e;
}

void preorderPrintTree(Node* w) {
	if (isExternal(w)) return;
	else {
		printf(" %d", w->key);
		preorderPrintTree(w->lChild);
		preorderPrintTree(w->rChild);
	}
}