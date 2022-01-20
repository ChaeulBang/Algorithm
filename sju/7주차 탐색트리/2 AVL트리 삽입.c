#include<stdio.h>
#include<stdlib.h>

//AVL 트리 생성
//삽입(i) : 입력 키에 대한 노드 생성 및 트리 삽입
//탐색(s) : 입력 키가 트리에 존재하면 해당 키를 출력 없으면 X 출력
//인쇄(p) : 현재 트리를 전위순회로 인쇄
//종료(q)
//중복 키 없는 것으로 전제

typedef struct Node {
	int key;
	int height;	//높이
	struct Node* parent;
	struct Node* lChild;
	struct Node* rChild;
} Node;

int isExternal(Node* node);					//노드의 외부노드 여부 반환
int isInternal(Node* node);					//노드의 내부노드 여부 반환
Node* sibling(Node* node);					//노드의 형제노드 반환
Node* inOrderSucc(Node* node);				//노드의 중위순회 후계자를 반환
Node* treeSearch(Node* node, int key);		//현재 트리에서 키를 저장한 노드 반환	, 없으면 만약 있었다면 위치할 외부 노드 반환
void preorderPrintTree(Node* node);			//전위순회 인쇄

void insertItem(Node** node, int key);		//현재 트리에 키를 저장한 노드 삽입
void expandExternal(Node* node);			//외부 노드로 확장
void searchAndFixAfterInsertion(Node** root, Node* node);	//균형검사를 수행하고 불균형이 있으면 개조를 통해 높이균형 속성 회복
int updateHeight(Node* node);								//노드의 높이를 (필요하면) 갱신 후 갱신 여부를 반환
int isBalanced(Node* node);									//노드의 높이 균형 여부를 반환
void restructure(Node** root, Node* x, Node* y, Node* z);	//3-노드 개조
void freeAll(Node* node);									//동적 할당 메모리 해제


int main() {
	int key, result = 0;
	Node* node = (Node*)malloc(sizeof(Node));	//루트 노드
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
	if (w->lChild == NULL && w->rChild == NULL) return 1;	//두 자식 노드가 모두 NULL일 경우 외부노드
	else return 0;
}

int isInternal(Node* w) {
	if (!isExternal(w)) return 1;
	else return 0;
}

Node* sibling(Node* w) {
	if (w->parent == NULL) return NULL;	//루트 노드일 경우

	if (w->parent->lChild == w) return w->parent->rChild;	//본인이 부모의 왼쪽 자식일 경우 오른쪽 자식을 반환
	else return w->parent->lChild;	//부모의 오른쪽 자식일 경우 왼쪽 자식을 반환
}

Node* inOrderSucc(Node* w) {
	w = w->rChild;	//오른쪽 자식으로 이동 후
	if (isExternal(w)) return NULL;
	while (isInternal(w->lChild)) w = w->lChild;	//왼쪽 자식 끝까지 내려감
	return w;
}

Node* treeSearch(Node* w, int k) {
	if (isExternal(w)) return w;

	if (w->key == k) return w;
	else if (k < w->key) return treeSearch(w->lChild, k);
	else return treeSearch(w->rChild, k);	//k > w->key 인 경우
}

void preorderPrintTree(Node* w) {	//본인->왼쪽자식->오른쪽자식
	if (isExternal(w)) return;
	else {
		printf(" %d", w->key);
		preorderPrintTree(w->lChild);
		preorderPrintTree(w->rChild);
	}
}


void insertItem(Node** root, int k) {
	Node* w = treeSearch(*root, k);	//현재 트리에서 키 값을 찾음
	if (isInternal(w)) return;	//이미 있는 키라면 종료
	else {	//이미 있는 키가 아니라면
		w->key = k;
		expandExternal(w);	//외부 노드로 확장하고
		searchAndFixAfterInsertion(root, w);	//높이 균형 속성 회복 작업
	}
}

void expandExternal(Node* w) {
	Node* l = (Node*)malloc(sizeof(Node));	//왼쪽 자식
	Node* r = (Node*)malloc(sizeof(Node));	//오른쪽 자식

	l->lChild = l->rChild = r->lChild = r->rChild = NULL;	//초기화 후 노드와 연결
	l->parent = r->parent = w;
	l->height = r->height = 0;
	w->lChild = l;
	w->rChild = r;
	w->height = 1;
}

void searchAndFixAfterInsertion(Node** root, Node* w) {
	Node* x, * y, * z;

	if (w->parent == NULL) return;	//w가 루트 노드일 경우 종료
	z = w->parent;	//w가 루트 노드가 아닐 경우 z를 w의 부모로 설정	
	updateHeight(z);	//높이 균형 속성 업데이트

	while (isBalanced(z)) {	//높이 균형 속성이 깨질 때까지 반복
		if (z->parent == NULL) return;	//루트까지 거슬러 올라감
		z = z->parent;
		updateHeight(z);
	}

	y = (z->lChild->height > z->rChild->height) ? z->lChild : z->rChild; //y는 z의 높은 자식
	x = (y->lChild->height > y->rChild->height) ? y->lChild : y->rChild;

	restructure(root, x, y, z);
}

int updateHeight(Node* w) {
	int h = 0;

	if (w->lChild->height > w->rChild->height) h = w->lChild->height + 1;	//더 높은 쪽의 높이에 1을 더해줌
	else if (w->lChild->height <= w->rChild->height) h = w->rChild->height + 1;
	if (h != w->height) {	//변경 후 높이가 현재 높이와 다르다면
		w->height = h;	//높이를 변경
		return 1;
	}
	else return 0;
}

int isBalanced(Node* w) {
	int dif = w->lChild->height - w->rChild->height;
	if ((dif >= -1 && dif <= 1)) return 1;	//왼쪽 자식의 높이와 오른쪽 자식의 높이가 0이거나 1이어야 함
	else return 0;
}

void restructure(Node** root, Node* x, Node* y, Node* z) {
	Node* a, * b, * c;	//3대의 직계 노드 x, y(x의 부모), z(y의 부모)의 중위순회 순서 a < b < c
	Node* T0, * T1, * T2, * T3;	//부트리 중위순회 순서

	a = b = c = T0 = T1 = T2 = T3 = NULL;

	if ((z->key < y->key) && (y->key < x->key)) {	//z<y<x 단일회전
		a = z;
		b = y;
		c = x;
		T0 = a->lChild;
		T1 = b->lChild;
		T2 = c->lChild;
		T3 = c->rChild;
	}

	else if ((x->key < y->key) && (y->key < z->key)) {	//x<y<z 단일회전
		a = x;
		b = y;
		c = z;
		T0 = a->lChild;
		T1 = a->rChild;
		T2 = b->rChild;
		T3 = c->rChild;
	}

	else if ((z->key < x->key) && (x->key < y->key)) {	//z<x<y 이중회전
		a = z;
		b = x;
		c = y;
		T0 = a->lChild;
		T1 = b->lChild;
		T2 = b->rChild;
		T3 = c->rChild;
	}

	else if ((y->key < x->key) && (x->key < z->key)) {	//y<x<z 이중회전
		a = y;
		b = x;
		c = z;
		T0 = a->lChild;
		T1 = b->lChild;
		T2 = b->rChild;
		T3 = c->rChild;
	}

	//z를 루트로 하는 부트리를 b를 루트로 하는 부트리로 대체
	if (z->parent == NULL) {	//z의 부모가 루트였을 경우
		*root = b;				//b를 루트로 대체
		b->parent = NULL;
	}
	else if (z->parent->lChild == z) {	//z가 왼쪽 자식이었을 경우
		z->parent->lChild = b;
		b->parent = z->parent;
	}
	else if (z->parent->rChild == z) {	//z가 오른쪽 자식이었을 경우
		z->parent->rChild = b;
		b->parent = z->parent;
	}

	//T0와 T1을 각각 a의 왼쪽 및 오른쪽 부트리로 만듦
	a->lChild = T0;
	a->rChild = T1;
	T0->parent = a;
	T1->parent = a;
	updateHeight(a);

	//T2와 T3를 각각 c의 왼쪽 및 오른쪽 부트리로 만듦
	c->lChild = T2;	
	c->rChild = T3;
	T2->parent = c;
	T3->parent = c;
	updateHeight(c);

	//a와 c를 각각 b의 왼쪽 및 오른쪽 자식으로 만듦
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