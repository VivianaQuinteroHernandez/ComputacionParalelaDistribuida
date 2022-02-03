/*  * Fecha: 3 de febrero de 2022
	* Autora: Ángela Viviana Quintero Hernández
	* Materia: Computación paralela y distribuida
	* Tema: Construcción del primer Benchmark
	* Benchmark: Aplicación de juguete que permite evaluar rendimiento de un aspecto en específico de la computadora
*/
#include <iostream>
#include <vector>
#include <random>

using namespace std;

/* Función multiplicación matrices: Se requiere multiplicar las 2 matrices: adicionalmente los ingenieros deben verificar y validar que realmente se cumple el algoritmo de multiplicación*/
vector<vector<double>> multiMatriz(vector<vector<double>> Ma, vector<vector<double>> Mb){
	int i,j,k;
	vector<vector<double>> MResultado(Ma.size(),	vector<double>	(Ma.size(),0));
	for(i=0; i<Ma.size(); ++i)
		for(j=0; j<Ma.size(); ++j)
			for(k=0; k<Ma.size(); ++k)
				MResultado[i][j] += Ma[i][k]*Mb[k][j];
	
	return MResultado;

}

/* Funciín inicializada: Se requiere inicializar las matrices con números aleatorios*/
vector<vector<double>> inicializarMatriz(vector<vector<double>> M){
	int i,j;
	float limInf = 0.001, limSup = 9.999;
	vector<vector<double>> MInicializada(M.size(),	vector<double>	(M.size(),0));
	random_device rd; //se usa para inicializar la semilla
	mt19937 gen(rd());
	uniform_real_distribution<> dis(limInf, limSup);
	//cout	"Valor aletorio -->	"	<<	dis(gen)	<<	"\n\n\n\n"
	
	for(i=0; i<M.size(); ++i){	
		for(j=0; j<M.size(); ++j){
			MInicializada[i][j]	=	dis(gen);
		}
	}
	return MInicializada;
}

/* Se crea la función para imprimir matrices*/
void imprimirMatriz(vector<vector<double>> M){
	int i,j;
	for(i=0; i<M.size(); ++i){	
		for(j=0; j<M.size(); ++j){
			cout	<<	M[i][j]	<<"\t";
		}
		cout	<<	"\n";
	}
}


/*  Se requiere implementar una aplicación que multiplique dos matrices. El algoritmo a usar sera el clásico (filas por columnas). */
int main(int argc, char** argv) {
	int i,j,k;
	int	N	=	atoi(argv[1]); // Convertir la cadena de caracteres en número entero con la función atoi()"castear" argv es una variable de tipo caracter
	
	/* Se una la clase vector  para crear las matrices */
					//vector<int> vector01{1,2,3}; vector 1, 2, 3
					//vector<int> vector01(3,-10);matriz 3 veces el número -10
	vector<vector<double>> M1(N,	vector<double>	(N,0));
	vector<vector<double>> M2(N,	vector<double>	(N,0));
	vector<vector<double>> MR(N,	vector<double>	(N,0));
	
	M1 = inicializarMatriz(M1);
	M2 = inicializarMatriz(M2);
	
	/* Se imprime M1*/
	cout	<<	"Se imprime M1"	<<	"\n";
	imprimirMatriz(M1);
	cout	<<	"\n \n \n";
	
	/* Se imprime M2*/
	cout	<<	"Se imprime M2"	<<	"\n";
	imprimirMatriz(M2);
	cout	<<	"\n \n \n";
	
	/* Se hace la multiplicacción de las matrices*/
	MR = multiMatriz(M1,M2);
	
	/* Se imprime MR*/
	cout	<<	"Se imprime MR"	<<	"\n";
	imprimirMatriz(MR);
	
				//std::cout	<<	"Numero ingresado "	<<	N	<<"\n"; //std es una clase
				//cout	<<	"Numero ingresado "	<<	N	<<"\n";  //se usa si se pone arriba using..
	
	
	return 0;
}
