#include <iostream>
#include <string>
using namespace std;

class Picos
{
private:
    bool *picos;

public:
    /*
    PRE:
    POS: inicializa un objeto picos
    */
    Picos(unsigned int tamanio)
    {
        this->picos = new bool[tamanio]();
    }
    /*
    PRE:
    POS: marca la montaña en la posicion "pos" como pico
    */
    void marcarPico(unsigned int pos)
    {
        this->picos[pos] = true;
    }
    /*
    PRE:
    POS: devuelve true sii la montaña en la posicion "pos" es pico
    */
    bool esPico(unsigned int pos)
    {
        return this->picos[pos];
    }
    /*
    PRE:
    POS: libera memoria
    */
    ~Picos()
    {
        delete[] this->picos;
    }
};

/*
PRE:
POS: aplica la tecnica D&C, marcando las montañas que son picos en la clase "picos"
*/
void encontrarPicos(unsigned int *alturas, bool *noSonPicos, Picos &picos, unsigned int inicio, unsigned int final)
{

    if (final - inicio + 1 == 2)
    {
        if (alturas[inicio] == alturas[final])
        {
            return;
        }
        int posPosiblePico;
        if (alturas[inicio] > alturas[final])
        {
            posPosiblePico = inicio;
        }
        else
        {
            posPosiblePico = final;
        }
        if (!noSonPicos[posPosiblePico])
        {
            picos.marcarPico(posPosiblePico);
        }
        return;
    }
    if (final == inicio)
    {
        if (!noSonPicos[inicio])
        {
            picos.marcarPico(inicio);
        }
        return;
    }
    unsigned int medio = (final + inicio) / 2;
    if (alturas[medio] > alturas[medio - 1] && alturas[medio] > alturas[medio + 1])
    {
        picos.marcarPico(medio);
        noSonPicos[medio - 1] = true;
        noSonPicos[medio + 1] = true;
    }
    else if ((alturas[medio] > alturas[medio - 1] && alturas[medio] == alturas[medio + 1]) || (alturas[medio] > alturas[medio + 1] && alturas[medio] == alturas[medio - 1]) || (alturas[medio] == alturas[medio - 1] && alturas[medio] == alturas[medio + 1]))
    {
        noSonPicos[medio - 1] = true;
        noSonPicos[medio + 1] = true;
    }
    else if (alturas[medio] >= alturas[medio - 1] && alturas[medio] < alturas[medio + 1])
    {
        noSonPicos[medio - 1] = true;
    }
    else if (alturas[medio] >= alturas[medio + 1] && alturas[medio] < alturas[medio - 1])
    {
        noSonPicos[medio + 1] = true;
    }
    encontrarPicos(alturas, noSonPicos, picos, inicio, medio - 1);
    encontrarPicos(alturas, noSonPicos, picos, medio + 1, final);
}
int main()
{

    unsigned int N;
    cin >> N;
    unsigned int *alturas = new unsigned int[N];
    bool *noSonPicos = new bool[N];
    for (int i = 0; i < N; i++)
    {
        unsigned int altura;
        cin >> altura;
        alturas[i] = altura;
        noSonPicos[i] = false;
    }

    Picos picos = Picos(N);
    encontrarPicos(alturas, noSonPicos, picos, 0, N - 1);
    bool noHayPicos = true;
    for (int i = 0; i < N; i++)
    {
        if (picos.esPico(i))
        {
            cout << alturas[i] << endl;
            noHayPicos = false;
        }
    }
    if (noHayPicos)
        cout << "No se encontraron picos" << endl;
    delete[] noSonPicos;
    delete[] alturas;
    return 0;
}