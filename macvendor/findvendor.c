#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FILENAME "oui.csv"
#define MAXSIZE 6
#define LINELEN 1024
#define SEPARATOR ','

int main(int argc, char * argv[]){
	/*Variabili*/
	/*File da cui leggere*/
	FILE * fp;
	/*addr: indirizzo input; line: linea letta*/
	char inaddr[MAXSIZE+1], outaddr[MAXSIZE+1], line[LINELEN+1];
	/*contatore*/
	int i, sep;

	/*L'utente inserisce in fase di avvio l'indirizzo MAC*/
	if(argc > 1)
		strcpy(inaddr, argv[1]);
	else{
		/*Richiesta utente inserimento indirizzo MAC*/
		printf("Inserisci l'indirizzo MAC senza spazi né trattini: ");
		scanf(" %s", &inaddr[0]);
	}
	/*In entrambi i casi inserisco qui il terminatore della stringa*/
	inaddr[MAXSIZE] = '\0';

	/*Lettura file*/
	if((fp = fopen(FILENAME, "r"))){
		if(!feof(fp)){
			while(!feof(fp)){
				fgets(line, LINELEN, fp); 
				/*printf("%s",line);*/
				for(i=0; line[i] != SEPARATOR && i<LINELEN; i++)
					;
				sep = i;
				for(i=0; i<MAXSIZE; i++)
					outaddr[i] = line[i+sep+1];
				outaddr[MAXSIZE] = '\0';
				if(strcmp(outaddr, inaddr) == 0)
					printf("%s", line);
			}
		}else
			printf("Il database degli indirizzi MAC è vuoto!\n");
		fclose(fp);
	}else
		printf("Cannot find %s\n", FILENAME);
	return 0;
}


