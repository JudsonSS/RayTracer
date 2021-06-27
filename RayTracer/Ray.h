/**********************************************************************************
// Ray (Arquivo de Cabeçalho)
//
// Criação:		25 Jun 2021
// Atualização:	27 Jun 2021
// Compilador:	Clang++ 12.0.5 / GNU g++ 9.3.0
//
// Descrição:	Define a representação de um raio, 
//              a ser usada por um traçador de raios.
//
**********************************************************************************/

#ifndef RAY_TRACER_RAY
#define RAY_TRACER_RAY

#include "Types.h"
#include "Matrix.h"
#include <vector>
using std::vector;

namespace RayTracer
{
    class Geometry;

	struct Ray
	{
        Point origin;                               // ponto de origem do raio
        Vector direction;                           // direção do raio

		Ray(Point orig, Vector dir);                // construtor
        Point Position(float t);                    // retorna posição na distância t ao longo do raio
        Ray Transform(Matrix m);                    // retorna raio transformada pela matrix
	};

    struct Intersection
    {           
        float time;                                 // valor de distância ao longo do raio
        Geometry * object;                          // objeto em que ocorreu a interseção
        Intersection(float t, Geometry & obj);      // construtor padrão 
    };
    
    bool operator==(Intersection &a, const Intersection &b);        // comparação de igualdade entre interseções
    bool operator<(const Intersection &a, const Intersection &b);   // permite comparações para ordenação
    Intersection * Hit(vector<Intersection> & intersections);       // retorna interseção com menor valor não-negativo
}

#endif