/*
Nombres:
Sergio Alejandro Zamora Dávila 616148
Javi Djorkaef 624198
Roberto De la Fuente 593303
*/

#include <algorithm>
#include <iostream>
#include <stdexcept>
#include <unordered_map>
#include <string>
#include <stack>
#include <unordered_map>
#include <utility>
#include <vector>
#include <cmath>

using namespace std;

// Bandera de Debugging
#ifdef DEBUG
#define LOG_DEBUG(msg) cout << "[DEBUG]" << msg << endl;
#else
#define LOG_DEBUG(msg)
#endif

// Constante que tiene todos los caracteres validos para el cifrado
const string ALPHABETO = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";

// Suma las posiciones de las letras para obtener la rotacion del mensaje.
int calcularRotacion(string mensaje) {
    int valor = 0;
    for (int i = 0; i < mensaje.size(); i++) {
        valor = valor + ALPHABETO.find(mensaje[i]); 
    }
    return valor;
}

// Combina dos partes al sumar la posicion de sus letras.
string combinar(string pt1, string pt2){
    for (int i = 0; i < pt1.size(); i++) {
        int nuevo = ALPHABETO.find(pt1[i]) + ALPHABETO.find(pt2[i]); 
        while (nuevo > 25) { // Como un reloj, regresar al inicio cuando se acaba el alphabeto.
            nuevo = nuevo - 26;
        }
        pt1[i] = ALPHABETO[nuevo];
    }
    return pt1;
}

// Mueve cada letra la cantidad de posiciones de la rotacion.
string rotarMensaje(string mensaje, int rotacion){
    string nuevoMensaje;
    for (size_t i = 0; i < mensaje.size(); i++) {
        int nuevo = ALPHABETO.find(mensaje[i]) + rotacion;
        while (nuevo > 25) { // Como un reloj, regresar al inicio cuando se acaba el alphabeto.
            nuevo = nuevo - 26;
        }
        mensaje[i] = ALPHABETO[nuevo];
    }
    return mensaje;
}

// Divide el mensaje, rota ambas partes y luego las combina para descifrarlo.
string descifrar(string mensaje){
    int largo = mensaje.length();

    // Dividir
    string pt1 = mensaje.substr(0, largo/2); 
    string pt2 = mensaje.substr(largo/2); 

    // Rotar
    pt1 = rotarMensaje(pt1,calcularRotacion(pt1));
    pt2 = rotarMensaje(pt2,calcularRotacion(pt2));
    
    // Combinar
    return combinar(pt1,pt2);
}


int main(){
    try {
        int casos; 
        string mensaje;
        cout << "Cantidad de casos: ";
        cin >> casos;

        if (casos <= 0) { // Debe de ver algun mensaje
            cout << "Nada? Okay bye";
            return 0;
        }

        for (int i = 0; i < casos; i++) {
            cout << "------------------------- (" << i << "/" << casos << ")" << endl;
            cout << "Mensaje " << i + 1 << ": ";
            cin >> mensaje;
            cout << "Descifrado "<< i + 1<< ": " << descifrar(mensaje) << endl;
        }
    } catch (const exception& error) { // Muestra el motivo del error sin terminar el programa de forma inesperada.
        cerr << "Error: " << error.what() << endl;
        return 1;
    }
    return 0;
}
