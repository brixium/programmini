#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define DEBUG
#define QUICK
/*#define BUBBLE*/
#define N 12 /*16777216=2^24 numeri*/

void quicksort(int *, int, int, int);
int qs_partition(int *, int, int, int);
void printnum(int *, int);
void printrange(int *, int, int);
void bubblesort(int *, int);

int main(int argc, char * argv[]){
	int * numeri, i;
	clock_t begin, end;
	double time_spent;
	
	srand(time(NULL));
	#ifdef QUICK
	if( (numeri = (int *)malloc(sizeof(int)*N)) ){
	/*inizializzazione*/
		/*
		*numeri = 1;
		*(numeri+1) = 2;
		*(numeri+2) = 7;
		*(numeri+3) = 5;
		*(numeri+4) = 8;
		*(numeri+5) = 3;
		*(numeri+6) = 3;
		*(numeri+7) = 0;
		*(numeri+8) = 4;
		*(numeri+9) = 4;
		*(numeri+10) = 5;
		*(numeri+11) = 3;
		*/
		
		for(i=0; i<N; i++)
			*(numeri+i) = ( rand() % 10 );
		
		begin = clock();
		quicksort(numeri, N, 0, N-1);
		end = clock();
		time_spent = (double)(end-begin) / CLOCKS_PER_SEC;
		printf("[QS] Time spent by the CPU: %lf s\n", time_spent);
		free(numeri);
/*Faccio il bubble sort per confronto*/
		
	}else
		printf("Not enough memory for %d bytes\n", N*4);
	#endif
	#ifdef BUBBLE
	if( (numeri = (int *)malloc(sizeof(int)*N)) ){
		begin = clock();
		bubblesort(numeri, N);
		end = clock();
		time_spent = (double)(end-begin) / CLOCKS_PER_SEC;
		printf("[BS] Time spent by the CPU: %lf s\n", time_spent);
		free(numeri);
	}else
		printf("Not enough memory for %d bytes\n", N*4);
	#endif
	return 0;
}
void printnum(int * arr, int len){
	int i;
	/*Questa parte commentata stampa in orizzontale con sopra la posizione*/
	/*
	for(i=0; i<len; i++)
		printf("%d|", i);
	printf("\n");
	for(i=0; i<len; i++)
		printf("%d|", *(arr+i));
	printf("\n");
	*/
	for(i=0; i<len; i++)
		printf("%d: %d\n", i, *(arr+i));
	return;
}
void printrange(int * arr, int min, int max){
	int i;
	for(i=min; i<=max; i++)
		printf("%d: %d\n", i, *(arr+i));
	return;
}
void quicksort(int * num, int len, int lo, int hi){
	int p;
	if(lo<hi){
		p = qs_partition(num, len, lo, hi);
		quicksort(num, len, lo, p);
        quicksort(num, len, p+1, hi);
	}
	return;
}
int qs_partition(int * num, int len, int lo, int hi){
	int pivot, i, j, aux;
	pivot = *(num+((hi+lo)/2));
	i = lo - 1;
	j = hi + 1;
	while(1){
		do
			i++;
		while(*(num+i) < pivot);
		do
			j--;
		while(*(num+j) > pivot);
		if(i>=j)
			return j;
		#ifdef DEBUG
		printf("Prima\n");
		printrange(num, lo, hi);
		#endif
		aux = *(num+i);
		*(num+i) = *(num+j);
		*(num+j) = aux;
		#ifdef DEBUG
		printf("Dopo ho scambiato el.%d con el.%d\n", j, i);
		printrange(num, lo, hi);
		#endif
	}
}

void bubblesort(int * num, int len){
	int i, j, aux;
	j=0;
	do{
		for(i=1; i<len; i++){
			if( *(num+i-1) > *(num+i) ){
				aux = *(num+i-1);
				*(num+i-1) = *(num+i);
				*(num+i) = aux;
			}
		}
		j++;
	}while(j<len);
	return;
}
