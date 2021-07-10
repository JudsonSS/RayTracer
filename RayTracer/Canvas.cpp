/**********************************************************************************
// Canvas (Arquivo de Código Fonte)
//
// Criação:		17 Jun 2021
// Atualização:	09 Jul 2021
// Compilador:	Clang++ 12.0.5 / GNU g++ 9.3.0
//
// Descrição:	Define uma representação para um grade retangular de pixels.
//              Cada pixel possui uma cor RGB.
//
**********************************************************************************/

#include "Canvas.h"
#include <fstream>
#include <iostream>
using std::ofstream;
using std::cerr;

namespace RayTracer
{
    // -------------------------------------------------------------------------------

    Canvas::Canvas(unsigned width, unsigned height)
        : mWidth(width), mHeight(height), mSize(width * height)
    {
        // aloca vetor dinâmico
        mGrid = new Color[mSize];
    }

    Canvas::Canvas(Canvas &c)
        : mGrid(new Color[c.mSize]),
          mWidth(c.mWidth),
          mHeight(c.mHeight),
          mSize(c.mSize)
    {
        for (int i = 0; i < mSize; ++i)
            mGrid[i] = c.mGrid[i];
    }

    Canvas::Canvas(Canvas &&c)
        : mGrid(c.mGrid),
          mWidth(c.mWidth),
          mHeight(c.mHeight),
          mSize(c.mSize)
    {
        c.mGrid = nullptr;
    }

    Canvas::~Canvas()
    {
        // libera vetor dinâmico
        delete[] mGrid;
    }

    // -------------------------------------------------------------------------------

    Canvas & Canvas::operator=(Canvas &c)
    {
        mWidth = c.mWidth;
        mHeight = c.mHeight;
        mSize = c.mSize;

        delete [] mGrid;
        mGrid = new Color[mSize];
        for (int i = 0; i < mSize; ++i)
            mGrid[i] = c.mGrid[i];

        return *this;
    }

    Canvas & Canvas::operator=(Canvas &&c)
    {
        mWidth = c.mWidth;
        mHeight = c.mHeight;
        mSize = c.mSize;
        delete [] mGrid;
        mGrid = c.mGrid;
        c.mGrid = nullptr;
        return *this;
    }

    // -------------------------------------------------------------------------------

    // Retorna largura da grade
    int Canvas::Width() const
    { return mWidth; }

    // Retorna altura da grade
    int Canvas::Height() const
    { return mHeight; }

    // Retorna cor da posição (x,y)
    Color Canvas::At(int x, int y)
    { return mGrid[y * mWidth + x]; }

    // pinta pixel com uma cor
    void Canvas::Paint(int x, int y, const Color &c)
    {
        if (x >= 0 && x < mWidth && y >= 0 && y < mHeight)
            mGrid[y * mWidth + x] = c;
    }

    // -------------------------------------------------------------------------------

    // calcula a quantidade de dígitos de um inteiro
    int Length(int num)
    {
        unsigned digitos = 1;
        while (num /= 10)
            digitos++;
        return digitos;
    }

    // grava canvas no formato PPM
    bool Canvas::Save(string filename)
    {
        ofstream fout;
        fout.open(filename);
        if (!fout.is_open())
        {
            cerr << "Abertura do arquivo " << filename << " falhou!\n";
            return false;
        }

        // cabeçalho do arquivo PPM
        fout << "P3\n";                           // arquivo PPM
        fout << mWidth << ' ' << mHeight << '\n'; // largura e altura
        fout << "255\n";                          // valor máximo de cor

        // pode haver no máximo 70 caracteres em uma linha
        int char_count = 0;

        // dados do arquivo PPM
        for (int y = 0; y < mHeight; y++)
        {
            for (int x = 0; x < mWidth; x++)
            {
                // adiciona 0.5 para arredondar valor
                int r = mGrid[y * mWidth + x].x * 255 + 0.5;
                int g = mGrid[y * mWidth + x].y * 255 + 0.5;
                int b = mGrid[y * mWidth + x].z * 255 + 0.5;

                // mantém na faixa [0-255]
                if (r < 0)
                    r = 0;
                else if (r > 255)
                    r = 255;
                if (g < 0)
                    g = 0;
                else if (g > 255)
                    g = 255;
                if (b < 0)
                    b = 0;
                else if (b > 255)
                    b = 255;

                // o quanto char_count irá crescer com cada cor
                int tamR = Length(r) + 1;
                int tamG = Length(g) + 1;
                int tamB = Length(b) + 1;

                // tentando inserir R na linha
                if (char_count + tamR < 70)
                {
                    fout << r << ' ';
                    char_count += tamR;
                }
                else if (char_count + tamR == 70)
                {
                    fout << r << '\n';
                    char_count = 0;
                }
                else
                {
                    fout << '\n';
                    fout << r << ' ';
                    char_count = tamR;
                }

                // tentando inserir G na linha
                if (char_count + tamG < 70)
                {
                    fout << g << ' ';
                    char_count += tamG;
                }
                else if (char_count + tamG == 70)
                {
                    fout << g << '\n';
                    char_count = 0;
                }
                else
                {
                    fout << '\n';
                    fout << g << ' ';
                    char_count = tamG;
                }

                // tentando inserir B na linha
                if (char_count + tamB < 70)
                {
                    fout << b << ' ';
                    char_count += tamB;
                }
                else if (char_count + tamB == 70)
                {
                    fout << b << '\n';
                    char_count = 0;
                }
                else
                {
                    fout << '\n';
                    fout << b << ' ';
                    char_count = tamB;
                }
            }

            // se terminou a linha sem pular para a próxima
            if (char_count < 70)
            {
                fout << '\n';
                char_count = 0;
            }
        }

        fout.close();
        return true;
    }
}