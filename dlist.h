/*
 * dlist.h
 *
 * Paulina Almada Martinez (A01710029)
 * 28/09/2023
 */

#ifndef DLIST_H_
#define DLIST_H_

#include <iostream>
#include <sstream>

using namespace std;

template <class T> class DList;

/* Clase Link para lista doble */
template <class T>
class DLink {
private:
	DLink(T);
	DLink(T, DLink<T>*, DLink<T>*);
	DLink(const DLink<T>&);

	T	    value;
	DLink<T> *previous;
	DLink<T> *next;

	friend class DList<T>;
};

//Constructores
template <class T>
DLink<T>::DLink(T val) : value(val), previous(0), next(0) {}

template <class T>
DLink<T>::DLink(T val, DLink *prev, DLink* nxt) : value(val), previous(prev), next(nxt) {}

template <class T>
DLink<T>::DLink(const DLink<T> &source) : value(source.value), previous(source.previous), next(source.next) {}

/* Clase Double Linked List */
template <class T>
class DList {
public:
	DList();
	DList(const DList<T>&);
	~DList();

    void addFirst(T);
    bool empty() const;
    void clear();

    void insertion(T val);
    T search(T val);
    void update(T pos, T val);
    T deleteAt(T pos);

    string toStringForward() const;
    string toStringBackward() const;

    private:
	DLink<T> *head;
	DLink<T> *tail;
	int 	 size;
};

//Constructor y destructor
template <class T>
DList<T>::DList() : head(0), tail(0), size(0) {}

template <class T>
DList<T>::~DList() {
	clear();
}

//Clases para procesos internos
template <class T>
bool DList<T>::empty() const {
	return (head == 0 && tail == 0);
}

template <class T>
void DList<T>::clear() {
	DLink<T> *p, *q;

	p = head;
	while (p != 0) {
		q = p->next; 
		delete p; 
		p = q;
	}

	head = 0; 
	tail = 0;
	size = 0;
}

template <class T>
void DList<T>::addFirst(T val){
	DLink<T> *newLink;

	newLink = new DLink<T>(val);

	if (empty()) { 
		head = newLink;
		tail = newLink;
	} else {
		newLink->next = head;
		head->previous = newLink; 
		head = newLink;
	}
	size++;
}

// Incluye estas funciones en tu dlist.h para poder imprimir tus respuestas
// en formatos compatibles con el main
template <class T>
std::string DList<T>::toStringForward() const {
	std::stringstream aux;
	DLink<T> *p;

	p = head;
	aux << "[";
	while (p != 0) {
		aux << p->value;
		if (p->next != 0) {
			aux << ", ";
		}
		p = p->next;
	}
	aux << "]";
	return aux.str();
}

template <class T>
std::string DList<T>::toStringBackward() const {
	std::stringstream aux;
	DLink<T> *p;

	p = tail;
	aux << "[";
	while (p != 0) {
		aux << p->value;
		if (p->previous != 0) {
			aux << ", ";
		}
		p = p->previous;
	}
	aux << "]";
	return aux.str();
}

/* Funciones de la tarea */

// Insertar un elemento 
template <class T>
void DList<T>::insertion(T val){
    DLink<T> *newLink;

	newLink = new DLink<T>(val);

	if (empty()) {
		addFirst(val);
	} else {
		tail->next = newLink;
		newLink->previous = tail;
		tail = newLink;
	}
	size++;
}

// Encontrar el elemento y devolver su posición
// Devolver -1 si no se encuentra
template <class T>
T DList<T>::search(T val){
    DLink<T> *p;
    int index = 0;

	p = head;
	while (p != 0) {
		if (p->value == val) {
			return index;
		} 
		p = p->next;
        index++;
	}
	return -1;
}

// Reemplazar un elemento en una posición específica con el valor dado
template <class T>
void DList<T>::update(T pos, T val){
    DLink<T> *p;
    int index = 0;

	p = head;
	while (p != 0) {
		if (index == pos) {
			p->value = val;
		} 
		p = p->next;
        index++;
	}
}

// Borrar un elemento segun su posición
// Regresar el valor numérico eliminado
template <class T>
T DList<T>::deleteAt(T pos){ 
    T  val;
    int index = 0;

    DLink<T> *p = head;
	DLink<T> *prev = 0;

	while (p != 0 && index != pos) {
		prev = p;
		p = p->next;
		index++;
	}

	val = p->value;

	if(prev == 0){
		head = p->next;
	} else {
		prev->next = p->next;
	}

	if(p->next != 0){
		p->next->previous = prev;
	} else {
		tail = prev;
	}

	delete p;
	size--;
    
	return val;
}

#endif /* DLIST_H_ */
