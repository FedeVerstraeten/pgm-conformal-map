#include "sy.hpp"

extern stack<t_operation*> opstack;
extern stack<float> numstack;
extern t_operation ops[];

/*** Implementación de funciones ***/

/******************************************************
getOp: recibe un token a procesar, si el mismo es un
valor numérico lo descarta y devuelve NULL, si es una
operación matemática lo busca en la tabla de operaciones
y devuelve un puntero a la posición en la misma.
*******************************************************/

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

/******************************************************
shuntingYard: recibe un vector de string con los tokens
a procesar mediante el algoritmo del mismo nombre. El
vector posee la cadena previamente parseada.
*******************************************************/
status_t shuntingYard (vector<string> &parser)
{
    t_operation *op=NULL; // Apuntará al elemento de la tabla de operadores
    string *num;
    t_operation startop={"X", 0, ASSOC_NONE, 0, NULL}; // Operador para marcar el incio
    t_operation *lastop=&startop;
    float n1, n2;

    for(size_t i=0; i<parser.size() ; i++)
    {

        if(!num)
        {
            // Si el token es una operación
            if((op=getOp(parser[i]))!=NULL)
            {
                // Si la operación anterior no es por default
                // o no es un paréntesis cerrado
                // Valido: "..+ -14 * 3.." ó "..) + 32 -..."
                // Inválido: " + +8 -4" u otro caso de repetición de operaciones

                if(lastop && (lastop==&startop || lastop->op!=")"))
                {
                    //Para el operador menos (-) unario.
                    if(op->op=="-") op=getOp("_");

                    //Un operador binario no puede aparecer después de
                    //otro operador o un paréntesis izquierdo.
                    else if(op->op!="(")
                    {
                        cerr<<"ERROR: Illegal use of binary operator "<<op->op<<endl;
                        return ERROR;
                    }
                }
               if(shunt_op(op)!=OK) return ERROR;
               lastop=op;
            }

            // Si el token es un valor numérico
            else if(isdigit(parser[i].c_str()[0])) num=&parser[i];

            // En otro caso, si ni siquiera es un espacio en blanco
            else if(!isspace(parser[i].c_str()[0]))
            {
                cerr<<"ERROR: Syntax error"<<endl;
                return ERROR;
            }
        }

        else
        {
			if(isspace(parser[i].c_str()[0]))
			{
			    numstack.push(atof(num->c_str()));
				num=NULL;
				lastop=NULL;
			}
			else if((op=getOp(parser[i])))
			{
                numstack.push(atof(num->c_str()));
				num=NULL;
                if(shunt_op(op)!=OK) return ERROR;
				lastop=op;
			}
			else if(!isdigit(parser[i].c_str()[0]))
			{
                cerr<<"ERROR: Syntax error"<<endl;
				return ERROR;
			}
		}
    }
    //Inserto el último número al stack
    if(num) numstack.push(atof(num->c_str()));

/**************************************
	while(!opstack.empty())
	{
		op=opstack.top();
		opstack.pop();
		n1=numstack.top();
		numstack.pop();
		if(op->unary) numstack.push(op->eval(n1, 0));
		else
		{
			n2=numstack.top();
            numstack.pop();
			numstack.push(op->eval(n2, n1));
		}
	}*/
	/*
	if(nnumstack!=1) {
		fprintf(stderr, "ERROR: Number stack has %d elements after evaluation. Should be 1.\n", nnumstack);
		return EXIT_FAILURE;
	}*/
    cout<<numstack.top()<<endl;

	return OK;
}

/******************************************************
shunt_op: función auxiliar para operaciones
*******************************************************/

status_t shunt_op(t_operation *op)
{
	t_operation *pop=NULL;
	float n1, n2;

	if(op->op=="(")
    {
        opstack.push(op);
		return OK;
	}
	else if(op->op==")")
	{
		while(!opstack.empty() && (opstack.top())->op!="(")
        {
			pop=opstack.top();
			opstack.pop();
			n1=numstack.top();
			numstack.pop();

			if(pop->unary) numstack.push(pop->eval(n1, 0));
			else
			{
				n2=numstack.top();
				numstack.pop();
				numstack.push(pop->eval(n2, n1));
			}
		}
		if(opstack.empty() || (opstack.top())->op!="(")
        {
            cerr<<"ERROR: Stack error. No matching '('"<<endl;
			return ERROR;
		}
		return OK;
	}

	if(op->assoc==ASSOC_RIGHT)
	{
		while(!opstack.empty() && (op->prec) < (opstack.top())->prec)
		{
			pop=opstack.top();
			opstack.pop();
			n1=numstack.top();
			numstack.pop();
			if(pop->unary) numstack.push(pop->eval(n1, 0));
			else
			{
				n2=numstack.top();
				numstack.pop();
				numstack.push(pop->eval(n2, n1));
			}
		}
	}
	else
	{
		while(!opstack.empty() && (op->prec) <= (opstack.top())->prec)
		{
			pop=opstack.top();
			opstack.pop();
			n1=numstack.top();
			numstack.pop();
			if(pop->unary) numstack.push(pop->eval(n1, 0));
			else
			{
				n2=numstack.top();
				numstack.pop();
				numstack.push(pop->eval(n2, n1));
			}
		}
	}
	opstack.push(op);
	return OK;
}

/******************************************************
funciones eval:
*******************************************************/
float eval_uminus(float a1, float a2)
{
	return -a1;
}

float eval_mul(float a1, float a2)
{
	return a1*a2;
}

float eval_add(float a1, float a2)
{
	return a1+a2;
}
float eval_sub(float a1, float a2)
{
	return a1-a2;
}

