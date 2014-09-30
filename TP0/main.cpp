/*********************************************************************
Jueves 25 de Septiembre de 2014.
TP0 - Algoritmos II - Cátedra Calvo

Docentes TP:
			- Lucio Santi,
			- Leandro Santi.

Autores:
			- Federico Verstraeten <federico.verstraeten@gmail.com>
			- Jeremías Ignacio Zec <jeremiaszec@gmail.com>

Título:

NOTA:

**********************************************************************/


/********************************************
*				BIBLIOTECAS					*
*********************************************/

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <cstring>

#include "common.hpp"
#include "dictionary.hpp"
#include "cmdline.h"
#include "options.hpp"
#include "process.hpp"
#include "printers.hpp"
#include "complejo.hpp"
#include "planoC.hpp"

/********************************************
*			DECLARACIONES GLOBALES			*
*********************************************/

istream *iss = 0;
ostream *oss = 0;
fstream ifs, ofs;
string typeFunction;
size_t  altoImag=0, anchoImag=0;

double deltaX=0;
double deltaY=0;
double initX=0;
double initY=0;

extern option_t options[];
extern string function_dictionary[];


/********************************************
*					MAIN					*
*********************************************/

int main(int argc,char *argv[])
{
    //OPTIONS AND ARGUMENTS VALIDATION
	cmdline cmdl(options);
	cmdl.parse(argc, argv);

    //DECLARACIONES
    size_t **matrixIn = NULL;
    size_t **matrixOut = NULL;
	size_t maxInten;
	string str, sMagicNum;
	complejo z;
	complejo w; // w=f(z)

    // Se extrae caracteres desde iss y los coloca en str,
	// hasta encontrar '/n'.
	readLine(*iss,str);

    // Transformo el string en un stream. Me permite usar '>>' en lectura.
    istringstream issMagicNum(str);

    //MagicNumber
    if(getMagicNumber(issMagicNum,sMagicNum)==ERROR)
    {
        cerr << "Error: invalid "
			 << sMagicNum
			 << " Magic Number" << endl;
        return EXIT_PROGRAM;
    }

    //Lectura tamaños de matrices
    if(readSize(*iss)==ERROR) return EXIT_PROGRAM;

	deltaX = 2.0/anchoImag;
	deltaY = 2.0/altoImag;
	initX = deltaX/2.0-1;
	initY = deltaY/2.0-1;

    //Lectura máximo de intensidad
    if(readMaxIntensity(*iss,maxInten)==ERROR) return EXIT_PROGRAM;

    //Creo las matrices. Otorgo memoria.
    createMatrix(matrixIn,altoImag,anchoImag);
    createMatrix(matrixOut,altoImag,anchoImag);

    //Lectura de la matriz de entrada
    if(readMatrixIN(*iss,matrixIn,maxInten)==ERROR)
    {
        deleteMatrix(matrixIn,altoImag,anchoImag);
        deleteMatrix(matrixOut,altoImag,anchoImag);
        return EXIT_PROGRAM;
    }

	// Recorro matriz destino y se copia los tonos de la matriz de origen,
	// según la función w=f(z)
	for(size_t fil=0 ; fil < altoImag ; fil++)
	{
		for(size_t col=0 ; col < anchoImag ; col++)
		{
			// Recibo las coordenadas de la matriz destino,
			// z es el correspondiente valor del plano complejo 2x2.
			z = matrizAplanoC(col,fil);

			if(typeFunction=="exp(z)" || typeFunction=="EXP(Z)") w=exp(z);
			else if (typeFunction=="z" || typeFunction=="Z") w=id(z);

			if(w.re()<-1 || w.re()>1 || w.im()<-1 || w.im()>1)
				matrixOut[fil][col]=0;
			else
			{
				w = planoCaMatriz(w);
				matrixOut[fil][col]=matrixIn[(int)w.im()][(int)w.re()];
			}
		}
	}

    //Impresión de imagen por salida
    printImage(*oss,matrixOut,altoImag,anchoImag,maxInten);

    deleteMatrix(matrixIn,altoImag,anchoImag);
    deleteMatrix(matrixOut,altoImag,anchoImag);

    return EXIT_SUCCESS;
}
