#define _CRT_SECURE_NO_WARNINGS
#define SUCCESS 0
#define ERROR -1
#define BUFFER 1024

#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>

typedef struct Tree *Position_Tree;
typedef struct Tree {
	char *directory_name;
	Position_Tree child;//ovo predstavlja prvo dijete, roditelja povezujemo samo s prvim djetetom
	Position_Tree next;//s pomoću next(siblings) povezujemo sve elemente stabla koji imaju istog roditelja kao i prvo dijete
}Tree;

typedef struct Stog *Position_Stog;
typedef struct Stog {
	Position_Tree Tree_Node;
	Position_Stog next;
}Stog;

int Enter_Command(Position_Tree, Position_Stog);
int Print_Files_In_Directrory(Position_Tree);
int Print_Path(Position_Stog, Position_Stog);
int Create_Directory(Position_Tree);
Position_Stog Return_To_Previous_Directory(Position_Stog, Position_Stog);
Position_Stog Move_To_Directory(Position_Stog, Position_Stog, Position_Tree);


int main(void) {
	Position_Tree root = NULL;
	root = (Position_Tree)malloc(sizeof(Tree));
	if (root == NULL) {
		printf("\r\tMemory not properly allocated for root in main");
		return ERROR;
	}
	root->child = NULL; //child predstavlja još jedan direktori (folder)
	root->next = NULL;//next predstavlja samo file (npr txt file) koji nisu folderi
	root->directory_name = (char*)malloc(sizeof(char)*BUFFER);
	strcpy(root->directory_name, "root");

	Position_Stog head_stog = NULL;
	head_stog = (Position_Stog)malloc(sizeof(Stog));
	if (head_stog == NULL) {
		printf("\r\tMemory not properly allocated for head_stog in main");
		return ERROR;
	}
	head_stog->next = NULL;
	head_stog->Tree_Node = NULL;

	Position_Stog Root_Directory = NULL;
	Root_Directory = (Position_Stog)malloc(sizeof(Stog));
	if (Root_Directory == NULL) {
		printf("\r\tMemory not properly allocated for Current_Directory in main");
		return ERROR;
	}
	Root_Directory->next = head_stog->next;//postavljamo na vrijednost NULL
	Root_Directory->Tree_Node = root;
	head_stog->next = Root_Directory;


	Enter_Command(root, head_stog);
	system("pause");
	return SUCCESS;

}

int Enter_Command(Position_Tree Tree, Position_Stog Stog){
	Position_Stog Current_Directory = Stog->next;
	char *command = NULL;
	command = (char*)malloc(sizeof(char)*BUFFER);
	if (command == NULL) {
		printf("\r\tMemory not properly allocated for command in main");
		return ERROR;
	}

	memset(command, '\0', BUFFER);
	while (strcmp(command, "EXIT") != 0) {
		memset(command, 0, BUFFER);
		Print_Menu();
		Print_Path(Current_Directory, Stog);

		scanf(" %s", command);

		if (strcmp(command, "dir")==0) {
			Print_Files_In_Directrory(Current_Directory->Tree_Node);
		}
		else if (strcmp(command, "cd..")==0) {
			Current_Directory = Return_To_Previous_Directory(Current_Directory,Stog);
		}

		else if (strcmp(command, "md")==0) {
			Create_Directory(Current_Directory->Tree_Node);
		}

		else if (strcmp(command, "cd")==0) {
			Current_Directory = Move_To_Directory(Current_Directory, Stog, Current_Directory->Tree_Node);

		}
		else {
			printf("\nIncorrect command, please try again!");
		}
	}
	return SUCCESS;
}
int Print_Menu() {
	printf("\nInput command:\n");
	printf("\rTo print the files located in the current dirrectory: dir\n");
	printf("\rTo return to the previous directory: cd..\n");
	printf("\rTo create a new directory: md <input directory name>\n");
	printf("\rTo open a directory: cd <input directory name>\n");
	printf("\rTo exit the program: EXIT\n");
	return SUCCESS;
}

int Create_Directory(Position_Tree Directory){
	if (Directory->child == NULL) {
		Position_Tree new_element;
		new_element = (Position_Tree)malloc(sizeof(Tree));
		new_element->directory_name = (char*)malloc(sizeof(char)*BUFFER);
		Directory->child = new_element;
		new_element->child = NULL;
		new_element->next = NULL;
		printf("\r\tEnter the name of the new directory: ");
		scanf(" %s", new_element->directory_name);
		return SUCCESS;
		}
	Position_Tree temp = Directory->child;
	while (temp->next != NULL) {
		temp = temp->next;
	}
	Position_Tree new_element;
	new_element = (Position_Tree)malloc(sizeof(Tree));
	new_element->directory_name = (char*)malloc(sizeof(char)*BUFFER);
	new_element->child = NULL;
	new_element->next = temp->next;
	temp->next = new_element;
	printf("\r\tEnter the name of the new directory: ");
	scanf(" %s", new_element->directory_name);
	return SUCCESS;
}

int Print_Files_In_Directrory(Position_Tree Directory) {
	Position_Tree temp = Directory->child;
	if (temp == NULL) {
		printf("\r\tThe directory named %s is empty!", Directory->directory_name);
		return SUCCESS;
	}

	printf("\r\tThe current files are located in the %s directory: ", Directory->directory_name);
	while (temp != NULL) {
		printf("\n\t- %s", temp->directory_name);
		temp = temp->next;
		}
	printf("\n");
	return SUCCESS;
}

int Print_Path(Position_Stog Current_Directory, Position_Stog head_Stog) {
	
	Position_Stog Previous = head_Stog->next;
	if (Previous == Current_Directory) {
		printf(" %s >", Current_Directory->Tree_Node->directory_name);
		return SUCCESS;

	}
	while (Previous != Current_Directory->next) {
		printf(" %s >", Previous->Tree_Node->directory_name);
		Previous = Previous->next;
	}
	return SUCCESS;
}

Position_Stog Return_To_Previous_Directory(Position_Stog Current_Directory, Position_Stog Stog_Head) {
	if (Current_Directory == Stog_Head->next) {
		printf("\r\tYou are currently in the main directory and you can't go back further.\n");
		return SUCCESS;
	}
	Position_Stog Previous = Stog_Head->next;
	Position_Stog temp = Current_Directory;
	while (Previous->next != temp) {
		Previous = Previous->next;
	}
	Previous->next = temp->next;
	free(temp);
	return Previous;
}

Position_Stog Move_To_Directory(Position_Stog Current_Directory, Position_Stog stog_head, Position_Tree Tree_Elements) {
	char* directory_name;
	Tree_Elements = Tree_Elements->child;
	directory_name = (char*)malloc(sizeof(char)*BUFFER);
	if (directory_name == NULL) {
		printf("\r\tMemory not properly allocated for directory_name in Move_To_Directory");
		return Current_Directory;
	}
	memset(directory_name, '\0', BUFFER);
	memset(directory_name, 0, BUFFER);
	printf("\r\tInsert the name of the directory you wish to open: ");
	scanf(" %s", directory_name);

	while (strcmp(directory_name, Tree_Elements->directory_name) != 0) {
		if (Tree_Elements == NULL) {
			printf("\r\tNo directory of %s name exists!", directory_name);
			return Current_Directory;
		}
		Tree_Elements = Tree_Elements->next;
	}
	
		printf("\r\tYou opened %s directory: ", Tree_Elements->directory_name);
		Position_Stog Q_Stog;
		Position_Tree Q_Tree;
		Q_Stog = (Position_Stog)malloc(sizeof(Stog));
		Q_Tree = (Position_Tree)malloc(sizeof(Tree));
		Q_Tree->directory_name = (char*)malloc(sizeof(char)*BUFFER);
		Q_Tree->directory_name = Tree_Elements->directory_name;
		Q_Tree->child = NULL;
		Q_Tree->next = NULL;

		Q_Stog->Tree_Node = Q_Tree;
		Q_Stog->next = Current_Directory->next;
		Current_Directory->next = Q_Stog;

		return Current_Directory->next;
}
