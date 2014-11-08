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
bool is_empty();

int main(int argc, const char *argv[])
{
	struct gPerson *pHead = NULL;

	pHead = create_list();
	traverse_list(pHead);
	
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
