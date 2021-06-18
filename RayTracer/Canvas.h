/**********************************************************************************
// Canvas (Arquivo de Cabeçalho)
//
// Criação:		17 Jun 2021
// Atualização:	17 Jun 2021
// Compilador:	Clang++ 12.0.5 / GNU g++ 9.3.0
//
// Descrição:	Define uma representação para um grade retangular de pixels.
//              Cada pixel possui uma cor RGB.
//
**********************************************************************************/

#ifndef RAY_TRACER_CANVAS
#define RAY_TRACER_CANVAS

#include "Types.h"
#include <string>
using std::string;

namespace RayTracer
{
	class Canvas
	{
	private:
		Color ** grid;									// grade (matriz) de cores
		int lines;										// número de linhas da grade
		int cols;										// número de colunas da grade

	public:
		Canvas(int width, int height);					// construtor 
		~Canvas();										// destrutor

		int Width() const;								// retorna largura da grade
		int Height() const;								// retorna altura da grade
		Color At(int x, int y);							// retorna cor da posição (x,y)
		void Paint(int x, int y, Color c);				// pinta pixel (x,y) com uma cor
		bool Save(string filename);						// grava canvas no formato PPM
	};
}

#endif