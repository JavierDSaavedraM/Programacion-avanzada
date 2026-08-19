/*
Roberto De la Fuente 593303
Nombre 2
Nombre 3

Declaramos haber realizado esta actividad con integridad académica
*/

#include <iostream>
#include <string>
#include <algorithm>
using namespace std;

// left 1, right 1... Son inclusivos

int minOperations(const string& s, int& l1, int& r1, int& l2, int& r2, int& l3, int& r3) {
    int s_size = s.size();

    // Minimo y maximo de s, y tambien checa si ya esta ordenada
    bool sorted = true;
    char min = s[0], max = s[0];
    for (int i = 1; i < s_size; ++i) {
        if (s[i - 1] > s[i]) sorted = false;
        if (s[i] < min) min = s[i];
        if (s[i] > max) max = s[i];
    }

    // Caso 0: Ya esta ordenada
    if (sorted) return 0; 

    // Caso -1: No se puede separar una cadena de dos en subcadenas
    if (s_size == 2) return -1;

    // Caso 1: Un extremo correcto = solo ordenar lo demas
    if (s[0] == min) {
        l1 = 1; r1 = s_size - 1; // ordenar la derecha
        return 1;
    }
    if (s[s_size - 1] == max) {
        l1 = 0; r1 = s_size - 2; // ordenar la izquierda
        return 1;
    }

    // Caso 2: Ambos extremos estan mal. 
    // Revisar si el min o max se repite o 
    // si el min no esta al final o el max no esta al principio
    for (int i = 0; i <= s_size - 1; ++i) {

        if (s[i] == min && i != s_size - 1) {
            l1 = 0; r1 = i;          // trae el minimo al frente
            l2 = 1; r2 = s_size - 1; // ordena el resto
            return 2;
        }

        if (s[i] == max && i != 0) {
            l1 = i; r1 = s_size - 1; // trae el maximo al final
            l2 = 0; r2 = s_size - 2; // ordena el resto
            return 2;
        }
    }

    // Caso 3: El minimo aparece unicamente en la ultima posicion y el maximo aparece unicamente en la primera.
    l1 = 1; r1 = s_size - 1; // el minimo pasa a la posicion 1
    l2 = 0; r2 = 1;          // el minimo pasa a la posicion 0
    l3 = 1; r3 = s_size - 1; // se ordena el resto
    return 3;
}

int main() {
    cout << "Cadena a ordenar: ";
    string s;
    cin >> s;
    string original = s;

    int l1 = -1, r1 = -1, l2 = -1, r2 = -1, l3 = -1, r3 = -1;

    int min_operations = minOperations(s, l1, r1, l2, r2, l3, r3);

    if (min_operations == -1) {
        cout << "No es posible ordenar la cadena." << endl;
        return 0;
    }
    if (min_operations == 0) {
        cout << "La cadena ya estaba ordenada: " << s << endl;
        return 0;
    }

    // Ordenar al final
    if (min_operations >= 1) {
        sort(s.begin() + l1, s.begin() + r1 + 1);
        cout << "  Paso 1: ordenar s[" << l1 << ".." << r1 << "] -> " << s << endl;
    }
    if (min_operations >= 2) {
        sort(s.begin() + l2, s.begin() + r2 + 1);
        cout << "  Paso 2: ordenar s[" << l2 << ".." << r2 << "] -> " << s << endl;
    }
    if (min_operations >= 3) {
        sort(s.begin() + l3, s.begin() + r3 + 1);
        cout << "  Paso 3: ordenar s[" << l3 << ".." << r3 << "] -> " << s << endl;
    }

    cout << endl;
    cout << "Cadena original:   " << original << endl;
    cout << "Cadena resultante: " << s << endl;
    return 0;
}