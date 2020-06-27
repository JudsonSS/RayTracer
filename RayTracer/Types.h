#ifndef RAY_TRACER_TYPES
#define RAY_TRACER_TYPES

namespace RayTracer
{
	struct Tuple
	{
		float x;
		float y;
		float z;
		float w;
	};

	class Point : public Tuple
	{
	public:
		Point(float px, float py, float pz)
		{
			x = px;
			y = py;
			z = pz;
			w = 1.0f;
		}
	};

	class Vector : public Tuple
	{
	public:
		Vector(float px, float py, float pz)
		{
			x = px;
			y = py;
			z = pz;
			w = 0.0f;
		}
	};

}

#endif
