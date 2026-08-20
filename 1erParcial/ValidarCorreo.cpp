/*
Roberto De la Fuente 593303
Javier Djorkaef Saavedra Mendiola 624198
Sergio Alejandro Zamora Dávila 616148
Declaramos haber realizado esta actividad con integridad académica
*/

#include <iostream>
#include <string>
#include <vector>
#include <regex>
using namespace std;

// La razon por la que falla el usuario y dominio esta escrito en el codigo.
// Se revisa cada requisito individualmente para tambien saber el porque fallo.
bool Validar_Usuario(string usuario, string& razon){
    if (usuario.size() < 1) {
        razon = "el usuario no tiene caracteres";
        return false;
    }
    
    if (usuario.size() > 20) {
        razon = "el usuario supera los 20 caracteres de longitud";
        return false;
    }
    regex pattern(R"([^\da-z_])");
    smatch match;
    if (regex_search(usuario,match,pattern)) {  
        razon = "el usuario contiene un caracter no valido: " + match.str();
        return false;
    }
    pattern = regex(R"(^[^a-z])");
    if (regex_search(usuario,match,pattern)) {  
        razon = "el usuario debe comenzar con una letra minuscula";
        return false;
    }
    pattern = regex(R"(_$)");
    if (regex_search(usuario,match,pattern)) {  
        razon = "el usuario no puede terminar con un guion bajo";
        return false;
    }
    pattern = regex(R"(__)");
    if (regex_search(usuario,match,pattern)) {  
        razon = "el usuario contiene dos guiones bajos consecutivos";
        return false;
    }

    return true;
}

bool Validar_Dominio(string dominio, string& razon){
    regex pattern(R"([A-Z])");
    smatch match;
    if (regex_search(dominio,match,pattern)) {  
        razon = "el dominio no puede contener letras mayusculas";
        return false;
    }
    
    pattern = regex(R"([^a-z.])");
    if (regex_search(dominio,match,pattern)) {  
        razon = "el dominio solo puede contener letras minusculas y un punto";
        return false;
    }

    if (dominio.find('.') == string::npos) {
        razon = "el dominio debe contener exactamente un punto";
        return false;
    }

    pattern = regex(R"(\..*\.)");
    if (regex_search(dominio,match,pattern)) {  
        razon = "el dominio tiene mas de un punto";
        return false;
    }

    pattern = regex(R"(^\.|\.$)");
    if (regex_search(dominio,match,pattern)) {  
        razon = "el punto no puede ser el primer ni el ultimo caracter del dominio";
        return false;
    }
    return true;
}

int main(){
    vector<string> candidatos1 = {"juan_perez@mail.com", "1ana@mail.com", "luis__m@tech.net", "maria@.com", "carlos_@domain.org", "z@a.b"};
    vector<string> candidatos2 = {"admin@sys.com", "root@sys.com", "test@otro.dominio.com", "admin@sys..com"};
    vector<string> candidatos3 = {"@sinusuario.com", "usuario_largo_que_pasa_de_veinte_caracteres@mail.com", "user@tech.", "us3r_n4me@domain.mx"};
    
    // Se separan los correctos de los incorrectos
    vector<string> correctos;
    vector<pair<string, string>> erroneos;
    vector<vector<string>> grupos = {candidatos1, candidatos2, candidatos3};

    // Los correos se clasifican una vez y se conserva la seccion que fallo con su razon.
    for (const vector<string>& grupo : grupos) {
        for (const string& correo : grupo) {
            size_t ubicacion = correo.find('@');
            if (ubicacion == string::npos || correo.find('@', ubicacion + 1) != string::npos) {
                erroneos.push_back({correo, "el correo debe tener exactamente un '@'"});
                continue;
            }

            string usuario = correo.substr(0, ubicacion);
            string dominio = correo.substr(ubicacion + 1);
            string razon;
            if (!Validar_Usuario(usuario, razon)) {
                erroneos.push_back({usuario, razon});
            } else if (!Validar_Dominio(dominio, razon)) {
                erroneos.push_back({dominio, razon});
            } else {
                correctos.push_back(correo);
            }
        }
    }

    cout << "Correos validos:" << endl;
    for (const string& correo : correctos) {
        cout << correo << endl;
    }

    cout << "\nCorreos invalidos:" << endl;
    for (const pair<string, string>& error : erroneos) {
        cout << "\"" << error.first << "\": Invalido (" << error.second << ")." << endl;
    }
    

    /*


    regex pattern(R"(^(?!.*__)[a-z](?:[a-z0-9_]{0,18}[a-z0-9])?@[a-z]+\.[a-z]+$)");

    vector<string> candidatos1 = {"juan_perez@mail.com", "1ana@mail.com", "luis__m@tech.net", "maria@.com", "carlos_@domain.org", "z@a.b"};
    vector<string> candidatos2 = {"admin@sys.com", "root@sys.com", "test@otro.dominio.com", "admin@sys..com"};
    vector<string> candidatos3 = {"@sinusuario.com", "usuario_largo_que_pasa_de_veinte_caracteres@mail.com", "user@tech.", "us3r_n4me@domain.mx"};
    vector<string> erroneos = {};
    smatch match;
    cout << "Los correos correctos son: " << endl;
    for (int i = 0; i < candidatos1.size(); i++) {
        if (regex_search(candidatos1[i],match,pattern))
        {
            cout << match.str() << endl;
        } else {
            erroneos.push_back(candidatos1[i]);
        }
    }

    cout << endl << "Los correos incorrectos son: " << endl;
    for (int i = 0; i < erroneos.size(); i++)
    {
        cout << erroneos[i] << endl;
    }
    */
    return 0;
}
