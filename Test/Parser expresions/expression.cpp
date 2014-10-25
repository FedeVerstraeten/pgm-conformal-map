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

void guardar(vector<string> &parser,char buff[],const size_t &pbuff)
{
    char c;
    size_t i=0;

    if(pbuff!=0)
    {
       //transformo mayúsculas a minúsculas
        while (buff[i])
        {
            c=buff[i];
            buff[i]=tolower(c);
            i++;
        }

       //guardo el token en el vector
       parser.push_back(string(buff));
    }
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
        // Se utilizan las funciones isdigit y isalpha de la biblioteca
        // ctype.h que corroboran si son números o letras la entrada.
        c = InBuff[pos];

        // Si el caracter es numérico. Se considera el punto decimal para los float
        if (isdigit(c) || c=='.')   chact = NUMBER;

        // Si es una palabra
        else if (isalpha(c)) chact = LETTER;

        // Si es una operación matemática
        else if (c=='+' || c=='-' || c=='*' || c=='/' || c=='^') chact = MATH;

        // Si es un espacio en blanco, lo eliminamos
        else if (c==' ') chact = SPACE;

        // Cualquier otra condición de análisis,
        // por ejemplo los paréntisis u otro símbolo.
        else chact = UNKNOWN;

        //-----------------------------------------------------------
        // CAMBIO DE TIPO: guardo el token hasta donde se ha leído
        // Si es un espacio (SPACE) salteo el cambio de tipo
        if (chact != chant  || chact==UNKNOWN || chact==MATH )
        {
          guardar(parser,OutBuff,pbuff);
          limpiar(OutBuff,LBUFF,pbuff);// limpia el buffer, inicializa pbuff
          chant = chact;
        }
        // mismo tipo
        else
        {
        // cualquier computación adicional
        }

        // actualizar buffer de salida
        if(chact != SPACE)
        {
            OutBuff[pbuff] = c;
            ++pbuff;
        }

        // incrementar iterador a buffer in
         ++pos;

    } while (pos < strlen(InBuff)); // fin del análisis

    // Guardo el último resultado
    guardar(parser,OutBuff,pbuff);
}
