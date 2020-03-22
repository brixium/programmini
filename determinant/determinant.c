#include <stdio.h>
#include <stdlib.h>

#define DEBUG 0

int det(int *, int); /*returns the determinant*/

int main(int argc, char * argv[]){
	int ncol, nelements, *values, i;
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
				printf("\nDeterminant: %d\n", det(values, ncol));
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
	return 0;
}

int det(int * matrix, int ncol){
	int *submatrix, h, i, j, k, partial, minus, nelsubmat, ncolsubmat, xpos, ypos, pivot;

	if(ncol == 1)
		return *matrix;
	if(ncol == 2)
		return ( *matrix * *(matrix+2) ) - ( *(matrix+1) * *(matrix+3) );
	if(ncol == 3){ /*Sarrus*/
		h = 0;
		k = 0;
		for(i=0; i<ncol; i++){
			h = h + *(matrix + (0*ncol) + i) * *( matrix + (1*ncol) + ((i+1)%3) ) * *( matrix + (2*ncol) + ((i+2)%3) ) ;
			k = k + *(matrix + (2*ncol) + i) * *( matrix + (1*ncol) + ((i+1)%3) ) * *( matrix + (0*ncol) + ((i+2)%3) ) ;
		}
		#if DEBUG
		printf("\nh:%d, k:%d\n", h, k);
		#endif
		return h-k;
	}
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

