/*
Nombres:
Sergio Alejandro Zamora Dávila 616148
Javi Djorkaef 624198
Roberto De la Fuente 593303
*/

#include <iostream>
#include <queue>
using namespace std;

// Definición de la estructura del nodo
struct Nodo {
    int dato,id;
    Nodo* izquierdo;
    Nodo* derecho;

    // Constructor
    Nodo(int val, int ID) {
        dato = val;
        id = ID;
        izquierdo = nullptr;
        derecho = nullptr;
    }
};

class ArbolBinario {
public:
    Nodo* raiz;

    ArbolBinario() {
        raiz = nullptr;
    }

    Nodo* crearArbol(const vector<string>& arbolito, int indice) {
        if (indice >= arbolito.size() or arbolito[indice] == "null"){
            return nullptr;
        }
        Nodo* nodo = new Nodo(stoi(arbolito[indice]),indice); 
        nodo->izquierdo= crearArbol(arbolito,2*indice+1);
        nodo->derecho= crearArbol(arbolito,2*indice+2);
        return nodo;
    }

    void inorderRecursivo(Nodo* raiz) {
        if (raiz == nullptr) {
            return;
        }
        inorderRecursivo(raiz->izquierdo); // 1. Izquierda
        cout << raiz->dato << " ";    // 2. Raíz (Procesar)
        inorderRecursivo(raiz->derecho);   // 3. Derecha
    }

};

void crearArbol(vector<string>&arbolito){
    ArbolBinario AB;
    AB.raiz = AB.crearArbol(arbolito,0);

    AB.inorderRecursivo(AB.raiz);
}


int main(){
    // guardar la posicion de cada valor como si fuera su ID
    vector<string> raiz = {"3","2","3","null","3","null","1"};
    crearArbol(raiz);
    // (n+1)*2
    return 0;
}
