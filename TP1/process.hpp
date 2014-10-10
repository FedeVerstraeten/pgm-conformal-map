#ifndef PROCESS_HPP_INCLUDED
#define PROCESS_HPP_INCLUDED

#include <iostream>
#include <string>
#include <sstream>
#include "common.hpp"
#include "dictionary.hpp"
#include "planoC.hpp"

bool FunctionType(string);
status_t getMagicNumber(istream& ,string& );
bool createMatrix(size_t** &matrix,size_t ,size_t );
void deleteMatrix(size_t** &matrix,size_t ,size_t );
void readLine(istream& , string& );
status_t readSize(istream&);
status_t readMaxIntensity(istream&,size_t&);
status_t readMatrixIN(istream& ,size_t** &matrix,const size_t& );
void matrixTransformation(size_t** &matrixIn,size_t** &matrixOut);

#endif // PROCESS_HPP_INCLUDED
