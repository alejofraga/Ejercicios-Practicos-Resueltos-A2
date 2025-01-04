#include <iostream>
#include <string>
#include "Ejercicio4/grafo.cpp"
#include "Ejercicio4/minHeap.cpp"
#include "Ejercicio4/tablaPlatos-Pos.cpp"
#include "Ejercicio4/cola.cpp"
using namespace std;

/*
PRE:
POS: asocia un valor entero a cada genero
*/
int miHash(string genero)
{
    unsigned int valorHash = 0;
    for (int i = 0; i < genero.length(); i++)
    {
        valorHash = (valorHash * 31) ^ genero[i] + 37;
    }
    return valorHash;
}

int main()
{
    int P;
    int D;
    cin >> P >> D;
    TablaPP platoPos = TablaPP(P, miHash);
    string *posiciones = new string[P];
    for (int i = 0; i < P; i++)
    {
        string plato;
        cin >> plato;
        platoPos.agregarPP(plato, i);
        posiciones[i] = plato;
    }
    
    GrafoDirigidoNoPonderado preferencias = GrafoDirigidoNoPonderado(P);
    for (int i = 0; i < D; i++)
    {
        string platoA;
        string platoB;
        cin >> platoA >> platoB;
        unsigned int posPlatoB = platoPos.recuperarPosicion(platoB);
        unsigned int posPlatoA = platoPos.recuperarPosicion(platoA);
        preferencias.insertarArista(posPlatoA, platoB, posPlatoB);
    }

    unsigned int *gradosIncidencia = new unsigned int[P]();
    MinHeapPlatos S = MinHeapPlatos(P);
    unsigned int cantidadDePlatosProcesados = 0;
    cola retorno = cola();

    for (int i = 0; i < P; i++)
    {
        string plato = posiciones[i];
        gradosIncidencia[i] = preferencias.cantIncidentes(plato);
        if (gradosIncidencia[i] == 0)
            S.insertar(plato, i);
    }

    while (!S.esVacio())
    {
        cantidadDePlatosProcesados++;
        NodoPlato *nodo = S.peek();
        retorno.encolar(nodo->plato);
        arista *adyacentes = preferencias.obtenerAdyacentes(nodo->pos);
        while (adyacentes != NULL)
        {
            gradosIncidencia[adyacentes->pos]--;
            if (gradosIncidencia[adyacentes->pos] == 0)
            {
                S.insertar(posiciones[adyacentes->pos], adyacentes->pos);
            }
            arista *borro = adyacentes;
            adyacentes = adyacentes->sig;
            delete borro;
            borro = NULL;
        }
        delete nodo;
        nodo = NULL;
    }
    delete[] gradosIncidencia;
    delete[] posiciones;

    if (cantidadDePlatosProcesados == P)
    {
        while (!retorno.esVacia())
        {
            NodoLista *nodo = retorno.desencolar();
            cout << nodo->dato << endl;
            delete nodo;
            nodo = NULL;
        }
    }
    else
    {
        cout << "CICLO DETECTADO" << endl;
    }

    return 0;
}
