#include"printers.hpp"

void printMatrix(size_t** matrix, ostream &os,const size_t &row,const size_t &col)
{
   // os << number_of_elements[0] << " Hubs"<<"\n";
   for(size_t i=0 ; i<row ; ++i)
   {
       for(size_t j=0 ; j<col ; ++j)
       {
           os<<matrix[i][j]<<" ";
       }
       os<<"\n";
   }

}

void printImage(ostream &os,size_t** matrix,const size_t &row,const size_t &col,const size_t &maxInten)
{
    os<<"P2"<<endl;
    os<<col<<" "<<row<<endl;
    os<<maxInten<<endl;

    //Impresión de matriz
    printMatrix(matrix,os,row,col);
}

void printString(string s, ostream& os){    os << s << "\n"; }
