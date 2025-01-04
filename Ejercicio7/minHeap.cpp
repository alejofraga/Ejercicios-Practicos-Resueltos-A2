#include <iostream>
#include <string>
using namespace std;

struct NodoHeap
{
    unsigned int digito;
};

class MinHeap
{
private:
    unsigned int Posultimo;
    unsigned int cantElementos;
    unsigned int espaciosReservados;
    NodoHeap **vec; // implementacion a partir de la pos 1


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
        NodoHeap *nodoX = this->vec[posX];
        NodoHeap *nodoY = this->vec[posY];
        unsigned int tempDigito = nodoX->digito;
        this->vec[posX]->digito = this->vec[posY]->digito;
        this->vec[posY]->digito = tempDigito;
    }

    /*
    PRE:
    POS: Compara el valor del nodo en la posición pos con su padre, si es pertinente, se intercambian, finaliza cuando el nodo cuya posición original es pos se encuentra en la posición adecuada.
    */
    void flotar(int pos)
    {
        if (pos <= 1)
            return;

        NodoHeap *nodoActual = vec[pos];
        NodoHeap *nodoPadre = vec[posPadre(pos)];
        unsigned int valorActual = nodoActual->digito;
        unsigned int valorPadre = nodoPadre->digito;
        if (valorActual < valorPadre)
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
        unsigned int valorHijoIzq;
        unsigned int valorHijoDer;
        if (posHijoIzq(pos) <= this->Posultimo)
            hijoIzq = true;
        if (posHijoDer(pos) <= this->Posultimo)
            hijoDer = true;
        if (hijoIzq)
            valorHijoIzq = this->vec[posHijoIzq(pos)]->digito;
        if (hijoDer)
            valorHijoDer = this->vec[posHijoDer(pos)]->digito;
        int posHijoMayorValor;
        if (!hijoIzq && !hijoDer)
            return;
        if (hijoIzq && !hijoDer)
            posHijoMayorValor = posHijoIzq(pos);
        else if (valorHijoIzq < valorHijoDer)
        {
            posHijoMayorValor = posHijoIzq(pos);
        }
        else
            posHijoMayorValor = posHijoDer(pos);

        if (vec[posHijoMayorValor]->digito < vec[pos]->digito)
        {
            this->intercambiar(posHijoMayorValor, pos);
            hundir(posHijoMayorValor);
        }
    }

public:

    /*
    PRE:
    POS: inicializa un objeto  MinHeap por digito
    */
    MinHeap(unsigned int tamanio)
    {
        this->vec = new NodoHeap *[tamanio + 1];
        this->Posultimo = 0;
        this->cantElementos = 0;
        this->espaciosReservados = tamanio + 1;
    }

    /*
    PRE:
    POS: devuelve true sii el heap no tiene elementos
    */
    bool esVacio()
    {
        return cantElementos == 0;
    }

    /*
    PRE:
    POS: devuelve true si el heap esta lleno (ya no tiene mas espacio para almacenar elementos)
    */
    bool estaLleno()
    {
        return cantElementos == espaciosReservados;
    }


    /*
    PRE: !estaLleno()
    POS: inserta un nuevo nodo en el heap
    */
    void insertar(unsigned int digito)
    {
        NodoHeap *nuevo = new NodoHeap;
        nuevo->digito = digito;
        this->vec[this->Posultimo + 1] = nuevo;
        this->Posultimo++;
        this->cantElementos++;
        flotar(this->Posultimo);
    }

    /*
    PRE: !esVacio()
    POS: retorna (no elimina) el nodo raiz del heap
    */
    NodoHeap *peek()
    {
        if (this->cantElementos == 1)
        {
            NodoHeap *nodo = this->vec[1];
            this->Posultimo--;
            this->cantElementos--;
            return nodo;
        }
        intercambiar(1, this->Posultimo);
        NodoHeap *nodo = this->vec[Posultimo];
        this->Posultimo--;
        this->cantElementos--;
        hundir(1);
        return nodo;
    }


    /*
    PRE:
    POS: libera la memoria del heap
    */
    ~MinHeap()
    {
        for (int i = 0; i < this->espaciosReservados; i++)
        {
            delete this->vec[i];
        }
        delete[] vec;
        vec = NULL;
    }
};
