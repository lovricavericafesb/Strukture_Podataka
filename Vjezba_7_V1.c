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

float resultPostfix(Nod _stog, char* buffer) {
	float result = 0;
	float number = 0;
	float operand1 = 0;
	float operand2 = 0;
	int howManyBytes = 0;
	char *p = buffer;
	while (p) {
		if (sscanf(p, " %f %n", &number, &howManyBytes) == 1) {
			PushStog(_stog, number);
			p += howManyBytes;
		}
		else if (strcmp(p, "+") == 0) {
			PopStog(_stog, &operand1);
			PopStog(_stog, &operand2);
			result = operand1 + operand2;
			PushStog(_stog, result);
			p++;
		}
		else if (strcmp(p, "-") == 0) {
			PopStog(_stog, &operand1);
			PopStog(_stog, &operand2);
			result = operand1 - operand2;
			PushStog(_stog, result);
			p++;
		}
		else if (strcmp(p, "*") == 0) {
			PopStog(_stog, &operand1);
			PopStog(_stog, &operand2);
			result = operand1 * operand2;
			PushStog(_stog, result);
			p++;
		}
		else if (strcmp(p, "/") == 0) {
			PopStog(_stog, &operand1);
			PopStog(_stog, &operand2);
			if (operand2 < 0) {
				printf("/n/t Dividing with zero is not allowed!");
				return ERROR;
			}
			else {
				result = operand1 / operand2;
				PushStog(_stog, result);
				p++;
			}
		}
		else {
			break;
		}
		
	}
	printf("/n/tThe result of the Postfix calculation is: %0.2f/n", _stog->Next->element);
	return SUCCESS;
}

const char* readFile(char *fileName) {
	FILE *fp = NULL;
	char *buffer = NULL;

	buffer = (char*)malloc(sizeof(char)*BUFFER);
	if (buffer == NULL) {
		printf("Memory not properly allocated for buffer in readFile!");
		exit(SUCCESS);
	}
	memset(buffer, '\0', BUFFER);

	if (fileName == NULL)
	{
		printf("File name can not be NULL!\n");
		exit(SUCCESS);
	}

	if (strlen(fileName) == 0)
	{
		printf("File can't be an empty string!\n");
		exit(SUCCESS);
	}

	fp = fopen(fileName, "r");
	if (fp == NULL)
	{
		printf("File didn't open! -> %s", fileName);
		exit(SUCCESS);
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