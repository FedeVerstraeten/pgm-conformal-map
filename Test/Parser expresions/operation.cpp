#include "operation.hpp"

float eval_uminus(float a1, float a2)
{
	return -a1;
}
float eval_exp(float a1, float a2)
{
	return a2<0 ? 0 : (a2==0?1:a1*eval_exp(a1, a2-1));
}
float eval_mul(float a1, float a2)
{
    return a1*a2;
}
float eval_div(float a1, float a2)
{
	if(!a2) {
		cerr<<"ERROR: Division by zero"<<endl;
		exit(EXIT_FAILURE);
	}
	return a1/a2;
}
float eval_mod(float a1, float a2)
{
    int a=a1,b=a2;
	if(!a2) {
		cerr<<"ERROR: Division by zero"<<endl;
		exit(EXIT_FAILURE);
	}
	return a%b;
}
float eval_add(float a1, float a2)
{
	return a1+a2;
}
float eval_sub(float a1, float a2)
{
	return a1-a2;
}
