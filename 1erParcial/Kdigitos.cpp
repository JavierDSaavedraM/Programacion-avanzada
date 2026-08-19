/*
Nombres:
Sergio Alejandro Zamora Dávila 616148
Javi Djorkaef 624198
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

    // Si k es igual al valor del tamaño del lenght del numero ingresado entonces automáticamente el resultado es 0
    if (valor_str.length() == k)
    {
        return 0;
    }
    // Como no se pueden eliminar más números de los que se tienen entonces regresamos -1, y esto lo tratamos como un error
    else if (valor_str.length() < k)
    {
        return -1;
    }

    // La lógica que usamos es que va a recorrer el numero de uno a uno, y va a borrar el primer digito que sea mayor que el que le sigue 
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
        // Si ya no hay digitos mayores que su siguiente, el numero ya está ordenado ascendentemente y toca eliminar por el final todos los numeros que falten
        if (!breaker)
            break;
    }

    // Si aun quedan eliminaciones pendientes, se quitan del final
    int restantes = k - contador_eliminados;
    valor_str.erase(valor_str.length() - restantes, restantes);

    // utilizamos stoi, que combierte el numero de string a entero, además de que tambien descarta los ceros a la izquierda 
    int resultado_numerico = stoi(valor_str);

    return resultado_numerico;
}

// Creamos una funcion que nos ayuda a imprimir el resultado obtenido, aquí es donde también tomamos en cuenta la opción de que el número sea menor que el valor de k, por lo que es un error
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
    // Utilizamos los casos de prueba que nos proporcionó el profesor durante clase para comprobar el comportamiento del algoritmo 
    imprimir(1432219, 3);  // Output: 1219
    imprimir(10200, 1);    // Output: 200
    imprimir(10, 2);       // Output: 0
    imprimir(12345, 1);    // Output: 1234
    imprimir(15234, 1);    // Output: 1432
    imprimir(87653899, 6); // Output: 38
    imprimir(3, 4);        // Output: Error
    return 0;
}
