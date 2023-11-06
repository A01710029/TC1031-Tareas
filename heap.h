/*
 * heap.h
 *
 * Paulina Almada Martinez (A01710029)
 * 30/10/2023
 */

#ifndef HEAP_H_
#define HEAP_H_

#include <string>
#include <sstream>
#include <iostream>

using namespace std;

template <class T>
class Heap {
private:
	T *data;
	unsigned int heapsize;
	unsigned int count;
	unsigned int parent(unsigned int) const;
	unsigned int left(unsigned int) const;
	unsigned int right(unsigned int) const;
	void heapify(unsigned int);
	void swap(unsigned int, unsigned int);

public:
	Heap(unsigned int) ;
	~Heap();
	void push(T);
	T pop();
    T top();
    bool empty() const;
    unsigned int size();
	void clear();
	string toString() const;
};

//Constructor
template <class T>
Heap<T>::Heap(unsigned int sze)  {
	heapsize = sze;
	data = new T[heapsize];
	count = 0;
}

//Destructor
template <class T>
Heap<T>::~Heap() {
	delete [] data;
	data = 0;
	heapsize = 0;
	count = 0;
}

/* FUNCIONES AUXILIARES */

//para ir de hijo a padre
template <class T>
unsigned int Heap<T>::parent(unsigned int pos) const {
	return (pos - 1) / 2;
}

//para ir a la izquierda
template <class T>
unsigned int Heap<T>::left(unsigned int pos) const {
	return ((2 * pos) + 1);
}

//para ir a la derecha
template <class T>
unsigned int Heap<T>::right(unsigned int pos) const {
	return ((2 * pos) + 2);
}

//para cambiar posiciones de valores
template <class T>
void Heap<T>::swap(unsigned int i, unsigned int j) {
	T aux = data[i];
	data[i] = data[j];
	data[j] = aux;
}

//para organizar el árbol de nuevo después de borrar
template <class T>
void Heap<T>::heapify(unsigned int pos) { //
	unsigned int le = left(pos);
	unsigned int ri = right(pos);
	unsigned int min = pos;
	if (le <= count && data[le] < data[min]) {
		min = le;
	}
	if (ri <= count && data[ri] < data[min]) {
		min = ri;
	}
	if (min != pos) {
		swap(pos, min);
		heapify(min);
	}
}

template <class T>
void Heap<T>::clear() {
	count = 0;
}

/* FUNCIONES DE LA TAREA */

//agrega un valor a la fila priorizada
template <class T>
void Heap<T>::push(T val)  {
	unsigned int pos;

	pos = count;
	count++;
	while (pos > 0 && val < data[parent(pos)]) {
		data[pos] = data[parent(pos)];
		pos = parent(pos);
	}
	data[pos] = val;
}

//elimina el dato con mayor prioridad (el root)
template <class T>
T Heap<T>::pop()  {
	T aux = data[0]; //valor del root

	data[0] = data[--count];
	heapify(0); //reorganizar desde el root
	return aux;
}

//regresa el valor del dato con mayor prioridad (el root)
template <class T>
T Heap<T>::top() {
    return data[0];
}

//determina si la fila priorizada tiene valores o no
template <class T>
bool Heap<T>::empty() const {
    //compara si num de valores es igual a 0
	return (count == 0);
}

//regresa el número de valores en la fila priorizada
template <class T>
unsigned int Heap<T>::size(){
    return count; //número de valores en heap
}

template <class T>
std::string Heap<T>::toString() const {
	std::stringstream aux;
	aux << "[";	for (unsigned int i = 0; i < count; i++) {
		if (i != 0) {
			aux << " ";
		} aux << data[i];
	} aux << "]";
	return aux.str();
}

#endif /* HEAP_H_ */
