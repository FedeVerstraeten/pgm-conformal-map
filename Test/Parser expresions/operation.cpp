#include "operation.hpp"

extern t_operation ops[];
/******************************************************
getOp: recibe un token a procesar, si es una
operación matemática lo busca en la tabla de operaciones
y devuelve un puntero a la posición en la misma, si el
token no está en la tabla lo descarta y devuelve NULL.
*******************************************************/

t_operation* getOp(const string &str)
{
    t_operation *op=ops;

	for( ; !END_TABLEOP(op) ; ++op)
	{
         // Devuelve la posición en el vector de op
		if(string(op->op)==str) return op;
	}

	return NULL;
}

/******************************************************
                    EVALUADORES
*******************************************************/
float eval_uminus(float a1, float a2)
{
	return -a1;
}

float eval_exp(float a1, float a2)
{
	return a2<0 ? 0 : (a2==0?1:a1*eval_exp(a1, a2-1));
}

float eval_mul(float a1, float a2)
{
    return a1*a2;
}

float eval_div(float a1, float a2)
{
	if(!a2) {
		cerr<<"ERROR: Division by zero"<<endl;
		exit(EXIT_FAILURE);
	}
	return a1/a2;
}

float eval_mod(float a1, float a2)
{
    int a=a1,b=a2;
	if(!a2) {
		cerr<<"ERROR: Division by zero"<<endl;
		exit(EXIT_FAILURE);
	}
	return a%b;
}

float eval_add(float a1, float a2)
{
	return a1+a2;
}

float eval_sub(float a1, float a2)
{
	return a1-a2;
}

/******************************************************
evaluateOpTree: recibe el árbol de operaciones y el
valor de la variable 'var' que será el que corresponde
a la función "z" (variable independiente) dentro del
árbol de operaciones. En el caso que en el árbol se
encuentre "z", al procesar será intercambiado e inter-
pretado por el valor numérico que contiene 'var'.
*******************************************************/

float evaluateOpTree(const t_opTree& tree,const float &var)
{
    float result=0,num=0,lRes=0,rRes=0;
    //complejo resultado,numero, lRes, rRes;

    //Si el nodo es un número
    istringstream issNum(tree.data);
    if(issNum>>num)
        return num;

    //Si es una operación o función
    else if (tree.tleft && tree.tright)
    {
        t_operation *op=getOp(tree.data);
        //if(!op) exit(1);
        if(string(op->op)=="z") return var;

        lRes=evaluateOpTree(*(tree.tleft),var);
        rRes=evaluateOpTree(*(tree.tright),var);
        result=op->eval(lRes,rRes);
    }

    return result;
}

