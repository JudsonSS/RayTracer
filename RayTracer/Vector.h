/**********************************************************************************
// Vector (Arquivo de Cabeçalho)
//
// Criação:     27 Jun 2020
// Atualização:	15 Jul 2021
// Compilador:	Clang++ 12.0.5 / GNU g++ 9.3.0
//
// Descrição:	Define o tipo vetor, baseado em tupla.
//
**********************************************************************************/

#ifndef RAY_TRACER_VECTOR
#define RAY_TRACER_VECTOR

#include "Tuple.h"

namespace RayTracer
{
    struct Vector : public Tuple
    {
        Vector();											// construtor padrão
        Vector(double px, double py, double pz); 			// construtor com coordenadas
        Vector(Tuple &&t);					  				// conversão de tupla para vetor

        double Magnitude() const;							// comprimento do vetor
        Vector Normalized() const;							// vetor normalizado
        double Dot(const Vector &v) const;				    // produto escalar entre vetores
        Vector Cross(const Vector &v) const; 				// produto vetorial entre vetores
        Vector Reflect(const Vector &normal) const;			// obtém reflexão do vetor com a normal
    };
}

#endif
