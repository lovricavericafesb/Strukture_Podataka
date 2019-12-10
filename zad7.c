#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#include <string.h>
#define BUFFER 1024
#define SUCCESS 0
#define ERROR -1

typedef struct Stog* Nod;
typedef struct Stog {
  int element;
  Nod next;
}Stog;

int push(int Element, Nod Stog);
int pop(Nod Stog);
int rezultPostfix(Nod Stog, const char *fileName);

int main(void)
{
    Nod head;
    head = (Nod)malloc(sizeof(Stog));
    head->next = NULL;
    int rezult = 0;


    char *fileName;

    fileName = (char*)malloc(sizeof(char)* BUFFER);
    if (fileName == NULL) {
        printf("Memory not poperly alocated for fileName");
        return ERROR;
    }

    memset(fileName, '\0', BUFFER);

    rezult = rezultPostfix(&head, "postfiks.txt");

    return 0;
}

int rezultPostfix(Nod Stog, const char *fileName) {
    FILE *fp = NULL;
    int number = 0;

    if (fileName == NULL)
    {
        printf("File name can not be NULL!\n");
        return ERROR;
    }

    if (strlen(fileName) == 0)
    {
        printf("File can't be an empty string!\n");
        return ERROR;
    }

    fp = fopen(fileName, "r");
    if (!fp)
    {
        printf("File didn't open! -> %s", fileName);
        return ERROR;
    }

    while (!feof(fp))
    {
         int howManyBytes = 0;
         char buffer[BUFFER] = { 0 };
         char *p = buffer;
         fgets(buffer, BUFFER, fp);



    if (sscanf(p, " %d %n", &number, &howManyBytes) == 1) {
        push(number, Stog);
        p += howManyBytes;
    }
    else
    {

    }



}
