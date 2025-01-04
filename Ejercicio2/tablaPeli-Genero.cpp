#include <cassert>
#include <string>
#include <iostream>
using namespace std;
struct NodoPG
{
    unsigned int idPeli;
    string genero;
    NodoPG *sig;
};

class TablaPGSIMPLE
{
private:
    unsigned int espaciosReservados;
    NodoPG **tablaPG;

    /*
   PRE:
   POS: Devuelve la posición que tiene asociada la pelicula en la tabla de hash
   */
    unsigned int pos(unsigned int idPeli)
    {
        unsigned int bucket = idPeli % espaciosReservados;
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
   POS: inicializa un objeto TablaPGSIMPLE
   */
    TablaPGSIMPLE(unsigned int cota)
    {
        unsigned int nuevaCota = sigPrimo(cota);
        espaciosReservados = nuevaCota;
        tablaPG = new NodoPG *[nuevaCota];
        for (int i = 0; i < espaciosReservados; i++)
        {
            tablaPG[i] = NULL;
        }
    }

    /*
   PRE:
   POS: asocia la pelicula al genero y se agrega a la tabla de hash
   */
    void agregarPG(unsigned int idPeli, string genero)
    {
        NodoPG *nuevo = new NodoPG;
        nuevo->genero = genero;
        nuevo->idPeli = idPeli;
        nuevo->sig = NULL;
        if (tablaPG[pos(idPeli)] == NULL)
        {
            tablaPG[pos(idPeli)] = nuevo;
        }
        else
        {
            nuevo->sig = tablaPG[pos(idPeli)];
            tablaPG[pos(idPeli)] = nuevo;
        }
    }

    /*
   PRE: idPeli debe existir
   POS: devuelve el genero que tiene asociada la pelicula cuyo id es idPeli
   */
    string buscarGenero(unsigned int idPeli)
    {

        unsigned int bucket = pos(idPeli);
        NodoPG *iter = tablaPG[bucket];
        while (iter->idPeli != idPeli && iter->sig != NULL)
        {
            iter = iter->sig;
        }

        return iter->genero;
    }

    /*
    PRE:
    POS: libera la memoria de la tabla
    */
    ~TablaPGSIMPLE()
    {
        for (int i = 0; i < this->espaciosReservados; i++)
        {
            delete this->tablaPG[i];
        }
        delete[] this->tablaPG;
        this->tablaPG = NULL;
    }
};
