CC=gcc
LINK=gcc
CFLAGS=-Wall -W -O2 -std=c89 -pedantic -static
CFLAGS_NOT_STATIC=-Wall -W -O2 -std=c89 -pedantic

install_static: sudoku.o 
	$(LINK) $(CFLAGS) sudoku.o -o sudoku
install: sudoku.o
	$(LINK) $(CFLAGS_NOT_STATIC) sudoku.o -o sudoku

sudoku.o: sudoku.c
	$(CC) $(CFLAGS_NOT_STATIC) -c sudoku.c -o sudoku.o
clean:
	rm sudoku.o
