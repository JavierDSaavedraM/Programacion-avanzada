/*
Nombres:
Sergio Alejandro Zamora Dávila 616148
Javi Djorkaef 624198
Roberto De la Fuente 593303

Damos nuestra palabra que hemos realizado esta actividad con integridad académica
*/

bool validarNombreCiudadPuesto(const string& s);    // ^[\p{L}\w\s]+$
bool validarEdad(const string& s);                  // ^\d+$
bool validarEmpresa(const string& s);               // ^[\p{L}\w\s.]+$
bool validarEmail(const string& s);                 //
bool validarTelefono(const string& s);              // ^\d{3}-\d{3}-\d{4}$

#include <iostream>
#include <string>
#include <vector>
#include <regex>
#include <fstream>
using namespace std;

int main(){
    ifstream archivo("Personas.json");
    string linea;
    while (getline(archivo, linea)) {
        cout << linea << endl;

    }

    archivo.close();

    return 0;
}


bool validarNombreCiudadPuesto(const string& s){
    regex patron(R"()");

}
