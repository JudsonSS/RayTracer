/**********************************************************************************
// Color (Arquivo de Código Fonte)
//
// Criação:     27 Jun 2020
// Atualização:	15 Jul 2021
// Compilador:	Clang++ 12.0.5 / GNU g++ 9.3.0
//
// Descrição:	Define o tipo cor, baseado em tupla.
//
**********************************************************************************/

#include "Color.h"
#include <cmath>

namespace RayTracer
{
    // ---------------------------------------------------------------------------------------
    // Color
    // ---------------------------------------------------------------------------------------

    Color::Color()
        : Tuple(0.0, 0.0, 0.0, 0.0) {}

    Color::Color(double r, double g, double b)
        : Tuple(r, g, b, 0.0) {}

    Color::Color(Tuple &&t)
        : Tuple(t.x, t.y, t.z, 0.0) {}

    Color operator*(const Color &c1, const Color &c2)
    { return Color(c1.x * c2.x, c1.y * c2.y, c1.z * c2.z); }

    Color Color::Black {0,0,0};
    Color Color::White {1,1,1};

    // ---------------------------------------------------------------------------------------
    // Stripe
    // ---------------------------------------------------------------------------------------

    Color Stripe::At(const Point &p) const
    {
        // a medida que a coordenada x muda, a listra alterna entre as cores 'a' e 'b'
        if (int(floor(p.x)) % 2 == 0)
            return a;
        else
            return b;
    }

    // ---------------------------------------------------------------------------------------
}