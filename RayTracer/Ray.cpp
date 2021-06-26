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
    // vetor do centro da esfera, posição (0,0,0), até a origem do raio
    Vector center_origin = r.origin - Point{0,0,0};

    // coeficientes da equação do segundo grau: at2 + bt + c = 0
    float a = r.direction.Dot(r.direction);
    float b = 2 * r.direction.Dot(center_origin);
    float c = center_origin.Dot(center_origin) - 1;

    // discriminante da equação do segundo grau
    float discriminant = b * b - 4 * a * c;

    // se o discriminante é negativo não há raízes reais 
    if (discriminant < 0)
        return Intersection();
    
    // existem duas raízes iguais 
    // quando o discriminante é igual a zero 
    // ou duas raízes diferentes se ele é positivo
    Intersection i;
    i.count = 2;
    i.positions[0] = (-b - sqrt(discriminant)) / (2 * a);
    i.positions[1] = (-b + sqrt(discriminant)) / (2 * a);   
    return i;
}
