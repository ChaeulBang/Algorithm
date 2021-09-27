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
}

void partition(ListNode* L, int k, ListNode** L1, ListNode** L2) {
	ListNode* temp = L;

	*L1 = L;
	for (int i = 0; i < k / 2 - 1; i++) temp = temp->next;
	*L2 = temp->next;
	temp->next = NULL;
}

ListNode* merge(ListNode** L1, ListNode** L2) {
	ListNode* temp, * mergedList;
	ListNode* tempL1 = *L1;
	ListNode* tempL2 = *L2;

	if (tempL1->elem <= tempL2->elem) {
		mergedList = tempL1;
		tempL1 = tempL1->next;
		temp = mergedList;
	}

	else {
		mergedList = tempL2;
		tempL2 = tempL2->next;
		temp = mergedList;
	}

	//두 리스트의 요소 비교
	while (tempL1 != NULL && tempL2 != NULL) {
		if (tempL1->elem <= tempL2->elem) {
			temp->next = tempL1;
			tempL1 = tempL1->next;
			temp = temp->next;
		}

		else {
			temp->next = tempL2;
			tempL2 = tempL2->next;
			temp = temp->next;
		}
	}

	//나머지 요소
	while (tempL1 != NULL) {
		temp->next = tempL1;
		temp = tempL1;
		tempL1 = tempL1->next;
	}

	while (tempL2 != NULL) {
		temp->next = tempL2;
		temp = tempL2;
		tempL2 = tempL2->next;
	}

	return mergedList;
}

void mergeSort(ListNode** L, int n) {
	ListNode* L1, * L2;
	ListNode* temp = *L;

	if (n > 1) {
		partition(temp, n, &L1, &L2);	//분할

		if (n % 2 == 0) {	//짝수 개일 경우
			mergeSort(&L1, n / 2);
			mergeSort(&L2, n / 2);
		}

		else {	//홀수 개일 경우
			mergeSort(&L1, n / 2);
			mergeSort(&L2, (n / 2) + 1);
		}

		*L = merge(&L1, &L2);	//합병
	}
}

void addList(ListNode** L, int value) {	//노드 추가
	ListNode* temp = *L;
	ListNode* newNode = (ListNode*)malloc(sizeof(ListNode));	//새로운 노드 생성 후 할당
	newNode->elem = value;
	newNode->next = NULL;

	if (*L == NULL) *L = newNode;	//리스트가 빈 리스트일 경우
	else {
		while (temp->next != NULL) temp = temp->next;	//끝으로 이동
		temp->next = newNode;
	}
}