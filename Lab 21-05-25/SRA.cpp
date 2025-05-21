#include <iostream>
#include <vector>

using namespace std;

// Exponenciación modular rápida
int potencia_modular(int base, int exponente, int modulo) {
    int resultado = 1;
    base %= modulo;
    while (exponente > 0) {
        if (exponente % 2 == 1)
            resultado = (resultado * base) % modulo;
        base = (base * base) % modulo;
        exponente /= 2;
    }
    return resultado;
}

// Convertir letra a número (A = 0, ..., Z = 25)
int letra_a_numero(char letra) {
    return letra - 'A';
}

// Convertir número a letra
char numero_a_letra(int numero) {
    return 'A' + numero;
}

// Cifrado RSA letra por letra
vector<int> cifrar_rsa(const string& mensaje, int e, int n) {
    vector<int> cifrado;
    for (char c : mensaje) {
        if (c >= 'A' && c <= 'Z') {
            int m = letra_a_numero(c);
            int c_valor = potencia_modular(m, e, n);
            cifrado.push_back(c_valor);
        }
    }
    return cifrado;
}

// Descifrado RSA letra por letra
string descifrar_rsa(const vector<int>& cifrado, int d, int n) {
    string mensaje_descifrado = "";
    for (int c_valor : cifrado) {
        int m = potencia_modular(c_valor, d, n);
        mensaje_descifrado += numero_a_letra(m);
    }
    return mensaje_descifrado;
}

int main() {
    string mensaje;
    cout << "Ingresa el mensaje en MAYÚSCULAS (solo letras): ";
    cin >> mensaje;

    int n = 187;
    int e = 7;
    int d = 23;

    // Cifrado
    vector<int> cifrado = cifrar_rsa(mensaje, e, n);
    cout << "\nMensaje cifrado: [ ";
    for (int valor : cifrado)
        cout << valor << " ";
    cout << "]\n";

    // Descifrado
    string descifrado = descifrar_rsa(cifrado, d, n);
    cout << "Mensaje descifrado: " << descifrado << endl;

    return 0;
}
