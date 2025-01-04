#include <iostream>
#include <string>
#include "Ejercicio7/minHeap.cpp"
using namespace std;


/*
PRE:
POS: separa "numero" en sus digitos y los inserta en el MinHeap "digitos"
*/
void insertarDigitosEnHeap(unsigned int numero, MinHeap &digitos)
{
    digitos.insertar(numero % 10);
    numero = numero / 10;
    while (numero > 0)
    {
        digitos.insertar(numero % 10);
        numero = numero / 10;
    }
}

int main()
{

    unsigned int N;
    cin >> N;

    unsigned int cantDigitos = (to_string(N)).length();

    MinHeap digitos = MinHeap(cantDigitos);
    insertarDigitosEnHeap(N, digitos);

    string N1 = "";
    string N2 = "";
    int largoN1 = 0;
    int largoN2 = 0;

    while (!digitos.esVacio())
    {

        NodoHeap *nodo = digitos.peek();
        unsigned int digito = nodo->digito;

        if (largoN1 <= largoN2)
        {
            N1 += to_string(digito);
            largoN1++;
        }
        else
        {
            N2 += to_string(digito);
            largoN2++;
        }
        delete nodo;
        nodo = NULL;
    }


    cout << stoi(N1) + stoi(N2) << endl;

    return 0;
}
