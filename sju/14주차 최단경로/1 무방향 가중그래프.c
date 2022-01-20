#include<stdio.h>
#include<stdlib.h>
#define INF 1e9+7

int n, m, s, arr[101][101], visited[101];	//��� ����, ���� ����, �������, �湮�迭

void Dijkstra() {
	visited[s] = 0;

	while (1) {
		int idx = 0, dst = INF;	//�������� �湮�� ����, �� ���������� �Ÿ�

		for (int i = 1; i <= n; i++) {	//���� ���� ������ ��� �� �ִܰŸ��� ã�� ����
			if (visited[i] == INF && arr[s][i] < dst) {
				idx = i;
				dst = arr[s][i];
			}
		}

		if (idx == 0) break;	//Ż������

		visited[idx] = dst;

		for (int i = 1; i <= n; i++) {	//���� �湮�� ��带 ���� �Ÿ��� �پ��� ������ ����
			if (arr[s][idx] + arr[idx][i] < arr[s][i])
				arr[s][i] = arr[s][idx] + arr[idx][i];
		}
	}
}
int main() {
	scanf("%d %d %d", &n, &m, &s);

	for (int i = 1; i <= n; i++) {	//������� �ʱ�ȭ
		for (int j = 1; j <= n; j++) {
			arr[i][j] = INF;
		}
	}

	for (int i = 1; i <= n; i++) {	//�湮�迭 �ʱ�ȭ
		visited[i] = INF;
	}

	for (int i = 0; i < m; i++) {	//�Է�
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