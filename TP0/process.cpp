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
