/**********************************************************************************
// Types (Arquivo de Cabeçalho)
//
// Criação:     27 Jun 2020
// Atualização:	10 Jul 2021
// Compilador:	Clang++ 12.0.5 / GNU g++ 9.3.0
//
// Descrição:	Define os tipos básicos necessários para a construção de um 
//              traçador de raios: tuplas, pontos, vetores, cores, etc.
//
**********************************************************************************/

#ifndef RAY_TRACER_TYPES
#define RAY_TRACER_TYPES

#include <string>
using std::string;

namespace RayTracer
{
    // ---------------------------------------------------------------------------------------
    // Tupla
    // ---------------------------------------------------------------------------------------

    const double EPSILON = 0.00001;							// diferença máxima para comparações
    
    struct Tuple
    {
        double x;											// coordenada no eixo x
        double y;											// coordenada no eixo y
        double z;											// coordenada no eixo z
        double w;											// ponto ou vetor

        Tuple();											// construtor padrão
        Tuple(double px, double py, double pz, double pw); 	// construtor com valores
    };

    bool Equal(double a, double b);	   						// comparação de pontos-flutuantes
    bool operator==(const Tuple &a, const Tuple &b);		// comparação de igualdade
    Tuple operator+(const Tuple &a, const Tuple &b);		// soma 
    Tuple operator-(const Tuple &a, const Tuple &b);		// subtração
    Tuple operator-(const Tuple &t);						// menos unário
    Tuple operator*(const Tuple &t, double v);				// multiplicação por escalar
    Tuple operator*(double v, const Tuple &t); 				// multiplicação por escalar
    Tuple operator/(const Tuple &t, double v);				// divisão por escalar

    // ---------------------------------------------------------------------------------------
    // Ponto
    // ---------------------------------------------------------------------------------------

    class Point : public Tuple
    {
    public:
        Point();											// construtor padrão
        Point(double px, double py, double pz); 			// construtor com coordenadas
        Point(Tuple &&t);					 				// conversão de tupla para ponto
    };

    // ---------------------------------------------------------------------------------------
    // Vetor
    // ---------------------------------------------------------------------------------------

    class Vector : public Tuple
    {
    public:
        Vector();											// construtor padrão
        Vector(double px, double py, double pz); 			// construtor com coordenadas
        Vector(Tuple &&t);					  				// conversão de tupla para vetor

        double Magnitude() const;							// comprimento do vetor
        Vector Normalized() const;							// vetor normalizado
        double Dot(const Vector &v);						// produto escalar entre vetores
        Vector Cross(const Vector &v); 						// produto vetorial entre vetores
        Vector Reflect(const Vector &normal);				// obtém reflexão do vetor com a normal
    };

    // ---------------------------------------------------------------------------------------
    // Cor
    // ---------------------------------------------------------------------------------------

    class Color : public Tuple
    {
    public:
        Color();											// construtor padrão
        Color(double red, double green, double blue); 		// construtor
        Color(Tuple &&t);						   			// conversão de tupla para cor
    };

    Color operator*(const Color &c1, const Color &c2); 		// mistura de cores (blend)

    // ---------------------------------------------------------------------------------------
}

#endif
