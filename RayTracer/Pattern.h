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
    // -------------------------------------------------------------------------------------------------
    // Padrão
    // -------------------------------------------------------------------------------------------------

    struct Pattern
    {
        Color first;                                                        // primeira cor
        Color second;                                                       // segunda cor
        Matrix transform;                                                   // matrix de transformação

        Pattern();                                                          // construtor padrão
        Pattern(const Color &a, const Color &b);                            // construtor com cores
        virtual ~Pattern();                                                 // destrutor
        virtual Color At(const Point &p) const = 0;                         // retorna cor no ponto
        Color AtShape(const Shape &shape, const Point &p) const;            // considera transformações
    };

    // -------------------------------------------------------------------------------------------------
    // Listra
    // -------------------------------------------------------------------------------------------------

    struct Stripe : public Pattern
    {
        Stripe();                                                           // construtor padrão
        Stripe(const Color &a, const Color &b);                             // construtor com cores
        Color At(const Point &p) const;                                     // retorna cor no ponto indicado
    };
}

#endif
