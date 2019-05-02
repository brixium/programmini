#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define FILENAME "oui.csv"
#define MAXSIZE 6
#define LINELEN 1024
#define SEPARATOR ','
#define DELIMIT '"'

int isValidChar(char);

int main(int argc, char * argv[]){
	/*Variabili*/
	/*File da cui leggere*/
	FILE * fp;
	/*addr: indirizzo input; line: linea letta*/
	char inaddr[MAXSIZE+1], outaddr[MAXSIZE+1], line[LINELEN+1];
	/*contatore, posizione stringa argomento e successivamente riciclata come numero di occorrenze della virgola e infine come fine riga, posizione virgola separatrice, condizione di uscita dalla lettura, lunghezza del MAC inserito come parametro a linea di comando*/
	int i, j, sep, flag, parlen;

	/*L'utente inserisce in fase di avvio l'indirizzo MAC*/
	if(argc > 1){
		/*per la lunghezza della parte di vendor del MAC (6 byte)*/
		parlen = strlen(argv[1]);
		for(i=0, j=0; i<parlen && j<MAXSIZE; i++){
			/*Controllo se l'utente ha inserito una lettera minuscola e la metto maiuscola*/
			if(argv[1][i] >= 'a' && argv[1][i] <= 'f')
				argv[1][i] = toupper(argv[1][i]);
			/*Salta caratteri non validi quali : e -*/
			if(isValidChar(argv[1][i])){
				inaddr[j] = argv[1][i];
				j++;
			}
			/*printf("%c", inaddr[j]);*/
		}
	}else{
		/*Richiesta utente inserimento indirizzo MAC e salvataggio su inaddr con funzionalità ridotte (non puoi inserire spazi né trattini e tutte lettere maiuscole*/
		printf("Inserisci l'indirizzo MAC senza spazi né trattini con lettere maiuscole: ");
		scanf(" %s", &inaddr[0]);
	}
	/*In entrambi i casi inserisco qui il terminatore della stringa*/
	inaddr[MAXSIZE] = '\0';

	/*Lettura file*/
	if((fp = fopen(FILENAME, "r"))){
		if(!feof(fp)){
			flag = 1;
			/*Legge tutto il file e si ferma alla prima occorrenza del MAC address*/
			while(!feof(fp) && flag){
				/*Legge linea*/
				fgets(line, LINELEN, fp); 
				/*Scandisce la linea finché non trova la prima virgola. Allora si arresta*/
				for(i=0; line[i] != SEPARATOR && i<LINELEN; i++)
					;
				/*Indico dove sta la virgola*/
				sep = i;
				/*Riporto il MAC address trovato*/
				for(i=0; i<MAXSIZE; i++)
					outaddr[i] = line[i+sep+1];
				/*Nell'ultimo spazio inserisco sempre il terminatore*/
				outaddr[MAXSIZE] = '\0';
				/*Se il MAC inserito è uguale a quello della riga letta stampo le informazioni relative all'azienda che lo possiede*/
				if(strcmp(outaddr, inaddr) == 0){
					/*Stampa la riga di DB corrispondente.*/
					/*
					printf("%s", line);
					*/

					/*Salta gli indirizzi MAC e la prima riga*/
					for(i=0, j=0; j<2 && i<LINELEN; i++){
						if(line[i] == SEPARATOR)
							j++;
					}

					/*Stampa il nome dell'org.*/
					printf("Organization name: ");
					/*Controlla se il nome inizia per virgolette (e quindi ha una virgola al suo interno) oppure no*/
					if(line[i] == DELIMIT){
						i++;
						for(; line[i] != DELIMIT; i++)
							printf("%c", line[i]);
						i = i+2;
					}else{
						for(; line[i] != SEPARATOR; i++)
							printf("%c", line[i]);
						i++;
					}
					printf("\n");
					/*Stampa l'indirizzo*/
					printf("Organization address: ");
					if(line[i] == DELIMIT){
						i++;
						for(; line[i] != DELIMIT; i++)
							printf("%c", line[i]);
					}else{
						/*La riga finisce con il carattere di fine riga*/
						j = strlen(line);
						for(; i < j ; i++)
							printf("%c", line[i]);
					}
					flag = 0;
				}
			}
		}else
			printf("Il database degli indirizzi MAC è vuoto!\n");
		fclose(fp);
	}else
		printf("Cannot find %s\n", FILENAME);
	return 0;
}

/*Controlla che il carattere sia numerico in base 16*/
int isValidChar(char c){
	if((c >= 'A' && c<= 'F') || (c >= '0' && c <= '9'))
		return 1;
	return 0;
}
