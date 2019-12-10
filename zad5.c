#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>
#include <ctype.h>
#define MAX_LINE 1024

struct Lista;
typedef struct Lista* lista;
typedef struct Lista {
	int el;
	lista next;
}Lista;

int CitajIzDat(lista head);
int Stvori_Clan(lista head);
int ispis(lista head);
int Unija(lista head1, lista head2, lista headU);
int Stvori_Uniju(int element, lista headU);
int Presjek(lista head1, lista head2, lista headP);

int main()
{
	lista head1;
	lista head2;
	lista head_Unija;
	lista head_Presjek;

	head1 = (lista)malloc(sizeof(Lista));
	head2 = (lista)malloc(sizeof(Lista));
	head_Unija = (lista)malloc(sizeof(Lista));
	head_Presjek = (lista)malloc(sizeof(Lista));

	head1->next = NULL;
	head2->next = NULL;
	head_Unija->next = NULL;
	head_Presjek->next = NULL;

	CitajIzDat(head1);
	CitajIzDat(head2);

	printf("\nPrva lista: ");
	ispis(head1);
	printf("\n*************************************************************\n");
	printf("Druga lista: ");
	ispis(head2);
	printf("\n*************************************************************\n");
	
	Unija(head1, head2, head_Unija);
	printf("Unija: ");
	ispis(head_Unija);
	printf("\n*************************************************************\n");

	Presjek(head1, head2, head_Presjek);
	printf("Presjek: ");
	ispis(head_Presjek);
	printf("\n");

	return 0;
}
int CitajIzDat(lista head)
{
	lista novi_clan;

	char* filename;
    filename = (char*)malloc(sizeof(char) * MAX_LINE);

	FILE* fp = NULL;
	
	printf("\nUnesite ime datoteke u kojoj se nalaze liste: ");
	scanf(" %s", filename);

	if (strchr(filename, '.') == NULL) {
		strcat(filename, ".txt");
	}

	fp = fopen(filename, "r");
	if (fp == NULL) {
		printf("Nije moguce otvoriti upisanu datoteku!");
		return 0;
	}

	while (!feof(fp)) {
		novi_clan = Stvori_Clan(head);
		fscanf(fp ," %d", &novi_clan->el);
	}

	fclose(fp);

	return 0;
}
int Stvori_Clan(lista head)
{
	lista novi_clan, temp1;
	novi_clan = (lista)malloc(sizeof(Lista));

	temp1 = head;

	while (temp1->next != NULL)
		temp1 = temp1->next;

	novi_clan->next = temp1->next;
	temp1->next = novi_clan;
	
	return novi_clan;
}
int ispis(lista head)
{
	lista temp1;
	temp1 = head->next;
	
	if (temp1 == NULL) {
		printf("\nLista je prazna!\n");
		return 0;
	}

	while (temp1 != NULL)
	{
		printf("\t%d", temp1->el);
		temp1 = temp1->next;
	}

	return 0;
	
}
int Unija(lista head1, lista head2, lista headU)
{
	lista temp1 = head1->next, temp2 = head2->next;

	while (temp1 != NULL && temp2 != NULL)
	{
		if (temp1->el == temp2->el) {
			Stvori_Uniju(temp1->el, headU);
			temp1 = temp1->next;
			temp2 = temp2->next;
		}
		else if (temp1->el < temp2->el) {
			Stvori_Uniju(temp1->el, headU);
			temp1 = temp1->next;
		}
		else {
			Stvori_Uniju(temp2->el, headU);
			temp2 = temp2->next;
		}
	}
	if (temp1 != NULL) {
		while (temp1 != NULL) {
			Stvori_Uniju(temp1->el, headU);
			temp1 = temp1->next;
		}
	}
	else if (temp2 != NULL) {
		while (temp2 != NULL) {
			Stvori_Uniju(temp2->el, headU);
			temp2 = temp2->next;
		}
	}

	return 0;
}
int Stvori_Uniju(int element, lista headU)
{
	lista novi_clan, temp;
	novi_clan = (lista)malloc(sizeof(Lista));

	temp = headU;
	while (temp->next != NULL)
		temp = temp->next;

	novi_clan->next = temp->next;
	temp->next = novi_clan;
	novi_clan->el = element;

	return 0;
	
}
int Presjek(lista head1, lista head2, lista headP)
{
	lista temp1 = head1->next, temp2 = head2->next;

	while (temp1 != NULL) {
		while (temp2 != NULL) {
			if (temp1->el == temp2->el) {
				Stvori_Uniju(temp1->el, headP);
				temp1 = temp1->next;
				temp2 = temp2->next;
			}
			else
				temp2 = temp2->next;
		}
		temp1 = temp1->next;
		temp2 = head2->next;
	}

	return 0;
}
