/**********************************************************************************
// Geometry (Arquivo de Cabeçalho)
//
// Criação:		26 Jun 2021
// Atualização:	26 Jun 2021
// Compilador:	Clang++ 12.0.5 / GNU g++ 9.3.0
//
// Descrição:	Define uma classe base para geometrias e classes para as 
//              geometrias específicas, como esferas, cubos, cilíndros, etc.
//
**********************************************************************************/

#ifndef RAY_TRACER_GEOMETRY
#define RAY_TRACER_GEOMETRY

#include <vector>
#include "Ray.h"
#include "Matrix.h"
using std::vector;

namespace RayTracer
{
    enum GeometryTypes
    {
        UNKNOWN_T,
        SPHERE_T
    };

    struct Geometry
    {
        unsigned type;                                      // tipo da geometria 
        Matrix transform;                                   // matrix de transformação
        
        Geometry();                                         // construtor padrão
        virtual vector<Intersection> Intersect(Ray r) = 0;  // retorna pontos de interseção com o raio
    };

    class Sphere : public Geometry
    {
    public:
        Sphere();                                           // construtor padrão
        vector<Intersection> Intersect(Ray r);              // retorna pontos de interseção com o raio
    };
}

#endif