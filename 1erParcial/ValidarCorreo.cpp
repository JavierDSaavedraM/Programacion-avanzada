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

void validarExpresiones(vector<string>& p_correos){
    regex patron(R"(^(?!.*__)[a-z](?:[a-z0-9_]{0,18}[a-z0-9])?@[a-z]+\.[a-z]+$)");
    vector<string> correos_correctos;
    vector<string> correos_erroneos;

    for (const string & correo: p_correos){
    // Los correos se clasifican una vez y se separan los correctos de los incorrectos
        if (regex_match(correo,patron))
            correos_correctos.push_back(correo);
        else 
            correos_erroneos.push_back(correo);
    }
    cout << "Correos validos:\n [";
    for (const string& correo : correos_correctos) 
        cout << "\""<< correo << "\" ";
    cout << "]" << endl;

    cout << "Correos invalidos:" << endl;
    for (const string & correo: correos_erroneos){
        // se separan el usuario del dominio para obtener la razon de fallo
        size_t ubicacion = correo.find('@');
        string usuario = correo.substr(0, ubicacion);
        string dominio = correo.substr(ubicacion + 1);
        string razon;
        cout << "- \"" << correo << "\" Invalido ( ";
        if (!Validar_Usuario(usuario, razon)) {
            cout << razon;
        } else if (!Validar_Dominio(dominio, razon)) {
            cout << razon;
        } else {
            cout << "Otro error";
        }
        cout << " )" << endl;
    }

    cout << endl;

}


int main(){
    vector<string> caso1 = {"juan_perez@mail.com", "1ana@mail.com", "luis__m@tech.net", "maria@.com", "carlos_@domain.org", "z@a.b"};
    vector<string> caso2 = {"admin@sys.com", "root@sys.com", "test@otro.dominio.com", "admin@sys..com"};
    vector<string> caso3 = {"@sinusuario.com", "usuario_largo_que_pasa_de_veinte_caracteres@mail.com", "user@tech.", "us3r_n4me@domain.mx"};

    validarExpresiones(caso1);
    validarExpresiones(caso2);
    validarExpresiones(caso3);
    return 0;
}
