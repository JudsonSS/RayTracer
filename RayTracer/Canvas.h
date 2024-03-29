/**********************************************************************************
// Canvas (Arquivo de Cabeçalho)
//
// Criação:     17 Jun 2021
// Atualização:	15 Jul 2021
// Compilador:	Clang++ 12.0.5 / GNU g++ 9.3.0
//
// Descrição:	Define uma representação para um grade retangular de pixels.
//              Cada pixel possui uma cor RGB.
//
**********************************************************************************/

#ifndef RAY_TRACER_CANVAS
#define RAY_TRACER_CANVAS

#include "Types.h"
#include "Color.h"
#include <string>
using std::string;

namespace RayTracer
{
    class Canvas
    {
    private:
        Color * mGrid;									// grade de pixels
        uint mWidth;								    // largura do canvas
        uint mHeight;								    // altura do canvas
        uint mSize;									    // total de pixels

    public:
        Canvas(uint width, uint height);		        // construtor 
        Canvas(Canvas &c);								// construtor de cópia
        Canvas(Canvas &&c);								// construtor de transferência
        ~Canvas();										// destrutor

        Canvas& operator=(Canvas& mat);                 // atribuição por cópia
        Canvas& operator=(Canvas&& mat);               	// atribuição por transferência

        int Width() const;								// retorna largura 
        int Height() const;								// retorna altura
        Color At(int x, int y) const;					// retorna cor da posição (x,y)
        void Paint(int x, int y, const Color &c);		// pinta pixel (x,y) com uma cor
        bool Save(string filename);						// grava canvas no formato PPM
    };
}

#endif