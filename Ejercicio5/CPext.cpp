#include <iostream>
#include <string>
#include "tablaVP.cpp"
using namespace std;

struct NodoHeap
{
    unsigned int vertice;
    unsigned int costo;
};

class CPext
{
private:
    unsigned int Posultimo;
    unsigned int cantElementos;
    unsigned int espaciosReservados;
    tablaVP *verticePos;
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
        this->verticePos->actualizarVP(vec[posX]->vertice, posY);
        this->verticePos->actualizarVP(vec[posY]->vertice, posX);
        NodoHeap *nodoX = this->vec[posX];
        NodoHeap *nodoY = this->vec[posY];
        unsigned tempVertice = nodoX->vertice;
        unsigned tempcosto = nodoX->costo;
        this->vec[posX]->vertice = this->vec[posY]->vertice;
        this->vec[posX]->costo = this->vec[posY]->costo;
        this->vec[posY]->vertice = tempVertice;
        this->vec[posY]->costo = tempcosto;
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
        unsigned int valorActual = nodoActual->costo;
        unsigned int valorPadre = nodoPadre->costo;
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
            valorHijoIzq = this->vec[posHijoIzq(pos)]->costo;
        if (hijoDer)
            valorHijoDer = this->vec[posHijoDer(pos)]->costo;
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

        if (vec[posHijoMayorValor]->costo < vec[pos]->costo)
        {
            this->intercambiar(posHijoMayorValor, pos);
            hundir(posHijoMayorValor);
        }
    }

public:
    /*
    PRE:
    POS: inicializa una cola de prioridad extendida por menor costo
    */
    CPext(unsigned int tamanio)
    {
        this->verticePos = new tablaVP(tamanio);
        this->vec = new NodoHeap *[tamanio + 1];
        this->Posultimo = 0;
        this->cantElementos = 0;
        this->espaciosReservados = tamanio + 1;
    }
    /*
    PRE:
    POS: devuelve true sii la cola de prioridad extendida no tiene elementos
    */
    bool esVacio()
    {
        return cantElementos == 0;
    }

    /*
    PRE:
    POS: inserta el vertice con su costo asociado a la cola de prioridad extendida
    */
    void insertar(unsigned int vertice, unsigned int costo)
    {
        NodoHeap *nuevo = new NodoHeap;
        nuevo->vertice = vertice;
        nuevo->costo = costo;
        this->vec[this->Posultimo + 1] = nuevo;
        this->Posultimo++;
        this->cantElementos++;
        flotar(this->Posultimo);
        this->verticePos->insertarVP(vertice, Posultimo);
    }
    /*
    PRE:
    POS: elimina y retorna la raiz de la cola de prioridad extendida
    */
    NodoHeap *peek()
    {
        if (this->cantElementos == 1)
        {
            NodoHeap *nodo = this->vec[1];
            verticePos->eliminarVP(nodo->vertice);
            this->Posultimo--;
            this->cantElementos--;
            return nodo;
        }
        intercambiar(1, this->Posultimo);
        NodoHeap *nodo = this->vec[Posultimo];
        this->Posultimo--;
        this->cantElementos--;
        hundir(1);
        verticePos->eliminarVP(nodo->vertice);
        return nodo;
    }

    /*
    PRE: "vertice" existe en la cola de prioridad extendida
    POS: actualiza el costo de "vertice", reubicandolo apropiadamente
    */
    void actualizarValor(unsigned int vertice, unsigned int costo)
    {
        unsigned int pos = this->verticePos->recuperarPos(vertice);
        this->vec[pos]->costo = costo;
        hundir(pos);
        flotar(pos);
    }
};
