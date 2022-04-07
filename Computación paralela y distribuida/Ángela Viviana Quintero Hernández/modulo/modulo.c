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





/* Se crea la funcion para inicializar las matrices*/
void initMatrix(int SZ, double *Ma, double *Mb, double *Mr){
	int i, j;
	for(i=0; i<SZ; ++i){
		for(j=0; j<SZ; ++j){
			Ma[j+i*SZ]= 3.2*(i+j);
			Mb[j+i*SZ]= 2.4*(j-i);
			Mr[j+i*SZ]= 0.0;
		}
	}
}

/* Se implementa la impresión para efectos de validación*/
void printMatrix(int SZ, double *M){
	int i, j;
	if(SZ<5){
		for(i=0; i<SZ; ++i){
			for(j=0; j<SZ; ++j){
				printf("%f   ",M[j+i*SZ]);
				
			}
			printf("\n");
		}
	}
}

void MM1c(int size, double *a, double *b, double *Mr){
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
/**
 * @brief Function that makes the matrix multiplication between two matrixes and the result is saved in another matrix. This uses Open MP
 */
void MM1cOMP(int threads, int size, double *a, double *b, double *c)
{
	omp_set_num_threads(threads);
#pragma omp parallel
	{
		int i, j, k;
#pragma omp for
		for (i = 0; i < size; ++i)
		{
			for (j = 0; j < size; ++j)
			{
				/*Necesita puteros auxiliares*/
				double *pA, *pB;
				double auxiliarSum = 0.0;
				pA = a + (i * size);
				pB = b + j;
				for (k = 0; k < size; ++k, pA++, pB += size)
				{
					auxiliarSum += (*pA * *pB);
				}
				c[i * size + j] = auxiliarSum;
			}
		}
	}
}

void MM1f(int size, double *a, double *b, double *Mr){
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

/**
 * @brief Function that makes the matrix multiplication between two matrixes and the result is saved in another matrix. This uses Open MP
 */
void MM1fOMP(int threads, int size, double *a, double *b, double *c)
{
	omp_set_num_threads(threads);
#pragma omp parallel
	{
		int i, j, k;
#pragma omp for
		
		for (i = 0; i < size; ++i)
		{
			for (j = 0; j < size; ++j)
			{
				/*Necesita puteros auxiliares*/
				double *pA, *pB;
				double sumaAuxiliar = 0.0;
				pA = a + (i * size);
				pB = b + (j * size);
				for (k = 0; k < size; ++k, pA++, pB++)
				{
					sumaAuxiliar += (*pA * *pB);
				}
				c[i * size + j] = sumaAuxiliar;
			}
		}
	}
}


/* Funcion a ser enviada a cada hilo, que realiza la multiplicación de matrices. La Matriz A,
 * se divide por porciones, en función de la dimensión y del número de hilos que requiere el usuario.
 * Nota la función setrá del tipo voidla cual retomará
 un warning potencial de riesgo. Pensar en eso, para mejorarla*/
void *multMM(void *argThreads){
	//arg: tiene el ID del hilo
	int i,j,k;
	int porcionSize, iniFila, finFila;
	double suma;
	int idTH = ((structHilos*)argThreads) -> idThread;
	int sizeTH = ((structHilos*)argThreads) -> size;
	int nThreadTH = ((structHilos*)argThreads) -> nThread;
	double **MA = ((structHilos*) argThreads) -> a;
	double **MB = ((structHilos*) argThreads) -> b;
	double **MC = ((structHilos*) argThreads) -> c;

	// Se determina la porción a ser enviada a cada hilo
	porcionSize = sizeTH/nThreadTH;
	//Se pasa el inicio de la fila, según el id del hilo
	iniFila = idTH*porcionSize;
	//Se pasa el fin de la fila, según el id del hilo
	finFila = (idTH+1)*porcionSize;
	
	for(i = iniFila; i < finFila; ++i){
		for(j = 0; j < sizeTH; ++j){
			suma = 0.0;
			for(k=0; k < sizeTH; ++k){
				suma += MA[i][k] * MB[k][j];
			}
			MC[i][j] = suma;
		}
	}
	pthread_exit(NULL);
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
			
			matA[i][j] = 3.2 * (i+j);
			matB[i][j] = 2.4 * (j-i);
			matC[i][j] = 0.0;
		}
	}
}

//* 6- Se necesita función para impresión de las matrices (doble puntero)
void printMatriz(double **matriz, int size){
	if(size < 5){
		int i, j;
		for(i=0; i<size; ++i){
			for(j=0; j<size; ++j){
				printf(" %f ",matriz[i][j]);
			}
			printf("\n");
		}
		printf("\n---------\n");
	}
}






