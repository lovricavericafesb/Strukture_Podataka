#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>


typedef struct polinom {
	int koef;
	int pot;
	struct polinom* next;
}polinom;

int unos(polinom*);
int stvori(polinom*, int);
int ispis(polinom*);
int sortiraj(polinom*);
int zamjeni(polinom*, polinom*, polinom*);
int zbroji(polinom*, polinom*, polinom*);
int stvoriZbroj(polinom*, int, int);
int pomnozi(polinom*, polinom*, polinom*);
int sortirajUmnozak(polinom*);
int izbrisi(polinom*, polinom*);

int main(void) {
	polinom* head1;
	polinom* head2;
	polinom* headz;
	polinom* headu;


	head1 = (polinom*)malloc(sizeof(polinom));
	head2 = (polinom*)malloc(sizeof(polinom));
	headz = (polinom*)malloc(sizeof(polinom));
	headu = (polinom*)malloc(sizeof(polinom));


	head1->next = NULL;
	head2->next = NULL;
	headz->next = NULL;
	headu->next = NULL;

	unos(head1);
	unos(head2);

	sortiraj(head1);
	sortiraj(head2);

	ispis(head1);
	ispis(head2);

	zbroji(head1, head2, headz);
	printf("\nZbroj:\n");
	ispis(headz);

	pomnozi(head1, head2, headu);
	printf("\nNe sortirani umnozak je:\n");
	ispis(headu);
	printf("\nSortirani umnozak je:\n");
	sortirajUmnozak(headu);
	ispis(headu);

	return 0;
}
int unos(polinom* head) {
	int br_clan = 0, i = 0;

	printf("\nUnesi broj clanova novog polinoma: ");
	scanf(" %d", &br_clan);

	for (i = 0; i < br_clan; i++) {
		stvori(head, i);
	}
	printf("\n");

	return 0;

}
int stvori(polinom* head, int i) {
	polinom* p;
	p = (polinom*)malloc(sizeof(polinom));

	p->next = head->next;
	head->next = p;

	printf("\nUnesite koeficijent %d. clana: ", i + 1);
	scanf(" %d", &(p->koef));
	printf("\nUnesite potenciju %d. clana: ", i + 1);
	scanf(" %d", &(p->pot));

	return 0;
}
int ispis(polinom* head) {
	polinom* temp;
	temp = (polinom*)malloc(sizeof(polinom));

	temp = head->next;
	while (temp != NULL) {
		if (temp->next == NULL) {
			printf("%dx^%d\n", temp->koef, temp->pot);
			temp = temp->next;
		}
		else {
			printf("%dx^%d + ", temp->koef, temp->pot);
			temp = temp->next;
		}
	}

	free(temp);
	return 0;
}
int sortiraj(polinom* head) {
	polinom* temp1;
	polinom* temp2;
	polinom* p;
	

	temp1 = (polinom*)malloc(sizeof(polinom));
	temp2 = (polinom*)malloc(sizeof(polinom));
	p = (polinom*)malloc(sizeof(polinom));


	temp1 = head->next;
	temp2 = temp1->next;
	p = head->next;

	while (temp1->next != NULL) {
		while (temp2 != NULL) {
			
			if (temp1->pot < temp2->pot)
				zamjeni(temp1, temp2, head);
			else {
				temp2 = temp2->next;
			}
		}
		p = p->next;
		temp1 = p;
		temp2 = temp1->next;
	}

	
	return 0;
}
int zamjeni(polinom* p1, polinom* p2, polinom* head) {
	polinom* prev1;
	polinom* prev2;
	polinom* temp1;
	polinom* temp2;

	prev1 = (polinom*)malloc(sizeof(polinom));
	prev2 = (polinom*)malloc(sizeof(polinom));
	temp1 = (polinom*)malloc(sizeof(polinom));
	temp2 = (polinom*)malloc(sizeof(polinom));

	prev1 = head;
	prev2 = head;

	if (p1->next == p2) {
		while (prev1->next != p1)
			prev1 = prev1->next;
		prev1->next = p2;
		temp1->next = p2->next;
		p2->next = p1;
		p1->next = temp1->next;
		
	}
	else if (p2->next == p1) {
		     while (prev2->next != p2)
			     prev2 = prev2->next;
		     prev2->next = p1;
		     temp1->next = p1->next;
		     p1->next = p2;
		     p2->next = temp1->next;

	}
	else {
		while (prev1->next != p1)
			prev1 = prev1->next;
		while (prev2->next != p2)
			prev2 = prev2->next;

		temp1->next = p1->next;
		p1->next = p2->next;
		p2->next = temp1->next;

		temp2->next = prev1->next;
		prev1->next = prev2->next;
		prev2->next = temp2->next;
	}
	
	

	

	return 0;
}
int zbroji(polinom* head1, polinom* head2, polinom* headz) {
	polinom* temp1;
	polinom* temp2;

	temp1 = (polinom*)malloc(sizeof(polinom));
	temp2 = (polinom*)malloc(sizeof(polinom));

	temp1 = head1->next;
	temp2 = head2->next;

	while (temp1 != NULL || temp2 != NULL) {
		if (temp1->pot == temp2->pot) {
			stvoriZbroj(headz, temp1->koef + temp2->koef, temp1->pot);
			temp1 = temp1->next;
			temp2 = temp2->next;
		}
		else if (temp1->pot > temp2->pot) {
			stvoriZbroj(headz, temp1->koef, temp1->pot);
			temp1 = temp1->next;
		}
		else {
			stvoriZbroj(headz, temp2->koef, temp2->pot);
			temp2 = temp2->next;
		}
	}
	return 0;
}
int stvoriZbroj(polinom* head, int k, int p) {
	polinom* temp;
	temp = (polinom*)malloc(sizeof(polinom));

	temp->koef = k;
	temp->pot = p;

	temp->next = head->next;
	head->next = temp;

	return 0;
}
int pomnozi(polinom* head1, polinom* head2, polinom* headu) {
	polinom* temp1;
	polinom* temp2;

	temp1 = (polinom*)malloc(sizeof(polinom));
	temp2 = (polinom*)malloc(sizeof(polinom));

	temp1 = head1->next;
	temp2 = head2->next;

	while (temp1 != NULL) {
		while (temp2 != NULL) {
			if (temp1->pot == 0) {
				stvoriZbroj(headu, temp1->koef * temp2->koef, temp2->pot);
				temp2 = temp2->next;
			}
			else if (temp2->pot == 0) {
				stvoriZbroj(headu, temp1->koef * temp2->koef, temp1->pot);
				temp2 = temp2->next;
			}
			else {
				stvoriZbroj(headu, temp1->koef * temp2->koef, temp1->pot + temp2->pot);
				temp2 = temp2->next;
			}
		}
		temp1 = temp1->next;
		temp2 = head2->next;
	}

	return 0;

}
int sortirajUmnozak(polinom* headu) {
	polinom* temp1;
	polinom* temp2;
	polinom* temp3;
	polinom* prev2;

	temp1 = (polinom*)malloc(sizeof(polinom));
	temp2 = (polinom*)malloc(sizeof(polinom));
	temp3 = (polinom*)malloc(sizeof(polinom));


	temp1 = headu->next;
	temp2 = temp1->next;
	temp3 = headu->next;
	

	while (temp1->next != NULL) {
		while (temp2 != NULL) {
			if (temp1->pot == temp2->pot) {
				temp1->koef = temp3->koef + temp2->koef;
				izbrisi(headu, temp2);
				temp2 = temp2->next;
			}
			else
				temp2 = temp2->next;
		}
		temp3 = temp3->next;
		temp1 = temp3;
		temp2 = temp1->next;
	}
}
int izbrisi(polinom* head, polinom* p) {
	polinom* prev;
	prev = (polinom*)malloc(sizeof(polinom));

	prev = head->next;
	while (prev->next != p)
		prev = prev->next;
	if (prev->next != p)
	{
		printf("\nElement nije pronadjen!\n");
		return 0;
	}
	else {
		prev->next = p->next;
		return 0;
	}
}
