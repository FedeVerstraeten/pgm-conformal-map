#include "options.hpp"

using namespace std;

extern istream *iss;
extern ostream *oss;
extern fstream ifs;
extern fstream ofs;
extern string typeFunction;

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
		exit(EXIT_FAILURE);
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
		exit(EXIT_FAILURE);
	}
}

void opt_help(string const &arg)
{
	cout << "cmdline [-i stream_in] [-o stream_out] [-f function]"
         << endl;
	exit(EXIT_SUCCESS);
}

void opt_function(string const &arg)
{
    // Leer linea de comandos y guardar globalmente
    // la función se valida en el algoritmo shunting yard
	typeFunction=arg;
}
