#include <iostream>
#include <string>
#include "Ejercicio6/MFSET.cpp"
#include "Ejercicio6/minHeap.cpp"
using namespace std;

struct ListaArista
{
    unsigned int origen;
    unsigned int destino;
    int peso;
    ListaArista *sig;
};
struct arista
{
    int verticeOrigen;
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
    PRE:
    POS: devuelve el arbol de cubrimiento minimo del grafo en forma de lista de aristas (aplicando el algoritmo de kruskall)
    */
    ListaArista *kruskal(MinHeap ordenAristas)
    {
        MFSET mf = MFSET(this->vertices);
        ListaArista *aceptadas = NULL;
        unsigned int cantAceptadas = 0;
        while (cantAceptadas < this->vertices - 1)
        {
            NodoHeap *nodo = ordenAristas.peek();
            bool produceCiclo = mf.merge(nodo->origen, nodo->destino);
            if (!produceCiclo)
            {
                ListaArista *nuevaArista = new ListaArista;
                nuevaArista->origen = nodo->origen;
                nuevaArista->destino = nodo->destino;
                nuevaArista->peso = nodo->peso;
                nuevaArista->sig = aceptadas;
                aceptadas = nuevaArista;
                cantAceptadas++;
            }
            delete nodo;
            nodo = NULL;
        }
        return aceptadas;
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
    unsigned int N;
    unsigned int M;
    cin >> N >> M;
    Grafo G = Grafo(N);
    for (int i = 0; i < M; i++)
    {
        unsigned int A;
        unsigned int B;
        int C;
        cin >> A >> B >> C;
        G.insertarArista(A, B, C);
    }

    MinHeap ordenAristas = MinHeap(M);
    for (int i = 1; i <= N; i++)
    {
        arista *ady = G.obtenerAdyacentes(i);
        while (ady != NULL)
        {
            ordenAristas.insertar(i, ady->verticeDestino, ady->costo);
            arista *borro = ady;
            ady = ady->sig;
            delete borro;
            borro = NULL;
        }
    }

    ListaArista *ACM = G.kruskal(ordenAristas);
    int costoMin = 0;
    while (ACM != NULL)
    {
        costoMin += ACM->peso;
        ListaArista *borro = ACM;
        ACM = ACM->sig;
        delete borro;
        borro = NULL;
    }
    cout << costoMin << endl;

    return 0;
}