#include <iostream>
#include <string>
using namespace std;

struct NodoUrgencias
{
    int P;
    int T;
    int U;
    unsigned int OrdenDeInsercion;
};

class HeapUrgencias
{
private:
    unsigned int Posultimo;
    unsigned int cantElementos;
    unsigned int espaciosReservados;
    NodoUrgencias **vec; // implementacion a partir de la pos 1

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
        NodoUrgencias *nodoX = this->vec[posX];
        NodoUrgencias *nodoY = this->vec[posY];
        int tempP = nodoX->P;
        int tempT = nodoX->T;
        int tempU = nodoX->U;
        unsigned int tempOrdenINS = nodoX->OrdenDeInsercion;
        this->vec[posX]->P = this->vec[posY]->P;
        this->vec[posX]->T = this->vec[posY]->T;
        this->vec[posX]->U = this->vec[posY]->U;
        this->vec[posX]->OrdenDeInsercion = this->vec[posY]->OrdenDeInsercion;
        this->vec[posY]->P = tempP;
        this->vec[posY]->T = tempT;
        this->vec[posY]->U = tempU;
        this->vec[posY]->OrdenDeInsercion = tempOrdenINS;
    }

    /*
    PRE:
    POS: Compara el valor del nodo en la posición pos con su padre, si es pertinente, se intercambian, finaliza cuando el nodo cuya posición original es pos se encuentra en la posición adecuada.
    */
    void flotar(int pos)
    {
        if (pos <= 1)
            return;

        NodoUrgencias *nodoActual = vec[pos];
        NodoUrgencias *nodoPadre = vec[posPadre(pos)];
        int valorActual = nodoActual->U;
        int valorPadre = nodoPadre->U;
        if (valorActual > valorPadre || (valorActual == valorPadre && nodoActual->T < nodoPadre->T) || (valorActual == valorPadre && nodoActual->T == nodoPadre->T && nodoActual->OrdenDeInsercion < nodoPadre->OrdenDeInsercion))
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
        float valorHijoIzq;
        float valorHijoDer;
        if (posHijoIzq(pos) <= this->Posultimo)
            hijoIzq = true;
        if (posHijoDer(pos) <= this->Posultimo)
            hijoDer = true;
        if (hijoIzq)
            valorHijoIzq = this->vec[posHijoIzq(pos)]->U;
        if (hijoDer)
            valorHijoDer = this->vec[posHijoDer(pos)]->U;
        int posHijoMayorValor;
        if (!hijoIzq && !hijoDer)
            return;
        if (hijoIzq && !hijoDer)
            posHijoMayorValor = posHijoIzq(pos);
        else if (valorHijoIzq > valorHijoDer || (valorHijoIzq == valorHijoDer && this->vec[posHijoIzq(pos)]->T < this->vec[posHijoDer(pos)]->T) || (valorHijoIzq == valorHijoDer && this->vec[posHijoIzq(pos)]->T == this->vec[posHijoDer(pos)]->T && this->vec[posHijoIzq(pos)]->OrdenDeInsercion < this->vec[posHijoDer(pos)]->OrdenDeInsercion))
        {
            posHijoMayorValor = posHijoIzq(pos);
        }
        else
            posHijoMayorValor = posHijoDer(pos);

        if (vec[posHijoMayorValor]->U > vec[pos]->U ||
            (vec[posHijoMayorValor]->U == vec[pos]->U && vec[posHijoMayorValor]->T < vec[pos]->T) || (vec[posHijoMayorValor]->U == vec[pos]->U && vec[posHijoMayorValor]->T == vec[pos]->T && vec[posHijoMayorValor]->OrdenDeInsercion < vec[pos]->OrdenDeInsercion))
        {
            this->intercambiar(posHijoMayorValor, pos);
            hundir(posHijoMayorValor);
        }
    }

public:

    /*
    PRE:
    POS: inicializa un objeto HeapUrgencias
    */
    HeapUrgencias(unsigned int tamanio)
    {
        this->vec = new NodoUrgencias *[tamanio + 1];
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
    POS: devuelve true sii el heap esta lleno (ya no tiene mas espacio para almacenar elementos)
    */
    bool estaLleno()
    {
        return cantElementos == espaciosReservados;
    }

    /*
    PRE: !estaLleno()
    POS: inserta un nuevo nodo en el heap
    */
    void insertar(int U, int T, int P)
    {
        this->cantElementos++;
        NodoUrgencias *nuevo = new NodoUrgencias;
        nuevo->U = U;
        nuevo->T = T;
        nuevo->P = P;
        nuevo->OrdenDeInsercion = cantElem();
        this->vec[this->Posultimo + 1] = nuevo;
        this->Posultimo++;
        flotar(this->Posultimo);
    }

    /*
    PRE: !esVacio()
    POS: retorna y elimina el nodo raiz del heap
    */
    NodoUrgencias *peek()
    {
        if (this->cantElementos == 1)
        {
            NodoUrgencias *nodo = this->vec[1];
            this->Posultimo--;
            this->cantElementos--;
            return nodo;
        }
        intercambiar(1, this->Posultimo);
        NodoUrgencias *nodo = this->vec[Posultimo];
        this->Posultimo--;
        this->cantElementos--;
        hundir(1);
        return nodo;
    }


    /*
    PRE:
    POS: devuelve la cantidad actual de elementos en el heap
    */
    unsigned int cantElem()
    {
        return this->cantElementos;
    }

    /*
    PRE:
    POS: Libera la memoria del heap
    */
    ~HeapUrgencias()
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
