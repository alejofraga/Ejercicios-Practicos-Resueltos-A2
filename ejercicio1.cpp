#include "Ejercicio1\miHeap.cpp"
#include <string>
#include <iostream>
using namespace std;

struct NodoHash
{
    string plato;
    unsigned int ordenes;
    NodoHash *sig;
};

class Restaurante
{
private:
    unsigned int espaciosReservados;
    unsigned int cantPlatos;
    int (*funcionHash)(string);
    NodoHash **tabla;

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
    POS: devuelve el factor de carga de la tabla de hash
    */
    float factorDeCarga()
    {
        return (float)cantPlatos / espaciosReservados;
    }

    /*
    PRE:
    POS: Devuelve la posición que tiene asociada el plato en la tabla de hash
    */
    unsigned int posPlato(string plato)
    {
        unsigned int pos = abs(funcionHash(plato)) % espaciosReservados;
        return pos;
    }

    /*
    PRE:
    POS: si el plato ya existe en la tabla de hash, aumenta la cantidad de ordenes del mismo, de lo contrario crea y agrega un nuevo nodo a la misma
    */
    void insertarEnTabla(string plato, unsigned int pos)
    {
        if (tabla[pos] == NULL)
        {
            NodoHash *nuevo = new NodoHash;
            nuevo->plato = plato;
            nuevo->ordenes = 1;
            nuevo->sig = NULL;
            tabla[pos] = nuevo;
        }
        else
        {
            NodoHash *iter = tabla[pos];
            while (iter != NULL)
            {
                if (iter->plato == plato)
                {
                    iter->ordenes++;
                    return;
                }
                else if (iter->sig == NULL)
                {
                    break;
                }
                else
                {
                    iter = iter->sig;
                }
            }
            NodoHash *nuevo = new NodoHash;
            nuevo->plato = plato;
            nuevo->ordenes = 1;
            nuevo->sig = NULL;
            iter->sig = nuevo;
        }
    }

public:
    /*
    PRE:
    POS: Inicicializa un objeto restaurante
    */
    Restaurante(unsigned int cota, int (*fHash)(string))
    {
        unsigned int nuevaCota = sigPrimo(cota);
        tabla = new NodoHash *[nuevaCota];
        for (int i = 0; i < nuevaCota; i++)
        {
            tabla[i] = NULL;
        }
        espaciosReservados = nuevaCota;
        cantPlatos = 0;
        funcionHash = fHash;
    }

    /*
    PRE:
    POS: Devuelve la cantidad de platos en la tabla de hash
    */
    unsigned int cantidadDePlatos()
    {
        return this->cantPlatos;
    }
    /*
    PRE:
    POS: Inserta el plato en la tabla de hash, aumentando la cantidad de platos en la misma
    */
    void agregarOrden(string plato)
    {
        unsigned int pos = posPlato(plato);
        insertarEnTabla(plato, pos);
        cantPlatos++;
    }
    /*
    PRE:
    POS: Devuelve true si no hay platos en la tabla de hash
    */
    bool esVacio()
    {
        return cantPlatos == 0;
    }

    /*
    PRE:
    POS: agrega todos los platos a un heap y lo retorna
    */
    MaxHeap recuperarTodos()
    {
        MaxHeap PorOrden(cantPlatos);
        for (int i = 0; i < espaciosReservados; i++)
        {
            if (tabla[i] != NULL)
            {
                NodoHash *iter = tabla[i];
                while (iter != NULL)
                {
                    PorOrden.insertar(iter->plato, iter->ordenes);
                    iter = iter->sig;
                    cantPlatos--;
                }
            }
        }
        return PorOrden;
    }

    /*
    PRE:
    POS: Libera la memoria de la tabla de hash
    */
    ~Restaurante()
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
        delete[] tabla;
        tabla = NULL;
    }
};

/*
PRE:
POS: Función de hash, a cada plato le asocia un valor entero.
*/
int miHash(string plato)
{
    unsigned int valorHash = 0;
    for (int i = 0; i < plato.length(); i++)
    {
        valorHash = (valorHash * 31) ^ plato[i] + 37;
    }
    return valorHash;
}

int main()
{

    unsigned int N;
    cin >> N;
    Restaurante miRestaurante(N, miHash);
    for (int i = 0; i < N; i++)
    {
        string plato;
        cin >> plato;
        miRestaurante.agregarOrden(plato);
    }
    MaxHeap PorOrden = miRestaurante.recuperarTodos();
    while (!PorOrden.esVacio())
    {
        NodoLista *nodo = PorOrden.peek();
        cout << nodo->valor << endl;
    }

    return 0;
}

