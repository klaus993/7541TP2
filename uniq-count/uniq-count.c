#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "lista.h"
#include "strutil.h"
#include "../hash/hash.h"

#define USAGE "Uso: %s [ARCHIVO]\n"
#define FILE_ERROR "%s error: el archivo %s no existe.\n"

void uniq_count(const char *dir) {
	FILE *file = fopen(dir, "r");
	hash_t *hash = hash_crear(free);
	lista_t *lista = lista_crear();
	char *input = NULL;
	size_t size = 0;
	size_t read;
	int *temp;
	while ((read = getline(&input, &size, file)) != -1) {
		if (input[read - 1] == '\n') {
			input[read - 1] = '\0';
		}
		char **splited = split(input, ' ');
		unsigned i = 0;
		while (splited[i] != NULL) {
			if (!hash_pertenece(hash, splited[i])) {
				int *cont = malloc(sizeof(int)); *cont = 1;
				hash_guardar(hash, splited[i], cont);
				lista_insertar_ultimo(lista, splited[i]);
			} else {
				temp = (int*)hash_obtener(hash, splited[i]);
				free(splited[i]);
				(*temp)++;
			}
			i++;

		}
	}
	free(input);
	while (!lista_esta_vacia(lista)) {
		char *palabra = (char*)lista_borrar_primero(lista);
		printf("%d %s\n", *(int*)hash_obtener(hash, palabra), palabra);
	}

	hash_destruir(hash);
	lista_destruir(lista, NULL);
}

int main(int argc, char *argv[]) {
	if (argc != 2) {
		printf(USAGE, argv[0]);
		return 1;
	}
	if (access(argv[1], R_OK) != 0) {
		printf(FILE_ERROR, argv[0], argv[1]);
		return -1;
	}
	uniq_count(argv[1]);
	return 0;
}