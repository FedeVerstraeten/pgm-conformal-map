#include "process.hpp"
#include "common.hpp"

extern string function_dictionary[];


/**********************************************************************/

bool getMagicNumber(istream &iss, string &sMagicNum)
{
    string aux;
    iss >> aux;
    if(aux==MAGICNUM)
    {
        iss >> aux;
        sMagicNum=aux;
        return true;
    }
    return false;
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
void readLine(istream &is, string &str)
{
	getline(is,str);
	while(str.find('#')==0) getline(is,str);
}
