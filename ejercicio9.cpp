#include <iostream>
#include <string>
using namespace std;

struct juego
{
    string nombre;
    int tamanio;
    int popularidadActual;
};
/*
PRE:
POS: devuelve el mayor de a y b
*/
int max(int a, int b)
{
    if (a > b)
        return a;
    else
        return b;
}
/*
PRE:
POS: devuelve la mayor popularidadActual que se puede alcanzar con una PolyStation de capacidad "capacidadDisco" y juegos "juegos", se aplica tecnica de tabulacion con Programacion Dinamica
*/
int maximaPopularidadActual(juego **juegos, int largo, int capacidadDisco)
{
    int **mat = new int *[largo];
    for (int juegoActual = 0; juegoActual < largo; juegoActual++)
    {
        mat[juegoActual] = new int[capacidadDisco + 1];
        for (int capacidadDiscoActual = 0; capacidadDiscoActual < capacidadDisco; capacidadDiscoActual++)
        {
            mat[juegoActual][capacidadDiscoActual] = 0;
        }
    }

    for (int juegoActual = 1; juegoActual < largo; juegoActual++)
    {
        for (int capacidadDiscoActual = 1; capacidadDiscoActual < capacidadDisco; capacidadDiscoActual++)
        {
            if (juegos[juegoActual]->tamanio > capacidadDiscoActual)
            {
                mat[juegoActual][capacidadDiscoActual] = mat[juegoActual - 1][capacidadDiscoActual];
            }
            else
            {
                int popularidadJuegoActual = juegos[juegoActual]->popularidadActual;
                int tamanioJuegoActual = juegos[juegoActual]->tamanio;
                int maxPopularidadSinConsiderarJuegoActual = mat[juegoActual - 1][capacidadDiscoActual];
                int maxPopularidadConsiderandoJuegoActual = popularidadJuegoActual + mat[juegoActual - 1][capacidadDiscoActual - tamanioJuegoActual];
                mat[juegoActual][capacidadDiscoActual] = max(maxPopularidadSinConsiderarJuegoActual, maxPopularidadConsiderandoJuegoActual);
            }
        }
    }
    int maximaPopularidad = mat[largo - 1][capacidadDisco - 1];
    // libero memoria de la matriz
    for (int juegoActual = 0; juegoActual < largo; juegoActual++)
    {
        delete[] mat[juegoActual];
    }
    delete[] mat;
    return maximaPopularidad;
}

int main()
{

    int capacidadDisco;
    cin >> capacidadDisco;
    int anioActual;
    cin >> anioActual;
    int cantJuegos;
    cin >> cantJuegos;
    juego **juegos = new juego *[cantJuegos + 1];
    for (int i = 1; i <= cantJuegos; i++)
    {
        string nombre;
        int tamanio;
        int popularidadAntes;
        int anioLanzamiento;
        cin >> nombre >> tamanio >> popularidadAntes >> anioLanzamiento;
        juego *nuevoJuego = new juego;
        nuevoJuego->nombre = nombre;
        nuevoJuego->tamanio = tamanio;
        nuevoJuego->popularidadActual = popularidadAntes - 5 * (anioActual - anioLanzamiento);
        juegos[i] = nuevoJuego;
    }
    cout << maximaPopularidadActual(juegos, cantJuegos + 1, capacidadDisco + 1) << endl;
    for (int i = 1; i <= cantJuegos; i++)
    {
        delete juegos[i];
        juegos[i] = NULL;
    }
    delete[] juegos;
    juegos = NULL;

    return 0;
}