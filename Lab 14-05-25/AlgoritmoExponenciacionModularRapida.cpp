//  Algoritmo de exponenciación rápida

#include <iostream>
using namespace std;

int exponenciacionModular(int base, int exponente, int modulo){

    int resultado = 1;
    base = base % modulo; //reducir la base desde un principio.

    while(exponente > 0){

        if(exponente % 2 == 1){ // SI es IMPAR: multplica el resultado por la base.
            resultado = (resultado * base) % modulo;
        }

        //reducir exponente a la mitad:
        exponente = exponente / 2 ; 

        //evaluo la base al cuadrado: (modulo n)
        base = (base * base) % modulo;
    }

    return resultado; 

}

int main(){
    int a = 5;
    int b = 23;
    int n = 11;

    int resultado = exponenciacionModular(a,b,n);

    cout<<a<< "^"<< b << " mod "<<n << " = " << resultado <<endl;
}