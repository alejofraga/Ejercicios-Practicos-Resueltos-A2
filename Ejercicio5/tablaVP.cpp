#include <iostream>
#include <string>
using namespace std;

struct NodoHash
{
    unsigned int vertice;
    unsigned int pos;
    NodoHash *sig;
};

class tablaVP
{
private:
    NodoHash **tabla;
    unsigned int espaciosReservados;

    /*
    PRE:
    POS: Devuelve la posición que tiene asociado el vertice en la tabla de hash
    */
    unsigned int pos(unsigned int vertice)
    {
        return vertice % espaciosReservados;
    }

    /*
    PRE:
    POS: Devuelve true si num es un número primo
    */
    bool esPrimo(unsigned int num)
    {
        if (num == 0 || num == 1 || num == 4 || num == 2)
            return false;
        for (int x = 2; x < num / 2; x++)
        {
            if (num % x == 0)
                return false;
        }
        return true;
    }

    /*
    PRE:
    POS: devuelve num si num ya es primo, de lo contrario devuelve el número primo mayor a num mas cercano.
    */
    unsigned int sigPrimo(unsigned int num)
    {
        while (!esPrimo(num))
            num++;
        return num;
    }

public:
    /*
    PRE:
    POS: inicializa una tabla de hash: vertice-> posicionEnHeap
    */
    tablaVP(unsigned int cota)
    {
        unsigned int nuevaCota = sigPrimo(cota);
        this->espaciosReservados = nuevaCota;
        this->tabla = new NodoHash *[nuevaCota];
        for (int i = 0; i < nuevaCota; i++)
        {
            this->tabla[i] = NULL;
        }
    }
    /*
    PRE: vertice no debe existir en la tabla de hash
    POS: le asocia a "vertice" la posicion "posHeap" del heap y lo inserta en la tabla de hash
    */
    void insertarVP(unsigned int vertice, unsigned int posHeap)
    {
        unsigned int bucket = pos(vertice);
        NodoHash *nuevo = new NodoHash;
        nuevo->pos = posHeap;
        nuevo->vertice = vertice;
        nuevo->sig = tabla[bucket];
        tabla[bucket] = nuevo;
    }
    /*
    PRE: vertice debe existir en la tabla de hash
    POS: devuelve la posicion en el heap de "vertice"
    */
    unsigned int recuperarPos(unsigned int vertice)
    {
        unsigned int bucket = pos(vertice);
        NodoHash *iter = tabla[bucket];
        while (iter != NULL)
        {
            if (iter->vertice == vertice)
                return iter->pos;
            else
                iter = iter->sig;
        }
    }
    /*
    PRE: vertice debe existir en la tabla de hash
    POS: elimina el vertice con su respectiva posicion asociada de la tabla de hash
    */
    void eliminarVP(unsigned int vertice)
    {
        unsigned int bucket = pos(vertice);
        if (tabla[bucket]->vertice == vertice)
        {
            NodoHash *borro = tabla[bucket];
            tabla[bucket] = tabla[bucket]->sig;
            delete borro;
            borro = NULL;
        }
        else
        {
            NodoHash *iter = tabla[bucket];
            while (iter->sig != NULL && iter->sig->vertice != vertice)
            {
                iter = iter->sig;
            }
            NodoHash *borro = iter->sig;
            iter->sig = iter->sig->sig;
            delete borro;
            borro = NULL;
        }
    }

    /*
    PRE: vertice debe existir en la tabla de hash
    POS: actualiza la posicion asociada a "vertice"
    */
    void actualizarVP(unsigned int vertice, unsigned int nuevaPos)
    {

        unsigned int bucket = pos(vertice);
        NodoHash *iter = tabla[bucket];
        while (iter != NULL && iter->vertice != vertice)
            iter = iter->sig;
        iter->pos = nuevaPos;
    }

    /*
    PRE: 
    POS: libera la memoria de la tabla
    */
    ~tablaVP()
    {
        for (int i = 0; i < this->espaciosReservados; i++)
        {
            while (this->tabla[i] != NULL)
            {
                NodoHash *borro = this->tabla[i];
                this->tabla[i] = this->tabla[i]->sig;
                delete borro;
                borro = NULL;
            }
        }
        delete[] this->tabla;
        this->tabla = NULL;
    }
};
