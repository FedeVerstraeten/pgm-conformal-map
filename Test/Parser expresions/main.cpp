#include <iostream>
#include <string>
#include <vector>
#include "common.hpp"
#include "expression.hpp"
#include "shuntingYard.hpp"
#include "operation.hpp"
#include "binTree.hpp"
#include "complejo.hpp"

/*** Declaraciones globales  ***/

//stack<t_operation*> opstack; // Pila contenedora de operaciones
//stack<float> numstack; // Pila contenedora de valores numéricos

//vector<string> parserRPN;


using namespace std;

/*** Tabla de operadores ***/

t_operation ops[]={
        {"^", 9, ASSOC_RIGHT,NOT_UNARY,OPERATOR, eval_pow},
        {"*", 8, ASSOC_LEFT, NOT_UNARY,OPERATOR, eval_mul},
        {"/", 8, ASSOC_LEFT, NOT_UNARY,OPERATOR, eval_div},
        //{"%", 8, ASSOC_LEFT, NOT_UNARY,OPERATOR, NULL},
        {"+", 5, ASSOC_LEFT, BINARY_UNARY,OPERATOR, eval_add},
        {"-", 5, ASSOC_LEFT, BINARY_UNARY,OPERATOR, eval_sub},
        {"+_", 10, ASSOC_LEFT, UNARY,OPERATOR, eval_unplus}, //suma unaria
        {"-_", 10, ASSOC_LEFT, UNARY,OPERATOR, eval_unminus}, //negación unaria
        {",", 0, ASSOC_NONE, NOT_UNARY,SEPARATOR, NULL},
        {"(", 0, ASSOC_NONE, NOT_UNARY,PARENTESIS_OPEN, NULL},
        {")", 0, ASSOC_NONE, NOT_UNARY,PARENTESIS_CLOSE, NULL},
        {"z",10, ASSOC_RIGHT,NOT_UNARY,VAR_INDEP,NULL},  //variable independiente
        {"j",10, ASSOC_NONE, NOT_UNARY,IMAGINARY_UNIT,NULL},  //considerar unidad imag como función
        {"re",10,ASSOC_RIGHT,NOT_UNARY,FUNCTION,eval_re},
        {"im",10,ASSOC_RIGHT,NOT_UNARY,FUNCTION,eval_im},
        {"exp",10,ASSOC_RIGHT,NOT_UNARY,FUNCTION,eval_exp},
        {"id",10,ASSOC_RIGHT,NOT_UNARY,FUNCTION,eval_id},
        {"abs",10,ASSOC_RIGHT,NOT_UNARY,FUNCTION,eval_abs},
        {"sinh",10,ASSOC_RIGHT,NOT_UNARY,FUNCTION,eval_sinh},
        {"cosh",10,ASSOC_RIGHT,NOT_UNARY,FUNCTION,eval_cosh},
        {"sin",10,ASSOC_RIGHT,NOT_UNARY,FUNCTION,eval_sin},
        {"cos",10,ASSOC_RIGHT,NOT_UNARY,FUNCTION,eval_cos},
        {"arg",10,ASSOC_RIGHT,NOT_UNARY,FUNCTION,eval_arg},
        {0, },

};


int main(int argc, char *argv[])
{

    vector<string> parser;
	binTree<string> opTree;
    complejo result,var;

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
    for(size_t i=0; i<parser.size() ; i++)
        cout<<parser[i];
    cout<<endl;

	// Construyo el árbol de operaciones desde el
	// parser en RPN
	opTree=constructionOpTree(parser);
	opTree.printTree(cout);

    //Procesar el arbol
    result=evaluateOpTree(opTree,var);
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
