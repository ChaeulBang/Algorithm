#include<stdio.h>
#include<stdlib.h>

typedef struct Node {	//자식 노드를 가리키는 포인터와 큐를 구현하기 위해 사용하는 노드
	int data;
	struct Node* left;	//왼쪽 자식
	struct Node* right;	//오른쪽 자식
	struct Node* link;
} Node;

typedef struct {	//큐에 접근하기 위한 포인터
	Node* front;
	Node* rear;
} Queue;

void enQueue(Queue* queue, Node* node) {	//트리의 노드를 큐에 저장
	if (!queue->front) {
		queue->front = node;
		queue->rear = node;
	}
	else {
		queue->rear->link = node;
		queue->rear = node;
	}
}

Node* deQueue(Queue* queue) {	//가장 앞의 트리 노드를 큐에서 제거 후 반환
	Node* temp;

	if (!queue->front) return NULL;

	temp = queue->front;
	queue->front = queue->front->link;

	return temp;
}

Node* peek(Queue* queue) {	//큐의 가장 앞의 트리 노드를 반환
	if (!queue->front) return NULL;
	return queue->front;
}

void insertNode(Queue* queue, Node** root, int data) {	//노드 삽입
	Node* newNode = (Node*)malloc(sizeof(Node));
	newNode->data = data;
	newNode->left = NULL;
	newNode->right = NULL;
	newNode->link = NULL;

	//큐가 비어있을 경우
	if (!queue->front) {
		*root = newNode;
	}

	//큐의 첫번째 요소인 트리의 노드가 가득 찼을 경우 (가장 앞의 노드의 자식 노드가 둘 다 채워져 있는지를 확인)
	else if (peek(queue)->right != NULL) {	//오른쪽 자식까지 채워져 있을 경우
		deQueue(queue);	//큐에서 제거
		peek(queue)->left = newNode;	//왼쪽에 노드 삽입
	}
	else if (peek(queue)->left != NULL) {	//왼쪽 자식만 채워져 있을 경우
		peek(queue)->right = newNode;	//오른쪽에 노드 삽입
	}
	else {
		peek(queue)->left = newNode;
	}
	enQueue(queue, newNode);
}

void downHeap(Node* node) {	//키를 크기에 맞는 위치로 하향 이동
	Node* max;
	int temp;

	if (node->left != NULL) {							//왼쪽 자식 노드 존재
		max = node->left;
		if (node->right != NULL)						//오른쪽 자식 노드 존재
			if (node->right->data > node->left->data)	//자식 노드 중 더 큰 키 값 저장
				max = node->right;
		if (node->data < max->data) {					//부모와 자식 비교 후 값 교환 (트리의 구조는 변하지 않으므로 값만 변경)
			temp = node->data;
			node->data = max->data;
			max->data = temp;
			downHeap(max);								//재귀호출
		}
	}
}

void printHeap(Node* root) {	//힙에 저장된 키들을 레벨 순서로 인쇄
	Queue* queue;	//탐색을 위한 큐
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

void rBuildHeap(Node* root) {		//재귀 방식으로 상향식 힙 생성
	if (root) {						//유효한 트리일 경우
		rBuildHeap(root->left);		//현재 부트리의 좌 부트리를 힙 생성
		rBuildHeap(root->right);	//현재 부트리의 우 부트리를 힙 생성
		downHeap(root);				//현재 부트리의 루트와 좌우 부트리를 합친 힙 생성
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

	scanf("%d", &n);	//키 개수 입력
	for (int i = 0; i < n; i++) {
		scanf("%d", &input);
		insertNode(queue, &root, input);
	}
	rBuildHeap(root);
	printHeap(root);
}