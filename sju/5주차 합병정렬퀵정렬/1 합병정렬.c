#include<stdio.h>
#include<stdlib.h>

typedef struct ListNode {	//리스트에 들어갈 노드
	int elem;
	struct ListNode* next;
} ListNode;

ListNode* merge(ListNode** L1, ListNode** L2);	//mergeSort에 호출되어 두 개의 정렬된 단일연결리스트 L1과 L2를 합병한 하나의 단일연결리스트를 반환
void mergeSort(ListNode** L, int n);	//단일연결리스트 L의 원소들을 합병 정렬하여 정렬된 결과를 오름차순으로 정렬
void partition(ListNode* L, int k, ListNode** L1, ListNode** L2);	//단일연결리스트 L과 양의 정수 k를 전달받아 L을 크기가 k이고 |L|-k인 두 개의 부리스트 L1과 L2로 분할하여 (L1, L2)를 반환
void addList(ListNode** L, int value);	//리스트에 노드 추가


int main() {
	int n, value;
	ListNode* list = NULL;

	scanf("%d", &n);	//단일연결리스트의 크기 n

	for (int i = 0; i < n; i++) {	//리스트에 노드 추가
		scanf("%d", &value);
		addList(&list, value);
	}

	mergeSort(&list, n);	//합병 정렬

	while (list != NULL) {	//출력
		printf(" %d", list->elem);
		list = list->next;
	}

	free(list);	//메모리 해제
}

void partition(ListNode* L, int k, ListNode** L1, ListNode** L2) {	//리스트 분할
	ListNode* temp = L;

	*L1 = L;	//부리스트 L1
	for (int i = 0; i < k / 2 - 1; i++) temp = temp->next;
	*L2 = temp->next;	//부리스트 L2를 크기 |L|-k로 만드는 과정
	temp->next = NULL;	//부리스트 L1과 L2를 분할
}

ListNode* merge(ListNode** L1, ListNode** L2) {
	ListNode* mergedList = NULL;	//최종 merged된 리스트
	ListNode* tempL1 = *L1;
	ListNode* tempL2 = *L2;

	while (tempL1 != NULL && tempL2 != NULL) {	//두 리스트 중 하나라도 널이 될 때까지
		if (tempL1->elem <= tempL2->elem) {	//리스트 요소 비교
			addList(&mergedList, tempL1->elem);	//최종 리스트에 더 작은 값 추가
			tempL1 = tempL1->next;
		}

		else {
			addList(&mergedList, tempL2->elem);
			tempL2 = tempL2->next;
		}
	}

	//나머지 요소
	while (tempL1 != NULL) {
		addList(&mergedList, tempL1->elem);
		tempL1 = tempL1->next;
	}

	while (tempL2 != NULL) {
		addList(&mergedList, tempL2->elem);
		tempL2 = tempL2->next;
	}

	return mergedList;
}

void mergeSort(ListNode** L, int n) {
	ListNode* L1, * L2;
	ListNode* temp = *L;

	if (n > 1) {
		partition(temp, n, &L1, &L2);	//분할

		if (n % 2 == 0) {	//리스트 크기가 짝수일 경우
			mergeSort(&L1, n / 2);
			mergeSort(&L2, n / 2);
		}

		else {	//리스트 크기가 홀수일 경우
			mergeSort(&L1, n / 2);
			mergeSort(&L2, (n / 2) + 1);
		}

		*L = merge(&L1, &L2);	//합병
	}
}

void addList(ListNode** L, int value) {	//노드 추가
	ListNode* temp = *L;
	ListNode* newNode = (ListNode*)malloc(sizeof(ListNode));	//새로운 노드 생성 후 할당
	newNode->next = NULL;
	newNode->elem = value;

	if (*L == NULL) *L = newNode;	//리스트가 빈 리스트일 경우
	else {
		while (temp->next != NULL) temp = temp->next;	//끝으로 이동
		temp->next = newNode;
	}
}