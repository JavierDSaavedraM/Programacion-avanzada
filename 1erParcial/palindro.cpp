/*
Nombres:
Sergio Alejandro Zamora Dávila 616148
Javi Djorkaef 624198
Roberto De la Fuente 593303

Damos nuestra palabra que hemos realizado esta actividad con integridad académica
*/

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <cmath>

using namespace std;

vector<int> primos = {2}; 
int maxCalculado = 2; 

// Expandir la lista de primos hasta el nuevo limite
void expandirPrimos(int limite) {
    if (limite <= maxCalculado) return;

    // Se empieza desde el siguiente numero
    int inicio = maxCalculado + 1;
    if (inicio % 2 == 0) inicio + 1; // saltar uno si es par

    for (int candidato = inicio; candidato <= limite; candidato += 2) { // Solo ver impares (impar + 2 = impar)
        bool es_primo = true;
        
        for (int divisor : primos) {
            if (divisor * divisor > candidato) break;
            if (candidato % divisor == 0) {
                es_primo = false;
                break;
            }
        }
        
        if (es_primo) {
            primos.push_back(candidato);
        }
    }
    maxCalculado = limite;
}

bool esPrimo(int numero) {
    // Descartes rapidos
    if (numero <= 1) return false;
    if (numero == 2) return true;
    if (numero % 2 == 0) return false; 

    int raiz = sqrt(numero);
    
    if (raiz > maxCalculado) {
        expandirPrimos(raiz);
    }

    // Verificar el numero
    for (int primo : primos) {
        if (primo * primo > numero) break;
        if (numero % primo == 0) return false;
    }

    return true;
}

bool esPalindromo(int _i){
    string original = to_string(_i);
    string palindromo = original;
    reverse(palindromo.begin(), palindromo.end());
    return palindromo == original;
}


int main(){
    int num = 100030000;
    string numero = to_string(num);
    int tamanio = numero.length();
    if (tamanio % 2 == 0) { tamanio++; }
    int revisar = pow(10,tamanio)/10;
    while (true) {
        if (revisar < num){
            revisar = num +1;
        }
        numero = to_string(revisar);
        tamanio = numero.length();
        if (tamanio % 2 ==0) {
            tamanio++;
            revisar = pow(10,tamanio)/10;
        }
        else{
            if (esPalindromo(revisar)){
                if (esPrimo(revisar)) { break;}
            }
            revisar++;
        }
    }

    cout << "El siguiente numero palindromo que es primo es: " << revisar << endl;
    
    return 0;
}
