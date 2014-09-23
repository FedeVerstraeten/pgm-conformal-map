#include <iostream>
#include "complejo.hpp"
#include <stdlib.h>

using namespace std;

#define LONG_X 	20
#define LONG_Y 	20
#define FN1	1
#define FN2	2

void emitirMatriz(unsigned char m[][LONG_X]);

//recordar que el formato de C y C++ es [FILAS]x[COLUMNAS] equivalente a decir [coordenada Y] x [coordenada X]
unsigned char matrizOrigen[LONG_Y][LONG_X]=
{
	{'9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9'},
	{'9','5','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','9'},
	{'9','0','5','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','9'},
	{'9','0','0','5','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','9'},
	{'9','0','0','0','5','0','0','0','0','0','0','0','0','0','0','0','0','0','0','9'},
	{'9','0','0','0','0','5','0','0','0','0','0','0','0','0','0','0','0','0','0','9'},
	{'9','0','0','0','0','0','5','0','0','0','0','0','0','0','0','0','0','0','0','9'},
	{'9','0','0','0','0','0','0','5','0','0','0','0','0','0','0','0','0','0','0','9'},
	{'9','0','0','0','0','0','0','0','5','0','0','0','0','0','0','0','0','0','0','9'},
	{'9','0','0','0','0','0','0','0','0','5','0','0','0','0','0','0','0','0','0','9'},
	{'9','0','0','0','0','0','0','0','0','0','5','0','0','0','0','0','0','0','0','9'},
	{'9','0','0','0','0','0','0','0','0','0','0','5','0','0','0','0','0','0','0','9'},
	{'9','0','0','0','0','0','0','0','0','0','0','0','5','0','0','0','0','0','0','9'},
	{'9','0','0','0','0','0','0','0','0','0','0','0','0','5','0','0','0','0','0','9'},
	{'9','0','0','0','0','0','0','0','0','0','0','0','0','0','5','0','0','0','0','9'},
	{'9','0','0','0','0','0','0','0','0','0','0','0','0','0','0','5','0','0','0','9'},
	{'9','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','5','0','0','9'},
	{'9','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','5','0','9'},
	{'9','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','5','9'},
	{'9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9'},
};
unsigned char matrizDestino[LONG_Y][LONG_X];

int main(void)
{
	int x,y;
	complejo z(1,3);
	complejo w(0,0); // w = f(z).
	int opcion;

	// w=exp(z); //w=(0.5403.., 0.1411..).
	// cout << "exp(z)=";
	// w.emitir();

	// w=complejo(1+w.re(),1-w.im());//w=(1.5403,0.8589).
	// cout << "con cambio de coordenadas: ";
	// w.emitir();

	// w=complejo(w.re()*(LONG_X/2.0),w.im()*(LONG_Y/2.0));//w=(18.4836,3.00).
	// cout << "ajustada al tamanio de la imagen: ";
	// w.emitir();

	// w.redondeo();//w=(18,3).
	// cout << "redondeado: ";
	// w.emitir();

	// matrizDestino[0][0]=matrizOrigen[(int)w.im()][(int)w.re()];
	// cout << "resultado: " << matrizDestino[0][0];
	// cout << "resultado: " << matrizDestino[(int)w.im()][(int)w.re()];

	cout << "elija una funcion:" << endl << "1) para f(z)=z" << endl << "2) para f(z) = exp(z)" << endl;
	while(opcion != FN1 && opcion != FN2)
		cin >> opcion;

	for(y=0;y<LONG_Y;y++)
	{
		for(x=0;x<LONG_X;x++)
		{
			if(opcion==1)
				matrizDestino[y][x]=matrizOrigen[y][x];
			else
			{
				z=complejo((double) x,(double) y);
				w=exp(z);
				w=complejo(1+w.re(),1-w.im());
				w=complejo(w.re()*((LONG_X-1)/2.0),w.im()*((LONG_Y-1)/2.0));
				w.redondeo();

				z.emitir();
				cout << " <---des---<---ori---<";
				w.emitir();
				cout << endl;


				matrizDestino[y][x]=matrizOrigen[(int)w.im()][(int)w.re()];
			}
		}
	}	

	emitirMatriz(matrizDestino);
	return EXIT_SUCCESS;
}

void emitirMatriz(unsigned char m[][LONG_X])
{
	int x=0,y=0;

	for(y=0;y<LONG_Y;y++)
	{
		for(x=0;x<LONG_X;x++)
			cout << m[y][x];
		cout << endl; 
	}
}