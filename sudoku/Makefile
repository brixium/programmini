CC=gcc
LINK=gcc
CFLAGS=-Wall -W -O2 -std=c89 -pedantic -static
CFLAGS_NOT_STATIC=-Wall -W -O2 -std=c89 -pedantic
DIR_IO=io/
DIR_BASE=base/

install_static: $(DIR_IO)io.o sudoku.o
	$(LINK) $(CFLAGS) sudoku.o $(DIR_IO)io.o -o sudoku
install: $(DIR_IO)io.o sudoku.o
	$(LINK) $(CFLAGS_NOT_STATIC) sudoku.o $(DIR_IO)io.o -o sudoku

sudoku.o: sudoku.c $(DIR_IO)io.h $(DIR_BASE)base.h
	$(CC) $(CFLAGS_NOT_STATIC) -c sudoku.c -o sudoku.o
io.o: $(DIR_IO)io.c $(DIR_IO)io.h $(DIR_BASE)base.h
	$(CC) $(CFLAGS_NOT_STATIC) -c $(DIR_IO)io.c -o io.o
clean:
	rm sudoku.o $(DIR_IO)io.o

