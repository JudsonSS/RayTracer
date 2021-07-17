/**********************************************************************************
// Ray (Arquivo de Código Fonte)
//
// Criação:     25 Jun 2021
// Atualização:	15 Jul 2021
// Compilador:	Clang++ 12.0.5 / GNU g++ 9.3.0
//
// Descrição:	Define a representação de um raio, 
//              a ser usada por um traçador de raios.
//
**********************************************************************************/

#include <cmath>
#include <algorithm>
#include "Ray.h"
#include "Object.h"
using std::sort;

namespace RayTracer
{
    // ---------------------------------------------------------------------------------------
    // Raio
    // ---------------------------------------------------------------------------------------

    Ray::Ray()
        : origin(Point{0,0,0}), direction(Vector{0,0,0}) {}

    Ray::Ray(const Point &orig, const Vector &dir)
        : origin(orig), direction(dir) {}

    Point Ray::Position(double t) const
    { return origin + direction * t; }

    Ray Ray::Transform(const Matrix &m) const
    { return Ray {m * origin, m * direction}; }

    // ---------------------------------------------------------------------------------------
    // Interseção
    // ---------------------------------------------------------------------------------------

    Intersection::Intersection()
        : time(0), object(nullptr) {}

    Intersection::Intersection(double t, Object &obj)
        : time(t), object(&obj) {}

    bool operator==(const Intersection &a, const Intersection &b)
    { return (a.time == b.time) && (a.object == b.object); }

    bool operator<(const Intersection &a, const Intersection &b)
    { return a.time < b.time; }

    // ---------------------------------------------------------------------------------------

    Intersection Hit(vector<Intersection> &intersections)
    {
        for (auto &i : intersections)
        {
            if (i.time >= 0)
                return i;
        }
        return Intersection();
    }
    
    // -------------------------------------------------------------------------------
}