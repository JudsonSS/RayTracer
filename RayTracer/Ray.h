/**********************************************************************************
// Ray (Arquivo de Cabeçalho)
//
// Criação:     25 Jun 2021
// Atualização:	17 Jul 2021
// Compilador:	Clang++ 12.0.5 / GNU g++ 9.3.0
//
// Descrição:	Define a representação de um raio, 
//              a ser usada por um traçador de raios.
//
**********************************************************************************/

#ifndef RAY_TRACER_RAY
#define RAY_TRACER_RAY

#include "Types.h"
#include "Point.h"
#include "Vector.h"
#include "Matrix.h"
#include <vector>
using std::vector;

namespace RayTracer
{
    // ---------------------------------------------------------------------------------------
    // Raio
    // ---------------------------------------------------------------------------------------

    struct Ray
    {
        Point origin;                               // ponto de origem do raio
        Vector direction;                           // direção do raio

        Ray();                                      // construtor padrão
        Ray(const Point &orig, const Vector &dir);  // construtor com origem e direção
        Point Position(double t) const;             // retorna posição na distância t ao longo do raio
        Ray Transform(const Matrix &m) const;       // retorna raio transformado pela matrix
    };

    // ---------------------------------------------------------------------------------------
    // Interseção
    // ---------------------------------------------------------------------------------------

    class Object;                                   // declaração adiantada

    struct Intersection
    {           
        double time;                                // valor de distância ao longo do raio
        Object * object;                            // objeto em que ocorreu a interseção

        Intersection();                             // construtor padrão
        Intersection(double t, Object & obj);       // construtor com tempo e objeto
    };
    
    // comparação de igualdade entre interseções
    bool operator==(const Intersection &a, const Intersection &b);
    
    // comparação de menor entre interseções  
    bool operator<(const Intersection &a, const Intersection &b);

    // retorna interseção com menor valor não-negativo   
    Intersection Hit(vector<Intersection> &intersections);          

    // ---------------------------------------------------------------------------------------
}

#endif