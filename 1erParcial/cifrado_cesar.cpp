#include <iostream>
#include <string>
#include <stack>
#include <utility>

using namespace std;

string ALPHABETO = "abcdefghijklmnopqrstuvwxyz";

// Funcion cifrado cesar que mueve la pos #define 
// @input: tienes una frase (_s) y una llave (_k) que mueve (shift) la pos de una letra k veces.
// @output: frase crifrada
string cifrar_cesar(string _s, int _k){
    string nueva_frase;
    int valor_circular = ALPHABETO.size();
    for(const auto& letra: _s){
        int pos = ALPHABETO.find(letra);
        nueva_frase += (pos == -1) ? letra: ALPHABETO[(pos + _k)%valor_circular];
    }
    return nueva_frase;
}

// Funcion cifrado cesar que mueve la pos #define 
// @input: tienes una frase (_s) y una llave (_k) que dependiendo de las palabras que contenga puede shiftear la pos del alfabeto.
// @output: frase crifrada con 
stack<pair<int,char>> eliminar_caracteres_invalidos(string& _s){
    stack<pair<int, char>> char_invalid;
    for(int i= 0; i < _s.size(); i++){
        if(ALPHABETO.find(_s[i]) == -1){
            char_invalid.push({i, _s[i]});
            _s.erase(i, 1);
        }
    }
    return char_invalid;
}

void regresar_caracters_invalidos(stack<pair<int,char>> &_stack, string &_s){
    while(!_stack.empty()){
        pair<int,char> p = _stack.top();
        _s.insert(p.first, 1, p.second);
        _stack.pop();
    }
}

// Funcion cifrado cesar que mueve la pos #define 
// @input: tienes una frase (_s) y una llave (_k) que dependiendo de las palabras que contenga puede shiftear la pos del alfabeto.
// @output: frase crifrada con 
string cifrar_vigenere(string _s, string _k){
    stack<pair<int, char>> invalid = eliminar_caracteres_invalidos(_s);
    string nueva_frase;
    int valor_circular_llave = _k.size();
    for (int i= 0; i < _s.size(); i++){
        int pos_shift = ALPHABETO.find(_k[i % valor_circular_llave]);
        nueva_frase += cifrar_cesar(string(1,_s[i]), pos_shift);
    }
    regresar_caracters_invalidos(invalid, nueva_frase);
    return nueva_frase;
}

int main(){

    cout << cifrar_cesar("Kasane Teto",14) << endl;
    cout << cifrar_vigenere("attacking tonight", "oculorhinolaryngology") << endl;
    return 0;
}
