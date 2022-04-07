/* 	* Universidad Sergio Arboleda
	* Fecha: 089 de febrero de 2022
	* Autora: Ángela Viviana Quintero Hernández
	* Materia: Parallel Computing
	* Tema: Implementación Posix (Library)
	* Programa: Principal pata multiplicar 2 matrices con variables globales
	* Se requiere que el diseño sea modular 
	* El modulo implementará las funciones para el cálculo del producto de la matrix
	* 1- Creación de variables doble puntero para matrices principal GLOBAL
	* 2- Función reserva de memoria para matrices de doble puntero
	* 3- Función de inicialización de matrices
	* 4- Función para el producto de matrices
	* Se divide la matriz A por porciones, a ser enviadas a cada hilo.
	*--> El número de hilos será enviada a ejecutar
	*--> La dimensión de la matriz será enviada a ejecutar
	* 5- La dimensiónde la matriz siempre será cuadrada (NxN)
	* 6- Se necesita función para impresión de las matrices (doble puntero)
	*************************************************************************
*/
#include "modulo.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <pthread.h>
#include <sys/time.h>
#include <omp.h>

int main(int argc, char* argv[]){
	double **Ma,**Mb,**Mc;
	if(argc !=3){
		printf(".Exe N<dimMtriz> Nth<numHilos> \n\n");
		return -1;
	}
	
	int N	 = atof(argv[1]); //dimesión de la matriz NxN
	int Nthreads = atof(argv[2]);
	//Se valida que el número de hilos ingresado sea menor o igual al número de cores detectados por el sistema operativo
	if(Nthreads > omp_get_max_threads()){
		printf("El número de hilos debe ser <= %d",omp_get_max_threads());
		return -1;
	}
	// Se crea el pool de hilos
	pthread_t *hilosExec;
	//Se reserva memoria para los hilos
	hilosExec = (pthread_t *)malloc(Nthreads*sizeof(pthread_t));
	
	//se crea un vector de arguento para ser pasados a los hilos
	structHilos argThreads[Nthreads];
	
	//Creación y reserva de Mem para cada Matriz
	Ma = ReservarMEM(N);
	Mb = ReservarMEM(N);
	Mc = ReservarMEM(N);
	//Se inicializa las matrices
	IniciarMatriz(Ma, Mb, Mc, N);
	
	
	printMatriz(Ma, N);
	printMatriz(Mb, N);
	
	
	SampleStart();
	// Se reparte la tarea a cada hilo, al usar la función pthread_create
	for(int i=0; i<Nthreads; ++i){
		argThreads[i].idThread = i;
		argThreads[i].size = N;
		argThreads[i].nThread = Nthreads;
		argThreads[i].a = Ma;
		argThreads[i].b = Mb;
		argThreads[i].c = Mc;
		//pthread_create(&hilosExec[i], NULL, multMM, (void *)argThreads[i].idThread);
		pthread_create(&hilosExec[i], NULL, multMM, &argThreads[i]);
	}
	//espero a que todos los hilos terminen
	for(int i=0; i<Nthreads; ++i){
		pthread_join(hilosExec[i], NULL);
	}
	SampleEnd();
	
	
	free(hilosExec);
	
	
	printMatriz(Mc, N);
	
	return EXIT_SUCCESS;
}


