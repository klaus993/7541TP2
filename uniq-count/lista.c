#include "lista.h"
#include <stdlib.h>

/***************************************************
 *               ESTRUCTURA NODO                   *
 ***************************************************/

typedef struct nodo {
	void *dato;
	struct nodo *prox;
} nodo_t;

/* Post: devuelve el nodo creado, con el dato pasado por parámetro
como dato, y con NULL como referencia al próximo. Devuelve NULL si no se pudo crear.*/
nodo_t *nodo_crear(void *dato) {
	nodo_t *nodo = malloc(sizeof(nodo_t));
	if (nodo == NULL) {
		return NULL;
	}
	nodo->dato = dato;
	nodo->prox = NULL;
	return nodo;
}


/***************************************************
 *           ESTRUCTURA LISTA ENLAZADA             *
 ***************************************************/


struct lista {
	nodo_t *prim;
	nodo_t *ult;
	size_t cantidad;
};

lista_t *lista_crear() {
	lista_t *lista = malloc(sizeof(lista_t));
	if (lista == NULL) {
		return NULL;
	}
	lista->prim = NULL;
	lista->ult = NULL;
	lista->cantidad = 0;
	return lista;
}

bool lista_esta_vacia(const lista_t *lista) {
	return lista->prim == NULL;
}

bool lista_insertar_primero(lista_t *lista, void *dato){
	nodo_t *nodo_nuevo = nodo_crear(dato);
	if (nodo_nuevo == NULL) {
		return false;
	}
	lista->cantidad++;
	if (lista_esta_vacia(lista)) {
		lista->ult = nodo_nuevo;
	} else {
		nodo_nuevo->prox = lista->prim;
	}
	lista->prim = nodo_nuevo;
	return true;
}

bool lista_insertar_ultimo(lista_t *lista, void *dato) {
	nodo_t *nodo_nuevo = nodo_crear(dato);
	if (nodo_nuevo == NULL) {
		return false;
	}
	lista->cantidad++;
	if (lista_esta_vacia(lista)) {
		lista->prim = nodo_nuevo;
	} else {
		lista->ult->prox = nodo_nuevo;
	}
	lista->ult = nodo_nuevo;
	return true;
}

void *lista_borrar_primero(lista_t *lista) {
	if (lista_esta_vacia(lista)) {
		return NULL;
	}
	nodo_t *aux = lista->prim;
	void *dato = aux->dato;
	lista->prim = lista->prim->prox;
	free(aux);
	lista->cantidad--;
	if (lista_esta_vacia(lista)) {
		lista->ult = NULL;
	}
	return dato;
}

void *lista_ver_primero(const lista_t *lista) {
	if (lista_esta_vacia(lista)) {
		return NULL;
	}
	return lista->prim->dato;
}

void *lista_ver_ultimo(const lista_t *lista) {
	if (lista_esta_vacia(lista)) {
		return NULL;
	}
	return lista->ult->dato;
}

size_t lista_largo(const lista_t *lista) {
	return lista->cantidad;
}

void lista_destruir(lista_t *lista, void destruir_dato(void *)) {
	void *dato;
	while (!lista_esta_vacia(lista)) {
		dato = lista_borrar_primero(lista);
		if (destruir_dato != NULL) {
			destruir_dato(dato);
		}
	}
	free(lista);
}

/***************************************************
 *               ITERADOR DE LISTA                 *
 ***************************************************/


struct lista_iter {
	nodo_t *actual;
	nodo_t *anterior;
	lista_t *lista;
};


lista_iter_t *lista_iter_crear(lista_t *lista) {
	lista_iter_t *iter = malloc(sizeof(lista_iter_t));
	if (iter == NULL) {
		return NULL;
	}
	iter->anterior = NULL;
	iter->actual = lista->prim;
	iter->lista = lista;
	return iter;
}

bool lista_iter_avanzar(lista_iter_t *iter){
	if (lista_iter_al_final(iter)) {
		return false;
	}
	iter->anterior = iter->actual;
	iter->actual = iter->actual->prox;
	return true;
}

void *lista_iter_ver_actual(const lista_iter_t *iter){
	if (lista_iter_al_final(iter)) {
		return NULL;
	}
	return iter->actual->dato;
}

bool lista_iter_al_final(const lista_iter_t *iter) {
	return iter->actual == NULL;
}

void lista_iter_destruir(lista_iter_t *iter) {
	free(iter);
}

bool lista_iter_insertar(lista_iter_t *iter, void *dato) {
	nodo_t *nodo_nuevo = nodo_crear(dato);
	if (nodo_nuevo == NULL) {
		return false;
	}
	if (iter->actual == iter->lista->ult || lista_iter_al_final(iter)) {
		iter->lista->ult = nodo_nuevo;
	} 
	if (iter->actual == iter->lista->prim || lista_esta_vacia(iter->lista)) {
		iter->lista->prim = nodo_nuevo;
	} else {
		iter->anterior->prox = nodo_nuevo;
	}
	nodo_nuevo->prox = iter->actual;
	iter->lista->cantidad++;
	iter->actual = nodo_nuevo;
	return true;
}

void *lista_iter_borrar(lista_iter_t *iter) {
	if (lista_iter_al_final(iter)) {
		return NULL;
	}
	if (iter->actual == iter->lista->prim) {
		iter->lista->prim = iter->lista->prim->prox;
	} else {
		iter->anterior->prox = iter->actual->prox;
	}
	if (iter->actual == iter->lista->ult) {
		iter->lista->ult = iter->anterior;
	}
	nodo_t *aux = iter->actual;
	void *dato = aux->dato;
	iter->actual = iter->actual->prox;
	iter->lista->cantidad--;
	free(aux);
	return dato;
}

/* ITERADOR INTERNO */

void lista_iterar(lista_t *lista, bool (*visitar)(void *dato, void *extra), void *extra) {
	nodo_t *actual = lista->prim;
	while (actual != NULL && visitar(actual->dato, extra)) {
		actual = actual->prox;
	}
}
