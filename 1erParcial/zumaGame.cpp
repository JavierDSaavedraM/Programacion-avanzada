/*
Nombres:
Sergio Alejandro Zamora Dávila 616148
Javi Djorkaef 624198
Roberto De la Fuente 593303

Nosotros damos nuestra palabra que hemos realizado esta examen con integridad académica.
*/

#include <cstddef>
#include <fstream>
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <cmath>
#include <chrono>
#include <unordered_map>
#include <unordered_set>

using namespace std; 

// Bandera de Debugging
#ifdef DEBUG
#define LOG_DEBUG(msg) cout << "[DEBUG]" << msg << endl;
#else
#define LOG_DEBUG(msg)
#endif

// Funcion que elimina cuando en el tablero existen combos de 3 colores o mas
// @input: Recibe una copia del tablero para manipularlo
// @output: Envia una version del tablero modificado o no.
string eliminar_combo(string _tablero){
    string tablero = _tablero;
    if (tablero.empty()) return "";
    char color = tablero[0];
    int contador = 1;
    for (size_t i = 1; i < tablero.size(); i++) {
        char act = tablero[i];
        if (act == color){
            contador++;
        } else {
            if (contador > 2) {
                tablero.erase(i-contador, contador);
                i = 0;
                act=tablero[0];
            }
            contador=1;
            color = act;
        }   
        if (i==tablero.size()-1 && contador > 2) {
            tablero.erase(i-contador+1,contador);
        }
    }
    return tablero;
}

// Funcion que obtiene las posiciones donde vale la pena insertar un color.
// @input: string del tablero actual (_t) y el caracter del color que quieres insertar (_c)
// @output: regresa una lista con posiciones validas para insertar.
vector<size_t> obtenerPosValidas(string& _tablero, char _color){
    vector<size_t> pos_validas; 
    unordered_set<string> valores_anteriores;
    for (size_t pos = 0; pos <= _tablero.size(); pos++){
        // Solamente inserta cuando existe el valor en el tablero
        if (_color == _tablero[pos]) {
            string nuevo_tablero = _tablero;
            nuevo_tablero.insert(pos,1,_color);
            if(valores_anteriores.find(nuevo_tablero) == valores_anteriores.end()){
                valores_anteriores.insert(nuevo_tablero);
                pos_validas.push_back(pos);
            }
        }
    }
    return pos_validas;
}

// Sirve para memoizar los estados ya visitados y prunar ramas inecesarias.
unordered_map<string, int> estados_visitados;
// Funcion recursiva que genera todos los posibles inserciones
// @input: toma como parametros una copia del tablero (_t) y de la mano (_m)
// @output: regresa el numero maximo de colores restantes
int resolver(string _t, string _m){
    string tablero = eliminar_combo(_t);
    string mano = _m;
    sort(mano.begin(), mano.end());
    // Casos Base
    if(tablero.empty()) return mano.size();
    if(mano.empty()) return -1;
    // Obtener una llave para el hash map
    string estado_actual = tablero + "#" + mano;
    if(estados_visitados.find(estado_actual) != estados_visitados.end()){
        return estados_visitados[estado_actual]; 
    }
    int mejor_mano = -1; // Inicializar limite inferior o no solucion
    // Revisa cada color del dentro del tablero
    for (size_t color = 0 ; color < mano.size() ; color++){
        // Solo revisa colores que no se hayan visto antes para que no se repitan casos
        if(color > 0 && mano[color] == mano[color-1]){
            continue;
        }
        // Itera las posiciones validas
        vector<size_t> pos_validas = obtenerPosValidas(tablero, mano[color]);
        for (size_t espacio_tablero = 0; espacio_tablero < pos_validas.size(); espacio_tablero++){
            string nuevo_tablero = tablero;
            string nueva_mano = mano;
            nuevo_tablero.insert(pos_validas[espacio_tablero],1, mano[color]);
            nuevo_tablero = eliminar_combo(nuevo_tablero);
            nueva_mano.erase(color, 1);
            int resultado_hojas = resolver(nuevo_tablero, nueva_mano); // Llamada recusiva que 
            LOG_DEBUG(estado_actual << "/" << nuevo_tablero << "#" << nueva_mano << "/" << resultado_hojas);
            // Si no hay una solucion valida revisar cuales el mejor de las hojas o a la actual
            if (resultado_hojas != -1){
                mejor_mano = max(mejor_mano, resultado_hojas);
            }
        }
    }
    // Ingresa el estado al hashmap con su solucion para memoizacion
    estados_visitados[estado_actual] = mejor_mano;
    return mejor_mano;
}

string obtenerTiempoDeEjecucion(string _b, string _h){
    estados_visitados = {};
    auto init_time = chrono::high_resolution_clock::now();
    resolver(_b,_h);
    auto end_time = chrono::high_resolution_clock::now();
    chrono::duration<double, milli> tiempo_ejecucion = end_time - init_time;
  return std::to_string(tiempo_ejecucion.count());
};

void escribirArchivoCSV(vector<string> & _b, vector<string> &_h){
    const int num_repeticiones = 31;
    vector<vector<string>> resultados(_b.size(), vector<string>(num_repeticiones));

    // Obtener todas las iteraciones por el input
    for (size_t i = 0; i < _b.size();i++){
        for (size_t j = 0; j < num_repeticiones; ++j){
            resultados[i][j] = obtenerTiempoDeEjecucion(_b[i], _h[i]);
        }
    } 

    ofstream  archivo_csv("zumaResultados.csv");

    if(!archivo_csv.is_open()){
        throw runtime_error("No se pudo abrir el archivo");
    }
    string linea;

    // Imprimir header
    for(size_t i = 0; i< _h.size(); i++){
        linea += _b[i] + "#" + _h[i];
        if(i+1 < _h.size())
            linea += ",";
    }
    archivo_csv << linea << endl;

    // Guardar verticalmente
    for (size_t i = 0; i< num_repeticiones; i++){
        linea = "";
        for (int j = 0; j < _h.size(); j++){
            linea += resultados[j][i];
            if (j + 1 < _h.size())
                linea += ",";
        }
        archivo_csv << linea << endl;
    }
    archivo_csv.close();
}


int main(){
    try{
        vector<string> tableros{"rr","rg","rbb","wwrrbbww","bbyyrrbb","bbwwrrwwbb","wgrrbbyyw","rybwg","rrwwbbyyggrr","rrwybwrr"};  
        vector<string> manos{"r","rrgg","rrbb","wrbrw","byr","wrb","wbgry","rryybbwwgg","gybwgybw","wwyybbw"};     
  //      escribirArchivoCSV(tableros, manos);
        for(size_t i= 0; i < tableros.size(); i++){
            string board = tableros[i];
            string hand = manos[i];
            estados_visitados = {};
            cout << board << "/"<< hand << " " << 
                resolver(board, hand) << endl;
        }

    } catch (const runtime_error& e) {
        cout << "Error: " << e.what() << endl;
    }

    return 0;
}
