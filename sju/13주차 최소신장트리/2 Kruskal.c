#include<stdio.h>
#include<stdlib.h>
#define MAX_VERTICES 100
#define MAX_EDGES 100

int parent[MAX_VERTICES]; //각 정점의 부모 노드
int num[MAX_VERTICES];    //각 집합의 크기

//union find 다시 학습
int set_find(int vertex) {  
    int p, s, i = -1;

    for (i = vertex; (p = parent[i]) >= 0; i = p);  //루트(parent 값 -1)까지 반복하여 루트 찾기
    s = i;  //루트 s
    for (i = vertex; (p = parent[i]) >= 0; i = p) { //해당 정점의 조상노드들이 모두 루트(s)를 향하게끔 설정
        parent[i] = s;
    }

    return s;   //루트 반환
}

void set_union(int s1, int s2) {    //집합 합치기
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
    int weight;     //간선 가중치
    int u;          //정점1
    int v;          //정점2
} Edge;

typedef struct {
    Edge heap[MAX_EDGES];
    int heapSize;
} HeapType;

void insertUpHeap(HeapType* h, Edge e) {
    int i = ++h->heapSize;
    while (e.weight < h->heap[i / 2].weight) {    //거슬러 올라가며 교체..연산
        if (i == 1) break;
        h->heap[i] = h->heap[i / 2];
        i /= 2; //부모노드의 자리로 이동
    }
    h->heap[i] = e; //삽입
}

Edge removeMin(HeapType* h) {
    int parent, child;
    Edge e, temp;

    e = h->heap[1]; //루트노드(최소값) 저장
    temp = h->heap[h->heapSize]; //마지막노드(최대값) 저장
    h->heapSize--;  //루트 자리에 두었다고 가정

    //시작 - 루트와 그 왼쪽 자식
    parent = 1;
    child = 2;

    while (1) {
        if (child > h->heapSize) break;
        if (h->heap[child].weight > h->heap[child + 1].weight) child++;  //우측자식 선택
        if (temp.weight <= h->heap[child].weight) break;

        h->heap[parent] = h->heap[child];   //자식과 교환
        parent = child;
        child *= 2;
    }
    h->heap[parent] = temp; //삽입

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
    int edgeCount = 0;  //현재까지 선택된 간선 수
    int uset, vset;
    Edge e;
    int sum = 0;

    //집합 초기화
    for (int i = 0; i < n; i++) {
        parent[i] = -1;
        num[i] = 1;
    }

    while (1) {
        if (edgeCount == n - 1) break;
        e = removeMin(h);   //최소 가중치 간선
        uset = set_find(e.u);   //정점이 어느 집합에 속해있는지 찾기
        vset = set_find(e.v);

        if (uset != vset) { //서로 다른 집합에 속해 있으면
            printf(" %d", e.weight);
            sum += e.weight;
            edgeCount++;    //선택 간선 수 ++
            set_union(uset, vset);  //합침
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