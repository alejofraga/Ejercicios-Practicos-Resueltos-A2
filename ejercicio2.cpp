#include <string>
#include <iostream>
#include "Ejercicio2/tablaHashNG.cpp"
#include "Ejercicio2/tablaPeli-Genero.cpp"
using namespace std;

int main()
{
    unsigned int G;
    cin >> G;
    TablaHash lasPelis = TablaHash(G, miHash);
    string *generos = new string[G];
    for (int i = 0; i < G; i++)
    {
        string nombre;
        cin >> nombre;
        lasPelis.agregarGenero(nombre);
        generos[i] = nombre;
    }
    unsigned int P;
    cin >> P;
    TablaPGSIMPLE PeliGenero = TablaPGSIMPLE(P);
    for (int i = 0; i < P; i++) 
    {
        unsigned int idPeli;
        string genero;
        cin >> idPeli >> genero;
        lasPelis.asociarPeliAGenero(idPeli, genero);
        PeliGenero.agregarPG(idPeli, genero);
    }

    unsigned int N;
    cin >> N;
    for (int i = 0; i < N; i++)
    {
        unsigned int puntuacion = 0;
        unsigned int idPeli = 0;
        cin >> idPeli >> puntuacion;
        string genero = PeliGenero.buscarGenero(idPeli);
        lasPelis.agregarPuntuacion(genero, idPeli, puntuacion);
    }

    for (int i = 0; i < G; i++)
    {
        string nombreGenero = generos[i];
        cout << lasPelis.recuperarIdCorrespondiente(nombreGenero) << endl;
    }
    delete [] generos;


    return 0;
}



