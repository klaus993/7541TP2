#include "heap.h"
#include <stdlib.h>
#include <stdio.h>

/* Función de comparación. */
int cmp(const void* a, const void* b) {
    if(*(int*)a < *(int*)b) return -1;
    if(*(int*)a > *(int*)b) return 1;
    return 0;
}

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

int main() {
    int aux[] = {1 ,7,-3,4,5,2};    
    void* elementos[6];
    for(int i = 0; i < 6; i++) {
        elementos[i] = &aux[i];
    }
    void** arreglo_k = top_k(4, elementos, 6, cmp);
    for(int i = 0; i < 4; i++) {
        printf("%i \n", *(int*)arreglo_k[i]);
    }
	free(arreglo_k);
}
