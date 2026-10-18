/*
Nombres:
Sergio Alejandro Zamora Dávila 616148
Javi Djorkaef 624198
Roberto De la Fuente 593303
*/

#include <iostream>
#include <algorithm>
#include <queue>
#include <vector>
#include <string>
#include <utility>
#include <chrono>
using namespace std;

// Definición de la estructura del nodo
struct Nodo {
    int dato;
    Nodo* izquierdo;
    Nodo* derecho;

    // Constructor
    Nodo(int val) {
        dato = val;
        izquierdo = nullptr;
        derecho = nullptr;
    }
};

// Clase que guarda el arbol binario a partir de su raiz
class ArbolBinario {
public:
    Nodo* raiz;

    // Constructor de la clase, el arbol empieza vacio
    ArbolBinario() {
        raiz = nullptr;
    }

    // Esta funcion construye el arbol por niveles usando una cola 
    // @input: arbolito: vector con los valores del arbol, "null" si no hay nodo
    // @output: apuntador a la raiz del arbol construido
    Nodo* crearArbol(const vector<string>& arbolito) {
        if(arbolito.empty() || arbolito[0] == "null") return nullptr; // validacion: arbol vacio
        Nodo* raiz = new Nodo(stoi(arbolito[0]));
        queue<Nodo *> q;
        q.push(raiz);
        int i =1; // posicion del siguiente valor por leer en el vector
        while(!q.empty() && i < arbolito.size()){
            Nodo* cur = q.front();
            q.pop();
            if(i < arbolito.size()){
                if(arbolito[i] !="null"){
                    cur->izquierdo = new Nodo(stoi(arbolito[i]));
                    q.push(cur->izquierdo);
                };
                i++;
            }
            if(i < arbolito.size()){
                if(arbolito[i] !="null"){
                    cur->derecho = new Nodo(stoi(arbolito[i]));
                    q.push(cur->derecho);
                };
                i++;
            }
        }
        return raiz;
    }
};

// Funcion wrapper para llamar construir el arbol
// @input: arbolito: Un vector con los valores del arbol
// @output: un instancia de la clase arbol con el arbol construido
ArbolBinario crearArbol(vector<string>&arbolito){
    ArbolBinario AB;
    AB.raiz = AB.crearArbol(arbolito);
    return AB;
}

// Funcion para combinar los resultados del subarbol izquierdo y derecho
// @input:
// - A: vector donde la posicion i es el maximo dinero robando i casas (izquierda)
// - B: lo mismo para el subarbol derecho
// - k: minimo de casas, las posiciones mayores a k se juntan en k
// @output: vector con el mejor dinero para cada numero de casas combinado
vector<int> combinar(const vector<int> &_A,const vector<int> &_B, int _k ){
    int A = _A.size(), B = _B.size();
    int n = min(A + B - 2, _k) + 1;
    vector<int> combinado(n, -1);
    for(int i= 0; i < A; i++){
        if (_A[i] == -1){continue;}; // -1 significa que esa cantidad de casas no es posible
        for (int j=0; j< B; j++){
            if (_B[j] == -1){continue;};
            int t = min(_k,i+j);  // total de casas, topado en k
            combinado[t] = max(combinado[t], _A[i] + _B[j]);
        }
    }
    return combinado;
}

//Funcion que se encarga de elegir cual es la mejor combinacion dado dos arreglos
//@input: 
//- nr: vector con valores que toma cuando se salta el nodo actual
//- r: vector con valores que toma cuando se roba el nodo actual
//@output: vector con el mejor valor de cada posicion entre robar y no robar
vector<int> optimizarRuta(vector<int> &_nr, vector<int>& _r){
    int nr = _nr.size();
    int r = _r.size();
    int n = max(nr,r);
    vector<int> ruta_optimizada(n,-1);
    for(int i = 0; i < n; i++){
        int a = (i < nr) ? _nr[i]: -1;
        int b = (i < r) ? _r[i]: -1;
        ruta_optimizada[i] = max(a,b);
    }
    return ruta_optimizada;
}

// Guarda los resultados de un nodo:
// - nr: mejor dinero por numero de casas si NO se roba el nodo
// - r: mejor dinero por numero de casas si SI se roba el nodo
struct solucion{
    vector<int> nr;
    vector<int> r;
};

// Recorre el arbol en postorden y calcula la solucion de cada nodo
// @input: n: nodo actual, k: minimo de casas
// @output: solucion con los vectores nr y r del nodo
solucion DFS(Nodo * n, int k){
    if(n == nullptr) {return {{0}, {-1}};}; // caso base: nodo vacio, 0 casas con 0 dinero

    solucion izq = DFS(n->izquierdo, k);
    solucion der = DFS(n->derecho, k);

    solucion actual;
    // saltarse el nodo actual
    actual.nr = combinar(optimizarRuta(izq.nr, izq.r), optimizarRuta(der.nr,der.r),k);
    // robar el nodo actual
    vector<int> m = combinar(izq.nr, der.nr,k);
    actual.r.assign(min((int)m.size(), k) + 1, -1); // si se roba el nodo actual, sus hijos no se pueden robar 

    for (int i = 0; i < (int)m.size(); i++){
        if (m[i] != -1){
            int t = min(k,i+1);
            actual.r[t] = max(actual.r[t], m[i] + n->dato);
        }
    }
    return actual;
}

// Calcula e imprime el maximo dinero robando al menos k casas
// @input: raiz: raiz del arbol, k: minimo de casas
void resolver(Nodo * raiz, int k ){
    solucion s = DFS(raiz, k);
    int a = (k < s.nr.size()) ? s.nr[k] : -1;
    int b = (k < s.r.size()) ? s.r[k] : -1;
    int resultado = max(a,b); // mejor opcion entre robar o no la raiz  
    if (resultado == -1){   // validacion: no hay forma de robar k casas
        cout << "No se pueden robar al menos " << k << " casas en este problema" << endl;
    } else {cout << "El resultado es:  " << resultado << endl;}
}

int main(){
    // Casos de prueba: {arbol, k}      
    vector<pair<vector<string>,int>> ejemplos = {
        {{"3","2","3","null","3","null","1"},2}, //Caso 1
        {{"3", "4", "5", "1", "3", "null", "1"},4}, //Caso 2
        {{"1","2","3"},2}, //caso 3
        {{"4","1","null","2","null","3"},3}, //caso 4
        {{"2","1","3","null","4"},2}, //caso 5
        {{"3","1","null","null","2"},2}, //caso 6
        {{"10","1","2","3","4","null","null","5","6"},5}, //caso 7
        {{"1","2","3","4","5","6","7","8","9","10","11","12","13","14","15"},8} //caso 8
    };
    // Caso 9: lista de 1,000 nodos hacia la derecha -> [1, null, 2, null, 3, ..., 1000]
    vector<string> caso9;
    for (int i = 1; i < 1001; i++) {
        caso9.push_back(to_string(i));
        if (i != 1000){
            caso9.push_back("null");
        }
    }
    ejemplos.push_back({caso9, 500});

    // Caso 10: árbol completo de 10,000 nodos, todos con valor 1
    vector<string> caso10(10000, "1");
    ejemplos.push_back({caso10, 5000});

    for (int i = 0; i < ejemplos.size(); i++) {
        cout << "Caso numero " << i+1 << " ";
        ArbolBinario AB = crearArbol(ejemplos[i].first);
        // Se mide solo el tiempo del algoritmo, sin contar la construccion del arbol 
        auto inicio = chrono::high_resolution_clock::now();
        resolver(AB.raiz, ejemplos[i].second);
        auto fin = chrono::high_resolution_clock::now();

        auto duracion = chrono::duration_cast<chrono::microseconds>(fin - inicio);
        cout << "Tiempo: " << duracion.count() << " microsegundos" << endl;
    }

    return 0;
}
