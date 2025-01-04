#include <iostream>
#include <string>
#include "Ejercicio3/heapUrgencias.cpp"
using namespace std;

int main()
{
    unsigned int N;
    cin >> N;
    HeapUrgencias urgencias = HeapUrgencias(N);
    for (int i = 0; i < N; i++)
    {
        int P;
        int T;
        int U;
        cin >> P >> T >> U;
        urgencias.insertar(U, T, P);
    }

    while (!urgencias.esVacio())
    {
        NodoUrgencias *nodo = urgencias.peek();
        cout << nodo->P << endl;
    }
}

