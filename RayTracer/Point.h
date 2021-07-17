/**********************************************************************************
// Point (Arquivo de Cabeçalho)
//
// Criação:     27 Jun 2020
// Atualização:	17 Jul 2021
// Compilador:	Clang++ 12.0.5 / GNU g++ 9.3.0
//
// Descrição:	Define o tipo point, baseado em tupla.
//
**********************************************************************************/

#ifndef RAY_TRACER_POINT
#define RAY_TRACER_POINT

#include "Tuple.h"

namespace RayTracer
{
    struct Point : public Tuple
    {
        Point();											// construtor padrão
        Point(double px, double py, double pz); 			// construtor com coordenadas
        Point(Tuple &&t);					 				// conversão de tupla para ponto
    };
}

#endif
