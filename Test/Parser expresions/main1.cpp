#include <iostream>
#include <string>
#include <cstring>

using namespace std;


string function_dictionary[] = {
                                 "+","-","*","/","^",
                                 "z", "Z",
                                 "exp(z)","EXP(Z)",
                                 "\0"
                               };

int main ()
{
    char ch[] = {"1243+exp(z)+2exp(z)-3^2"}; // como vendria de argv
    string functions;

    size_t i=0;
    while(function_dictionary[i]!="\0")
    {
         functions+=function_dictionary[i]+" ";
         i++;
    }

    //cout<<functions<<endl;

    char* pch=NULL;
    pch = strtok (ch,functions.c_str());
    string str_out[100];
    string out;
    int j=0;

    while (pch != NULL)
    {
        str_out[j]=string(pch);
        //In subsequent calls, the function expects a
        //null pointer and uses the position right after
        // the end of the last token as the new starting
        // location for scanning.
         pch = strtok (NULL, functions.c_str());
         j++;

    }

    for(size_t i=0 ; i<10 ; i++)
        out+=str_out[i]+" ";
    cout<<out<<endl;


    return 0;
}
