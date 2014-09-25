#ifndef _COMPLEJO_H_INCLUDED_
#define _COMPLEJO_H_INCLUDED_

#include <iostream>
#include <cmath>

using namespace std;

class complejo 
{
private:
		double re_, im_;
public:
	/************************* CONSTRUCTORES **************************/
	complejo();
	complejo(double);
	complejo(double, double);
	complejo(const complejo &);
	/*************************  DESTRUCTORES **************************/
	~complejo();
	/************************* OPERADORES *****************************/
	complejo const &operator=(complejo const &);
	complejo const &operator*=(complejo const &);
	complejo const &operator+=(complejo const &);
	complejo const &operator-=(complejo const &);
	/*************************** METODOS ******************************/
	complejo const redondeo(void);//en el caso que la parte decimal sea 0.5 se redondea hacia abajo.
	double re() const;
	double im() const;
	double abs() const;
	double abs2() const;
	complejo const &conjugar();
	complejo const conjugado() const;
	void emitir()const;
	bool zero() const;
	/*********************** OPERADORES FRIEND *************************/
	friend complejo const operator+(complejo const &, complejo const &);
	friend complejo const operator-(complejo const &, complejo const &);
	friend complejo const operator*(complejo const &, complejo const &);
	friend complejo const operator/(complejo const &, complejo const &);
	friend complejo const operator/(complejo const &, double);
	friend bool operator==(complejo const &, double);
	friend bool operator==(complejo const &, complejo const &);
	friend std::ostream &operator<<(std::ostream &, const complejo &);
	friend std::istream &operator>>(std::istream &, complejo &);
	/*********************** FUNCIONES FRIEND *************************/
	friend complejo const exp(const complejo &);
	friend complejo const id(const complejo &);
	/******************************************************************/
};

#endif
