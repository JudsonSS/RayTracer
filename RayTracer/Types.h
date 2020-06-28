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

		Tuple(float px, float py, float pz, float pw);
		bool operator==(const Tuple t);
	};

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
