#include <iostream>
#include <string>
using namespace std;
struct posicion
{
    int posFila;
    int posCol;
};
/*
PRE:
POS: devuelve en un struct la siguiente posicion vacia en la matriz (con 0)
*/
posicion *sigPosVacia(int **mat, int cantFilas, int cantColumnas)
{
    for (int filaActual = 0; filaActual < cantFilas; filaActual++)
    {
        for (int colActual = 0; colActual < cantColumnas; colActual++)
        {
            if (mat[filaActual][colActual] == 0)
            {
                posicion *pos = new posicion;
                pos->posFila = filaActual;
                pos->posCol = colActual;
                return pos;
            }
        }
    }
    return NULL;
}
/*
PRE:
POS: devuelve el maximo entre a y b
*/
int myMax(int a, int b)
{
    if (a > b)
        return a;
    else
        return b;
}
/*
PRE:
POS: devuelve true sii "numero" esta repetido en la fila "posFila"
*/
bool hayRepetidoEnfila(int **mat, int posFila, int posColumna, int numero, int cantCol)
{
    for (int colActual = 0; colActual < cantCol; colActual++)
    {
        if (mat[posFila][colActual] == numero && colActual != posColumna)
            return true;
    }
    return false;
}
/*
PRE:
POS: devuelve true sii "numero" esta repetido en la columna "posColumna"
*/
bool hayRepetidoEnColumna(int **mat, int posFila, int posColumna, int numero, int cantFilas)
{
    for (int filaActual = 0; filaActual < cantFilas; filaActual++)
    {
        if (mat[filaActual][posColumna] == numero && filaActual != posFila)
            return true;
    }
    return false;
}
/*
PRE:
POS: devuelve true sii "numero" esta repetido en el cuadrante asociado a la fila "posFila" y la columna "posColumna"
*/
bool hayRepetidoEnCuadrante(int **mat, int posFila, int posColumna, int numero, int cantFilas, int cantColumnas)
{
    int cuadranteFila = posFila / (cantFilas / 3);
    int cuadranteColumna = posColumna / (cantColumnas / 3);

    int filaInicial = cuadranteFila * (cantFilas / 3);
    int filaFinal = filaInicial + 3;
    int columnaInicial = cuadranteColumna * (cantColumnas / 3);
    int columnaFinal = columnaInicial + 3;

    for (int filaActual = filaInicial; filaActual < filaFinal; filaActual++)
    {
        for (int columnaActual = columnaInicial; columnaActual < columnaFinal; columnaActual++)
        {
            if (mat[filaActual][columnaActual] == numero)
                return true;
        }
    }
    return false;
}
/*
PRE:
POS: devuelve true sii "numero" en la posicion [posFila][posColumna] no rompe las reglas del sudoku
*/
bool esMovimientoValido(int **mat, int posFila, int posColumna, int numero, int cantFilas, int cantColumnas)
{
    if (!hayRepetidoEnfila(mat, posFila, posColumna, numero, cantColumnas) && !hayRepetidoEnColumna(mat, posFila, posColumna, numero, cantFilas) && !hayRepetidoEnCuadrante(mat, posFila, posColumna, numero, cantFilas, cantColumnas))
    {
        return true;
    }
    else
        return false;
}
/*
PRE:
POS: guarda "numeroActual" en la posicion [posFila][posColumna] de la matriz
*/
void ejecutarMovimiento(int **mat, int posFila, int posColumna, int numeroActual)
{
    mat[posFila][posColumna] = numeroActual;
}
/*
PRE:
POS: guarda un 0 en la posicion [posFila][posColumna] de la matriz
*/
void deshacerMovimiento(int **mat, int posFila, int posCol)
{
    mat[posFila][posCol] = 0;
}
/*
PRE:
POS: imprime por consola los elementos de la matriz
*/
void imprimir(int **mat, int cantFilas, int cantColumnas)
{
    for (int i = 0; i < cantFilas; i++)
    {
        for (int j = 0; j < cantColumnas; j++)
        {
            cout << mat[i][j] << " ";
        }
        cout << endl;
    }
}
/*
PRE: recibe una matriz la cual se interpreta como la matriz del sudoku a resolverse
POS: una vez que encuentra una solucion al sudoku, la imprime por consola. Este metodo utiliza la tecnica "Backtracking"
*/
void sudoku(int **mat, int cantFilas, int cantColumnas, bool &solucionEncontrada)
{
    posicion *pos = sigPosVacia(mat, cantFilas, cantColumnas);

    if (pos == NULL)
    {
        imprimir(mat, cantFilas, cantColumnas);
        solucionEncontrada = true;
    }
    else if (!solucionEncontrada)
    {
        for (int numeroActual = 1; numeroActual <= myMax(cantFilas, cantColumnas); numeroActual++)
        {
            if (esMovimientoValido(mat, pos->posFila, pos->posCol, numeroActual, cantFilas, cantColumnas))
            {
                ejecutarMovimiento(mat, pos->posFila, pos->posCol, numeroActual);
                sudoku(mat, cantFilas, cantColumnas, solucionEncontrada);
                deshacerMovimiento(mat, pos->posFila, pos->posCol);
            }
        }
    }
    delete pos;
    pos = NULL;
}

int main()
{

    int fil;
    int col;
    cin >> fil >> col;
    int **sudokuMat = new int *[fil];
    for (int filaActual = 0; filaActual < fil; filaActual++)
    {
        sudokuMat[filaActual] = new int[col];
        for (int colActual = 0; colActual < col; colActual++)
        {
            cin >> sudokuMat[filaActual][colActual];
        }
    }
    bool solucionEncontrada = false;
    sudoku(sudokuMat, fil, col, solucionEncontrada);
    // libero memoria
    for (int i = 0; i < fil; i++)
    {
        delete[] sudokuMat[i];
    }
    delete[] sudokuMat;
}