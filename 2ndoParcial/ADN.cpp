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

class TablaHash{
private:
  int capacidad;
  vector<list<pair<string,int>>> TABLA;
  int generadorHash(const string valor){
    int clave = 0;
    for(int i=0; i < valor.length(); i++){
      clave = clave * 31 * valor[i];
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
};


vector<string> prueba;
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
    prueba.push_back(nuevo);
  }
}

int main(){
  vector<string> secuencias = {"AAAAACCCCCAAAAACCCCCCAAAAAGGGTTT","AAAAAAAAAAAAA"};
/*
  string secuencia;
  cout << "Dame la secuencia: ";
  cin >> secuencia;
*/


  obtenerCombinaciones(secuencias[0]);

  for (size_t i = 0; i < prueba.size(); i++) {
    cout << prueba[i] << endl;
  }
  



  /*

  TablaHash MiTabla(5);
  MiTabla.put("usuario1","ana");
  MiTabla.put("usuario2","pedro");
  MiTabla.put("usuario3","carlos");
  MiTabla.put("NegritoOjoClaro","Ozuna");
  MiTabla.put("Luffy","Rey de los piratas");

  cout << "Buscar: usuario2" << MiTabla.get("usuario2") << endl;*/
  return 0;
}
