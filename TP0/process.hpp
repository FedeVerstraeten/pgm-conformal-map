#ifndef PROCESS_HPP_INCLUDED
#define PROCESS_HPP_INCLUDED

#include <string>
#include <sstream>
#include"common.hpp"
#include "dictionary.hpp"

bool FunctionType(string);
bool getMagicNumber(istream& , string& );
bool createMatrix(size_t** &matrix,size_t row,size_t col);

#endif // PROCESS_HPP_INCLUDED
