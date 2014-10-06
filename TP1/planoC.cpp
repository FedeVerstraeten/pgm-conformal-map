#include "planoC.hpp"
extern double deltaX;
extern double deltaY;
extern double initX;
extern double initY;

/************************** matrizAplanoC *************************
 * matrizAplanoC: recive como argumento una coordenada de una matriz
 * retorna un complejo comprendido en el plano complejo 2x2 
 * correspondiente a dichas coordenadas.
 ******************************************************************/
complejo matrizAplanoC(int col, int fil)
{
	return complejo(initX+deltaX*col,initY+deltaY*fil);	
}

/**************************** planoCaMatriz ************************
 * planoCaMatriz: modifica el complejo que recive por referencia 
 * para que queden las coordenadas de la matriz correspondiente
 * En la parte real e imaginaria quedan asignadas las columnas y 
 * las filas respectivamente.
 ******************************************************************/
complejo planoCaMatriz(const complejo &z)
{
	complejo a((z.re()-initX)/deltaX,(z.im()-initY)/deltaY);
	a.redondeo();
	return a;
}

