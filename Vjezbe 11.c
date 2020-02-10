#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<malloc.h>
#define MAX 256
#define SIZE 11
typedef struct Student* pokStud;
typedef struct Student {
	char ime[MAX];
	char prezime[MAX];
	int m_broj;
	pokStud next;
}Student;
typedef struct Hash {
	pokStud element;
}Hash;

Student** initializeTable();
int inputElement(int, Student**);
int ReadFile(Student**, char*);
int Unos(Student**, char*, char*, int);
int Ispis(Student**);
int PronadiElement(Student**, char*, char*);
int main()
{
	Student** tablica = (Student**)malloc(SIZE * sizeof(Student*));
	int i = 0;
	for (i = 0; i < SIZE; i++) {
		tablica[i] = NULL;
	}
	char filename[MAX] = { 0 };
	printf("Unesite ime datoteke: ");
	scanf(" %s", filename);
	if (strchr(filename, '.') == NULL)
		strcat(filename, ".txt");
	int indikator = ReadFile(tablica, filename);
	if (!indikator)
		return 0;
	Ispis(tablica);
	char trazeno_ime[MAX] = { 0 };
	char trazeno_prezime[MAX] = { 0 };
	printf("Unesite ime i prezime studenta kojem zelite znati maticni broj: ");
	scanf(" %s %s", trazeno_ime, trazeno_prezime);
	PronadiElement(tablica, trazeno_ime, trazeno_prezime);

	return 0;
}
int inputElement(int i, Student** tablica)
{
	if (i == 0) {
		memset(tablica[i]->ime, 0, MAX);
		memset(tablica[i]->prezime, 0, MAX);
		tablica[i]->m_broj = 0;
		tablica[i]->next = NULL;
		return 0;
	}
	tablica[i - 1]->next = tablica[i];
	tablica[i] = NULL;
	memset(tablica[i]->ime, 0, MAX);
	memset(tablica[i]->prezime, 0, MAX);
	tablica[i]->m_broj = 0;
	return 0;
}
int ReadFile(Student** tablica, char* filename)
{
	FILE* fp = fopen(filename, "r");
	char buffer[MAX] = { 0 };
	char ime[MAX] = { 0 };
	char prezime[MAX] = { 0 };
	int maticni = 0;
	int i = 0;
	if (!fp) {
		printf("Datoteka nije otvorena!");
		return 0;
	}
	while (!feof(fp)) {
		fgets(buffer, MAX, fp);
		sscanf(buffer, "%s %s %d", ime, prezime, &maticni);
		Unos(tablica, ime, prezime, maticni);
		
	}
	return 1;
}
int Unos(Student** tablica, char* ime, char* prezime, int maticni)
{
	int pozicija = 0;
	int suma = 0;
	int i = 0;
	for (i = 0; i < sizeof(prezime); i++)
		suma += (int)prezime[i];
	pozicija = suma % SIZE;
	Student* element = tablica[pozicija];
	if(element != NULL)
		while (element != NULL) {
			pozicija++;
			if (pozicija >= SIZE)
				pozicija = 0;
			element = tablica[pozicija];
		}
	element = (Student*)malloc(sizeof(Student));
	strcpy(element->ime, ime);
	strcpy(element->prezime, prezime);
	element->m_broj = maticni;
	element->next = NULL;
	tablica[pozicija] = element;
	return 1;
}
int Ispis(Student** tablica)
{
	int i = 0;
	for (i = 0; i < SIZE; i++) {
		if (tablica[i] != NULL)
			printf("%d %s %s %d\n", i + 1,tablica[i]->ime, tablica[i]->prezime, tablica[i]->m_broj);
	}
	return 0;
}
int PronadiElement(Student** tablica, char* ime, char* prezime)
{
	int i = 0;
	for (int i = 0; i < SIZE; i++) {
		if(tablica[i] != NULL)
			if ((strcmp(tablica[i]->ime, ime) == NULL) && (strcmp(tablica[i]->prezime, prezime) == NULL)) {
				printf("Maticni broj trazenog studenta je %d\n", tablica[i]->m_broj);
				return 0;
			}
	}
	printf("Taj student ne postoji!\n");
	return 0;
}
