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
  
  try
  {
    for (int i = 2; i*i <= limite; i++){
      if (es_primo[i]){
        for(int j=i*i; j<=limite; j+=i)
          es_primo[j] = false;
      }
    }
  }
  catch(const std::exception& e)
  {
    cerr << "Error en criba(" << _limite << "): " << e.what() << endl;
    return "ERROR";
  }
  
  auto end_time = chrono::high_resolution_clock::now();
  chrono::duration<double, milli> tiempo_ejecucion = end_time - init_time;
  return std::to_string(tiempo_ejecucion.count());
}
string secuencia(int _limite) {
  auto init_time = chrono::high_resolution_clock::now();
  int limite = _limite;

  vector<int> primos;

  try
  {
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
  }
  catch(const std::exception& e)
  {
    cerr << "Error en secuencial(" << _limite << "): " << e.what() << endl;
    return "ERROR";
  }

  auto end_time = chrono::high_resolution_clock::now();
  chrono::duration<double, milli> tiempo_ejecucion = end_time - init_time;
  return std::to_string(tiempo_ejecucion.count());
}

bool recursivoProceso(int& revisar,int divisor){
  if (divisor * divisor > revisar){
    return true;
  }
  if (revisar % divisor == 0) {
    return false;
  }
  return recursivoProceso(revisar,divisor+1);
}


string recursivo(int _limite) {
  auto init_time = chrono::high_resolution_clock::now();
  vector<int> primos;

  try {
    for (int i = 2; i <= _limite; i++) {
      if (recursivoProceso(i,2)) {
        primos.push_back(i);
      }
    }
  }
  catch(const std::exception& e)
  {
    cerr << "Error en recursivo(" << _limite << "): " << e.what() << endl;
    return "ERROR";
  }
    
  auto end_time = chrono::high_resolution_clock::now();
  chrono::duration<double, milli> tiempo_ejecucion = end_time - init_time;
  //cout << primos.size() << endl;
  return std::to_string(tiempo_ejecucion.count());
}


int main(){
  vector<int> vec_limites = {50, 500, 5000, 50000,500000,5000000};
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

    archivo_csv << "Recursivo," << limite;
    for (int repeticion = 0; repeticion < n; repeticion++) {
      archivo_csv << "," << recursivo(limite);
      cout << "Recursivo " << limite << " R" << repeticion + 1 << " completada\n";
    }
    archivo_csv << endl;
  }

  return 0;
}
