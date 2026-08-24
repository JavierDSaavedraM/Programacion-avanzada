/*
Nombres:
Sergio Alejandro Zamora Dávila 616148
Javier Djorkaef Saavedra Mendiola 624198
Roberto De la Fuente 593303

Damos nuestra palabra que hemos realizado esta actividad con integridad académica
*/

#include <cctype>
#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>
#include <regex>
#include <fstream>
using namespace std;

#ifdef DEBUG
#define LOG_DEBUG(msg) cout << "[DEBUG]" << msg << endl;
#else
#define LOG_DEBUG(msg)
#endif

string leerArchivo(const string& nombre_archivo);

class Lexer{
    public:
        Lexer(const string & contenido){this->contenido = contenido; pos = 0; JSON_SYNTAX="[]{}:,"; Tokenizar();};
        vector<string> obtenerTokens(){return tokens;};

    private:
        void Tokenizar();
        string JSON_SYNTAX;
        string contenido;
        vector<string> tokens;
        size_t pos;
        void lex_string();
        void lex_numero();
};

void Lexer::lex_numero(){
    string json_numero;
    char caracter_actual = contenido[pos];

    while(pos < contenido.length()){
        caracter_actual = contenido[pos];
        if(!isdigit(caracter_actual)){
            tokens.push_back(json_numero);
            return;
        } else{
            json_numero += caracter_actual;
            pos++;
        }
    }

};

void Lexer::lex_string(){
    string json_valor;
    char caracter_actual = contenido[pos];
    if (caracter_actual == '\"')
        pos++;
    else  
        return;

    while(pos < contenido.length()){
        caracter_actual = contenido[pos];
        if (caracter_actual == '\"'){
            tokens.push_back(json_valor);
            pos++;
            return;
        } else{
            json_valor += caracter_actual;
            pos++;
        }
    }
};

void Lexer::Tokenizar(){
    while(pos < contenido.length()){
        char caracter_actual = contenido[pos];
        LOG_DEBUG(caracter_actual);
        if (caracter_actual == '\"') {lex_string(); continue;};
        if (isdigit(caracter_actual)) {lex_numero(); continue;};

        if(JSON_SYNTAX.find(caracter_actual) != -1){
            tokens.push_back(string(1,caracter_actual));
            pos++;
        } else if (isspace(caracter_actual)){
            pos++;
        }
        else{
            throw runtime_error("Error al lexear el string");
        }
    }
}

struct Contacto{ string email , telefono; };
struct Empleo{ string puesto , empresa; };
struct Detalles{
    vector<Contacto> contactos;
    vector<Empleo> empleos;
};

struct Persona{
    int id, edad;
    string nombre, ciudad;
    Detalles detalles;
};

class Parser{
    public:
        Parser(const vector<string> & tokens){this->tokens = tokens; pos=0; tokenActual = tokens[pos];};
    private:
        vector<string> tokens;
        string tokenActual;
        vector<Persona> Personas;
        size_t pos;
        vector<Persona> parsear_ArrayPersonas(); //array de personas
        Persona parsear_objPersona(); // obj
        Detalles parsear_objDetalles();
        
        vector<Contacto> parsear_ArrayContactos();
        Contacto parsear_objContacto();
        string parsear_correo();
        string parsear_telefono();

        vector<Empleo> parsear_ArrayEmpleos();
        Empleo parsear_ObjEmpleo();
        string parsear_empresa();

        string parsear_nombreCiudadPuesto();
        int parsear_idEdad();

        void siguienteToken() {
            ++pos;

            if (pos >= tokens.size()) {
                tokenActual = "";
                return;
            }

            tokenActual = tokens[pos];
        }

        void checarTokenActual(string s){
            if(tokenActual != s)
                throw runtime_error("Error en el formato del archivo");
            else
               siguienteToken();
        }
};

Detalles Parser::parsear_objDetalles() {
    Detalles obj_actual;

    checarTokenActual("{");

    while (tokenActual != "}") {
        string key = tokenActual;
        siguienteToken();
        checarTokenActual(":");
        if (key == "contacto") {
            if (tokenActual == "[") {
                obj_actual.contactos = parsear_ArrayContactos();
            }
            else if (tokenActual == "{") {
                obj_actual.contactos.push_back(parsear_objContacto());
            }
            else {
                throw runtime_error("Formato invalido para contacto");
            }
        }
        else if (key == "empleo") {
            if (tokenActual == "[") {
                obj_actual.empleos = parsear_ArrayEmpleos();
            }
            else if (tokenActual == "{") {
                obj_actual.empleos.push_back(parsear_ObjEmpleo());
            }
            else {
                throw runtime_error("Formato invalido para empleo");
            }
        }
        else {
            throw runtime_error("Llave no reconocida");
        }
        if (tokenActual == ",") {
            siguienteToken();
        }
        else if (tokenActual != "}") {
            throw runtime_error("Se esperaba ',' o '}'");
        }
    }

    checarTokenActual("}");

    return obj_actual;
}

vector<Contacto> Parser::parsear_ArrayContactos(){
    vector<Contacto> array_contactos;

    checarTokenActual("[");
    while(pos < tokens.size() && tokenActual != "]"){
        array_contactos.push_back(parsear_objContacto());
        if (tokenActual == ",") {
            siguienteToken();
        }
        else if (tokenActual != "]") {
            throw runtime_error("Se esperaba ',' o ']'");
        }
    }
    if (tokenActual != "]"){
        throw runtime_error("Error en el formato del archivo");
    }
    checarTokenActual("]");
    return array_contactos;
}

Contacto Parser::parsear_objContacto(){
    Contacto obj_contacto;
    checarTokenActual("{");

    while(pos < tokens.size() && tokenActual != "}" ){
        string key = tokenActual;
        siguienteToken();

        if (key == "email"){ 
            checarTokenActual(":");
            obj_contacto.email = parsear_correo();
        } 
        else if (key == "telefono"){
            checarTokenActual(":");
            obj_contacto.telefono = parsear_telefono();
        }
        else { 
            throw runtime_error("Llave no reconocida"); 
        }
        if (tokenActual == ",") {
            siguienteToken();
        }
        else if (tokenActual != "}") {
            throw runtime_error("Se esperaba ',' o '}'");
        }
    }
    checarTokenActual("}");
    return obj_contacto;
}

Empleo Parser::parsear_ObjEmpleo(){
    Empleo obj_empleo;
    checarTokenActual("{");

    while(pos < tokens.size() && tokenActual != "}" ){
        string key = tokenActual;
        siguienteToken();

        if (key == "puesto"){ 
            checarTokenActual(":");
            obj_empleo.puesto = parsear_nombreCiudadPuesto();
        } 
        else if (key == "empresa"){
            checarTokenActual(":");
            obj_empleo.empresa = parsear_empresa();
        }
        else { 
            throw runtime_error("Llave no reconocida"); 
        }
        if (tokenActual == ",") {
            siguienteToken();

            if (tokenActual == "}") {
                throw runtime_error("No se permite coma final");
            }
        }
        else if (tokenActual != "}") {
            throw runtime_error("Se esperaba ',' o '}'");
        }
    }
    checarTokenActual("}");
    return obj_empleo;
}


vector<Empleo> Parser::parsear_ArrayEmpleos(){
    vector<Empleo> array_empleos;

    checarTokenActual("[");
    while(pos < tokens.size() && tokenActual != "]"){
        array_empleos.push_back(parsear_ObjEmpleo());
        if (tokenActual == ",") {
            siguienteToken();
        }
        else if (tokenActual != "]") {
            throw runtime_error("Se esperaba ',' o ']'");
        }
    }
    if (tokenActual != "]"){
        throw runtime_error("Error en el formato del archivo");
    }
    checarTokenActual("]");
    return array_empleos;
}

vector<Persona> Parser::parsear_ArrayPersonas(){
    vector<Persona> personasArchivos;

    checarTokenActual("[");
    while(pos < tokens.size() && tokenActual != "]"){
        personasArchivos.push_back(parsear_objPersona());
        if (tokenActual == ",") {
            siguienteToken();

            if (tokenActual == "]") {
                throw runtime_error("No se permite coma final");
            }
        }
        else if (tokenActual != "]") {
            throw runtime_error("Se esperaba ',' o ']'");
        }
    }
    checarTokenActual("]");

    return personasArchivos;
}

Persona Parser::parsear_objPersona(){
    Persona obj_actual;
    checarTokenActual("{");

    while(pos < tokens.size() && tokenActual != "}" ){
        string key = tokenActual;
        siguienteToken();

        if (key == "id"){ 
            checarTokenActual(":");
            obj_actual.id = parsear_idEdad();
        } 
        else if (key == "nombre"){
            checarTokenActual(":");
            obj_actual.nombre = parsear_nombreCiudadPuesto();
        }
        else if (key == "edad"){
            checarTokenActual(":");
            obj_actual.edad = parsear_idEdad();
        }
        else if (key == "ciudad"){
            checarTokenActual(":");
            obj_actual.ciudad = parsear_nombreCiudadPuesto();
        }
        else if (key == "detalles"){
            checarTokenActual(":");
            obj_actual.detalles = parsear_objDetalles();
        }
        else { 
            throw runtime_error("Llave no reconocida"); 
        }

        if (tokenActual == ",") {
            siguienteToken();
        }
        else if (tokenActual != "}") {
            throw runtime_error("Se esperaba ',' o '}'");
        }
    }
    checarTokenActual("}");
    return obj_actual;
}

int Parser::parsear_idEdad(){
    string valor = tokenActual;
    regex patron(R"(^\d+$)");
    if(!regex_match(valor,patron)){ throw runtime_error("Valor no int");}
    siguienteToken();
    return stoi(valor);
};

string Parser::parsear_nombreCiudadPuesto(){
    string valor = tokenActual;
    regex patron(R"(^[\p{L}\w\s]+$)");
    if(!regex_match(valor,patron)){ throw runtime_error("Valor no es solo letras y acentos ");}
    siguienteToken();
    return valor;
}

string Parser::parsear_correo(){
    string valor = tokenActual;
    regex patron(R"(^(?!.*__)[a-z](?:[a-z0-9_]{0,18}[a-z0-9])?@[a-z]+\.[a-z]+$)");
    if(!regex_match(valor,patron)){ throw runtime_error("Correo no valido");}
    siguienteToken();
    return valor;
}
string Parser::parsear_telefono(){
    string valor = tokenActual;
    regex patron(R"(^\d{3}-\d{3}-\d{4}$)");
    if(!regex_match(valor,patron)){ throw runtime_error("Telefono no valido");}
    siguienteToken();
    return valor;
}

string Parser::parsear_empresa(){
    string valor = tokenActual;
    regex patron(R"(^[\p{L}\w\s.,]+$)");
    if(!regex_match(valor,patron)){ throw runtime_error("Empresa no valido");}
    siguienteToken();
    return valor;
}

int main(){
    string path_archivo = "./1erParcial/personas.json";
    try {
        string c = leerArchivo(path_archivo);
        Lexer lexer(c);
        vector<string> t = lexer.obtenerTokens();

#ifdef DEBUG
        for (const string& s: t){
            cout << s ;
            cout << ((s =="}" || s =="]") ? "\n" : " ");
        }

#endif // DEBUG

    } catch (const runtime_error& e) {
        cout << "Error: " << e.what() << endl;

    }

    return 0;
}

string leerArchivo(const string & nombre_archivo){
    ifstream archivo(nombre_archivo);

    string contenido, linea;
    while (getline(archivo, linea)) {
        contenido += linea;
    }
    archivo.close();

    return contenido;
}
