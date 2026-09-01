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

vector<int> primos = {2}; 
int maxCalculado = 2; 

// Expandir la lista de primos hasta el nuevo limite
void expandirPrimos(int limite) {
    if (limite <= maxCalculado) return;

    // Se empieza desde el siguiente numero
    int inicio = maxCalculado + 1;
    if (inicio % 2 == 0) inicio += 1; // saltar uno si es par

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

int obtenerNumeroPrimoPalindromo(int _i){
    int limite_inicial = _i;
    string limite_str = to_string(limite_inicial);
    int tamanio = limite_str.length();
    if (tamanio % 2 == 0) { tamanio++; }
    int numero_actual = pow(10,tamanio)/10;
    while (true) {
        if (numero_actual < limite_inicial){
            numero_actual = limite_inicial +1;
        }
        limite_str = to_string(numero_actual);
        tamanio = limite_str.length();
        if (tamanio % 2 ==0) {
            tamanio++;
            numero_actual = pow(10,tamanio)/10;
        }
        else{
            if (esPalindromo(numero_actual)){
                if (esPrimo(numero_actual)) { break;}
            }
            numero_actual++;
        }
    }
    return numero_actual;
}

string obtenerTiempoDeEjecucion(int _i){
    auto init_time = chrono::high_resolution_clock::now();
    primos = {2}; 
    maxCalculado = 2; 
    obtenerNumeroPrimoPalindromo(_i);
    auto end_time = chrono::high_resolution_clock::now();
    chrono::duration<double, milli> tiempo_ejecucion = end_time - init_time;
  return std::to_string(tiempo_ejecucion.count());
};

void escribirArchivoCSV(vector<int> & _inputs){
    const int num_repeticiones = 31;
    vector<vector<string>> resultados(_inputs.size(), vector<string>(num_repeticiones));

    // Obtener todas las iteraciones por el input
    for (size_t i = 0; i < _inputs.size();i++){
        for (size_t j = 0; j < num_repeticiones; ++j){
            resultados[i][j] = obtenerTiempoDeEjecucion(_inputs[i]);
        }
    } 

    ofstream  archivo_csv("numerosPrimosPalindromos.csv");

    if(!archivo_csv.is_open()){
        throw runtime_error("No se pudo abrir el archivo");
    }
    string linea;

    // Imprimir header
    for(size_t i = 0; i<_inputs.size(); i++){
        linea += to_string(_inputs[i]);
        if(i+1 < _inputs.size())
            linea += ",";
    }
    archivo_csv << linea << endl;

    // Guardar verticalmente
    for (size_t i = 0; i< num_repeticiones; i++){
        linea = "";
        for (int j = 0; j < _inputs.size(); j++){
            linea += resultados[j][i];
            if (j + 1 < _inputs.size())
                linea += ",";
        }
        archivo_csv << linea << endl;
    }
    archivo_csv.close();
}

int main(){
    try{
        vector<int> input = {6,8,13,99899,10000000,100030000};
        escribirArchivoCSV(input);
    } catch (const runtime_error& e) {
        cout << "Error: " << e.what() << endl;
    }
    return 0;
}
