#include<stdio.h>
#include<stdlib.h>
#define MAX_VERTICES 100
#define MAX_EDGES 100

int parent[MAX_VERTICES]; //�� ������ �θ� ���
int num[MAX_VERTICES];    //�� ������ ũ��

//union find �ٽ� �н�
int set_find(int vertex) {  
    int p, s, i = -1;

    for (i = vertex; (p = parent[i]) >= 0; i = p);  //��Ʈ(parent �� -1)���� �ݺ��Ͽ� ��Ʈ ã��
    s = i;  //��Ʈ s
    for (i = vertex; (p = parent[i]) >= 0; i = p) { //�ش� ������ ��������� ��� ��Ʈ(s)�� ���ϰԲ� ����
        parent[i] = s;
    }

    return s;   //��Ʈ ��ȯ
}

void set_union(int s1, int s2) {    //���� ��ġ��
    if (num[s1] < num[s2]) {
        parent[s1] = s2;
        num[s2] += num[s1];
    }
    else {
        parent[s2] = s1;
        num[s1] += num[s2];
    }
}

typedef struct {
    int weight;     //���� ����ġ
    int u;          //����1
    int v;          //����2
} Edge;

typedef struct {
    Edge heap[MAX_EDGES];
    int heapSize;
} HeapType;

void insertUpHeap(HeapType* h, Edge e) {
    int i = ++h->heapSize;
    while (e.weight < h->heap[i / 2].weight) {    //�Ž��� �ö󰡸� ��ü..����
        if (i == 1) break;
        h->heap[i] = h->heap[i / 2];
        i /= 2; //�θ����� �ڸ��� �̵�
    }
    h->heap[i] = e; //����
}

Edge removeMin(HeapType* h) {
    int parent, child;
    Edge e, temp;

    e = h->heap[1]; //��Ʈ���(�ּҰ�) ����
    temp = h->heap[h->heapSize]; //���������(�ִ밪) ����
    h->heapSize--;  //��Ʈ �ڸ��� �ξ��ٰ� ����

    //���� - ��Ʈ�� �� ���� �ڽ�
    parent = 1;
    child = 2;

    while (1) {
        if (child > h->heapSize) break;
        if (h->heap[child].weight > h->heap[child + 1].weight) child++;  //�����ڽ� ����
        if (temp.weight <= h->heap[child].weight) break;

        h->heap[parent] = h->heap[child];   //�ڽİ� ��ȯ
        parent = child;
        child *= 2;
    }
    h->heap[parent] = temp; //����

    return e;
}

void insertEdge(HeapType* h, int u, int v, int weight) {
    Edge e;
    e.u = u;
    e.v = v;
    e.weight = weight;
    insertUpHeap(h, e);
}

void kruskal(HeapType* h, int n) {
    int edgeCount = 0;  //������� ���õ� ���� ��
    int uset, vset;
    Edge e;
    int sum = 0;

    //���� �ʱ�ȭ
    for (int i = 0; i < n; i++) {
        parent[i] = -1;
        num[i] = 1;
    }

    while (1) {
        if (edgeCount == n - 1) break;
        e = removeMin(h);   //�ּ� ����ġ ����
        uset = set_find(e.u);   //������ ��� ���տ� �����ִ��� ã��
        vset = set_find(e.v);

        if (uset != vset) { //���� �ٸ� ���տ� ���� ������
            printf(" %d", e.weight);
            sum += e.weight;
            edgeCount++;    //���� ���� �� ++
            set_union(uset, vset);  //��ħ
        }
    }
    printf("\n%d", sum);
}

int main() {
    int n, m;
    int v1, v2, w;
    HeapType* h = malloc(sizeof(HeapType));

    h->heapSize = 0;
    scanf("%d %d", &n, &m);
    for (int i = 0; i < m; i++) {
        scanf("%d %d %d", &v1, &v2, &w);
        insertEdge(h, v1, v2, w);
    }

    kruskal(h, n);
}