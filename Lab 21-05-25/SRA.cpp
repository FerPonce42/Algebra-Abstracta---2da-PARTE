#include <iostream>
#include <vector>
#include <string>
#include <iomanip>  // para setw y setfill
using namespace std;

// Exponenciación modular rápida
int mod_pow(int base, int exp, int mod) {
    int resultado = 1;
    base %= mod;
    while (exp > 0) {
        if (exp % 2 == 1)
            resultado = (resultado * base) % mod;
        base = (base * base) % mod;
        exp /= 2;
    }
    return resultado;
}

// Tabla de caracteres personalizada (A-Z)
string TABLA = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";

// Convertir bloque de letras a número (concatenando dos dígitos por letra)
int bloque_a_numero(const string& bloque) {
    string num_str = "";
    for (char c : bloque) {
        size_t val = TABLA.find(c);
        if (val == string::npos) {
            cout << "Error: caracter no válido en el bloque.\n";
            exit(1);
        }
        // Convertir val a dos dígitos, ej: 0 -> "00", 5 -> "05"
        if (val < 10)
            num_str += "0" + to_string(val);
        else
            num_str += to_string(val);
    }
    return stoi(num_str);
}


// Convertir número a bloque de letras (cada dos dígitos son una letra)
string numero_a_bloque(int num, int tamaño_bloque) {
    string num_str = to_string(num);

    // Rellenar con ceros a la izquierda para completar tamaño esperado (2 dígitos por letra)
    while ((int)num_str.length() < tamaño_bloque * 2) {
        num_str = "0" + num_str;
    }

    string bloque = "";
    for (int i = 0; i < tamaño_bloque * 2; i += 2) {
        int val = stoi(num_str.substr(i, 2));
        if (val < 0 || val >= (int)TABLA.size()) {
            cout << "Error: número fuera de rango en la conversión.\n";
            exit(1);
        }
        bloque += TABLA[val];
    }
    return bloque;
}

// Cifrado RSA en bloques
vector<int> rsa_cifrar(const string& mensaje, int e, int n, int tamaño_bloque, char relleno) {
    string mensaje_aux = mensaje;
    while (mensaje_aux.size() % tamaño_bloque != 0) {
        mensaje_aux += relleno;
    }

    vector<int> cifrado;
    for (size_t i = 0; i < mensaje_aux.size(); i += tamaño_bloque) {
        string bloque = mensaje_aux.substr(i, tamaño_bloque);
        int m = bloque_a_numero(bloque);
        if (m >= n) {
            cout << "Error: bloque numérico >= n. Ajusta tamaño de bloque o tabla.\n";
            exit(1);
        }
        int c = mod_pow(m, e, n);
        cifrado.push_back(c);
    }
    return cifrado;
}

// Descifrado RSA en bloques
string rsa_descifrar(const vector<int>& cifrado, int d, int n, int tamaño_bloque) {
    string mensaje = "";
    for (int c : cifrado) {
        int m = mod_pow(c, d, n);
        mensaje += numero_a_bloque(m, tamaño_bloque);
    }
    return mensaje;
}

int main() {
    string mensaje;
    int n, e, d, tamaño_bloque;
    char relleno;

    cout << "Ingresa el mensaje (solo letras A-Z, sin espacios): ";
    cin >> mensaje;

    cout << "Ingresa el valor de n (producto de primos p*q): ";
    cin >> n;

    cout << "Ingresa el exponente público e: ";
    cin >> e;

    cout << "Ingresa el exponente privado d: ";
    cin >> d;

    cout << "Ingresa el tamaño del bloque (número de letras por bloque): ";
    cin >> tamaño_bloque;

    cout << "Ingresa el caracter de relleno para completar bloques: ";
    cin >> relleno;

    TABLA = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";

    vector<int> cifrado = rsa_cifrar(mensaje, e, n, tamaño_bloque, relleno);

    cout << "\nMensaje cifrado: ";
    for (int c : cifrado)
        cout << c << " ";
    cout << "\n";

    string descifrado = rsa_descifrar(cifrado, d, n, tamaño_bloque);
    cout << "Mensaje descifrado: " << descifrado << "\n";

    return 0;
}
