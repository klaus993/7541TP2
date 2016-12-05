CC = gcc
CFLAGS = -g -std=c99 -Wall -Wconversion -Wno-sign-conversion -Werror
FILEOUT = comm
VALGRIND = valgrind
TDA = abb
VFLAGS = --leak-check=full --track-origins=yes --show-reachable=yes
VALGRIND_V = $(VALGRIND) $(VFLAGS)

all:
	$(CC) $(CFLAGS) -o $(FILEOUT) ../hash/hash.c comm.c

clean:
	rm *.o
	rm -r *.dSYM
	rm *.out

test:
	$(VALGRIND_V) ./$(FILEOUT) 

run:
	./$(FILEOUT)
