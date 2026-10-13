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
    int dato, id;
    Nodo* izquierdo;
    Nodo* derecho;

    // Constructor
    Nodo(int val,int ID) {
        id = ID;
        dato = val;
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

    // Función para buscar un nodo por su valor (para saber dónde insertar)
    Nodo* buscar(Nodo* actual, int idBuscado) {
        if (actual == nullptr) return nullptr;
        if (actual->id == idBuscado) return actual;

        Nodo* encontrado = buscar(actual->izquierdo, idBuscado);
        if (encontrado != nullptr) return encontrado;

        return buscar(actual->derecho, idBuscado);
    }

    // Función para insertar un hijo especificando el padre y el lado ('I' para izquierdo, 'D' para derecho)
    bool insertarHijo(int idPadre, int idHijo, int valorNuevoHijo, char lado) {
        // Si el árbol está vacío, se crea como raíz
        if (raiz == nullptr) {
            raiz = new Nodo(valorNuevoHijo, idHijo);
            return true;
        }

        // Buscar el nodo padre
        Nodo* padre = buscar(raiz, idPadre);
        if (padre == nullptr) {
            cout << "No se encontró el nodo padre con valor: " << idPadre << endl;
            return false;
        }

        // Insertar según el lado especificado
        if (lado == 'I' || lado == 'i') {
            if (padre->izquierdo == nullptr) {
                padre->izquierdo = new Nodo(valorNuevoHijo, idHijo);
                return true;
            } else {
                cout << "El nodo padre ya tiene un hijo izquierdo." << endl;
                return false;
            }
        } else if (lado == 'D' || lado == 'd') {
            if (padre->derecho == nullptr) {
                padre->derecho = new Nodo(valorNuevoHijo,idHijo);
                return true;
            } else {
                cout << "El nodo padre ya tiene un hijo derecho." << endl;
                return false;
            }
        }

        return false;
    }
};

void crearArbol(vector<string>&arbolito){
    ArbolBinario AB;
    AB.insertarHijo(0,0,stoi(arbolito[0]),'i');
    for (int i = 0; i < arbolito.size(); i++){
        AB.insertarHijo(0,i,stoi(arbolito[i]),'i');
        i++;
        AB.insertarHijo(0,i,stoi(arbolito[i]),'d');
    }
}

int main(){
    // guardar la posicion de cada valor como si fuera su ID
    vector<string> raiz = {"3","2","3","null","3","null","1"};
    crearArbol(raiz);
    // (n+1)*2
    return 0;
}
