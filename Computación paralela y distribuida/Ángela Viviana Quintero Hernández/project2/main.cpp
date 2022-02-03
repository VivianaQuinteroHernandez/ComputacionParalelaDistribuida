/* Fecha: 01 de febrero de 2022
 * Nombre Ángela Viviana Quintero Hernández
 * ID: 1121945497
 * Correo: angela.quintero01@correo.usa.edu.co
 * Materia: Computación paralela y distribuida
 * Tema: Presentación de tipo de datos disponibles C++
 */

/* Se declaran las interfaces */
#include <iostream>
#define SIZEBITES(x) sizeof(x)	*	8/*Definición lambda para calculo de bites*/
using namespace std;

int main() {
	cout	<<	"========================================================================================="	<<	endl;
	cout	<<	"|	Type		|	Meaning			|	Bytes	|	bites	|"	<<	endl;
	cout	<<	"========================================================================================="	<<	endl; /*formatear espacios en pantalla*/
	cout	<<	"|	bool		|	boolean			|	 "	<<	sizeof(bool)	<<"	|	  "	<<	SIZEBITES(bool)	<<	"	|	"	<<	endl; /*sizeof es una funcion que entrega el tamaño de un tipo de datos*/
	cout	<<	"|	char		|	Character		|	 "	<<	sizeof(char)	<<"	|	  "	<<	SIZEBITES(char)	<<	"	|	"	<<	endl;
	cout	<<	"|	wchar_t		|	Wide Character		|	 "	<<	sizeof(wchar_t)	<<"	|	 "	<<	SIZEBITES(wchar_t)	<<	"	|	"	<<	endl;
	cout	<<	"|	char16_t	|	Unicode Character	|	 "	<<	sizeof(char16_t)	<<"	|	 "	<<	SIZEBITES(char16_t)	<<	"	|	"	<<	endl;
	cout	<<	"|	char32_t	|	Unicode Character	|	 "	<<	sizeof(char32_t)	<<"	|	 "	<<	SIZEBITES(char32_t)	<<	"	|	"	<<	endl;
	cout	<<	"|	short		|	Short Integer		|	 "	<<	sizeof(short)	<<"	|	 "	<<	SIZEBITES(short)	<<	"	|	"	<<	endl;
	cout	<<	"|	int		|	Integer			|	 "	<<	sizeof(int)	<<"	|	 "	<<	SIZEBITES(int)	<<	"	|	"	<<	endl;
	cout	<<	"|	long		|	Long Integer		|	 "	<<	sizeof(long)	<<"	|	 "	<<	SIZEBITES(long)	<<	"	|	"	<<	endl;
	cout	<<	"|	long long	|	Long Long Integer	|	 "	<<	sizeof(long long)	<<"	|	 "	<<	SIZEBITES(long long)	<<	"	|	"	<<	endl;
	cout	<<	"|	float		|Simple Precision Floating point|	 "	<<	sizeof(float)	<<"	|	 "	<<	SIZEBITES(float)	<<	"	|	"	<<	endl;
	cout	<<	"|	double		|Double Precision Floating point|	 "	<<	sizeof(double)	<<"	|	 "	<<	SIZEBITES(double)	<<	"	|	"	<<	endl;
	cout	<<	"|	long double	|Extend Precision Floating point|	"	<<	sizeof(long double)	<<"	|	"	<<	SIZEBITES(long double)	<<	"	|	"	<<	endl;
	cout	<<	"========================================================================================="	<<	endl;

	return 0;
}
