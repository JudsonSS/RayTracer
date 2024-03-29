/**********************************************************************************
// Color (Arquivo de Cabeçalho)
//
// Criação:     27 Jun 2020
// Atualização:	17 Jul 2021
// Compilador:	Clang++ 12.0.5 / GNU g++ 9.3.0
//
// Descrição:	Define o tipo cor, baseado em tupla.
//
**********************************************************************************/

#ifndef RAY_TRACER_COLOR
#define RAY_TRACER_COLOR

#include "Tuple.h"

namespace RayTracer
{
    struct Color : public Tuple
    {
        Color();                                                    // construtor padrão
        Color(double red, double green, double blue);               // construtor
        Color(Tuple &&t);                                           // conversão de tupla para cor

        // membros estáticos
        static Color Black;                                         // cor preta
        static Color White;                                         // cor branca
    };

    Color operator*(const Color &c1, const Color &c2);              // mistura de cores (blend)
}

#endif
