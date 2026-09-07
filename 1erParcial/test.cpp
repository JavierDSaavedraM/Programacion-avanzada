#include <iostream>
#include <string>

using namespace std;

int main(){
    string tablero = "rbb";
    char color_actual = 'c';

    for (size_t espacio_tablero = 0; espacio_tablero <= tablero.size(); espacio_tablero++){
        string nuevo = tablero;
        nuevo.insert(espacio_tablero,1,color_actual);
        cout << nuevo << " ";
    }
    return 0;
}
