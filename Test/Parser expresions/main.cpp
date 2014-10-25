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


using namespace std;

/*** Tabla de operadores ***/

t_operation ops[]={
        {"^", 9, ASSOC_RIGHT, 0,OPERATOR, eval_exp},
        {"*", 8, ASSOC_LEFT, 0,OPERATOR, eval_mul},
        {"/", 8, ASSOC_LEFT, 0,OPERATOR, eval_div},
        {"%", 8, ASSOC_LEFT, 0,OPERATOR, eval_mod},
        {"+", 5, ASSOC_LEFT, 1,OPERATOR, eval_add},
        {"-", 5, ASSOC_LEFT, 1,OPERATOR, eval_sub},
        {",", 0, ASSOC_NONE, 0,SEPARATOR, NULL},
        {"(", 0, ASSOC_NONE, 0,PARENTESIS_OPEN, NULL},
        {")", 0, ASSOC_NONE, 0,PARENTESIS_CLOSE, NULL},
        {"z",10, ASSOC_RIGHT,0,FUNCTION,NULL},
        {"j",10, ASSOC_NONE, 0,FUNCTION,NULL}, //considerar unidad imag como función
        {"exp",10,ASSOC_RIGHT,0,FUNCTION,NULL},
        {"sin",10,ASSOC_RIGHT,0,FUNCTION,NULL},
        {0, },

};


int main(int argc, char *argv[])
{
    vector<string> parser;
    t_opTree tree,ltree,rtree;
    float result,var;

    //Se parsea la entrada
    processBuffer(argv[1],parser);
    //mostrar(parser);

    //Se transforma de notación infija a RPN
    if(shuntingYard(parser)==ERROR_INVALID_TOKEN)
    {
        cerr<<"invalid token"<<endl;
        return EXIT_FAILURE;
    }


    //Armar arbol de binario de operaciones
    cout<<"RPN: "<<endl;
    for(size_t i=0; i<parserRPN.size() ; i++)
        cout<<parserRPN[i];
    cout<<endl;

    //Arbol de pruebas
    tree.data="+";
    ltree.data="2.34";
    rtree.data="z";
    var=50;

    tree.tleft=&ltree;
    tree.tright=&rtree;

    //Procesar el arbol
    result=evaluateOpTree(tree,var);
    cout<<"Resultado: "<<result<<endl;

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
    return EXIT_SUCCESS;
}
