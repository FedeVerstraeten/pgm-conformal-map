#include <iostream>
#include "complejo.hpp"
#include <stdlib.h>

using namespace std;

int main(void)
{
	complejo z(1.4,2.6);
	complejo w; // w = f(z).
	int a=2;

	cout<<z;
	cout<<endl;
	z=z^(a);
	cout<<z;


	cout << a;


	return EXIT_SUCCESS;
}