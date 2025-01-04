#include <iostream>
#include <string>
using namespace std;

class MFSET
{
private:
    int *vec;
    unsigned int *rank;
    unsigned int tamanio;

public:
    /*
    PRE:
    POS: inicializa un MFSET
    */
    MFSET(unsigned int cantVertices)
    {
        this->vec = new int[cantVertices + 1];
        this->rank = new unsigned int[cantVertices + 1];
        this->tamanio = cantVertices + 1;

        for (int i = 1; i <= cantVertices; i++)
        {
            this->vec[i] = -1;
            this->rank[i] = 0;
        }
    }

    /*
    PRE:
    POS: devuelve el "representante" de la componente conexa a la que pertenece "elemento", aplica "path compression"
    */
    unsigned int find(unsigned int elemento)
    {
        if (this->vec[elemento] == -1)
            return elemento;

        return this->vec[elemento] = find(this->vec[elemento]);
    }

    /*
    PRE:
    POS: une las componenetes conexas de elemento1 y elemento2 en una sola, aplica "union by rank"
    */
    bool merge(unsigned int elemento1, unsigned int elemento2)
    {
        unsigned int set1 = find(elemento1);
        unsigned int set2 = find(elemento2);
        if (set1 == set2)
            return true;
        if (set1 != set2 && this->rank[set1] == this->rank[set2])
        {
            this->vec[set1] = set2;
            this->rank[set1] = 0;
            this->rank[set2]++;
        }
        else if (set1 != set2 && this->rank[set1] > this->rank[set2])
        {
            this->vec[set2] = set1;
            this->rank[set2] = 0;
        }
        else if (set1 != set2)
        {
            this->vec[set1] = set2;
            this->rank[set1] = 0;
        }
        return false;
    }

    ~MFSET()
    {
        delete[] vec;
        delete[] rank;
        vec = NULL;
        rank = NULL;
    }
};
