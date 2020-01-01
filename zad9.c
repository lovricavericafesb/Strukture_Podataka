#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <malloc.h>
#include <string.h>

typedef struct CvorStabla* Stablo;
typedef struct CvorStabla {
	int element;
	Stablo lijevo;
	Stablo desno;
}CvorStabla;

int menu(Stablo root);
int DodajElement(int vrijednost, Stablo root);
int ispis(Stablo root);
Stablo PronadjiElement(int vrijednost, Stablo root);
int brisi(int vrijednost, Stablo root);
Stablo brisiRoot(Stablo root);

int main(void)
{
	Stablo root;
	root = (Stablo)malloc(sizeof(CvorStabla));
	printf("\nUnesite vrijednost root elementa: ");
	scanf(" %d", &root->element);
	root->desno = NULL;
	root->lijevo = NULL;

	int odabir = 0;
	while (!odabir)
	{
		odabir = menu(root);
	}

	return 0;
}

int menu(Stablo root)
{
	int izbor = 0;
	printf("\nOdaberite neku od navedenih opcija:\n");
	printf("1. Unos elementa u stablo\n");
	printf("2. Ispis elemenata\n");
	printf("3. Brisanje elementa\n");
	printf("4. Pronalazenje elementa\n");
	printf("0. Izlaz iz programa\n");
	scanf(" %d", &izbor);

	switch (izbor) {
	case(1): {
		int element = 0;
		printf("\nUnesite vrijednost novog elementa: ");
		scanf(" %d", &element);
		DodajElement(element, root);
		return 0;
	}
	case(2): {
		printf("\nVase stablo se sastoji od sljedecih elemenata:\n");
		ispis(root);
		printf("\n");
		return 0;
	}
	case(3): {
		int element = 0;
		printf("\nUnesite vrijednost elementa kojeg zelite izbrisati: ");
		scanf(" %d", &element);
		if (root->element != element)
			brisi(element, root);
		else
			root = brisiRoot(root);
		return 0;
	}
	case(4): {
		int element = 0;
		printf("\nUnesite vrijednost elementa koji zelite pronaci: ");
		scanf(" %d", &element);
		Stablo temp = PronadjiElement(element, root);
		if (temp != NULL)
		{
			printf("\nElement %d je pronadjen\n", temp->element);
			return 0;
		}
		else {
			printf("\nElement nije pronadjen\n");
			return 0;
		}
	}
	case(0):
		return 1;
	}

}

int DodajElement(int vrijednost, Stablo root)
{
	Stablo temp = root;
	Stablo temp_prev = root;
	while (temp != NULL)
	{
		if (temp->element > vrijednost) {
			temp_prev = temp;
			temp = temp->lijevo;
		}
		else if (temp->element < vrijednost) {
			temp_prev = temp;
			temp = temp->desno;
		}
		else {
			printf("\nTaj element se vec nalazi u stablu!\n");
			return 0;
		}
	}
	if (temp == NULL)
	{
		Stablo new_element;
		new_element = (Stablo)malloc(sizeof(CvorStabla));
		if (temp_prev->element > vrijednost) {
			new_element->element = vrijednost;
			temp_prev->lijevo = new_element;
			new_element->desno = NULL;
			new_element->lijevo = NULL;
			return 0;
		}
		else if (temp_prev->element < vrijednost)
		{
			new_element->element = vrijednost;
			temp_prev->desno = new_element;
			new_element->desno = NULL;
			new_element->lijevo = NULL;
			return 0;
		}
		else {
			printf("\nGreska pri unosu novog elementa!");
			return 0;
		}

	}
	
}
int ispis(Stablo cvor)
{
	if (cvor != NULL)
	{
		printf("%d\t", cvor->element);
		ispis(cvor->desno);
		ispis(cvor->lijevo);
		return 0;
	}
	else
		return 0;

}

Stablo PronadjiElement(int vrijednost, Stablo root)
{
	Stablo cvor = root;
	if (cvor == NULL)
		return cvor;
	else if (cvor->element < vrijednost)
		cvor = PronadjiElement(vrijednost, cvor->desno);
	else if (cvor->element > vrijednost)
		cvor = PronadjiElement(vrijednost, cvor->lijevo);

	return cvor;
		
}
int brisi(int vrijednost, Stablo cvor)
{
	if (cvor->element > vrijednost)
		cvor->lijevo = brisi(vrijednost, cvor->lijevo);
	else if (cvor->element < vrijednost)
		cvor->desno = brisi(vrijednost, cvor->desno);
	else if (cvor->element == vrijednost)
	{
		free(cvor);
		return NULL;
	}
	return cvor;
}
Stablo brisiRoot(Stablo root)
{
	if (root->desno == NULL)
	{
		root = root->lijevo;
		return root;
	}
	Stablo temp = root->desno;
	if (temp->lijevo == NULL)
	{
		root->element = temp->element;
		root->desno = temp->desno;
		return root;
	}
	while (temp->lijevo->lijevo != NULL)
		temp = temp->lijevo;
	root->element = temp->lijevo->element;
	temp->lijevo = NULL;
	return root;
	
}
