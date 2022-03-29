
#include "modulo.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <math.h>
#include <sys/time.h>
#include <errno.h>
/* Se crea una variable con un valor alto para reservar memoria*/
#define DATA_SZ (1024*1024*64*3)

/* Se reserva el espacio de memoria según el valor */
static double MEM_CHUNK[DATA_SZ];


/* Se implementa paso a paso benchmark Multiplicaión de Matrices
	Algoritmo clásico ( filas x columnas) de matrices
	de igual dimensión*/

int main(int argc, char *argv[]) {
	
	/* Se calcula la dimensión de la matriz*/
	int N = (int) atof(argv[1]);
	//printf("Valor ingresado %d", N);
	
	/* Apuntamos los vectores (creación) al espacio de memoeria reservado, con dimension NxN*/
	double *Ma, *Mb, *Mr; // * el asterísco se refiere al puntero de memoria
	Ma = MEM_CHUNK;//Ma tiene el espacio de memoria de mem_chunk
	Mb = Ma + N*N;//Ma
	Mr = Mb + N*N;
	
	initMatrix(N, Ma, Mb, Mr);
	
	SampleStart();
	//printf("\nA\n");
	//printMatrix(N, Ma);
	//printf("\nB\n");
	//printMatrix(N, Mb);
	matrixMM1c(N, Ma, Mb, Mr);
	//printf("\nR\n");
	//printMatrix(N, Mr);
	SampleEnd();
	
	
	return 0;
}
