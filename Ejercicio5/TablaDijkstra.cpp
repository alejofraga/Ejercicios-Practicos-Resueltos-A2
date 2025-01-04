#include <iostream>
#include <string>
using namespace std;

struct ListaCamino
{
    unsigned int vertice;
    ListaCamino *sig;
};
class TablaResultado
{
private:
    unsigned int origen;
    unsigned int espaciosReservados;
    int *vertices;
    int *costos;
    int *vengoDe;
    bool *visitados;

public:
    /*
    PRE:
    POS: incializa un objeto TablaResultado donde se almacenara la informacion obtenida al aplicar Dijkstra a nuestro grafo para "origen"
    */
    TablaResultado(unsigned int cantVertices, unsigned int origen)
    {
        this->origen = origen;
        this->espaciosReservados = cantVertices + 1;
        this->vertices = new int[espaciosReservados];
        this->costos = new int[espaciosReservados];
        this->vengoDe = new int[espaciosReservados];
        this->visitados = new bool[espaciosReservados];
        for (int i = 1; i <= cantVertices; i++)
        {
            this->vertices[i] = i;
            this->costos[i] = INT_MAX;
            this->vengoDe[i] = -1;
            this->visitados[i] = false;
        }
    }
    /*
    PRE: ambos "vertice" y "vengoDe" deben ser vertices validos
    POS: inserta la informacion (vengoDe, costo) en la tabla en la fila "vertice"
    */
    void insertarCosto(unsigned int vertice, unsigned int vengoDe, unsigned int costo)
    {
        this->vengoDe[vertice] = vengoDe;
        this->costos[vertice] = costo;
    }
    /*
    PRE: "vertice" debe ser un vertice válido
    POS: marca "vertice" como vertice visitado
    */
    void visitado(unsigned int vertice)
    {
        this->visitados[vertice] = true;
    }
    /*
    PRE: "vertice" debe ser un vertice válido
    POS: devuelve true sii "vertice" fue visitado
    */
    bool esVisitado(unsigned int vertice)
    {
        return this->visitados[vertice];
    }

    /*
    PRE: "vertice" debe ser un vertice válido
    POS: devuelve el costo de llegar a vertice a partir de origen
    */
    unsigned int retornarCosto(unsigned int vertice)
    {
        return this->costos[vertice];
    }
    /*
    PRE: "vertice" debe ser un vertice válido
    POS: devuelve el costo de llegar a vertice a partir de origen, si no se puede llegar devuelve -1
    */
    int costoParticular(unsigned int destino)
    {
        if (this->costos[destino] != INT_MAX)
        {
            return this->costos[destino];
        }
        else
            return -1;
    }

    ~TablaResultado()
    {
        delete[] this->vertices;
        delete[] this->costos;
        delete[] this->vengoDe;
        delete[] this->visitados;
        this->vertices = NULL;
        this->costos = NULL;
        this->vengoDe = NULL;
        this->visitados = NULL;
    }
};
