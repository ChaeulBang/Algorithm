#include<stdio.h>
#include<stdlib.h>
#define MAX_VERTEX 100
#define MAX_EDGE 1000

//BFS
//인접행렬

typedef struct Graph {
	int vertices[MAX_VERTEX];
	int adjMat[MAX_VERTEX][MAX_VERTEX];
} Graph;

typedef struct Queue {
	int vertex[MAX_VERTEX];
	int front, rear;
} Queue;

void initQueue (Queue* q) {
	q->front = q->rear = 0;
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

void initGraph(Graph* graph) {
	for (int i = 0; i < MAX_VERTEX; i++) {
		graph->vertices[i] = -1;
		for (int j = 0; j < MAX_VERTEX; j++) {
			graph->adjMat[i][j] = -1;
		}
	}
}

void insertEdge(Graph* graph, int a, int b) {
	graph->vertices[a - 1] = 1;
	graph->vertices[b - 1] = 1;
	graph->adjMat[a - 1][b - 1] = 1;
	graph->adjMat[b - 1][a - 1] = 1;
}

void BFS1(Graph* graph, int point, int n, Queue* q) {
	//정점 없음 = -1, 있음 = 1, Fresh = 2, Visited = 3
	//간선 없음 = -1, 있음 = 1, Fresh = 2, Tree = 3, Cross = 4
	enqueue(q, point);
	graph->vertices[point - 1] = 3;

	while (!isEmpty(q)) {
		int v = dequeue(q);
		for (int j = 0; j < n; j++) {
			if (graph->adjMat[v - 1][j] == 2) {
				if (graph->vertices[j] == 2) {
					printf("%d\n", j + 1);
					graph->adjMat[v - 1][j] = 3;
					graph->vertices[j] = 3;
					enqueue(q, j + 1);
				}
			}
		}
	}
}

void BFS(Graph* graph, int n, int s) {
	int i, j;
	Queue queue;
	initQueue(&queue);
	for (i = 0; i < n; i++) graph->vertices[i] = 2;
	for (i = 0; i < n; i++)
		for (j = 0; j < n; j++)
			if (graph->adjMat[i][j] == 1) graph->adjMat[i][j] = 2;
	BFS1(graph, s, n, &queue);
}


int main() {
	int n, m, s;
	int p1, p2;
	Graph graph;
	initGraph(&graph);

	scanf("%d %d %d", &n, &m, &s);

	for (int i = 0; i < m; i++) {
		scanf("%d %d", &p1, &p2);
		insertEdge(&graph, p1, p2);
	}

	printf("%d\n", s);
	BFS(&graph, n, s);

	return 0;
}