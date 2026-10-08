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

    if (i < casas.size()) {
        val1 = resolver(casas,valor+casas[i],i+2);
    } 
        
    if (i+1 < casas.size()) {
        val2 = resolver(casas,valor,i+1);
    }

    if (val1 > val2) {
        return val1;
    } else return val2;
}

int main(){
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
    
    return 0;
}
