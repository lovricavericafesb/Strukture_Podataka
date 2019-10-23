#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include<malloc.h>
#include <string.h>
#define MAX_BODOVI 50
#define MAX_CHAR 1024

typedef struct {
	char ime[MAX_CHAR];
	char prezime[MAX_CHAR];
	int bodovi;
	float rel_bod;
}_student;
int br_stud(const char *fileName);
_student *ucitaj_stud(const char *fileName, int br);
void ispis_bodova(_student *S, int br);

int main(void)
{
	_student* S = NULL;
	int br = 0;
	char fileName[MAX_CHAR] = { 0 };

	br = br_stud("studenti.txt");

	if (br <= 0)
	{
		printf("Greska!");
			return -1;
	}
	S = ucitaj_stud("studenti.txt", br);
	ispis_bodova(S, br);
	free(S);
	system("pause");
	return 0;
}
int br_stud(const char *fileName) {
	FILE *fp = NULL;
	int br = 0;
	char line[MAX_CHAR] = { 0 };

	if (fileName == NULL)
	{
		printf("File name cannot be NULL!\n");
		return -1;
	}
	if (strlen(fileName) == 0)
	{
		printf("File name cannot be empty string!\n");
		return -2;
	}
	fp = fopen(fileName, "r");
	if (!fp)
	{
		printf("File didn't open! -> %s", fileName);
		return -3;
	}
	while (!feof(fp)) // while not found end of file of fp
	{
		fgets(line, MAX_CHAR, fp);
		if (strlen(line) == 0)
		{
			continue;
		}
		br++;
	}
	fclose(fp);
	return br;
}
_student* ucitaj_stud(const char *fileName, int br) {
	FILE *fp = NULL;
	_student* students = NULL;
	int i = 0;
	if (fileName == NULL)
	{
		printf("File name cannot be NULL!\n");
		return NULL;
	}
	if (strlen(fileName) == 0)
	{
		printf("File name cannot be empty string!\n");
		return NULL;
	}
	fp = fopen(fileName, "r");
	if (!fp)
	{
		printf("File didn't open! -> %s", fileName);
		return NULL;
	}
	students = (_student*)malloc(br * sizeof(_student));
	if (!students)
	{
		fclose(fp);
		printf("Memory not allocated!");
		return NULL;
	}
	while (!feof(fp)) // while not found end of file of fp
	{
		if (fscanf(fp, " %d %s %s", &students[i].bodovi, students[i].ime, students[i].prezime) == 3)
		{
			i++;
		}
	}
	fclose(fp);
	return students;
}
void ispis_bodova(_student *S, int br) {
	int i = 0;
	if (!S)
	{
		printf("NIJE POSLANA NITI JEDAN STUDENT!");
		return NULL;
	}
	for (i = 0; i < br; i++)
		S[i].rel_bod = ((float)S[i].bodovi / MAX_BODOVI) * 100;
	for (i = 0; i < br; i++)
		printf("%s %s %d %2.2f\r\n", S[i].ime, S[i].prezime, S[i].bodovi, S[i].rel_bod);
}