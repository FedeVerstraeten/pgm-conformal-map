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

istream *iss = 0;
ostream *oss = 0;
fstream ifs, ofs;

extern option_t options[];
extern string fuction_struct[];

//size_t line=0;


/***************MAIN**********************/

int main(int argc,char *argv[])
{
    //OPTIONS AND ARGUMENTS VALIDATION
	cmdline cmdl(options);
	cmdl.parse(argc, argv);

	string str, str2, aux;
	string sMagicNum;

    getline(*iss,str); // Extrae caracteres desde iss y los coloca en str, hasta encontrar '/n'.
    istringstream issMagicNum(str); // Transformo el string en un stream. Me permite usar '>>' en lectura.

    //MagicNumber
    if(getMagicNumber(issMagicNum, sMagicNum)==false)
    {
        cerr << "error: missing P2 Magic Number" << endl;
        return EXIT_PROGRAM;
    }



    //while( getline(*iss_net,str) )
/***************PRINTS**********************/
/*
    *oss_net << "NetworkName "<<NetName << endl;
    rootElement.PrintElements();
    rootElement.Printconnection();
*/



   // while( getline(*iss_faults,str2) )


    return EXIT_SUCCESS;
}
