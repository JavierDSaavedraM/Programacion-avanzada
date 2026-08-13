/*
Nombres:
Sergio Alejandro Zamora Dávila 616148
Javi chan 624198
Roberto De la Fuente 593303
*/

#include <iostream>
#include <string>
using namespace std;

int eliminar_k_digitos(int valor_entrada, int k_entrada)
{
    int valor = valor_entrada;
    int k = k_entrada;
    bool breaker = false;
    int contador_eliminados = 0;
    string valor_str = to_string(valor);

    if (valor_str.length() == k)
    {
        return 0;
    }
    else if (valor_str.length() < k)
    {
        return -1;
    }

    for (; contador_eliminados < k; contador_eliminados++)
    {
        breaker = false;
        for (int i = 0; i < valor_str.length() - 1; i++)
        {
            if (valor_str[i] > valor_str[i + 1])
            {
                valor_str.erase(i, 1);
                breaker = true;
                break;
            }
        }
        if (!breaker)
            break;
    }
    int restantes = k - contador_eliminados;
    valor_str.erase(valor_str.length() - restantes, restantes);

    int resultado_numerico = stoi(valor_str);

    return resultado_numerico;
}

void imprimir(int x, int y)
{
    int respuesta = eliminar_k_digitos(x, y);
    if (respuesta == -1)
    {
        cout << "Error, el valor es menor que el numero a eliminar" << endl;
    }
    else
    {
        cout << respuesta << endl;
    }
}

int main()
{
    imprimir(1432219, 3);  // Output: 1219
    imprimir(10200, 1);    // Output: 200
    imprimir(10, 2);       // Output: 0
    imprimir(12345, 1);    // Output: 1234
    imprimir(15234, 1);    // Output: 1432
    imprimir(87653899, 6); // Output: 38
    imprimir(3, 4);        // Output: Error
    return 0;
}
