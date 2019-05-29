/*
PROBLEMA CORRENTE: SEGFAULT, VEDI RIGA 167
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <wchar.h>
#include <locale.h>
/*Stabilisco alcune cose: nomi dei file in ingresso, lunghezza stringhe*/
#define TABELLA1 "macchina_3508.CSV"
#define TABELLA2 "tabella_portoghese_giusta.CSV"
#define ERRORLOG "ERRORI.TXT"
#define STRLENMAX 1024
#define SEPARATOR ';'
#define COLID 5
#define COLCHANGE 6

int main(int argc, char * argv[]){
	/*Dichiarazione variabili*/
	/*
	t1, t2 ed err sono rispettivamente la tabella su cui sostituire il testo, la tabella da cui prelevare il testo e il file di log degli errori.
	Durante l'utilizzo del programma, controllare sempre gli errori.
	*/
	FILE * t1, * t2, * err;
	char riga1[STRLENMAX];
	char inglese1[STRLENMAX], inglese2[STRLENMAX];
/*	char portoghese1[STRLENMAX];*/
	char riga2[STRLENMAX];
	char tab2[STRLENMAX][STRLENMAX];
	int i, j, k, l, riga1len, riga2len, npv, npv2, flag, tab2nrows, tab2maxcol, aux, p;
	int debug_nriga, nerrors;
	wchar_t portoghese1[STRLENMAX], portoghese2[STRLENMAX];
	
	/*Codice*/
	debug_nriga = 1;
	nerrors = 0;
	setlocale(LC_ALL, "pt_BR.UTF-8");
	
	/*Leggo n.righe file dizionario e salvo il dato*/
	if((t2 = fopen(TABELLA2, "r"))){
		for(i=0, flag=1; i<STRLENMAX && flag; i++){
			fgets(&tab2[i][0], STRLENMAX, t2);
		}
	}
	/*
	tab2nrows = 0;
	tab2maxcol = 0;
	if((t2 = fopen(TABELLA2, "r"))){
		if(!feof(t2)){
			do{
				fscanf(t2, "%s", riga1);
				aux = strlen(riga1);
				if(aux > tab2maxcol)
					tab2maxcol = aux;
				tab2nrows++;
			}while(!feof(t2));
		}else{
			printf("Errore: file dizionario (%s) non trovato! Il programma termina\n", TABELLA2);
			return(1);
		}
		if((*tab2 = malloc(sizeof(wchar_t)*tab2nrows)))
			;
		if(tab2 == NULL)
			return(1);
		fclose(t2);
		if((t2 = fopen(TABELLA2, "r"))){
			fgets(*tab2, tab2maxcol, t2);
			*(tab2+20-1) = '\0';
			printf("%s", *tab2);
			if(!feof(t2))
				for(i=1; !feof(t2); i++){
					printf("%d", strlen(*tab2));
					fgets(*(tab2+i+strlen(*tab2)), tab2maxcol, t2);
				}
		}else{
			printf("Errore nella lettura del file %s, il programma termina\n", TABELLA2);
			return(1);
		}
	}
	*/

	/*Apertura file TABELLA1*/
	if((t1 = fopen(TABELLA1, "r"))){
		printf("File %s aperto correttamente\n", TABELLA1);
		/*Apertura file TABELLA2*/
		if((t2 = fopen(TABELLA2, "r"))){
			printf("File %s aperto correttamente\n", TABELLA2);
			/*(TABELLA 1) Lettura prima riga e controllo EOF
			ASSUNZIONE: si ignora la prima riga in quanto intestazione della tabella
			*/
			if(!feof(t1)){
				fgets(&riga1[0], STRLENMAX, t1);
				/*Apro il file di error log*/
				if((err = fopen(ERRORLOG, "w"))){
					/*Lettura di ciascuna riga fino alla fine TABELLA1*/
					while(!feof(t1)){
						fgets(&riga1[0], STRLENMAX, t1);
						/*printf("Prima riga %s\n", riga);*/
						riga1len = strlen(riga1);
	/*					printf("%s\n", &riga1[0]);*/
						for(i=0, npv=0, flag=1; i<riga1len && flag; i++){
							if(riga1[i] == SEPARATOR)
								npv++;
							if(npv == COLID-1)
								flag = 0;
						}
						/*Qui dentro salvo su inglese1 la stringa in inglese, in portoghese1 l'altra*/
/*						printf("Carattere %d\n", i);*/
						for(j=0; i<STRLENMAX && riga1[i] != SEPARATOR; j++, i++)
							inglese1[j] = riga1[i];
						if(riga1[i] == SEPARATOR)
							i++;
						inglese1[j] = '\0';
/*						printf("Carattere %d\n", i);*/
						for(j=0; i<STRLENMAX && riga1[i] != SEPARATOR; j++, i++)
							portoghese1[j] = riga1[i];
						if(riga1[i] == SEPARATOR)
							i++;
						portoghese1[j] = '\0';
						/*printf("Caratrtere %d\n", i);*/
						/*
						printf("Inglese: %s\nPortoghese: ", inglese1);
						wprintf(L"%ls\n", portoghese1);
						*/
						/*Controllo degli errori*/
						if(npv != COLID-1){ /*Questa è una condizione di errore*/
						/*Questo può succedere se la stringa da tradurre è divisa in più righe*/
							if(err){
								fprintf(err, "Err: %d %c presenti in riga %d; testo riga:\n", npv, SEPARATOR, debug_nriga);
								fprintf(err, "\t%s", &riga1[0]);
								nerrors++;
							}else
								printf("Err: %d %c in riga %d; testo:\n", npv, SEPARATOR, debug_nriga);
							printf("%s", &riga1[0]);
						}else{
							/*Se non ci sono stati errori nel parsing del file, allora scorro il secondo file alla ricerca della riga da sostituire*/
							/*Mi correggo: NON SCORRO IL FILE MA LA SUA RAPPRESENTAZIONE CHE HO CREATO E SI CHIAMA TAB2*/
							for(k=0; k<STRLENMAX; k++){
								npv2 = 0;
								for(l=0, flag=1; l<STRLENMAX && flag; l++){
									if(tab2[k][l] == SEPARATOR)
										npv2++;
									if(npv2 == COLID-1)
										flag = 0;
								}
								l++;
								/*Potrebbe essere la nostra stringa; Verificare il resto della corrispondenza*/
								if(tab2[k][l] == inglese1[0]){
									aux = strlen(inglese1);
									for(p=0; p<aux; p++)
										inglese2[p] = tab2[k][l+p];
									inglese2[p] = '\0';
									if(strcmp(inglese2, inglese1)){
										/*Abbiamo trovato una corrispondenza tra il file della macchina e quello del dizionario, vado avanti con il portoghese*/
										for(p=0; p<STRLENMAX && portoghese2[p] != SEPARATOR; p++)
											/*Sostituisco la stringa portoghese2, che prelevo dalla matrice, a portoghese1*/
											portoghese2[p] = tab2[k][l+p];
										portoghese2[p] = '\0';
										/*
										wcscpy(portoghese1, portoghese2);
										fwprintf(stdout, portoghese1);
										*/
										/*Il prossimo passo è quello di sostituire portoghese1 nella prima tabella al posto del portoghese*/


										/*SONO PIÙ O MENO ARRIVATO QUI PERÒ SE SCOMMENTO STA ROBA MI DÀ SEGFAULT*/
									}
								}
							}

							/*
							fgets(&riga2[0], STRLENMAX, t2);
							if(!feof(t2)){
								while(!feof(t2)){
									fgets(&riga2[0], STRLENMAX, t2);
									riga2len = strlen(riga2);
									for(k=0, npv2=0, flag=1; k<riga2len && flag; i++){
										if(riga2[i] == SEPARATOR)
											npv2++;
										if(npv2 == COLID-1)
											flag = 0;
									}
								}
							}else
								printf("Il file %s è vuoto\n", TABELLA2);
							*/
						}
						debug_nriga++;
						printf("Nr. riga file 1: %d\n", debug_nriga);
					}
					fprintf(err, "N. errori: %d\n", nerrors);
					fclose(err);
				}else
					printf("Errore nell'apertura del file %s\n", ERRORLOG);
			}else
				printf("Il file %s è vuoto :\\\n", TABELLA1);
			fclose(t2);
		}else
			printf("Errore nell'apertura del file %s\n", TABELLA2);
		fclose(t1);
	}else
		printf("Errore nell'apertura del file %s\n", TABELLA1);
	printf("Il programma termina\n");
	return 0;
}
