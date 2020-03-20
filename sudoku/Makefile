CC=gcc
CFLAGS=-Wall -O2 -std=c89 -pedantic -static
CFLAGS_NOT_STATIC=-Wall -O2 -std=c89 -pedantic

install_static: sudoku.o 
	$(CC) $(CFLAGS) sudoku.o -o sudoku
install: sudoku.o
	$(CC) $(CFLAGS_NOT_STATIC) sudoku.o -o sudoku

sudoku.o: sudoku.c
	$(CC) $(CFLAGS_NOT_STATIC) -c sudoku.c -o sudoku.o
clean:
	rm *.o
