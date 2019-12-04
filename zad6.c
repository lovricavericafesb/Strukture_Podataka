#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#include <string.h>

typedef struct Stog* Cvor;
typedef struct Stog {
	int element;
	Cvor* next;
}Stog;

int push(int El, Cvor S);
int pop(Cvor S);
int menu(Cvor S);

int main(void)
{
	Cvor head;
	head = (Cvor)malloc(sizeof(Stog));
	Cvor S;
	S = (Cvor)malloc(sizeof(Stog));
	head->next = NULL;
	S = head;

	int izbor = 0;
	while (!izbor)
	{
		izbor = menu(S);
	}

	return 0;
}
int menu(Cvor S) {

	

	int izbor = 0;
	int element = 0;
	printf("\n********************************\n");
	printf("Odaberite zeljenu opciju:\n");
	printf("\t1 Unesite element na stog.\n");
	printf("\t2 Skinite element sa stoga.\n");
	printf("\t0 Iskljuci program\n");
	scanf(" %d", &izbor);

	switch (izbor) {
	case(1):
		printf("\nUnesite element koji zelite dodati na stog: ");
		scanf(" %d", &element);
		push(element, S);
		return 0;
	case(2):
		pop(S);
		return 0;
	case(0):
		return 1;
	}
}
int push(int element, Cvor S)
{
	Cvor q;
	q = (Cvor)malloc(sizeof(Stog));
	q->element = element;
	q->next = S->next;
	S->next = q;

	return 0;
}
int pop(Cvor S)
{
	Cvor temp1;
	Cvor temp2;
	temp1 = (Cvor)malloc(sizeof(Stog));
	temp2 = (Cvor)malloc(sizeof(Stog));
	int x = 0;
	if (S->next != NULL)
	{
		temp1 = S->next;
		temp2 = S->next;
		S->next = temp2->next;
		temp2 = S;
		x = temp1->element;
		free(temp1);
		printf("\nSa stoga je skinut element %d\n", x);
	}
	else {
		printf("\nStog je prazan!\n");
		return 0;
	}
}
