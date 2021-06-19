
/**********************************************************************************
// Matrix (Arquivo de Cabeçalho)
//
// Criação:		19 Jun 2020
// Atualização:	19 Jun 2021
// Compilador:	Clang++ 12.0.5 / GNU g++ 9.3.0
//
// Descrição:	Define uma classe para uma matriz dinâmica com as operações
//              necessárias para criação do traçador de raios.
//
**********************************************************************************/

#ifndef RAY_TRACER_MATRIX
#define RAY_TRACER_MATRIX

#include "Types.h"
#include <initializer_list>
using std::initializer_list;

namespace RayTracer
{
    class Matrix
    {
    private:
        unsigned mRows;                                         // número de linhas
        unsigned mCols;                                         // número de colunas
        unsigned mSize;                                         // número de elementos
        float *mData;                                           // dados da matriz

    public:
        Matrix();                                               // construtor padrão
        Matrix(unsigned rows, unsigned cols);                   // construtor com linhas e colunas
        Matrix(unsigned rows, unsigned cols, 
               initializer_list<float> init);                   // construtor com lista de valores
        Matrix(Matrix& mat);                                    // construtor de cópia
        Matrix(Matrix&& mat);                                   // construtor de transferência (move)
        ~Matrix();                                              // destrutor

        // funções membro da classe 
        Matrix& operator=(Matrix& mat);                         // atribuição por cópia
        Matrix& operator=(Matrix&& mat);                        // atribuição por transferência (cópia)
        Matrix& operator=(initializer_list<float> init);        // atribuição de lista de valores
        float &operator()(unsigned i, unsigned j);              // retorna referência a elemento
        float operator()(unsigned i, unsigned j) const;         // retorna cópia do elemento

        // funções amiga não são membros da classe
        friend bool operator==(Matrix &m1, Matrix &m2);         // igualdade de matrizes
        friend bool operator!=(Matrix &m1, Matrix &m2);         // desigualdade de matrizes
        friend Matrix operator*(Matrix &m1, Matrix &m2);        // multiplicação de matrizes
        friend Tuple operator*(Matrix &m, Tuple t);             // multiplicação de matriz com tupla

        // membros estáticos da classe
        static Matrix Identity;                                 // matriz identidade
    };
}

#endif