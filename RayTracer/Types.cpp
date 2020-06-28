#include "Types.h"
#include <cmath>

using namespace RayTracer;

// ------------------------------------------------
// Comparação Ponto-Flutuante
// ------------------------------------------------

const float Epsilon = 0.00001f;

bool Equal(float a, float b)
{
	if (abs(a - b) < Epsilon)
		return true;
	else
		return false;
}

// ------------------------------------------------
// Tupla
// ------------------------------------------------

RayTracer::Tuple::Tuple(float px, float py, float pz, float pw) : x(px), y(py), z(pz), w(pw)
{
}

bool RayTracer::Tuple::operator==(const Tuple t) 
{
	return Equal(x, t.x) && Equal(y, t.y) && Equal(z, t.z) && Equal(w, t.w);
}

Tuple RayTracer::Tuple::operator+(const Tuple t)
{
	return Tuple(x + t.x, y + t.y, z + t.z, w + t.w);
}

Tuple RayTracer::Tuple::operator-(const Tuple t)
{
	return Tuple(x - t.x, y - t.y, z - t.z, w - t.w);
}

// ------------------------------------------------
// Ponto
// ------------------------------------------------

RayTracer::Point::Point(float px, float py, float pz) : Tuple(px, py, pz, 1.0f)
{
}

// ------------------------------------------------
// Vetor
// ------------------------------------------------

RayTracer::Vector::Vector(float px, float py, float pz) : Tuple(px, py, pz, 0.0f)
{
}