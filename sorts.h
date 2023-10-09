/*
 * sorts.h
 *
 * Paulina Almada Martinez (A01710029)
 * 7/09/2023
 */

#ifndef SORTS_H_
#define SORTS_H_

#include <iostream>
#include <vector>

using namespace std;

//Clase Sorts
template <class T>
class Sorts {
    private:
	void swap(vector<T> &v, int i, int j);
	void copyArray(vector<T> &A, vector<T> &B, int low, int high);
	void mergeArray(vector<T> &A, vector<T> &B, int low, int mid, int high);
	void mergeSplit(vector<T> &A, vector<T> &B, int low, int high);

	public:  
	void ordenaSeleccion(vector<T> &v);
    void ordenaBurbuja(vector<T> &v);
    void ordenaMerge(vector<T> &v);
    int busqSecuencial(const vector<T> &v, const T &target);
    int busqBinaria(const vector<T> &v, const T &target);
};

template <class T>
void Sorts<T>::swap(vector<T> &v, int i, int j) {
	T aux = v[i];
	v[i] = v[j];
	v[j] = aux;
}

template <class T>
void Sorts<T>::ordenaSeleccion(vector<T> &v) {
	// primer ciclo es el límite del segundo
	int pos; // valor de indice

	// recorre arreglo de mayor a menor
	for (int i = v.size() - 1; i > 0; i--) {
		pos = 0;
		for (int j = 1; j <= i; j++) {
			if (v[j] > v[pos]) { // si num en j es mayor que num en pos actual 
				pos = j; // replazar indice de j (mayor) con pos
			}
		}

		// si 
		if (pos != i) { // si max no está hasta el final
			swap(v, i, pos); // moverlo al final
		}
	}
}

template <class T>
void Sorts<T>::ordenaBurbuja(vector<T> &v) {
	// primer ciclo es el límite del segundo
	for (int i = v.size() - 1; i > 0; i--) {
		for (int j = 0; j < i; j++) {
			if (v[j] > v[j + 1]) {
				swap(v, j, j + 1); // se cambia la posición aka se modifica v
			}
		}
	}
}

template <class T>
void Sorts<T>::copyArray(vector<T> &A, vector<T> &B, int low, int high) {
	// sobreescribe el progreso logrado hasta el momento en B
	// al array original A para que el siguiente sort
	// ya tenga las partes organizadas
	for(int i = low; i <= high; i++){
		A[i] = B[i];
	}
}

template <class T>
void Sorts<T>::mergeArray(vector<T> &A, vector<T> &B, int low, int mid, int high) {
	int i;
	int j;
	int k;

	i = low; // tracker arreglo A
	j = mid + 1; // para dividir cada arreglo en 2 (pares originalmente merged)
	k = low; // tracker arreglo B

	while (i <= mid && j <= high){
		if(A[i] < A[j]){ // si valor con menor indice de A < a valor con mayor indice de A
			B[k] = A[i]; // valor con menor indice de A se guarda en B (al inicio) 
			i++; // incrementa counter de A
		} else {
			B[k] = A[j]; // valor con menor indice de A se guarda en B (al final)
			j++; // se expande gap de comparación
		}
		k++;
	}

	if(i > mid){
		for(; j <= high; j++){
			B[k++] = A[j]; 
		} 
	} else {
		for(; i <= mid; i++){
			B[k++] = A[i];
		}
	}
}

template <class T>
void Sorts<T>::mergeSplit(vector<T> &A, vector<T> &B, int low, int high) {
	int mid;

	if ( (high - low) < 1 ) {
		return;
	}
	mid = (high + low) / 2;
	mergeSplit(A, B, low, mid);
	mergeSplit(A, B, mid + 1, high);
	mergeArray(A, B, low, mid, high);
	copyArray(A, B, low, high);
}

template <class T>
void Sorts<T>::ordenaMerge(vector<T> &v) {
	vector<T> tmp(v.size());

	mergeSplit(v, tmp, 0, v.size()-1);
}

template <class T>
int Sorts<T>::busqSecuencial(const vector<T> &v, const T &target) {
	for (int i = 0; i < v.size(); i++){
		if(v[i] == target){
			return i;
		}
	}
	return -1;
}

template <class T>
int Sorts<T>::busqBinaria(const vector<T> &v, const T &target) {
	int low = 0;
	int mid = 0;
    int size = v.size();
	int high = size - 1;

	while(low <= high){
		mid = (low + high)/2;
		if(v[mid] == target){
			return mid;
		} else if (v[mid] < target){
			low = low + 1;
		} else if (v[mid] > target){
			high = high - 1;
		} else {
			return mid + 1;
		}
	}
    return -1;
}

#endif /* SORTS_H_ */