#include "../heap/heap.h"
#include <stdlib.h>
#include <stdio.h>

/* Recibe un arreglo de elementos y una función de comparación. Devuelve un nuevo
arreglo con los k elementos más chicos, en orden de menor a mayor. */
void** top_k(size_t k, void** datos, size_t tam_datos, cmp_func_t cmp) {
	heap_t* heap = heap_crear(cmp);
	void** arreglo_k = calloc(sizeof(void*), k);
	size_t i;
	for(i = 0; i < k; i++) {
		printf("%i numero en vector \n",*(int*)(datos[i]));
		if(i == tam_datos) break;
		heap_encolar(heap, datos[i]);
	}
	for(; i < tam_datos; i++) {
		void *num = heap_ver_max(heap);
		if(*(int*)datos[i] < *(int*)num) {
			heap_desencolar(heap);
			heap_encolar(heap, datos[i]);
		}
	}
	i = k - 1;
	while(!heap_esta_vacio(heap)) {
		arreglo_k[i] = heap_desencolar(heap);
		i--;
	}
	heap_destruir(heap, NULL);
	return arreglo_k;
}
