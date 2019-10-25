/*
Zadatak 2.
Definirati strukturu osoba (ime, prezime, godina roðenja) i napisati program koji:
a) dinamièki dodaje novi element na poèetak liste,
b) ispisuje listu,
c) dinamièki dodaje novi element na kraj liste,
d) pronalazi element u listi (po prezimenu),
e) briše odreðeni element iz liste,
U zadatku se ne smiju koristiti globalne varijable.
*/
#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#include<malloc.h>
#define BUFFER_LENGTH 1024
#define ERROR -1
#define SUCCESS 0

typedef struct _student* Pozicija;
typedef struct _student _STUDENT;
struct _student
{
	char ime[BUFFER_LENGTH];
	char prezime[BUFFER_LENGTH];
	int godina_rodenja;
	Pozicija next;
}student;

int PrintMenu();
int CreateListNode(Pozicija *);
int Unos_Student(Pozicija);
int Unos_Pocetak_Liste(Pozicija);
int PrintList(Pozicija);
Pozicija FindLast(Pozicija);
int InsertEnd(Pozicija);
Pozicija FindPrezime(Pozicija);
int Delete_Prezime(Pozicija);
int GarbageCollector(Pozicija);

int main(void)
{
	_STUDENT head; //kreiramo head element liste
	Pozicija studentF = NULL; // postavljamo studentF->next na NULL
	char *izbor = NULL;

	head.next = NULL; //postavljamo da nam head element liste trenutni pokazuje na NULL
	izbor = (char*)malloc(sizeof(char) * BUFFER_LENGTH);
	if (izbor == NULL) return ERROR;
	memset(izbor, '\0', BUFFER_LENGTH); //postavljamo iznos na prazna skup (da se osiguramo)

	while (strcmp(izbor, "EXIT") != 0) //vrtimo programo dok ne odlučimo završiti s njin
	{
		memset(izbor, 0, BUFFER_LENGTH); //svaki put kada ponovimo funkciju moramo vratit izbor na nulu

		PrintMenu(); //printa meni

		scanf(" %s", izbor);

		if (strcmp(izbor, "1") == 0)
		{
			Unos_Pocetak_Liste(&head); 
		}
		else if (strcmp(izbor, "2") == 0)
		{
			PrintList(head.next); 
		}
		else if (strcmp(izbor, "3") == 0)
		{
			InsertEnd(&head); 
		}
		else if (strcmp(izbor, "4") == 0)
		{
			studentF = FindPrezime(head.next);
			if (studentF != NULL)
				printf("\r\nTrazeni student je :\r\n%s %s %d\r\n", studentF->ime, studentF->prezime, studentF->godina_rodenja);
			else
				printf("\r\nStudent s trazenim prezimenom nije pronaden\r\n");
		}
		else if (strcmp(izbor, "5") == 0)
		{
			Delete_Prezime(&head);//
			PrintList(head.next);
		}
		else if (strcmp(izbor, "EXIT") == 0)
		{//Do Nothing
			break;
		}
		else
		{
			printf("\r\nPogresan izbor <%s>.\r\nPokusajte ponovno.\r\n", izbor);
		}
	}

	free(izbor);
	GarbageCollector(head.next);

	return SUCCESS;
}

int PrintMenu()
{
	printf("\t*********************************************\r\n");
	printf("\t***   VJEZBA BROJ 2 - Vezane liste ***\r\n");
	printf("\t*********************************************\r\n");
	printf("\r\n\r\n");
	printf("\t\t1. Unos\r\n");
	printf("\t\t2. Ispis\r\n");
	printf("\t\t3. Unos na kraj\r\n");
	printf("\t\t4. Pronadji po prezimenu\r\n");
	printf("\t\t5. Izbrisi po prezimenu\r\n");

	return SUCCESS;
}


int CreateListNode(Pozicija *head)
{
	Pozicija Q = NULL;

	*head = (Pozicija)malloc(sizeof(_STUDENT));
	if (*head == NULL) return ERROR;

	Q = *head;
	Q->next = NULL;

	return SUCCESS;
}

int Unos_Student(Pozicija P)
{
	if (P == NULL) return ERROR;

	printf("\r\n\tUnesite ime, prezime i godinu rodenja studenta :\r\n\t");
	scanf(" %s %s %d", P->ime, P->prezime, &P->godina_rodenja);

	return SUCCESS;
}

int Unos_Pocetak_Liste(Pozicija P)
{
	int error = ERROR;
	Pozicija Q = NULL;

	error = CreateListNode(&Q);
	if (error)
	{
		printf("\r\nGRESKA!\r\nAlokacija memorije nije uspjela.\r\n");
		return ERROR;
	}

	error = Unos_Student(Q);
	if (error)
	{
		printf("\r\nGRESKA!\r\nUnos korisnickih podataka nije uspjesan.\r\n");
		return ERROR;
	}

	Q->next = P->next;
	P->next = Q;

	return SUCCESS;
}

int PrintList(Pozicija P)
{
	if (P == NULL)
		printf("\r\n\tLista je prazna!\r\n");
	else
	{
		printf("\r\n\r\n\tU listi se nalaze : \r\n");
		while (P != NULL)
		{
			printf("\t\t%s %s %d\r\n", P->ime, P->prezime, P->godina_rodenja);
			P = P->next;
		}
	}
	printf("\r\n\r\n");

	return SUCCESS;
}

Pozicija FindLast(Pozicija P)
{
	if (P == NULL) return NULL;

	while (P->next != NULL)
		P = P->next;
	return P;
}

int InsertEnd(Pozicija P)
{
	P = FindLast(P);
	return Unos_Pocetak_Liste(P);
}

Pozicija FindPrezime(Pozicija P)
{
	char *prez = NULL;

	prez = (char*)malloc(sizeof(char) * BUFFER_LENGTH);
	if (prez == NULL) return NULL;
	memset(prez, '\0', BUFFER_LENGTH);

	printf("\r\n\tUnesite prezime koje trazite <max %d znakova>: ", BUFFER_LENGTH - 1);
	scanf(" %s", prez);
	while (P != NULL && strcmp(P->prezime, prez) != 0)
		P = P->next;

	free(prez);

	return P;
}

Pozicija FindPrevPrez(Pozicija P)
{
	char *prez = NULL;

	prez = (char*)malloc(sizeof(char) * BUFFER_LENGTH);
	if (prez == NULL) return NULL;
	memset(prez, '\0', BUFFER_LENGTH);

	printf("\r\n\tUnesite prezime koje trazite <max %d znakova>: ", BUFFER_LENGTH - 1);
	scanf(" %s", prez);
	while (P->next != NULL && strcmp(P->next->prezime, prez) != 0)
		P = P->next;

	if (P->next == NULL)
		P = NULL;

	free(prez);

	return P;
}

int Delete_Prezime(Pozicija P)
{
	Pozicija tmp = NULL;

	printf("\r\n\tBrisanje!");
	P = FindPrevPrez(P);
	if (P == NULL)
	{
		printf("\r\n\tTrazeno prezime se ne nalazi u listi!");
		return ERROR;
	}

	tmp = P->next;
	if (tmp != NULL)
	{
		P->next = tmp->next;
		printf("\r\nIz liste se brise : %s %s %d", tmp->ime, tmp->prezime, tmp->godina_rodenja);
		free(tmp);
	}

	return SUCCESS;
}

int GarbageCollector(Pozicija P)
{
	if (P->next != NULL)
		GarbageCollector(P->next);

	free(P);

	return SUCCESS;
}
