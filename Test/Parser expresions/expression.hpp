#ifndef EXPRESSION_HPP_INCLUDED
#define EXPRESSION_HPP_INCLUDED

#include <iostream>
#include <string.h>
#include <vector>
#include <ctype.h>

#define LBUFF 50           // longitud del buffer de salida

using namespace std;

enum caracter {
                NONE, LETTER, NUMBER,MATH,UNKNOWN,SPACE
               };

void limpiar(char buff[],const int longBuff,size_t &pbuff);     // función auxiliar limpiar el buffer de salida
void mostrar(const vector<string> &);        // función auxiliar mostrar el buffer de salida
void guardar(vector<string> &,char buff[],const size_t &);        // guardar en un string la salida luego del Parser
void processBuffer(const char InBuff[],vector<string> &);

#endif
