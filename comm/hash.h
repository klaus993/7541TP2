#ifndef HASH_H
#define HASH_H

#include <stdbool.h>
#include <stddef.h>

struct hash;
struct hash_iter;

typedef struct hash hash_t;
typedef struct hash_iter hash_iter_t;

// tipo de función para destruir dato
typedef void (*hash_destruir_dato_t)(void *);

/* Crea el hash.
 * Post: Si pudo crearlo, devuelve un puntero al hash, sino, devuelve un puntero a NULL.
 */
hash_t *hash_crear(hash_destruir_dato_t destruir_dato);

/* 
 * Pre: El hash fue creado.
 * Post: Se almacenó el par (clave, dato). Si la clave ya se encuentra en la
 * estructura, reemplaza el valor con el nuevo. De no poder guardarlo devuelve false, de lo contrario, devuelve true.
 */
bool hash_guardar(hash_t *hash, const char *clave, void *dato);

/* Pre: El hash fue creado.
 * Post: El elemento fue borrado de la estructura, se lo devolvió el valor,
 * en el caso de que estuviera guardado. Si el dato no estaba, devuelve NULL.
 */
void *hash_borrar(hash_t *hash, const char *clave);

/* Pre: El hash fue creado.
 * Post: Devuelve el valor de un elemento del hash, si la clave no se encuentra
 * devuelve NULL.
 */
void *hash_obtener(const hash_t *hash, const char *clave);

/* Pre: La estructura hash fue inicializada.
 * Post: Si el elemento está en el hash, devuelve true, de lo contrario, false.
 */
bool hash_pertenece(const hash_t *hash, const char *clave);

/* Pre: La estructura hash fue inicializada
 * Post: devuelve la cantidad de elementos del hash.
 */
size_t hash_cantidad(const hash_t *hash);

/* Destruye la estructura liberando la memoria pedida y llamando a la función
 * destruir para cada dato en caso de existir dicha función.
 * Pre: El hash fue creado.
 * Post: La estructura hash fue destruida.
 */
void hash_destruir(hash_t *hash);

/* Iterador del hash */

// Crea iterador
hash_iter_t *hash_iter_crear(const hash_t *hash);

// Avanza iterador
bool hash_iter_avanzar(hash_iter_t *iter);

// Devuelve clave actual, esa clave no se puede modificar ni liberar.
const char *hash_iter_ver_actual(const hash_iter_t *iter);

// Comprueba si terminó la iteración
bool hash_iter_al_final(const hash_iter_t *iter);

// Destruye iterador
void hash_iter_destruir(hash_iter_t* iter);

#endif // HASH_H
