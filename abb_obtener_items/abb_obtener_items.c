#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../abb/abb.h"

typedef struct abb_item {
    const char* clave;
    void* valor;
} abb_item_t;

abb_item_t* abb_obtener_items(abb_t* abb) {
	abb_item_t *items = malloc(sizeof(abb_item_t) * abb_cantidad(abb));
	abb_iter_t *iter = abb_iter_in_crear(abb);
	unsigned i = 0;
	while (!abb_iter_in_al_final(iter)) {
		items[i].clave = abb_iter_in_ver_actual(iter);
		items[i].valor = abb_obtener(abb, items[i].clave);
		abb_iter_in_avanzar(iter);
		i++;
	}
	abb_iter_in_destruir(iter);
	return items;
}
