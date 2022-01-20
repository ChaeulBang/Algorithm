#include<stdio.h>
#include<stdlib.h>
#define MAX_VERTEX 100
#define MAX_EDGE 1000

//����׷��� ������� ã��
//�����Ŭ
//�� ������ ���������� �̿��ϴ� ����

typedef struct Edge {
	int origin;			//����
	int destination;	//����
} Edge;

typedef struct EdgeNode {	//������������Ʈ
	int element;			//������ �ε���
	struct EdgeNode* next;
} EdgeNode;

typedef struct Vertex {
	char name;
	EdgeNode* outEdges;	//���� ������������Ʈ (���)
	EdgeNode* inEdges;	//���� ������������Ʈ (���)
	int inDegree;		//��������
} Vertex;

typedef struct Graph {
	Vertex vertices[MAX_VERTEX];
	Edge edges[MAX_EDGE];
} Graph;

typedef struct Queue {
	int vertex[MAX_VERTEX];	//�������� ��⿭
	int front, rear;
} Queue;

int n, m;	//����n�� ����m��
char topOrder[MAX_VERTEX + 1];	//DAG�̸� [0]= 1, DAG �ƴϸ� [0] = 0, �� ���ķ� �������� �������	<!--�ε��� �迭��?-->
Graph g;

void buildGraph();		//����׷��� ������ �о� �鿩 g�� ����
void insertVertex(char vName, int i);	//���� ����
void insertDirectedEdge(char uName, char wName, int i);	//���� ����
int index(char vName);	//vName�� �ش��ϴ� ������ �ε����� ��ȯ	
void addFirst(EdgeNode* H, int i);	//H�� ù ��� ��ġ�� ���� i�� ���ҷ� �ϴ� ��带 ����
void topologicalSort();
int isEmpty(Queue* q);
void enqueue(Queue* q, int v);
int dequeue(Queue* q);


void buildGraph() {
	char vName, uName, wName;

	scanf("%d", &n);	//���� ��
	getchar();
	for (int i = 0; i < n; i++) {
		scanf("%c", &vName);
		insertVertex(vName, i);	//�׷����� ���� ����
		getchar();
	}

	scanf("%d", &m);	//���� ��
	getchar();
	for (int i = 0; i < m; i++) {
		scanf("%c %c", &uName, &wName);
		insertDirectedEdge(uName, wName, i);	//�׷����� ���Ⱓ�� ����
		getchar();
	}
}

void insertVertex(char vName, int i) {
	EdgeNode* newNode1 = (EdgeNode*)malloc(sizeof(EdgeNode));	//��� ��� ���� �� ��ȿ���� ���� �� �����Ͽ� �ʱ�ȭ
	EdgeNode* newNode2 = (EdgeNode*)malloc(sizeof(EdgeNode));
	newNode1->element = -1;
	newNode1->next = NULL;
	newNode2->element = -1;
	newNode2->next = NULL;
	g.vertices[i].outEdges = newNode1;
	g.vertices[i].inEdges = newNode2;
	g.vertices[i].name = vName;
	g.vertices[i].inDegree = 0;	//���� i�� �������� �ʱ�ȭ
}

void insertDirectedEdge(char uName, char wName, int i) {	//���� ����
	int u = g.edges[i].origin = index(uName);		//����
	int w = g.edges[i].destination = index(wName);	//����
	addFirst(g.vertices[u].outEdges, i);		//u�� ���� ������������Ʈ�� ����
	addFirst(g.vertices[w].inEdges, i);			//w�� ���� ������������Ʈ�� ����
	g.vertices[w].inDegree++;					//w�� �������� ����
}

int index(char vName) {
	for (int i = 0; i < n; i++)
		if (g.vertices[i].name == vName)
			return i;
}

void addFirst(EdgeNode* H, int i) {	//H�� ù ��� ��ġ�� ���� i�� ���ҷ� �ϴ� ��带 ����	
	EdgeNode* newNode = (EdgeNode*)malloc(sizeof(EdgeNode));	//�����Ҵ�
	newNode->element = i;										//newNode ���ҷ� i�� ����
	newNode->next = H->next;									//���� ���Ḯ��Ʈ�� newNode �ڿ� ����
	H->next = newNode;											//newNode�� H�� ù ���� ����
}

void topologicalSort() {
	int in[MAX_VERTEX];	//in[i] = ���� i�� ��������
	int t = 1;	//�������
	EdgeNode* tmp;

	Queue* queue = (Queue*)malloc(sizeof(Queue));
	queue->front = queue->rear = 0;	//ť �ʱ�ȭ

	for (int i = 0; i < n; i++) {
		in[i] = g.vertices[i].inDegree;		//���� i�� ���������� �迭�� ����
		if (in[i] == 0) enqueue(queue, i);	//�������� 0�� ������(�ε�����) ť�� ����
	}

	while (!isEmpty(queue)) {
		int u = dequeue(queue);
		topOrder[t++] = g.vertices[u].name;	//������� t ���� ����

		tmp = g.vertices[u].outEdges->next;
		while (tmp != NULL) {	//u�� ��� ���Ⱓ�� e�� ���� �ݺ�
			int idx = tmp->element;
			int w = g.edges[idx].destination;	//w�� ���� e�� ����
			in[w]--;
			if (in[w] == 0) enqueue(queue, w);	//w�� ���������� 0�̸� ť�� ����
			tmp = tmp->next;
		}
	}

	topOrder[0] = (t <= n) ? '0' : '1';	//���� ��������� �Ű����� ���� ������ �����ϴ��� ����
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
	buildGraph();		//g ����

	topologicalSort();	//g�� ���� ����
	if (topOrder[0] == '0') printf("0");	//g�� DAG�� �ƴ� �� (����Ŭ ����)
	else {	//g�� DAG�� ��
		for (int i = 1; i <= n; i++)
			printf("%c ", topOrder[i]);
	}

	return 0;
}