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

int calcularRotacion(string mensaje){
    int valor = 0;
    for (int i = 0; i < mensaje.size(); i++) {
        valor = valor + ALPHABETO.find(mensaje[i]); 
    }
    return valor;
}

string combinar(string pt1, string pt2){
    for (int i = 0; i < pt1.size(); i++) {
        int nuevo = ALPHABETO.find(pt1[i]) + ALPHABETO.find(pt2[i]); 
        while (nuevo > 25) {
            nuevo = nuevo - 26;
        }
        pt1[i] = ALPHABETO[nuevo];
    }
    return pt1;
}

string rotarMensaje(string mensaje, int rotacion){
    string nuevoMensaje;
    for (size_t i = 0; i < mensaje.size(); i++) {
        int nuevo = ALPHABETO.find(mensaje[i]) + rotacion;
        while (nuevo > 25) {
            nuevo = nuevo - 26;
        }
        mensaje[i] = ALPHABETO[nuevo];
    }
    return mensaje;
}

string descifrar(string mensaje){
    int largo = mensaje.length();

    string pt1 = mensaje.substr(0, largo/2); 
    string pt2 = mensaje.substr(largo/2); 

    pt1 = rotarMensaje(pt1,calcularRotacion(pt1));
    pt2 = rotarMensaje(pt2,calcularRotacion(pt2));
    
    return combinar(pt1,pt2);
}


int main(){
    int casos; 
    string mensaje;
    cin >> casos;
    for (int i = 0; i < casos; i++) {
        cin >> mensaje;
        cout << descifrar(mensaje) << endl;
    }
    return 0;
}
