#include "lista.h"
#include <stdlib.h>

/*Definición del struct nodo para la lista*/
typedef struct nodo_lista{
	void* dato;
	struct nodo_lista* sig;
} nodo_lista_t;

/*Definición del struct lista*/
struct lista{
	nodo_lista_t* prim;
	nodo_lista_t* ult;
	size_t largo;
};

/*Definición del struct iter para la lista*/
struct lista_iter{
	nodo_lista_t* act;
	nodo_lista_t* ant;
	lista_t* lista;
};

/* Recibe un puntero hacia un dato y crea un nodo con ese valor en caso de ser
posible, y devuelve el nodo. Sino devuelve NULL. */
nodo_lista_t* crear_nodo2(void* dato){// por defecto se le pone al siguiente del nodo NUULL?
	nodo_lista_t* nodo = malloc(sizeof(nodo_lista_t));
	if(!nodo) return NULL;
	nodo->dato = dato;
	return nodo;
}

//A CONTINUACIÓN SE MUESTRAN IMPLEMENTADAS LAS PRIMITVAS DE LA LISTA ENLAZADA.

lista_t* lista_crear(void){
	lista_t* lista = malloc(sizeof(lista_t));
	if(!lista) return NULL;
	lista->prim = NULL;
	lista->ult = NULL;
	lista->largo = 0;
	return lista;
}

void lista_destruir(lista_t *lista, void destruir_dato(void *)){
	while(!lista_esta_vacia(lista)){
		void* dato = lista_borrar_primero(lista);
		if(destruir_dato) destruir_dato(dato);
		
	}
	free(lista);
}

bool lista_esta_vacia(const lista_t *lista){
	return !lista->prim;
}

bool lista_insertar_primero(lista_t *lista, void *dato){
	nodo_lista_t* nodo = crear_nodo2(dato);
	if(!nodo) return false;
	if(!lista->prim) lista->ult = nodo;
	nodo_lista_t* aux = lista->prim;
	lista->prim = nodo;
	nodo->sig = aux;
	lista->largo++;
	return true;
}

bool lista_insertar_ultimo(lista_t *lista, void *dato){
	nodo_lista_t* nodo = crear_nodo2(dato);
	if(!nodo) return false;
	nodo->sig = NULL;
	if(!lista->prim) lista->prim = nodo;
	else lista->ult->sig = nodo;
	lista->ult = nodo;
	lista->largo++;
	return true;
}

void* lista_ver_primero(const lista_t *lista){
	if(lista_esta_vacia(lista)) return NULL;
	return lista->prim->dato;
}

void* lista_ver_ultimo(const lista_t *lista){
	if(lista_esta_vacia(lista)) return NULL;
	return lista->ult->dato;
}

void *lista_borrar_primero(lista_t *lista){
	if(lista_esta_vacia(lista)) return NULL;
	nodo_lista_t* aux = lista->prim;
	void* dato = lista->prim->dato;
	lista->prim = lista->prim->sig;
	if(!lista->prim) lista->ult = lista->prim;
	free(aux);
	lista->largo--;
	return dato;
}

size_t lista_largo(const lista_t *lista){
	return lista->largo;
}

//A CONTINUACIÓN SE MUESTRAN IMPLEMENTADAS LAS PRIMITVAS DEL ITERADOR EXTERNO.

lista_iter_t *lista_iter_crear(lista_t *lista){
	lista_iter_t* iter = malloc(sizeof(lista_iter_t));
	if(!iter) return NULL;
	iter->lista = lista;
	if(!lista->prim) iter->act = NULL;
	else iter->act = lista->prim;
	iter->ant = NULL;
	return iter;
}

bool lista_iter_avanzar(lista_iter_t *iter){
	if(lista_iter_al_final(iter)) return false;
	iter->ant = iter->act;
	iter->act = iter->act->sig;
	return true;
}

void *lista_iter_ver_actual(const lista_iter_t *iter){
	if(lista_iter_al_final(iter)) return NULL;
	return iter->act->dato;
}

bool lista_iter_al_final(const lista_iter_t *iter){
	return !iter->act;
}

void lista_iter_destruir(lista_iter_t *iter){
	free(iter);
}

bool lista_iter_insertar(lista_iter_t *iter, void *dato){
	if((!lista_esta_vacia(iter->lista) && iter->act == iter->lista->prim) 
		|| (lista_esta_vacia(iter->lista))){
		if(!lista_insertar_primero(iter->lista, dato)) return false;
		iter->act = iter->lista->prim;
	}
	else if(lista_iter_al_final(iter) && iter->ant){
		if(!lista_insertar_ultimo(iter->lista, dato)) return false;
		iter->act = iter->lista->ult;
		iter->ant->sig = iter->act;
	}
	else{
		nodo_lista_t* nodo = crear_nodo2(dato);
		if(!nodo) return false;
		nodo->sig = iter->act;
		iter->act = nodo;
		iter->ant->sig = iter->act;
		iter->lista->largo++;
	}
	return true;
}

void *lista_iter_borrar(lista_iter_t *iter){
	void* dato;
	if(lista_iter_al_final(iter)) return NULL;
	else{
		if(iter->act == iter->lista->prim){
			iter->act = iter->act->sig;
			dato = lista_borrar_primero(iter->lista);
		}
		else{
			nodo_lista_t* aux;
			aux = iter->act->sig;
			dato = iter->act->dato;
			free(iter->act);
			if(!aux) iter->lista->ult = iter->ant;
			iter->act = aux;
			iter->ant->sig = iter->act;
			iter->lista->largo--;
		}
	}
	return dato;
}

//A CONTINUACIÓN SE MUESTRAN IMPLEMENTADAS LAS PRIMITVAS DEL ITERADOR INTERNO.

void lista_iterar(lista_t *lista, bool (*visitar)(void *dato, void *extra), void *extra){
	nodo_lista_t* aux = lista->prim;
	while(aux && visitar(aux->dato, extra)) aux = aux->sig;
}
		
