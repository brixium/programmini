/*
CLIINPUT: if defined and != 0, the input for the program will be taken from a file in the command line as such:
	$ ./sudoku < inputfile.txt
	this file must be formatted as such:
	-the last line must be blank or must contain a leading carriage return (\n);
	-each line (except the last one) starts with a number and ends with a number and must be exactly 5 characters long;
	-there are three numbers per line separated with a white space
DEBUG: if defined and != 0, prints debug info
HEXINPUT: if defined and != 0 it prints the values of the input file as hexadecimal. ITS VALUE MUST NOT BE 1 WHEN CLIINPUT IS 0 !
PRINTCANDIDATES: prints ALL the candidates when the program says so ( printAllCandidates() in the code ) and when its value is != 0.
STOPWATCH: if defined, the execution time of the whole program will be measured and the results printed at the end of main
*/
#define DEBUG 1
#define STOPWATCH 1

#define NINE 9
#define THREE 3
#define TWO 2

typedef struct square_s{
	int num;
	int candidates[NINE]; /*CANDIDATES: |1|0|1|0|0|0|0|1|0| means that in that square there might be a 1,3 or an 8*/
}square_t;

square_t grid[NINE][NINE];
