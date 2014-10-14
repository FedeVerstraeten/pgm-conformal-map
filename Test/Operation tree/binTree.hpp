#ifndef BINTREE_HPP
#define BINTREE_HPP

#include "common.hpp"

/*************************************************
*                 CLASS TEMPLATE                 *
**************************************************/

template <typename T>

class binTree
{
    private:
        T data;
        binTree *left_;
        binTree *right_;
        binTree *root_;

    public:
        // Constructors & destructor
        binTree();
        binTree(const T&);
        binTree(const binTree&);
        ~binTree();

        // Methods
        void insert(T);
        void remove(T);
        void print (ostream&);

};

/*************************************************
*                 IMPLEMENTATION                 *
**************************************************/

template <typename T>
binTree <T> :: binTree ()
{
    left_=NULL;
    right_=NULL;
    root_=NULL;
}

template <typename T>
binTree <T> :: binTree (const T &value)
{
    data=value;
    left_=NULL;
    right_=NULL;
    root_=NULL;
}

template <typename T>
binTree <T> :: binTree (const binTree &tree)
{
    left_=NULL;
    rigth_=NULL;

    // Copio la información de un árbol a otro
    data=tree.data;

    if(tree.l_)
    {
        // Solicito memoria y copio la estructura.
        // Al copiar obtengo el valor y una copia
        // de las direcciones de memoria. (?)
        l_=new binTree (*(tree.l_));

        // Apunto el nuevo árbol copiado al objeto
        // sobre el que estoy operando
        l_->root_=this;
    }
    if(tree.r_)
    {
        r_=new binTree (*(tree.r_));
        r_->root_=this;
    }


}

template <typename T>
binTree <T> :: ~binTree ()
{
    delete left_;
    delete right_;
}


#endif
