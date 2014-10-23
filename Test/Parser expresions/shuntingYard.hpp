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

/*** Definiciones ***/

#define END_TABLEOP(x) ((x)->op==0 && (x)->prec==0 &&  \
                        (x)->assoc==0 && (x)->unary==0)


/*** Tabla de asociatividad de operadores ***/

enum {
        ASSOC_NONE=0,
        ASSOC_LEFT,     //Izquierda a derecha
        ASSOC_RIGHT     //Derecha a izquierda
    };

/*** Estructura para manejar los operadores ***/

typedef struct operation {
                            const char *op;      //Nombre o símbolo
                            int prec;       //Valor de precedencia
                            int assoc;      //Asociatividad
                            int unary;      //Es unario
                            float (*eval)(float a1, float a2); //Función
                        } t_operation;


/*** Funciones ***/

status_t shuntingYard(vector<string> &);
//t_operation* getOp(const string &);
bool isFunction(const string &str);

#endif
