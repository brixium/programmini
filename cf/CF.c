/*
Programma per il calcolo di CF
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAXDIM 40
#define PADDING 'X'
#define CFDIM 16

int isVocal(char);
char * surname(char[], int);

int main(int argc, char * argv[]){
	char name[MAXDIM+1];
	char sur[MAXDIM+1];
	char sex;
	int year;
	int month;
	int day;
	char birthplace[MAXDIM+1];
	char cf[CFDIM+1];

	printf("Inserisci il tuo cognome: ");
	scanf(" %s", &sur[0]);
	strcpy(cf, surname(sur, strlen(sur)));
	printf("%s\n", cf);
	return 0;
}

char * surname(char cognome[], int dim){
	char * ris;
	int i, k, flag;

	ris = malloc(sizeof(char)*3);
	if(!ris)
		return NULL;
	flag = 0;
	k = 0;
/*Converto stringa in maiuscolo*/
	for(i=0; i<dim; i++)
		cognome[i] = toupper(cognome[i]);
/*Controllo consonanti*/
	for(i=0; i<dim && k<3; i++)
		if(!isVocal(cognome[i])){
			ris[k] = cognome[i];
			k++;
		}
	if(k>=3)
		return ris;
/*Controllo vocali*/
	for(i=0; i<dim && k<3; i++)
		if(isVocal(cognome[i])){
			ris[k] = cognome[i];
			k++;
		}
	if(k>=3)
		return ris;
	for(i=k; i<3; i++)
		ris[i] = PADDING;
	return ris;
}

int isVocal(char val){
	if(val == 'a' || val == 'A' || val == 'e' || val == 'E' || val == 'i' || val == 'I' || val == 'o' || val == 'O' || val == 'u' || val == 'U')
		return 1;
	return 0;
}
