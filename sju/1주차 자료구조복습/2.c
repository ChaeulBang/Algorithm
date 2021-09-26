#include<stdio.h>
#include<stdlib.h>

typedef struct Node {	//이진연결트리를 위한 노드 정의
	int data;			//노드 번호
	struct Node* left;	//왼쪽 자식 링크
	struct Node* right;	//오른쪽 자식 링크
} Node;

void processRoot(Node* root);
void processInput(Node* root);
Node* findNode(Node* root, int data);
void searchNode(Node* root);


int main() {
	int i, n, s;
	Node* root;

	root = (Node*)malloc(sizeof(Node));

	scanf("%d", &n);	//노드 개수
	processRoot(root);

	for (i = 0; i < n - 1; i++) processInput(root);

	scanf("%d", &s);	//탐색 횟수

	for (i = 0; i < s; i++) {
		searchNode(root);
		printf("\n");
	}
}

void processRoot(Node* root) {	//루트 노드의 데이터 입력
	int data, left, right;

	scanf("%d %d %d", &data, &left, &right);
	root->data = data;	//노드 번호 입력

	if (left != 0) {								//값이 0이 아닐때
		root->left = (Node*)malloc(sizeof(Node));	//메모리 할당
		root->left->data = left;					//노드 번호 입력
	}
	if (right != 0) {
		root->right = (Node*)malloc(sizeof(Node));
		root->right->data = right;
	}
}

void processInput(Node* root) {	//루트 노드를 제외한 나머지 노드의 데이터 입력
	int data, left, right;
	Node* node;

	scanf("%d %d %d", &data, &left, &right);
	node = findNode(root, data); //트리를 탐색하여 노드 번호가 data인 노드 반환

	if (left != 0) {
		node->left = (Node*)malloc(sizeof(Node));
		node->left->data = left;
	}
	else node->left = NULL;	//입력값이 0일 때 = 노드를 생성하지 않을 때 트리 검색을 위해 포인터에 NULL 대입

	if (right != 0) {
		node->right = (Node*)malloc(sizeof(Node));
		node->right->data = right;
	}
	else node->right = NULL;
}

Node* findNode(Node* root, int data) {	//노드 번호가 data인 노드 반환
	//선위순회 root-left-right
	Node* left;
	Node* right;

	if (root != NULL) {
		if (root->data == data) return root;	//노드 찾음

		left = findNode(root->left, data);		//없을 경우 루트 기준 왼쪽 탐색
		if (left != NULL) return left;

		right = findNode(root->right, data);	//왼쪽에도 없을 경우 루트 기준 오른쪽 탐색
		if (right != NULL) return right;
	}

	return NULL; //현재 노드를 루트로 하는 서브트리에서 찾는 노드가 없을 경우
}

void searchNode(Node* root) {	//노드 탐색 후 출력
	int index = 0;
	char search[101];
	Node* cur = root;			//현재 탐색 노드

	scanf("%s", search);
	printf(" %d", cur->data);	//루트 노드의 번호 출력

	while (search[index] != '\0') {
		if (search[index] == 'L') {
			cur = cur->left;	//루트의 왼쪽으로 이동
			printf(" %d", cur->data);
		}
		else {
			cur = cur->right;
			printf(" %d", cur->data);
		}

		index++;				//문자열의 다음 문자로 이동
	}
}