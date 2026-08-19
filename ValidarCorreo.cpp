#include <iostream>
#include <string>
#include <vector>
#include <regex>
using namespace std;

bool Validar_Usuario(string usuario){
    if (usuario.size()<1){
        cout << "El usuario cuenta con muy pocos caracteres, incorrecto" << endl;
        return false;
    }
    
    if (usuario.size() > 20){
        cout << "El usuario cuenta con muchos caracteres, incorrecto" << endl;
        return false;
    }
    regex pattern(R"([^\da-z_])");
    smatch match;
    if (regex_search(usuario,match,pattern))
    {  
        cout << "Error, el usuario contiene el siguiente caracter, no es valido " << match.str() << endl;
        return false;
    }
    pattern = regex(R"(^\d)");
    if (regex_search(usuario,match,pattern))
    {  
        cout << "Error, el usuario debe de comenzar con una letra minuscula" << endl;
        return false;
    }
    pattern = regex(R"(_$)");
    if (regex_search(usuario,match,pattern))
    {  
        cout << "Error, el usuario no puede terminar con un guion bajo" << endl;
        return false;
    }
    pattern = regex(R"(__)");
    if (regex_search(usuario,match,pattern))
    {  
        cout << "Error, el usuario no puede contener dos guiones bajos consecutivos" << endl;
        return false;
    }

    return true;
}

bool Validar_Dominio(string dominio){
    regex pattern(R"([A-Z])");
    smatch match;
    if (regex_search(dominio,match,pattern))
    {  
        cout << "Error, el dominio no puede contener letras mayusculas" << endl;
        return false;
    }
    
    pattern = regex(R"([^\da-z_.])");
    if (regex_search(dominio,match,pattern))
    {  
        cout << "Error, el dominio no puede contener un caracter que no sea una letra minuscula, un numero o un punto" << endl;
        return false;
    }

    pattern = regex(R"(.{0,1})");
    if (regex_search(dominio,match,pattern))
    {  
        cout << "Error, el dominio no puede contener mas de 1 punto" << endl;
        return false;
    }

    pattern = regex(R"(^.$.)");
    if (regex_search(dominio,match,pattern))
    {  
        cout << "Error, en el dominio el punto no puede ser el primer ni el último carácter del dominio" << endl;
        return false;
    }

    return true;
}

int main(){
    vector<string> candidatos1 = {"juan_perez@mail.com", "1ana@mail.com", "luis__m@tech.net", "maria@.com", "carlos_@domain.org", "z@a.b"};
    vector<string> candidatos2 = {"admin@sys.com", "root@sys.com", "test@otro.dominio.com", "admin@sys..com"};
    vector<string> candidatos3 = {"@sinusuario.com", "usuario_largo_que_pasa_de_veinte_caracteres@mail.com", "user@tech.", "us3r_n4me@domain.mx"};
    for (int i = 0; i < candidatos2.size(); i++) {
        string correo = candidatos2[i];
        int ubicacion = correo.find('@');
        if (ubicacion == -1) {
            cout << "error, el correo debe de contener un '@'" << endl;
        } 
        string usuario = correo.substr(0,ubicacion);
        string dominio = correo.substr(ubicacion + 1);
        if (Validar_Usuario(usuario) == true and Validar_Dominio(dominio) == true)
        {
            cout << "El correo es valido" << endl;
        }
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
