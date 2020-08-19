#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#include <string.h>
#define BUFFER 1024
#define SUCCESS 0
#define ERROR -1

typedef struct  Stog *Nod;
typedef struct Stog {
	float element;
	Nod Next;
}Stog;


int CreateNewStog(Nod *);
int PushStog(Nod, float);
const char* readFile(char*);
int PopStog(Nod, float*);
float resultPostfix(Nod, char*);
int GarbageCollector(Nod);

int main(void) {
	Stog head;
	head.Next = NULL;
	char *fileName = NULL;
	char *buffer = NULL;

	fileName = (char*)malloc(sizeof(char)*BUFFER);
	if (fileName == NULL) {
		printf("Memory not properly alocated for fileName");
		return ERROR;
	}
	memset(fileName, '\0', BUFFER);
	printf("\r\n\tUnesite naziv datoteke s posfix izrazome <max %d znakova>: ", BUFFER);
	scanf(" %s", fileName);


	if (strchr(fileName, '.') == NULL)
		strcat(fileName, ".txt");

	buffer = (char*)malloc(sizeof(char)*BUFFER);
	if (buffer == NULL) {
		printf("Memory not properly alocated for buffer in main");
		return ERROR;
	}
	memset(buffer, '\0', BUFFER);

	buffer = readFile(fileName);
	if (buffer == NULL) {
		printf("File not read correctly in main function!");
		return ERROR;
	}

	resultPostfix(&head, buffer);
	system("pause");
}

float resultPostfix(Position S, char* buffer) {
	float result = 0;
	float number = 0;
	float operand1 = 0;
	float operand2 = 0;
	int howManyBytes = 0;
	char *p = buffer;
	while (p) {
		if (sscanf(p, " %f %n", &number, &howManyBytes) == 1) {//čita znak po znak i priskače space, ako dođemo na broj zapiše ga u float a dužinu u howManyBytes
			PushStog(S, number); //to radi jer je u float učitao cijeli broj(koliko god znamenki imao) a s uvjetmo ==1 sscanf se prekida kada se učita 1 element
			p += howManyBytes;//znači howManyBytes predstavlja dužinu učitanog broja jer se space priskače, s njim možemo inkrementirati buffer p, tj. šetat kroz file za howManyBtyes koraka
		}
		else if (strncmp(p, "+", 1) == 0) {
			PopStog(S, &operand1);
			PopStog(S, &operand2);
			result = operand1 + operand2;
			PushStog(S, result);
			p+=2;
		}
		else if (strncmp(p, "-", 1) == 0) {
			PopStog(S, &operand1);
			PopStog(S, &operand2);
			result = operand1 - operand2;
			PushStog(S, result);
			p += 2;
		}
		else if (strncmp(p, "*", 1) == 0) {
			PopStog(S, &operand1);
			PopStog(S, &operand2);
			result = operand1 * operand2;
			PushStog(S, result);
			p += 2;
		}
		else if (strncmp(p, "/", 1) == 0) {
			PopStog(S, &operand1);
			PopStog(S, &operand2);
			if (operand1 < 0) {
				printf("\r\tDividing with zero is not allowed");
				return ERROR;
			}
			else {
				result = operand1 / operand2;
				PushStog(S, result);
				p += 2;
			}
		}
		else {
			break;
		}
	}
	printf("\t\rThe result of the Postfix calculation is: %0.2f \n", S->Next->element);
	return SUCCESS;
}

const char* readFile(char *fileName) {
	FILE *fp = NULL;
	char *buffer = NULL;

	buffer = (char*)malloc(sizeof(char)*BUFFER);
	if (buffer == NULL) {
		printf("Memory not properly allocated for buffer in readFile!");
		return NULL;
	}
	memset(buffer, '\0', BUFFER);

	if (fileName == NULL)
	{
		printf("File name can not be NULL!\n");
		return NULL;
	}

	if (strlen(fileName) == 0)
	{
		printf("File can't be an empty string!\n");
		return NULL;
	}

	fp = fopen(fileName, "r");
	if (fp == NULL)
	{
		printf("File didn't open! -> %s", fileName);
		return NULL;
	}
	while (!feof(fp)) {
		memset(buffer, 0, BUFFER);
		fgets(buffer, BUFFER, fp);
	}
	fclose(fp);
	return buffer;
}

int CreateNewStog(Nod *head)
{
	Nod q = NULL;

	*head = (Nod)malloc(sizeof(Stog));
	if (*head == NULL) return ERROR;

	q = *head;
	q->Next = NULL;

	return SUCCESS;
}


int PushStog(Nod P, float x)
{
	int err = SUCCESS;
	Nod q = NULL;

	err = CreateNewStog(&q);
	if (err) return err;

	q->element = x;

	q->Next = P->Next;
	P->Next = q;

	return err;
}


int PopStog(Nod P, float *x)
{
	Nod tmp = NULL;

	tmp = P->Next;
	if (tmp == NULL) return ERROR;

	P->Next = tmp->Next;
	*x = tmp->element;
	free(tmp);

	return SUCCESS;
}
int GarbageCollector(Nod S)
{
	if (S == NULL) return SUCCESS;

	GarbageCollector(S->Next);
	free(S);
	return SUCCESS;
}
