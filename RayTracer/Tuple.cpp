/**********************************************************************************
// Tuple (Arquivo de Código Fonte)
//
// Criação:     27 Jun 2020
// Atualização:	15 Jul 2021
// Compilador:	Clang++ 12.0.5 / GNU g++ 9.3.0
//
// Descrição:	Define o tipo base tupla, necessário para a construção 
//              de pontos, vetores e cores.
//
**********************************************************************************/

#include "Types.h"
#include "Tuple.h"

namespace RayTracer
{
    Tuple::Tuple()
        : x(0.0), y(0.0), z(0.0), w(0.0) {}

    Tuple::Tuple(double px, double py, double pz, double pw)
        : x(px), y(py), z(pz), w(pw) {}

    bool operator==(const Tuple &a, const Tuple &b)
    { return Equal(a.x, b.x) && Equal(a.y, b.y) && Equal(a.z, b.z) && Equal(a.w, b.w); }

    Tuple operator+(const Tuple &a, const Tuple &b)
    { return Tuple(a.x + b.x, a.y + b.y, a.z + b.z, a.w + b.w); }

    Tuple operator-(const Tuple &a, const Tuple &b)
    { return Tuple(a.x - b.x, a.y - b.y, a.z - b.z, a.w - b.w); }

    Tuple operator-(const Tuple &t)
    { return Tuple(-t.x, -t.y, -t.z, -t.w); }

    Tuple operator*(const Tuple &t, double v)
    { return Tuple(t.x * v, t.y * v, t.z * v, t.w * v); }

    Tuple operator/(const Tuple &t, double v)
    { return Tuple(t.x / v, t.y / v, t.z / v, t.w / v); }

    Tuple operator*(double v, const Tuple &t)
    { return Tuple(t.x * v, t.y * v, t.z * v, t.w * v); }
}