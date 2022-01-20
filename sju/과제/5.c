#include<stdio.h>
#include<stdlib.h>

//무방향그래프 - 인접리스트로 구현
//트리(싸이클 없고 모든 정점 연결) 검사 - DFS BFS 활용
//자유 트리 O - 중심과 이심율 출력
//자유 트리 X - 연결 요소 개수 출력

int edge[100];	//각 정점에 대한 간선 개수
int visited[100];	//DFS방문 체크

typedef struct Node {	//정점을 담을 노드 구조체
	int node;
	struct Node* next;
}Node;

void addEdge(Node* prev, int node) {	//정점에 간선을 인접리스트로 추가
	Node* newNode = (Node*)malloc(sizeof(Node));
	newNode->node = node;
	newNode->next = prev->next;
	prev->next = newNode;
}

void DFS(Node** head, int now) {	//DFS로 정점 방문
	visited[now] = 1;	//정점 방문 했음을 표시
	Node* curr = head[now]->next;
	while (curr != NULL) {
		if (visited[curr->node] == 0)	//방문 안 한 정점은
			DFS(head, curr->node);	//DFS 재귀호출
		curr = curr->next;	//다음 정점으로 이동
	}
}
int isTree(Node** head, int n, int m) {	//트리(싸이클 없고 모든 정점 연결) 검사
	int cnt = 0;	//연결요소 개수
	for (int i = 1; i <= n; i++) {
		if (visited[i] == 0) {	//방문 안 한 노드
			DFS(head, i);	//모든 노드 방문
			cnt++;	//연결요소 = 모든 노드를 순회한 게 몇 번 이루어졌는지 세기
		}
	}
	if (n - 1 == m && cnt == 1)	return 0;	//트리는 간선 개수가 (정점 - 1)개이고 모든 노드 순회를 총 1회 함

	return cnt;	//연결요소 개수 반환
}
void removeLeaves(int* cnt, Node** head, int n) {	//간선의 개수가 1개인 정점(잎)을 삭제
	int temp[100] = { 0, };	//간선의 개수가 1개인 정점을 저장할 임시 배열
	for (int i = 1; i <= n; i++) {
		if (edge[i] == 1) temp[i] = 1;	//간선의 개수가 1개인 정점을 임시 배열에 저장(표시)
	}

	for (int i = 1; i <= n; i++) {
		if (temp[i] == 1) {	//간선의 개수가 1개라면
			edge[i] = 0;	//간선 개수 감소
			cnt[i] = 1;	//트리에서 삭제(표시)
			Node* curr = head[i]->next;
			while (curr != NULL) {
				if (edge[curr->node] > 0)	//연결되어 있는 정점의 간선 개수 감소
					edge[curr->node]--;
				curr = curr->next;
			}
		}
	}
}

int main() {
	int n, m, v1, v2;
	scanf("%d %d", &n, &m);	//정점n개 간선m개
	Node** head = (Node**)malloc(sizeof(Node) * (n + 1));	//할당

	for (int i = 1; i <= n; i++) {	//초기화
		head[i] = (Node*)malloc(sizeof(Node));
		head[i]->next = NULL;
	}

	for (int i = 0; i < m; i++) {	//간선 추가
		scanf("%d %d", &v1, &v2);
		addEdge(head[v1], v2);
		addEdge(head[v2], v1);
		edge[v1]++;	//정점에 붙은 간선 개수 증가
		edge[v2]++;
	}

	if (!isTree(head, n, m)) {	//트리 O
		int ans = 0;	//잎 삭제 횟수(이심율)
		int cnt[100] = { 0, };	//현재 트리에 남아있는 정점을 위한 임시 배열
		int mid = 0;	//중심 개수

		while (1) {
			int flag = 0;	//현재 트리에 남아있는 정점 개수

			for (int i = 1; i <= n; i++) {
				if (cnt[i] == 0) flag++;	//현재 트리에 남아있는 정점은 cnt가 0으로 표시되어 있음
			}

			if (flag <= 2) break;	//현재 트리에 남아있는 정점 개수가 2 이하라면 반복문 종료

			removeLeaves(cnt, head, n);	//잎 삭제
			ans++;	//이심율을 위해 잎 삭제가 몇 번 이루어졌는지 셈
		}

		for (int i = 1; i <= n; i++) {
			if (cnt[i] == 0) {	//현재 트리에 남아있는 정점이라면 = 중심
				printf("%d ", i);	//출력
				mid++;	//중심 개수 증가
			}
		}
		printf("\n%d", (mid == 1 ? ans : ans + 1));	//중심이 두 개라면 이심율 + 1 출력
	}

	else {	//트리 X
		for (int i = 1; i <= n; i++) visited[i] = 0;	//visited 배열 초기화 - 트리 검사에 사용
		printf("%d", isTree(head, n, m));	//연결요소 개수 출력
	}
}