#include "testing.h"
#include <stdlib.h>
#include <stdio.h>

void pruebas_abb_alumno(void);
void pruebas_volumen_alumno(size_t);

/* ******************************************************************
 *                        PROGRAMA PRINCIPAL
 * *****************************************************************/

int main(int argc, char *argv[])
{

    printf("~~~ PRUEBAS CÁTEDRA ~~~\n");
    pruebas_abb_alumno();

    return failure_count() > 0;
}
