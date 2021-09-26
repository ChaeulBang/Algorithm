#include<stdio.h>
#include<stdlib.h>

typedef struct ListNode {	//리스트에 들어갈 노드
	char elem;
	struct ListNode* prev;
	struct ListNode* next;
} ListNode;

typedef struct ListType {
	int size;	//리스트의 크기
	ListNode* header;
	ListNode* trailer;
} ListType;

void add(ListType* list, int r, char e) {
	if (list->size + 1 < r) {			//현재 리스트의 크기 + 1 보다 순위가 클 때
		printf("invalid position\n");	//순위 정보 유효하지 않음
	}
	else {
		ListNode* newNode = malloc(sizeof(ListNode));	//새로운 노드 생성
		newNode->elem = e;

		if (list->size == 0) {			//비어있는 리스트일 경우
			newNode->next = list->trailer;
			newNode->prev = list->header;
			list->header->next = newNode;
			list->trailer->prev = newNode;
		}
		else if (list->size + 1 == r) {	//리스트의 끝에 노드를 추가할 때 trailer를 이용해 접근
			newNode->next = list->trailer;
			newNode->prev = list->trailer->prev;
			list->trailer->prev->next = newNode;
			list->trailer->prev = newNode;
		}
		else {							//그 외의 경우에 header를 이용해 접근
			int i;
			ListNode* visit = list->header;					//특정 노드 찾기 위함

			for (i = 0; i < r; i++) visit = visit->next;	//삽입 위치 찾기
			newNode->next = visit;
			newNode->prev = visit->prev;
			visit->prev->next = newNode;	
			visit->prev = newNode;
		}

		list->size++; //리스트에 노드를 추가했으므로 크기 + 1
	}
}

void delete(ListType* list, int r) {
	if (list->size < r) {				//현재 리스트 크기보다 순위가 클 때
		printf("invalid position\n");	//순위 정보 유효하지 않음
	}
	else {
		int i;
		ListNode* visit = list->header;					//특정 노드 찾기 위함

		for (i = 0; i < r; i++) visit = visit->next;	//삭제 위치 찾기
		visit->prev->next = visit->next;
		visit->next->prev = visit->prev;
		free(visit);

		list->size--; //리스트에서 노드를 삭제했으므로 크기 - 1
	}
}

void get(ListType* list, int r) {
	if (list->size < r) {				//현재 리스트 크기보다 순위가 클 때
		printf("invalid position\n");	//순위 정보 유효하지 않음
	}
	else {
		int i;
		ListNode* visit = list->header;					//특정 노드 찾기 위함

		for (i = 0; i < r; i++) visit = visit->next;	//위치 찾기
		printf("%c\n", visit->elem);
	}
}

void print(ListType* list) {
	if (list->size != 0) {
		ListNode* visit = list->header->next;

		while (visit != list->trailer) {
			printf("%c", visit->elem);
			visit = visit->next;
		}
		printf("\n");
	}
}


int main() {
	int i, num, rank;
	char ch, element;
	ListType* list;

	list = malloc(sizeof(ListType));			//리스트 생성
	list->size = 0;
	list->header = malloc(sizeof(ListNode));	//헤더 생성
	list->trailer = malloc(sizeof(ListNode));	//트레일러 생성
	
	scanf("%d", &num);
	getchar();

	for (i = 0; i < num; i++) {
		scanf("%c", &ch);
		getchar();

		if (ch == 'A') {		//add()
			scanf("%d %c", &rank, &element);
			getchar();
			add(list, rank, element);
		}
		else if (ch == 'D') {	//delete()
			scanf("%d", &rank);
			getchar();
			delete(list, rank);
		}
		else if (ch == 'G') {	//get()
			scanf("%d", &rank);
			getchar();
			get(list, rank);
		}
		else if (ch == 'P') {	//print()
			print(list);
		}
	}
	free(list->trailer);
	free(list->header);
	free(list);
}