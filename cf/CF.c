/*
Programma per il calcolo di CF
*/
#include <stdio.h>

#define PADDING 'X'
int main(int argc, char * argv[]){
	
	printf("%s", );
	return 0;
}

char * surname(char cognome[], int dim){
	char ris[3];
	int i, k, flag;
	flag = 0;
	k = 0;
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
