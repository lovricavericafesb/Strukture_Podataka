#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#include <string.h>
#define BUFFER 1024
#define SUCCESS 0
#define ERROR -1

typedef struct Stog* Nod;
typedef struct Stog {
	float element;
	Nod Next;
}Stog;

int CreateNew(Nod *);
int Push(Nod,float);
int Pop(Nod, float* );
int rezultPostfix(Nod, const char*);
int IsOperand(char*, float *);
int IsValidStack(Nod);
int Calculator(float, float, char *, float *);
int GarbageCollector(Nod);

int main(void)
{
	Stog head;
	head.Next = NULL;
	int result = 0;

	char *fileName;

	fileName = (char*)malloc(sizeof(char)* BUFFER);
	if (fileName == NULL) {
		printf("Memory not poperly alocated for fileName");
		return ERROR;
	}

	memset(fileName, '\0', BUFFER);
	while (strlen(fileName) == 0)
	{
		printf("\r\n\tUnesite naziv datoteke s posfix izrazome <max %d znakova>: ", BUFFER);
		scanf(" %s", fileName);
	}

	if (strchr(fileName, '.') == NULL)
		strcat(fileName, ".txt");

	result = rezultPostfix(&head, fileName);
	if (result) return result;

	result = IsValidStack(&head);
	if (result) {
		printf("\r\nPosfix calculation error!");
		return ERROR;
	}
	else {
		printf("\\n\tResult of calculation is: %.2f", head.Next->element);
	}
	GarbageCollector(head.Next);
	free(fileName);
	system("pause");
	return SUCCESS;
}

int rezultPostfix(Nod Stog, const char *fileName) {
	FILE *fp = NULL;
	int result = SUCCESS;
	float number = 0;
	float operand1 = 0;
	float operand2 = 0;
	char *buffer = NULL;

	buffer = (char*)malloc(sizeof(char)*BUFFER);
	if (buffer == NULL) {
		printf("Memory not properly alocated for buffer in rezultPostfix!");
		return ERROR;
	}
	memset(buffer, '\0', BUFFER);

	if (fileName == NULL)
	{
		printf("File name can not be NULL!\n");
		return ERROR;
	}

	if (strlen(fileName) == 0)
	{
		printf("File can't be an empty string!\n");
		return ERROR;
	}

	fp = fopen(fileName, "r");
	if (!fp)
	{
		printf("File didn't open! -> %s", fileName);
		return ERROR;
	}

	while (!feof(fp))
	{
		memset(buffer, 0, BUFFER);
		fscanf(fp, " %s", buffer);
		if (strlen(buffer) == 0) continue;

		if (SUCCESS != IsOperand(buffer, &number))
		{
			result = Pop(Stog, &operand2);
			if (result) break;

			result = Pop(Stog, &operand1);
			if (result) break;

			result = Calculator(operand1, operand2, buffer, &number);
			if (result) break;

		}
		result = Push(Stog, number);
		if (result) break;
	}
	fclose(fp);

	if (result) {
		printf("\r\nPostfix calucaltion error!");
		return ERROR;
	}

	return result;
}

int IsOperand(char *buff, float *number)
{
	int result = SUCCESS;

	result = sscanf(buff, " %f", number);
	if (result == EOF || result == 0 || result != 1) return ERROR;

	return SUCCESS;
}
int Calculator(float x, float y, char *operation, float *result)
{
	int error = SUCCESS;
	if (operation == NULL || strlen(operation) == 0)
		return ERROR;

	if (strcmp(operation, "+") == 0)
	{
		*result = x + y;
	}
	else if (strcmp(operation, "-") == 0)
	{
		*result = x - y;
	}
	else if (strcmp(operation, "*") == 0)
	{
		*result = x * y;
	}
	else if (strcmp(operation, "/") == 0)
	{
		if (y < 0)
		{
			*result = 0;
			printf("\r\n\t\tDivide with zero not allowed!");
			error = ERROR;
		}
		else
		{
			*result = x / y;
		}
	}
	else
	{
		*result = 0;
		printf("\r\n\t\tOperation not recognized!");
		error = ERROR;
	}

	return error;
}

int CreateNew(Nod *head)
{
	Nod q = NULL;

	*head = (Nod)malloc(sizeof(Stog));
	if (*head == NULL) return ERROR;

	q = *head;
	q->Next = NULL;

	return SUCCESS;
}

int Push(Nod P, float x)
{
	int err = SUCCESS;
	Nod q = NULL;

	err = CreateNew(&q);
	if (err) return err;

	q->element = x;

	q->Next = P->Next;
	P->Next = q;

	return err;
}

int Pop(Nod P, float *x)
{
	Nod tmp = NULL;

	tmp = P->Next;
	if (tmp == NULL) return ERROR;

	P->Next = tmp->Next;
	*x = tmp->element;
	free(tmp);

	return SUCCESS;
}
int IsValidStack(Nod S)
{
	if (S == NULL) return ERROR;

	if (S->Next == NULL) return ERROR;

	if (S->Next->Next != NULL) return ERROR;

	return SUCCESS;
}
int GarbageCollector(Nod S)
{
	if (S == NULL) return SUCCESS;

	GarbageCollector(S->Next);
	free(S);
	return SUCCESS;
}