#include "shuntingYard.hpp"

extern vector<string> parserRPN;
extern t_operation ops[];

/*** Implementación de funciones ***/

/******************************************************
getOp: recibe un token a procesar, si el mismo es un
valor numérico lo descarta y devuelve NULL, si es una
operación matemática lo busca en la tabla de operaciones
y devuelve un puntero a la posición en la misma.
*******************************************************/
/*
t_operation* getOp(const string &str)
{
	int i;
	for(i=0; i<MAXOPERATION; ++i)
	{
         // Devuelve la posición en el vector de op
		if(ops[i].op==str) return ops+i;
	}
	return NULL;
}
*/
/******************************************************
isFunction: recibe un token a procesar, si es una
función lo busca en la tabla de operaciones
y devuelve verdadero, sino falso.
*******************************************************/

bool isFunction(const string &str)
{
    for(t_operation *op=ops ; !END_TABLEOP(op) ; ++op)
    {
        if(op->op == str) return true;
    }
    return false;
}

/******************************************************
shuntingYard:
*******************************************************/
status_t shuntingYard (vector<string> &parser)
{
    //t_operation *op=NULL; // Apuntará al elemento de la tabla de operadores
   // string *num;
    //t_operation startop={"X", 0, ASSOC_NONE, 0, NULL}; // Operador para marcar el incio
    //t_operation *lastop=&startop;
    float num;
    stack<string> aux;

    // Leo el vector hasta que haya tokens
    for(size_t i=0; i<parser.size() ; i++)
    {
        istringstream issparser(parser[i]);

        //Si el token es un número
        if(issparser>>num) parserRPN.push_back(parser[i]);

        else
        {
            if(isFunction(parser[i])) cout<<"Function "<<parser[i]<<endl;
        }
    }

	return OK;
}
