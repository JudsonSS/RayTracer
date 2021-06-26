/**********************************************************************************
// Ray (Arquivo de Cabeçalho)
//
// Criação:		25 Jun 2021
// Atualização:	25 Jun 2021
// Compilador:	Clang++ 12.0.5 / GNU g++ 9.3.0
//
// Descrição:	Define a representação de um raio, 
//              a ser usada por um traçador de raios.
//
**********************************************************************************/

#ifndef RAY_TRACER_RAY
#define RAY_TRACER_RAY

#include "Types.h"

namespace RayTracer
{
	struct Ray
	{
        Point origin;                   // ponto de origem do raio
        Vector direction;               // direção do raio
		
		Ray(Point orig, Vector dir);    // construtor
        Point Position(float t);        // retorna posição na distância t ao longo do raio
	};

    struct Intersection
    {
        unsigned count;                 // quantidade de interseções
        float positions[2];             // posições das interseções
        
        Intersection();                 // construtor padrão
        float operator[](unsigned i);   // retorna valores das interseções
    };


    class Sphere
    {
    public:
        Intersection Intersect(Ray r);  // retorna pontos de interseção com o raio
    };
}

#endif