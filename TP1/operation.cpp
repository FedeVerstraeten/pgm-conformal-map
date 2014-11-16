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

/** Operadores **/

complejo eval_unminus(complejo &a1, complejo &a2)
{
	return a2-a1;
}

complejo eval_unplus(complejo &a1, complejo &a2)
{
	return a2+a1;
}

complejo eval_add(complejo &a1, complejo &a2)
{
	return a1+a2;
}

complejo eval_sub(complejo &a1, complejo &a2)
{
	return a1-a2;
}

complejo eval_mul(complejo &a1, complejo &a2)
{
    return a1*a2;
}

complejo eval_div(complejo &a1, complejo &a2)
{
    return a1/a2;
}

complejo eval_pow(complejo &a1, complejo &a2)
{
    return a1^a2.re();
}

/** Funciones **/
complejo eval_re(complejo &a1,complejo &a2)
{
    return re(a1);
}

complejo eval_im(complejo &a1,complejo &a2)
{
    return im(a1);
}
complejo eval_exp(complejo &a1,complejo &a2)
{
    return exp(a1);
}
complejo eval_id(complejo &a1,complejo &a2)
{
    return id(a1);
}
complejo eval_abs(complejo &a1,complejo &a2)
{
    return abs(a1);
}
complejo eval_sinh(complejo &a1,complejo &a2)
{
    return sinh(a1);
}
complejo eval_cosh(complejo &a1,complejo &a2)
{
    return cosh(a1);
}
complejo eval_sin(complejo &a1,complejo &a2)
{
    return sin(a1);
}
complejo eval_cos(complejo &a1,complejo &a2)
{
    return cos(a1);
}
complejo eval_arg(complejo &a1,complejo &a2)
{
    return arg(a1);
}


/******************************************************
evaluateOpTree: recibe el árbol de operaciones y el
valor de la variable 'var' que será el que corresponde
a la función "z" (VARDEP: variable independiente) dentro
del árbol de operaciones. En el caso que en el árbol se
encuentre "z", al procesar será intercambiado e inter-
pretado por el valor numérico que contiene 'var'.
*******************************************************/

complejo evaluateOpTree(binTree<string>& tree,const complejo &var)
{
    //float result=0,num=0,lRes=0,rRes=0;
    double num;
    complejo result, lRes, rRes,zero(0,0);

    //Si el nodo es un número
    istringstream issNum(tree.getData());
    if(issNum>>num)
    {
        complejo numberC(num,0);
        return numberC;
    }

    //Si es una operación o función
    else
    {
        t_operation *op=getOp(tree.getData());
        if(!op) exit(1);

		// Si el token es la variable independiente "z"
        if(op->func==VAR_INDEP) return var;

        // Si el token es la unidad imaginaria "j"
        else if(op->func==IMAGINARY_UNIT)
        {
            complejo imag(0,1);
            return imag;
        }

		if (tree.hasLeftSon())
			lRes=evaluateOpTree(tree.getLeftSon(),var);

        if (tree.hasRightSon())
			rRes=evaluateOpTree(tree.getRightSon(),var);

		if(op->func==FUNCTION || op->unary==UNARY)
			result=op->eval(lRes,zero); // Tienen un solo hijo
		else
			result=op->eval(lRes,rRes);
    }

    return result;
}

/******************************************************
constructionOpTree: recibe un vector de string con los
tokens en Notación Polaca Inversa (RPN), lo procesa y
construye el árbol binario de operaciones matemáticas
(binary expressions tree), y devuelve una referencia al
nodo raíz del mismo.
*******************************************************/

binTree<string>& constructionOpTree(const vector<string>& parserRPN)
{
	 t_operation *op=NULL;
	 float num;
	 binTree<string> *node=NULL,*t1=NULL,*t2=NULL;
	 stack<binTree<string>*> opTreeStk;

	// Mientras hay tokens por leer
	for(size_t i=0 ; i<parserRPN.size() ; i++)
	{
		// Si el token es un número
		istringstream issparser(parserRPN[i]);

		if(issparser>>num)
        {
            node=new binTree<string>(parserRPN[i]);
            opTreeStk.push(node);

        }

		// Si el token es una operación o función
		else if((op=getOp(parserRPN[i]))!=NULL)
		{
			 node=new binTree<string>(string(op->op));

            // Si el token es una variable independiente o la
            // unidad imaginaria, apilarlo.
			 if(op->func==VAR_INDEP || op->func==IMAGINARY_UNIT)
            		opTreeStk.push(node);

            // Si el token es una función o un operador
			// unario, desapilo un nodo y se inserta el
			// nodo función u operador al stack luego.
			 else if (  op->func==FUNCTION ||
                        (op->func==OPERATOR && op->unary==UNARY)
                    )
			 {
                if(!opTreeStk.empty())
                {
                    t1=opTreeStk.top();
                    opTreeStk.pop();

                    // Insertar el nodo hijo al padre
                    node->insert(*t1);

                    // Colocar el nodo padre en la pila
                    opTreeStk.push(node);
                }
			    else
                {   //si hay errores en el parserRPN
                    cerr<<"ERROR: Function entered "
                        <<"without independent variable"
                        << "or numeric value ."<<endl;
                    exit(EXIT_FAILURE);
                }
			 }

			 // Si el token es una operación, desapilar dos
			 // nodos y los insertar al nodo padre operación
			 else if(op->func==OPERATOR)
			 {
			 	if(!opTreeStk.empty())
			 	{
			 	    t2=opTreeStk.top();
                    opTreeStk.pop();
			 	}
			 	if(!opTreeStk.empty())
			 	{
			 	    t1=opTreeStk.top();
                    opTreeStk.pop();
			 	}
                else
                {   //si hay errores en el parserRPN
                    cerr<<"ERROR: Operation entered incomplete,"
                        <<" missing terms."<<endl;
                    exit(EXIT_FAILURE);
                }

			 	// Insertar los nodos hijos al padre
			 	node->insert(*t1);
			 	node->insert(*t2);

			 	// Colocar el nodo padre en la pila
			 	opTreeStk.push(node);
			 }
		}
	}

	// Si no hay más tokens por leer
	node=opTreeStk.top();
	opTreeStk.pop();

	if(!opTreeStk.empty())
	{
	    cerr<<"ERROR: Expression entered incomplete."<<endl;
        exit(EXIT_FAILURE);
	}

	return (*node);

}

