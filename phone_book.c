#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>

struct gPerson
{
	char name[20];
	long long num;
	struct gPerson * pNext;
};

struct gPerson *create_list();
void traverse_list(struct gPerson *);
int is_empty(struct gPerson *);
int length_list(struct gPerson *);
void sort_list(struct gPerson *);
int insert_list(struct gPerson *, int);
int delect_list(struct gPerson *, int);

int main(int argc, const char *argv[])
{
	int pos;
	struct gPerson *pHead = NULL;

	pHead = create_list();
	if(1 == is_empty(pHead))
	{
		printf("The list is empty\n");
		return 0;
	}
	else
	{
		printf("The node of list is %d\n", length_list(pHead));
		traverse_list(pHead);
		sort_list(pHead);
		traverse_list(pHead);
		printf("input addr of add list\n");
		scanf("%d", &pos);
		insert_list(pHead, pos);
		traverse_list(pHead);
		printf("input addr of delect list\n");
		scanf("%d", &pos);
		delect_list(pHead, pos);
		traverse_list(pHead);
	}
	
	return 0;
}

struct gPerson *create_list(void)
{
	int i, len;
	char name[20];
	long long num;
	struct gPerson *pHead, *pTail, *pNew;

	pHead = (struct gPerson *)malloc(sizeof(struct gPerson));
	if(NULL == pHead)
	{
		printf("allocate buffer failed!\n");
		exit(-1);
	}
	pTail = pHead;
	printf("Please input num of people\n");
	scanf("%d", &len);
	for(i=0; i<len; i++)	
	{
		printf("Please input name %dth people'name\n", i+1);
		scanf("%s", name);
		printf("Please input name %dth people'phonenum\n", i+1);
		scanf("%lld", &num);
		pNew = (struct gPerson *)malloc(sizeof(struct gPerson));
		if(NULL == pHead)
		{
			printf("allocate buffer failed!\n");
			exit(-1);
		}
//		pNew->name = name;
		strcpy(pNew->name, name);
		pNew->num = num;

		pTail->pNext = pNew;//also pHead->pNext=pNew
		pNew->pNext = NULL;
		pTail = pNew; 

	}
	printf("\n");

	return pHead;

}

void traverse_list(struct gPerson *pNode)
{
	struct gPerson * pTemp;
	pTemp = pNode->pNext;

	while(NULL != pTemp)
	{
		printf("name = %s, phonenum = %lld\n", pTemp->name, pTemp->num );
		pTemp = pTemp->pNext;
	}
	printf("\n");
}

int is_empty(struct gPerson *pHead)
{
	if(NULL == pHead->pNext)
		return 1;
	else
		return -1;
}
int length_list(struct gPerson *pHead)
{
	int i = 0;
	struct gPerson * pTemp;
	pTemp = pHead->pNext;
	while(NULL != pTemp)
	{
		i++;
		pTemp = pTemp->pNext;
	}

	return i;
}

void sort_list(struct gPerson *pHead)
{
	int i, j, len;
	long long temp;
	struct gPerson *pi, *pj;
	
	len = length_list(pHead);
	for(i=0,pi=pHead->pNext; i<len-1; i++,pi=pi->pNext)
	{
		for(j=i+1,pj=pi->pNext; j<len; j++,pj=pj->pNext)
		{
			if(pi->num > pj->num)	
			{
				temp = pi->num;
				pi->num = pj->num;
				pj->num = temp;
			}
		}
	}

}

int insert_list(struct gPerson *pHead, int pos)
{
	int i = 0;
	struct gPerson *pTemp = pHead;

	while(NULL!=pTemp && i<pos-1)
	{
		pTemp = pTemp->pNext;
		i++;
	}
	if(i>pos-1 || NULL==pTemp)
	{
		return -1;
	}

	struct gPerson *pNew = (struct gPerson *)malloc(sizeof(struct gPerson));
	if(NULL == pNew)
	{
		printf("allocate buffer failed!\n");
		exit(-1);
	}
	printf("Please input insert info\n");
	printf("Please input name people'name\n");
	scanf("%s", pNew->name);
	printf("Please input name people'phonenum\n");
	scanf("%lld", &(pNew->num) );
	
	pNew->pNext = pTemp->pNext;
	pTemp->pNext = pNew;

	return 0;
}

int delect_list(struct gPerson *pHead, int pos)
{
	int i = 0;
	struct gPerson *pTemp = pHead;

	while(NULL!=pTemp->pNext && i<pos-1)
	{
		pTemp = pTemp->pNext;
		i++;
	}
	if(i>pos-1 || NULL==pTemp->pNext)
	{
		return -1;
	}

	struct gPerson *pTemp1 = pTemp->pNext;
	pTemp->pNext = pTemp->pNext->pNext;
	free(pTemp1);
	pTemp1 = NULL;

	return 0;
}
