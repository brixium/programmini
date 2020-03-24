#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define DEBUG 0
#define STOPWATCH 0
#define LEIBNIZ 1
#define SARRUS 1
#define SARRUS4X4 1

long det(int *, int); /*returns the determinant*/
void swapColumns(int *, int, int, int); /*input: address of matrix, number of columns, index of first column, i of second column*/

int main(int argc, char * argv[]){
	int ncol, nelements, *values, i;
	#if STOPWATCH
	double elapsed_time;
	clock_t begin, end;

	begin = clock();
	#endif
	if(argc < 2){
		printf("How many columns does your matrix have? ");
		scanf("%d", &ncol);
		if(ncol > 0){
			nelements = ncol*ncol;
			if( (values = (int *)malloc(sizeof(int)*nelements)) ){
				printf("Insert the %d values of your matrix: ", nelements);
				for(i=0; i<nelements; i++){
					scanf("%d", values+i);
				}
				printf("\nDeterminant: %ld\n", det(values, ncol));
				free(values);
			}else
				printf("Out Of Memory Error! The application will shut down\n");
		}else
			printf("This matrix does not exist. The application will shut down\n");
	}else if(argc == 2){
		/*TODO: read from file. Command: ./det input.txt */
		printf("Sorry, this functionality isn't here yet. Try running the command witout parameters :)\n");
	}else if(argc == 3){
		/*TODO: read from file, number of columns given as a parameter before filename.txt . Es: ./det 4 values.txyt */
		printf("Sorry, this functionality isn't here yet. Try running the command witout parameters :)\n");
	}else
		printf("Too many arguments, the program will shut down\n");
	#if STOPWATCH
	end = clock();
	elapsed_time = (double)(end - begin) / CLOCKS_PER_SEC;
	printf("CPU Execution time: %f s\n", elapsed_time); /*Not the same as real world time*/
	#endif
	return 0;
}

long det(int * matrix, int ncol){
	int *submatrix, h, i, j, k, /*partial, */minus, nelsubmat, ncolsubmat, xpos, ypos, pivot;
	long sa1, sa2, partial;
	if(ncol == 1)
		return *matrix;
	#if LEIBNIZ
	if(ncol == 2)
		return ( *(matrix) * *(matrix+3) ) - ( *(matrix+1) * *(matrix+2) );
	#endif
	#if SARRUS
	if(ncol == 3){ /*Sarrus*/
		sa1 = 0;
		sa2 = 0;
		for(i=0; i<ncol; i++){
			sa1 = sa1 + *(matrix + (0*ncol) + i) * *( matrix + (1*ncol) + ((i+1)%ncol) ) * *( matrix + (2*ncol) + ((i+2)%ncol) ) ;
			sa2 = sa2 + *(matrix + (2*ncol) + i) * *( matrix + (1*ncol) + ((i+1)%ncol) ) * *( matrix + (0*ncol) + ((i+2)%ncol) ) ;
		}
		#if DEBUG
		printf("\nsa1:%ld, sa2:%ld\n", sa1, sa2);
		#endif
		return sa1-sa2;
	}
	#endif
	#if SARRUS4X4
	#if DEBUG
	printf("\n");
	#endif
	partial = 0;
	if(ncol == 4){
		for(j=0; j < 3; j++){
			for(i=0; i<ncol; i++){
				if( (j == 0 && i%2 == 0) || (j>0 && i%2 == 1) )
					minus = 1;
				else
					minus = -1;
				partial += *(matrix + (0*ncol) + i) * *( matrix + (1*ncol) + ((i+1)%ncol) ) * *( matrix + (2*ncol) + ((i+2)%ncol) ) * *( matrix + (3*ncol) + ((i+3)%ncol) ) * minus;
				partial += *(matrix + (3*ncol) + i) * *(matrix + (2*ncol) + ((i+1)%ncol) ) * *( matrix + (1*ncol) + ((i+2)%ncol) ) * *( matrix + (0*ncol) + ((i+3)%ncol) ) * minus;
				#if DEBUG
				printf("(i:%d,j:%d) I'm doing: %d * %d * %d * %d * %d(=minus)\n", i, j, *(matrix+i), *(matrix+ncol+((i+1)%4)), *(matrix+2*ncol+(i+2)%4), *(matrix+3*ncol+(i+3)%4), minus);
				printf("(i:%d,j:%d) I'm doing: %d * %d * %d * %d * %d(=minus)\n", i, j, *(matrix+(3*ncol)+i), *(matrix+(2*ncol)+((i+1)%4)), *( matrix + ncol + ( (i+2) %4 ) ), *(matrix+((i+3)%4)), minus);
				#endif
			}
			if(j==0)
				swapColumns(matrix, 4, 1, 2);
			else if(j == 1){
				swapColumns(matrix, 4, 1, 2);
				swapColumns(matrix, 4, 2, 3);
			}else if(j == 2){
				swapColumns(matrix, 4, 2, 3);
			}
		}
		return partial;
	}
	#endif
	/*Laplace*/
	pivot = *(matrix);
	ncolsubmat = ncol-1;
	nelsubmat = (ncolsubmat)*(ncolsubmat);
	partial = 0;
	if(( submatrix = (int *)malloc( sizeof(int) * nelsubmat ) )){
		xpos = 0;
		ypos = 0;
		h = 0;
		while(h < ncol){
			k=0;
			for(i=0; i<ncol; i++){
				for(j=0; j<ncol; j++){
					if(i != xpos && j != ypos){
						#if DEBUG
						printf("i:%d,j:%d Insert %d\n", i, j, *(matrix+(i*ncol)+j));
						#endif
						*(submatrix+k) = *(matrix+(i*ncol)+j);
						k++;
					}
				}
			}
			if((minus = ((xpos+ypos)%2)))
				minus = -minus;
			else
				minus = 1;
			if( pivot != 0)
				partial = partial + (minus * pivot * det(submatrix, ncolsubmat));
			ypos++; /*we are cycling by rows, so no updates from the column side*/
			pivot = *(matrix+(xpos*ncol)+ypos);
			h++;
		}
		free(submatrix);
		return partial;
	}else{
		printf("Out Of Memory error! Terminating\n");
		return -1;
	}
}

void swapColumns(int * m, int ncol, int ic1, int ic2){
	int i, aux;
	#if DEBUG
	printf("Changing column %d with column %d\n", ic1, ic2);
	#endif
	for(i=0; i<ncol; i++){
		aux = *(m+(i*ncol)+ic1);
		*(m+(i*ncol)+(ic1)) = *(m+(i*ncol)+(ic2));
		*(m+(i*ncol)+(ic2)) = aux;
	}
	return;
}
