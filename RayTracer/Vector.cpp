/**********************************************************************************
// Vector (Arquivo de Código Fonte)
//
// Criação:     27 Jun 2020
// Atualização:	15 Jul 2021
// Compilador:	Clang++ 12.0.5 / GNU g++ 9.3.0
//
// Descrição:	Define o tipo vetor, baseado em tupla.
//
**********************************************************************************/

#include "Vector.h"
#include <cmath>

namespace RayTracer
{
    Vector::Vector()
        : Tuple(0.0, 0.0, 0.0, 0.0) {}

    Vector::Vector(double px, double py, double pz)
        : Tuple(px, py, pz, 0.0) {}

    Vector::Vector(Tuple &&t)
        : Tuple(t.x, t.y, t.z, 0.0) {}

    double Vector::Magnitude() const
    { return sqrt(x * x + y * y + z * z + w * w); }

    Vector Vector::Normalized() const
    {
        double mag = Magnitude();
        return Vector(x / mag, y / mag, z / mag);
    }

    double Vector::Dot(const Vector &v) const
    { return x * v.x + y * v.y + z * v.z; }

    Vector Vector::Cross(const Vector &v) const
    { return Vector(y * v.z - z * v.y, z * v.x - x * v.z, x * v.y - y * v.x); }

    Vector Vector::Reflect(const Vector &normal) const
    { return (*this) - normal * 2 * this->Dot(normal); }

}