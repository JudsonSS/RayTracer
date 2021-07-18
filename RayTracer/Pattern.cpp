/**********************************************************************************
// Pattern (Arquivo de Código Fonte)
//
// Criação:     17 Jul 2020
// Atualização:	18 Jul 2021
// Compilador:	Clang++ 12.0.5 / GNU g++ 9.3.0
//
// Descrição:	Define padrões de cores, como listrado, gradiente, circular, etc.
//
**********************************************************************************/

#include "Pattern.h"
#include <cmath>

namespace RayTracer
{
    // -------------------------------------------------------------------------------------------------
    // Padrão
    // -------------------------------------------------------------------------------------------------

    Pattern::Pattern()
        : first(Color::White),
          second(Color::Black),
          transform(Matrix::Identity) {}

    Pattern::Pattern(const Color &a, const Color &b)
        : first(a),
          second(b),
          transform(Matrix::Identity) {}

    Pattern::~Pattern() {}
    
    // ---------------------------------------------------------------------------------------

    Color Pattern::AtShape(const Shape &shape, const Point &p) const
    {
        // converte ponto para coordenadas do objeto
        Point local_point = shape.transform.Inverse() * p;
        // converte ponto para coordenadas do padrão
        Point pattern_point = this->transform.Inverse() * local_point;
        // retorna cor do ponto transformado
        return At(pattern_point);
    }

    // -------------------------------------------------------------------------------------------------
    // Listra
    // -------------------------------------------------------------------------------------------------

    Stripe::Stripe() {}

    Stripe::Stripe(const Color &a, const Color &b)
        : Pattern(a,b) {}

    // ---------------------------------------------------------------------------------------

    Color Stripe::At(const Point &p) const
    {
        // a medida que a coordenada x muda, a listra alterna entre as cores 'a' e 'b'
        if (int(floor(p.x)) % 2 == 0)
            return first;
        else
            return second;
    }

    // -------------------------------------------------------------------------------------------------
    // Gradiente
    // -------------------------------------------------------------------------------------------------

    Gradient::Gradient() {}

    Gradient::Gradient(const Color &a, const Color &b)
        : Pattern(a,b) {}

    // ---------------------------------------------------------------------------------------

    Color Gradient::At(const Point &p) const
    {
        // interpolação linear entre as cores
        return first + (second - first) * (p.x - floor(p.x));
    }

    // ---------------------------------------------------------------------------------------
}