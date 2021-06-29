/**********************************************************************************
// Ray (Arquivo de Código Fonte)
//
// Criação:		25 Jun 2021
// Atualização:	28 Jun 2021
// Compilador:	Clang++ 12.0.5 / GNU g++ 9.3.0
//
// Descrição:	Define a representação de um raio, 
//              a ser usada por um traçador de raios.
//
**********************************************************************************/

#include <cmath>
#include <algorithm>
#include "Ray.h"
using std::sort;

namespace RayTracer
{
    // -------------------------------------------------------------------------------

    Ray::Ray(Point orig, Vector dir)
        : origin(orig), direction(dir) {}

    Point Ray::Position(float t)
    { return origin + direction * t; }

    Ray Ray::Transform(Matrix m)
    { return Ray {m * origin, m * direction}; }

    // -------------------------------------------------------------------------------

    Intersection::Intersection(float t, Geometry &obj)
        : time(t), object(&obj) {}

    bool operator==(Intersection &a, const Intersection &b)
    {
        return (a.time == b.time) && (a.object == b.object);
    }

    bool operator<(const Intersection &a, const Intersection &b)
    {
        return a.time < b.time;
    }

    // -------------------------------------------------------------------------------

    Intersection * Hit(vector<Intersection> & intersections)
    {
        sort(intersections.begin(), intersections.end());

        for (auto &i : intersections)
        {
            if (i.time >= 0)
                return &i;
        }
        return nullptr;
    }

    // -------------------------------------------------------------------------------
}