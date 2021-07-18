/**********************************************************************************
// Pattern (Arquivo de Cabeçalho)
//
// Criação:     17 Jul 2020
// Atualização:	17 Jul 2021
// Compilador:	Clang++ 12.0.5 / GNU g++ 9.3.0
//
// Descrição:	Define padrões de cores, como listrado, gradiente, circular, etc.
//
**********************************************************************************/

#ifndef RAY_TRACER_PATTERN
#define RAY_TRACER_PATTERN

#include "Color.h"
#include "Point.h"
#include "Matrix.h"
#include "Shape.h"

namespace RayTracer
{
    struct Stripe
    {
        Color a;                                                    // primeira cor da listra
        Color b;                                                    // segunda cor da listra
        Matrix transform;                                           // matrix de transformação

        Stripe();                                                   // construtor padrão
        Stripe(const Color &c1, const Color &c2);                   // construtor com cores
        Color At(const Point &p) const;                             // retorna cor no ponto indicado
        Color AtShape(const Shape &shape, const Point &p) const;    // considera transformações
    };
}

#endif
