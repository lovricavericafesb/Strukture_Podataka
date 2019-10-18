#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include<malloc.h>
#include <string.h>
#define MAX 50
#define BR 120 

typedef struct {
	char ime[BR];
	char prezime[BR];
	int bodovi;
	float rel_bod;
}_student;
int brojstud(FILE *file);
void printbodovi(_student *S, int br, FILE *file);

int main(void)
{
	_student *S;
	FILE *ulz;
	int br = 0;
	ulz = fopen("studenti.txt", "r");
	br = brojstud(ulz);
	S = (_student *)malloc(br * sizeof(_student));
	printbodovi(S, br, ulz);
	free(S);
	system ("pause");
	return 0;
}
int brojstud(FILE *file) {
	int br = 0;
	if (file == NULL)
	{
		puts("Greska pri otvaranju datoteke!");
	}

	while (!feof(file))
		if (fgetc(file) == '\n') ++br;
	rewind(file);
	return br;
}
void printbodovi(_student *S, int br, FILE *file) {
	int i = 0;
	for (i = 0; i < br; i++) {
		fscanf(file, " %d %s %s", &S[i].bodovi, S[i].ime, S[i].prezime);
	}

	for (i = 0; i < br; i++)
		S[i].rel_bod = ((float)S[i].bodovi / MAX) * 100;
	for (i = 0; i < br; i++)
		printf("%s %s %d %2.2f\r\n", S[i].ime, S[i].prezime, S[i].bodovi, S[i].rel_bod);
}