#include<stdio.h>
#include<stdlib.h>

//이진탐색트리 구현
//삽입(i) : 입력 키에 대한 노드 생성 및 트리 삽입
//삭제(d) : 입력 키가 트리에 존재하면 해당 노드 삭제 후 삭제된 키 출력 없으면 X 출력
//탐색(s) : 입력 키가 트리에 존재하면 해당 키를 출력 없으면 X 출력
//인쇄(p) : 현재 트리를 전위순회로 인쇄
//종료(q)
//중복 키 없는 것으로 전제

typedef struct Node {
	int key;
	struct Node* parent;
	struct Node* lChild;
	struct Node* rChild;
} Node;

int isExternal(Node* node); //노드의 외부노드 여부 반환
int isInternal(Node* node); //노드의 내부노드 여부 반환
Node* sibling(Node* node);
Node* inOrderSucc(Node* node); //노드의 중위순회 후계자를 반환
Node* reduceExternal(Node** rootNode, Node* node);
Node* treeSearch(Node* node, int key);	//현재 트리에서 키를 저장한 노드 반환	, 없으면 만약 있었다면 위치할 외부 노드 반환
void insertItem(Node* node, int key);	//현재 트리에 키를 저장한 노드 삽입
int removeElement(Node** node, int key);	//현재 트리에서 키를 저장한 노드를 삭제 후 키 반환
void preorderPrintTree(Node* node);	//전위순회 인쇄


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
	else return treeSearch(w->rChild, k);	//k > w->key 인 경우
}

void insertItem(Node* root, int k) {
	Node* w = treeSearch(root, k);
	Node* l = (Node*)malloc(sizeof(Node));
	Node* r = (Node*)malloc(sizeof(Node));

	l->lChild = l->rChild = r->lChild = r->rChild = NULL;

	if (isInternal(w)) return;	//이미 있는 키
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