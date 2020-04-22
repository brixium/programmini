#include <stdio.h>
#include "../base/base.h"

#define CLIINPUT 1
#define HEXINPUT 0
#define PRINTCANDIDATES 0
#define PRINT_FINAL_CANDIDATES 1
#define PRINT_GRIDS_HORIZONTAL 1
#if CLIINPUT
#define BUFFERSIZE 7 /*7+1 is the number of chars required on Linux.
	This is our input string as we humans read it: "1 2 5".
	Here's the same string but viewed from the computer's POW in HEX: 31 20 32 20 35 0a (6 bytes).
	Here are my clues:
		1) Computers like numbers which are to the power of 2. 8 is ok, 6 is not. Therefore strings have to be 8 bytes long
		2) The '\0' character (NUL terminator) is 2 bytes long (0xC0 0x80) instead of one (0x00). For further info, visit https://en.wikipedia.org/wiki/Null-terminated_string#Character_encodings .
*/
#endif
#if PRINT_GRIDS_HORIZONTAL
square_t copy[NINE][NINE];
#endif

#define DASH '-'
#define PIPE '|'
#define SPACE ' '

/*Prints the grid*/
void printGrid();
/*Prints the original grid on the left and the result on the right*/
void printHorizontally();
/*Prints all candidates for every cell in the grid*/
void printAllCandidates();
/*Prints the input values as hexadecimals*/
void print_hex(const char *);
/*Prints all the candidates for a given cell*/
void printCandidatesCell(int, int);
