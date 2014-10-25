#ifndef OPERATION_HPP_INCLUDED
#define OPERATION_HPP_INCLUDED

#include "common.hpp"

#include <iostream>
#include <stdlib.h>
#include <string>
#include <sstream>

/*** Definiciones ***/

#define END_TABLEOP(x) ((x)->op==0 && (x)->prec==0 &&  \
                        (x)->assoc==0 && (x)->unary==0)


/*** Tabla de asociatividad de operadores ***/

typedef enum {
                 ASSOC_NONE=0,
                 ASSOC_LEFT,     //Izquierda a derecha
                 ASSOC_RIGHT     //Derecha a izquierda
               }t_assoc;

/*** Tabla de clasificador tipo de operadores ***/

typedef enum {
                 FUNCTION,      // Funciones
                 OPERATOR,      // Operadores matemáticos
                 SEPARATOR,     // Separadores: coma, punto y coma, etc.
                 PARENTESIS_OPEN,    // Abierto: Paréntesis, corchetes, llaves,etc.
                 PARENTESIS_CLOSE,   // Cerrado:  Paréntesis, corchetes, llaves,etc.
                 NONEOP           // Sin clasificación. Indicador de error.
               }t_typeop;

/*** Estructura para manejar los operadores ***/

typedef struct operation {
                            const char *op;  //Nombre o símbolo
                            int prec;        //Valor de precedencia
                            t_assoc assoc;    //Asociatividad
                            int unary;       //Es unario
                            t_typeop func;    //tipo de operador
                            float (*eval)(float a1, float a2); //Función
                        } t_operation;

/** Estructura auxiliar binOpTree **/
typedef struct opTree{
                        string  data;
                        struct opTree *tleft;
                        struct opTree *tright;
                        } t_opTree;


/*** Evaluadores ***/
float eval_uminus(float a1, float a2);
float eval_exp(float a1, float a2);
float eval_mul(float a1, float a2);
float eval_div(float a1, float a2);
float eval_mod(float a1, float a2);
float eval_add(float a1, float a2);
float eval_sub(float a1, float a2);

/*** Evaluador árbol de operaciones ***/
t_operation* getOp(const string &);
float evaluateOpTree(const t_opTree&,const float&);


#endif
