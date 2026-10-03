/*
Nombres:
Sergio Alejandro Zamora Dávila 616148
Javi Djorkaef 624198
Roberto De la Fuente 593303
*/

#include <iostream>
#include <string>
#include <vector>
#include <list>

using namespace std;

class TablaHash{ // Utilizamos como base el codigo visto en clase para armar nuestra propia estructura de tabla hash
private:
  int capacidad; // Es la cantidad de datos que la tabla hash va a tener 
  vector<list<pair<string,int>>> TABLA; // Declaramos la tabla hash 
  int generadorHash(const string valor){ // Creamos nuestro propio generador de clave 
    int clave = 1;
    for(int i=0; i < valor.length(); i++){
      clave = clave * 31 * valor[i]; // Hacemos esto 
    }
    return clave;
  }
  int GetIndex(const string& clave){
    size_t hash_obtenido = generadorHash(clave);
    return hash_obtenido % capacidad;
  }

public:
  TablaHash(int capacidad_inicial = 10){
    capacidad = capacidad_inicial;
    TABLA.resize(capacidad); //
  }
  void put(const string& clave, const int& valor){
    int indice = GetIndex(clave); // Cambiar a valor numerico para no usar texto
    for(auto& par: TABLA[indice]){
        if(par.first == clave){
        par.second = valor;
      }
    }
    TABLA[indice].push_back({clave, valor});
  }
  int get(const string& clave){
    int indice = GetIndex(clave);
    for(auto& par: TABLA[indice]){
        if(par.first == clave){
        return par.second;
      }
    }
    return -1;
  }

  void sumar(const string& clave){
    int indice = GetIndex(clave);
    for(auto& par: TABLA[indice]){
        if(par.first == clave){
          par.second++;
      }
    }
  }

  void imprimir(){
    bool primero = true;
    cout << "Resultado del problema: " << endl << "[";
    for (int i = 0; i < TABLA.size(); i++) {
      for (auto& par : TABLA[i]) {
        if (par.second > 0) {
          if (primero == false) {
            cout << ", ";
          }
          cout << '"' << par.first << '"';
          primero = false;
        }
      }
    }
    cout << "]"<<endl;
  }
};


void obtenerCombinaciones(const string& secuencia) {
  TablaHash MiTabla(secuencia.size()-10);
  for (int i = 9; i < secuencia.size(); i++) {
    string nuevo = secuencia.substr(i-9,10);
    int valor = MiTabla.get(nuevo);
    if(valor == -1) {
      MiTabla.put(nuevo, 0);
    } else {
      MiTabla.sumar(nuevo);
    }
  }
  MiTabla.imprimir();
}

int main(){
  //vector<string> secuencias = {"AAAAACCCCCAAAAACCCCCCAAAAAGGGTTT","AAAAAAAAAAAAA"};
  //obtenerCombinaciones(secuencias[0]);
  //obtenerCombinaciones(secuencias[1]);
  string secuencia;
  cout << "Dame la secuencia: ";
  cin >> secuencia;
  obtenerCombinaciones(secuencia);
  return 0;
}
