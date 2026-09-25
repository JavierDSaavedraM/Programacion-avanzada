#include <iostream>
#include <string>
#include <chrono>
#include <numeric>


/*
================================================================================
  IMPLEMENTACIÓN Y ANÁLISIS DE RSA light (TEORÍA DE NÚMEROS)
================================================================================

  IMPORTANTE: Queda estrictamente PROHIBIDO el uso de GitHub Copilot, ChatGPT 
  o cualquier otro asistente de IA durante el desarrollo de esta actividad. 
  El objetivo es evaluar tu comprensión directa del flujo y la matemática. DESACTIVALO.

  ------------------------------------------------------------------------------
  INSTRUCCIONES DEL EJERCICIO:
  ------------------------------------------------------------------------------
  1. COMENTAR EL CÓDIGO:
     Agrega comentarios detallados dentro del código explicando:
     - El flujo general del programa.
     - Qué está haciendo cada algoritmo/función matemáticamente segun lo visto en clase.

  2. PREGUNTAS DE REFLEXIÓN (Responder al final de este código como comentario o en la entrega de blackboard):
     - Pregunta 1: ¿Por qué falla el Caso 4 al intentar cifrar "HOLA"? Explica la causa

     - Pregunta 2: ¿Cómo resolverías esta limitación?

     - Pregunta 3: ¿En qué partes específicas de este código implementarías 
       dichos cambios? Indica qué funciones modificarías o agregarías y cómo.
================================================================================
*/



using namespace std;

// Funcion que performa operaciones a los bits para generar un numero muy grande.
long long stringToNumber(const string &s) {
    long long res = 0; // el numero resultante
    for (unsigned char c : s) {
        res = (res << 8) | c; // shiftea los bits anteriores y luego opera con or para insertar el nuevo caracter a la cadena de bits.
    }
    return res;
}

// Funcion que performa lo mismo para obtener de los bits al texto
string numberToString(long long num) {
    string str = "";
    while (num > 0) {
        char c = static_cast<char>(num & 0xFF); // obliga a que el numero 
        str = c + str;
        num >>= 8;
    }
    return str;
}

long long extGCD(long long a, long long b, long long &x, long long &y) { // calcula el MCD y los coeficientes de Bézout
    if (b == 0) {
        x = 1;
        y = 0;
        return a;
    }
    long long x1, y1;
    long long gcd = extGCD(b, a % b, x1, y1);
    x = y1;
    y = x1 - y1 * (a / b);
    return gcd;
}

long long modInverse(long long e, long long phi) {
    long long x, y;
    long long g = extGCD(e, phi, x, y);
    if (g != 1) return -1;
    return (x % phi + phi) % phi;
}

long long modExp(long long base, long long exp, long long mod) {
    long long res = 1;
    base %= mod;
    while (exp > 0) {
        if (exp % 2 == 1) {
            res = (unsigned __int128)res * base % mod;
        }
        base = (unsigned __int128)base * base % mod;
        exp /= 2;
    }
    return res;
}

struct RSAKeys {
    long long n;
    long long phi;
    long long e;
    long long d;
};

RSAKeys generateKeys(long long p, long long q, long long e_proced = 17) {
    RSAKeys keys;
    keys.n = p * q;
    keys.phi = (p - 1) * (q - 1);
    long long e = e_proced;
    while (e < keys.phi && gcd(e, keys.phi) != 1) {
        e += 2;
    }
    keys.e = e;
    keys.d = modInverse(keys.e, keys.phi);
    return keys;
}

void ejecutarPruebaRSA(long long p, long long q, const string &mensaje, long long e_sugerido = 17) {
    cout << "--------------------------------------------------\n";
    cout << "Prueba RSA con texto: \"" << mensaje << "\"\n";
    cout << "Primos: p = " << p << ", q = " << q << "\n";
    cout << "--------------------------------------------------\n";

    RSAKeys keys = generateKeys(p, q, e_sugerido);
    long long m = stringToNumber(mensaje);

    cout << "[Claves Generadas]\n";
    cout << "  - Modulo (n): " << keys.n << "\n";
    cout << "  - Exponente publico (e): " << keys.e << "\n";
    cout << "  - Exponente privado (d): " << keys.d << "\n";
    cout << "  - phi: " << keys.phi << "\n\n";

    cout << "Texto original: \"" << mensaje << "\"\n";
    cout << "Valor numerico de m: " << m << "\n";
    cout << "\n";

    auto t_start = chrono::high_resolution_clock::now();
    long long c = modExp(m, keys.e, keys.n);
    auto t_end = chrono::high_resolution_clock::now();
    chrono::duration<double, micro> t_cifrado = t_end - t_start;

    cout << "[Cifrado]\n";
    cout << "  - Criptograma (c): " << c << "\n";
    cout << "  - Tiempo: " << t_cifrado.count() << " us\n\n";

    t_start = chrono::high_resolution_clock::now();
    long long m_descifrado = modExp(c, keys.d, keys.n);
    t_end = chrono::high_resolution_clock::now();
    chrono::duration<double, micro> t_descifrado = t_end - t_start;

    string mensaje_recuperado = numberToString(m_descifrado);

    cout << "[Descifrado]\n";
    cout << "  - Numero recuperado: " << m_descifrado << "\n";
    cout << "  - Texto recuperado: \"" << mensaje_recuperado << "\"\n";
    cout << "  - Tiempo: " << t_descifrado.count() << " us\n\n";

    if (mensaje == mensaje_recuperado) {
        cout << "RESULTADO: [EXITO] Texto recuperado intacto.\n";
    } else {
        cout << "RESULTADO: [FALLO/DESTRUIDO] El texto se corrompio.\n";
    }
    cout << "\n";
}

int main() {
    ejecutarPruebaRSA(61, 53, "A", 17);
    ejecutarPruebaRSA(40009, 40013, "RSA", 65537);
    ejecutarPruebaRSA(2147483647LL, 2147483629LL, "Cripto!", 65537);
    ejecutarPruebaRSA(40009, 40013, "HOLA", 17);
    return 0;
}
