#include <iostream>
using namespace std;

// Funcion que ayuda a calcular mas facilmente los numeros con exponentes grandes al dividir en pequenias operaciones. Funcion basada en pseudocodigo de wikipedia
// @input: base y exponente con el cual quieres calcular y el modulo para obtene 
// @output: numero calculado con algebra modular
long long modPow(long long &base, long long &exponente,long long &modulo){
   long long resultado = 1;
   if (modulo == 1){
      return 0;
   }
   base = base % modulo; // checa si la base es muy grande y la reduce.
   while(exponente > 0){
      if (exponente % 2 == 1){
         resultado = (resultado * base) % modulo;
      }
      exponente = exponente >> 1;
      base = (base * base) % modulo;
   }
   return resultado;
}

// recibir los primeros dos numeros publicos desde la ejecucion del programa
int main(int argc, char* argv[]){
   try{
      long long p = stol(argv[1]); // Numero primo publico
      long long g = stol(argv[2]); //Numero Generador publico
      long long a = stol(argv[3]); // numero privado como seed inicial

      if(argc == 4){
         long long A = modPow(g, a, p); // llave publica A para compartir
         cout << A;
         return 0;
      } else {
         long long B = stol(argv[4]); // llave publica B recibida del otro cliente
         long long K = modPow(B, a, p);
         cout << K;
      }

   } catch(const exception& e){
      cout << "[ERROR " << e.what() << " ]\n";

   }
   return 0;
}
