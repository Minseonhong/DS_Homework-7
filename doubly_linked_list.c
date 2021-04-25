#include<stdio.h>
#include<stdlib.h>
/* 필요한 헤더파일 추가 if necessary */


typedef struct Node { // listNode 구조체 생성
	int key;
	struct Node* llink;
	struct Node* rlink;
} listNode;



typedef struct Head { // headNode 구조체 생성
	struct Node* first;
}headNode;

/* 함수 리스트 */

/* note: initialize는 이중포인터를 매개변수로 받음
         singly-linked-list의 initialize와 차이점을 이해 할것 */
int initialize(headNode** h); // h에 직접 메모리 할당하는 함수

/* note: freeList는 싱글포인터를 매개변수로 받음
        - initialize와 왜 다른지 이해 할것
        - 이중포인터를 매개변수로 받아도 해제할 수 있을 것 */
int freeList(headNode* h); // h와 연결된 노드들 메모리 할당 해제

int insertNode(headNode* h, int key); // 입력값에 대한 노드를 추가하는 함수
int insertLast(headNode* h, int key); // 입력값을 마지막 노드 추가하여 넣는 함수
int insertFirst(headNode* h, int key); // 입력값을 맨 처음 노드에 추가하는 함수
int deleteNode(headNode* h, int key); // 입력값에 대한 노드 삭제하는 함수
int deleteLast(headNode* h); // 마지막 노드 삭제하는 함수
int deleteFirst(headNode* h); // 첫번째 노드 삭제하는 함수
int invertList(headNode* h); // 리스트의 링크를 역순으로 배치하는 함수

void printList(headNode* h); // 리스트의 노드를 출력하는 함수


int main()
{
	printf("[----- [민선홍] [2018038028] -----");
	char command; // 문자형 변수 command 생성
	int key; // 정수형 변수 key 생성
	headNode* headnode=NULL; //headNode형 포인터 구조체 headnode를 생성하여 NULL값 대입

	do{
		printf("----------------------------------------------------------------\n");
		printf("                     Doubly Linked  List                        \n");
		printf("----------------------------------------------------------------\n");
		printf(" Initialize    = z           Print         = p \n");
		printf(" Insert Node   = i           Delete Node   = d \n");
		printf(" Insert Last   = n           Delete Last   = e\n");
		printf(" Insert First  = f           Delete First  = t\n");
		printf(" Invert List   = r           Quit          = q\n");
		printf("----------------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command); // command값 입력

		switch(command) { // command의 입력 받은 값에 따라 switch 문 실행
		case 'z': case 'Z':
			initialize(&headnode); // 헤느도드에 직접 메모리 할당하는 함수 실행
			break;
		case 'p': case 'P':
			printList(headnode); // 리스트의 노드 출력하는 함수 실행
			break;
		case 'i': case 'I':
			printf("Your Key = ");
			scanf("%d", &key); // key의 값을 요청받음
			insertNode(headnode, key); // 노드의 값을 넣는 함수 실행
			break;
		case 'd': case 'D':
			printf("Your Key = ");
			scanf("%d", &key); // key의 값을 요청받음
			deleteNode(headnode, key); // 입력받은 노드의 값을 가지고 있는 노드 삭제하는 함수 실행
			break;
		case 'n': case 'N':
			printf("Your Key = ");
			scanf("%d", &key); // key의 값을 요청받음
			insertLast(headnode, key); // 연결리스트 맨 뒤에 값 추가하는 함수 실행
			break;
		case 'e': case 'E':
			deleteLast(headnode); // 연결리스트 맨 뒤에 있는 노드의 값 삭제하는 함수 실행
			break;
		case 'f': case 'F':
			printf("Your Key = ");
			scanf("%d", &key); // key의 값을 요청받음
			insertFirst(headnode, key); // 연결리스트 맨 처음에 값 추가하는 함수 실행
			break;
		case 't': case 'T':
			deleteFirst(headnode); // 연결리스트 맨 처음에 있는 노드 삭제하는 함수 실행
			break;
		case 'r': case 'R':
			invertList(headnode); // 역순으로 배치하는 함수 실행
			break;
		case 'q': case 'Q':
			freeList(headnode); // 노드 및 연결리스트를 해제하는 함수 실행
			break;
		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	}while(command != 'q' && command != 'Q');

	return 1;
}


int initialize(headNode** h) {

	if(*h!=NULL) //headNode가 NULL이 아니면, freeNode를 호출하여 할당된 메모리 모두 해제
		freeList(*h);

	*h = (headNode*)malloc(sizeof(headNode)); // headNode에 대한 메모리를 직접 *h에 할당
	(*h) -> first = NULL;


	return 1;
}

int freeList(headNode* h){ // h와 연결된 노드 메모리 해제, headNode도 해제

	listNode *p = h->first;

	listNode *prev = NULL;
	while (p != NULL)
	{
		prev = p;
		p = p -> rlink;
		free(prev);
	}
	free(h);
	return 0;
}


void printList(headNode* h) {
	int i = 0;
	listNode* p;

	printf("\n---PRINT\n");

	if(h == NULL) { //h 가 NULL일경우 종료
		printf("Nothing to print....\n");
		return ;
	}

	p = h->first; // 포인터 변수p 에 h -> first 값 대입

	while(p != NULL) { // p가 NULL이 아닐경우 p -> key의 값을 출력한 뒤 p -> link값을 변경하면서 p의 값이 NULL이 될때 까지 반복
		printf("[ [%d]=%d ] ", i, p->key);
		p = p->rlink;
		i++;
	}

	printf("  items = %d\n", i); // 개수를 출력
}




/**
 * list에 key에 대한 노드하나를 추가
 */
int insertLast(headNode* h, int key) {

	listNode* node = (listNode*)malloc(sizeof(listNode)); // 포인터 변수 node에 메모리 할당
	node -> key = key; // 입력값을 node -> key 에 대입
	node -> rlink = NULL; // node -> rlink 의 값은 NULL

	listNode *p = h -> first; // 포인터 변수 p에  h -> first 대입

	if(h -> first == NULL) // 헤더노드가 NULL 일 경우
	{
		node -> rlink = h -> first; // node -> rlink 값에 헤더노드 대입
		h -> first = node; // h -> first 에 node 대입
		node -> llink = h -> first; // node -> link 값에 헤더 노드 대입

		return 0;
	}
	else
	{
		while(p -> rlink != NULL) // p -> rlink의 값이 NULL 될 때 까지 반복
		{
			p = p -> rlink; // 포인터 변수 p에 p -> rlink 값 대입
		}
		p -> rlink = node; // p -> rlink 값에 node 대입
		node -> llink = p; // node -> link 값에 p 대입
	}
	return 0;
}



/**
 * list의 마지막 노드 삭제
 */
int deleteLast(headNode* h) {

	listNode *del = (listNode*)malloc(sizeof(listNode)); //포인터 변수 del에 메모리 할당
	listNode *p = h -> first; // 포인터 변수 p에 헤더노드값 대입
	listNode *prev = NULL; // 포인터 변수 prev를 선언하고 NULL 값 대입

	while(p -> rlink != NULL) // p -> rlink의 값이 NULL이 될 떄 까지 반복
	{
		prev = p; // prev에 p의 값 대입
		p = p -> rlink; // p에 p -> rlink의 값을 대입
	}

	del = p; // del에 p의 값 대입
	free(del); // p가 대입 되어있는 del 메모리 해제
	prev -> rlink = NULL; // prve -> rlink의 값을 NULL 대입
	return 0;
}



/**
 * list 처음에 key에 대한 노드하나를 추가
 */
int insertFirst(headNode* h, int key) {

	listNode * node = (listNode*)malloc(sizeof(listNode)); // node 메모리 할당
	node -> key = key; // node -> key 값에 key의 값 대입
	node -> rlink = NULL; // node -> rlink 값 NULL 대입
	node -> llink = NULL; // node -> llink 값 NULL 대입

	node -> rlink = h -> first; // node -> rlink 값에 헤더노드 대입
	h -> first = node; // 헤더노드에 node 대입
	node -> llink = h -> first; // node -> llink에 node의 값이 대입되어있는 헤더노드 대입

	return 0;
}

/**
 * list의 첫번째 노드 삭제
 */
int deleteFirst(headNode* h) {

	listNode* del = (listNode*)malloc(sizeof(listNode)); // 포인터 변수 del 메모리 할당
	listNode* p = h -> first; // 포인터 변수 p에 헤더노드 대입

	del = h -> first; // del에 헤더노드 대입
	p = p -> rlink; // p에 p -> rlink값 대입

	free(del); // 헤더노드가 대입되어있는 del 메모리 해제
	h -> first = p; // 헤더노드에 p 대입
	p -> llink = h -> first; // p -> llink에 p값이 대입되어있는 헤더노드 대입

	return 0;
}



/**
 * 리스트의 링크를 역순으로 재 배치
 */
int invertList(headNode* h) {

	listNode *p, *q, *r; // listNode에 포인터 변수 p q r 생성
	p = h -> first; // p에 헤더노드 값 대입
	q = NULL; // q에 NULL 대입
	r = NULL; // r에 NULL 대입
	while (p != NULL) // p의 값이 NULL이 될 때 까지 반복
	{
		r = q; // r에 q값 대입
		q = p; // q에 p값 대입
		p = p -> rlink; // p에 p -> rlink 값 대입
		q -> rlink = r; // q -> rlink에 q값이 들어가 있는 r 대입
	}
	h -> first = q; // 헤더노드에 q 대입
	return 0;
}



/* 리스트를 검색하여, 입력받은 key보다 큰값이 나오는 노드 바로 앞에 삽입 */
int insertNode(headNode* h, int key) {

	listNode *node = (listNode*)malloc(sizeof(listNode)); // listNode의 포인터 변수 node 메모리 할당
	node -> key = key; // node -> key 값에 key 값 대입
	node -> rlink = NULL; // node -> rlink에 NULL 대입

	listNode* p; // listNode 포인터 변수 p 생성
	p = h -> first; // p에 헤더노드 대입
	listNode *prev; // listNode 포인터 변수 prev 생성
	prev = NULL; // prev에 NULL 값 대입

	if( h -> first == NULL) // 헤더노드 NULL일 경우
	{
		node -> rlink = h -> first; // node -> rlink에 헤더노드 대입
		h -> first = node; // 헤더노드에 node 값 대입
		node -> llink = h -> first; // node -> llink에 node의 값이 들어가있는 헤더노드 대입
		return 0;
	}

	else
	{
		prev = p; // prev에 p의 값 대입
		p = p -> rlink; // p에 p -> rlink 값 대입

		if (prev -> key >= node -> key) // prev -> key의 값이 node -> key 값보다 크거나 같으면
		{
			node -> rlink = h -> first; // node -> rlink에 헤더노드 대입
			h -> first = node; // 헤더노드에 node 값 대입
			node -> llink = h -> first; // node -> llink에 node의 값이 들어가 있는 헤더노드 대입
		}
		else if (p == NULL) // p가 NULL일 경우
		{
			prev -> rlink = node; // prev -> rlink에 node의 값 대입
			node -> llink = prev; // node -> llink에 prev의 값 대입
		}
		else if (p -> key >= node -> key) // p -> key의 값이  node -> key값 보다 크거나 같으면
		{
			node -> rlink = p; // node -> rlink에 p의 값 대입
			node -> llink = prev; // node -> llink에 prev의 값 대입
			prev -> rlink = node; // prev -> rlink에 node의 값 대입
			p -> llink = node; // p -> llink에 node의 값 대입
		}
	}
	return 0;
}


/**
 * list에서 key에 대한 노드 삭제
 */
int deleteNode(headNode* h, int key) {

	listNode *del = (listNode*)malloc(sizeof(listNode)); // listNode의 포인터 변수 del 메모리 할당
	listNode *prev; // listNode의 포인터변수 prev 생성
	listNode *p; // listNode의 포인터변수 p 생성
	prev = NULL; // prev에 NULL 값 대입
	p = h -> first; // p에 헤더노드 대입

	if(h -> first == NULL){ // 헤더노드가 NULL이면 문구출력하고 종료
		printf("키와 같은 값을 찾을 수 없습니다.");
		return 0;
	}
	else // 아니면
	{
		prev = p; // prev에 p 값 대입
		p = p -> rlink; // p에 p -> rlink의 값 대입

		if(prev -> key == key) // prev -> key의 값이 key의 값과 같으면
		{
			del = prev; // del에 prev 값 대입
			free(del); // del 메모리 해제
			h -> first = p; // 헤더노드에 p의 값 대입
		}
		else if(prev -> rlink == NULL) // prev -> rlink가 NULL일 경우 없다는 문구 출력
		{
			printf("키와 같은 값을 찾을 수 없습니다.");
		}
		else if(p -> key == key) // p -> key의 값이 key와 같을 경우
		{
			prev -> rlink = p -> rlink; // prev -> rlink에 p -> rlink 값 대입

			if(p -> rlink == NULL) // p -> rlink의 값이 NULL일 경우
			{
				del = p; // del에 p의값 대입
				free(del); // d의 값이 들어가있는 del 메모리 해제
			}
			else // 아니면
			{
				p -> rlink -> llink = prev; // p -> rlink -> llink에 prev 값 대입
				del = p; // del에 p의 값 대입
				free(del); // p의 값이 들어가있는 del 메모리 해제
			}
		}
		else if (p -> rlink == NULL) // p -> rlink의 값이 NULL이면 없다는 문구 출력
		{
			printf("키와 같은 값을 찾을 수 없습니다.");
		}
	}

	return 1;
}


