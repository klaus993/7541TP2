#define _POSIX_C_SOURCE 200809L
#include <stdint.h>
#include "hash.h"
#include <stdlib.h>
#include <string.h>

#define rot(x,k) (((x)<<(k)) | ((x)>>(32-(k))))

#define mix(a,b,c) \
{ \
  a -= c;  a ^= rot(c, 4);  c += b; \
  b -= a;  b ^= rot(a, 6);  a += c; \
  c -= b;  c ^= rot(b, 8);  b += a; \
  a -= c;  a ^= rot(c,16);  c += b; \
  b -= a;  b ^= rot(a,19);  a += c; \
  c -= b;  c ^= rot(b, 4);  b += a; \
}

#define final(a,b,c) \
{ \
  c ^= b; c -= rot(b,14); \
  a ^= c; a -= rot(c,11); \
  b ^= a; b -= rot(a,25); \
  c ^= b; c -= rot(b,16); \
  a ^= c; a -= rot(c,4);  \
  b ^= a; b -= rot(a,14); \
  c ^= b; c -= rot(b,24); \
}

uint32_t lookup3 (
  const void *key,
  size_t      length,
  uint32_t    initval
) {
  uint32_t  a,b,c;
  const uint8_t  *k;
  const uint32_t *data32Bit;

  data32Bit = key;
  a = b = c = 0xdeadbeef + (((uint32_t)length)<<2) + initval;

  while (length > 12) {
    a += *(data32Bit++);
    b += *(data32Bit++);
    c += *(data32Bit++);
    mix(a,b,c);
    length -= 12;
  }

  k = (const uint8_t *)data32Bit;
  switch (length) {
    case 12: c += ((uint32_t)k[11])<<24;
    case 11: c += ((uint32_t)k[10])<<16;
    case 10: c += ((uint32_t)k[9])<<8;
    case 9 : c += k[8];
    case 8 : b += ((uint32_t)k[7])<<24;
    case 7 : b += ((uint32_t)k[6])<<16;
    case 6 : b += ((uint32_t)k[5])<<8;
    case 5 : b += k[4];
    case 4 : a += ((uint32_t)k[3])<<24;
    case 3 : a += ((uint32_t)k[2])<<16;
    case 2 : a += ((uint32_t)k[1])<<8;
    case 1 : a += k[0];
             break;
    case 0 : return c;
  }
  final(a,b,c);
  return c;
}

unsigned int fhash(const char *word, unsigned int hashTableSize){
  unsigned int initval;
  unsigned int hashAddress;

  initval = 12345;
  hashAddress = lookup3(word, strlen(word), initval);
  return (hashAddress%hashTableSize);
}


#define TAM_INICIAL 100
#define FACTOR_CARGA_AGRANDAR 0.70
#define FACTOR_CARGA_ACHICAR 0.15
#define FACTOR_REDIMENSION 2

/*Definición el tipo estado_t. */
typedef enum estado {VACIO, OCUPADO, BORRADO} estado_t;

/*Definición del struct nodo para la tabla de hash. */
typedef struct nodo_hash {
	char *clave;
	void *valor;
	estado_t estado;
} nodo_hash_t;

struct hash {
	nodo_hash_t *tabla;
	size_t cantidad;
	size_t capacidad;
	hash_destruir_dato_t destruir_dato;
};

/* Crea una tabla de nodo_hash_t, inicializando los estados de los nodos en VACIO.
Post: si se pudo crear la tabla, devuelve un puntero a la misma, sino, devuelve un puntero a NULL.
*/
nodo_hash_t *crear_tabla(size_t tamanio) {
	nodo_hash_t *tabla = malloc(tamanio * sizeof(nodo_hash_t));
	if (!tabla) {
		return NULL;
	}
	for (int i = 0; i < tamanio; i++) {
		tabla[i].estado = VACIO;
	}
	return tabla;
}

hash_t *hash_crear(hash_destruir_dato_t destruir_dato) {
	hash_t *hash = malloc(sizeof(hash_t));
	if (!hash) return NULL;
	hash->tabla = crear_tabla(TAM_INICIAL);
	if (!hash->tabla) {
		free(hash);
		return NULL;
	}
	hash->destruir_dato = destruir_dato;
	hash->cantidad = 0;
	hash->capacidad = TAM_INICIAL;
	return hash;
}

/* Recibe la estructura hash y la variable redimension de tipo size_t y re hashea
todos los datos en una nueva tabla del tamaño indicado por parámetro.
Pre: El hash fue creado.
Post: Devuelve true si se rehasheó correctamente, o false en caso de no poder haberse creado la tabla nueva.
	  La tabla vieja se liberó de la memoria, y la tabla nueva es la nueva tabla del hash.
*/
bool hash_redimensionar(hash_t *hash, size_t redimension) {
	nodo_hash_t *tabla_nueva = crear_tabla(redimension);
	if (!tabla_nueva) {
		return false;
	}
	size_t capacidad_vieja = hash->capacidad;
	hash->capacidad = redimension;
	nodo_hash_t *tabla_vieja = hash->tabla;
	hash->tabla = tabla_nueva; 
	if (hash->cantidad != 0) {
		hash->cantidad = 0;
		for (int i = 0; i < capacidad_vieja; i++) {
			if (tabla_vieja[i].estado == OCUPADO) {
				hash_guardar(hash, tabla_vieja[i].clave, tabla_vieja[i].valor);
				free(tabla_vieja[i].clave);
			}
		}
	}
	free(tabla_vieja);
	return true;
}

/* Función que recibe una tabla de hash y una clave. 
Recorre la tabla de hash hasta encontrar la clave y una vez encontrada devuelve
el índice en el cual se encuentra la clave o el siguiente vacío.
Pre: el hash fue creado
Post: si la clave está en la tabla, devuelve su índice, de lo contrario devuelve
el próximo espacio vacío.
*/
size_t recorrer(const hash_t *hash, const char *clave){
	size_t indice = fhash(clave, (unsigned int)hash->capacidad);
	while (hash->tabla[indice].estado != VACIO) {
		if (hash->tabla[indice].estado == OCUPADO && strcmp(hash->tabla[indice].clave, clave) == 0) {
			return indice;
		}
		if (indice == hash->capacidad - 1) { 
			indice = 0;
		}
		indice = (indice + 1) % hash->capacidad;
	}
	return indice;
}

bool hash_guardar(hash_t *hash, const char *clave, void *dato) {
	if (((double)hash->cantidad / (double)hash->capacidad) >= (double)FACTOR_CARGA_AGRANDAR) {
		if (!hash_redimensionar(hash, hash->capacidad * FACTOR_REDIMENSION)) return false;
	}
	size_t indice = recorrer(hash, clave);
	if (hash->tabla[indice].estado == OCUPADO) {
		if (hash->destruir_dato) {
			hash->destruir_dato(hash->tabla[indice].valor);
		}
	} else {
		char *clave_copiada = malloc(sizeof(char) * strlen(clave) + 1);
		strcpy(clave_copiada, clave);
		hash->tabla[indice].clave = clave_copiada;
		hash->tabla[indice].estado = OCUPADO;
		hash->cantidad++;
	}
	hash->tabla[indice].valor = dato;
	return true;
}

void *hash_borrar(hash_t *hash, const char *clave) {
	size_t indice = recorrer(hash, clave);
	if (hash->tabla[indice].estado == OCUPADO && ((double)(hash->cantidad - 1) / (double)hash->capacidad) <= (double)FACTOR_CARGA_ACHICAR) {
		hash_redimensionar(hash, hash->capacidad / FACTOR_REDIMENSION);
		indice = recorrer(hash, clave);
	}
	if (hash->tabla[indice].estado == OCUPADO) {
		free(hash->tabla[indice].clave);
		hash->tabla[indice].estado = BORRADO;
		hash->cantidad--;
	} else {
		return NULL;
	}
	return hash->tabla[indice].valor;
}

void *hash_obtener(const hash_t *hash, const char *clave) {
	size_t indice = recorrer(hash, clave);
	if (hash->tabla[indice].estado == OCUPADO) {
		return hash->tabla[indice].valor;
	}
	return NULL;
}

bool hash_pertenece(const hash_t *hash, const char *clave) {
	return hash->tabla[recorrer(hash, clave)].estado == OCUPADO;
}

size_t hash_cantidad(const hash_t *hash) {
	return hash->cantidad;
}

void hash_destruir(hash_t *hash) {
	for (int i = 0; i < hash->capacidad; i++){
		if (hash->destruir_dato && hash->tabla[i].estado == OCUPADO) hash->destruir_dato(hash->tabla[i].valor);
		if (hash->tabla[i].estado == OCUPADO) free(hash->tabla[i].clave);
	}
	free(hash->tabla);
	free(hash);
}

/* Iterador del hash */

struct hash_iter {
	const hash_t *hash;
	size_t pos;
};

hash_iter_t *hash_iter_crear(const hash_t *hash) {
	hash_iter_t *iter = malloc(sizeof(hash_iter_t));
	if (!iter) return NULL;
	iter->hash = hash;
	iter->pos = 0;
	if (iter->hash->tabla[iter->pos].estado != OCUPADO) {
		hash_iter_avanzar(iter);
	}
	return iter;
}

bool hash_iter_avanzar(hash_iter_t *iter) {
	if (hash_iter_al_final(iter)) return false;
	do {
		iter->pos++;
	} while (!hash_iter_al_final(iter) && iter->hash->tabla[iter->pos].estado != OCUPADO);
	return true;
}

const char *hash_iter_ver_actual(const hash_iter_t *iter) {
	if (hash_iter_al_final(iter)) {
		return NULL;
	}
	return iter->hash->tabla[iter->pos].clave;
}

bool hash_iter_al_final(const hash_iter_t *iter) {
	return iter->pos == iter->hash->capacidad;
}

void hash_iter_destruir(hash_iter_t* iter) {
	free(iter);
}
