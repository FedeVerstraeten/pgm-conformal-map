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

//size_t line=0;


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
	string str, str2;
	string sMagicNum;
	complejo z; 
	complejo w; // w=f(z)

    //size_t found=0;

    // Se extrae caracteres desde iss y los coloca en str,
	// hasta encontrar '/n'.
	readLine(*iss,str);

    // Transformo el string en un stream. Me permite usar '>>' en lectura.
    istringstream issMagicNum(str);

    //MagicNumber
    if(getMagicNumber(issMagicNum, sMagicNum)==false)
    {
        cerr << "error: missing "
			 << sMagicNum
			 << " Magic Number" << endl;
        return EXIT_PROGRAM;
    }

    //Lectura tamaños de matrices
    readLine(*iss,str);
    istringstream issSize(str);
    issSize>>anchoImag;	
    issSize>>altoImag;
	
	deltaX = 2.0/anchoImag;
	deltaY = 2.0/altoImag;
	initX = deltaX/2.0-1;
	initY = deltaY/2.0-1;

    //Creo las matrices. Otorgo memoria.
    createMatrix(matrixIn,altoImag,anchoImag);
    createMatrix(matrixOut,altoImag,anchoImag);

    //Lectura máximo de intensidad
    readLine(*iss,str);
    istringstream issMax(str);
    issMax>>maxInten;

    //Lectura de la matriz de entrada
    size_t i=0;
    size_t aux;
	
    while(getline(*iss,str))
    {
        istringstream iss_matrix(str);
        
        for(size_t j=0 ; j<anchoImag; ++j)
        {
            iss_matrix>>aux;
            if(aux>maxInten)
			{	
				cerr<<"Invalid value "<<matrixIn[i][j]
					<<"in position "
					<<"("<<i<<";"<<j<<")"
					<<endl;
				return EXIT_PROGRAM; 
			}
			else
            	matrixIn[i][j]=aux;
        }
        i++;
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


    return EXIT_SUCCESS;
}
