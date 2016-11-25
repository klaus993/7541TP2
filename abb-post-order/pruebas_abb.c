#include "abb.h"
#include "testing.h"
#include "lista.h"
#include <stdio.h>
#include <stdbool.h>
#include <string.h>


bool comparar_resultado(lista_t* lista, char* arreglo[],size_t tam){
	lista_iter_t* iter = lista_iter_crear(lista);
	size_t pos = 0;
	while(!lista_iter_al_final(iter)){
		char* cadena = lista_iter_ver_actual(iter);
		if(pos >= tam || strcmp(cadena,arreglo[pos]) != 0){
			lista_iter_destruir(iter);
			return false;
		}
		lista_iter_avanzar(iter);
		pos ++;
	}
	lista_iter_destruir(iter);
	return true;
}	

bool visitar(const char* clave, void* dato, void* extra){
	return lista_insertar_ultimo((lista_t*) extra,dato);
}

static void prueba_abb_iterador_interno_post(){
	printf("\nINICIO DE PRUEBAS DE ABB ITERADOR INTERNO POST ORDER\n\n");

    abb_t* abb = abb_crear(strcmp,NULL);

    char *claves[] = {"1", "2", "3", "4", "5", "6" , "7" ,"8", "9"};
	char *post[] = {"1", "2", "4", "3", "7", "6" , "9" ,"8", "5"};
	lista_t* lista= lista_crear();

	print_test("Prueba abb insertar clave1", abb_guardar(abb, claves[4], claves[4]));
    print_test("Prueba abb insertar clave2", abb_guardar(abb, claves[2], claves[2]));
    print_test("Prueba abb insertar clave3", abb_guardar(abb, claves[7], claves[7]));
	print_test("Prueba abb insertar clave1", abb_guardar(abb, claves[1], claves[1]));
    print_test("Prueba abb insertar clave2", abb_guardar(abb, claves[3], claves[3]));
    print_test("Prueba abb insertar clave3", abb_guardar(abb, claves[5], claves[5]));
	print_test("Prueba abb insertar clave1", abb_guardar(abb, claves[8], claves[8]));
    print_test("Prueba abb insertar clave2", abb_guardar(abb, claves[0], claves[0]));
    print_test("Prueba abb insertar clave3", abb_guardar(abb, claves[6], claves[6]));

	abb_post_order(abb, visitar, lista);
	print_test("La lista obtenida esta ordenada correctamente", comparar_resultado(lista,post,9));
	
	lista_destruir(lista,NULL);
	abb_destruir(abb);
}

static void prueba_abb_iterador_externo_post(){
	printf("\nINICIO DE PRUEBAS DE ABB ITERADOR INTERNO POST ORDER\n\n");

    abb_t* abb = abb_crear(strcmp,NULL);

    char *claves[] = {"1", "2", "3", "4", "5", "6" , "7" ,"8", "9"};
	char *post[] = {"1", "2", "4", "3", "7", "6" , "9" ,"8", "5"};

	print_test("Prueba abb insertar clave1", abb_guardar(abb, claves[4], claves[4]));
    print_test("Prueba abb insertar clave2", abb_guardar(abb, claves[2], claves[2]));
    print_test("Prueba abb insertar clave3", abb_guardar(abb, claves[7], claves[7]));
	print_test("Prueba abb insertar clave1", abb_guardar(abb, claves[1], claves[1]));
    print_test("Prueba abb insertar clave2", abb_guardar(abb, claves[3], claves[3]));
    print_test("Prueba abb insertar clave3", abb_guardar(abb, claves[5], claves[5]));
	print_test("Prueba abb insertar clave1", abb_guardar(abb, claves[8], claves[8]));
    print_test("Prueba abb insertar clave2", abb_guardar(abb, claves[0], claves[0]));
    print_test("Prueba abb insertar clave3", abb_guardar(abb, claves[6], claves[6]));

	abb_iter_t* iter = abb_iter_post_crear(abb);
	
	size_t pos = 0;
	while(!abb_iter_post_al_final(iter)){
		const char* cadena = abb_iter_post_ver_actual(iter);
		print_test("El valor obtenido tiene el orden correcto", strcmp(cadena,post[pos]) == 0);
		print_test("Prueba abb iterador avanzar es true", abb_iter_post_avanzar(iter));
		pos ++;
	}
	print_test("Prueba abb iterador esta al final, es true", abb_iter_post_al_final(iter));
	
	abb_iter_post_destruir(iter);
	abb_destruir(abb);
}

//No se como hacer el de iterador en volumen para comparar_resultado

	
void pruebas_abb_alumno()
{
    /* Ejecuta todas las pruebas unitarias. */
	prueba_abb_iterador_interno_post();
	prueba_abb_iterador_externo_post();
	
   
}
