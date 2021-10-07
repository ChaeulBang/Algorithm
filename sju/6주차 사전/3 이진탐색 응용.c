#include<stdio.h>
#include<stdlib.h>

//이진탐색 응용

void BinarySearch(char ch, int* a, int* b) {
	int m = (*a + *b) / 2;

	if (ch == 'Y') {
		*a = m + 1;
	}

	else {
		*b = m;
	}
}


int main() {
	int a, b, cnt;
	char answer;

	scanf("%d %d %d", &a, &b, &cnt);
	getchar();

	for (int i = 0; i < cnt; i++) {
		scanf("%c", &answer);
		BinarySearch(answer, &a, &b);
	}

	printf("%d", a);
}