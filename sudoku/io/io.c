#include "io.h"

void printGrid(){
	int i, j, k;
	for(i=0; i<NINE*2+1; i++)
        printf("%c", DASH);
	printf("\n");
	for(i=0; i<NINE; i++){
		for(j=0; j<NINE; j++){
			if(j%3 == 0){
				if(grid[i][j].num > 0 && grid[i][j].num < 10)
					printf("%c%d", PIPE, grid[i][j].num);
				else
					printf("%c%c", PIPE, SPACE);
			}else{
				if(grid[i][j].num > 0 && grid[i][j].num < 10)
					printf("%c%d", SPACE, grid[i][j].num);
				else
					printf("%c%c", SPACE, SPACE);
			}
		}
		printf("%c", PIPE);
		printf("\n");
		if(i%THREE==2){
			for(k=0; k<NINE*2+1; k++)
				printf("%c", DASH);
			printf("\n");
		}
	}
	return;
}

void printCandidatesCell(int x, int y){
	int k;
	for(k=0; k<NINE; k++)
		if(grid[x][y].candidates[k] != 0)
			printf("%d%c", k+1, SPACE);
	printf("\n");
	return;
}

void printAllCandidates(){
	int i, j, k;
	for(i=0; i<NINE; i++)
		for(j=0; j<NINE; j++){
			printf("x:%d, y:%d; candidates: ", i+1, j+1);
			/*printCandidatesCell(i, j);*/
			for(k=0; k<NINE; k++)
				if(grid[i][j].candidates[k] != 0)
					printf("%d%c", k+1, SPACE);
			printf("\n");

		}
	return;
}

void printHorizontally(){
	int i, j, k;
	/*First line, two lines of dashes*/
	for(j=0; j<2; j++){
		for(i=0; i<NINE*2+1; i++)
    	    printf("%c", DASH);
		printf("%c%c", SPACE, SPACE);
	}
	printf("\n");
	/*Main part of the grids with their values*/
	for(i=0; i<NINE; i++){
		/*rows of the first grid*/
		for(j=0; j<NINE; j++){
			if(j%3 == 0){
				if(copy[i][j].num > 0 && copy[i][j].num < 10)
					printf("%c%d", PIPE, copy[i][j].num);
				else
					printf("%c%c", PIPE, SPACE);
			}else{
				if(copy[i][j].num > 0 && copy[i][j].num < 10)
					printf("%c%d", SPACE, copy[i][j].num);
				else
					printf("%c%c", SPACE, SPACE);
			}
		}
		/*Two spaces gap*/
		printf("|%c%c", SPACE, SPACE);
		/*rows of the second grid*/
		for(j=0; j<NINE; j++){
			if(j%3 == 0){
				if(grid[i][j].num > 0 && grid[i][j].num < 10)
					printf("%c%d", PIPE, grid[i][j].num);
				else
					printf("%c%c", PIPE, SPACE);
			}else{
				if(grid[i][j].num > 0 && grid[i][j].num < 10)
					printf("%c%d", SPACE, grid[i][j].num);
				else
					printf("%c%c", SPACE, SPACE);
			}
		}
		/*Last pipe of second grid*/
		printf("%c", PIPE);
		/*newline and also dash line*/
		printf("\n");
		if(i%THREE==2){
			for(j=0; j<TWO; j++){
				for(k=0; k<NINE*2+1; k++)
					printf("%c", DASH);
				printf("%c%c", SPACE, SPACE);
			}
			printf("\n");
		}
	}
	return;
}

#if CLIINPUT && HEXINPUT
void print_hex(const char *s){
/*This function is copy-pasted from stackoverflow*/
	while(*s)
		printf("%02x", (unsigned int) *s++);
	printf("\n");
	return;
}
#endif
