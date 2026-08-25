#include <iostream>
#include <vector>
#include <chrono>

using namespace std;

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
  return to_string(tiempo_ejecucion.count());
}
string secuencia(int _limite);
string tomar_tiempoRecursivo(int _limite);

int main(){
  for (int i= 0; i <= 31; i++){
    cout << criba(100) << ",";
  }
  cout << endl;

  return 0;
}
