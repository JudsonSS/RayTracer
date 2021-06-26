/**********************************************************************************
// Ray (Arquivo de Código Fonte)
//
// Criação:		25 Jun 2021
// Atualização:	25 Jun 2021
// Compilador:	Clang++ 12.0.5 / GNU g++ 9.3.0
//
// Descrição:	Define a representação de um raio, 
//              a ser usada por um traçador de raios.
//
**********************************************************************************/

#include <cmath>
#include "Ray.h"
using namespace RayTracer;

// -------------------------------------------------------------------------------

RayTracer::Ray::Ray(Point orig, Vector dir)
    : origin(orig), direction(dir) {}

Point RayTracer::Ray::Position(float t)
{ return origin + direction * t; } 

// -------------------------------------------------------------------------------

RayTracer::Intersection::Intersection()
    : count(0), positions{0,0} {}

float RayTracer::Intersection::operator[](unsigned i)
{ return positions[i]; }

// -------------------------------------------------------------------------------

Intersection RayTracer::Sphere::Intersect(Ray r)
{
    // vetor do centro da esfera (0,0,0) até a origem do raio
    Vector sphere_to_ray = r.origin - Point{0,0,0};

    float a = r.direction.Dot(r.direction);
    float b = 2 * r.direction.Dot(sphere_to_ray);
    float c = sphere_to_ray.Dot(sphere_to_ray) - 1;

    float discriminant = b * b - 4 * a * c;

    if (discriminant < 0)
        return Intersection();
    
    Intersection i;
    i.count = 2;
    i.positions[0] = (-b - sqrt(discriminant)) / (2 * a);
    i.positions[1] = (-b + sqrt(discriminant)) / (2 * a);   
    return i;
}
