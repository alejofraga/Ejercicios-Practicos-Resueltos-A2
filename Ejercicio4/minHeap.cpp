#include <iostream>
#include <string>
using namespace std;

struct NodoPlato
{
    string plato;
    unsigned int pos;
};

class MinHeapPlatos
{
private:
    unsigned int Posultimo;
    unsigned int cantElementos;
    unsigned int espaciosReservados;
    NodoPlato **vec; // implementacion a partir de la pos 1



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
        NodoPlato *nodoX = this->vec[posX];
        NodoPlato *nodoY = this->vec[posY];
        string tempPlato = nodoX->plato;
        unsigned int tempPos = nodoX->pos;
        this->vec[posX]->plato = this->vec[posY]->plato;
        this->vec[posX]->pos = this->vec[posY]->pos;
        this->vec[posY]->plato = tempPlato;
        this->vec[posY]->pos = tempPos;
    }


    /*
    PRE:
    POS: Compara el valor del nodo en la posición pos con su padre, si es pertinente, se intercambian, finaliza cuando el nodo cuya posición original es pos se encuentra en la posición adecuada.
    */
    void flotar(int pos)
    {
        if (pos <= 1)
            return;

        NodoPlato *nodoActual = vec[pos];
        NodoPlato *nodoPadre = vec[posPadre(pos)];
        string valorActual = nodoActual->plato;
        string valorPadre = nodoPadre->plato;
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
        string valorHijoIzq;
        string valorHijoDer;
        if (posHijoIzq(pos) <= this->Posultimo)
            hijoIzq = true;
        if (posHijoDer(pos) <= this->Posultimo)
            hijoDer = true;
        if (hijoIzq)
            valorHijoIzq = this->vec[posHijoIzq(pos)]->plato;
        if (hijoDer)
            valorHijoDer = this->vec[posHijoDer(pos)]->plato;
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

        if (vec[posHijoMayorValor]->plato < vec[pos]->plato)
        {
            this->intercambiar(posHijoMayorValor, pos);
            hundir(posHijoMayorValor);
        }
    }

public:


    /*
    PRE:
    POS: inicializa un objeto MinHeapPlatos
    */
    MinHeapPlatos(unsigned int tamanio)
    {
        this->vec = new NodoPlato *[tamanio + 1];
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
    void insertar(string Nombreplato, unsigned int pos)
    {
        NodoPlato *nuevo = new NodoPlato;
        nuevo->plato = Nombreplato;
        nuevo->pos = pos;
        this->vec[this->Posultimo + 1] = nuevo;
        this->Posultimo++;
        this->cantElementos++;
        flotar(this->Posultimo);
    }


    /*
    PRE: !esVacio()
    POS: retorna y elimina el nodo raiz del heap
    */
    NodoPlato *peek()
    {
        if (this->cantElementos == 1)
        {
            NodoPlato *nodo = this->vec[1];
            this->Posultimo--;
            this->cantElementos--;
            return nodo;
        }
        intercambiar(1, this->Posultimo);
        NodoPlato *nodo = this->vec[Posultimo];
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
    ~MinHeapPlatos()
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
