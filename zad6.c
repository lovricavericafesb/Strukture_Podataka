#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#include <string.h>

typedef struct Stog* Cvor;
typedef struct Stog {
	int element;
	Cvor next;
}Stog;

typedef struct Red* Pozicija;
typedef struct Red {
	int element;
	Pozicija next;
}Red;

int push(int El, Cvor S);
int pop(Cvor S);
int menu1(Cvor S);
int ispisStoga(Cvor S);
int menu2(Pozicija R);
int StaviURed(int element, Pozicija R);
int SkiniIzReda(Pozicija R);
int ispisReda(Pozicija R);

int main(void)
{
	Cvor headS;
	headS = (Cvor)malloc(sizeof(Stog));
	Cvor S;
	S = (Cvor)malloc(sizeof(Stog));
	headS->next = NULL;
	S = headS;

	Pozicija headR;
	headR = (Pozicija)malloc(sizeof(Red));
	Pozicija R;
	R = (Pozicija)malloc(sizeof(Red));
	headR->next = NULL;
	R = headR;

	int opcija = 0;
	int izbor = 0;

	printf("Odaberite opciju:\n");
	printf("\t1 Rad sa stogom\n");
	printf("\t2 Rad sa redom\n");
	scanf(" %d", &opcija);

	switch (opcija) {
	case(1):
		while (!izbor)
		{
			izbor = menu1(S);
		}
		break;
	case(2):
		while (!izbor)
		{
			izbor = menu2(R);
		}
		break;
	}

	

	return 0;
}
int menu1(Cvor S) {

	

	int izbor = 0;
	int element = 0;
	printf("\n********************************\n");
	printf("Odaberite zeljenu opciju:\n");
	printf("\t1 Unesite element na stog\n");
	printf("\t2 Skinite element sa stoga\n");
	printf("\t3 Ispis stoga\n");
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
		ispisStoga(S);
		return 0;
	case(3):
		ispisStoga(S);
		return 0;
	case(0):
		return 1;
	}
}
int menu2(Pozicija R) {
	int izbor = 0;
	int element = 0;
	printf("\n********************************\n");
	printf("Odaberite zeljenu opciju:\n");
	printf("\t1 Unesite element na red\n");
	printf("\t2 Skinite element sa reda\n");
	printf("\t3 Ispis reda\n");
	printf("\t0 Iskljuci program\n");
	scanf(" %d", &izbor);

	switch (izbor) {
	case(1):
		printf("\nUnesite element koji zelite staviti u red: ");
		scanf(" %d", &element);
		StaviURed(element, R);
		return 0;
	case(2):
		SkiniIzReda(R);
		ispisReda(R);
		return 0;
	case(3):
		ispisReda(R);
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
int StaviURed(int element, Pozicija R)
{
	Pozicija q;
	q = (Pozicija)malloc(sizeof(Red));

	q->element = element;
	if (R->next == NULL) {
		q->next = R->next;
		R->next = q;
	}
	else
	{
		Pozicija temp;
		temp = (Pozicija)malloc(sizeof(Red));
		temp = R;
		while (temp->next != NULL)
			temp = temp->next;

		q->next = temp->next;
		temp->next = q;
	}

	return 0;
}
int SkiniIzReda(Pozicija R)
{
	int x = 0;
	Pozicija temp1, temp2;
	temp1 = (Pozicija)malloc(sizeof(Red));
	temp2 = (Pozicija)malloc(sizeof(Red));

	if (R->next != NULL)
	{
		temp1 = R->next;
		temp2 = R->next;
		R->next = temp2->next;
		temp2 = R;
		x = temp1->element;
		free(temp1);
		printf("\nIz reda je izbacen element: %d\n", x);
		return 0;
	}
	else
	{
		printf("\nRed je prazan\n");
		return 0;
	}
	
}
int ispisStoga(Cvor S)
{
	Pozicija q;
	q = (Cvor)malloc(sizeof(Stog));

	q = S;
	if (q->next == NULL)
	{
		printf("\nNije moguc ispis praznog stoga!\n");
		return 0;
	}
	else
	{
		int velicinaStoga = 0;
		Cvor temp;
		temp = (Cvor)malloc(sizeof(Stog));
		temp = q->next;
		while (temp != NULL)
		{
			temp = temp->next;
			velicinaStoga++;
		}
		printf("\n");
		printf("Vas stog je:\n");
		q = q->next;
		while (q != NULL)
		{
			printf("\t%d. element: %d\n", velicinaStoga, q->element);
			q = q->next;
			velicinaStoga--;
		}
		return 0;
	}
}
int ispisReda(Pozicija R)
{
	Pozicija q;
	q = (Pozicija)malloc(sizeof(Red));

	q = R;
	if (q->next == NULL)
	{
		printf("\nNije moguce ispisati prazan red!\n");
		return 0;
	}
	else
	{
		int i = 1;
		q = q->next;
		printf("\n");
		printf("Vas red je:\n");
		while (q != NULL) {
			printf("\t%d. element reda: %d\n", i, q->element);
			i++;
			q = q->next;
		}
		return 0;
	}
}
