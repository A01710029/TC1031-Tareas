/*
 * funciones.h
 *
 * Paulina Almada Martinez (A01710029)
 * 14/08/2023
 */

#ifndef FUNCIONES_H_
#define FUNCIONES_H_

#include <iostream>

//Clase Funciones
class Funciones {
    public:  

    long sumaIterativa(int n);
    long sumaRecursiva(int n);
    long sumaDirecta(int n);

};

long Funciones::sumaIterativa(int n){
    int sum = 0;
    for(int i = 0; i <= n; i++){
        sum = sum + i;
    }
    return sum;
}

long Funciones::sumaRecursiva(int n){
    if(n == 0){
        return 0;
    } else {
        return n + sumaRecursiva(n-1);
    }
}

long Funciones::sumaDirecta(int n){
    return n*(n+1)/2;
}

#endif /* FUNCIONES_H_ */
