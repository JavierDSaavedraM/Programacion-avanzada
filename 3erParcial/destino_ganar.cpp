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

// Minimax con memoizacion.
// used: Used as a list for the numbers that have been taken. 0 = not yet, 1 = taken
// remaining: Whats missing to reach the target
// memo: Memory. -1 = not calculated, 0 = looses the turn, 1 = wins the turn
bool canWin(int used, int remaining, int& max_number, vector<short>& memo) {
    if (memo[used] != -1) return memo[used]; // Poda

    for (int i = 1; i <= max_number; i++) {
        int bit = 1 << (i - 1);
        if (used & bit) continue; // Number already used, skip

        // wins in this turn (max), or when the rival doesn't win / looses  on his next turn (min)
        if (i >= remaining || !canWin(used | bit, remaining - i, max_number, memo)) {
            return memo[used] = 1;
        }
    }
    return memo[used] = 0; // All plays are loosing
}

int main() {
    try {
        int max_number, target;
        cout << "Numero maximo a elegir = ";
        cin >> max_number;
        if (max_number > 30) {
            cout << "No se pueden usar numeros maximos mayores a 30 por limitaciones de memoria" << endl;
            return 0;
        }

        cout << "Total deseado = ";
        cin >> target;
        if (target <= 0) {
            cout << "Verdadero (ya tiene 0)" << endl;
            return 0;
        } 

        int max_possible = 0;
        for (int i = 1; i < max_number + 1; i++) max_possible += i;
        if (max_possible < target) {
            cout << "Imposible al tener un maximo posible " << max_possible << " menor al numero deseado " << target << endl;
            return 0;
        }

        vector<short> memo(1 << max_number, -1);
        bool result = canWin(0, target, max_number, memo);
        if (result) cout << "Verdadero" << endl;
        else cout << "Falso" << endl;

    } catch (const exception& error) { // Muestra el motivo del error sin terminar el programa de forma inesperada.
        cerr << "Error: " << error.what() << endl;
        return 1;
    }

    return 0;
}