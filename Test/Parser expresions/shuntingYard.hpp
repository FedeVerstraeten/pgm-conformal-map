#ifndef SHUNTINGYARD_HPP_INCLUDED
#define SHUNTINGYARD_HPP_INCLUDED

#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <stack>
#include <cctype>
#include <cstdlib>
#include "common.hpp"
#include "operation.hpp"


/*** Funciones ***/

status_t shuntingYard(vector<string> &);
t_typeop isOperation(const string &str);


#endif
