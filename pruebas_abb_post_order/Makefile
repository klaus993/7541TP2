CC = gcc
CFLAGS = -g -std=c99 -Wall -Wconversion -Wno-sign-conversion -Werror
FILEOUT = pruebas
VALGRIND = valgrind
TDA = abb
VFLAGS = --leak-check=full --track-origins=yes --show-reachable=yes
VALGRIND_V = $(VALGRIND) $(VFLAGS)

all:
	$(CC) $(CFLAGS) -o $(FILEOUT) ../abb/abb.c ../abb/pila.c main.c pruebas_abb.c testing.c lista.c

clean:
	rm *.o
	rm -r *.dSYM
	rm *.out

test:
	$(VALGRIND_V) ./$(FILEOUT) 

run:
	./$(FILEOUT)
