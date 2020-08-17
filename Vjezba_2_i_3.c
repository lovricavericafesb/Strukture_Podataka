/*
Zadatak 2.
Definirati strukturu osoba (ime, prezime, godina roðenja) i napisati program koji:
a) dinamièki dodaje novi element na poèetak liste,
b) ispisuje listu,
c) dinamièki dodaje novi element na kraj liste,
d) pronalazi element u listi (po prezimenu),
e) briše odreðeni element iz liste,
U zadatku se ne smiju koristiti globalne varijable.

Zadatak 3.
Prethodnom zadatku dodati funkcije:
a) dinamièki dodaje novi element iza odreðenog elementa,
b) dinamièki dodaje novi element ispred odreðenog elementa,
c) sortira listu po prezimenima osoba,
d) upisuje listu u datoteku,
e) èita listu iz datoteke.
*/

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include<stdlib.h>
#include<string.h>
#include<malloc.h>
#define BUFFER_LENGTH 1024
#define ERROR -1
#define SUCCESS 0

typedef struct student* Position;
typedef struct student {
	char name[BUFFER_LENGTH];
	char surname[BUFFER_LENGTH];
	int birht_year;
	Position Next;
}student;
//Zadatak broj 2
int Print_Menu();
Position CreateListNode(Position);
Position Insert_Student_Data(Position);
int Insert_At_Beggining_Of_List(Position);
int Print_List(Position);
Position Find_Last(Position);
int Insert_At_End_Of_List(Position);
Position Find_By_LastName(Position);
int Delete_By_LastName(Position);
Position Find_Previous_List_Element(Position);
int Garbage_Collector(Position);
//Zadatak broj 3
int Insert_After_LastName(Position);
int Insert_Before_LastName(Position);
int Sort_List_By_LastName(Position);
int Print_To_File(Position);
int Load_From_File(Position);

int main(void)
{
	student head; //kreiramo head element liste
	Position searched_Student = NULL; //kada budemo tražili studenta, postavljamo prvo na NULL da budemo sigurni
	char *choice;
	head.Next = NULL;
	choice = (char*)malloc(sizeof(char)*BUFFER_LENGTH);
	if (choice == NULL)
	{
		printf("\r\tMemory not properly allocated for choice!");
		return ERROR;
	}
	memset(choice, '\0', BUFFER_LENGTH); //postavljamo iznos na prazan skup veličine BUFFER-a kako bi osigurali da je choice prazan

	while (strcmp(choice, "EXIT") != SUCCESS)
	{
		memset(choice, 0, BUFFER_LENGTH);
		Print_Menu();

		scanf(" %s", choice);

		if (strcmp(choice, "1") == SUCCESS)
		{
			Insert_At_Beggining_Of_List(&head);
		}
		else if (strcmp(choice, "2") == SUCCESS)
		{
			Print_List(&head);
		}
		else if (strcmp(choice, "3") == SUCCESS)
		{
			Insert_At_End_Of_List(&head);
		}
		else if (strcmp(choice, "4") == SUCCESS)
		{
			searched_Student = Find_By_LastName(&head);
			if (searched_Student != NULL) 
			{
				printf("\r\tThe student you searched for is:\r\n %s %s %d\r\n", searched_Student->name, searched_Student->surname, searched_Student->birht_year);
			}
			else
			{
				printf("\r\tThe student you searched for is currently not in the data base.\r\n");
			}
		}
		else if (strcmp(choice, "5") == SUCCESS) 
		{
			Delete_By_LastName(&head);
			Print_List(&head);
		}
		else if (strcmp(choice, "6") == SUCCESS)
		{
			Insert_After_LastName(&head);
			Print_List(&head);
		}
		else if (strcmp(choice, "7") == SUCCESS)
		{
			Insert_Before_LastName(&head);
			Print_List(&head);
		}
		else if (strcmp(choice, "8") == SUCCESS)
		{
			Sort_List_By_LastName(&head);
			Print_List(&head);
		}
		else if (strcmp(choice, "9") == SUCCESS)
		{
			Read_From_File(&head);
			Print_List(&head);
		}
		else if (strcmp(choice, "A") == SUCCESS)
		{
			Print_To_File(&head);
			Print_List(&head);
		}
		else if(strcmp(choice,"EXIT")==SUCCESS)
		{
			break;
		}
		else
		{
			printf("\r\tIncorrect input <%s>.\rPlease try again.\n", choice);
		}
	}
	free(choice);
	Garbage_Collector(&head);

	return SUCCESS;
}

int Print_Menu()
{
	printf("\t*********************************************\r\n");
	printf("\t***   VJEZBA BROJ 2 - Vezane liste ***\r\n");
	printf("\t*********************************************\r\n");
	printf("\r\n\r\n");
	printf("\t\t1. Insert a student at the beggining\r\n");
	printf("\t\t2. Print list\r\n");
	printf("\t\t3. Insert a student at the end\r\n");
	printf("\t\t4. Find by surname\r\n");
	printf("\t\t5. Delete by surname\r\n");
	printf("\t\t6. Insert after student\r\n");
	printf("\t\t7. Insert before student\r\n");
	printf("\t\t8. Sort database\r\n");
	printf("\t\t9. Load list from file\r\n");
	printf("\t\tA. Print list into file\r\n");
	printf("\t\tExit. Exit the program\r\n");
	printf("\r\n\tIzbor : ");

	return SUCCESS;
}

int Insert_At_Beggining_Of_List(Position P)
{
	
	Position Q = NULL;
	Q = CreateListNode(Q);

	if(Q==NULL)
	{
		printf("\r\tMemory not properly allocated for variable in CreateListNode!");
		return ERROR;
	}
	Q = Insert_Student_Data(Q);
	if (Q == NULL)
	{
		printf("\r\tSomething went wrong in the Insert_Student_Data function!");
		return ERROR;
	}

	Q->Next = P->Next;
	P->Next = Q;

	return SUCCESS;
}

Position CreateListNode(Position Q)
{
	Q = (Position)malloc(sizeof(student));
	if (Q == NULL)
	{
		printf("\r\tMemory not properly allocated for variable in CreateListNode!");
		return NULL;
	}
	
	Q->Next = NULL;
	return Q;
}
Position Insert_Student_Data(Position Q)
{
	if (Q == NULL) {
		printf("\r\tVariable not properly sent into the Insert_Student_Data function!");
		return NULL;
	}
	printf("Please insert the name, last name and birth year of the student.\t\n");
	scanf(" %s %s %d", Q->name, Q->surname, &Q->birht_year);

	return Q;
}

int Print_List(Position P) {
	P = P->Next;
	if (P == NULL) {
		printf("\r\tThe database is empty.");
	}
	else {
		printf("\r\t\nThese students are in the database: \r\n");
		while (P != NULL) {
			printf("\t %s %s %d\r\n", P->name, P->surname, P->birht_year);
			P = P->Next;
		}
	}
	printf("\r\n\r\n");
	return SUCCESS;
}

int Insert_At_End_Of_List(Position P) {
	if (P == NULL) {
		printf("\r\tThere was an error while sending head element into Insert_At_End_Of_List.");
		return ERROR;
	}
	P = Find_Last(P);
	return Insert_At_Beggining_Of_List(P);
}
Position Find_Last(Position P) {
	if (P == NULL) {
		printf("\r\tThere was an error while sending head element into Find_Last function.");
		return NULL;
	}
	while (P->Next != NULL)
		P = P->Next;

	return P;
}	

Position Find_By_LastName(Position P) {
	P = P->Next;
	char *lastName = NULL;
	lastName = (char*)malloc(sizeof(char)*BUFFER_LENGTH);
	if (lastName == NULL) {
		printf("\r\tError while allocating memory for lastName in Find_By_LasName function.");
		return NULL;
	}
	memset(lastName, '\0', BUFFER_LENGTH);

	printf("\r\tPlease insert the last name of the student you wish to search for.\t\n");
	scanf(" %s", lastName);
	while (P != NULL && strcmp(P->surname, lastName) != 0) {
		P = P->Next;
	}
	free(lastName);
	return P;
}

int Delete_By_LastName(Position P) {
	Position temp = NULL;
	P = Find_Previous_List_Element(P);
	if (P == NULL) {
		printf("\r\tThe student with last name you search for doesn't exist in the database.");
		return ERROR;
	}
	temp = P->Next;
	if (temp != NULL) {
		P->Next = temp->Next;
		printf("\r\tThe student with the following data is being removed: %s %s %d", temp->name, temp->surname, temp->birht_year);
		free(temp);
	}
	return SUCCESS;
}
Position Find_Previous_List_Element(Position P) {
	char *lastName = NULL;

	lastName = (char*)malloc(sizeof(char)*BUFFER_LENGTH);
	if (lastName == NULL) {
		printf("\r\tThere was an error allocating memory for lastName in Find_Previous_List_Element");
		return NULL;
	}
	memset(lastName, '\0', BUFFER_LENGTH);
	printf("\r\t Please insert the last name of the student you are searching for: ");
	scanf(" %s", lastName);
	while (P->Next != NULL && strcmp(P->Next->surname, lastName) != 0)
		P = P->Next;

	if (P->Next == NULL)
		return NULL;

	free(lastName);

	return P;
}
int Garbage_Collector(Position P) {
	if (P->Next != NULL) {
		Garbage_Collector(P->Next);
	}
	free(P);
	return SUCCESS;
}
int Insert_After_LastName(Position P)
{
	P = Find_By_LastName(P);
	if (P == NULL) {
		printf("\r\t Error while returning variable from Find_By_LastName into Insert_After_LastName");
		return ERROR;
	}
	return Insert_At_Beggining_Of_List(P);
}
int Insert_Before_LastName(Position P) {
	P = Find_Previous_List_Element(P);
	if (P == NULL) {
		printf("\r\t Error while returning variable from Find_Previous_List_Element into Insert_Before_LastName");
		return ERROR;
	}
	return Insert_At_Beggining_Of_List(P);
}
int Read_From_File(Position P) {
	Position Q = NULL;
	char *fileName = NULL;
	FILE *fp = NULL;

	fileName = (char*)malloc(sizeof(char)*BUFFER_LENGTH);
	if (fileName == NULL) {
		printf("\r\tMemory not properly allocated for fileName in Print_To_File.");
		return ERROR;
	}
	memset(fileName, '\0', BUFFER_LENGTH);

	printf("\r\tInput the name of the writing file.\n");
	scanf(" %s", fileName);

	if (strchr(fileName, '.') == NULL) {
		strcat(fileName, '.txt');
	}

	fp = fopen(fileName, "w+");
	if (fp == NULL) {
		printf("\r\tFile not properly open in Print_To_File.\n");
		return ERROR;
	}
	while (!feof(fp)) {
		Q = CreateListNode(Q);
		if (Q == NULL)
		{
			printf("\r\tMemory not properly allocated for variable in CreateListNode for function Read_From_File!");
			return ERROR;
		}
		fscanf(fp, " %s %s %d", Q->name, Q->surname, &Q->birht_year);

		Q->Next = P->Next;
		P->Next = Q;
	}
	fclose(fp);
	return SUCCESS;
}

int Print_To_File(Position P) {
	FILE *fp = NULL;
	char *fileName = NULL;

	fileName = (char*)malloc(sizeof(char)*BUFFER_LENGTH);
	if (fileName == NULL) {
		printf("\r\tMemory not properly allocated for fileName in Print_To_File.");
		return ERROR;
	}
	memset(fileName, '\0', BUFFER_LENGTH);

	printf("\r\tInput the name of the writing file.\n");
	scanf(" %s", fileName);

	if (strchr(fileName, '.') == NULL) {
		strcat(fileName, '.txt');
	}

	fp = fopen(fileName, "w+");
	if (fp == NULL) {
		printf("\r\tFile not properly open in Print_To_File.\n");
		return ERROR;
	}
	while (P != NULL) {
		fprintf(fp, "%s %s %d", P->name, P->surname, P->birht_year);
		P = P->Next;
		if (P != NULL) {
			fprintf(fp, "\n");
		}
	}
	fclose(fp);
	return SUCCESS;
}
int Sort_List_By_LastName(Position P) {
	Position i = P;
	Position j = NULL;
	Position prev_j = NULL;
	Position end = NULL;

	while (i->Next != end) {
		prev_j = i;
		j = prev_j->Next;
		while (j->Next != end) {
			if (strcmp(j->surname, j->Next->surname) > 0) {
				prev_j->Next = j->Next;
				j->Next = j->Next->Next;
				prev_j->Next->Next = j;
				j = prev_j->Next;
			}
			prev_j = j;
			j = j->Next;
		}
		end = j;
	}
	return SUCCESS;
}
