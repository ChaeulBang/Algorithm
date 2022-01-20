#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
	int node;
	int weight;
	struct Node* link;
} Node;

typedef struct Vertex {
	Node* head;
} Vertex;

typedef struct Graph {
	int count;
	Vertex* vertex;
} Graph;

Graph* createGraph() {
	Graph* graph = (Graph*)malloc(sizeof(Graph));
	graph->count = 0;
	graph->vertex = (Vertex*)malloc(sizeof(Vertex) * 6);
	for (int i = 0; i < 6; i++) {
		graph->vertex[i].head = (Node*)malloc(sizeof(Node));
		graph->vertex[i].head->link = NULL;
	}
	return graph;
}

void print(Graph* g, int a) {
	if (a > 6) {
		printf("-1\n");
	}
	else {
		a--;
		Node* curr = g->vertex[a].head->link;
		while (curr != NULL) {
			printf(" %d %d", (curr->node) + 1, curr->weight);
			curr = curr->link;
		}
		printf("\n");
	}
}

void removeNode(Node* prev) {
	Node* temp = prev->link;
	prev->link = prev->link->link;
	free(temp);
	temp = NULL;
}

void insertNode(Node* prev, int node, int weight) {
	Node* newNode = (Node*)malloc(sizeof(Node));
	newNode->node = node;
	newNode->weight = weight;
	newNode->link = prev->link;
	prev->link = newNode;
}

void modify(Graph* g, int a, int b, int w) {
	if (a > 6 || b > 6) {
		printf("-1\n");
	}
	else {
		a--;
		b--;
		Node* prev = g->vertex[a].head;
		while (prev->link != NULL && prev->link->node < b) {
			prev = prev->link;
		}
		if (prev->link == NULL) {
			insertNode(prev, b, w);
			if (a != b) {
				Node* prev2 = g->vertex[b].head;
				while (prev2->link != NULL && prev2->link->node < a) {
					prev2 = prev2->link;
				}
				insertNode(prev2, a, w);
			}
		}
		else if (prev->link->node == b) {
			if (w == 0) {
				removeNode(prev);
				if (a != b) {
					Node* prev2 = g->vertex[b].head;
					while (prev2->link != NULL && prev2->link->node < a) {
						prev2 = prev2->link;
					}
					removeNode(prev2);
				}
			}
			else {
				prev->link->weight = w;
				if (a != b) {
					Node* prev2 = g->vertex[b].head;
					while (prev2->link != NULL && prev2->link->node < a) {
						prev2 = prev2->link;
					}
					prev2->link->weight = w;
				}
			}
		}
		else {
			insertNode(prev, b, w);
			if (a != b) {
				Node* prev2 = g->vertex[b].head;
				while (prev2->link != NULL && prev2->link->node < a) {
					prev2 = prev2->link;
				}
				insertNode(prev2, a, w);
			}
		}
	}
}

int main() {
	int a, b, w;
	Graph* g = createGraph();
	insertNode(g->vertex[0].head, 1, 1);
	insertNode(g->vertex[0].head->link, 2, 1);
	insertNode(g->vertex[0].head->link->link, 3, 1);
	insertNode(g->vertex[0].head->link->link->link, 5, 2);
	insertNode(g->vertex[1].head, 0, 1);
	insertNode(g->vertex[1].head->link, 2, 1);
	insertNode(g->vertex[2].head, 0, 1);
	insertNode(g->vertex[2].head->link, 1, 1);
	insertNode(g->vertex[2].head->link->link, 4, 4);
	insertNode(g->vertex[3].head, 0, 1);
	insertNode(g->vertex[4].head, 2, 4);
	insertNode(g->vertex[4].head->link, 4, 4);
	insertNode(g->vertex[4].head->link->link, 5, 3);
	insertNode(g->vertex[5].head, 0, 2);
	insertNode(g->vertex[5].head->link, 4, 3);

	while (1) {
		switch (getchar()) {
		case 'a':
			scanf("%d", &a);
			print(g, a);
			break;
		case 'm':
			scanf("%d %d %d", &a, &b, &w);
			modify(g, a, b, w);
			break;
		case 'q':
			return;
		default:
			break;
		}
	}
}