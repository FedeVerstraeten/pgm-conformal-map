#include"dictionary.hpp"
#include"cmdline.h"
#include"options.hpp"

string fuction_struct[] = {
                            "z", "Z",
                            "exp(z)","EXP(Z)"
                          };

option_t options[] = {
	{1, "i", "input" , "-", opt_input, OPT_DEFAULT},
	{1, "o", "output", "-", opt_output, OPT_DEFAULT},
    {0, "h", "help"  , NULL, opt_help, OPT_DEFAULT},
	{1, "f", "function","z",opt_function,OPT_DEFAULT},// f(z)=z valor por defecto
	{0, },
};

 // No funciona correctamente si pongo NULL como opcion corta, lo mismo sucede con la opcion larga.
 // se invalidan las opciones cortas (o largas) siguientes en la tabla, eso sucede porque las funciones
 // do_short_opt y do_long_opt, usan como parametro de iteracion recorrer la tabla de opciones
 // hasta encontrar un valor 0 (cero) o NULL. Por esto mismo no es valido poner NULL como opcion corta
 // (o larga) en el caso de que no se considere necesario; es obligatorio poner ambar opciones, o como
 // alternativa dejar un caracter vacio " ".


