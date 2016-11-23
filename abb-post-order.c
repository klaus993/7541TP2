struct abb_iter {
	pila_t* pila;
};

void apilar_traza_izquierda(pila_t* pila, nodo_abb_t* act) {
	while(act->izq) {
		while(act->izq) {
			pila_apilar(pila, act->clave);
			act = act->izq;
		}
		if(act->der) {
			pila_apilar(pila, act->clave);
			act = act->der;
		}
	}
}

abb_iter_t *abb_iter_post_crear(const abb_t *arbol) {
	abb_iter_t* iter = malloc(sizeof(abb_iter_t));
	if(!iter) return NULL;
	pila_t* pila = pila_crear();
	if(!pila) {
		free(iter);
		return NULL;
	}
	iter->pila = pila;
	nodo_abb_t* act = arbol->raiz; 
	apilar_traza_izquierda(iter->pila, act);
	return iter;
}

bool abb_iter_post_avanzar(abb_iter_t *iter) {
	if(pila_esta_vacia(iter->pila)) return false;
	nodo_abb_t* ant = pila_desapilar(iter->pila);
	nodo_abb_t* act = pila_ver_tope(iter->pila);
	if(ant == act->izq) {
		if(act->der) {
			pila_apilar(iter->pila, act->clave);
			act = act->der;
		}
		apilar_traza_izquierda(iter->pila, act);
	}
	return true;
}

const char *abb_iter_post_ver_actual(const abb_iter_t *iter) {
	if(abb_iter_post_al_final(iter)) return NULL;
	return pila_ver_tope(iter->pila);
}

bool abb_iter_post_al_final(const abb_iter_t *iter) {
	return pila_esta_vacia(iter->pila);
}

void abb_iter_post_destruir(abb_iter_t* iter) {
	free(iter->pila);
	free(iter);
}

//PRIMITIVA DEL ITERADOR INTERNO DEL ÁRBOL.

/* Recibe un puntero a una raíz de un árbol, una función visitar para modificar 
los subárboles ubicados por debajo de la raíz y un puntero extra para hacer con
él lo que se prefiera. */
void _iterar_post_order(nodo_abb_t* nodo, bool visitar(const char *, void *, void *), void *extra) {
	if(!nodo) return;
	_iterar_post_order(nodo->izq,visitar, extra);
	_iterar_post_order(nodo->der, visitar, extra);
	visitar(nodo->clave, nodo->valor, extra);
}

void abb_post_order(abb_t *arbol, bool visitar(const char *, void *, void *), void *extra) {
	_iterar_post_order(arbol->raiz, visitar, extra);
}
