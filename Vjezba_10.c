#define _CRT_SECURE_NO_WARNINGS
#define SUCCESS 0
#define ERROR -1
#define BUFFER 20

#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>

typedef struct Stog* Position_Stog;
typedef struct Stog {
	char* Stog_Element;
	Position_Stog next;
}Stog;

typedef struct Tree* Position_Tree;
typedef struct Tree {
	char* Tree_Element;
	Position_Tree left;
	Position_Tree right;
}Tree;

const char* readFile(char*);
Position_Tree Create_Tree(Position_Stog);
Position_Tree Create_Budget_Tree(Position_Stog, Position_Tree);
int Create_Stack(Position_Stog, char*);
int Push_Stog(Position_Stog, char*);
int Pop_Stog(Position_Stog, char*);
Position_Stog Create_Stog_Element(Position_Stog);
Position_Tree Create_Tree_Element(Position_Tree);
int In_Order_Print(Position_Tree);

int main(void) {
	Position_Stog stog_head;
	stog_head = (Position_Stog)malloc(sizeof(Stog));
	if (stog_head == NULL) {
		printf("\r\tError while allocating memory for stog_head in main!");
		return ERROR;
	}
	stog_head->next = NULL;

	char* filename = NULL;
	char* buffer = NULL;
	filename = (char*)malloc(sizeof(char)*BUFFER);
	if (filename == NULL) {
		printf("\r\tError while allocating memory for filename in main!");
		return ERROR;
	}
	memset(filename, '\0', BUFFER);
	printf("Insert the name of the file with the postfix expression: ");
	scanf(" %s", filename);
	if (strchr(filename, '.') == NULL)
	{
		strcat(filename, ".txt");
	}
	buffer = (char*)malloc(sizeof(char)*BUFFER);
	if (buffer == NULL) {
		printf("\r\tMemory not properly allocated for buffer in main!");
		return ERROR;
	}
	memset(buffer, '\0', BUFFER);

	buffer = readFile(filename);
	if (buffer == NULL) {
		printf("\r\tNULL returned to main from readFile!");
		return ERROR;
	}
	Position_Tree root;
	root = (Position_Tree)malloc(sizeof(Tree));
	root->left = NULL;
	root->right = NULL;
	root->Tree_Element = 0;
	Create_Stack(stog_head, buffer);
	root = Create_Budget_Tree(stog_head, root);
	In_Order_Print(root);
	system("pause");
	return SUCCESS;
}

const char* readFile(char* fileName) {
	FILE *fp = NULL;
	char *buffer = NULL;

	buffer = (char*)malloc(sizeof(char)*BUFFER);
	if (buffer == NULL) {
		printf("\r\tMemory not properly allocated for buffer in readFile!");
		return NULL;
	}
	memset(buffer, '\0', BUFFER);

	if (fileName == NULL) {
		printf("\r\tFile name can not be NULL!");
		return NULL;
	}

	if (strlen(fileName) == 0) {
		printf("\r\tFile can not be empty string!");
		return NULL;
	}

	fp = fopen(fileName, "r");
	if (fp == NULL) {
		printf("\r\tFile didn't open! -> %s", fileName);
		return NULL;
	}
	while (!feof(fp)) {
		memset(buffer, 0, BUFFER);
		fgets(buffer, BUFFER, fp);//radi jer samo učitavamo jednu liniju
	}
	fclose(fp);
	return buffer;
}

int Create_Stack(Position_Stog stog_head, char* buffer) {
	char* element = NULL;
	char* p = buffer;
	int how_Many_Bytes = 0;
	element = (char*)malloc(sizeof(char));
	while (p) {
		if (sscanf(p, " %s %n", element, &how_Many_Bytes) == 1) {
			Push_Stog(stog_head, element);
			p += how_Many_Bytes;
			how_Many_Bytes = 0;
		}
		else break;
	}
	return SUCCESS;
}
Position_Tree Create_Budget_Tree(Position_Stog stog_head, Position_Tree root) {
	char* element = NULL;
	element = (char*)malloc(sizeof(char));
	Pop_Stog(stog_head, element);
	Position_Tree Q = NULL;
	Q = Create_Tree_Element(Q);
	if (Q == NULL) {
		printf("\r\tNULL returned from Create_Tree_Element to Create_Tree_Node!");
		return ERROR;
	}
	Q->Tree_Element = (char*)malloc(sizeof(char));
	memset(Q->Tree_Element, '\0', BUFFER);
	strcpy(Q->Tree_Element, element);
	root = Q;
	if (strcmp(element, "+") == 0) {
		root->right = Create_Budget_Tree(stog_head, root->right);
		root->left = Create_Budget_Tree(stog_head, root->left);
	}
	else if (strcmp(element, "-") == 0) {
		root->right = Create_Budget_Tree(stog_head, root->right);
		root->left = Create_Budget_Tree(stog_head, root->left);
	}
	else if (strcmp(element, "*") == 0) {
		root->right = Create_Budget_Tree(stog_head, root->right);
		root->left = Create_Budget_Tree(stog_head, root->left);
	}
	else if (strcmp(element, "/") == 0) {
		root->right = Create_Budget_Tree(stog_head, root->right);
		root->left = Create_Budget_Tree(stog_head, root->left);
	}
	return root;
}
int Pop_Stog(Position_Stog stog_head, char* element) {
	Position_Stog temp = NULL;
	temp = stog_head->next;
	if (temp == NULL) {
		printf("\r\tThe stog is empty!");
		return ERROR;
	}
	stog_head->next = temp->next;
	strcpy(element, temp->Stog_Element);
	free(temp);
	return SUCCESS;

}
int Push_Stog(Position_Stog P, char* element) {
	Position_Stog Q = NULL;
	Q = Create_Stog_Element(Q);
	if (Q == NULL) {
		printf("\r\tNULL returned from Create_Stog_Element to Push_Stog!");
		return ERROR;
	}
	Q->Stog_Element = (char*)malloc(sizeof(char));
	strcpy(Q->Stog_Element, element);
	Q->next = P->next;
	P->next = Q;
	return SUCCESS;
}

Position_Stog Create_Stog_Element(Position_Stog P) {
	Position_Stog Q = NULL;
	Q = (Position_Stog)malloc(sizeof(Stog));
	if (Q == NULL) {
		printf("\r\tMemory not properly allocated for Q in Create_Stog_Element!");
		return NULL;
	}

	P = Q;
	Q->next = NULL;
	return Q;
}

Position_Tree Create_Tree_Element(Position_Tree P) {
	Position_Tree Q = NULL;
	Q = (Position_Tree)malloc(sizeof(Tree));
	if (Q == NULL) {
		printf("\r\tMemory not properly allocated for Q in Create_Tree_Element!");
		return NULL;
	}
	P = Q;
	Q->left = NULL;
	Q->right = NULL;
	return Q;
}
int In_Order_Print(Position_Tree root) {//infix printamo pomoću in_Order ispisa
	if (root == NULL) {
		return ERROR;
	}
	printf("(");
	In_Order_Print(root->left);
	printf(" %s", root->Tree_Element);
	In_Order_Print(root->right);
	printf(")");
	return SUCCESS;
}