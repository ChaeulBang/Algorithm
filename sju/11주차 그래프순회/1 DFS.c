#include<stdio.h>
#include<stdlib.h>
#define MAX_VERTEX 100
#define MAX_EDGE 1000

//DFS
//인접리스트

typedef struct Edge {
	int endpoint1;
	int endpoint2;
	int eLabel;	//Fresh = 1, Tree = 2, Back = 3
} Edge;

typedef struct EdgeNode {
	int idx;
	Edge* edge;
	struct EdgeNode* link;
} EdgeNode;

typedef struct Vertex {
	EdgeNode* edges;	//헤더 노드
	int vLabel;	//Fresh = 1, Visited = 0
} Vertex;

typedef struct Graph {
	int count;	//간선의 개수
	Vertex vertices[MAX_VERTEX];
	Edge edges[MAX_EDGE];
} Graph;

void initGraph(Graph* graph) {
	graph->count = 0;
	for (int i = 0; i < MAX_VERTEX; i++) {
		EdgeNode* newNode = (EdgeNode*)malloc(sizeof(EdgeNode));	//헤더 노드 생성 후 유효하지 않은 값 대입하여 초기화
		newNode->idx = -1;
		newNode->edge = NULL;
		newNode->link = NULL;
		graph->vertices[i].edges = newNode;
		graph->vertices[i].vLabel = 1;
	}
}

void insertNode(EdgeNode* header, EdgeNode* newNode) {
	EdgeNode* curr = header;
	while (curr->link && curr->link->idx < newNode->idx) curr = curr->link;
	newNode->link = curr->link;
	curr->link = newNode;
}

void insertEdge(Graph* graph, int a, int b) {
	graph->edges[graph->count].endpoint1 = a;
	graph->edges[graph->count].endpoint2 = b;
	graph->edges[graph->count].eLabel = 1;

	EdgeNode* newNode = (EdgeNode*)malloc(sizeof(EdgeNode));
	newNode->idx = b;
	newNode->edge = &(graph->edges[graph->count]);
	newNode->link = NULL;
	insertNode(graph->vertices[a - 1].edges, newNode);

	if (a != b) {	//루프가 아닐 경우 반대 방향도 삽입
		newNode = (EdgeNode*)malloc(sizeof(EdgeNode));
		newNode->idx = a;
		newNode->edge = &(graph->edges[graph->count]);
		newNode->link = NULL;
		insertNode(graph->vertices[b - 1].edges, newNode);
	}
	graph->count++;
}

void destroyGraph(Graph* graph) {
	for (int i = 0; i < MAX_VERTEX; i++) {	//각 정점에 대해 인접 리스트 해제
		EdgeNode* curr = graph->vertices[i].edges;
		while (curr) {
			EdgeNode* temp = curr;
			curr = curr->link;
			free(temp);
		}
	}
}

void rDFS(Graph* graph, int index) {
	graph->vertices[index].vLabel = 0;
	int opposite;
	EdgeNode* curr = graph->vertices[index].edges->link;

	while (curr) {
		if (curr->edge->eLabel == 1) {
			opposite = curr->idx;
			if (graph->vertices[opposite - 1].vLabel == 1) {
				curr->edge->eLabel = 2;
				printf("%d\n", opposite);
				rDFS(graph, opposite - 1);
			}
			else curr->edge->eLabel = 3;
		}
		curr = curr->link;
	}
}

void DFS(Graph* graph, int n, int s) {
	int j = 0;
	for (int i = 0; i < n; i++) {
		j = i + s;
		if (j > n) j %= n;
		if (graph->vertices[j - 1].vLabel == 1) {
			rDFS(graph, j - 1);
		}
	}
}


int main() {
	int n, m, s;	//정점 개수 n, 간선 개수 m, 순회 시작 정점 번호 s
	int p1, p2;
	Graph graph;
	initGraph(&graph);

	scanf("%d %d %d", &n, &m, &s);

	for (int i = 0; i < m; i++) {
		scanf("%d %d", &p1, &p2);
		insertEdge(&graph, p1, p2);
	}

	printf("%d\n", s);
	DFS(&graph, n, s);

	destroyGraph(&graph);

	return 0;
}