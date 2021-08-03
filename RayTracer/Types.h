/**********************************************************************************
// Types (Arquivo de Cabeçalho)
//
// Criação:     27 Jun 2020
// Atualização:	15 Jul 2021
// Compilador:	Clang++ 12.0.5 / GNU g++ 9.3.0
//
// Descrição:	Define alguns apelidos para tipos básicos e a 
//              operação de igualdade sobre pontos flutuantes.
//
**********************************************************************************/

#ifndef RAY_TRACER_TYPES
#define RAY_TRACER_TYPES

using uint   = unsigned int;
using ushort = unsigned short;
using ulong  = unsigned long;
using ullong = unsigned long long;

namespace RayTracer
{
    // ---------------------------------------------------------------------------------------

    const double EPSILON = 0.0001;		    // diferença máxima permitida para a igualdade
    const double PI = 3.14159265358979;     // constante PI
    
    bool Equal(double a, double b);	   	    // comparação de pontos-flutuantes
    
    // ---------------------------------------------------------------------------------------
}

#endif
