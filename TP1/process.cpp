#include "process.hpp"
#include "common.hpp"

extern string function_dictionary[];
extern size_t  altoImag, anchoImag;


/**********************************************************************/

status_t getMagicNumber(istream &is,string &str)
{
    is >> str;
    if(str==MAGICNUM) return OK;
    else return ERROR;
}

bool FunctionType(string aux)
{
    for( size_t i=0;i<MAX_NUMFUCTION;i++)
	{
        if(aux==function_dictionary[i])
            return true;
    }
    return false;
}

bool createMatrix(size_t** &matrix,size_t row,size_t col)
{
    if(row>0 && col>0)
    {
        matrix=new size_t* [row];
        for(size_t i=0 ; i<row ; ++i)
        {
            matrix[i]=new size_t [col];
        }
        return true;
    }
    return false;
}

void deleteMatrix(size_t** &matrix,size_t row,size_t col)
{
    for(size_t i = 0 ; i < row ; i++)
        delete[] matrix[i];

    delete[] matrix;
}


void readLine(istream &is, string &str)
{
	getline(is,str);
	while(str.find('#')==0) getline(is,str);
}

status_t readSize(istream &is)
{
    string str;
    bool good;

    readLine(is,str);
    istringstream issSize(str);

    if(issSize>>anchoImag && issSize>>altoImag && anchoImag!=0 && altoImag!=0) good=true;
    else good=false;

    if(good==false)
    {
        issSize.clear(ios::badbit);
        cerr<<"Error: invalid size value "<<endl;
        return ERROR;
    }

    return OK;
}

status_t readMaxIntensity(istream &is,size_t &maxInten)
{
    string str;
    bool good;

    readLine(is,str);
    istringstream issMax(str);

    if(issMax>>maxInten && maxInten<=255)good=true;
    else good=false;

    if(good==false)
    {
        issMax.clear(ios::badbit);
        cerr<<"Error: invalid max intensity value "<<endl;
        return ERROR;
    }

    return OK;
}

status_t readMatrixIN(istream& is,size_t** &matrix,const size_t &maxInten)
{
    size_t i=0; //iterador de "Alto de imagen"
    size_t j=0; //iterador de "Ancho de imagen"
    size_t aux;

    while(is>>aux && aux<=maxInten)
    {                
         matrix[i][j]=aux;
         j++;
        
        if(j>=anchoImag){ j=0; i++;}
    }
    if((is.fail() && !is.eof()) || aux>maxInten)
    {
        cerr<<"Invalid value "
            <<"in position "
            <<"("<<i<<";"<<j<<")"
            <<endl;
            return ERROR;
     }

    return OK;
}
