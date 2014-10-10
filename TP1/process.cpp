#include "process.hpp"
#include "common.hpp"

extern string function_dictionary[];
extern size_t  altoImag, anchoImag;
extern string typeFunction;


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

void matrixTransformation(size_t** &matrixIn,size_t** &matrixOut)
{
    complejo z;
	complejo w; // w=f(z)

    for(size_t fil=0 ; fil < altoImag ; fil++)
	{
		for(size_t col=0 ; col < anchoImag ; col++)
		{
			// Recibo las coordenadas de la matriz destino,
			// z es el correspondiente valor del plano complejo 2x2.
			z = matrizAplanoC(col,fil);

			if(typeFunction=="exp(z)" || typeFunction=="EXP(Z)") w=exp(z);
			else if (typeFunction=="z" || typeFunction=="Z") w=id(z);

			if(w.re()<-1 || w.re()>1 || w.im()<-1 || w.im()>1)
				matrixOut[fil][col]=0;
			else
			{
				w = planoCaMatriz(w);
				matrixOut[fil][col]=matrixIn[(int)w.im()][(int)w.re()];
			}
		}
	}
}
