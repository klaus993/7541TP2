#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>

void comm(FILE *file1, FILE *file2, int indicador) {
	char* lineafile1 = NULL;
	size_t capacidadfile1 = 0;
	hash_t* hash1 = hash_crear(free);
	while(true) {
		ssize_t longitudfile1 = getline(&lineafile1, &capacidadfile1, file1);
		int* num = malloc(sizeof(int));
		*num = 0;
		hash_guardar(hash1, lineafile1, num);
	}
	char* lineafile2 = NULL;
	size_t capacidadfile2 = 0;
	if(indicador) {
		void* aux;
		while(true) {
			ssize_t longitudfile2 = getline(&lineafile2, &capacidadfile2, file2);
			if(hash_pertenece(hash1, lineafile2) && *(int*)hash_obtener(hash1, lineafile2) < 1) {
				aux = hash_obtener(hash1, lineafile2);
				(*(int*)aux)++;
				hash_guardar(hash1, lineafile2, aux);
				fprintf(stdout,"%s", lineafile2);
		}
	}
	
	}

/* Función principal. */
int main(int argc, char *argv[]) {
	if(argc < 3) {
		fprintf(stderr,"La cantidad de argumentos pasados es diferente de tres.\n");
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
	bool resultado = comm(file1, file2);
	if(fclose(file1) == EOF || fclose(file2) == EOF) {
		fprintf(stderr, "Error al cerrar los archivos.\n");
		return EXIT_FAILURE;
	}
	return 0;
}		