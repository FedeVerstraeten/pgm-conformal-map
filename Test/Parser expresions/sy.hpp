#ifndef SY_HPP_INCLUDED
#define SY_HPP_INCLUDED

#include <iostream>
#include <string>
#include <vector>
#include <stack>
#include <cctype>
#include <cstdlib>
#include "common.hpp"

/*** Definiciones ***/

#define MAXOPERATION 6


/*** Tabla de asociatividad de operadores ***/

enum {
        ASSOC_NONE=0,
        ASSOC_LEFT,     //Izquierda a derecha
        ASSOC_RIGHT     //Derecha a izquierda
    };

/*** Estructura para manejar los operadores ***/

typedef struct operation {
                            string op;      //Nombre o símbolo
                            int prec;       //Valor de precedencia
                            int assoc;      //Asociatividad
                            int unary;      //Es unario
                            float (*eval)(float a1, float a2); //Función
                        } t_operation;

/*** Evaluadores ***/
float eval_uminus(float a1, float a2);
float eval_mul(float a1, float a2);
float eval_add(float a1, float a2);
float eval_sub(float a1, float a2);



/*** Funciones ***/

t_operation* getOp(const string &);
status_t shuntingYard(vector<string> &);
status_t shunt_op(t_operation *op);





#endif
