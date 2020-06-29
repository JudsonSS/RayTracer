#ifndef RAY_TRACER_TYPES
#define RAY_TRACER_TYPES

namespace RayTracer
{
	// Tupla
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

	Tuple operator*(float v, Tuple t);					// multiplica��o por escalar

	// Ponto
	class Point : public Tuple
	{
	public:
		Point(float px, float py, float pz);
	};

	// Vetor
	class Vector : public Tuple
	{
	public:
		Vector(float px, float py, float pz);
	};

}

#endif
