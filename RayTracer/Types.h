/**********************************************************************************
// Types (Arquivo de Cabeçalho)
//
// Criação:		27 Jun 2020
// Atualização:	03 Jul 2021
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

	struct Tuple
	{
		float x;
		float y;
		float z;
		float w;

		Tuple();										// construtor padrão
		Tuple(float px, float py, float pz, float pw); 	// construtor com valores
	};

	bool Equal(float a, float b);	   					// comparação de pontos-flutuantes
	bool operator==(const Tuple &a, const Tuple &b);	// comparação de igualdade
	Tuple operator+(const Tuple &a, const Tuple &b);	// soma 
	Tuple operator-(const Tuple &a, const Tuple &b);	// subtração
	Tuple operator-(const Tuple &t);					// menos unário
	Tuple operator*(const Tuple &t, float v);			// multiplicação por escalar
	Tuple operator*(float v, const Tuple &t); 			// multiplicação por escalar
	Tuple operator/(const Tuple &t, float v);			// divisão por escalar

	// ---------------------------------------------------------------------------------------
	// Ponto
	// ---------------------------------------------------------------------------------------

	class Point : public Tuple
	{
	public:
		Point(float px, float py, float pz); 			// construtor
		Point(Tuple &&t);					 			// conversão de tupla para ponto
	};

	// ---------------------------------------------------------------------------------------
	// Vetor
	// ---------------------------------------------------------------------------------------

	class Vector : public Tuple
	{
	public:
		Vector(float px, float py, float pz); 			// construtor
		Vector(Tuple &&t);					  			// conversão de tupla para vetor

		float Magnitude();								// comprimento do vetor
		Vector Normalized();							// vetor normalizado
		float Dot(Vector v);							// produto escalar entre vetores
		Vector Cross(Vector v); 						// produto vetorial entre vetores
		Vector Reflect(Vector normal);					// obtém reflexão do vetor com a normal
	};

	// ---------------------------------------------------------------------------------------
	// Cor
	// ---------------------------------------------------------------------------------------

	class Color : public Tuple
	{
	public:
		Color();										// construtor padrão
		Color(float red, float green, float blue); 		// construtor
		Color(Tuple &&t);						   		// conversão de tupla para cor
	};

	Color operator*(const Color &c1, const Color &c2); 	// multiplicação de cores (blend)

	// ---------------------------------------------------------------------------------------
}

#endif
