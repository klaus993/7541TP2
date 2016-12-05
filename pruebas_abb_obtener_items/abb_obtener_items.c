#include <string.h>
#include <stdio.h>
#include "../abb/abb.h"

int main() {
    abb_t* abb = abb_crear(strcmp, NULL);

    char *clave1 = "perro", *valor1 = "guau";
    char *clave2 = "gato", *valor2 = "miau";
    char *clave3 = "vaca", *valor3 = "mu";

    abb_guardar(abb, clave1, valor1);
	abb_guardar(abb, clave2, valor2);
    abb_guardar(abb, clave3, valor3);

	abb_item_t *items = abb_obtener_items(abb);

	for (int i = 0; i < 3; i++) {
		printf("Clave: %s\n", items[i].clave);
		printf("Valor: %s\n", (char*)items[i].valor);
	}

	return 0;
}
