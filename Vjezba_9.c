#define _CRT_SECURE_NO_WARNINGS
#define SUCCESS 0
#define ERROR -1
#define BUFFER 1024

#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include <stdlib.h>

typedef struct Tree_Node* Tree_Position;
typedef struct Tree_Node {
	int element;
	Tree_Position left;
	Tree_Position right;
}Tree_Node;

int menu(Tree_Position);
int Print_Menu();
int Add_Element_To_Tree(Tree_Position);
int Print_Tree(Tree_Position);
Tree_Position Delete_Element_From_Tree(Tree_Position, int);
Tree_Position Find_Minimum(Tree_Position);
Tree_Position Find_Element(Tree_Position, int);
int Garbage_Collector(Tree_Position);

int main(void) {
	Tree_Position root;
	root = (Tree_Position)malloc(sizeof(Tree_Node));
	printf("\r\tInsert the value of the root element: ");
	scanf(" %d", &root->element);
	root->left = NULL;
	root->right = NULL;

	menu(root);
	system("pause");
	Garbage_Collector(root);
	return SUCCESS;
}

int menu(Tree_Position root) {
	char* choice;
	choice = (char*)malloc(sizeof(char)*BUFFER);
	memset(choice, '\0', BUFFER);

	while (strcmp(choice, "EXIT") != 0) {
		Print_Menu();
		printf("\r\tChoose operation: ");
		scanf(" %s", choice);
		if (strcmp(choice, "1") == 0){
			Add_Element_To_Tree(root);
		}
		else if (strcmp(choice, "2") == 0) {
			Print_Tree(root);
		}
		else if (strcmp(choice, "3") == 0) {
			int new_integer = 0;
			printf("\r\tPlease insert the value of the element you wish to delete from the tree: ");
			scanf(" %d", &new_integer);
			root = Delete_Element_From_Tree(root, new_integer);

		}
		else if (strcmp(choice, "4") == 0) {
			int new_integer = 0;
			printf("\r\tPlease insert the value of the element you wish to find in the tree: ");
			scanf(" %d", &new_integer);
			Tree_Position searched;
			searched = Find_Element(root, new_integer);
			printf("\r\tThe element you were searching for: %d ", searched->element);

		}
		else if (strcmp(choice, "EXIT") == 0) {
			break;
		}
		else {
			printf("\r\tInncorrect command, please try again. ");
		}
	}
	return SUCCESS;
}

int Print_Menu() {
	printf("\r\nPlease choose one of the following operations: \n");
	printf("1 - For inserting element into the tree\n");
	printf("2 - For printing the elements of the tree\n");
	printf("3 - For deleting an element from the tree\n");
	printf("4 - For finding an element in the tree\n");
	printf("EXIT - For exiting the program\n");
	return SUCCESS;
}

int Add_Element_To_Tree(Tree_Position root) {
	int new_integer = 0;
	Tree_Position temp = root;
	Tree_Position Previous = root;
	
	printf("\r\tInsert the value of the new element you wish to add to the tree: ");
	scanf(" %d", &new_integer);
	while (temp != NULL) {

		if (temp->element > new_integer) {
			Previous = temp;
			temp = temp->left;
		}
		else if (temp->element < new_integer) {
			Previous = temp;
			temp = temp->right;
		}
		else {
			printf("\r\tElement %d is already located in the tree: ", new_integer);
			return SUCCESS;
		}
	}

	Tree_Position new_element;
	new_element = (Tree_Position)malloc(sizeof(Tree_Node));
	if (new_element == NULL) {
		printf("\r\tERROR while allocating memory for new_element in function Add_Element_To_Tree!");
		return SUCCESS;
	}
	if (Previous->element > new_integer) {
		new_element->element = new_integer;
		Previous->left = new_element;
		new_element->left = NULL;
		new_element->right = NULL;
		return SUCCESS;
	}
	else if (Previous->element < new_integer) {
		new_element->element = new_integer;
		Previous->right = new_element;
		new_element->left = NULL;
		new_element->right = NULL;
		return SUCCESS;
	}
	return SUCCESS;
}

int Print_Tree(Tree_Position node) {
	if (node != NULL) {
		printf(" %d ", node->element);
		Print_Tree(node->left);
		Print_Tree(node->right);
	}
	return SUCCESS;
}

Tree_Position Delete_Element_From_Tree(Tree_Position root, int element) {
	Tree_Position temp;
	if (root != NULL) {
		if (root->element > element) {
			root->left = Delete_Element_From_Tree(root->left, element);
		}
		else if (root->element < element) {
			root->right = Delete_Element_From_Tree(root->right, element);
		}
		else {
			if (root->left != NULL && root->right != NULL) {
				temp = Find_Minimum(root->right);
				root->element = temp->element;
				root->right = Delete_Element_From_Tree(root->right, temp->element);
			}
			else {
				temp = root;
				if (root->left == NULL) {
					root = root->right;
				}
				else{
					root = root->left;
				}
				free(temp);
			}
		}
	}
	return root;	
}

Tree_Position Find_Minimum(Tree_Position node) {
	if (node != NULL) {
		if (node->left == NULL) {
			return node;
		}
		else {
			node = Find_Minimum(node->left);
		}
	}
	else
		return node;
}

Tree_Position Find_Element(Tree_Position node, int element) {
	if (node != NULL) {
		if (node->element > element) {
			return Find_Element(node->left, element);
		}
		else if (node->element < element) {
			return Find_Element(node->right, element);
		}
		else if (node->element == element) {
			return node;
		}
	}
	else return NULL;
}

int Garbage_Collector(Tree_Position root) {
	if (root->left != NULL) {
		Garbage_Collector(root->left);
	}
	else if (root->right != NULL) {
		Garbage_Collector(root->right);
	}
	free(root);
	return SUCCESS;
}



