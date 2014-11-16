#ifndef OPERATION_HPP_INCLUDED
#define OPERATION_HPP_INCLUDED

#include <stack>
#include <iostream>
#include <stdlib.h>
#include <string>
#include <sstream>
#include <vector>

#include "common.hpp"
#include "binTree.hpp"
#include "complejo.hpp"

/*** Definiciones ***/

#define END_TABLEOP(x) ((x)->op==0 && (x)->prec==0 &&  \
                        (x)->assoc==0 && (x)->unary==0 &&\
                        (x)->func==0)


/*** Tabla de asociatividad de operadores ***/

typedef enum {
                 ASSOC_NONE=0,
                 ASSOC_LEFT,     //Izquierda a derecha
                 ASSOC_RIGHT     //Derecha a izquierda
               }t_assoc;

/*** Tabla de clasificador tipo de operadores ***/

typedef enum {
                 NONEOP,           // Sin clasificación. Indicador de error
                 FUNCTION,          // Funciones
                 OPERATOR,          // Operadores matemáticos
                 SEPARATOR,         // Separadores: coma, punto y coma, etc.
                 PARENTESIS_OPEN,   // Abierto: Paréntesis, corchetes, llaves,etc.
                 PARENTESIS_CLOSE,  // Cerrado:  Paréntesis, corchetes, llaves,etc.
                 VAR_INDEP,         // Variable independiente
                 IMAGINARY_UNIT    // Unidad imaginaria "j" o "i"
               }t_typeop;

/*** Tabla de clasificador de operadores unarios***/
typedef enum {
                UNARY,         // Operador unario
                NOT_UNARY,     // Operador no unario
                BINARY_UNARY  // Operador binario y unario. Ej: menos (-X)
               }t_unaryop;

/*** Estructura para manejar los operadores ***/

typedef struct operation {
                            const char *op;  //Nombre o símbolo
                            int prec;        //Valor de precedencia
                            t_assoc assoc;    //Asociatividad
                            int unary;       //Es unario
                            t_typeop func;    //tipo de operador
                            complejo (*eval)(complejo &a1, complejo &a2); //Función
                        } t_operation;


/*** Evaluadores ***/
// Operadores
complejo eval_unminus(complejo &a1, complejo &a2);
complejo eval_unplus(complejo &a1, complejo &a2);
complejo eval_add(complejo &a1, complejo &a2);
complejo eval_sub(complejo &a1, complejo &a2);
complejo eval_mul(complejo &a1, complejo &a2);
complejo eval_div(complejo &a1, complejo &a2);
complejo eval_pow(complejo &a1, complejo &a2);

//Funciones
complejo eval_re(complejo &a1,complejo &a2);
complejo eval_im(complejo &a1,complejo &a2);
complejo eval_exp(complejo &a1,complejo &a2);
complejo eval_id(complejo &a1,complejo &a2);
complejo eval_abs(complejo &a1,complejo &a2);
complejo eval_sinh(complejo &a1,complejo &a2);
complejo eval_cosh(complejo &a1,complejo &a2);
complejo eval_sin(complejo &a1,complejo &a2);
complejo eval_cos(complejo &a1,complejo &a2);
complejo eval_arg(complejo &a1,complejo &a2);

/*** Evaluador árbol de operaciones ***/
t_operation* getOp(const string &);
complejo evaluateOpTree(binTree<string>&,const complejo&);
binTree<string>& constructionOpTree(const vector<string>&);


#endif
