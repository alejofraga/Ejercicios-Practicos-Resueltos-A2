#include <iostream>
#include <string>
#include "Ejercicio5/TablaDijkstra.cpp"
#include "Ejercicio5/CPext.cpp"
using namespace std;

struct arista
{
    int verticeDestino;
    int costo;
    arista *sig;
};
class Grafo
{

private:
    unsigned int vertices;
    unsigned int espaciosReservados;
    arista **listaAdy;

public:
    /*
     PRE:
     POS: inicializa el grafo
     */
    Grafo(int cantVertices)
    {
        this->vertices = cantVertices;
        this->espaciosReservados = cantVertices + 1;
        this->listaAdy = new arista *[espaciosReservados];
        for (int i = 0; i < espaciosReservados; i++)
        {
            this->listaAdy[i] = NULL;
        }
    }
    /*
    PRE:
    POS: inserta la arista verticeA -> verticeB
    */
    void insertarArista(int verticeA, int verticeB, int costo)
    {

        arista *nueva = new arista;
        nueva->verticeDestino = verticeB;
        nueva->costo = costo;
        nueva->sig = listaAdy[verticeA];
        listaAdy[verticeA] = nueva;
    }

    /*
    PRE:
    POS: devuelve todos los adyacentes a "vertice"
    */
    arista *obtenerAdyacentes(unsigned int vertice)
    {
        arista *ret = NULL;
        arista *iter = listaAdy[vertice];
        while (iter != NULL)
        {
            arista *nueva = new arista;
            nueva->verticeDestino = iter->verticeDestino;
            nueva->costo = iter->costo;
            nueva->sig = ret;
            ret = nueva;
            iter = iter->sig;
        }
        return ret;
    }

    /*
    PRE: 1<=Origen<=vertices, el grafo no debe tener aristas cuyo costo sea negativo
    POS: Completa la TablaResultado segun el algoritmo de Dijkstra
    */
    void Dijkstra(TablaResultado &T, CPext cola, unsigned int origen)
    {
        cola.actualizarValor(origen, 0);
        T.insertarCosto(origen, -1, 0);

        while (!cola.esVacio())
        {
            NodoHeap *nodo = cola.peek();
            T.visitado(nodo->vertice);
            arista *adyV = obtenerAdyacentes(nodo->vertice);
            while (adyV != NULL)
            {
                if (nodo->costo != INT_MAX)
                {
                    unsigned int costo = adyV->costo + nodo->costo;
                    if (costo < T.retornarCosto(adyV->verticeDestino) && !T.esVisitado(adyV->verticeDestino))
                    {
                        T.insertarCosto(adyV->verticeDestino, nodo->vertice, costo);
                        cola.actualizarValor(adyV->verticeDestino, costo);
                    }
                }

                arista *borro = adyV;
                adyV = adyV->sig;
                delete borro;
                borro = NULL;
            }
        }
    }
    /*
    PRE:
    POS: libera la memoria del grafo
    */
    ~Grafo()
    {
        for (int i = 0; i <= this->vertices; i++)
        {
            while (this->listaAdy[i] != NULL)
            {
                arista *borro = this->listaAdy[i];
                this->listaAdy[i] = this->listaAdy[i]->sig;
                delete borro;
                borro = NULL;
            }
        }
    }
};

int main()
{

    int N; // vertices
    int M; // aristas
    cin >> N >> M;
    Grafo G = Grafo(N);
    for (int i = 0; i < M; i++)
    {
        int A; // vertice A
        int B; // vertice B
        int C; // costo A -> B
        cin >> A >> B >> C;
        G.insertarArista(A, B, C);
    }
    int O; // vertice origen
    int D; // vertice destino
    cin >> O >> D;

    TablaResultado T = TablaResultado(N, O);
    CPext cola = CPext(N);
    for (int i = 1; i <= N; i++)
    {
        cola.insertar(i, INT_MAX);
    }
    G.Dijkstra(T, cola, O);
    cout << T.costoParticular(D);

    return 0;
}