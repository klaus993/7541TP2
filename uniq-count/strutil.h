#ifndef STRUTIL_H
#define STRUTIL_H

#include <stddef.h>

/*
 * Devuelve en un arreglo dinÃ¡mico terminado en NULL con todos los subsegmentos
 * de â€˜strâ€™ separados por el carÃ¡cter â€˜sepâ€™. Tanto el arreglo devuelto como las
 * cadenas que contiene son allocadas dinÃ¡micamente.
 *
 * Quien llama a la funciÃ³n toma responsabilidad de la memoria dinÃ¡mica del
 * arreglo devuelto. La funciÃ³n devuelve NULL si fallÃ³ alguna llamada a
 * malloc(), o si â€˜sepâ€™ es '\0'.
 */
char** split(const char* str, char sep);

/*
 * Devuelve una cadena, allocada dinÃ¡micamente, resultado de unir todas las
 * cadenas del arreglo terminado en NULL â€˜strvâ€™.
 *
 * Quien llama a la funciÃ³n toma responsabilidad de la memoria dinÃ¡mica de la
 * cadena devuelta. La funciÃ³n devuelve NULL si no se pudo allocar memoria.
 */
char* join(char** strv, char sep);

/*
 * Libera un arreglo dinÃ¡mico de cadenas, y todas las cadenas que contiene.
 */
void free_strv(char* strv[]);

#endif  // STRUTIL_H
