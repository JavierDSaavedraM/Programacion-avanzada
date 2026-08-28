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

int maxVerificado = 1;
vector<int> primos;

bool esPrimo(int numero) {
    // Si el numero a verificar es menor al maximo verificado,
    // solo buscar entre los primos conocidos.
    if (numero <= maxVerificado) {
        for (int primo : primos) {
            if (primo > numero / primo)
                break;

            if (numero % primo == 0)
                return false;
        }

        return true;
    }

    // Si el numero a verificar es mayor al maximo verificado,
    // entonces avanzar progresivamente hasta el numero.
    for (int candidato = maxVerificado + 1; candidato <= numero; ++candidato) {
        bool primo = true;

        for (int divisor : primos) {
            if (divisor > candidato / divisor)
                break;

            if (candidato % divisor == 0) {
                primo = false;
                break;
            }
        }

        if (primo)
            primos.push_back(candidato);

        maxVerificado = candidato;
    }

    // Si el ultimo primo agregado es el numero buscado, entonces sí es primo
    return !primos.empty() && primos.back() == numero;
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
