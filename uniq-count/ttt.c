#include <stdio.h>
#include <stdlib.h>

int main() {
	int *x = malloc(sizeof(int)); //calloc(1, sizeof(int));
	*x = 1;
	printf("%d\n", *x);
	(*x)++;
	printf("%d\n", *x);
	free(x);
}
