#include "process.hpp"

extern string function_struct[];


/**********************************************************************/

bool getMagicNumber(istream &iss, string &sMagicNum)
{
    string aux;
    iss >> aux;
    if(aux=="P2")
    {
        iss >> aux;
        sMagicNum=aux;
        return true;
    }
    return false;
}

bool FunctionType(string aux)
{
    for( size_t i=0;i<MAX_NUMFUCTION;i++){
        if(aux==function_struct[i])
            return true;
    }
    return false;
}

bool createMatrix(size_t** &imagIn,size_t** &imagOut,size_t row,size_t col)
{
    if(row>0 && col>0)
    {
        imagIn=new size_t* [row];
        for(size_t i=0 ; i<row ; ++i)
        {
            imagIn[i]=new size_t [col];
        }

        imagOut=new size_t* [row];
        for(size_t i=0 ; i<row ; ++i)
        {
            imagOut[i]=new size_t [col];
        }
        return true;
    }
    return false;
}
