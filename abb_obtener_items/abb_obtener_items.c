#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../abb/abb.h"

typedef struct abb_item {
    const char* clave;
    void* valor;
} abb_item_t;

abb_item_t* abb_obtener_items(abb_t* abb) {
	if (abb_cantidad(abb) == 0) {
		return NULL;
	}
	abb_item_t *items = malloc(sizeof(abb_item_t) * abb_cantidad(abb));
	abb_iter_t *iter = abb_iter_in_crear(abb);
	unsigned i = 0;
	while(!abb_iter_in_al_final(iter)) {
		items[i].clave = abb_iter_in_ver_actual(iter);
		items[i].valor = abb_obtener(abb, items[i].clave);
		abb_iter_in_avanzar(iter);
		i++;
	}
	return items;
}

int main() {
    abb_t* abb = abb_crear(strcmp, NULL);

    char *clave1 = "perro", *valor1 = "guau";
    char *clave2 = "gato", *valor2 = "miau";
    char *clave3 = "vaca", *valor3 = "mu";

    abb_guardar(abb, clave1, valor1);
    abb_guardar(abb, clave2, valor2);
    abb_guardar(abb, clave3, valor3);

    abb_item_t*	items = abb_obtener_items(abb);
    size_t cant = abb_cantidad(abb);
    for (int i = 0; i <= cant+1; i++) {
    	puts(items[i].clave);
//    	puts((char*)(items[i].valor));
    	i++;
    }

	abb_destruir(abb);

	return 0;
}