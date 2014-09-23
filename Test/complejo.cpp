#include "complejo.hpp"  
#include <iostream>
#include <cmath>

using namespace std;

const complejo exp(const complejo & z)
{
	double re = z.re_;
	double im = z.im_;
	return complejo(cos(re),sin(im));
}
complejo::complejo() 
{
	re_ = 0;
	im_ = 0;
}
complejo::complejo(double r) 
{
	re_ = r;
	im_ = 0;
}
complejo::complejo(double r, double i) 
{
	re_ = r;
	im_ = i;
}
complejo::complejo(complejo const &c) 
{
	re_ = c.re_;
	im_ = c.im_;
}
void complejo::emitir()const
{
	cout << "(" << re_ << "," << im_ << ")" << endl; 
}
complejo const & complejo::operator=(complejo const &c)
{
	re_ = c.re_;
	im_ = c.im_;
	return *this;
}
complejo const & complejo::operator*=(complejo const &c)
{
	double re = re_ * c.re_ - im_ * c.im_;
	double im = re_ * c.im_ + im_ * c.re_;
	re_ = re, im_ = im;
	return *this;
}

complejo const & complejo::operator+=(complejo const &c)
{
	double re = re_ + c.re_;
	double im = im_ + c.im_;
	re_ = re, im_ = im;
	return *this;
}

complejo const & complejo::operator-=(complejo const &c)
{
	double re = re_ - c.re_;
	double im = im_ - c.im_;
	re_ = re, im_ = im;
	return *this;
}
complejo const complejo::redondeo(void)
{
	if( (((int)re_)+0.5) < re_)
		re_=(int)++re_; 
	else re_=(int)re_;

	if( (((int)im_)+0.5) < im_)
		im_=(int)++im_; 
	else im_=(int)im_;
}
complejo::~complejo()
{
}
double complejo::re() const
{
	return re_;
}
double complejo::im() const
{
	return im_;
}

double complejo::abs() const
{
	return std::sqrt(re_ * re_ + im_ * im_);
}

double complejo::abs2() const
{
	return re_ * re_ + im_ * im_;
}

complejo const & complejo::conjugar()
{
	im_*= -1;
	return *this;
}

complejo const complejo::conjugado() const
{
	return complejo(re_, -im_);
}

bool complejo::zero() const
{
 #define ZERO(x) ((x) == +0.0 && (x) == -0.0)
	
	if(ZERO(re_) && ZERO(im_)) return true;
	
	else false;
}

complejo const operator+(complejo const &x, complejo const &y)
{
	complejo z(x.re_ + y.re_, x.im_ + y.im_);
	return z;
}

complejo const operator-(complejo const &x, complejo const &y)
{
	complejo r(x.re_ - y.re_, x.im_ - y.im_);
	return r;
}

complejo const operator*(complejo const &x, complejo const &y)
{
	complejo r(x.re_ * y.re_ - x.im_ * y.im_,
	          x.re_ * y.im_ + x.im_ * y.re_);
	return r;
}

complejo const operator/(complejo const &x, complejo const &y)
{
	return x * y.conjugado() / y.abs2();
}

complejo const operator/(complejo const &c, double f)
{
	return complejo(c.re_ / f, c.im_ / f);
}

bool operator==(complejo const &c, double f)
{
	bool b = (c.im_ != 0 || c.re_ != f) ? false : true;
	return b;
}

bool operator==(complejo const &x, complejo const &y)
{
	bool b = (x.re_ != y.re_ || x.im_ != y.im_) ? false : true;
	return b;
}

ostream &operator<<(ostream &os, const complejo &c)
{
	return os << "(" << c.re_<< "," << c.im_ << ")";
}

istream & operator>>(istream &is, complejo &c)
{
	int good = false;
	int bad  = false;
	double re = 0;
	double im = 0;
	char ch = 0;

	if (is >> ch && ch == '(') 
	{
		if (is >> re && is >> ch && ch == ',' && is >> im && is >> ch && ch == ')')
			good = true;
		else
			bad = true;
	} 
	else if (is.good())
	{
		is.putback(ch);
		if (is >> re)
				good = true;
		else
				bad = true;
	}

	if (good)
		c.re_ = re, c.im_ = im;
	if (bad)
		is.clear(ios::badbit);

	return is;
}
