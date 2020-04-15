/*	
 * Author: brixium 
 * License: GPLv2
 * Release: 0.1.1
 *
 * Before reading the comments below, here's a little background about this project. This is a sudoku solver made for fun, so no big deal.
 * Currently it is able to solve grids ranging from easy to hard; expert grids are currently out of range.
 * Algorithms already implemented: naked pairs.
 * Future algorithms that needs to be implemented (TODO): 
 * X-wing, XY-wing, naked pairs, BUG+1, skyscraper.
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
/* README:

CLIINPUT: if defined and != 0, the input for the program will be taken from a file in the command line as such:
	$ ./sudoku < inputfile.txt
	this file must be formatted as such:
	-the last line must be blank or must contain a leading carriage return (\n);
	-each line (except the last one) starts with a number and ends with a number and must be exactly 5 characters long;
	-there are three numbers per line separated with a white space
DEBUG: if defined and != 0, prints debug info
HEXINPUT: if defined and != 0 it prints the values of the input file as hexadecimal. ITS VALUE MUST NOT BE 1 WHEN CLIINPUT IS 0 !
PRINTCLUES: prints ALL the clues when the program says so ( printAllClues() in the code ) and when its value is != 0.
STOPWATCH: if defined, the execution time of the whole program will be measured and the results printed at the end of main
*/
#define CLIINPUT 1
#define DEBUG 1
#define HEXINPUT 0
#define PRINTCLUES 1
#define STOPWATCH 0

#define NINE 9
#define THREE 3
#define TWO 2
#define DASH '-'
#define PIPE '|'
#define SPACE ' '

#if CLIINPUT
#define BUFFERSIZE 7 /*7+1 is the number of chars required on Linux.
	This is our input string as we humans read it: "1 2 5".
	Here's the same string but viewed from the computer's POW in HEX: 31 20 32 20 35 0a (6 bytes).
	Here's my clues:
		1) Computers like numbers which are to the power of 2. 8 is ok, 6 is not. Therefore strings have to be 8 bytes long
		2) The '\0' character (NUL terminator) is 2 bytes long (0xC0 0x80) instead of one (0x00). For further info, visit https://en.wikipedia.org/wiki/Null-terminated_string#Character_encodings .
*/
#endif

typedef struct square_s{
	int num;
	int clues[NINE]; /*CLUES: |1|0|1|0|0|0|0|1|0| means that in that square there might be a 1,3 or an 8*/
}square_t;

square_t grid[NINE][NINE];

int canBePlaced(int, int, int); /*returns 0 if a number cannot be placed in that square, 1 otherwise*/
int checkSubGrid(int, int, int); /*checks if a number can be placed in a square of x,y coords. Returns 1 if it can, 0 otherwise*/
int checkRow(int, int); /*checks if a number can be placed in the x row. If it can, it returns 1, 0 otherwise*/
int checkColumn(int, int); /*returns 1 if a number can be placed in the column y, 0 otherwise*/
int placeNumber(int, int, int); /*returns 0 if the cell is already occupied, 1 otherwise*/
void initGrid(); /*initialises the grid as blank*/
void printGrid(); /*prints the grid*/
void initAllClues(); /*Initialises the clues grid*/
void refreshAllClues(); /*Refreshes the clues grid by deleting numbers*/
void editClue(int, int, int, int); /*Adds or remove a clue for a given number, passed as 3rd parameter (placed in x=1st param and y=2nd par) depending on the fourth parameter (1 adds it, 0 removes it)*/
void deleteCluesNakedPair(int, int, int, int, int); /*Input: x1, y1, x2, y2, mode. Deletes every clue in a naked pair logic, as defined by mode, matching those in x1,y1 & x2,y2 while simultaneously leaving them out of this deletion process*/
/* void printCluesCell(int, int); *//*Prints all the clues for a given cell*/
void printAllClues(); /*Self-explainatory*/
int numberFromOnlyClue(int, int); /*Given the x and y, if it succeedes in converting a square with only one clue into a number on the same square, this function will return the number converted, 0 otherwise*/
int numberFromClue(int, int, int); /*given thx x,y coordinates and a number, it transforms the cell in a number. Returns 0 if the cell is already occupied, 1 otherwise*/
int numberFromClueInRow(int, int); /*If this sees an only clue in a row it makes it a number and deletes all the clues for that square. Parameters: x,y coords*/
int numberFromClueInColumn(int, int); /*If this sees an only clue in a column it makes it a number and deletes all the clues for that square. Parameters: x,y coord*/
int numberFromClueInSubGrid(int *, int *, int); /*If this sees an only clue in a subGrid it makes it a number and deletes all the clues for that square. Parameters: */
int solveGrid(); /*Returns 1 if the grid is solvable, 0 otherwise*/
int numCluesOfSquare(int , int); /*Get number of possible clues of a specified square (x,y)*/
int howManyNumbersOnGrid(); /*Returns how many numbers are placed on the grid*/
int haveTheSameCluesByPos(int, int, int, int); /*input: x1, y1, x2, y2. returns 0 if they dont have the same clues, 1 otherwise*/
int firstContainsAtLeastSameCluesAsSecond(square_t, square_t); /*Checks if the first square has the at least all the clues as the second*/
int firstContainsAtLeastOneClueAsSecond(square_t, square_t); /*If the first square has at least one clue as the second, it returns 1, 0 otherwise*/
int findAndManageNakedPairs(int, int, int); /*Input: x, y coords and MODE(1=row, 2=col, 3=subgrid). Returns 1 if found, 0 otherwise. It deletes on its own the clues not needed anymore*/
int findAndDeleteImpossibleClues(int, int); /*TODO: find a better name for this one. Input:x,y. Return value: 0 if no operations done, >=1 otherwise, 1 for each ghost number found*/
#if CLIINPUT && HEXINPUT
void print_hex(const char *); /*Prints the input values as hexadecimals*/
#endif
int main(int argc, char * argv[]){
	#if CLIINPUT
	int x, y, num, blen;
	char buffer[BUFFERSIZE+1];
	#endif
	#if STOPWATCH
	double time_elapsed;
	clock_t begin, end;
	begin = clock();
	#endif
	#if CLIINPUT
	initGrid();
	while(buffer[0] != '\n'){
	    fgets(buffer, BUFFERSIZE, stdin);
		#if HEXINPUT
		print_hex(buffer);
		#endif
		blen = strlen(buffer);
		if(blen > 4){
			x = buffer[0] - '1'; /*cast from char to integer; then subtracts 1 beacuse arrays starts at 0*/
			y = buffer[2] - '1'; /*cast from char to integer; then subtracts 1 beacuse arrays starts at 0*/
			num = buffer[4] - '0'; /*cast from char to integer*/
			if(! placeNumber(x, y, num) )
				printf("The programmer did something wrong here\n");
		}
	}
	#endif
	printf("Before:\n");
	printGrid();
	if(	solveGrid() )
		printf("After:\n");
	else
		printf("The grid can't be solved. Either you entered some wrong values or the sudoku was too complex\n");
	#if PRINTCLUES
	printf("Final candidates:\n");
	printAllClues();
	#endif
	printGrid();
	#if STOPWATCH
	end = clock();
	time_elapsed = (double)(end-begin)/CLOCKS_PER_SEC;
	printf("Time elapsed: %f seconds\n", time_elapsed);
	#endif
	return 0;
}

void initGrid(){
	int i, j, k;
	for(i=0; i<NINE; i++)
		for(j=0; j<NINE; j++){
			grid[i][j].num = 0;
			for(k=0; k<NINE; k++)
				grid[i][j].clues[k] = 0;
		}
	return;
}
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

int placeNumber(int x, int y, int number){
	if(grid[x][y].num != 0)
		return 0;
	grid[x][y].num = number;
	return 1;
}

int checkSubGrid(int x, int y, int number){ /*If a square with the same number is present, returns 0; else 1*/
	int i, j, startx, starty, stopx, stopy;
	
	startx = x - (x % THREE);
	starty = y - (y % THREE);
	stopx = startx + THREE;
	stopy = starty + THREE;
	for(i=startx; i<stopx; i++)
		for(j=starty; j<stopy; j++)
			if(grid[i][j].num == number)
				return 0;
	return 1;
}

int checkRow(int x, int number){
    int j;
    for(j=0; j<NINE; j++)
        if(grid[x][j].num == number)
            return 0;
    return 1;
}
int checkColumn(int y, int number){
    int i;
    for(i=0; i<NINE; i++)
        if(grid[i][y].num == number)
            return 0;
    return 1;
}

int canBePlaced(int x, int y, int number){
	if(checkSubGrid(x, y, number) && checkRow(x, number) && checkColumn(y, number))
		return 1;
	return 0;
}

void initAllClues(){
	int i, j, k;

	for(i=0; i<NINE; i++)
		for(j=0; j<NINE; j++)
			if(grid[i][j].num == 0)
				for(k=1; k <=NINE; k++){
					if( canBePlaced(i, j, k) )
						editClue(i, j, k, 1);
					else
						editClue(i, j, k, 0);
				}
	return;
}

void refreshAllClues() {
	int i, j, k;

	for (i = 0; i < NINE; i++)
		for (j = 0; j < NINE; j++)
			if (grid[i][j].num == 0)
				for (k = 1; k <= NINE; k++)
					if (!canBePlaced(i, j, k))
						editClue(i, j, k, 0);
}

void editClue(int x, int y, int clue, int mode){
	if(mode)
		grid[x][y].clues[clue-1] = 1;
	else
		grid[x][y].clues[clue-1] = 0;
	return ;
}
/*
void printCluesCell(int x, int y){
	int k;
	for(k=0; k<NINE; k++)
		if(grid[x][y].clues[k] != 0)
			printf("%d%c", k+1, SPACE);
	printf("\n");
	return;
}
*/

void printAllClues(){
	int i, j, k;
	for(i=0; i<NINE; i++)
		for(j=0; j<NINE; j++){
			printf("x:%d, y:%d; clues: ", i+1, j+1);
			/*printCluesCell(i, j);*/
			for(k=0; k<NINE; k++)
				if(grid[i][j].clues[k] != 0)
					printf("%d%c", k+1, SPACE);
			printf("\n");

		}
	return;
}

int numberFromClueInRow(int row, int number){
	int j, counter, index;
	
	counter = 0;
	for(j=0; j<NINE; j++)
		if(grid[row][j].clues[number-1] == 1){
			counter++;
			index = j;
		}
	if(counter == 1){ /*Bingo*/
		if(numberFromClue(row, index, number))
			return index+1;
	}
	return 0;
}

int numberFromClueInColumn(int col, int number){
	int i, counter, index;

	counter = 0;
	for(i=0; i<NINE; i++)
		if(grid[i][col].clues[number-1] == 1){
			counter++;
			index = i;
		}
	if(counter == 1){ /*Bingo*/
		if(numberFromClue(index, col, number))
			return index+1;
	}
	return 0;
}

int numberFromClueInSubGrid(int * x, int * y, int number){
	int startx, starty, stopx, stopy, i, j, counter, ix, iy;
	
	startx = *x - (*x % THREE);
	starty = *y - (*y % THREE);
	stopx = startx + THREE;
	stopy = starty + THREE;
	counter = 0;
	for(i=startx; i<stopx; i++)
		for(j=starty; j<stopy; j++)
			if(grid[i][j].clues[number-1] == 1){
				counter++;
				ix = i;
				iy = j;
			}
	if(counter == 1){ /*Bingo*/
		if(numberFromClue(ix, iy, number)){
			*x = ix;
			*y = iy;
			return 1;
		}
	}
	return 0;
}

int numberFromOnlyClue(int x, int y){
	int k, num, flag;

	flag = 1;
	num = 0;
	if(grid[x][y].num != 0)
		return 0;
	for(k=0; flag && k<NINE; k++)
		if(grid[x][y].clues[k] == 1){
			num = k+1;
			flag = 1;
			grid[x][y].clues[k] = 0;
		}
	grid[x][y].num = num;
	return num;
}

int numberFromClue(int x, int y, int number){
	int i;
	if(grid[x][y].num == 0){
		grid[x][y].num = number;
		for(i=0; i<NINE; i++)
			grid[x][y].clues[i] = 0;
		return 1;
	}
	return 0;
}

int howManyNumbersOnGrid(){
	int i, j, counter;

	counter = 0;
	for(i=0; i<NINE; i++)
		for(j=0; j<NINE; j++)
			if(grid[i][j].num != 0)
				counter++;
	return counter;
}

int numCluesOfSquare(int x, int y){
	int k, n;
	
	n=0;
	for(k=0; k<NINE; k++)
		if(grid[x][y].clues[k] == 1)
			n++;
	return n;
}

int solveGrid(){
	int iterations, maxIterations, i, j, k, found, xaux, yaux;
/*We're supposing that the grid is already initialised*/
	iterations=0;
	maxIterations = 81;
	initAllClues();
	#if PRINTCLUES
	printf("Initial clues:\n");
	printAllClues();
	printf("---------\n");
	#endif
	while( (iterations < maxIterations) && (howManyNumbersOnGrid() < (NINE * NINE)) ){
		for(i=0; i< NINE; i++){
			for(j=0; j<NINE; j++){
				if(grid[i][j].num == 0){
					if( numCluesOfSquare(i, j) == 1 ){ /* == found*/
						k = numberFromOnlyClue(i, j);
						refreshAllClues();
						#if DEBUG
						printf("(%d,%d) Number %d found in (%d,%d) [only clue]\n", i+1, j+1, k, i+1, j+1);
						#endif
						#if PRINTCLUES
						printAllClues();
						#endif
					}else{
						for(k=1; k<=NINE; k++){
							if( (yaux = numberFromClueInRow(i, k)) ){
								#if DEBUG
								printf("(%d,%d) Number %d found in (%d,%d) [clue in row]\n", i+1, j+1, k, i+1, yaux+1);
								#endif
								found = 1;
							}else if( (xaux = numberFromClueInColumn(j, k)) ){
								#if DEBUG
								printf("(%d,%d) Number %d found in (%d,%d) [clue in column]\n", i+1, j+1, k, xaux+1, j+1);
								#endif
								found = 2;
							}else {
								xaux = i;
								yaux = j;
								if( numberFromClueInSubGrid(&xaux, &yaux, k) ){
									#if DEBUG
									printf("(%d,%d) Number %d found in (%d,%d) [clue in subgrid]\n", i+1, j+1, k, xaux+1, yaux+1);
									#endif
									found = 3;
								}
							}
							if(!found){
								if( findAndManageNakedPairs(i, j, 1) ){
									found = 4;
									#if DEBUG
									/*printf("(%d,%d) [naked pairs found by row]\n", i+1, j+1 );*/
									#endif
								}else if(findAndManageNakedPairs(i, j, 2)){
									found = 5;
									#if DEBUG
									/*printf("(%d,%d) [naked pairs found by column]\n", i+1, j+1 );*/
									#endif
								}else if(findAndManageNakedPairs(i, j, 3)){
									found = 6;
									#if DEBUG
									/*printf("(%d,%d) [naked pairs found by subgrid]\n", i+1, j+1 );*/
									#endif
								}else if( i == j && i % 3 == 0){
									if(findAndDeleteImpossibleClues(i, j)){
										#if DEBUG
										printf("Platessa\n");
										#endif
									}
								}
							}
							if(found){
								refreshAllClues();
								#if PRINTCLUES
								printAllClues();
								#endif
								found = 0;
							}
						}
					}
				}
			}
		}
		iterations++;
		#if DEBUG || PRINTCLUES
		printf("Iteration n.%d is over\n", iterations);
		#endif
	}
	if( howManyNumbersOnGrid() < (NINE * NINE) ) /*If there are less number than what the grid can accomodate, the sudoku is not solved*/
		return 0;
	/*
	#if DEBUG
	printf("Iterations:%d\n", iterations);
	#endif
	*/
	return 1;
}

int findAndManageNakedPairs(int x, int y, int mode){
	int i, j, k, startx, stopx, starty, stopy, ocount, ccount, flag, found;
	
	if(mode == 1){ /*mode==1->find n.p. in the row*/
		startx = x;
		stopx = x+1;
		starty = 0;
		stopy = NINE;
	}else if(mode == 2){ /*mode==2->find n.p. in the column*/
		startx = 0;
		stopx = NINE;
		starty = y;
		stopy = y+1;
	}else if(mode == 3){ /*mode==3->find n.p. in the subgrid*/
		startx = x - (x % THREE);
		stopx = startx + THREE;
		starty = y - (y % THREE);
		stopy = starty + THREE;
	}else{
		#if DEBUG
		printf("[ERROR] Wrong call to function findAndManageNakedPairs: invalid mode code\n");
		#endif
		return 0;
	}
	for(ocount=0, k=0; k < NINE; k++)
		if(grid[x][y].clues[k] != 0)
			ocount++;
	if(ocount != TWO) /*Here I say that only pairs are eliglible*/
		return 0;
	found = 0;
	for(i=startx; i<stopx; i++){
		for(j=starty; j<stopy; j++){
			for(ccount = 0, k=0; k < NINE; k++)
				if(grid[i][j].clues[k] != 0)
					ccount++;
			if(grid[x][y].num == 0 && grid[i][j].num == 0 && ccount == ocount ){
				flag = 1;
				if(mode == 1 && y==j)
					flag = 0;
				if(mode == 2 && x==i)
					flag = 0;
				if(mode == 3 && ( x==i && y==j ) )
					flag = 0;
				for(k=0; k<NINE && flag; k++)
					if(grid[i][j].clues[k] != grid[x][y].clues[k])
						flag = 0;
				if(flag){
					deleteCluesNakedPair(x, y, i, j, mode);
					found = 1;
				}
			}
		}
	}
	return found;
}

void deleteCluesNakedPair(int ogx, int ogy, int x, int y, int mode){
	int i, j, k, l, startx, stopx, starty, stopy, clues[TWO], cluescount;

	if(mode == 1){ /*mode==1->find n.p. in the row*/
		startx = x;
		stopx = x+1;
		starty = 0;
		stopy = NINE;
	}else if(mode == 2){ /*mode==2->find n.p. in the column*/
		startx = 0;
		stopx = NINE;
		starty = y;
		stopy = y+1;
	}else if(mode == 3){ /*mode==3->find n.p. in the subgrid*/
		startx = x - (x % THREE);
		stopx = startx + THREE;
		starty = y - (y % THREE);
		stopy = starty + THREE;
	}else{
		printf("[ERROR] Wrong call to function deleteCluesNakedPair: invalid mode code\n");
		return ;
	}
	/*Crucial point*/
	for(k = 0, cluescount = 0; k < NINE; k++)
		if(grid[ogx][ogy].clues[k] == 1){
			clues[cluescount] = k;
			cluescount++;
		}

	for(i=startx; i<stopx; i++){
		for(j=starty; j<stopy; j++){
			if(mode == 1){ /*row case*/
				if( j!=ogy && j!=y && firstContainsAtLeastOneClueAsSecond( grid[i][j], grid[ogx][ogy] ) )
					for(k=0; k<cluescount; k++)
						for(l=0; l<NINE; l++)
							if(l == clues[k]){
								grid[i][j].clues[l] = 0;
								#if DEBUG && PRINTCLUES
								printf("Clue %d in (%d,%d) deleted\n", l+1, i+1, j+1);
								#endif
							}
			}else if(mode == 2){ /*column case*/
				if( i!=ogx && i!=x && firstContainsAtLeastOneClueAsSecond( grid[i][j], grid[ogx][ogy] ) ) /*E qui casca l'asino*/
					for(k=0; k<cluescount; k++)
						for(l=0; l<NINE; l++)
							if(l == clues[k]){
								grid[i][j].clues[l] = 0;
								#if DEBUG && PRINTCLUES
								printf("Clue %d in (%d,%d) deleted\n", l+1, i+1, j+1);
								#endif
							}
			}else{ /*subgrid case*/
				if(((j!=ogy && j!=y) || (i!=ogx && i!=x))&& firstContainsAtLeastOneClueAsSecond( grid[i][j], grid[ogx][ogy] ) )
					for(k=0; k<cluescount; k++)
						for(l=0; l<NINE; l++)
							if(l == clues[k]){
								grid[i][j].clues[l] = 0;
								#if DEBUG && PRINTCLUES
								printf("Clue %d in (%d,%d) deleted\n", l+1, i+1, j+1);
								#endif
							}
			}
		}
	}
	return;
}

int haveTheSameCluesByPos(int x1, int y1, int x2, int y2){ /*Useless as today 2020-04-02*/
	int k;
	for(k=0; k<NINE; k++)
		if(grid[x1][y1].clues[k] != grid[x2][y2].clues[k])
			return 0;
	return 1;
}

int firstContainsAtLeastSameCluesAsSecond(square_t first, square_t second){ /*useless as today 2020-04-03*/
	int k, count, total;

	for(k=0, total=0; k<NINE; k++)
		if(second.clues[k] == 1)
			total++;
	for(k=0, count = 0; k<NINE; k++){
		if(second.clues[k] == 1 && first.clues[k] == 1)
			count++;
		if(count == total)
			return 1;
	}
	return 0;
}

int firstContainsAtLeastOneClueAsSecond(square_t first, square_t second){ /*checks if the first has at least all the same elements of the second*/
	int k;

	for(k=0; k<NINE; k++)
		if(second.clues[k] == 1 && first.clues[k] == 1)
			return 1;
	return 0;
}

int findAndDeleteImpossibleClues(int x, int y){
	/* 
	* This function goes into a subgrid and if it founds a pattern it operates on other row or columns.
	* Pattern: in a THREE by THREE subgrid, it looks for a candidate which is distributed only on a row or only on a column.
	* If the pattern is found, it goes on the row/column and deletes every other same candidate.
	*/
	int i, j, k, l, startx, starty, stopx, stopy, potential_candidates[NINE], row_counter, col_counter, ret_value;
	/*Defines the subgrid's boundaries*/
	startx = x - (x % THREE);
	stopx  = startx + THREE;
	starty = y - (y % THREE);
	stopy  = starty + THREE;
	/*Calculates how many clues there are for each number*/
	for(k=0; k<NINE; k++){
		potential_candidates[k] = 0;
		for(i=startx; i<NINE; i++)
			for(j=starty; j<NINE; j++)
				if(grid[i][j].clues[k] == 1)
					potential_candidates[k]++;
	}
	ret_value = 0;
	for(k=0; k<NINE; k++){
		if(potential_candidates[k] == 3 || potential_candidates[k] == 2){
			/*check if they are on the same row or column*/
			for(i=startx; i<stopx; i++){
				for(j=starty, row_counter=0, col_counter=0; j<stopy; j++){
					if(grid[i][j].clues[k] == 1){
						row_counter++;
					}
					if(grid[j][i].clues[k] == 1){
						col_counter++;
					}

					if(row_counter == potential_candidates[k]){
						/*Delete every clue in the same row except those ranging from starty to starty*/
						for(l = 0; l < NINE; l++){
							if( (l < starty || l > stopy) && grid[i][l].clues[k] == 1){
								grid[i][l].clues[k] = 0;
								ret_value++;
							}
						}
					}
					if(col_counter == potential_candidates[k]){
						/*Delete every clue in the same column except those ranging from startx to stopx*/
						for(l=0; l < NINE; l++){
							if( (l < startx || l > stopx) && grid[l][i].clues[k] == 1 ){
								grid[l][i].clues[k] = 0;
								ret_value++;
							}
						}
					}
				}
			}
		}
	}
	return ret_value;
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

