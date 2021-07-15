/**********************************************************************************
// Tuple (Arquivo de Cabeçalho)
//
// Criação:     27 Jun 2020
// Atualização:	15 Jul 2021
// Compilador:	Clang++ 12.0.5 / GNU g++ 9.3.0
//
// Descrição:	Define o tipo base tupla, necessário para a construção 
//              de pontos, vetores e cores.
//
**********************************************************************************/

#ifndef RAY_TRACER_TUPLE
#define RAY_TRACER_TUPLE

#include "Types.h"

namespace RayTracer
{
    struct Tuple
    {
        double x;											    // coordenada no eixo x
        double y;											    // coordenada no eixo y
        double z;											    // coordenada no eixo z
        double w;											    // ponto ou vetor

        Tuple();											    // construtor padrão
        Tuple(double px, double py, double pz, double pw); 	    // construtor com valores
    };

    bool operator==(const Tuple &a, const Tuple &b);		    // comparação de igualdade
    Tuple operator+(const Tuple &a, const Tuple &b);		    // soma 
    Tuple operator-(const Tuple &a, const Tuple &b);		    // subtração
    Tuple operator-(const Tuple &t);						    // menos unário
    Tuple operator*(const Tuple &t, double v);				    // multiplicação por escalar
    Tuple operator*(double v, const Tuple &t); 				    // multiplicação por escalar
    Tuple operator/(const Tuple &t, double v);				    // divisão por escalar
}

#endif
