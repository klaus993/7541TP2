#ifndef LISTA_H
#define LISTA_H

#include <stdbool.h>
#include <stdlib.h>

/* ******************************************************************
 *                DEFINICION DE LOS TIPOS DE DATOS
 * *****************************************************************/

/* La lista está planteada como una lista de punteros genéricos. */

struct lista;
typedef struct lista lista_t;

/* El iterador planteado como una estructura que recorre una lista enlazada */
struct lista_iter;
typedef struct lista_iter lista_iter_t;

/* ******************************************************************
 *                    PRIMITIVAS DE LA LISTA
 * *****************************************************************/

// Crea una lista.
// Post: devuelve una nueva lista vacía.
lista_t* lista_crear(void);

// Destruye la lista. Si se recibe la función destruir_dato por parámetro,
// para cada uno de los elementos de la lista llama a destruir_dato.
// Pre: la lista fue creada. destruir_dato es una función capaz de destruir
// los datos de la lista, o NULL en caso de que no se la utilice.
// Post: se eliminaron todos los elementos de la lista.
void lista_destruir(lista_t *lista, void destruir_dato(void *));

// Devuelve verdadero o falso, según si la lista tiene o no elementos.
// Pre: la lista fue creada.
bool lista_esta_vacia(const lista_t *lista);

// Agrega un nuevo elemento al principio de la lista. Devuelve falso en caso de 
// error.
// Pre: la lista fue creada.
// Post: se agregó un nuevo elemento a la lista, dato se encuentra al comienzo
// de la lista.
bool lista_insertar_primero(lista_t *lista, void *dato);

// Agrega un nuevo elemento al final de la lista. Devuelve falso en caso de 
// error.
// Pre: la lista fue creada.
// Post: se agregó un nuevo elemento a la lista, dato se encuentra al final
// de la lista.
bool lista_insertar_ultimo(lista_t *lista, void *dato);

// Obtiene el valor del primer elemento de la lista. Si la lista tiene
// elementos, se devuelve el valor del primero, si está vacía devuelve NULL.
// Pre: la lista fue creada.
// Post: se devolvió el primer elemento de la lista, cuando no está vacía.
void* lista_ver_primero(const lista_t *lista);

// Obtiene el valor del ultimo elemento de la lista. Si la lista tiene
// elementos, se devuelve el valor del ultimo, si está vacía devuelve NULL.
// Pre: la lista fue creada.
// Post: se devolvió el ultimo elemento de la lista, cuando no está vacía.
void* lista_ver_ultimo(const lista_t *lista);

// Saca el primer elemento de la lista. Si la lista tiene elementos, se quita el
// primero de la lista, y se devuelve su valor, si está vacía, devuelve NULL.
// Pre: la lista fue creada.
// Post: se devolvió el valor del primer elemento anterior, la lista
// contiene un elemento menos, si la lista no estaba vacía.
void *lista_borrar_primero(lista_t *lista);

// Devuelve la cantidad de elementos que posee la lista.
// Pre: la lista fue creada.
size_t lista_largo(const lista_t *lista);


/* ******************************************************************
 *                PRIMITIVAS DEL ITERADOR EXTERNO
 * *****************************************************************/

// Crea un iterador.
//Pre: lista fue creada.
// Post: devuelve un nuevo iterador que apunta al primer elemento de la
// estructura a iterar. En caso de no tener elementos, el iterador se crea y
// apunta al final.
lista_iter_t *lista_iter_crear(lista_t *lista);

// Avanza el iterador en una posición de la lista. Devuelve true en caso de 
// haber podido avanzar(el iterador no esta al final de la lista), false en caso
// contrario.
// Pre: el iterador fue creado.
// Post: se avanzó en una posicion el iterador. El iterador apunta al siguiente 
// elemento.
bool lista_iter_avanzar(lista_iter_t *iter);

// Obtiene el elemento del nodo al que apunta el iterador en la lista. 
// Si el iterador se encuentra al final de esta devuelve NULL.
// Pre: el iterador fue creado.
// Post: se devolvió el elemento ubicado en la posición a la que apunta el
// iterador, cuando este no esta ubicado al final.
void *lista_iter_ver_actual(const lista_iter_t *iter);

// Devuelve verdadero o falso, según si el iterador está ubicado al final de la 
// lista o no.
// Pre: el iterador fue creado.
bool lista_iter_al_final(const lista_iter_t *iter);

// Destruye el iterador.
// Pre: el iterador fue creado.
// Post: se eliminó el iterador.
void lista_iter_destruir(lista_iter_t *iter);

// Agrega un nuevo elemento en la posición a la que apunta el iterador en la
// lista. Devuelve falso en caso de error.
// Pre: el iterador fue creado.
// Post: se agregó un nuevo elemento a la lista, dato se encuentra en la
// posicion de la lista apuntada por el iterador.
bool lista_iter_insertar(lista_iter_t *iter, void *dato);

// Saca el elemento de la lista ubicado en la posicion a la que apunta el
// iterador. Si la lista tiene elementos, se quita el elemento ubicado en la
// posicion apuntada por el iterador, y se devuelve su valor, si está vacía, 
// devuelve NULL.
// Pre: el iterador fue creado.
// Post: se devolvió el valor del elemento anteriormente mencionado, la lista
// contiene un elemento menos, si la lista no estaba vacía.
void *lista_iter_borrar(lista_iter_t *iter);

/* ******************************************************************
 *                PRIMITIVA DEL ITERADOR INTERNO
 * *****************************************************************/

// Itera sobre la lista y la modifica mediante la función visitar recibida por
// parámetro. Recibe un puntero extra para hacer con el lo que se prefiera.
// Pre: la lista fue creada. visitar es una función capaz de modificar los
// elementos de la lista.
// Post: se modificaron todos los elementos de la lista según lo que hace
// la función visitar.
void lista_iterar(lista_t *lista, bool (*visitar)(void *dato, void *extra), void *extra);


/* *****************************************************************
 *                      PRUEBAS UNITARIAS
 * *****************************************************************/


// Realiza pruebas sobre la implementación del alumno.
//
// Las pruebas deben emplazarse en el archivo ‘pruebas_alumno.c’, y
// solamente pueden emplear la interfaz pública tal y como aparece en lista.h
// (esto es, las pruebas no pueden acceder a los miembros del struct lista).
//
// Para la implementación de las pruebas se debe emplear la función
// print_test(), como se ha visto en TPs anteriores.
void pruebas_lista_alumno(void);

#endif // LISTA_H
