#include <iostream>
#include <cassert>
#include <string>
using namespace std;

struct NodoLista
{
    string dato;
    NodoLista *sig;
};
struct cabezal_cola
{
    NodoLista *ppio;
    NodoLista *fin;
};
class cola
{
private:
    cabezal_cola *lista;
    unsigned int cantElementos;

public:
    /*
    PRE:
    POS: inicializa una cola FIFO
    */
    cola()
    {
        this->lista = new cabezal_cola;
        this->lista->fin = NULL;
        this->lista->ppio = NULL;
        this->cantElementos = 0;
    }

    /*
    PRE:
    POS: encola un elemento a la cola siguiendo la política FIFO
    */
    void encolar(string e)
    {
        NodoLista *nuevo = new NodoLista;
        nuevo->dato = e;
        nuevo->sig = NULL;
        if (this->lista->ppio == NULL)
        {
            this->lista->ppio = nuevo;
            this->lista->fin = nuevo;
            this->cantElementos++;
        }
        else
        {
            this->lista->fin->sig = nuevo;
            this->lista->fin = nuevo;
            this->cantElementos++;
        }
    }
    /*
    PRE: !esVacia()
    POS: desencola un elemento de la cola siguiendo la política FIFO
    */
    NodoLista *desencolar()
    {
        NodoLista *ret = new NodoLista;
        ret->dato = this->lista->ppio->dato;
        ret->sig = NULL;
        if (this->cantElementos == 1)
        {
            delete this->lista->ppio;
            this->lista->ppio = NULL;
            this->lista->fin = NULL;
            this->cantElementos--;
        }
        else
        {
            NodoLista *borro = this->lista->ppio;
            this->lista->ppio = this->lista->ppio->sig;
            delete borro;
            borro = NULL;
            this->cantElementos--;
        }
        return ret;
    }
    /*
    PRE:
    POS: devuelve true sii la cola no tiene elementos
    */
    bool esVacia()
    {
        return this->cantElementos == 0;
    }
    /*
    PRE:
    POS: libera la memoria de la cola
    */
    ~cola()
    {
        while (this->lista->ppio != NULL)
        {
            NodoLista *borro = NULL;
            this->lista->ppio = this->lista->ppio->sig;
            delete borro;
            borro = NULL;
        }
        delete this->lista;
        this->lista = NULL;
    }
};
