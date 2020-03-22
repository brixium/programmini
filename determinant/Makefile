CC=gcc
CFLAGS=-Wall -O2 -std=c89 -pedantic -static
CFLAGS_NOT_STATIC=-Wall -O2 -std=c89 -pedantic
DEBUG_FLAGS=-g

install_static: determinant.o 
	$(CC) $(CFLAGS) determinant.o -o determinant
install: determinant.o
	$(CC) $(CFLAGS_NOT_STATIC) determinant.o -o determinant

determinant.o: determinant.c
	$(CC) $(CFLAGS_NOT_STATIC) -c determinant.c -o determinant.o
clean:
	rm *.o
