#include "heap.c"
#include <stdio.h>

int cmp(const void* a, const void* b) {
    if(*(int*)a < *(int*)b) return -1;
    if(*(int*)a > *(int*)b) return 1;
    return 0;
}

void pruebas_heap_alumno(void) {
	int arr[] = {1, 7, -3, 4, 5, 2, 34, -11};

	void *elementos[8];
    for(int i = 0; i < 8; i++) {
        elementos[i] = &arr[i];
    }

    heap_t *heap = heap_crear_arr(elementos, 8, cmp);

    //arr[1] = 6;
    size_t cant = heap_cantidad(heap);
    unsigned i = 0;
    while (i < cant) {
    	printf("%d, ", *(int*)heap->arreglo[i]);
    	i++;
    }

    putchar('\n');

    heap_actualizar_prioridad(heap, elementos[1]);

    while (!heap_esta_vacio(heap)) {
        printf("%d, ", *(int*)heap_desencolar(heap));        
    }

    putchar('\n');
    
    heap_destruir(heap, NULL);


}

int main() {

	pruebas_heap_alumno();

	return 0;
}