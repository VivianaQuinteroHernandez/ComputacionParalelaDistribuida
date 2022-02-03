/* Fecha: 01 de febrero de 2022
 * Nombre Ángela Viviana Quintero Hernández
 * ID: 1121945497
 * Correo: angela.quintero01@correo.usa.edu.co
 * Materia: Computación paralela y distribuida
 * Tema: Mini Bencjmark (Aplicación de juguete para medir rendimiento)
 */

/* Se declaran las interfaces */
#include <iostream>

/* Se define una constante */
#define size 32768

/*Se declara el espacio de dominio */
using namespace std;

/* Loop para determinar el tiempo de acceso de los datos */
int main(void) {
	int matrix[size][size];
	for(int i = 0; i<size; i++) {
		for(int j = 0; j<size; j++) {
			matrix[i][j] = 47;
 		}
	}
	return 0;
}
