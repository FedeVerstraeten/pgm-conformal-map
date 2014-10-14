#include <iostream>
#include <string.h>
#include <vector>
#include "expression.hpp"

string function_dictionary[]={
                                "z", "Z", // equivalente al unico valor de variable reservado
                                "exp","EXP",
                                "sin","SIN",
                                "cos","COS"
                             };

char InBuff[] = "1243+(exp(z)+265*exp(z))-3^5";  // Buffer de entrada

using namespace std;

int main()
{
    vector<string> parser;
    processBuffer(InBuff,parser);
    mostrar(parser);

    //validateParser(parser)
    //if(...=OK) coninue; else exit

    //Shunting Yard: infix -->RPN

    //Armar arbol de operaciones y procesar

    return 0;
}
