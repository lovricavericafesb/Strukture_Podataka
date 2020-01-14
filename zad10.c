#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <malloc.h>
#include <string.h>
#define MAX_LINE 50

typedef struct Stog* pokazivacStog;
typedef struct Stog {
	char element[MAX_LINE];
	pokazivacStog next;
}Stog;

typedef struct Stablo* pokazivacStablo;
typedef struct Stablo {
	char element[MAX_LINE];
	pokazivacStablo left;
	pokazivacStablo right;
}Stablo;

int pushStog(pokazivacStog, char*);
int Start(pokazivacStog);
char* readFile(char*);
int CreateStog(pokazivacStog, char*);
pokazivacStablo createStablo(pokazivacStog);
char* popStog(pokazivacStog);
int inOrderIspis(pokazivacStablo);


int main(void)
{
	pokazivacStog headStog;
	headStog = (pokazivacStog)malloc(sizeof(Stog));
	headStog->next = NULL;

	Start(headStog);


	return 0;

}

int Start(pokazivacStog headStog)
{
	char* filename = NULL;
	char* buffer = NULL;

	filename = (char*)malloc(sizeof(char) * MAX_LINE);
	if (filename == NULL)
	{
		printf("Memory not properly alocated for filename!\n");
		return 0;
	}
	memset(filename, '\0', MAX_LINE);
	printf("\nUnesite naziv datoteke s postfix izrazom: ");
	scanf(" %s", filename);

	if (strchr(filename, '.') == NULL)
		strcat(filename, ".txt");

	buffer = (char*)malloc(sizeof(char) * MAX_LINE);
	if (buffer == NULL)
	{
		printf("\nMemory not alocated correctly for buffer!\n");
		return 0;
	}
	memset(buffer, '\0', MAX_LINE);
	buffer = readFile(filename);
	if (buffer == NULL)
	{
		printf("\nFile not open correctly!\n");
		return 0;
	}
	
	CreateStog(headStog, buffer);
	pokazivacStablo Root;
	Root = (pokazivacStablo)malloc(sizeof(Stablo));
	Root = createStablo(headStog);
	inOrderIspis(Root);


	return 0;
}

char* readFile(char* filename)
{
	FILE* fp = NULL;
	char* buffer = NULL;

	buffer = (char*)malloc(sizeof(char) * MAX_LINE);
	if (buffer == NULL)
	{
		printf("\nMemory not alocated correctly for buffer!\n");
		return 0;
	}
	memset(buffer, '\0', MAX_LINE);

	if (filename == NULL)
	{
		printf("\nFile name can't be NULL!\n");
		return 0;
	}
	else if (strlen(filename) == NULL)
	{
		printf("\nFile can't be an empty string!\n");
		return 0;
	}
	fp = fopen(filename, "r");
	if (fp == NULL)
	{
		printf("\nFile didn't open -> %s\n", filename);
		return 0;
	}
	
	fgets(buffer, MAX_LINE, fp);
	fclose(fp);

	return buffer;
}
int CreateStog(pokazivacStog headStog, char* buffer)
{
	int howManyBytes = 0;
	char element[MAX_LINE] = {0};

	while (sscanf(buffer, " %s %n", element, &howManyBytes) == 1)
	{
		pushStog(headStog, element);
		buffer += howManyBytes;
		howManyBytes = 0;
	}


	return 0;
}

int pushStog(pokazivacStog head, char* element)
{
	pokazivacStog newNode;
	newNode = (pokazivacStog)malloc(sizeof(Stog));
	

	strcpy(newNode->element, element);
	newNode->next = head->next;
	head->next = newNode;

	return 0;

}
pokazivacStablo createStablo(pokazivacStog headStog)
{
	
	pokazivacStablo Root;
	Root = (pokazivacStablo)malloc(sizeof(Stablo));
	strcpy(Root->element, popStog(headStog));
	
	if ((Root->element[0] == '+') || (Root->element[0] == '-') || (Root->element[0] == '*') || (Root->element[0] == '%') || (Root->element[0] == '/'))
	{
		Root->right = createStablo(headStog);
		Root->left = createStablo(headStog);
	}
	else {
		Root->left = NULL;
		Root->right = NULL;
	}

	return Root;
}
char* popStog(pokazivacStog head)
{
	if (head->next == NULL)
	{
		printf("\nStog je prazan\n!");
		return 0;
	}
	char* element = malloc(sizeof(char));
	pokazivacStog temp = head->next;
	strcpy(element, temp->element);
	head->next = temp->next;
	free(temp);

	return element;
}
int inOrderIspis(pokazivacStablo Root)
{
	if (Root == NULL)
		return 0;

	printf("(");

	inOrderIspis(Root->left);

	printf("%s", Root->element);

	inOrderIspis(Root->right);

	printf(")");

	return 0;
}
