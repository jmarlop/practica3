#define HASHTABLE_H

#include <iostream>
#include <ostream>
#include <stdexcept>
#include "Dict.h"
#include "TableEntry.h"
#include "ListLinked.h"

using namespace std;

template <typename V>

class HashTable: public Dict<V>{
private:
	//elementos
	int n;
	//cubetas
	int max = 3;
	//tabla de cubetas
	ListLinked<TableEntry<V>>** table;
	//return key con calculos ascii
	int h(string key){
		int asci= 0;
		for(int i = 0; i < key.length(); i++){
			asci+=int(key.at(i));
		}
		return asci%max;
	}
public:
	HashTable(int size) {
		n = 0;
		max = size;
		table = new ListLinked<TableEntry<V>>*[max]; // Reserva arreglo dinámico de punteros
		for (int i = 0; i < max; i++) {
			table[i] = nullptr; // Inicializa cada entrada a nullptr
		}
	}

	~HashTable() {
		for (int i = 0; i < max; i++) {
			delete table[i]; // Libera cada lista enlazada
		}
		delete[] table; // Libera el arreglo de punteros
	}
	//devuelve las cubetas
	int capacity(){
		return max;
	}
	// busca la llave
	V search(string key) override {
		int index = h(key);
		Node<TableEntry<V>>* aux = nullptr; // Inicializa aux a nullptr

		if (table[index] != nullptr) { // Verifica si la lista en ese índice existe
			aux = table[index]->first;
		}

		while (aux != nullptr) { // Recorre la lista completa
			if (aux->data.key == key) { // Clave encontrada
				return aux->data.value;
			}
				aux = aux->next;
		}

		// Clave no encontrada
		return -1;
	}

	//insertar key en value
	void insert(string key, V value) override {
		int indice = h(key);
		V status = search(key);
		if (status != -1){
			throw runtime_error("Elemento ya existente");
		}
		Node<TableEntry<V>>* nuevoNodo = new Node<TableEntry<V>>(TableEntry(key, value), nullptr);

		if(table[indice] == nullptr){
			table[indice] = new ListLinked<TableEntry<V>>();
		}
		Node<TableEntry<V>>* aux = table[indice]->first;


		//inserccion en primer nodo por tabla vacia
		if (aux == nullptr) {
			table[indice]->first = nuevoNodo;
		} 
		else {
			while (aux->next != nullptr) {
				aux = aux->next;
			}
			aux->next = nuevoNodo;
		}

		n++;
	}

	V remove(string key) override{
		int indice = h(key);
		if(search(key) == -1){
			throw runtime_error("No existe esta entrada");
		}
		else{

		Node<TableEntry<V>>* aux = nullptr;
		Node<TableEntry<V>>* prev = nullptr;

		if(table[indice] != nullptr){
			aux = table[indice]->first;

		}
		if (aux->data.key == key) { // Comparamos la clave del nodo
			if (prev == nullptr) {
			// Caso especial: el nodo a eliminar es el primero
				table[indice]->first = aux->next;
			} 
			else {
			// Nodo intermedio o final
				prev->next = aux->next;
			}

			// Almacenar el valor antes de eliminar el nodo
			V removedValue = aux->data.value;
			delete aux; // Liberar memoria del nodo eliminado

			n--; // Decrementar el número de elementos
			return removedValue; // Retornar el valor eliminado
		}
		}
		return -1;
	}
	//devolver entreadas
	int entries() override{
		return n;
	}
	friend std::ostream& operator<<(std::ostream &out, const HashTable<V> &th){
		Node<TableEntry<V>>* aux = nullptr;
		for (int i = 0; i < th.max; i++){
			if(th.table[i] != nullptr){
			aux = th.table[i]->first;
			}
			while(aux != nullptr){
				out << aux->data.key << ": " << aux->data.value << endl;
				aux = aux->next;
			}
		}
		return out;
	}
	V operator[](std::string key){
		return search(key);
	}


};