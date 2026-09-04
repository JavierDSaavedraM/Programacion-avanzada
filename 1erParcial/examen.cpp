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

using namespace std; 

bool calculo(string &tablero){
    bool cambio = false;
    if (tablero.empty()) return false;
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
    return cambio;
}


int juego(string& tablero,string& mano){
    if (tablero.empty()) return 1;
    if (mano.empty()) return 0;
    
    for (size_t i = 0; i < mano.size(); i++) {
        for (size_t j = 0; j < tablero.size(); j++) {
            string tableroAct = tablero;
            string manoAct = mano;

            tableroAct.insert(j,1,manoAct[i]);
            manoAct.erase(i,1);
            calculo(tableroAct);
            
            if (juego(tableroAct,manoAct) == 1) {
                return 1;
            }
        }
    }
}

//voy revisando cada color del tablero y hago 2 cosas, o le meto uno de ese color o no 

int juego2(string& tablero,string& mano){
    if (tablero.empty()) return mano.size();
    if (mano.empty()) return 9999;
    
    int mejorCaso = 9999; 
    for (size_t i = 0; i < tablero.size(); i++) {
        for (size_t j = 0; j < mano.size(); j++) {
            if (mano[j] == tablero[i]) {
                // pruebo si lo meto y no 
                string tableroAct = tablero;
                string manoAct = mano;

                tableroAct.insert(i,1,manoAct[j]);
                manoAct.erase(j,1);
                calculo(tableroAct);

                int intento = juego2(tableroAct,manoAct);
                if (intento > mejorCaso) {
                    mejorCaso = intento;
                }
            }
        }
    }
}

int main(){
    vector<string> tableros{"rr","rg","rbb","wwrrbbww","bbyyrrbb","bbwwrrwwbb","wgrrbbyyw","rybwg","rrwwbbyyggrr","rrwybwrr"};  
    vector<string> manos{"r","rrgg","rrbb","wrbrw","byr","wrb","wbgry","rryybbwwgg","gybwgybw","wwyybbw"};     
    
    for (int i = 0; i < tableros.size(); i++) {
        cout << "tablero numero " << i+1 << " :" << endl;
        cout << "numero de colores restantes: " << juego2(tableros[i],manos[i]) << endl;
    }

    return 0;
}
