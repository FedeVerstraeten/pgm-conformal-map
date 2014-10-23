#include <iostream>
#include <string>
#include <vector>
#include "common.hpp"
#include "expression.hpp"
#include "shuntingYard.hpp"
#include "operation.hpp"

/*** Declaraciones globales  ***/

stack<t_operation*> opstack; // Pila contenedora de operaciones
stack<float> numstack; // Pila contenedora de valores numéricos

vector<string> parserRPN;


string function_dictionary[]={
                                "z", "Z", // equivalente al unico valor de variable reservado
                                "exp","EXP",
                                "sin","SIN",
                                "cos","COS"
                             };

//char InBuff[] = "1243+(exp(z)+265*exp(z))-3^5";  // Buffer de entrada

using namespace std;

/*** Tabla de operadores ***/

t_operation ops[]={
            {"_", 10, ASSOC_RIGHT, 1, eval_uminus},
            {"^", 9, ASSOC_RIGHT, 0, eval_exp},
            {"*", 8, ASSOC_LEFT, 0, eval_mul},
            {"/", 8, ASSOC_LEFT, 0, eval_div},
            {"%", 8, ASSOC_LEFT, 0, eval_mod},
            {"+", 5, ASSOC_LEFT, 0, eval_add},
            {"-", 5, ASSOC_LEFT, 0, eval_sub},
            {"(", 0, ASSOC_NONE, 0, NULL},
            {")", 0, ASSOC_NONE, 0, NULL},
            {"exp",10,ASSOC_RIGHT,0,NULL},
            {0, },

};


int main(int argc, char *argv[])
{
    vector<string> parser;

    processBuffer(argv[1],parser);
    //mostrar(parser);
    shuntingYard(parser);
    //validateParser(parser)
    //if(...=OK) coninue; else exit

    //Armar arbol de operaciones y procesar
    for(size_t i=0; i<parserRPN.size() ; i++)
        cout<<parserRPN[i]<<endl;

    /* Para procesar el arbol se contruirá uno de string.
       Modelo aproximado de procesamiento recursivo:
	complejo procesarArbol(const arbolString &arbol)
	{
            complejo resultado,numero, lRes, rRes;	    

	    if(leerArbol(arbol)==NUMERO)
            {
		numero=tranformarNumero(arbol->dato);
		return numero;
            }
	    else if(leerArbol(arbol)==OPERACION)
	    {
		t_operacion op=geOP(arbol->dato);
		lRes=procesarArbol(arbol->left);
		rRes=procesarArbol(arbol->right);
		resultado=op->eval(lres,rRes);
	    }
	    return rerultado;
	}
    */
    return 0;
}
