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

istream *iss = 0;
ostream *oss = 0;
fstream ifs, ofs;

extern option_t options[];
extern string function_struct[];

//size_t line=0;


/***************MAIN**********************/

int main(int argc,char *argv[])
{
    //OPTIONS AND ARGUMENTS VALIDATION
	cmdline cmdl(options);
	cmdl.parse(argc, argv);

    //DECLARACIONES
    size_t **imagIn = NULL;
    size_t **imagOut = NULL;
	size_t  row=0, col=0, maxInten;
	string str, str2, aux;
	string sMagicNum;
    //size_t found=0;

    // Se extrae caracteres desde iss y los coloca en str, hasta encontrar '/n'.
    getline(*iss,str);

    // Transformo el string en un stream. Me permite usar '>>' en lectura.
    istringstream issMagicNum(str);

    //MagicNumber
    if(getMagicNumber(issMagicNum, sMagicNum)==false)
    {
        cerr << "error: missing P2 Magic Number" << endl;
        return EXIT_PROGRAM;
    }

    //Lectura tamaños de matrices
    getline(*iss,str);
    istringstream issSize(str);
    issSize>>col;
    issSize>>row;

    //Creo las matrices. Otorgo memoria.
    createMatrix(imagIn,imagOut,row,col);

    //Lectura máximo de intensidad
    getline(*iss,str);
    istringstream issMax(str);
    issMax>>maxInten;

    //Lectura de la matriz de entrada
    int i=0;
    while(getline(*iss,str))
    {
        istringstream iss_matrix(str);
        size_t aux;
        for(size_t j=0 ; j<col; ++j)
        {
            iss_matrix>>aux;
            imagIn[i][j]=aux;
        }
        i++;
    }

    //Impresión de imagen por salida
    // ATENCION: Figura imagIn porque se hicieron pruebas, aun no se posee cargada imagOut
    printImage(*oss,imagIn,row,col,maxInten);


    return EXIT_SUCCESS;
}
