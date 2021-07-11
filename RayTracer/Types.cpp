/**********************************************************************************
// Types (Arquivo de Código Fonte)
//
// Criação:     27 Jun 2020
// Atualização:	10 Jul 2021
// Compilador:	Clang++ 12.0.5 / GNU g++ 9.3.0
//
// Descrição:	Define os tipos básicos necessários para a construção de um 
//              traçador de raios: tuplas, pontos, vetores, cores, etc.
//
**********************************************************************************/

#include "Types.h"
#include <cmath>

namespace RayTracer
{
    // -------------------------------------------------------------------------------
    // Comparação Ponto-Flutuante
    // -------------------------------------------------------------------------------

    bool Equal(double a, double b)
    {
        if (abs(a - b) < EPSILON)
            return true;
        else
            return false;
    }

    // -------------------------------------------------------------------------------
    // Tupla
    // -------------------------------------------------------------------------------

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

    // -------------------------------------------------------------------------------
    // Ponto
    // -------------------------------------------------------------------------------

    Point::Point()
        : Tuple(0.0, 0.0, 0.0, 1.0) {}

    Point::Point(double px, double py, double pz)
        : Tuple(px, py, pz, 1.0) {}

    Point::Point(Tuple &&t)
        : Tuple(t.x, t.y, t.z, 1.0) {}

    // -------------------------------------------------------------------------------
    // Vetor
    // -------------------------------------------------------------------------------

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

    // -------------------------------------------------------------------------------
    // Cor
    // -------------------------------------------------------------------------------

    Color::Color()
        : Tuple(0.0, 0.0, 0.0, 0.0) {}

    Color::Color(double r, double g, double b)
        : Tuple(r, g, b, 0.0) {}

    Color::Color(Tuple &&t)
        : Tuple(t.x, t.y, t.z, 0.0) {}

    Color operator*(const Color &c1, const Color &c2)
    { return Color(c1.x * c2.x, c1.y * c2.y, c1.z * c2.z); }

    // -------------------------------------------------------------------------------
}