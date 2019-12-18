#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <malloc.h>
#include <stdlib.h>
#define MAX_NAME 50

typedef struct Stablo* Cvor;
typedef struct Stablo {
	char name_stablo[MAX_NAME];
	Cvor sibling;
	Cvor child;
}Stablo;

typedef struct Stog* Pozicija;
typedef struct Stog {
	Cvor pokazivac_stablo;
	Pozicija next;
}Stog;

int menu(Cvor);
Cvor CreateRootStablo(Cvor , char*);
int CreateElementStablo(Cvor);
Pozicija CreateStogHead(Pozicija, char*);
int CreateStogElement(Pozicija, Cvor);
int ispis(Cvor);
Cvor TraziPoImenu(Cvor, char*);
Cvor VratiUnazad(Pozicija);
int StaviNaStog(Cvor);

int main()
{
	Cvor root = NULL;   //deklaracija root elementa
	char* root_name = "root";   //ime root elementa
	root = CreateRootStablo(root, root_name);  //pravljenje root elementa u stablu

	Pozicija head_stog;
	head_stog = (Pozicija)malloc(sizeof(Stog));
	head_stog->next = NULL;
	head_stog->pokazivac_stablo = NULL;


	int odluka = 1;

	do
	{
		odluka = menu(root, head_stog);
	} while (odluka);


	return 0;
}

int menu(Cvor root, Pozicija head)
{
	char izbor[MAX_NAME];
	Pozicija temp;
	temp = (Pozicija)malloc(sizeof(Stog));
	temp->next = head->next;
	temp->pokazivac_stablo = root;
	head->next = temp;
	char* name;
	name = (char*)malloc(MAX_NAME * sizeof(char));

	printf("\nOdaberite zeljeno:\n");
	printf("\t1. Za ispis liste datoteka vaseg direktorija: dir\n");
	printf("\t2. Za vracanje u prethodni direktorij: cd..\n");
	printf("\t3. Za stvaranje novog direktorija: md \n");
	printf("\t4. Za otvaranje direktorija: cd \n");
	printf("\t5. Za iskljucivanje programa: quit\n");
	scanf(" %s", &izbor);

	if (strcmp(izbor, "dir") == 0)
	{
		ispis(temp->pokazivac_stablo);
		return 1;
	}
	else if (strcmp(izbor, "cd") == 0)
	{
		
		printf("Unesite ime direktorija: ");
		scanf("%s", name);
		temp->pokazivac_stablo = TraziPoImenu(temp->pokazivac_stablo, name);
		printf("\nOtvorili ste %s direktorij\n", temp->pokazivac_stablo->name_stablo);
		CreateStogElement(head, temp->pokazivac_stablo);
		ispis(temp->pokazivac_stablo);
		return 1;
	}
	else if (strcmp(izbor, "md") == 0)
	{
		
		CreateElementStablo(temp->pokazivac_stablo);

		return 1;
	}
	else if (strcmp(izbor, "quit") == 0)
	{
		return 0;
	}
	else if (strcmp(izbor, "cd..") == 0) {
		temp->pokazivac_stablo = VratiUnazad(head);
		return 1;
	}
	else {
		printf("\nNeispravan unos, pokusajte opet!");
		return 1;
	}
}

Cvor CreateRootStablo(Cvor root, char* name)
{
	root = (Cvor)malloc(sizeof(Stablo));
	root->sibling = NULL;
	root->child = NULL;
	strcpy(root->name_stablo, name);
	

	return root;
}


int CreateElementStablo(Cvor ParentElement)
{
	if (ParentElement->child == NULL)
	{
		Cvor new_element;
		new_element = (Cvor)malloc(sizeof(Stablo));
		ParentElement->child = new_element;
		new_element->child = NULL;
		new_element->sibling = NULL;
		printf("\nUnesite ime novog direktorija: ");
		scanf("%s", new_element->name_stablo);

		return 0;
	}

	else {
		Cvor temp = ParentElement->child;
		while (temp->sibling != NULL)
			temp = temp->sibling;
		Cvor new_element;
		new_element = (Cvor)malloc(sizeof(Stablo));
		temp->sibling = new_element;
		new_element->child = NULL;
		new_element->sibling = NULL;
		printf("\nUnesite ime novog direktorija: ");
		scanf("%s", new_element->name_stablo);
		free(temp);

		return 0;
	}
}


int CreateStogElement(Pozicija head_stog, Cvor stablo_element)
{
	Pozicija new_element;
	new_element = (Pozicija)malloc(sizeof(Stog));
	new_element->pokazivac_stablo = stablo_element;
	new_element->next = head_stog->next;
	head_stog->next = new_element;

	return 0;
}
int ispis(Cvor Parent)
{
	Cvor temp = Parent->child;
	if (temp == NULL)
	{
		printf("\n%s direktorij je prazan!", Parent->name_stablo);
		return 0;
	}
	else {
		printf("\nU %s direktoriju se nalaze sljedece datoteke: ", Parent->name_stablo);
		while (temp != NULL)
		{
			int i = 1;
			printf("\n\t%d. %s", i, temp->name_stablo);
			temp = temp->sibling;
		}
		printf("\n");
		return 0;
	}
}
Cvor TraziPoImenu(Cvor parent, char* name)
{
	Cvor element = parent->child;
	if (!element)
	{
		printf("\nGreska pri pronalazenju elemnta stabla!\n");
		return 0;
	}
	else {
		while (strcmp(element->name_stablo, name) != 0)
			element = element->sibling;
		if (element == NULL)
		{
			printf("\nElement nije pronadjen!\n");
			return 0;
		}
		else {
			return element;
		}
	}
}
Cvor VratiUnazad(Pozicija head)
{
	if (head->next == NULL)
	{
		printf("\nNalazite se u osnovnom direktoriju i nije moguce iz njega izaci!\n");
		return 0;
	}
	else {
		Pozicija q = head->next;
		head->next = head->next->next;

		free(q);
		printf("\nSada ste u %s direktoriju\n", head->next->pokazivac_stablo->name_stablo);
		return head->next->pokazivac_stablo;
	}
}
