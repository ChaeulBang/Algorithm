#include<stdio.h>
#include<stdlib.h>

//������׷��� - ��������Ʈ�� ����
//Ʈ��(����Ŭ ���� ��� ���� ����) �˻� - DFS BFS Ȱ��
//���� Ʈ�� O - �߽ɰ� �̽��� ���
//���� Ʈ�� X - ���� ��� ���� ���

int edge[100];	//�� ������ ���� ���� ����
int visited[100];	//DFS�湮 üũ

typedef struct Node {	//������ ���� ��� ����ü
	int node;
	struct Node* next;
}Node;

void addEdge(Node* prev, int node) {	//������ ������ ��������Ʈ�� �߰�
	Node* newNode = (Node*)malloc(sizeof(Node));
	newNode->node = node;
	newNode->next = prev->next;
	prev->next = newNode;
}

void DFS(Node** head, int now) {	//DFS�� ���� �湮
	visited[now] = 1;	//���� �湮 ������ ǥ��
	Node* curr = head[now]->next;
	while (curr != NULL) {
		if (visited[curr->node] == 0)	//�湮 �� �� ������
			DFS(head, curr->node);	//DFS ���ȣ��
		curr = curr->next;	//���� �������� �̵�
	}
}
int isTree(Node** head, int n, int m) {	//Ʈ��(����Ŭ ���� ��� ���� ����) �˻�
	int cnt = 0;	//������ ����
	for (int i = 1; i <= n; i++) {
		if (visited[i] == 0) {	//�湮 �� �� ���
			DFS(head, i);	//��� ��� �湮
			cnt++;	//������ = ��� ��带 ��ȸ�� �� �� �� �̷�������� ����
		}
	}
	if (n - 1 == m && cnt == 1)	return 0;	//Ʈ���� ���� ������ (���� - 1)���̰� ��� ��� ��ȸ�� �� 1ȸ ��

	return cnt;	//������ ���� ��ȯ
}
void removeLeaves(int* cnt, Node** head, int n) {	//������ ������ 1���� ����(��)�� ����
	int temp[100] = { 0, };	//������ ������ 1���� ������ ������ �ӽ� �迭
	for (int i = 1; i <= n; i++) {
		if (edge[i] == 1) temp[i] = 1;	//������ ������ 1���� ������ �ӽ� �迭�� ����(ǥ��)
	}

	for (int i = 1; i <= n; i++) {
		if (temp[i] == 1) {	//������ ������ 1�����
			edge[i] = 0;	//���� ���� ����
			cnt[i] = 1;	//Ʈ������ ����(ǥ��)
			Node* curr = head[i]->next;
			while (curr != NULL) {
				if (edge[curr->node] > 0)	//����Ǿ� �ִ� ������ ���� ���� ����
					edge[curr->node]--;
				curr = curr->next;
			}
		}
	}
}

int main() {
	int n, m, v1, v2;
	scanf("%d %d", &n, &m);	//����n�� ����m��
	Node** head = (Node**)malloc(sizeof(Node) * (n + 1));	//�Ҵ�

	for (int i = 1; i <= n; i++) {	//�ʱ�ȭ
		head[i] = (Node*)malloc(sizeof(Node));
		head[i]->next = NULL;
	}

	for (int i = 0; i < m; i++) {	//���� �߰�
		scanf("%d %d", &v1, &v2);
		addEdge(head[v1], v2);
		addEdge(head[v2], v1);
		edge[v1]++;	//������ ���� ���� ���� ����
		edge[v2]++;
	}

	if (!isTree(head, n, m)) {	//Ʈ�� O
		int ans = 0;	//�� ���� Ƚ��(�̽���)
		int cnt[100] = { 0, };	//���� Ʈ���� �����ִ� ������ ���� �ӽ� �迭
		int mid = 0;	//�߽� ����

		while (1) {
			int flag = 0;	//���� Ʈ���� �����ִ� ���� ����

			for (int i = 1; i <= n; i++) {
				if (cnt[i] == 0) flag++;	//���� Ʈ���� �����ִ� ������ cnt�� 0���� ǥ�õǾ� ����
			}

			if (flag <= 2) break;	//���� Ʈ���� �����ִ� ���� ������ 2 ���϶�� �ݺ��� ����

			removeLeaves(cnt, head, n);	//�� ����
			ans++;	//�̽����� ���� �� ������ �� �� �̷�������� ��
		}

		for (int i = 1; i <= n; i++) {
			if (cnt[i] == 0) {	//���� Ʈ���� �����ִ� �����̶�� = �߽�
				printf("%d ", i);	//���
				mid++;	//�߽� ���� ����
			}
		}
		printf("\n%d", (mid == 1 ? ans : ans + 1));	//�߽��� �� ����� �̽��� + 1 ���
	}

	else {	//Ʈ�� X
		for (int i = 1; i <= n; i++) visited[i] = 0;	//visited �迭 �ʱ�ȭ - Ʈ�� �˻翡 ���
		printf("%d", isTree(head, n, m));	//������ ���� ���
	}
}