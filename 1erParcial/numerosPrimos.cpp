#include <iostream>
#include <vector>
#include <chrono>
#include <string>
#include <fstream>

using namespace std;

int n = 31; // cantidad de repeticiones

string criba(int _limite){
  auto init_time = chrono::high_resolution_clock::now();
  int limite = _limite;
  vector<bool> es_primo(limite+1,true);
  es_primo[0] = false;
  es_primo[1] = false;
  for (int i = 2; i*i <= limite; i++){
    if (es_primo[i]){
      for(int j=i*i; j<=limite; j+=i)
        es_primo[j] = false;
    }
  }
  auto end_time = chrono::high_resolution_clock::now();
  chrono::duration<double, milli> tiempo_ejecucion = end_time - init_time;
  return std::to_string(tiempo_ejecucion.count());
}
string secuencia(int _limite) {
  auto init_time = chrono::high_resolution_clock::now();
  int limite = _limite;

  vector<int> primos;
  for (int numero = 2; numero <= limite; numero++) {
    bool es_primo = true;
    for (int divisor = 2; divisor < numero; divisor++) {
      if (numero % divisor == 0) {
        es_primo = false;
        break;
      }
    }
    if (es_primo) {
      primos.push_back(numero);
    }
  }

  auto end_time = chrono::high_resolution_clock::now();
  chrono::duration<double, milli> tiempo_ejecucion = end_time - init_time;
  return std::to_string(tiempo_ejecucion.count());
}
string recursivo(int _limite) {
  auto init_time = chrono::high_resolution_clock::now();
  int limite = _limite;


  auto end_time = chrono::high_resolution_clock::now();
  chrono::duration<double, milli> tiempo_ejecucion = end_time - init_time;
  return std::to_string(tiempo_ejecucion.count());
}

int main(){
  vector<int> vec_limites = {500, 5000, 50000};
  ofstream archivo_csv("NumerosPrimosResultados.csv");

  archivo_csv << "Metodo,Limite";
  for (int repeticion = 1; repeticion <= n; repeticion++) {
    archivo_csv << ",R" << repeticion;
  }
  archivo_csv << endl;

  for (int limite : vec_limites) {
    archivo_csv << "Criba," << limite;
    for (int repeticion = 0; repeticion < n; repeticion++) {
      archivo_csv << "," << criba(limite);
      cout << "Criba " << limite << " R" << repeticion + 1 << " completada\n";
    }
    archivo_csv << endl;

    archivo_csv << "Secuencial," << limite;
    for (int repeticion = 0; repeticion < n; repeticion++) {
      archivo_csv << "," << secuencia(limite);
      cout << "Secuencial " << limite << " R" << repeticion + 1 << " completada\n";
    }
    archivo_csv << endl;
/*
    archivo_csv << "Recursivo," << limite;
    for (int repeticion = 0; repeticion < n; repeticion++) {
      archivo_csv << "," << recursivo(limite);
      cout << "Recursivo " << limite << " R" << repeticion + 1 << " completada\n";
    }
    archivo_csv << endl;
*/

  }

  return 0;
}
