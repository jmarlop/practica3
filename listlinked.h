#include <ostream>
#include <iostream>
#include "List.h"
#include "Node.h"

template <typename T>
class ListLinked : public List<T> {

public:
    Node<T>* first;
    int n;

    ListLinked(){
        first = nullptr;
        n = 10;
    }
    ~ListLinked(){
        Node<T>* actual = first;

        while(actual != nullptr){
            Node<T>* siguiente = actual->next;
            delete actual;
            actual = siguiente;
    }
        first = nullptr;

    }
    T operator[](int pos){
        try{
            if(pos < 0 || pos > size()-1){
                throw std::out_of_range("Valor fuera de rango");

            }
            else{
                for (int i = 0; i <= pos ;i++){
                    first = first->next;
                }
                    return first->data;
            }
        }
        catch(std::out_of_range& e){
            std::cerr << e.what();
        }
    }
    friend std::ostream& operator<<(std::ostream &out, const ListLinked<T> &list){
        out << "[";
        for(int i = 0; list.n;i++){
                out << list.first->data << " ";
        }
        out << "]\n";
        return out;
    }
    int size() override{
        Node<T> *aux = first;
        int tamaño = 0;
        while(aux != nullptr){
            tamaño++;
            aux = aux->next;
        }
        return tamaño;
    }
    void insert(int pos, T e) override{
        if(pos == 0){
            first->data = e;
        }
        else{
            Node<T>* prev = nullptr;
            Node<T>* aux = first;
            int i = 0;
            while (aux != nullptr && i < pos){
                prev = aux;
                aux = aux->next;
                i++;
            }
            if(i == pos){
                prev->next = new Node<T>(e,aux);
            }

        }
    }
    void append(T e) override{
        insert(size(),e);
    }
    void prepend(T e) override{
        insert(0,e);
    }
    T remove(int pos) override{
        Node<T>* aux = first;
        Node<T>* prev = nullptr;
        int i = 1;
        T devolver;
        if(pos == 0){
            first = first->next;
            devolver = aux->data;
            delete aux;
            return devolver;
        }
        else{
            while(aux != nullptr && i < pos){
                prev = aux;
                aux = aux->next;
                i++;
            }
            devolver = aux->data;
            prev->next = aux->next;
            return devolver;
        }
    }
    bool empty() override{
        if(size() == 0){
            return true;
        }
        else{
            return false;
        }
    }

    int search(T e){
        int cont = 0;
        Node<T>* aux = first;
        for(int i = 0; i <= size(); i++){
            if(aux->data == e){
                return i;
            }
            aux = aux->next;
        }
        return -1;

    }

    T get(int pos) override{
        Node<T>* aux = first;
        for(int i = 0; i < pos; i++){
            aux = aux->next;
        }
        return aux->data;

    }

};
// ...