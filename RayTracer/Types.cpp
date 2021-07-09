/**********************************************************************************
// Types (Arquivo de Código Fonte)
//
// Criação:		27 Jun 2020
// Atualização:	08 Jul 2021
// Compilador:	Clang++ 12.0.5 / GNU g++ 9.3.0
//
// Descrição:	Define os tipos básicos necessários para a construção de um 
//              traçador de raios: tuplas, pontos, vetores, cores, etc.
//
**********************************************************************************/

#include "Types.h"
#include <cmath>

namespace RayTracer
{
	// -------------------------------------------------------------------------------
	// Comparação Ponto-Flutuante
	// -------------------------------------------------------------------------------

	const float Epsilon = 0.0001f;

	bool Equal(float a, float b)
	{
		if (abs(a - b) < Epsilon)
			return true;
		else
			return false;
	}

	// -------------------------------------------------------------------------------
	// Tupla
	// -------------------------------------------------------------------------------

	Tuple::Tuple()
		: x(0.0f), y(0.0f), z(0.0f), w(0.0f) {}

	Tuple::Tuple(float px, float py, float pz, float pw)
		: x(px), y(py), z(pz), w(pw) {}

	bool operator==(const Tuple &a, const Tuple &b)
	{ return Equal(a.x, b.x) && Equal(a.y, b.y) && Equal(a.z, b.z) && Equal(a.w, b.w); }

	Tuple operator+(const Tuple &a, const Tuple &b)
	{ return Tuple(a.x + b.x, a.y + b.y, a.z + b.z, a.w + b.w); }

	Tuple operator-(const Tuple &a, const Tuple &b)
	{ return Tuple(a.x - b.x, a.y - b.y, a.z - b.z, a.w - b.w); }

	Tuple operator-(const Tuple &t)
	{ return Tuple(-t.x, -t.y, -t.z, -t.w); }

	Tuple operator*(const Tuple &t, float v)
	{ return Tuple(t.x * v, t.y * v, t.z * v, t.w * v); }

	Tuple operator/(const Tuple &t, float v)
	{ return Tuple(t.x / v, t.y / v, t.z / v, t.w / v); }

	Tuple operator*(float v, const Tuple &t)
	{ return Tuple(t.x * v, t.y * v, t.z * v, t.w * v); }

	// -------------------------------------------------------------------------------
	// Ponto
	// -------------------------------------------------------------------------------

	Point::Point()
		: Tuple(0.0f, 0.0f, 0.0f, 1.0f) {}

	Point::Point(float px, float py, float pz)
		: Tuple(px, py, pz, 1.0f) {}

	Point::Point(Tuple &&t)
		: Tuple(t.x, t.y, t.z, 1.0f) {}

	// -------------------------------------------------------------------------------
	// Vetor
	// -------------------------------------------------------------------------------

	Vector::Vector()
		: Tuple(0.0f, 0.0f, 0.0f, 0.0f) {}

	Vector::Vector(float px, float py, float pz)
		: Tuple(px, py, pz, 0.0f) {}

	Vector::Vector(Tuple &&t)
		: Tuple(t.x, t.y, t.z, 0.0f) {}

	float Vector::Magnitude()
	{ return sqrt(x * x + y * y + z * z + w * w); }

	Vector Vector::Normalized()
	{
		float mag = Magnitude();
		return Vector(x / mag, y / mag, z / mag);
	}

	float Vector::Dot(Vector v)
	{ return x * v.x + y * v.y + z * v.z; }

	Vector Vector::Cross(Vector v)
	{ return Vector(y * v.z - z * v.y, z * v.x - x * v.z, x * v.y - y * v.x); }

	Vector Vector::Reflect(Vector normal)
	{ return (*this) - normal * 2 * this->Dot(normal); }

	// -------------------------------------------------------------------------------
	// Cor
	// -------------------------------------------------------------------------------

	Color::Color()
		: Tuple(0.0f, 0.0f, 0.0f, 0.0f) {}

	Color::Color(float r, float g, float b)
		: Tuple(r, g, b, 0.0f) {}

	Color::Color(Tuple &&t)
		: Tuple(t.x, t.y, t.z, 0.0f) {}

	Color operator*(const Color &c1, const Color &c2)
	{ return Color(c1.x * c2.x, c1.y * c2.y, c1.z * c2.z); }

	// -------------------------------------------------------------------------------
}