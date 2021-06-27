/**********************************************************************************
// Geometry (Arquivo de Código Fonte)
//
// Criação:		26 Jun 2021
// Atualização:	26 Jun 2021
// Compilador:	Clang++ 12.0.5 / GNU g++ 9.3.0
//
// Descrição:	Define uma classe base para geometrias e classes para as 
//              geometrias específicas, como esferas, cubos, cilíndros, etc.
//
**********************************************************************************/

#include <cmath>
#include "Geometry.h"
using namespace RayTracer;

// -------------------------------------------------------------------------------

RayTracer::Geometry::Geometry()
    : type(UNKNOWN_T) {}

// -------------------------------------------------------------------------------

RayTracer::Sphere::Sphere()
{ 
    type = SPHERE_T; 
}

vector<Intersection> RayTracer::Sphere::Intersect(Ray r)
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
        return {};
    
    // existem duas raízes iguais 
    // quando o discriminante é igual a zero 
    // ou duas raízes diferentes se ele é positivo
    vector<Intersection> v;
    v.push_back(Intersection((-b - sqrt(discriminant)) / (2 * a), *this));
    v.push_back(Intersection((-b + sqrt(discriminant)) / (2 * a), *this));
    return v;
}