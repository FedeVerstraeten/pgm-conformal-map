/*********************************************************************
Jueves 23 de Octubre de 2014.
TP1 - Algoritmos II - Cátedra Calvo

Docentes TP:
			- Lucio Santi,
			- Leandro Santi.

Autores:
			- Federico Verstraeten <federico.verstraeten@gmail.com>
			- Jeremías Ignacio Zec <jeremiaszec@gmail.com>

Título: Programación C++ - Procesador de imágenes PGM

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

#include "binTree.hpp"
#include "cmdline.h"
#include "common.hpp"
#include "complejo.hpp"
#include "dictionary.hpp"
#include "expression.hpp"
#include "operation.hpp"
#include "options.hpp"
#include "planoC.hpp"
#include "printers.hpp"
#include "process.hpp"
#include "shuntingYard.hpp"

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


/**********************************************
*			    TABLA DE OPERACIONES 	    	*
***********************************************/
t_operation ops[]={

        //Operaciones
        {"^", 9, ASSOC_RIGHT,NOT_UNARY,OPERATOR, eval_pow},
        {"*", 8, ASSOC_LEFT, NOT_UNARY,OPERATOR, eval_mul},
        {"/", 8, ASSOC_LEFT, NOT_UNARY,OPERATOR, eval_div},
        {"+", 5, ASSOC_LEFT, BINARY_UNARY,OPERATOR, eval_add},
        {"-", 5, ASSOC_LEFT, BINARY_UNARY,OPERATOR, eval_sub},
        {"+_",10, ASSOC_LEFT, UNARY,OPERATOR, eval_unplus}, //suma unaria
        {"-_",10, ASSOC_LEFT, UNARY,OPERATOR, eval_unminus}, //negación unaria
        {",", 0, ASSOC_NONE, NOT_UNARY,SEPARATOR, NULL},
        {"(", 0, ASSOC_NONE, NOT_UNARY,PARENTESIS_OPEN, NULL},
        {")", 0, ASSOC_NONE, NOT_UNARY,PARENTESIS_CLOSE, NULL},
        //{"%", 8, ASSOC_LEFT, NOT_UNARY,OPERATOR, NULL},

        //variable independiente
        {"z",10, ASSOC_RIGHT,NOT_UNARY,VAR_INDEP,NULL},
        //unidad imaginaria
        {"j",10, ASSOC_NONE, NOT_UNARY,IMAGINARY_UNIT,NULL},

        //Funciones
        {"re",10,ASSOC_RIGHT,NOT_UNARY,FUNCTION,eval_re},
        {"im",10,ASSOC_RIGHT,NOT_UNARY,FUNCTION,eval_im},
        {"exp",10,ASSOC_RIGHT,NOT_UNARY,FUNCTION,eval_exp},
        {"id",10,ASSOC_RIGHT,NOT_UNARY,FUNCTION,eval_id},
        {"abs",10,ASSOC_RIGHT,NOT_UNARY,FUNCTION,eval_abs},
        {"sinh",10,ASSOC_RIGHT,NOT_UNARY,FUNCTION,eval_sinh},
        {"cosh",10,ASSOC_RIGHT,NOT_UNARY,FUNCTION,eval_cosh},
        {"sin",10,ASSOC_RIGHT,NOT_UNARY,FUNCTION,eval_sin},
        {"cos",10,ASSOC_RIGHT,NOT_UNARY,FUNCTION,eval_cos},
        {"arg",10,ASSOC_RIGHT,NOT_UNARY,FUNCTION,eval_arg},
        {0, },

};


/********************************************
*					MAIN					*
*********************************************/

int main(int argc,char *argv[])
{

    //DECLARACIONES
    size_t **matrixIn = NULL;
    size_t **matrixOut = NULL;
	size_t maxInten;
	string str, sMagicNum;
	complejo z;     // z variable independiente
	complejo w;     // w=f(z)
	vector<string> parser;
	binTree<string> *opTree=NULL;

	//VALIDACION DE OPCIONES Y ARGUMENTOS
	cmdline cmdl(options);
	cmdl.parse(argc, argv);

	//Se parsea la funcion ingresada con -f
    processBuffer(typeFunction.c_str(),parser);

    //Se transforma de notación infija a RPN
    if(shuntingYard(parser)==ERROR_INVALID_TOKEN)
    {
        cerr<<"invalid token"<<endl;
        return EXIT_PROGRAM;
    }

    // Se construye el árbol de operacione desde el parser en RPN.
    // Se retorna un puntero a la raíz del árbol
	opTree=constructionOpTree(parser);

    // Se extrae caracteres desde iss y los coloca en str,
	// hasta encontrar '/n'.
	readLine(*iss,str);

    // Transformo el string en un stream.
    // Me permite usar '>>' en lectura.
    istringstream issMagicNum(str);

    // MagicNumber
    if(getMagicNumber(issMagicNum,sMagicNum)==ERROR)
    {
        delete opTree;
        return EXIT_PROGRAM;
    }


    // Lectura tamaños de matrices
    if(readSize(*iss)==ERROR)
    {
        delete opTree;
        return EXIT_PROGRAM;
    }

	deltaX = 2.0/anchoImag;
	deltaY = 2.0/altoImag;
	initX = deltaX/2.0-1;
	initY = deltaY/2.0-1;

    //Lectura máximo de intensidad
    if(readMaxIntensity(*iss,maxInten)==ERROR)
    {
        delete opTree;
        return EXIT_PROGRAM;
    }

    //Creo las matrices. Otorgo memoria.
    createMatrix(matrixIn,altoImag,anchoImag);
    createMatrix(matrixOut,altoImag,anchoImag);

    //Lectura de la matriz de entrada
    if(readMatrixIN(*iss,matrixIn,maxInten)==ERROR)
    {
        // Si no se puede procesar la matriz de entrada
        // liberamos la memoria y cortamos el programa
        deleteMatrix(matrixIn,altoImag,anchoImag);
        deleteMatrix(matrixOut,altoImag,anchoImag);
        delete opTree;
        return EXIT_PROGRAM;
    }

	// Recorro matriz destino y se copia los tonos de
	// la matriz de origen, según la función w=f(z)
	matrixTransformation(matrixIn,matrixOut,*opTree);

    //Impresión de imagen por salida
    printImage(*oss,matrixOut,altoImag,anchoImag,maxInten);

    // Libero la memoria utilizada
    deleteMatrix(matrixIn,altoImag,anchoImag);
    deleteMatrix(matrixOut,altoImag,anchoImag);

    // Destruyo el árbol y libero toda la memoria utilizada
    delete opTree;

    return EXIT_SUCCESS;
}
