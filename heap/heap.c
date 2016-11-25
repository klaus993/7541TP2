#include "heap.h"
#include <stdlib.h>
#include <stdio.h>

#define TAM_INICIAL 10

void swap(void *arreglo[], size_t i, size_t pos_mayor);
void heapify(void* arreglo[], size_t n, cmp_func_t cmp);
void downheap(void *arreglo[], size_t n, size_t i, cmp_func_t cmp);

void heap_sort(void *elementos[], size_t cant, cmp_func_t cmp) {
	if (cant <= 1) {
		return;
	}
	size_t cantidad = cant;
	heapify(elementos, cant, cmp);
	for(size_t i = 0; i < cant; i++) {
		swap(elementos, 0, cantidad - 1);
		cantidad--;
		downheap(elementos, cantidad, 0, cmp);
	}
}

struct heap {
	void** arreglo;
	size_t cantidad;
	size_t capacidad;
	cmp_func_t cmp;
};

// Pre: el heap fue creado.
// Post: el heap duplicó o redujo en la mitad su capacidad y devolvió true,
// o el heap queda intacto y devuelve false si no se pudo cambiar la capacidad.
bool heap_redimensionar(heap_t* heap, size_t redimension) {
	void** arreglo_nuevo = realloc(heap->arreglo, redimension * sizeof(void*));
	if(redimension > 0 && !arreglo_nuevo) return false;
	heap->arreglo = arreglo_nuevo;
	heap->capacidad = redimension;
	return true;
}	

/* Recibe un puntero a un arreglo, un tamaño n y una función de comparación.
Devuelve un heap con un arreglo nuevo, cuyos elementos pertenecen al arreglo 
pasado por parámetro. En caso de ser NULL ese arreglo, se crea un nuevo arreglo
vacío. */
heap_t* _heap_crear(void *arreglo[], size_t n, cmp_func_t cmp) {
	heap_t* heap = malloc(sizeof(heap_t));
	if(!heap) return NULL;
	void** arreglo_nuevo = malloc(sizeof(void*) * n);
	if(!arreglo_nuevo) {
		free(heap);
		return NULL;
	}
	if(arreglo) {
		for(int i = 0; i < n; i++) {
			arreglo_nuevo[i] = arreglo[i];
		}
	}
	heap->arreglo = arreglo_nuevo;
	heap->capacidad = n;
	heap->cantidad = 0;
	heap->cmp = cmp;
	return heap;
}

/* Recibe un puntero a un arreglo, y dos posiciones. Intercambia el contenido de
ambas posiciones del arreglo. */
void swap(void *arreglo[], size_t i, size_t pos_mayor) {
	void* aux = arreglo[i];
	arreglo[i] = arreglo[pos_mayor];
	arreglo[pos_mayor] = aux; 
}

/* Recibe un puntero a un arreglo, su tamaño, una posición i y una función de
comparación. Distribuye los "hijos" del elemento ubicado en esa posición según el
que tenga mayor valor, comparando el "padre" con los "hijos". */
void downheap(void *arreglo[], size_t n, size_t i, cmp_func_t cmp) {
	if(i >= n) return;
	size_t pos_izq = i*2 + 1;
	size_t pos_der = i*2 + 2;
	size_t pos_mayor = i;
	if(pos_izq < n && cmp(arreglo[i], arreglo[pos_izq]) < 0) {
		pos_mayor = pos_izq;
	}
	if(pos_der < n && cmp(arreglo[pos_mayor], arreglo[pos_der]) < 0) {
		pos_mayor = pos_der;
	}
	if(pos_mayor != i) {
		swap(arreglo, i, pos_mayor);
		downheap(arreglo, n, pos_mayor, cmp);
	}
}

/* Recibe un puntero a un arreglo, su tamaño y una función de comparación.
Reacomoda el heap con downheap. */
void heapify(void* arreglo[], size_t n, cmp_func_t cmp) {
	size_t i = n/2 - 1;
	for(; i >= 0; i--) {
		downheap(arreglo, n, i, cmp);
		if(i == 0) break;
	}
}

/* Recibe un puntero a un arreglo, una posición i y una función de comparación. 
Distribuye un elemento recién agregado en la posición i y se lo ordena en el
heap según su valor, comparándolo con cada "padre". */
void upheap(void *arreglo[], size_t i, cmp_func_t cmp) {
	if(i == 0) return;
	size_t pos_padre = (i - 1) / 2;
	if(cmp(arreglo[i], arreglo[pos_padre]) > 0) {
		swap(arreglo, i, pos_padre);
		upheap(arreglo, pos_padre, cmp);
	}
}

heap_t *heap_crear(cmp_func_t cmp) {
	heap_t* heap = _heap_crear(NULL, TAM_INICIAL, cmp);
	if(!heap) return NULL;
	return heap;
}

heap_t *heap_crear_arr(void *arreglo[], size_t n, cmp_func_t cmp) {
	heapify(arreglo, n, cmp);
	heap_t* heap = _heap_crear(arreglo, n, cmp);
	if(!heap) return NULL;
	heap->cantidad = n;
	return heap;
}

void heap_destruir(heap_t *heap, void destruir_elemento(void *e)) {
	if (!heap_esta_vacio(heap)) {
		for(size_t i = 0; i < heap->cantidad; i++) {
			if(destruir_elemento) destruir_elemento(heap->arreglo[i]);
		}
	}
	free(heap->arreglo);
	free(heap);
}

size_t heap_cantidad(const heap_t *heap) {
	return heap->cantidad;
}

bool heap_esta_vacio(const heap_t *heap) {
	return !heap->cantidad;
}

bool heap_encolar(heap_t *heap, void *elem) {
	if(!elem) return false;
	if(heap->cantidad >= heap->capacidad){
		if(!(heap_redimensionar(heap, 2 * heap->capacidad))) return false;
	}
	heap->arreglo[heap->cantidad] = elem;
	heap->cantidad++;
	upheap(heap->arreglo, heap->cantidad - 1, heap->cmp);
	return true;
}

void *heap_ver_max(const heap_t *heap) {
	if(heap_esta_vacio(heap)) return NULL;
	return heap->arreglo[0];
}

void *heap_desencolar(heap_t *heap) {
	if(heap_esta_vacio(heap)) return NULL;
	swap(heap->arreglo, 0, heap->cantidad - 1);
	void* aux = heap->arreglo[heap->cantidad - 1];
	heap->arreglo[heap->cantidad - 1] = NULL;
	heap->cantidad--;
	if(heap->cantidad <= heap->capacidad / 4 && TAM_INICIAL < heap->cantidad){ 
		heap_redimensionar(heap, heap->capacidad / 2);
	}
	downheap(heap->arreglo, heap->cantidad, 0, heap->cmp);
	return aux;
}

void heap_actualizar_prioridad(heap_t* heap, void* dato) {
	unsigned i = 0;
	unsigned pos = -1;
	while (i < heap->cantidad) {
		if (*(int*)dato == *(int*)(heap->arreglo[i])) {
			pos = i;
		}
		i++;
	}
	if (pos == -1) {
		return;
	}
	size_t pos_padre = (pos - 1) / 2;
	size_t pos_izq = pos * 2 + 1;
	size_t pos_der = pos * 2 + 2;
	if ((pos_izq < heap->cantidad && heap->cmp(heap->arreglo[pos], heap->arreglo[pos_izq]) < 0) || 
			(pos_der < heap->cantidad && heap->cmp(heap->arreglo[pos], heap->arreglo[pos_der]) < 0)) {
		downheap(heap->arreglo, heap->cantidad, pos, heap->cmp);
	} else if (pos_padre >= 0 && heap->cmp(heap->arreglo[pos], heap->arreglo[pos_padre]) > 0) {
		upheap(heap->arreglo, pos, heap->cmp);
	}
}
