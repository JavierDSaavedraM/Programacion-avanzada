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

// backtracking
int resolver(vector<int> &casas, int valor, int i) {
    int val1 = 0;
    int val2 = 0;
    if (i >= casas.size()){
        return valor; 
    }

    try {
        val1 = resolver(casas,valor+casas[i],i+2);
    } catch (const exception& error) {
        // Solo lo hace si se puede hacer
    }

    try {
        val2 = resolver(casas,valor,i+1);
    } catch (const exception& error) {
        // Solo lo hace si se puede hacer
    }

    if (val1 > val2) {
        return val1;
    } else return val2;
}

int main() {
    try {
        /* // Testing: 
        vector<int> caso1{1,2,3,1};
        vector<int> caso2{2,7,9,3,1};
        int res1 = resolver(caso1, 0, 0);
        int res2 = resolver(caso2, 0, 0);
        
        cout << "Entrada1: ";
        for (int i: caso1) cout << i << ' ';
        cout << endl << "Salida: " << res1 << endl;

        cout << "Entrada2: ";
        for (int i: caso2) cout << i << ' ';
        cout << endl << "Salida: " << res2 << endl;
        */

        string caso;
        cout << "Dame la lista de numeros: " << endl;
        getline(cin, caso);

        string numero; // para separar el numero del string
        vector<int> caso_vec;
        for (int i = 0; i < caso.size(); i++) {
            char c = caso[i];
            if (isdigit(c)) {
                numero += c;
            } else { // Termina un número encontrado
                if (!numero.empty()) { // Evita mandar numeros vacios.
                    caso_vec.push_back(stoi(numero));
                    numero.clear();
                }
            }
        }

        if (!numero.empty()) { // Por si el último número no termino antes del final de la cadena
            caso_vec.push_back(stoi(numero));
        }

        int res = resolver(caso_vec, 0, 0);
        
        cout << "Entrada: ";
        for (int i: caso_vec) cout << i << ' ';
        cout << endl << "Salida: " << res << endl;

    } catch (const exception& error) { // Muestra el motivo del error sin terminar el programa de forma inesperada.
        cerr << "Error: " << error.what() << endl;
        return 1;
    }
    
    return 0;
}
