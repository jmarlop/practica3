#ifndef BSNODE_H
#define BSNODE_H

#include <ostream>

template <typename T> 
class BSNode {
    public:
        T elem;
        //elemento almacenado
        BSNode<T>* left;
        //nodo apuntando a la izquierda
        BSNode<T>* right;
        //nodo apuntando a la derecha
        BSNode(T elem, BSNode<T>* left = nullptr, BSNode<T>* right = nullptr) : elem(elem), left(left), right(right){}
        friend std::ostream& operator <<(std::ostream &out, const BSNode<T> & bsd){
            out << "Elemento:" << bsd.elem << "\n";
            return out;
        }
    
};

#endif