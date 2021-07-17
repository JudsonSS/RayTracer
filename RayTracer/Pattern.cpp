/**********************************************************************************
// Pattern (Arquivo de Código Fonte)
//
// Criação:     17 Jul 2020
// Atualização:	17 Jul 2021
// Compilador:	Clang++ 12.0.5 / GNU g++ 9.3.0
//
// Descrição:	Define padrões de cores, como listrado, gradiente, circular, etc.
//
**********************************************************************************/

#include "Pattern.h"
#include <cmath>

namespace RayTracer
{
    // ---------------------------------------------------------------------------------------

    Stripe::Stripe()
        : transform(Matrix::Identity) {}

    Stripe::Stripe(const Color &c1, const Color &c2)
        : a(c1), 
          b(c2), 
          transform(Matrix::Identity) {}

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

    Color Stripe::AtObject(const Object &obj, const Point &p) const
    {
        // converte ponto para coordenadas do objeto
        Point local_point = obj.transform.Inverse() * p;
        // converte ponto para coordenadas do padrão
        Point pattern_point = this->transform.Inverse() * local_point;
        // retorna cor do ponto transformado
        return this->At(pattern_point);
    }

    // ---------------------------------------------------------------------------------------
}