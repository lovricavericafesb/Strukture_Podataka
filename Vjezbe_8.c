#define _CRT_SECURE_NO_WARRNING
#include<stdio.h>>
#include<stdlib.h>
#include<malloc.h>>
#include<string.h>
#define BUFFER_LENGTH 1024
#define SUCCESS 0
#define ERROR -1

typedef struct tree *Node;
typedef struct tree {
	char *tree_name;
	Node child;
	Node Next;
}tree;

typedef struct stog *Position;
typedef struct stog {
	Node Position_Tree;
	Position Next;
}stog;

int menu(Node, Position, Position, Position);
Node Create_Tree_Root(Node, char*);
int Create_Tree_Element(Node);
Position Create_Stog_Head(Position, Node);
int Print_Tree(Node);
Node Search_By_Name(Node, char*);
Node Return_Back(Position, Position);
int Insert_Onto_Stog(Node);
int Print_Line(Position, Position);
int Print_Menu();

int main(void) {
	Node root = NULL;
	char *root_Name = NULL;
	char *command = NULL;
	root_Name = (char*)malloc(sizeof(char)*BUFFER_LENGTH);
	if (root_Name == NULL) {
		printf("\r\tError while allocating memeory for root_Name in main");
		return ERROR;
	}
	memset(root_Name, '\0', BUFFER_LENGTH);
	printf("\tPlease write the trees root name: ");
	scanf(" %s", root_Name);
	if (root_Name == NULL) {
		printf("\r\tRoot name can not be empty in main");
		return NULL;
	}
	root = Create_Tree_Root(root, root_Name);
	if(root == NULL) {
		printf("\r\tError while returning root from Create_Tree_Root to main");
		return ERROR;
	}

	Position stog_head;
	stog_head = (Position)malloc(sizeof(stog));
	if (stog_head == NULL) {
		printf("\r\tMemory not properly allocated for stog_head in main function");
		return ERROR;
	}
	stog_head->Next = NULL;
	stog_head->Position_Tree = NULL;

	command = (char*)malloc(sizeof(char)*BUFFER_LENGTH);
	if (command == NULL) {
		printf("\r\tError while allocating memeory for command in main");
		return ERROR;
	}
	memset(command, '\0', BUFFER_LENGTH);

	while (strcmp(command, "EXIT") != 0) {
		memset(command, 0, BUFFER_LENGTH);
		Print_Menu();

		scanf(" %s", command);
	}

}

Node Create_Tree_Root(Node root, char *root_Name) {
	if (root == NULL) {
		printf("\r\tError while passing Node root into Create_Tree_Root");
		return NULL;
	}
	if (root_Name == NULL) {
		printf("\r\tRoot name can not be empty in Create_Tree_Root");
		return NULL;
	}
	root = (Node)malloc(sizeof(tree));
	if (root == NULL) {
		printf("\r\tError while allocating memory for root in Create_Tree_Root");
		return NULL;
	}
	root->child = NULL;
	root->Next = NULL;
	strcpy(root->tree_name, root_Name);

	return root;
}