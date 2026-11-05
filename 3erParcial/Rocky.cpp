/*
Nombres:
Sergio Alejandro Zamora Dávila 616148
Javi Djorkaef 624198
Roberto De la Fuente 593303
*/

#include <iostream>
#include <string>
#include <vector>
using namespace std;

void probar(const vector<int>& stones) {
    int n = stones.size();
    int total = 0;
    bool negative_switch = false;
    bool decimal_switch = false;
    for (int stone : stones) {
        cout << stone << " ";
        total += stone;

        if (stone < 0) negative_switch = true; // Illegal number
        else if (stone % 1 != 0) decimal_switch = true; // Illegal number
    }
    if (negative_switch) {
        cout << "-> Algun numero es negativo" << endl;
        return;
    } else if (decimal_switch) {
        cout << " -> Algun numero no es entero" << endl;
        return;
    }

    if (n == 0)                 cout << "-> Falso por lista vacia" << endl; 
    else if (n % 2 == 1)        cout << "-> Falso por numero impar de grupos de piedras (tamano = " << n << ")" << endl;
    else if (total % 2 == 0)    cout << "-> Falso por cantidad total par de piedras (total = " << total << ")" << endl;
    else                        cout << "-> Verdadero" << endl; // There will always be a strategy to win.
}

int main() {
    try {
        // Ejemplos
        probar({5, 3, 4, 5});          // Verdadero 
        probar({3, 7, 2, 3});          // Verdadero 

        // Casos de prueba
        probar({1, 2, 3, 3, 2, 1});    // Cantidad total par de piedras (debe de ser impar)
        probar({7, 2, 9, 2, 4});       // Numero impar de grupos de piedras (debe de ser par)
        probar({3, 3, 1, 5, 3, 3});    // Cantidad total par de piedras (debe de ser impar)

        // Otros casos
        probar({4, 7, 2, 8});          // Verdadero 
        probar({10, 1, 2, 4, 3, 5});   // Verdadero 
        probar({1, 2, 3});             // Numero impar de grupos de piedras (debe de ser par)
        probar({2, 4, 6, 8});          // Cantidad total par de piedras (debe de ser impar)

    } catch (const exception& error) { // Muestra el motivo del error sin terminar el programa de forma inesperada.
        cerr << "Error: " << error.what() << endl;
        return 1;
    }
    return 0;
}