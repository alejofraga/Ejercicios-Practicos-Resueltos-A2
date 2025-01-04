#include <iostream>
#include <string>
using namespace std;

struct NodoPelis
{
    float promedio;
    unsigned int cantidadPuntajes;
    unsigned int id;
};

class HeapNP
{
private:
    unsigned int Posultimo;
    unsigned int cantElementos;
    unsigned int espaciosReservados;
    NodoPelis **vec; // implementacion a partir de la pos 1

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
    POS: calcula un nuevo promedio a partir del actual teniendo en cuenta una nueva puntuacion
    */
    float actualizarPromedio(unsigned int puntuacion, float promedioActual, unsigned int cantPuntuaciones)
    {
        return ((promedioActual * cantPuntuaciones) + puntuacion) / (cantPuntuaciones + 1);
    }

    /*
    PRE: 
    POS: Intercambia los valores de los nodos en las posiciones posX y posY
    */
    void intercambiar(unsigned int posX, unsigned int posY)
    {
        NodoPelis *nodoX = this->vec[posX];
        NodoPelis *nodoY = this->vec[posY];
        unsigned int tempCantidadPuntajes = nodoX->cantidadPuntajes;
        float tempValorPromedio = nodoX->promedio;
        unsigned int tempValorID = nodoX->id;
        this->vec[posX]->cantidadPuntajes = this->vec[posY]->cantidadPuntajes;
        this->vec[posX]->promedio = this->vec[posY]->promedio;
        this->vec[posX]->id = this->vec[posY]->id;
        this->vec[posY]->cantidadPuntajes = tempCantidadPuntajes;
        this->vec[posY]->promedio = tempValorPromedio;
        this->vec[posY]->id = tempValorID;
    }

    /*
    PRE:
    POS: Compara el valor del nodo en la posición pos con su padre, si es pertinente, se intercambian, finaliza cuando el nodo cuya posición original es pos se encuentra en la posición adecuada.
    */
    void flotar(int pos)
    {
        if (pos <= 1)
            return;

        NodoPelis *nodoActual = vec[pos];
        NodoPelis *nodoPadre = vec[posPadre(pos)];
        float valorActual = nodoActual->promedio;
        float valorPadre = nodoPadre->promedio;
        if (valorActual > valorPadre || (valorActual == valorPadre && nodoActual->id < nodoPadre->id))
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
            valorHijoIzq = this->vec[posHijoIzq(pos)]->promedio;
        if (hijoDer)
            valorHijoDer = this->vec[posHijoDer(pos)]->promedio;
        int posHijoMayorValor;
        if (!hijoIzq && !hijoDer)
            return;
        if (hijoIzq && !hijoDer)
            posHijoMayorValor = posHijoIzq(pos);
        else if (valorHijoIzq > valorHijoDer || (valorHijoIzq == valorHijoDer && this->vec[posHijoIzq(pos)]->id < this->vec[posHijoDer(pos)]->id))
        {
            posHijoMayorValor = posHijoIzq(pos);
        }
        else
            posHijoMayorValor = posHijoDer(pos);

        if (vec[posHijoMayorValor]->promedio > vec[pos]->promedio ||
            (vec[posHijoMayorValor]->promedio == vec[pos]->promedio && vec[posHijoMayorValor]->id < vec[pos]->id))
        {
            this->intercambiar(posHijoMayorValor, pos);
            hundir(posHijoMayorValor);
        }
    }

public:
    /*
    PRE:
    POS: inicializa un objeto HeapNp
    */
    HeapNP(unsigned int tamanio)
    {
        this->vec = new NodoPelis *[tamanio + 1];
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
    PRE:
    POS: incrementa la capacidad del heap de forma que se puedan almacenar nuevos elementos
    */
    void Redimensionar()
    {
        unsigned int nuevaCota = espaciosReservados * 2;
        NodoPelis **nuevoVec = new NodoPelis *[nuevaCota];

        for (int i = 0; i < espaciosReservados; i++)
        {
            nuevoVec[i] = vec[i];
            vec[i] = NULL;
        }

        delete[] vec;

        for (int i = espaciosReservados; i < nuevaCota; i++)
        {
            nuevoVec[i] = NULL;
        }

        vec = nuevoVec;
        espaciosReservados = nuevaCota;
    }

    /*
    PRE: !estaLleno()
    POS: inserta un nuevo nodo en el heap
    */
    void insertar(float promedio, unsigned int cantidadPuntajes, unsigned int idPeli)
    {
        this->cantElementos++;
        if (estaLleno())
            Redimensionar();
        NodoPelis *nuevo = new NodoPelis;
        nuevo->promedio = promedio;
        nuevo->cantidadPuntajes = cantidadPuntajes;
        nuevo->id = idPeli;
        this->vec[this->Posultimo + 1] = nuevo;
        this->Posultimo++;
        flotar(this->Posultimo);
    }

    /*
    PRE: !esVacio()
    POS: retorna (no elimina) el nodo raiz del heap
    */
    NodoPelis *peek()
    {
        NodoPelis *nodo = this->vec[1];
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
   PRE: existe idPeli
   POS: actualiza el promedio del nodo cuyo id es idpeli a partir de un nuevo puntaje en el heap, reubicandolo en su lugar correspondiente
   */
    void actualizarValor(unsigned int idPeli, unsigned int puntaje) 
    {
        int pos;
        bool encontre = false;
        for (int i = 1; i <= Posultimo && !encontre; i++)
        {
            if (vec[i]->id == idPeli)
            {
                pos = i;
                encontre = true;
            }
        }
        vec[pos]->promedio = actualizarPromedio(puntaje, vec[pos]->promedio, vec[pos]->cantidadPuntajes);
        vec[pos]->cantidadPuntajes++;
        hundir(pos);
        flotar(pos);
    }

    /*
    PRE:
    POS: Libera la memoria del heap
    */
    void destruir()
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
