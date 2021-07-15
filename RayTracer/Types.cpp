/**********************************************************************************
// Types (Arquivo de Código Fonte)
//
// Criação:     27 Jun 2020
// Atualização:	15 Jul 2021
// Compilador:	Clang++ 12.0.5 / GNU g++ 9.3.0
//
// Descrição:	Define alguns tipos básicos e operações sobre eles.
//
**********************************************************************************/

#include "Types.h"
#include <cmath>

namespace RayTracer
{
    bool Equal(double a, double b)
    {
        if (abs(a - b) < EPSILON)
            return true;
        else
            return false;
    }
}