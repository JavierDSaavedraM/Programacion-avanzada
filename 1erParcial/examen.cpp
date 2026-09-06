/*
Nombres:
Sergio Alejandro Zamora Dávila 616148
Javi Djorkaef 624198
Roberto De la Fuente 593303

Damos nuestra palabra que hemos realizado esta actividad con integridad académica
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

// COUT PARA DEBUG
#ifdef DEBUG
#define LOG_DEBUG(msg) cout << "[DEBUG]" << msg << endl;
#else
#define LOG_DEBUG(msg)
#endif

// Funcion que obtiene un string  
string eliminar_combo(string _tablero){
    string tablero = _tablero;
    bool cambio = false;
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
                cambio = true;
            }
            contador=1;
            color = act;
        }   
        if (i==tablero.size()-1 and contador > 2) {
            tablero.erase(i-contador+1,contador);
            cambio = true;
        }
    }
    return tablero;
}

unordered_set<string> valores_anteriores;
// Solo añade cuando un color en la mano es igual al del tablero 
vector<size_t> obtenerPosValidas(string _t, char _c){
    string tablero_actual = _t;
    char color_actual = _c;

    vector<size_t> pos_validas;
    

    for (size_t pos = 0; pos <= tablero_actual.size(); pos++){
        if (color_actual == tablero_actual[pos]) {
            string nuevo_tablero = tablero_actual;
            nuevo_tablero.insert(pos,1,color_actual);

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
    if(tablero.empty()) return mano.size();
    if(mano.empty()) return -1;
    string estado_actual = tablero + "#" + mano;
    if(estados_visitados.find(estado_actual) != estados_visitados.end()){
        return estados_visitados[estado_actual]; 
    }
    int mejor_mano = -1;
    for (size_t color = 0 ; color < mano.size() ; color++){
        if(color > 0 && mano[color] == mano[color-1]){
            continue;
        }
        vector<size_t> pos_validas = obtenerPosValidas(tablero, mano[color]);
        for (size_t espacio_tablero = 0; espacio_tablero < pos_validas.size(); espacio_tablero++){
            string nuevo_tablero = tablero;
            string nueva_mano = mano;
            nuevo_tablero.insert(pos_validas[espacio_tablero],1, mano[color]);
            nuevo_tablero = eliminar_combo(nuevo_tablero);
            nueva_mano.erase(color, 1);
            int resultado_hojas = resolver(nuevo_tablero, nueva_mano);
            LOG_DEBUG(estado_actual << "/" << nuevo_tablero << "#" << nueva_mano << "/" << resultado_hojas);
            if (resultado_hojas != -1){
                mejor_mano = max(mejor_mano, resultado_hojas);
            }
        }
    }
    estados_visitados[estado_actual] = mejor_mano;
    return mejor_mano;
}

//voy revisando cada color del tablero y hago 2 cosas, o le meto uno de ese color o no 

int main(){
    vector<string> tableros{"rr","rg","rbb","wwrrbbww","bbyyrrbb","bbwwrrwwbb","wgrrbbyyw","rybwg","rrwwbbyyggrr","rrwybwrr"};  
    vector<string> manos{"r","rrgg","rrbb","wrbrw","byr","wrb","wbgry","rryybbwwgg","gybwgybw","wwyybbw"};     

    for(size_t i= 0; i < tableros.size(); i++){
        string board = tableros.at(i);
        string hand = manos.at(i);
        cout << board << "/"<< hand << " " << 
            resolver(board, hand) << endl;
    }
    
    return 0;
}
