
/**********************************************************************************
// Matrix (Arquivo de Cabeçalho)
//
// Criação:     19 Jun 2021
// Atualização:	17 Jul 2021
// Compilador:	Clang++ 12.0.5 / GNU g++ 9.3.0
//
// Descrição:	Define uma classe para uma matriz dinâmica com as operações
//              necessárias para criação do traçador de raios.
//
**********************************************************************************/

#ifndef RAY_TRACER_MATRIX
#define RAY_TRACER_MATRIX

#include "Types.h"
#include "Tuple.h"
#include <initializer_list>
using std::initializer_list;

namespace RayTracer
{
    class Matrix
    {
    private:
        uint mRows;                                                     // número de linhas
        uint mCols;                                                     // número de colunas
        uint mSize;                                                     // número de elementos
        double *mData;                                                  // dados da matriz

    public:
        Matrix();                                                       // construtor padrão
        Matrix(uint rows, uint cols);                                   // construtor com linhas e colunas
        Matrix(uint rows, uint cols, 
               const initializer_list<double> &init);                   // construtor com lista de valores

        Matrix(Matrix& mat);                                            // construtor de cópia
        Matrix(Matrix&& mat);                                           // construtor de transferência (move)
        ~Matrix();                                                      // destrutor

        // --------------------------------------------------------

        // membros estáticos da classe
        static Matrix Identity;                                         // matriz identidade

        // --------------------------------------------------------

        // funções membro da classe 
        Matrix& operator=(Matrix& mat);                                 // atribuição por cópia
        Matrix& operator=(Matrix&& mat);                                // atribuição por transferência
        Matrix& operator=(const initializer_list<double> &init);        // atribuição de lista de valores
        double &operator()(uint i, uint j);                             // retorna referência a elemento
        double operator()(uint i, uint j) const;                        // retorna cópia do elemento

        // --------------------------------------------------------

        // funções amiga não são membros da classe
        friend bool operator==(const Matrix &m1, const Matrix &m2);     // igualdade de matrizes
        friend bool operator!=(const Matrix &m1, const Matrix &m2);     // desigualdade de matrizes
        friend Matrix operator*(const Matrix &m1, const Matrix &m2);    // multiplicação de matrizes
        friend Tuple operator*(const Matrix &m, const Tuple &t);        // multiplicação de matriz com tupla

        // --------------------------------------------------------

        // operações sobre as matrizes
        Matrix Transpose() const;                                       // retorna a matriz transposta
        double Determinant() const;                                     // retorna o determinante
        Matrix Submatrix(uint row, uint col) const;                     // retorna matrix sem a linha e coluna indicadas
        double Minor(uint row, uint col) const;                         // retorna minor da matrix na posição indicada
        double Cofactor(uint row, uint col) const;                      // retorna cofator da matrix na posição indicada
        bool Invertible() const;                                        // testa se a matriz tem inversa
        Matrix Inverse() const;                                         // retorna a matrix inversa

        // --------------------------------------------------------
    };

    // transformações de matrizes
    Matrix Translation(double x, double y, double z);                   // retorna matriz de translação
    Matrix Scaling(double x, double y, double z);                       // retorna matriz de escala
    Matrix RotationX(double radians);                                   // retorna matriz de rotação para o eixo x
    Matrix RotationY(double radians);                                   // retorna matriz de rotação para o eixo y
    Matrix RotationZ(double radians);                                   // retorna matriz de rotação para o eixo z
    Matrix Shearing(double xy, double xz, 
                    double yx, double yz,
                    double zx, double zy);                              // retorna matriz de distorção
}

#endif