#include <string>
#include <iostream>
using namespace std;
struct NodoPP
{
    string plato;
    unsigned int pos;
    NodoPP *sig;
};

class TablaPP
{
private:
    unsigned int espaciosReservados;
    NodoPP **tablaPP;
    int (*funcionHash)(string);

    /*
    PRE:
    POS: Devuelve la posición que tiene asociado el plato en la tabla de hash
    */
    unsigned int pos(string plato)
    {
        unsigned int bucket = funcionHash(plato) % espaciosReservados;
        return bucket;
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
    POS: Inicializa un objeto TablaPP
    */
    TablaPP(unsigned int cota, int (*fHash)(string))
    {
        unsigned int nuevaCota = sigPrimo(cota);
        espaciosReservados = nuevaCota;
        tablaPP = new NodoPP *[nuevaCota];
        funcionHash = fHash;
        for (int i = 0; i < espaciosReservados; i++)
        {
            tablaPP[i] = NULL;
        }
    }

    /*
    PRE:
    POS: le asocia al plato una posicion y lo inserta en la tabla de hash
    */

    void agregarPP(string plato, unsigned int posP)
    {
        NodoPP *nuevo = new NodoPP;
        nuevo->plato = plato;
        nuevo->pos = posP;
        nuevo->sig = NULL;
        if (tablaPP[pos(plato)] == NULL)
        {
            tablaPP[pos(plato)] = nuevo;
        }
        else
        {
            nuevo->sig = tablaPP[pos(plato)];
            tablaPP[pos(plato)] = nuevo;
        }
    }

    /*
    PRE: El plato existe en la tabla
    POS:
    */
    unsigned int recuperarPosicion(string plato)
    {
        NodoPP *iter = tablaPP[pos(plato)];
        while (iter->plato != plato)
            iter = iter->sig;
        return iter->pos;
    }

    /*
    PRE:
    POS: libera la memoria de la tabla de hash
    */
    ~TablaPP()
    {
        for (int i = 0; i < this->espaciosReservados; i++)
        {
            while (this->tablaPP[i] != NULL)
            {
                NodoPP *borro = this->tablaPP[i];
                this->tablaPP[i] = this->tablaPP[i]->sig;
                delete borro;
                borro = NULL;
            }
        }
        delete[] this->tablaPP;
        this->tablaPP = NULL;
    }
};
