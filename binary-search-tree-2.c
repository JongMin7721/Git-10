/*
 * Binary Search Tree #2
 *
 * Data Structures
 *
 * Department of Computer Science
 * at Chungbuk National University
 *
 */

#include <stdio.h>
#include <stdlib.h>



typedef struct node {
	int key;
	struct node *left;
	struct node *right;
} Node;

/* for stack */
#define MAX_STACK_SIZE		20
Node* stack[MAX_STACK_SIZE];
int top = -1;

Node* pop();
void push(Node* aNode);

/* for queue */
#define MAX_QUEUE_SIZE		20
Node* queue[MAX_QUEUE_SIZE];
int front = 0;
int rear = 0;

Node* deQueue();
void enQueue(Node* aNode);


int initializeBST(Node** h);

/* functions that you have to implement */
void recursiveInorder(Node* ptr);	  /* recursive inorder traversal */
void iterativeInorder(Node* ptr);     /* iterative inorder traversal */
void levelOrder(Node* ptr);	          /* level order traversal */
int insert(Node* head, int key);      /* insert a node to the tree */
int deleteNode(Node* head, int key);  /* delete the node for the key */
int freeBST(Node* head); /* free all memories allocated to the tree */

/* you may add your own defined functions if necessary */


void printStack();



int main()
{
	char command;
	int key;
	Node* head = NULL;

	do{
		printf("\n\n");
		printf("------------[      [Won Jong Min] [2019038014]      ]-----------\n");
		printf("----------------------------------------------------------------\n");
		printf("                   Binary Search Tree #2                        \n");
		printf("----------------------------------------------------------------\n");
		printf(" Initialize BST       = z                                       \n");
		printf(" Insert Node          = i      Delete Node                  = d \n");
		printf(" Recursive Inorder    = r      Iterative Inorder (Stack)    = t \n");
		printf(" Level Order (Queue)  = l      Quit                         = q \n");
		printf("----------------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command);

		switch(command) {
		case 'z': case 'Z':
			initializeBST(&head);
			break;
		case 'q': case 'Q':
			freeBST(head);
			break;
		case 'i': case 'I':
			printf("Your Key = ");
			scanf("%d", &key);
			insert(head, key);
			break;
		case 'd': case 'D':
			printf("Your Key = ");
			scanf("%d", &key);
			deleteNode(head, key);
			break;

		case 'r': case 'R':
			recursiveInorder(head->left);
			break;
		case 't': case 'T':
			iterativeInorder(head->left);
			break;

		case 'l': case 'L':
			levelOrder(head->left);
			break;

		case 'p': case 'P':
			printStack();
			break;

		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	}while(command != 'q' && command != 'Q');

	return 1;
}

int initializeBST(Node** h) {

	/* if the tree is not empty, then remove all allocated nodes from the tree*/
	if(*h != NULL)
		freeBST(*h);

	/* create a head node */
	*h = (Node*)malloc(sizeof(Node));
	(*h)->left = NULL;	/* root */
	(*h)->right = *h;
	(*h)->key = -9999;

	top = -1;

	front = rear = -1;

	return 1;
}



void recursiveInorder(Node* ptr)
{
	if(ptr) {
		recursiveInorder(ptr->left);
		printf(" [%d] ", ptr->key);
		recursiveInorder(ptr->right);
	}
}

/**
 * textbook: p 224
 */
void iterativeInorder(Node* node)
{
	while (1)
	{
		for (; node; node = node->left)	//노드의 왼쪽으로 이동하며 노드 저장
		{
			push(node);
		}
		node = pop();					//노드를 입력받아서
		if (!node)				//노드가 없다면
		{
			break;				//반복문 멈춤
		}
		printf(" [%d] ", node->key);	//노드의 값을 출력 후
		node = node->right;				//노드의 우측으로 이동
	}
	
}

/**
 * textbook: p 225
 */
void levelOrder(Node* ptr)
{
	if (!ptr)	//노드가 없다면
	{
		return;	//함수 종료
	}
	enQueue(ptr);	//노드를 큐에 입력
	while (1)
	{
		ptr = deQueue();	//큐에서 제일 먼저 입력한 노드를 빼내서
		if (ptr)	//노드가 있다면
		{
			printf(" [%d] ", ptr->key);	//노드의 값을 출력 후
			if (ptr->left)		//왼쪽노드가 있다면
			{
				enQueue(ptr->left);		//왼쪽 노드를 큐에 입력
			}
			if (ptr->right)		//오른쪽노드가 있다면
			{
				enQueue(ptr->right);	//오른쪽 노드를 큐에 입력
			}
		}
		else	//노드가 없다면
		{
			break;	//반복문 종료
		}
	}
	
}


int insert(Node* head, int key)
{
	Node* newNode = (Node*)malloc(sizeof(Node));
	newNode->key = key;
	newNode->left = NULL;
	newNode->right = NULL;

	if (head->left == NULL) {
		head->left = newNode;
		return 1;
	}

	/* head->left is the root */
	Node* ptr = head->left;

	Node* parentNode = NULL;
	while(ptr != NULL) {

		/* if there is a node for the key, then just return */
		if(ptr->key == key) return 1;

		/* we have to move onto children nodes,
		 * keep tracking the parent using parentNode */
		parentNode = ptr;

		/* key comparison, if current node's key is greater than input key
		 * then the new node has to be inserted into the right subtree;
		 * otherwise the left subtree.
		 */
		if(ptr->key < key)
			ptr = ptr->right;
		else
			ptr = ptr->left;
	}

	/* linking the new node to the parent */
	if(parentNode->key > key)
		parentNode->left = newNode;
	else
		parentNode->right = newNode;
	return 1;
}


int deleteNode(Node* head, int key)
{
	if (head == NULL || head->left == NULL)	//헤드가 없거나 노드가 없다면
	{
		printf("No Nodes!\n");	//노드가 없다고 출력
		return -1;
	}

	Node* n = head->left;		//현재노드

	Node* f = n;				//현재노드의 부모노드

	while (n != NULL)			//현재노드가 NULL이 아니라면 반복
	{
		if (n->key == key)		//현재 값과 노드의 값이 같다면
		{
			if (n->right == NULL && n->left == NULL)		//현재노드의 하위 노드가 없다면
			{
				if (f->right == n)		//부모노드와 현재노드의 연결을 NULL로 연결 후
				{
					f->right = NULL;
				}
				else if (f->left == n)
				{
					f->left = NULL;
				}
				free(n);			//현재노드 메모리 반환
				return 1;			//후 함수종료
			}

			if (n->left == NULL || n->right == NULL)		//현재노드의 하위노드가 하나라도 있다면
			{
				if (n->left != NULL)				//현재노드의 좌측노드가 있다면
				{
					if (f->right == n)				//부모노드와 현재노드의 좌측노드를 연결
					{
						f->right = n->left;
					}
					else if (f->left == n)			
					{
						f->left = n->left;
					}
				}

				if (n->right != NULL)			//현재노드의 우측에 있다면
				{
					if (f->right == n)			//부모노드와 현재노드의 우측노드를 연결 후
					{
						f->right = n->right;
					}
					else if (f->left == n)
					{
						f->left = n->right;
					}
				}
				free(n);					//현재노드 메모리 반환
				return 1;					//후 함수종료
			}


			if (n->left != NULL && n->right != NULL)		//현재노드의 하위노드가 둘 다 있다면
			{
				Node* ptr = n->right;		//이동하는 노드
				Node* pptr = n;				//이동하는 노드의 부모노드

				while (ptr->left != NULL)		//왼쪽 노드가 없을 때까지
				{
					pptr = ptr;					//부모노드 저장
					ptr = ptr->left;			//왼쪽으로 이동
				}

				if (ptr->right != NULL)			//현재노드의 우측노드중 제일 작은 값을 가진 노드가 우측노드를 가질 때
				{
					pptr->left = ptr->right;	//제일 작은 값의 노드의 부모와 우측노드를 연결
				}

				if (f->right == n)				//현재노드의 부모노드와 제일 작은 값의 노드를 연결
				{
					f->right = ptr;
				}
				else if (f->left == n)
				{
					f->left = ptr;
				}
				
				ptr->left = n->left;			//현재노드의 좌측을 제일 작은 값의 노드의 좌측으로 설정
				if (n->right != ptr)			//현재노드의 우측노드가 제일 작은 값의 노드가 아닐 때
				{
					ptr->right = n->right;		//현재노드의 우측을 그 노드의 우측으로 설정
				}
				free(n);				//현재노드 메모리 반환
				return 1;				//함수 종료
			}
			
		}

		f = n;				//부모노드 설정
		if (n->key < key)	//현재노드의 값과 입력받은 값을 비교 후 작은쪽으로 이동
		{
			n = n->right;
		}
		else
		{
			n = n->left;
		}
	}
	
	
	printf("No key in Nodes!\n");	//반복문이 끝나고도 찾지 못한다면 없다고 출력
	return 1;
	
	
}


void freeNode(Node* ptr)
{
	if(ptr) {
		freeNode(ptr->left);
		freeNode(ptr->right);
		free(ptr);
	}
}

int freeBST(Node* head)
{

	if(head->left == head)
	{
		free(head);
		return 1;
	}

	Node* p = head->left;

	freeNode(p);

	free(head);
	return 1;
}



Node* pop()
{
	if (top < 0)			//top이 0보다 작으면 NULL반환
	{
		printf(("No Nodes in Stack\n"));
		return NULL;
	}
	return stack[top--];	//스택의 최근값을 반환 후 top의 값 1 감소
}

void push(Node* aNode)
{
	stack[++top] = aNode;	//top에 1을 더한 후 스택에 입력받은 노드 입력
}



Node* deQueue()
{
	if (rear == front)		//front와 rear가 같다면 NULL반환
	{
		printf("No Nodes in Queue\n");	//큐에 노드가 없다고 출력
		return NULL;
	}
	front = front % MAX_QUEUE_SIZE;		//front에 front를 최대큐 크기로 나눈 나머지를 입력
	return queue[front++];				//큐의 맨 처음 값을 반환 후 front의 값 1 증가
}

void enQueue(Node* aNode)
{
	if ((rear + 1) % MAX_QUEUE_SIZE == front)			//rear에 1을 더한 값을 최대큐크기로 나눈 값이 front와 같다면
	{
		printf("No area in Queue\n");				//큐에 남은공간이 없다고 출력
		return;										//NULL반환
	}
	rear = rear % MAX_QUEUE_SIZE;		//rear에 rear를 최대큐크기로 나눈 나머지를 입력
	
	queue[rear++] = aNode;				//rear위치에 있는 큐값 반환 후 rear값 1 증가
}


void printStack()
{
	int i = 0;
	while (i <= top)		//0부터 현재Stack에 있는 모든 값을 출력
	{	
		printf(" [%d] [%d] \n", i, stack[i]->key);
		i++;
	}
}


