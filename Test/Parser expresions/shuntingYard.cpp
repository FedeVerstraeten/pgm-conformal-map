#include "shuntingYard.hpp"

extern vector<string> parserRPN;
extern t_operation ops[];

/*** Implementación de funciones ***/

/******************************************************
isOperation: recibe un token a procesar, si es una
función,operación o paréntesis lo busca en la tabla de
operaciones y devuelve el tipo de operador que es.
*******************************************************/

t_typeop isOperation(const string &str)
{
    for(t_operation *op=ops ; !END_TABLEOP(op) ; ++op)
    {
        if(op->op == str)
        {
            if(op->func==FUNCTION) return FUNCTION;
            if(op->func==SEPARATOR) return SEPARATOR;
            if(op->func==PARENTESIS_OPEN) return PARENTESIS_OPEN;
            if(op->func==PARENTESIS_CLOSE) return PARENTESIS_CLOSE;

        }
    }
    return NONEOP;
}

/******************************************************
shuntingYard: Función que aplica el algoritmo del mismo
nombre. Recibe un vector a analizar (parsing) con una
expresión matemática separada en tokens en notación
infija y la transforma en Notación Polaca Inversa (RPN).
El resultado lo devuelve mediante un vector global,
denominado 'parserRPN'.
*******************************************************/
status_t shuntingYard (vector<string> &parser)
{
    //Se está usando un vector global "parserRPN"

    float num;
    bool f_opAnt=false; //El flag indicará si el token anterior es un operador
    stack<string> opStack;
    t_operation *op=NULL,*op_aux=NULL;

    // Se lee el vector hasta que haya tokens
    for(size_t i=0; i<parser.size() ; i++)
    {
        istringstream issparser(parser[i]);
        ostringstream ossparser;

        //Si el token es un número
        if(issparser>>num)
        {
            ossparser<<num;
            parserRPN.push_back(ossparser.str());
            f_opAnt=false;
        }

        else
        {
            //Valida el token con la tabla de operaciones
            op=getOp(parser[i]);
            if(op==NULL) return ERROR_INVALID_TOKEN;

            //Si es función lo coloco en la pila
            if(op->func==FUNCTION)
            {
                opStack.push(parser[i]);
                f_opAnt=false;
            }
            // Si es un separador desapilar hasta encontrar "("
            else if(op->func==SEPARATOR)
            {
                f_opAnt=false;
                while(!opStack.empty() && opStack.top()!="(")//<--mejorar
                {
                    parserRPN.push_back(opStack.top());
                    opStack.pop();
                }
                if(opStack.empty())
                    return ERROR_INVALID_TOKEN;
            }

            //Si el token es un operador matemático
            else if(op->func==OPERATOR)
            {
                //Si el operador es unario lo concatenamos
                //al siguiente token y luego lo procesamos
                if(f_opAnt && op->unary)
                    parser[i+1]=(op->op)+parser[i+1];

                else if(!opStack.empty())
                {
                    op_aux=getOp(opStack.top());

                    //Evaluamos la precedencia y la asociatividad del operador
                    //a insertar a la pila con los ya existentes, y desapilamos
                    //según lo evaluado.
                    while( opStack.top()!="(" && !opStack.empty() &&
                          ((op->assoc==ASSOC_LEFT && op->prec<=op_aux->prec) ||
                          (op->assoc==ASSOC_RIGHT && op->prec<op_aux->prec))
                          )
                      {
                        parserRPN.push_back(opStack.top());
                        opStack.pop();
                        if(opStack.empty()) break;
                        op_aux=getOp(opStack.top());
                      }

                    //Insertamos el nuevo operador a la pila
                    opStack.push(parser[i]);
                    f_opAnt=true;
                }
                else
                {
                    opStack.push(parser[i]);
                    f_opAnt=true;
                }
            }

            //Si el token es un parentesis abierto "("
            else if(op->func==PARENTESIS_OPEN)
            {
                f_opAnt=true;
                opStack.push(parser[i]);
            }

            //Si el token es un parentesis cerrado ")"
            else if(op->func==PARENTESIS_CLOSE)
            {
                f_opAnt=false;
                //Se vacía el stack hasta encontrar la pareja
                while(!opStack.empty() && opStack.top()!="(")
                {
                    parserRPN.push_back(opStack.top());
                    opStack.pop();
                }

                //Si no se encuntra
                if(opStack.empty())
                    return ERROR_INVALID_TOKEN;

                //Si lo encuentro lo desapilo
                else if(opStack.top()=="(") opStack.pop();

                //Si en el tope hay una función lo pongo en la cola
                if(!opStack.empty())
                {
                    op_aux=getOp(opStack.top());

                    if(op_aux->func==FUNCTION)
                    {
                        parserRPN.push_back(opStack.top());
                        opStack.pop();
                    }
                }
            }

            //Si el token no es ninguno de los permitidos
            else if(op->func==NONEOP)
                return ERROR_INVALID_TOKEN;
        }
    }

    //Si no hay tokens que leer pero hay operadores
    //en la pila, entonces se desapila y se pone en la cola.
    while(!opStack.empty() && opStack.top()!="(")
    {
        parserRPN.push_back(opStack.top());
        opStack.pop();
    }
    if(!opStack.empty() && opStack.top()=="(")
        return ERROR_INVALID_TOKEN;

	return OK;
}
