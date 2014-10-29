#ifndef BINTREE_HPP
#define BINTREE_HPP

#include <stdlib.h>
#include "common.hpp"


/**************************************************
 *                 CLASS TEMPLATE                 *
 **************************************************/

template <typename T>

class binTree
{
    private:
        T data;
        binTree *left_;
        binTree *right_;

    public:
        /**************************** CONSTRUCTORES ****************************/
        binTree();
        binTree(const T&);
        binTree(const binTree&);
        /***************************** DESTRUCTORES ****************************/
        ~binTree();
        /******************************* METODOS *******************************/
        status_t insert(binTree <T> &);
        //bool explore(const T);
        //binTree<T> search(const T); 
        void print (ostream&);
        void printTree(ostream&);
        /****************************** OPERADORES *****************************/
        /************************** FUNCIONES FRIENDS **************************/
        /************************** OPERADORES FRIENDS *************************/
};

/******************************************************************************/
/******************************* CONSTRUCTORES ********************************/
/******************************************************************************/
template <typename T>
binTree<T>::binTree()
{
    left_=NULL;
    right_=NULL;
}
template <typename T>
binTree<T>::binTree(const T &value)
{
    data=value;
    left_=NULL;
    right_=NULL;
}
template <typename T>
binTree<T>::binTree(const binTree &tree)
{
    left_=NULL;
    right_=NULL;

    // Copio la información de un árbol a otro
    data=tree.data;

    if(tree.left_)
    {
        // Solicito memoria y copio la estructura.
        // Al copiar obtengo el valor y una copia
        // de las direcciones de memoria. (?)
        left_=new binTree (*(tree.left_));

        // Apunto el nuevo árbol copiado al objeto
        // sobre el que estoy operando
    }
    if(tree.right_)
    {
        right_=new binTree (*(tree.right_));
    }


}
template <typename T>
binTree <T> :: ~binTree ()
{
    //delete left_;
    //delete right_;
}

template <typename T>
status_t binTree <T> :: insert(binTree <T> & subTree)
{
    if(left_==NULL)
    {
        left_=&subTree; 
        return  OK;
    }
    else if(right_==NULL)
    {
        right_=&subTree;
        return OK;
    }
    return ERROR_INSERT_TREE_NODE;
}

template <typename T>
void binTree <T> :: print(ostream & os)
{
    os<<data<<endl;
}

template <typename T>
void binTree <T> :: printTree(ostream & os)
{
    os<<data<<endl;
    if(left_!=NULL) 
        left_->printTree(os);
    if(right_!=NULL)
        right_->printTree(os);
}

#endif
