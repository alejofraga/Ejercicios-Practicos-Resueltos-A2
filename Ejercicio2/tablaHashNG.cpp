#include <cassert>
#include <string>
#include <iostream>
#include "heapNodoPelis.cpp"
using namespace std;

struct NodoGenero
{
    string nombre;
    HeapNP *pelis;
    NodoGenero *sig;
};

class TablaHash
{
private:
    unsigned int cantidadGeneros;
    unsigned int espaciosReservados;
    int (*funcionHash)(string);
    NodoGenero **tabla;

    /*
    PRE:
    POS: Devuelve la posición que tiene asociado el genero en la tabla de hash
    */
    unsigned int pos(string genero)
    {
        unsigned int bucket = abs(funcionHash(genero)) % espaciosReservados;
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

    /*
    PRE:
    POS: inserta genero al final de la lista ubicada en el bucket pos
    */
    void insertarEnTabla(NodoGenero *genero, unsigned int pos)
    {
        if (tabla[pos] == NULL)
            tabla[pos] = genero;
        else
        {
            NodoGenero *iter = tabla[pos];
            while (iter->sig != NULL)
            {
                iter = iter->sig;
            }
            iter->sig = genero;
        }
    }

public:

    /*
    PRE:
    POS: inicializa un objeto TablaHash
    */
    TablaHash(unsigned int cantidadGeneros, int (*fHash)(string))
    {
        unsigned int nuevaCota = sigPrimo(cantidadGeneros);
        tabla = new NodoGenero *[nuevaCota];
        for (int i = 0; i < nuevaCota; i++)
        {
            tabla[i] = NULL;
        }
        cantidadGeneros = 0;
        funcionHash = fHash;
        espaciosReservados = nuevaCota;
    }



    /*
    PRE:
    POS: devuelve true si la tabla no tiene elementos
    */
    bool esVacio()
    {
        return cantidadGeneros == 0;
    }

    /*
    PRE:
    POS: inserta genero en la tabla de hash
    */
    void agregarGenero(string genero)
    {
        NodoGenero *nuevo = new NodoGenero;
        nuevo->nombre = genero;
        nuevo->pelis = NULL;
        nuevo->sig = NULL;
        unsigned int bucket = pos(genero);
        nuevo->sig = tabla[bucket];
        tabla[bucket] = nuevo;
        cantidadGeneros++;
    }

    /*
    PRE: nombreGenero debe existir
    POS: inserta una nueva pelicula dentro del genero nombreGenero
    */
    void asociarPeliAGenero(unsigned int idPeli, string nombreGenero)
    {
        unsigned int bucket = pos(nombreGenero);
        NodoGenero *iter = tabla[bucket];
        while (iter->nombre != nombreGenero)
            iter = iter->sig;
        if (iter->pelis == NULL)
        {
            iter->pelis = new HeapNP(5);
        }
        iter->pelis->insertar(0, 0, idPeli);
    }

    /*
    PRE: nombreGenero debe existir, idPeli debe existir y deben estar asociados.
    POS: actualiza el promedio de puntuaciones de la pelicula teniendo en cuenta la nueva puntuacion
    */
    void agregarPuntuacion(string nombreGenero, unsigned int idPeli, unsigned int puntuacion)
    {
        unsigned int bucket = pos(nombreGenero);
        NodoGenero *iter = tabla[bucket];
        while (iter->nombre != nombreGenero)
            iter = iter->sig;
        iter->pelis->actualizarValor(idPeli, puntuacion);
    }

    /*
    PRE: nombreGenero debe existir
    POS: devuelve el ID de la película con la calificación promedio más alta dentro del genero. En caso de empate, devuelve el ID de película más pequeño.

    */
    unsigned int recuperarIdCorrespondiente(string nombreGenero)
    {
        unsigned int bucket = pos(nombreGenero);
        NodoGenero *iter = tabla[bucket];
        while (iter->nombre != nombreGenero)
            iter = iter->sig;
        NodoPelis *nodo = iter->pelis->peek();
        return nodo->id;
    }

    /*
    PRE:
    POS: libera la memoria de la tabla
    */
    ~TablaHash()
    {
        for (int i = 0; i < this->espaciosReservados; i++)
        {
            this->tabla[i]->pelis->destruir();
            delete this->tabla[i];
        }
        delete[] this->tabla;
        this->tabla = NULL;
    }
};

/*
PRE:
POS: asocia un valor entero a genero
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
