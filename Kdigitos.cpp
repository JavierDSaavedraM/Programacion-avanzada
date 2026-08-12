/*
Nombres: 
Sergio Alejandro Zamora Dávila 616148
Javi chan 624198
Roberto De la Fuente 593303
*/


#include <iostream>
#include <string>
using namespace std;

int eliminar_k_digitos(int valor_entrada, int k_entrada) {
    int valor = valor_entrada;
    int k = k_entrada;
    bool breaker = false;
    int contador_eliminados = 0;
    string valor_str = to_string(valor);
    
    if (valor_str.length() == k){
        cout << "0" ;
        return 0;
    } else if (valor_str.length() < k) {
        return -1;
    }

    for (;contador_eliminados < k; contador_eliminados++) {
        breaker = false;
            for (int i = 0; i < valor_str.length() - 1; i++) {
                if (valor_str[i] >= valor_str[i + 1]) {
                    valor_str.erase(i, 1);
                    breaker = true;
                    break;
                }
            }
        if (!breaker) break;
   }
   valor_str.erase(valor_str.length() - 1, k - contador_eliminados); // Didn't delete anything

   int resultado_numerico = stoi(valor_str);

   return resultado_numerico; 
}

int main(){
   cout << eliminar_k_digitos(1432219, 3) << endl; // Output: 1219
   cout << eliminar_k_digitos(10200, 1) << endl; // Output: 200
   cout << eliminar_k_digitos(10, 2) << endl;// Output: 0
   cout << eliminar_k_digitos(12345, 1) << endl; // Output: 1234
   cout <<eliminar_k_digitos(15234, 1) << endl; // Output: 1432
   cout <<eliminar_k_digitos(87653899, 6) << endl; // Output: 38
   return 0;
}
