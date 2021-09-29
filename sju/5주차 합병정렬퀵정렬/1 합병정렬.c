#include<stdio.h>
#include<stdlib.h>

typedef struct ListNode {	//����Ʈ�� �� ���
	int elem;
	struct ListNode* next;
} ListNode;

ListNode* merge(ListNode** L1, ListNode** L2);	//mergeSort�� ȣ��Ǿ� �� ���� ���ĵ� ���Ͽ��Ḯ��Ʈ L1�� L2�� �պ��� �ϳ��� ���Ͽ��Ḯ��Ʈ�� ��ȯ
void mergeSort(ListNode** L, int n);	//���Ͽ��Ḯ��Ʈ L�� ���ҵ��� �պ� �����Ͽ� ���ĵ� ����� ������������ ����
void partition(ListNode* L, int k, ListNode** L1, ListNode** L2);	//���Ͽ��Ḯ��Ʈ L�� ���� ���� k�� ���޹޾� L�� ũ�Ⱑ k�̰� |L|-k�� �� ���� �θ���Ʈ L1�� L2�� �����Ͽ� (L1, L2)�� ��ȯ
void addList(ListNode** L, int value);	//����Ʈ�� ��� �߰�


int main() {
	int n, value;
	ListNode* list = NULL;

	scanf("%d", &n);	//���Ͽ��Ḯ��Ʈ�� ũ�� n

	for (int i = 0; i < n; i++) {	//����Ʈ�� ��� �߰�
		scanf("%d", &value);
		addList(&list, value);
	}

	mergeSort(&list, n);	//�պ� ����

	while (list != NULL) {	//���
		printf(" %d", list->elem);
		list = list->next;
	}

	free(list);	//�޸� ����
}

void partition(ListNode* L, int k, ListNode** L1, ListNode** L2) {	//����Ʈ ����
	ListNode* temp = L;

	*L1 = L;	//�θ���Ʈ L1
	for (int i = 0; i < k / 2 - 1; i++) temp = temp->next;
	*L2 = temp->next;	//�θ���Ʈ L2�� ũ�� |L|-k�� ����� ����
	temp->next = NULL;	//�θ���Ʈ L1�� L2�� ����
}

ListNode* merge(ListNode** L1, ListNode** L2) {
	ListNode* mergedList = NULL;	//���� merged�� ����Ʈ
	ListNode* tempL1 = *L1;
	ListNode* tempL2 = *L2;

	while (tempL1 != NULL && tempL2 != NULL) {	//�� ����Ʈ �� �ϳ��� ���� �� ������
		if (tempL1->elem <= tempL2->elem) {	//����Ʈ ��� ��
			addList(&mergedList, tempL1->elem);	//���� ����Ʈ�� �� ���� �� �߰�
			tempL1 = tempL1->next;
		}

		else {
			addList(&mergedList, tempL2->elem);
			tempL2 = tempL2->next;
		}
	}

	//������ ���
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
		partition(temp, n, &L1, &L2);	//����

		if (n % 2 == 0) {	//����Ʈ ũ�Ⱑ ¦���� ���
			mergeSort(&L1, n / 2);
			mergeSort(&L2, n / 2);
		}

		else {	//����Ʈ ũ�Ⱑ Ȧ���� ���
			mergeSort(&L1, n / 2);
			mergeSort(&L2, (n / 2) + 1);
		}

		*L = merge(&L1, &L2);	//�պ�
	}
}

void addList(ListNode** L, int value) {	//��� �߰�
	ListNode* temp = *L;
	ListNode* newNode = (ListNode*)malloc(sizeof(ListNode));	//���ο� ��� ���� �� �Ҵ�
	newNode->next = NULL;
	newNode->elem = value;

	if (*L == NULL) *L = newNode;	//����Ʈ�� �� ����Ʈ�� ���
	else {
		while (temp->next != NULL) temp = temp->next;	//������ �̵�
		temp->next = newNode;
	}
}