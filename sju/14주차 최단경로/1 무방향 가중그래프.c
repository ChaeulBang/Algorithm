#include<stdio.h>
#include<stdlib.h>
#define INF 1e9+7

int n, m, s, arr[101][101], visited[101];	//노드 개수, 간선 개수, 인접행렬, 방문배열

void Dijkstra() {
	visited[s] = 0;

	while (1) {
		int idx = 0, dst = INF;	//다음으로 방문할 정점, 그 정점까지의 거리

		for (int i = 1; i <= n; i++) {	//현재 도달 가능한 노드 중 최단거리를 찾아 저장
			if (visited[i] == INF && arr[s][i] < dst) {
				idx = i;
				dst = arr[s][i];
			}
		}

		if (idx == 0) break;	//탈출조건

		visited[idx] = dst;

		for (int i = 1; i <= n; i++) {	//새로 방문한 노드를 통해 거리가 줄어드는 노드들을 갱신
			if (arr[s][idx] + arr[idx][i] < arr[s][i])
				arr[s][i] = arr[s][idx] + arr[idx][i];
		}
	}
}
int main() {
	scanf("%d %d %d", &n, &m, &s);

	for (int i = 1; i <= n; i++) {	//인접행렬 초기화
		for (int j = 1; j <= n; j++) {
			arr[i][j] = INF;
		}
	}

	for (int i = 1; i <= n; i++) {	//방문배열 초기화
		visited[i] = INF;
	}

	for (int i = 0; i < m; i++) {	//입력
		int v1, v2, w;
		scanf("%d %d %d", &v1, &v2, &w);
		arr[v1][v2] = arr[v2][v1] = w;
	}

	Dijkstra();

	for (int i = 1; i <= n; i++) {
		if (i != s && visited[i] != INF)
			printf("%d %d\n", i, visited[i]);
	}

	return 0;
}