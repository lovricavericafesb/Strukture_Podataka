#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <malloc.h>
#include <stdlib.h>

#define ERROR -1
#define SUCCES 0

typedef struct List;
typedef struct List* list;
typedef struct List {
	int element;
	int br_element;
	list next;
}List;

int input(list);
int createElement(list, int);
int sortList(list);
int switchElements(list, list, list);
int ispis(list);
int Unija(list, list, list);
int Presjek(list, list, list);
int createUnija(int, list);
int main(void)
{
	list head1;
	list head2;
	list head3;
	list head4;

	head1 = (list)malloc(sizeof(List));
	head2 = (list)malloc(sizeof(List));
	head3 = (list)malloc(sizeof(List));
	head4 = (list)malloc(sizeof(List));

	head1->next = NULL;
	head2->next = NULL;
	head3->next = NULL;
	head4->next = NULL;

	input(head1);
	input(head2);

	sortList(head1);
	sortList(head2);

	ispis(head1);
	printf("\n------------------------------------------------------------\n");
	ispis(head2);
	printf("\n");

	Unija(head1, head2, head3);
	printf("\nUnija:");
	printf("\n");
	ispis(head3);
	printf("\n");
	printf("______________________________________\n");
	
	Presjek(head1, head2, head4);
	printf("Presjek:\n");
	ispis(head4);
	
	return 0;
}
int input(list head) {
	int i = 0;

	printf("Input number of elements: ");
	scanf(" %d", &(head->br_element));

	for (i = 0; i < head->br_element; i++) {
		createElement(head, i);
	}


	return SUCCES;
}
int createElement(list head, int i) {
	list temp;
	temp = (list)malloc(sizeof(List));

	temp->next = head->next;
	head->next = temp;

	printf("\nInput %d element: ", i + 1);
	scanf(" %d", &(temp->element));
	printf("\n");

	return SUCCES;
}
int sortList(list head) {
	list temp1;
	list temp2;
	list temp3;
	temp1 = (list)malloc(sizeof(List));
	temp2 = (list)malloc(sizeof(List));
	temp3 = (list)malloc(sizeof(List));

	temp1 = head->next;
	temp2 = temp1->next;
	temp3 = temp1;

	while (temp1->next != NULL) {
		while (temp2 != NULL) {
			if (temp1->element < temp2->element)
				switchElements(temp1, temp2, head);
			else
				temp2 = temp2->next;
		}
		temp3 = temp3->next;
		temp1 = temp3;
		temp2 = temp1->next;
	}

	return SUCCES;
}
int switchElements(list temp1, list temp2, list head)
{
	list prev1;
	list prev2;
	list temp3;
	list temp4;

	prev1 = (list)malloc(sizeof(List));
	prev2 = (list)malloc(sizeof(List));
	temp3 = (list)malloc(sizeof(List));
	temp4 = (list)malloc(sizeof(List));

	prev1 = head;
	prev2 = head;

	while (prev1->next != temp1)
		prev1 = prev1->next;
	while (prev2->next != temp2)
		prev2 = prev2->next;

	if (temp1->next == temp2) {
		prev1->next = temp2;
		temp3->next = temp2->next;
		temp2->next = temp1->next;
		temp1->next = temp3->next;
		return SUCCES;
	}
	else if (temp2->next == temp1) {
		prev2->next = temp1;
		temp3->next = temp1->next;
		temp1->next = temp2->next;
		temp2->next = temp3->next;
		return SUCCES;
	}
	else {
		temp4->next = prev1->next;
		prev1->next = prev2->next;
		prev2->next = temp4->next;

		temp3->next = temp1->next;
		temp1->next = temp2->next;
		temp2->next = temp3->next;
		return SUCCES;
	}

	return ERROR;

}
int ispis(list head)
{
	list temp;
	temp = (list)malloc(sizeof(List));

	temp = head->next;
	while (temp != NULL) {
		printf("%d\t", temp->element);
		temp = temp->next;
	}
	return SUCCES;
}
int Unija(list head1, list head2, list head3) {
	list temp1;
	list temp2;

	temp1 = (list)malloc(sizeof(List));
	temp2 = (list)malloc(sizeof(List));

	temp1 = head1->next;
	temp2 = head2->next;

	while (temp1 != NULL || temp2 != NULL) {
		if (temp1->element == temp2->element) {
			createUnija(temp1->element, head3);
			temp1 = temp1->next;
			temp2 = temp2->next;
		}
		else if (temp1->element > temp2->element) {
			createUnija(temp1->element, head3);
			temp1 = temp1->next;
		}
		else {
			createUnija(temp2->element, head3);
			temp2 = temp2->next;
		}

	}
	return SUCCES;
}

int createUnija(int el, list head) {
	list temp;
	temp = (list)malloc(sizeof(List));

	temp->element = el;
	temp->next = head->next;
	head->next = temp;


	return SUCCES;
}
int Presjek(list head1, list head2, list head4) {
	list temp1;
	list temp2;

	temp1 = (list)malloc(sizeof(List));
	temp2 = (list)malloc(sizeof(List));

	temp1 = head1->next;
	temp2 = head2->next;

	while (temp1 != NULL) {
		while (temp2 != NULL) {
			if (temp1->element == temp2->element) {
				createUnija(temp1->element, head4);
				temp2 = temp2->next;
				temp1 = temp1->next;
			}
			else
				temp2 = temp2->next;
		}
		temp1 = temp1->next;
		temp2 = head2->next;
	}
	return SUCCES;
}
