#include<stdio.h>
#include<stdlib.h>
#include<malloc.h>

struct node
{
	int data;
	struct node *pNext;
};

struct stack
{
	struct node *pTop;
	struct node *pBom;
};
void initStack(struct stack *pStack);
void pushStack(struct stack *pStack, int val);
void traverseStack(struct stack *pStack);
int popStack(struct stack *pStack, int *pval);
int isEmpty(struct stack *pStack);

int main(int argc, const char *argv[])
{
	struct stack stack;	
	int popval;

	initStack(&stack);
	pushStack(&stack, 1);
	pushStack(&stack, 2);
	pushStack(&stack, 3);
	pushStack(&stack, 4);
	traverseStack(&stack);
	if(0 == popStack(&stack, &popval) )
		printf("pop failed,because of stack empty\n");
	else
		printf("pop sucess, and val is %d\n", popval);
	traverseStack(&stack);

	return 0;
}

void initStack(struct stack *pStack)
{
	pStack->pBom = (struct node *)malloc(sizeof(struct node)); 	
	if(NULL == pStack->pBom)
	{
		printf("allocate buffer failed!\n");
		exit(-1);
	}
	pStack->pTop = pStack->pBom;
	pStack->pBom->pNext = NULL; //最底下node的指针域为空
}

void pushStack(struct stack *pStack, int val)
{
	struct node *pNew = (struct node*)malloc(sizeof(struct node));
	if(NULL == pStack->pBom)
	{
		printf("allocate buffer failed!\n");
		exit(-1);
	}
	pNew->data = val;
	pNew->pNext = pStack->pTop;
	pStack->pTop = pNew;
}

void traverseStack(struct stack *pStack)
{
	struct node *pTemp;
	pTemp = pStack->pTop;
	while(pTemp != pStack->pBom)
	{
		printf("%d\n", pTemp->data);
		pTemp = pTemp->pNext;
	}
	printf("\n");
}

int isEmpty(struct stack *pStack)
{
	if(pStack->pTop == pStack->pBom)
		return 1;
	else
		return 0;	
}

int popStack(struct stack *pStack, int * pval)
{
	if( 1 == isEmpty(pStack) )		
	{
		return 0;	
	}
	else
	{
		struct node *pTemp = pStack->pTop;
		pStack->pTop = pStack->pTop->pNext;
		*pval = pTemp->data;
		free(pTemp);
		pTemp = NULL;

		return 1;
	}
}
