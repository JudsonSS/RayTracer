#ifndef RAY_TRACER_TYPES
#define RAY_TRACER_TYPES

namespace RayTracer
{
	// -----------------------------------
	// Tupla
	// -----------------------------------

	struct Tuple
	{
		float x;
		float y;
		float z;
		float w;

		Tuple(float px, float py, float pz, float pw);	// construtor
		bool operator==(const Tuple t);					// comparação de igualdade
		Tuple operator+(const Tuple t);					// soma
		Tuple operator-(const Tuple t);					// subtração
		Tuple operator-();								// menos unário
		Tuple operator*(float v);						// multiplicação por escalar
		Tuple operator/(float v);						// divisão por escalar
	};

	bool Equal(float a, float b);						// comparação de pontos-flutuantes
	Tuple operator*(float v, Tuple t);					// multiplicação por escalar

	
	// -----------------------------------
	// Ponto
	// -----------------------------------

	class Point : public Tuple
	{
	public:
		Point(float px, float py, float pz);			// construtor
		Point(Tuple&& t);								// conversão de tupla para ponto
	};


	// -----------------------------------
	// Vetor
	// -----------------------------------

	class Vector : public Tuple
	{
	public:
		Vector(float px, float py, float pz);			// construtor
		Vector(Tuple&& t);								// conversão de tupla para vetor

		float Magnitude();								// comprimento do vetor
		Vector Normalized();							// vetor normalizado
		float Dot(Vector v);							// produto escalar entre vetores
		Vector Cross(Vector v);							// produto vetorial entre vetores
	};

}

#endif
