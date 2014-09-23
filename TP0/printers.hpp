#ifndef PRINTERS_HPP
#define PRINTERS_HPP
#include"common.hpp"
#include<iostream>
#include <string>
#include <sstream>
#include<fstream>

void printMatrix(size_t**,ostream &,const size_t &,const size_t &);
void printImage(ostream &,size_t**,const size_t &,const size_t &,const size_t &);
void printString(string, ostream&);


#endif // PRINTERS_HPP_INCLUDED
