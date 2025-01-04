#include <iostream>
#include <string>
using namespace std;

struct NodoLista
{
    string valor;
    unsigned int ordenes;
};

class MaxHeap
{
private:
    unsigned int Posultimo;
    unsigned int cantElementos;
    unsigned int espaciosReservados;
    NodoLista **vec; // implementacion a partir de la pos 1

    /*
    PRE:
    POS: devuelve la posición del "padre" del nodo en la posición pos
    */
    unsigned int posPadre(unsigned int pos)
    {
        return (pos / 2);
    }
    /*
   PRE:
   POS: devuelve la posición del "hijo izquierdo" del nodo en la posición pos
   */
    unsigned int posHijoIzq(unsigned int pos)
    {
        return (pos * 2);
    }
    /*
   PRE:
   POS: devuelve la posición del "hijo derecho" del nodo en la posición pos
   */
    unsigned int posHijoDer(unsigned int pos)
    {
        return ((pos * 2) + 1);
    }

    /*
    PRE:
    POS: Intercambia los valores de los nodos en las posiciones posX y posY
    */
    void intercambiar(unsigned int posX, unsigned int posY)
    {
        NodoLista *nodoX = this->vec[posX];
        NodoLista *nodoY = this->vec[posY];
        string tempValorX = nodoX->valor;
        unsigned int tempValorOrdenes = nodoX->ordenes;
        this->vec[posX]->valor = this->vec[posY]->valor;
        this->vec[posX]->ordenes = this->vec[posY]->ordenes;
        this->vec[posY]->valor = tempValorX;
        this->vec[posY]->ordenes = tempValorOrdenes;
    }

    /*
    PRE:
    POS: Compara el valor del nodo en la posición pos con su padre, si es pertinente, se intercambian, finaliza cuando el nodo cuya posición original es pos se encuentra en la posición adecuada.
    */
    void flotar(int pos)
    {
        if (pos == 1)
            return;
        NodoLista *nodoActual = vec[pos];
        NodoLista *nodoPadre = vec[posPadre(pos)];
        int valorActual = nodoActual->ordenes;
        int valorPadre = nodoPadre->ordenes;
        if (valorActual > valorPadre || (valorActual == valorPadre && nodoActual->valor < nodoPadre->valor))
        {
            intercambiar(pos, posPadre(pos));
            flotar(posPadre(pos));
        }
    }


    /*
    PRE:
    POS: Compara el valor del nodo en la posición pos con su su hijo de mayor valor, si es pertinente, se intercambian, finaliza cuando el nodo cuya posición original es pos se encuentra en la posición adecuada.
    */
    void hundir(unsigned int pos)
    {
        bool hijoIzq = false;
        bool hijoDer = false;
        int valorHijoIzq;
        int valorHijoDer;
        if (posHijoIzq(pos) <= this->Posultimo)
            hijoIzq = true;
        if (posHijoDer(pos) <= this->Posultimo)
            hijoDer = true;
        if (hijoIzq)
            valorHijoIzq = this->vec[posHijoIzq(pos)]->ordenes;
        if (hijoDer)
            valorHijoDer = this->vec[posHijoDer(pos)]->ordenes;
        int posHijoMayorValor;
        if (!hijoIzq && !hijoDer)
            return;
        if (hijoIzq && !hijoDer)
            posHijoMayorValor = posHijoIzq(pos);
        else if (valorHijoIzq > valorHijoDer || (valorHijoIzq == valorHijoDer && this->vec[posHijoIzq(pos)]->valor < this->vec[posHijoDer(pos)]->valor))
        {
            posHijoMayorValor = posHijoIzq(pos);
        }
        else
            posHijoMayorValor = posHijoDer(pos);

        if (vec[posHijoMayorValor]->ordenes > vec[pos]->ordenes || (vec[posHijoMayorValor]->ordenes == vec[pos]->ordenes && vec[posHijoMayorValor]->valor < vec[pos]->valor))
        {
            this->intercambiar(posHijoMayorValor, pos);
            hundir(posHijoMayorValor);
        }
    }

public:
    /*
    PRE:
    POS:Inicializa y devuelve un objeto MaxHeap
    */
    MaxHeap(unsigned int tamanio)
    {
        this->vec = new NodoLista *[tamanio];
        this->Posultimo = 0;
        this->cantElementos = 0;
        this->espaciosReservados = tamanio;
    }
    /*
    PRE:
    POS:Devuelve true si la cantidad de elementos en el heap es 0
    */
    bool esVacio()
    {
        return cantElementos == 0;
    }

    /*
    PRE:
    POS:inserta nuevoElemento con sus ordenes como nodo en el heap, dejandolo en su posición adecuada
    */
    void insertar(string nuevoElemento, unsigned int ordenes)
    {
        NodoLista *nuevo = new NodoLista;
        nuevo->valor = nuevoElemento;
        nuevo->ordenes = ordenes;
        this->vec[this->Posultimo + 1] = nuevo;
        this->Posultimo++;
        this->cantElementos++;
        flotar(this->Posultimo);
    }

    /*
    PRE:
    POS: elimina del heap el nodo raiz y lo retorna manteniendo las propiedades estructural y de orden del mismo
    */
    NodoLista *peek()
    {
        if (this->cantElementos == 1)
        {
            NodoLista *nodo = this->vec[1];
            this->Posultimo--;
            this->cantElementos--;
            return nodo;
        }

        intercambiar(1, this->Posultimo);
        NodoLista *nodo = this->vec[Posultimo];
        this->Posultimo--;
        this->cantElementos--;
        hundir(1);
        return nodo;
    }
    /*
    PRE:
    POS: Devuelve la cantidad de elementos en el heap
    */
    unsigned int cantElem()
    {
        return this->cantElementos;
    }
    /*
    PRE:
    POS:Libera la memoria del heap
    */
    ~MaxHeap()
    {
        for (unsigned int i = 1; i <= Posultimo; i++)
        {
            delete vec[i];
            vec[i] = NULL;
        }
        delete[] vec;
        vec = NULL;
    }
};

