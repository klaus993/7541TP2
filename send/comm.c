#define _POSIX_C_SOURCE 200809L
#include "hash.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/*Recibe dos archivos y un booleano imprimir_coincidencias, y según su valor,
imprime las líneas que coinciden de los dos archivos o las que no coinciden del
segundo archivo pasado por parámetro. */
void comm(FILE *file1, FILE *file2, bool imprimir_coincidencias) {
	char* lineafile1 = NULL;
	size_t capacidadfile1 = 0;
	hash_t* hash1 = hash_crear(NULL);
	while(true) {
		ssize_t longitudfile1 = getline(&lineafile1, &capacidadfile1, file1);
		hash_guardar(hash1, lineafile1, NULL);
		if(longitudfile1 == -1) break;
	}
	char* lineafile2 = NULL;
	size_t capacidadfile2 = 0;
	while(true) {
		ssize_t longitudfile2 = getline(&lineafile2, &capacidadfile2, file2);
		if(imprimir_coincidencias) {
			if(hash_pertenece(hash1, lineafile2)) {
				hash_borrar(hash1, lineafile2);
				fprintf(stdout,"%s", lineafile2);
			}
		}
		else {
			if(!hash_pertenece(hash1, lineafile2)) {
				hash_guardar(hash1, lineafile2, NULL);
				fprintf(stdout,"%s", lineafile2);
			}
		}
		if(longitudfile2 == -1) break;
	}
	free(lineafile1);
	free(lineafile2);
	hash_destruir(hash1);
}

/* Función principal. */
int main(int argc, char *argv[]) {
	if(argc < 3 || argc > 4) {
		fprintf(stderr,"La cantidad de argumentos pasados es diferente de dos.\n");
		return -1;
	}
	FILE *file1, *file2;
	if(!(file1 = fopen(argv[1], "rt"))) {
		fprintf(stderr, "No pudo abrirse el archivo %s.\n", argv[1]);
		return EXIT_FAILURE;
	}
	if(!(file2 = fopen(argv[2], "rt"))) {
		fprintf(stderr, "No pudo abrirse el archivo %s.\n", argv[2]);
		fclose(file1);
		return EXIT_FAILURE;
	}
	char *opcion1 = "-1"; 
	char *opcion2 = "-2";
	if(argc == 4) {
		if(strcmp(argv[3], opcion1) == 0) comm(file2, file1, false);
		else if(strcmp(argv[3], opcion2) == 0) comm(file1, file2, false);
		else fprintf(stderr, "El tercer argumento no es válido.\n");
		return -1;
	}
	else comm(file1, file2, true);
	if(fclose(file1) == EOF || fclose(file2) == EOF) {
		fprintf(stderr, "Error al cerrar los archivos.\n");
		return EXIT_FAILURE;
	}
	return 0;
}		