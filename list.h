/*
 * sorts.h
 *
 * Paulina Almada Martinez (A01710029)
 * 24/09/2023
 */

#ifndef LIST_H_
#define LIST_H_

#include <iostream>
#include <sstream>

using namespace std;

template <class T> class List;

/* Clase Link */
template <class T>
class Link {
    private:
	Link(T);
	Link(T, Link<T>*);
	Link(const Link<T>&);

	T	    value;
	Link<T> *next;

	friend class List<T>; 
};

//Constructores
template <class T>
Link<T>::Link(T val): value(val), next(0) {} 

template <class T>
Link<T>::Link(T val, Link* nxt): value(val), next(nxt) {}

template <class T>
Link<T>::Link(const Link<T> &source): value(source.value), next(source.next) {}

/* Clase List */
template <class T>
class List {
    public:
    List();
	List(const List<T>&) ; 
	~List();

    void addFirst(T);
    bool empty() const;
    void clear();

    void insertion(T val);
    T search(T val);
    void update(T pos, T val);
    T deleteAt(T pos);

    string toString() const;
    
    private:
	Link<T> *head;
	int 	size;
};

//Constructores
template <class T>
List<T>::List() : head(0), size(0) {} 

template <class T>
List<T>::~List() { 
	clear(); 
}

// Clases para procesos internos
template <class T>
bool List<T>::empty() const {
	return (head == 0);
}

template <class T>
void List<T>::clear() {
	Link<T> *p, *q; 
	
	p = head;
	while (p != 0) { 
		q = p->next; 
		delete p; 
		p = q; 
	}
	head = 0;
	size = 0;
}

template <class T>
void List<T>::addFirst(T val)  {
	Link<T> *newLink;

	newLink = new Link<T>(val); 
	
	newLink->next = head; 
	head = newLink; 
	size++;
}

template <class T>
string List<T>::toString() const {
	stringstream aux;
	Link<T> *p;

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

/* Funciones de la tarea */

// Insertar un elemento 
template <class T>
void List<T>::insertion(T val){
	Link<T> *newLink, *p;

	newLink = new Link<T>(val);

	if (empty()) {
		addFirst(val);
		return;
	}

	p = head;
	while (p->next != 0) {
		p = p->next;
	}

	newLink->next = 0; 
	p->next = newLink; 
	size++;
}

// Encontrar el elemento y devolver su posición
// Devolver -1 si no se encuentra
template <class T>
T List<T>::search(T val){
    Link<T> *p;
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
void List<T>::update(T pos, T val){
    Link<T> *p;
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
T List<T>::deleteAt(T pos){
    T val;
    int index = 0;

    Link<T> *p;
	Link<T> *prev = 0;

	p = head;
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
    
	delete p;
	size--;
	return val;
}

#endif /* LIST_H_ */
