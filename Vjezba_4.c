#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>
#define SUCCESS 0
#define ERROR -1
#define BUFFER_LENGTH 1024

typedef struct polinom* Position;
typedef struct polinom {
	int coefficient;
	int potention;
	Position Next;
}polinom;

int Create_Polinom(Position);
Position Insert_Polinom_Data(Position, int);
int Print_List(Position);
int Sort_Polinom(Position);
Position CreateListNode(Position);
int AddPolinom(Position, Position, Position); //unija
int MulPolinom(Position, Position, Position);
int Adjust_Pointers(Position, Position);
//Zadatak 5
int Cross_Section(Position, Position, Position);//presijek - samo elementi koji su isti za obe liste

int main(void) {

	polinom P1, P2, S, M, Cross;
	P1.Next = NULL;
	P2.Next = NULL;
	S.Next = NULL;
	M.Next = NULL;
	Cross.Next = NULL;
	int correct = 0;

	correct = Create_Polinom(&P1);
	if (correct != SUCCESS) {
		printf("\r\tError while creating polinom P1");
		return ERROR;
	}
	printf("\r\tFirst polinom: \n");
	Print_List(&P1);

	correct = Create_Polinom(&P2);
	if (correct != SUCCESS) {
		printf("\r\tError while creating polinom P2");
		return ERROR;
	}
	printf("\r\tSecond polinom: \n");
	Print_List(&P2);

	correct = AddPolinom(&P1, &P2, &S);
	if (correct != SUCCESS) {
		printf("\r\tError while creating polinom S");
		return ERROR;
	}
	printf("\r\tP1+P2 polinom: \n");
	Print_List(&S);

	correct = MulPolinom(&P1, &P2, &M);
	if (correct != SUCCESS) {
		printf("\r\tError while creating polinom M");
		return ERROR;
	}
	printf("\r\tP1*P2 polinom: \n");
	Print_List(&M);

	correct = Cross_Section(&P1, &P2, &Cross);
	if (correct != SUCCESS) {
		printf("\r\tError while creating polinom Cross");
		return ERROR;
	}
	printf("\r\tP1 i P2 polinom: \n");
	Print_List(&Cross);

	system("pause");
	return SUCCESS;
}
int Print_List(Position P) {
	P = P->Next;
	while (P!=NULL)
	{
		printf("\r\t %d * X^%d \n", P->coefficient, P->potention);
		P = P->Next;
	}
	return SUCCESS;
}
int Create_Polinom(Position P) {
	
	Position Q = NULL;
	int memberNum = 0;

	printf("\r\t\nPlease insert the number of members of this polynom (whole number):\n");
	scanf(" %d", &memberNum);

	for (int i = 0; i < memberNum; i++) {

		Q = CreateListNode(Q);
		if (Q == NULL) {
			printf("\r\tError while returning variable from Insert_Polinom_Data to Create_Polinom");
			return ERROR;
		}
		Q = Insert_Polinom_Data(Q, i);
		if (Q == NULL) {
			printf("\r\tError while returning variable from Insert_Polinom_Data to Create_Polinom");
			return ERROR;
		}

		Adjust_Pointers(P, Q);
		printf("\n");
	}

	Sort_Polinom(P);
	return SUCCESS;
}

int Adjust_Pointers(Position P, Position Q) {
	
	Q->Next = P->Next;
	P->Next = Q;
	return SUCCESS;
}
Position CreateListNode(Position Q)
{
	Q = (Position)malloc(sizeof(polinom));
	if (Q == NULL) {
		printf("\r\tError while allocating memory in CreateNew");
		return NULL;
	}

	Q->Next = NULL;

	return Q;
}
Position Insert_Polinom_Data(Position Q, int memberNum) {
	
	
	printf("\r\t\nInsert the coeficient of %d memeber: ", memberNum + 1);
	scanf(" %d", &(Q->coefficient));
	printf("\r\t\nInsert the potention of %d memeber: ", memberNum + 1);
	scanf(" %d", &(Q->potention));

	return Q;

}
int Sort_Polinom(Position P) {
	Position temp1 = P;
	Position temp2 = NULL;
	Position temp2_Prev = NULL;
	Position end = NULL;

	temp2_Prev = temp1->Next;
	temp2 = temp2_Prev->Next;
	Position tempDelete = NULL;
	
		while (temp2!= end) {
			if ((temp2_Prev->potention) < (temp2->potention)) {
				temp2_Prev->Next = temp2->Next;
				temp2->Next = temp1->Next;
				temp1->Next = temp2;

				temp2_Prev = temp2;
				temp2 = temp2->Next;
			}
			else if ((temp2_Prev->potention) == (temp2->potention)) {
				tempDelete = temp2_Prev;
				temp2->coefficient += temp2_Prev->coefficient;
				temp2_Prev = temp2;
				temp2 = temp2->Next;
				temp1->Next = temp2_Prev;
				free(tempDelete);
			}
			else {
				temp2_Prev = temp2;
				temp2 = temp2->Next;
			}
		
	}

	return SUCCESS;
	
}

int AddPolinom(Position P1, Position P2, Position S) { //Ovo je također i unija dviju složeni list
	Position Q = NULL;
	Position tmp = NULL;
	P1 = P1->Next;
	P2 = P2->Next;

	while (P1 != NULL && P2 != NULL) {
		Q = CreateListNode(Q);
		if (Q == NULL) {
			printf("\r\tError while returning variable rom CreateNew to Addpolinom\n");
			return ERROR;
		}
		if (P1->potention > P2->potention) {
			Q->potention = P1->potention;
			Q->coefficient = P1->coefficient;
			P1 = P1->Next;
		}
		else if (P1->potention < P2->potention) {
			Q->potention = P2->potention;
			Q->coefficient = P2->coefficient;
			P2 = P2->Next;
		}
		else if (P1->potention == P2->potention) {
			Q->potention = P1->potention;
			Q->coefficient = P1->coefficient + P2->coefficient;
			P1 = P1->Next;
			P2 = P2->Next;
		}

		Q->Next = S->Next;
		S->Next = Q;
	}

	if (P1 == NULL) {
		tmp = P2;
	}
	else
		tmp = P1;

	while (tmp != NULL) {
		Q = CreateListNode(Q);
		if (Q == NULL) {
			printf("\r\tError while returning variable rom CreateNew to Addpolinom\n");
			return ERROR;
		}
		Q->potention = tmp->potention;
		Q->coefficient = tmp->coefficient;
		tmp = tmp->Next;

		Q->Next = S->Next;
		S->Next = Q;
	}
	Sort_Polinom(S);
	return SUCCESS;
}

int MulPolinom(Position P1, Position P2, Position M) {
	Position Q = NULL;
	P1 = P1->Next;
	P2 = P2->Next;
	Position temp = P2;
	while (P1 != NULL) {
		while (temp != NULL) {
			Q = CreateListNode(Q);
			if (Q == NULL) {
				printf("\r\tError while returning variable rom CreateNew to Addpolinom\n");
				return ERROR;
			}
			Q->potention = (P1->potention) + (temp->potention);
			Q->coefficient = (P1->coefficient)*(temp->coefficient);

			Q->Next = M->Next;
			M->Next = Q;
			temp = temp->Next;
		}
		temp = P2;
		P1 = P1->Next;
	}

	Sort_Polinom(M);
	return SUCCESS;
}

int Cross_Section(Position P1, Position P2, Position Cross) {
	Position Q = NULL;
	P1 = P1->Next;
	P2 = P2->Next;
	Position temp = P2;
	while (P1 != NULL) {
		while (temp != NULL) {
			if (P1->coefficient == temp->coefficient && P1->potention == temp->potention) {
				Q = CreateListNode(Q);
				if (Q == NULL) {
					printf("\r\tError while returning variable rom CreateNew to Addpolinom\n");
					return ERROR;
				}
				Q->potention = temp->potention;
				Q->coefficient = temp->coefficient;

				Q->Next = Cross->Next;
				Cross->Next = Q;
			}
			temp = temp->Next;
		}
		temp = P2;
		P1 = P1->Next;
	}
	return SUCCESS;
}