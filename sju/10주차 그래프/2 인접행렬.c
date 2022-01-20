#include<stdio.h>
#include<stdlib.h>

// 그래프 인접행렬

int main() {
	int n, v1, v2, w;
	int adjMatrix[6][6];

	for (int i = 0; i < 6; i++)
		for (int j = 0; j < 6; j++)
			adjMatrix[i][j] = 0;

	adjMatrix[0][1] = 1;
	adjMatrix[0][2] = 1;
	adjMatrix[0][3] = 1;
	adjMatrix[0][5] = 2;
	adjMatrix[1][0] = 1;
	adjMatrix[1][2] = 1;
	adjMatrix[2][0] = 1;
	adjMatrix[2][1] = 1;
	adjMatrix[2][4] = 4;
	adjMatrix[3][0] = 1;
	adjMatrix[4][2] = 4;
	adjMatrix[4][4] = 4;
	adjMatrix[4][5] = 3;
	adjMatrix[5][0] = 2;
	adjMatrix[5][4] = 3;

	while (1) {
		switch (getchar()) {
		case 'a':
			scanf("%d", &n);
			for (int i = 0; i < 6; i++) {
				if (n > 6) {
					printf("-1");
					break;
				}
				else if (adjMatrix[n - 1][i] == 0) continue;
				else printf(" %d %d", i + 1, adjMatrix[n - 1][i]);
			}
			printf("\n");
			break;
		case 'm':
			scanf("%d %d %d", &v1, &v2, &w);
			if (v1 > 6 || v2 > 6) printf("-1\n");
			else if (w == 0) adjMatrix[v1 - 1][v2 - 1] = adjMatrix[v2 - 1][v1 - 1] = 0;
			else adjMatrix[v1 - 1][v2 - 1] = adjMatrix[v2 - 1][v1 - 1] = w;
			break;
		case 'q':
			goto QUIT;
		}
	}
QUIT:
	return 0;
}