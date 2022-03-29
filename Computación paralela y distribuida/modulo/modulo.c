/* 	* Universidad Sergio Arboleda
	* Fecha: 089 de febrero de 2022
	* Autora: Ángela Viviana Quintero Hernández
	* Materia: Parallel Computing
	* Tema: Implementación de BenchMarck en C
*/
#include "modulo.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <math.h>
#include <sys/time.h>
#include <errno.h>

/* Se crea una variable con un valor alto para reservar memoria*/
//#define DATA_SZ (1024*1024*64*3)

/* Se reserva el espacio de memoria según el valor */
//static double MEM_CHUNK[DATA_SZ];

/*Definiciòn de constantes*/
struct timespec inicio, fin;

/******************funciones **********/
/*Inicio: medida de tiempo*/
void SampleStart(){
	clock_gettime(CLOCK_MONOTONIC, &inicio); //& està indicando la direcciòn de inicio
}

/*Fin: medida de tiempo*/
void SampleEnd(){
	clock_gettime(CLOCK_MONOTONIC, &fin); //& està indicando la direcciòn de inicio
	/* Se imprime el tiempo*/
	double tiempoTotal;
	tiempoTotal = (fin.tv_sec - inicio.tv_sec)*1e9;//tv_sec es una funciòn de struct//// 1e9 son macrosegundos
	tiempoTotal = (tiempoTotal + (fin.tv_nsec - inicio.tv_nsec))*1e-9;
	printf(" %f \n", tiempoTotal);
	
}

/*Se crea un doble precisiòn aleatorio*/
float randMM(){
	float min = 0.001, max = 9.999;
	static int first = -1;
	if((first =(first<0)))
		srand(time(NULL)+getpid());
	if(min>max)
		return errno=EDOM, NAN;
	return min + (float)rand()/((float)RAND_MAX/(max-min));
}


/* Funcion a ser enviada a cada hilo, que realiza la multiplicación de matrices. La Matriz A,
 * se divide por porciones, en función de la dimensión y del número de hilos que requiere el usuario.
 * Nota la función setrá del tipo voidla cual retomará
 un warning potencial de riesgo. Pensar en eso, para mejorarla*/

void *multMM(void *arg){
	//los datos importados de MMposix
	struct dataThread *data = (struct dataThread *)arg;
	int idTh = data->idThread;
	double **Ma = data->Ma;
	double **Mb = data->Mb;
	double **Mr = data->Mr;
	int N = data->N;
	int Nthreads = data->NThreads;
	//arg: tiene el ID del hilo
	int i,j,k;
	int porcionSize, iniFila, finFila;
	double suma;
	
	// El arg es del tipo puntero vacío y se castea a puntero entero
	idTh = *(int *)(arg);
	// Se determina la porción a ser enviada a cada holi
	porcionSize = N/Nthreads;
	//Se pasa el inicio de la fila, según el id del hilo
	iniFila = idTh*porcionSize;
	//Se pasa el fin de la fila, según el id del hilo
	finFila = (idTh+1)*porcionSize;
	
	for(i = iniFila; i < finFila; ++i){
		for(j = 0; j < N; ++j){
			suma = 0.0;
			for(k=0; k < N; ++k){
				suma += Ma[i][k] * Mb[k][j];
			}
			Mc[i][j] = suma;
		}
	}
}



/* Se crea la funcion para inicializar las matrices*/
void initMatrix(int SZ, double *Ma, double *Mb, double *Mr){
	int i, j;
	for(i=0; i<SZ; ++i){
		for(j=0; j<SZ; ++j){
			Ma[j+i*SZ]= 3.9*(i-j);
			Mb[j+i*SZ]= 2.0*(j+i);
			Mr[j+i*SZ]= 0.0;
		}
	}
}

/* Se implementa la impresión para efectos de validación*/
void printMatrix(int SZ, double *M){
	int i, j;
	for(i=0; i<SZ; ++i){
		for(j=0; j<SZ; ++j){
			printf("%f   ",M[j+i*SZ]);
			
		}
		printf("\n");
	}
}

void matrixMM1c(int size, double *a, double *b, double *Mr){
	int i, j, k;
	for(i=0; i<size; ++i){
		for(j=0; j<size; ++j){
			/*Necesita punteros auxiliares*/
			double *pA, *pB;
			double sumaAuxiliar = 0.0;
			pA = a + (i*size);
			pB = b + j;
			for(k=0; k<size; ++k,pA++,pB+=size){
				sumaAuxiliar += (*pA * *pB);
			}
			Mr[i*size+j]= sumaAuxiliar;
		}	
	}
}

void matrixMM1f(int size, double *a, double *b, double *Mr){
	int i, j, k;
	for(i=0; i<size; ++i){
		for(j=0; j<size; ++j){
			/*Necesita punteros auxiliares*/
			double *pA, *pB;
			double sumaAuxiliar = 0.0;
			pA = a + (i*size);
			pB = b + (j*size);
			for(k=0; k<size; ++k,pA++,pB++){
				sumaAuxiliar += (*pA * *pB);
			}
			Mr[i*size+j]= sumaAuxiliar;
		}	
	}
}


/**** FUNCIONES PARA EL PROGRAMA DE PTHREADS ****/
/** 2- Función reserva de memoria para matrices de doble puntero*/
double ** ReservarMEM(int size){
	//Reservamos memoria de simensión NxN double contigua
	double * valor = (double *) malloc(size*size*sizeof(double));//malloc reserva de memoria

	//Reserva de un vector de 'punteros double' con simensión size
	double **ptr = (double **) malloc(size*size*sizeof(double*));
	
	//Iteración para que cada ountero posicione en la reserva Mem
	for(int i=0; i<size; ++i)
		ptr[i] = &valor[i*size];
		
	return ptr;	
	
}
//* 3- Función de inicialización de matrices
void IniciarMatriz(double **matA, double **matB, double **matC, int size){
	int i, j;
	for(i=0; i<size; ++i){
		for(j=0; j<size; ++j){
			
			matA[i][j] = 3.9 * (i-j);
			matB[i][j] = 2.0 * (j+i);
			matC[i][j] = 0.0;
		}
	}
}

//* 6- Se necesita función para impresión de las matrices (doble puntero)
void printMatriz(double **matriz, int size){
	int i, j;
	for(i=0; i<size; ++i){
		for(j=0; j<size; ++j){
			printf("%lf",matriz[i][j]);
		}
		printf("\n");
	}
	printf("\n---------\n");
}







