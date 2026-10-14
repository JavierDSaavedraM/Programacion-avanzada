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
#include <utility>
#include <string>
#include <climits>
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

int calcularResultado(ArbolBinario AB,Nodo* raiz,int valor, int k,bool valido,int casasRobadas){
    // izquierdo
    int opt1 = 0; // no lo agarra
    int opt2 = 0; // si lo agarra
    
    //derecho 
    int opt3 = 0; // no lo agarra
    int opt4 = 0; // si lo agarra
    // pregunto si es que agarro el actual o no
    
    // digamos que es que no agarro el nodo actual 
    if (raiz->izquierdo != nullptr) {
        // no lo añade 
        opt1 = opt1 + calcularResultado(AB,raiz->izquierdo,valor,k,true,casasRobadas);
        // si lo añade
        if (valido == true) {
            opt2 = opt2 + calcularResultado(AB,raiz->izquierdo,valor,k,false,casasRobadas+1);
        }
    }
    if (raiz->derecho != nullptr) {
        // no lo añade 
        opt3 = opt3 + calcularResultado(AB,raiz->derecho,valor,k,true,casasRobadas);
        // si lo añade
        if (valido == true) {
            opt4 = opt4 + calcularResultado(AB,raiz->derecho,valor,k,false,casasRobadas+1);
        }
    }
    if (raiz->derecho == nullptr and raiz->izquierdo == nullptr){
        if (valido){
            casasRobadas++;
            if (k > casasRobadas + 1) {
                return INT_MIN;
            }
            return raiz->dato;
        }
        if (k > casasRobadas){
            return INT_MIN;
        }
        return 0;
    }
    
    int noAgarro = INT_MIN;
    if (opt1 != INT_MIN and opt3 != INT_MIN) {
        noAgarro = opt1 + opt3;
    }
    
    if (valido == false) {
        return noAgarro;
    }

    int agarro = INT_MIN;
    if (opt2 != INT_MIN and opt4 != INT_MIN) {
        agarro = raiz->dato + opt2 + opt4;
    }
    
    if (noAgarro > agarro) {
        return noAgarro;
    } else {return agarro;}
    
}

int calcularResultado(ArbolBinario AB,int k){
    Nodo* nodo = AB.raiz;
    return calcularResultado(AB,nodo,0,k,true,0);
}

void crearArbol(vector<string>&arbolito,int k){
    ArbolBinario AB;
    AB.raiz = AB.crearArbol(arbolito,0);

    AB.inorderRecursivo(AB.raiz);


    int resultado = calcularResultado(AB,k);
    if (resultado > 0){
        cout << "\n" <<resultado << endl;
    } else {cout << "\nNo se puede resolver el problema" << endl;}
    
    
}


int main(){
    vector<pair<vector<string>,int>> ejemplos = {{{"3","2","3","null","3","null","1"},2},{{"3", "4", "5", "1", "3", "null", "1"},4},{{"1","2","3"},2},{{"4","1","null","2","null","3"},3},{{"2","1","3","null","4"},2},{{"3","1","null","null","2"},2}};
    for (int i = 0; i < ejemplos.size(); i++) {
        cout << "Caso numero " << i+1 << endl;
        crearArbol(ejemplos[i].first,ejemplos[i].second);
    }
    return 0;
}
