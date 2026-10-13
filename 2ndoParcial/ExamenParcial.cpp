/*
Nombres:
Sergio Alejandro Zamora Dávila 616148
Javi Djorkaef 624198
Roberto De la Fuente 593303
*/

#include <iostream>
#include <queue>
#include <vector>
#include <string>
using namespace std;

// Definición de la estructura del nodo
struct Nodo {
    int dato,id;
    Nodo* izquierdo;
    Nodo* derecho;

    // Constructor
    Nodo(int val) {
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

    Nodo* crearArbol(const vector<string>& arbolito, int indice) {
        if (indice >= arbolito.size() or arbolito[indice] == "null"){
            return nullptr;
        }
        Nodo* nodo = new Nodo(stoi(arbolito[indice])); 
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

int calcularResultado(ArbolBinario AB,Nodo* raiz,int valor, int k,bool valido){
    // izquierdo
    int opt1 = valor; // no lo agarra
    int opt2 = valor; // si lo agarra
    
    //derecho 
    int opt3 = valor; // no lo agarra
    int opt4 = valor; // si lo agarra
    // pregunto si es que agarro el actual o no
    
    // digamos que es que no agarro el nodo actual 
    if (raiz->izquierdo != nullptr) {
        // no lo añade 
        opt1 = calcularResultado(AB,raiz->izquierdo,valor,k,true);
        // si lo añade
        if (valido == true) {
            opt2 = calcularResultado(AB,raiz->izquierdo,valor+raiz->dato,k-1,false);
        }        
    }
    if (raiz->derecho != nullptr) {
        // no lo añade 
        opt3 = calcularResultado(AB,raiz->derecho,valor,k,true);
        // si lo añade
        if (valido == true) {
            opt4 = calcularResultado(AB,raiz->derecho,valor+raiz->dato,k-1,false);
        }
    }
    if (raiz->derecho == nullptr and raiz->izquierdo == nullptr){
        if (valido){
            k--;
            if (k > 0) {
                return 0;
            }
            return valor + raiz->dato;
        }
        if (k > 0) {
            return 0;
        }
        return valor;        
    }
    
    
    if ((opt1 + opt3 - valor) > (opt2 + opt4 - raiz->dato - valor)) {
        return (opt1 + opt3 - valor);
    } else {return (opt2 + opt4 - raiz->dato - valor);}
}

int calcularResultado(ArbolBinario AB,int k){
    Nodo* nodo = AB.raiz;
    return calcularResultado(AB,nodo,0,k,true);
}

void crearArbol(vector<string>&arbolito,int k){
    ArbolBinario AB;
    AB.raiz = AB.crearArbol(arbolito,0);

    AB.inorderRecursivo(AB.raiz);
    cout << endl <<calcularResultado(AB,k) << endl;
}


int main(){
    // guardar la posicion de cada valor como si fuera su ID
    vector<string> raiz = {"3","2","3","null","3","null","1"};
    int k = 2;

    vector<string> ej2 = {"3", "4", "5", "1", "3", "null", "1"};
    int l = 4;
    crearArbol(raiz,k);
    crearArbol(ej2,l);
    // (n+1)*2
    return 0;
}
