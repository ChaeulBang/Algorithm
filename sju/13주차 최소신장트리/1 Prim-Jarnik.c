#include<stdio.h>
#include<stdlib.h>
#include<math.h>

//Prim-Jarnik 알고리즘
//무방향간선 (한 정점에서 다른 정점 가는 경로 반드시 존재)
//가중치 유일

typedef struct Vertex {
	int index;
	float weight;
	int flag;
}Vertex;

int main() {
	int n, m;
	int v1, v2;
	float w, sum = 0;

	scanf("%d %d", &n, &m);
	Vertex* vertices = malloc(n * sizeof(Vertex));
	float** adjMat = malloc(n * sizeof(float*));
	int* result = malloc(n * sizeof(int));

	for (int i = 0; i < n; i++) {
		adjMat[i] = malloc(n * sizeof(float));
		vertices[i].index = i;
		vertices[i].weight = INFINITY;
		vertices[i].flag = 0;
		for (int j = 0; j < n; j++) {
			adjMat[i][j] = 0;	//0이면 간선 존재X
		}
	}

	for (int i = 0; i < m; i++) {
		scanf("%d %d %f", &v1, &v2, &w);
		adjMat[v1 - 1][v2 - 1] = w;
		adjMat[v2 - 1][v1 - 1] = w;
	}

	int idx = 0, minIdx = 0, resultIdx = 0;
	result[resultIdx++] = vertices[minIdx].index + 1;
	vertices[minIdx].flag = 1;

	for (int i = 1; i < n; i++) {	//n-1회 반복
		for (int j = 1; j < n; j++) {	//인접행렬 검사
			if (adjMat[minIdx][j] != 0 && vertices[j].flag == 0) {
				vertices[j].weight = vertices[j].weight < adjMat[minIdx][j] ? vertices[j].weight : adjMat[minIdx][j];
			}
		}
		minIdx = 0;
		for (int k = 1; k < n; k++) {
			if (vertices[k].flag == 0 && vertices[k].weight < vertices[minIdx].weight) minIdx = k;
		}
		result[resultIdx++] = vertices[minIdx].index + 1;
		vertices[minIdx].flag = 1;
		sum += vertices[minIdx].weight;
	}

	for (int i = 0; i < n; i++) printf(" %d", result[i]);
	printf("\n%.0f", sum);

	for (int i = 0; i < n; i++) free(adjMat[i]);
	free(adjMat);
	free(vertices);
	free(result);
}