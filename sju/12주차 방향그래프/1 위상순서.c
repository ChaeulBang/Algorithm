#include<stdio.h>
#include<stdlib.h>
#define MAX_VERTEX 100
#define MAX_EDGE 1000

//방향그래프 위상순서 찾기
//비싸이클
//각 정점의 진입차수를 이용하는 버전

typedef struct Edge {
	int origin;			//시점
	int destination;	//종점
} Edge;

typedef struct EdgeNode {	//부착간선리스트
	int element;			//간선의 인덱스
	struct EdgeNode* next;
} EdgeNode;

typedef struct Vertex {
	char name;
	EdgeNode* outEdges;	//진출 부착간선리스트 (헤더)
	EdgeNode* inEdges;	//진입 부착간선리스트 (헤더)
	int inDegree;		//진입차수
} Vertex;

typedef struct Graph {
	Vertex vertices[MAX_VERTEX];
	Edge edges[MAX_EDGE];
} Graph;

typedef struct Queue {
	int vertex[MAX_VERTEX];	//정점들의 대기열
	int front, rear;
} Queue;

int n, m;	//정점n개 간선m개
char topOrder[MAX_VERTEX + 1];	//DAG이면 [0]= 1, DAG 아니면 [0] = 0, 그 이후론 정점들의 위상순서	<!--인덱스 배열로?-->
Graph g;

void buildGraph();		//방향그래프 정보를 읽어 들여 g에 저장
void insertVertex(char vName, int i);	//정점 삽입
void insertDirectedEdge(char uName, char wName, int i);	//간선 삽입
int index(char vName);	//vName에 해당하는 정점의 인덱스를 반환	
void addFirst(EdgeNode* H, int i);	//H의 첫 노드 위치에 정수 i를 원소로 하는 노드를 삽입
void topologicalSort();
int isEmpty(Queue* q);
void enqueue(Queue* q, int v);
int dequeue(Queue* q);


void buildGraph() {
	char vName, uName, wName;

	scanf("%d", &n);	//정점 수
	getchar();
	for (int i = 0; i < n; i++) {
		scanf("%c", &vName);
		insertVertex(vName, i);	//그래프에 정점 삽입
		getchar();
	}

	scanf("%d", &m);	//간선 수
	getchar();
	for (int i = 0; i < m; i++) {
		scanf("%c %c", &uName, &wName);
		insertDirectedEdge(uName, wName, i);	//그래프에 방향간선 삽입
		getchar();
	}
}

void insertVertex(char vName, int i) {
	EdgeNode* newNode1 = (EdgeNode*)malloc(sizeof(EdgeNode));	//헤더 노드 생성 후 유효하지 않은 값 대입하여 초기화
	EdgeNode* newNode2 = (EdgeNode*)malloc(sizeof(EdgeNode));
	newNode1->element = -1;
	newNode1->next = NULL;
	newNode2->element = -1;
	newNode2->next = NULL;
	g.vertices[i].outEdges = newNode1;
	g.vertices[i].inEdges = newNode2;
	g.vertices[i].name = vName;
	g.vertices[i].inDegree = 0;	//정점 i의 진입차수 초기화
}

void insertDirectedEdge(char uName, char wName, int i) {	//간선 삽입
	int u = g.edges[i].origin = index(uName);		//시점
	int w = g.edges[i].destination = index(wName);	//종점
	addFirst(g.vertices[u].outEdges, i);		//u의 진출 부착간선리스트에 삽입
	addFirst(g.vertices[w].inEdges, i);			//w의 진입 부착간선리스트에 삽입
	g.vertices[w].inDegree++;					//w의 진입차수 갱신
}

int index(char vName) {
	for (int i = 0; i < n; i++)
		if (g.vertices[i].name == vName)
			return i;
}

void addFirst(EdgeNode* H, int i) {	//H의 첫 노드 위치에 정수 i를 원소로 하는 노드를 삽입	
	EdgeNode* newNode = (EdgeNode*)malloc(sizeof(EdgeNode));	//동적할당
	newNode->element = i;										//newNode 원소로 i를 저장
	newNode->next = H->next;									//기존 연결리스트를 newNode 뒤에 연결
	H->next = newNode;											//newNode를 H의 첫 노드로 설정
}

void topologicalSort() {
	int in[MAX_VERTEX];	//in[i] = 정점 i의 진입차수
	int t = 1;	//위상순위
	EdgeNode* tmp;

	Queue* queue = (Queue*)malloc(sizeof(Queue));
	queue->front = queue->rear = 0;	//큐 초기화

	for (int i = 0; i < n; i++) {
		in[i] = g.vertices[i].inDegree;		//정점 i의 진입차수를 배열에 저장
		if (in[i] == 0) enqueue(queue, i);	//진입차수 0인 정점을(인덱스를) 큐에 삽입
	}

	while (!isEmpty(queue)) {
		int u = dequeue(queue);
		topOrder[t++] = g.vertices[u].name;	//위상순위 t 정점 저장

		tmp = g.vertices[u].outEdges->next;
		while (tmp != NULL) {	//u의 모든 진출간선 e에 대해 반복
			int idx = tmp->element;
			int w = g.edges[idx].destination;	//w는 간선 e의 종점
			in[w]--;
			if (in[w] == 0) enqueue(queue, w);	//w의 진입차수가 0이면 큐에 삽입
			tmp = tmp->next;
		}
	}

	topOrder[0] = (t <= n) ? '0' : '1';	//아직 위상순위가 매겨지지 않은 정점이 존재하는지 여부
}

int isEmpty(Queue* q) {
	return (q->front == q->rear);
}

void enqueue(Queue* q, int v) {
	q->rear = (q->rear + 1) % MAX_VERTEX;
	q->vertex[q->rear] = v;
}

int dequeue(Queue* q) {
	q->front = (q->front + 1) % MAX_VERTEX;
	return q->vertex[q->front];
}


int main() {
	buildGraph();		//g 구축

	topologicalSort();	//g를 위상 정렬
	if (topOrder[0] == '0') printf("0");	//g가 DAG가 아닐 때 (싸이클 존재)
	else {	//g가 DAG일 때
		for (int i = 1; i <= n; i++)
			printf("%c ", topOrder[i]);
	}

	return 0;
}