CC = gcc
CFLAGS = -g -std=c99 -Wall -Wconversion -Wno-sign-conversion -Werror
LFLAGS = -lm
COMM_OUT = prueba
UNIQ_OUT = uniq-count
HEAP_UTILS = heap-utils.o
ABB = abb.o
VALGRIND = valgrind
V_FLAGS = --leak-check=full --track-origins=yes --show-reachable=yes
VALGRIND_V = $(VALGRIND) $(V_FLAGS)

prueba: abb.o prueba.o testing.o main.o lista.o pila.o
	$(CC) $(CFLAGS) -o prueba abb.o prueba.o testing.o main.o lista.o pila.o $(LFLAGS)

prueba.o: pruebas_abb.c testing.h abb.h lista.h
	$(CC) $(CFLAGS) -c -o prueba.o pruebas_abb.c $(LFLAGS)

pila.o: pila.c pila.h
	$(CC) $(CFLAGS) -c -o pila.o pila.c $(LFLAGS)
abb.o: abb.c abb.h pila.h
	$(CC) $(CFLAGS) -c -o abb.o abb.c $(LFLAGS)

testing.o: testing.c testing.h
	$(CC) $(CFLAGS) -c -o testing.o testing.c $(LFLAGS)

main.o: main.c testing.h
	$(CC) $(CFLAGS) -c -o main.o main.c $(LFLAGS)

lista.o: lista.c lista.h
	$(CC) $(CFLAGS) -c -o lista.o lista.c $(LFLAGS)
