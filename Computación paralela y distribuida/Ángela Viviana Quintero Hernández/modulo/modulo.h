#ifndef MODULO_C_H_INCLUDE
#define MODULO_C_H_INCLUDE
/* A continuación se crea una estructura de datos
 * para ser enviada como argumentos a la función de multiplicación 
 *de matrices, implementada con la biblioteca Posix*/

typedef struct arg_hilos{
	int idThread;
	int size;
	int nThread;
	double **a,**b,**c;
} structHilos;


/*Prototipo de funciones*/
void SampleStart();
void SampleEnd();
float randMM();
void initMatrix(int SZ, double *Ma, double *Mb, double *Mr);
void printMatrix(int SZ, double *M);
void MM1c(int size, double *a, double *b, double *Mr);
void MM1f(int size, double *a, double *b, double *Mr);

void MM1cOMP(int threads, int size, double *a, double *b, double *c);
void MM1fOMP(int threads, int size, double *a, double *b, double *c);

double ** ReservarMEM(int size);
void IniciarMatriz(double **matA, double **matB, double **matC, int size);
void printMatriz(double **matriz, int size);
void *multMM(void *arg);

#endif


