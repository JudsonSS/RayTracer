/**********************************************************************************
// Ray (Arquivo de Código Fonte)
//
// Criação:		25 Jun 2021
// Atualização:	27 Jun 2021
// Compilador:	Clang++ 12.0.5 / GNU g++ 9.3.0
//
// Descrição:	Define a representação de um raio, 
//              a ser usada por um traçador de raios.
//
**********************************************************************************/

#include <cmath>
#include <algorithm>
#include "Ray.h"
using namespace RayTracer;
using std::sort;

// -------------------------------------------------------------------------------

RayTracer::Ray::Ray(Point orig, Vector dir)
    : origin(orig), direction(dir) {}

Point RayTracer::Ray::Position(float t)
{ return origin + direction * t; } 

Ray RayTracer::Ray::Transform(Matrix m)
{
    Ray r {m * origin, m * direction};
    return r;
}

// -------------------------------------------------------------------------------

RayTracer::Intersection::Intersection(float t, Geometry & obj)
    : time(t), object(&obj) {}

bool RayTracer::operator==(Intersection &a, const Intersection &b)
{ return (a.time == b.time) && (a.object == b.object); }

bool RayTracer::operator<(const Intersection &a, const Intersection &b)
{ return a.time < b.time; }

// -------------------------------------------------------------------------------

Intersection * RayTracer::Hit(vector<Intersection> intersections)
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