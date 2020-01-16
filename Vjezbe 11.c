/*
11. Napisati program koji generira 25 slucajnih brojeva u opsegu od 50 do 1000 i formira
od njih AVL stablo. Ispisati koji su sve brojevi generirani i na kraju formirano stablo.
*/
#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#include<time.h>

#ifdef _WIN64
#ifndef _CLRSCR
#define _CLRSCR "cls"
#endif
#elif _WIN32
#ifndef _CLRSCR
#define _CLRSCR "cls"
#endif
#else
#ifndef _CLRSCR
#define _CLRSCR "clear"
#endif
#endif

#ifndef ERROR
#define ERROR -1
#endif

#ifndef SUCCESS
#define SUCCESS 0
#endif

#ifndef BUFFER_LENGTH
#define BUFFER_LENGTH 1024
#endif

#ifndef MIN
#define MIN 50
#endif

#ifndef MAX
#define MAX 1000
#endif

#ifndef NUM_EL
#define NUM_EL 25
#endif

struct _node;
typedef struct _node *Pos;
typedef struct _node _NODE;
struct _node
{
	int Element;
	Pos Left;
	Pos Right;
	int Height;
};

int PrintError(char*);
int PrintMenu();
int RandomeGenerateInteger(int, int, int *);
Pos Insert(int, Pos, int*);
void Print(Pos);
int Height(Pos);
Pos SingleRotateWithLeft(Pos);
Pos SingleRotateWithRight(Pos);
Pos DoubleRotateWithLeft(Pos);
Pos DoubleRotateWithRight(Pos);
int Max(int, int);

int main(int argc, char *argv[])
{
	int result = SUCCESS;
	int min = MIN;
	int max = MAX;
	int numberOfElements = NUM_EL;
	int number = 0;
	int nCount = 0;
	int inserted = 0;
	Pos root = NULL;

	srand((unsigned)time(NULL));

	PrintMenu();

	PrintError("Generated numbers: ");
	printf("\r\n\t");
	while(nCount < numberOfElements)
	{
		inserted = 0;
		result = RandomeGenerateInteger(min, max, &number);
		if (result) continue;

		root = Insert(number, root, &inserted);
		if (!inserted) continue;

		nCount++;
		printf("%d ", number);
	}
	printf("\r\n\t");
	PrintError("************************************");
	PrintError("AVL tree records:");
	Print(root);

	printf("\r\n");
	return result;
}

int PrintError(char *message)
{
	if (message == NULL || strlen(message) == 0)
	{
		printf("\r\n\tUnknown error!");
	}
	else
	{
		printf("\r\n\t%s", message);
	}
	printf("\r\n");
	return SUCCESS;
}

int PrintMenu()
{
	printf("\r\n");
	printf("\t************************************\r\n");
	printf("\t***   VJEZBA BR. 11  -  AVL tree ***\r\n");
	printf("\t************************************\r\n");
	printf("\r\n");

	return SUCCESS;
}

int RandomeGenerateInteger(int min, int max, int *number)
{
	int range = max - min;

	if (range == 0) return ERROR;

	*number = rand() % range + min;

	return SUCCESS;
}

Pos Insert(int X, Pos T, int *inserted)
{
	if (NULL == T)
	{
		T = (Pos)malloc(sizeof(_NODE));
		T->Left = NULL;
		T->Right = NULL;
		T->Element = X;
		T->Height = 0;
		*inserted = 1;
	}
	else if (X > T->Element)
	{
		T->Right = Insert(X, T->Right, inserted);
		if (Height(T->Right) - Height(T->Left) == 2)
			if (X>T->Right->Element)
				T = SingleRotateWithRight(T);
			else
				T = DoubleRotateWithRight(T);
	}
	else if (X < T->Element)
	{
		T->Left = Insert(X, T->Left, inserted);
		if (Height(T->Left) - Height(T->Right) == 2)
			if (X<T->Left->Element)
				T = SingleRotateWithLeft(T);
			else
				T = DoubleRotateWithLeft(T);
	}
	else
	{
		*inserted = 0;
	}

	T->Height = Max(Height(T->Left), Height(T->Right)) + 1;
	return T;
}

void Print(Pos T)
{
	static int n = 0;
	int i;

	if (-1 == n)
		n = 0;

	if (NULL != T)
	{
		n++;
		Print(T->Right);

		printf("\n");
		for (i = 0; i < n; i++)
			printf("\t");

		printf(" %d", T->Element);

		printf("\n");
		n++;
		Print(T->Left);
	}
	n--;
}

int Height(Pos P)
{
	if (P == NULL)
		return -1;
	else
		return P->Height;
}

Pos SingleRotateWithLeft(Pos K2)
{
	Pos K1 = NULL;

	K1 = K2->Left;
	K2->Left = K1->Right;
	K1->Right = K2;

	K2->Height = Max(Height(K2->Left), Height(K2->Right)) + 1;
	K1->Height = Max(Height(K1->Left), K2->Height) + 1;

	return K1;
}

Pos SingleRotateWithRight(Pos K2)
{
	Pos K1 = NULL;

	K1 = K2->Right;
	K2->Right = K1->Left;
	K1->Left = K2;

	K2->Height = Max(Height(K2->Left), Height(K2->Right)) + 1;
	K1->Height = Max(K2->Height, Height(K1->Right)) + 1;

	return K1;
}

Pos DoubleRotateWithLeft(Pos K3)
{
	K3->Left = SingleRotateWithRight(K3->Left);

	return SingleRotateWithLeft(K3);
}

Pos DoubleRotateWithRight(Pos K3)
{
	K3->Right = SingleRotateWithLeft(K3->Right);

	return SingleRotateWithRight(K3);
}

int Max(int x, int y)
{
	if (x > y)
		return x;
	else
		return y;
}
