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


int main(int argc, char* argv[]){
	if(argc !=3){
		printf(".Exe N<dimMtriz> Nth<numHilos> \n\n");
		return -1;
	}
	double **Ma,**Mb,**Mc;
	N	 = atof(argv[1]);
	Nthreads = atof(argv[2]);

	// Se crea el pool de hilos
	pthread_t *hilosExec;
	//Se reserva memoria para los hilos
	hilosExec = (pthread_t *)malloc(Nthreads*sizeof(pthread_t));
	//Creación y reserva de Mem para cada Matriz
	Ma = ReservarMEM(N);
	Mb = ReservarMEM(N);
	Mc = ReservarMEM(N);
	//Se inicializa las matrices
	IniciarMatriz(Ma, Mb, Mc, N);
	if (N<4){
		printf("Matriz A: \n");
		printMatriz(Ma, N);
		printf("Matriz B: \n");
		printMatriz(Mb, N);
	}
	SampleStart();
	// Se reparte la tarea a cada hilo, al usar la función pthread_create
	for(int i=0; i<Nthreads; ++i){
		int *IDthread;
		IDthread = (int *)malloc(sizeof(int));
		*IDthread = i;	
		struct dataThread *dataThread_=(struct dataThread *)malloc(sizeof(struct dataThread));//los datos que reserva el hilo
		dataThread_->NThreads=Nthreads;
		dataThread_->N=N;
		dataThread_->Ma=Ma;
		dataThread_->Mb=Mb;
		dataThread_->Mr=Mc;
		dataThread_->idThread=*idThread;
		pthread_create(&hilosExec[i], NULL, multMM, (void *)IDthread);
	}
	//espero a que todos los hilos terminen
	for(int i=0; i<Nthreads; ++i){
		pthread_join(hilosExec[i], NULL);
	}
	SampleEnd();
	free(hilosExec);
	
	if(N<4){
		printf("Matriz C: \n");
		printMatriz(Mc, N);
	}
	
	
	
	return 0;
}


