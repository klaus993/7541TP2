#define _POSIX_C_SOURCE 200809L
#include "strutil.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

char** split(const char* str, char sep) {
	if (sep == '\0') {
		return NULL;
	}
	char **result;
	size_t count = 0;
	int i;
	const char *tmp = str;
	while (*tmp) {
		if (*tmp == sep) {
			count++;
		}
		tmp++;
	}
	count++;
	result = malloc(sizeof(char*) * count);
	tmp = str;
	size_t last = 0;
	i = 0;
	while (true) {
		if (*tmp == sep || *tmp == '\0') {
			result[i] = strndup(tmp - last, last);
			i++;
			last = 0;
		} else {
			last++;
		}
		if (*tmp == '\0') {
			break;
		}
		tmp++;
	}
	result[i] = NULL;
	return result;
}

char* join(char** strv, char sep) {
	size_t strings = 0, chars = 0;
	char *result;
	while (strv[strings] != NULL) {
		while (strv[strings][chars] != '\0') {
			chars++;	//para contar cantidad de caracteres y luego poder reservar la memoria que haga falta
		}
		strings++;	//para calcular la cantidad de cadenas que hay, y por lo tanto calcular la cantidad de separadores a insertar
	}
	if (strings == 0) {
		result = malloc(sizeof(char));
		result[0] = '\0';
		return result;
	}
	result = malloc(sizeof(char) * chars + strings); //le sumo 'strings' para hacer espacio para los separadores y el \0
	if (!result) {
		return NULL;
	}
	int k = 0;
	for (int i = 0; strv[i] != NULL; i++) {
		if (i != 0) {
			result[k] = sep;
			k++;
		}
		for (int j = 0; strv[i][j] != '\0'; j++) {
			result[k] = strv[i][j];
			k++;
		}
	}
	result[k] = '\0';
	return result;
}

void free_strv(char* strv[]) {
	for (int i = 0; strv[i] != NULL; i++) {
		free(strv[i]);
	}
	free(strv);
}

void print_strv(const char *strv[]) {
	putchar('[');
	for (int i = 0; strv[i] != NULL; i++) {
		printf("\"%s\", ", strv[i]);
	}
	putchar(']');
	putchar('\n');
}

