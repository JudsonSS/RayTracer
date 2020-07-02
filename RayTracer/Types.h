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
		bool operator==(const Tuple t);					// compara��o de igualdade
		Tuple operator+(const Tuple t);					// soma
		Tuple operator-(const Tuple t);					// subtra��o
		Tuple operator-();								// menos un�rio
		Tuple operator*(float v);						// multiplica��o por escalar
		Tuple operator/(float v);						// divis�o por escalar
	};

	bool Equal(float a, float b);						// compara��o de pontos-flutuantes
	Tuple operator*(float v, Tuple t);					// multiplica��o por escalar

	
	// -----------------------------------
	// Ponto
	// -----------------------------------

	class Point : public Tuple
	{
	public:
		Point(float px, float py, float pz);			// construtor
		Point(Tuple&& t);								// convers�o de tupla para ponto
	};


	// -----------------------------------
	// Vetor
	// -----------------------------------

	class Vector : public Tuple
	{
	public:
		Vector(float px, float py, float pz);			// construtor
		Vector(Tuple&& t);								// convers�o de tupla para vetor

		float Magnitude();								// comprimento do vetor
		Vector Normalized();							// vetor normalizado
		float Dot(Vector v);							// produto escalar entre vetores
		Vector Cross(Vector v);							// produto vetorial entre vetores
	};

}

#endif
