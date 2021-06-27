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
#include "Ray.h"
using namespace RayTracer;

// -------------------------------------------------------------------------------

RayTracer::Ray::Ray(Point orig, Vector dir)
    : origin(orig), direction(dir) {}

Point RayTracer::Ray::Position(float t)
{ return origin + direction * t; } 

// -------------------------------------------------------------------------------

RayTracer::Intersection::Intersection(float t, Geometry & obj)
    : time(t), object(obj) {}

// -------------------------------------------------------------------------------