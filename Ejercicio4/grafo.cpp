
#include <iostream>
#include <string>
using namespace std;

struct arista
{
    string precedeA;
    unsigned int pos;
    arista *sig;
};

class GrafoDirigidoNoPonderado
{
private:
    bool *verticesEliminados;
    unsigned int vertices;
    unsigned int espaciosReservados;
    arista **listaAdy;

public:


    /*
    PRE:
    POS: inicializa el grafo
    */
    GrafoDirigidoNoPonderado(int cantVertices)
    {
        this->verticesEliminados = new bool[cantVertices];
        this->vertices = cantVertices;
        this->espaciosReservados = cantVertices;
        this->listaAdy = new arista *[this->vertices];
        for (int i = 0; i < vertices; i++)
        {
            this->listaAdy[i] = NULL;
            this->verticesEliminados[i] = false;
        }
    }

    /*
    PRE:
    POS: inserta la precedencia PlatoA,PlatoB en el grafo
    */
    void insertarArista(unsigned int posPlatoA, string platoB, unsigned int posPlatoB)
    {

        arista *nueva = new arista;
        nueva->precedeA = platoB;
        nueva->pos = posPlatoB;
        nueva->sig = listaAdy[posPlatoA];
        listaAdy[posPlatoA] = nueva;
    }

    /*
    PRE:
    POS: devuelve todos los platos que dependen del plato asociado a posPlato
    */
    arista *obtenerAdyacentes(unsigned int posPlato)
    {
        arista *ret = NULL;
        arista *iter = listaAdy[posPlato];
        while (iter != NULL)
        {
            arista *nueva = new arista;
            nueva->pos = iter->pos;
            nueva->precedeA = iter->precedeA;
            nueva->sig = ret;
            ret = nueva;
            iter = iter->sig;
        }
        return ret;
    }

    /*
    PRE: platoA debe existir en el grafo
    POS: devuelve la cantidad de platos que preceden a platoA
    */
    unsigned int cantIncidentes(string platoA)
    {

        unsigned int cont = 0;
        for (int i = 0; i < vertices; i++)
        {
            arista *iter = listaAdy[i];
            while (iter != NULL)
            {
                if (iter->precedeA == platoA)
                    cont++;

                iter = iter->sig;
            }
        }

        return cont;
    }

    /*
    PRE:
    POS: Devuelve la cantidad de vertices (platos) del grafo
    */
    unsigned int cantidadDeVertices()
    {
        return this->vertices;
    }
    /*
    PRE:
    POS: libera la memoria del grafo
    */
    ~GrafoDirigidoNoPonderado()
    {
        for (int i = 0; i < this->espaciosReservados; i++)
        {
            while (this->listaAdy[i] != NULL)
            {
                arista *nodo = this->listaAdy[i];
                this->listaAdy[i] = this->listaAdy[i]->sig;
                delete nodo;
                nodo = NULL;
            }
        }
        delete[] this->listaAdy;
        this->listaAdy = NULL;
    }
};
