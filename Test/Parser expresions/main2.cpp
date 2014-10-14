#include <iostream>        // Un parser muy simple
#include <string.h>
#include <vector>

using namespace std;

char InBuff[] = "1243+(exp(z)+2exp(z))-3^2";  // Buffer de entrada

enum caracter {
                NONE, LETTER, NUMBER,MATH,
               };


#define LBUFF 50           // longitud del buffer de salida
char OutBuff[LBUFF];
caracter chact, chant;  // Caracter actual y anterior respectivamente
vector<string> parser;

int pbuff;
void limpiar();        // función auxiliar limpiar el buffer de salida
void mostrar();        // función auxiliar mostrar el buffer de salida
void guardar();

int main()
{
    int pos = 0;         // posición inicial
    limpiar();
    char c;
    do
    {
        c = InBuff[pos];
        if (c >= '0' && c<= '9')      chact = NUMBER;
        else if (c >= 'A' && c<= 'Z') chact = LETTER;
        else if (c >= 'a' && c<= 'z') chact = LETTER;
        else if (c=='+' || c=='-' || c=='*' || c=='/' || c=='^') chact = MATH;

    // cualquier otra condición de análisis
        else chact = UNKNOWN;

        // cambio de tipo
        if (chact != chant  || chact==UNKNOWN )
        {
          //mostrar();
          guardar();
          limpiar();
          chant = chact;
        }
        // mismo tipo
        else
        {
        // cualquier computación adicional
        }
        OutBuff[pbuff] = c;     // actualizar buffer de salida

        ++pbuff; ++pos;           // incrementar punteros
    } while (pos < strlen(InBuff));        // fin del análisis


    guardar();
    mostrar();

    return 0;
}

void limpiar() {      // limpiar buffer de salida
  for (int i=0; i<LBUFF; ++i) OutBuff[i] = '\0';
  pbuff =0;
  chant = NONE;
}
void mostrar()
{
  if (!parser.empty())
  {
      for(size_t i=0; i<parser.size(); i++)
        cout<<parser[i]<<endl;
  }
}

void guardar()
{
   if(pbuff!=0)parser.push_back(string(OutBuff));
}
