/**********************************************************************************
// Point (Arquivo de Código Fonte)
//
// Criação:     27 Jun 2020
// Atualização:	15 Jul 2021
// Compilador:	Clang++ 12.0.5 / GNU g++ 9.3.0
//
// Descrição:	Define o tipo point, baseado em tupla.
//
**********************************************************************************/

#include "Point.h"

namespace RayTracer
{
    Point::Point()
        : Tuple(0.0, 0.0, 0.0, 1.0) {}

    Point::Point(double px, double py, double pz)
        : Tuple(px, py, pz, 1.0) {}

    Point::Point(Tuple &&t)
        : Tuple(t.x, t.y, t.z, 1.0) {}
}