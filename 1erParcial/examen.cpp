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

int juego(string tablero,string mano){
    int contr,conty,contb,contg,contw,contn;
    contr = conty = contb = contg = contw = contn = 0;
    for (int i = 0; i < tablero.size(); i++) {
        char color = tablero[i];
        if (color == 'r'){
            contr++;
        } else if (color == 'y'){
            conty++;
        } else if (color == 'b'){
            contb++;
        } else if (color == 'g'){
            contg++;
        } else if (color == 'w'){
            contw++;
        } else if (color == 'n'){
            contn++;
        }
    }
    for (int i = 0; i < mano.size(); i++) {
        char color = mano[i];
        if (color == 'r'){
            contr++;
        } else if (color == 'y'){
            conty++;
        } else if (color == 'b'){
            contb++;
        } else if (color == 'g'){
            contg++;
        } else if (color == 'w'){
            contw++;
        } else if (color == 'n'){
            contn++;
        }
    }
    if (0 < contg and contg < 3) {
        return -1;
    } else {
        return 0;
    }
    
    int numMin = mano.size();



}

void calculo(string &tablero){
    char color = tablero[0];
    int contador = 1;
    for (int i = 1; i < tablero.size(); i++) {
        char act = tablero[i];
        if (act == color){
            contador++;
        } else {
            if (contador >= 3) {
                tablero.erase(i-contador, contador);
                i = 0;
                act=tablero[0];
            }
            contador=1;
            color = act;
        }   
        if (i==tablero.size()-1 and contador >= 3) {
            tablero.erase(i-contador+1,contador);
        }
    }
}



int main(){
    vector<string> tableros{"rr","gggrrr","rbb","wwrrbbww","bbyyrrbb","bbwwrrwwbb","wgrrbbyyw","rybwg","rrwwbbyyggrr","rrwybwrr"};  
    vector<string> manos{"r","rrgg","rrbb","wrbrw","byr","wrb","wbgry","rryybbwwgg","gybwgybw","wwyybbw"}; 
    
    /*
    for (int i = 0; i < tableros.size(); i++) {
        if (juego(tableros[i],manos[i]) == -1) {
            cout << "El tablero " << i+1 << " no tiene solucion" << endl;
        } else
        {
            cout << "Tablero: " << tableros[i] << endl;
        }
        
    }*/
    calculo(tableros[1]);
    cout << "Return: " << tableros[1] << endl;
    
    return 0;
}
