#include "options.hpp"
#include <string>

using namespace std;

extern istream *iss;
extern ostream *oss;
extern fstream ifs;
extern fstream ofs;
extern string function_struct[];

void opt_input(string const &arg)
{

	if (arg == "-") {
		iss = &cin;
	} else {
		ifs.open(arg.c_str(), ios::in);
		iss = &ifs;
	}

	// Verificamos que el stream este OK.
	//
	if (!iss->good()) {
		cerr << "cannot open "
		     << arg
		     << "."
		     << endl;
		exit(1);
	}
}

void opt_output(string const &arg)
{
	if (arg == "-") {
		oss = &cout;
	} else {
		ofs.open(arg.c_str(), ios::out);
		oss = &ofs;
	}

	if (!oss->good()) {
		cerr << "cannot open "
		     << arg
		     << "."
		     << endl;
		exit(1);
	}
}

void opt_help(string const &arg)
{
	cout << "cmdline [-i stream_in] [-o stream_out]"
         << endl;
	exit(0);
}

void opt_function(string const &arg)
{
	//istringstream iss(arg);
    bool arg_ok;

	// Leemos de la linea de comandos el tipo de funcion utilizada
    arg_ok=false;
	for(int i=0 ; function_struct[i] ; i++)
	{
      if(arg == function_struct[i])
        {   /*Asignar funcion al objeto*/
            cout<<"Fuction enable: "<<arg<<endl;
            arg_ok=true;
        }
	}

	if(arg_ok==false)
    {
        cerr << "Forbidden Function "
             << arg
             << endl;
        exit(1);
	}
/*
	if (iss.bad()) {
		cerr << "cannot read function."
		     << endl;
		exit(1);
	}
*/
}
