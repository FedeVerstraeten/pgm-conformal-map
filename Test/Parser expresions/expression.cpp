#include "expression.hpp"

// Global enum
caracter chact;     // Caracter actual
caracter chant;     // Caracter anaterior


void limpiar(char buff[],const int longBuff,size_t &pbuff)
{
  for (int i=0; i<longBuff; ++i) buff[i] = '\0';
  pbuff =0;
  chant = NONE;
}

void mostrar(const vector<string> &parser)
{
  if (!parser.empty())
  {
      for(size_t i=0; i<parser.size(); i++)
        cout<<parser[i]<<endl;
  }
}

void guardar(vector<string> &parser,const char buff[],const size_t &pbuff)
{
   if(pbuff!=0)parser.push_back(string(buff));
}

void processBuffer(const char InBuff[],vector<string> &parser)
{
    size_t pos=0,pbuff=0;   // posición inicial
    char c;
    char OutBuff[LBUFF];

    limpiar(OutBuff,LBUFF,pbuff);
    do
    {
        // Análisis del string de entrada.
        // Se forman tokens según sean números, letras u operaciones
        c = InBuff[pos];
        if (c >= '0' && c<= '9')       chact = NUMBER;
        else if (c >= 'A' && c<= 'Z') chact = LETTER;
        else if (c >= 'a' && c<= 'z') chact = LETTER;
        else if (c=='+' || c=='-' || c=='*' || c=='/' || c=='^') chact = MATH;

        // Cualquier otra condición de análisis,
        // por ejemplo los paréntisis u otro símbolo.
        else chact = UNKNOWN;

        // cambio de tipo
        if (chact != chant  || chact==UNKNOWN )
        {
          guardar(parser,OutBuff,pbuff);
          limpiar(OutBuff,LBUFF,pbuff);
          chant = chact;
        }
        // mismo tipo
        else
        {
        // cualquier computación adicional
        }

        // actualizar buffer de salida
        OutBuff[pbuff] = c;

        // incrementar punteros
        ++pbuff; ++pos;

    } while (pos < strlen(InBuff)); // fin del análisis

    // Guardo el último resultado
    guardar(parser,OutBuff,pbuff);
}
