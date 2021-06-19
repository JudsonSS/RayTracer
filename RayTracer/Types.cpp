/**********************************************************************************
// Types (Arquivo de Código Fonte)
//
// Criação:		27 Jun 2020
// Atualização:	17 Jun 2021
// Compilador:	Clang++ 12.0.5 / GNU g++ 9.3.0
//
// Descrição:	Define os tipos básicos necessários para a construção de um 
//              traçador de raios: tuplas, pontos, vetores, cores, etc.
//
**********************************************************************************/

#include "Types.h"
#include <cmath>

using namespace RayTracer;

// ------------------------------------------------
// Comparação Ponto-Flutuante
// ------------------------------------------------

const float Epsilon = 0.00001f;

bool RayTracer::Equal(float a, float b)
{
	if (abs(a - b) < Epsilon)
		return true;
	else
		return false;
}

// ------------------------------------------------
// Tupla
// ------------------------------------------------

RayTracer::Tuple::Tuple(float px, float py, float pz, float pw) 
	: x(px), y(py), z(pz), w(pw) {}

bool RayTracer::Tuple::operator==(const Tuple t) 
{ return Equal(x, t.x) && Equal(y, t.y) && Equal(z, t.z) && Equal(w, t.w); }

Tuple RayTracer::Tuple::operator+(const Tuple t)
{ return Tuple(x + t.x, y + t.y, z + t.z, w + t.w); }

Tuple RayTracer::Tuple::operator-(const Tuple t)
{ return Tuple(x - t.x, y - t.y, z - t.z, w - t.w); }

Tuple RayTracer::Tuple::operator-()
{ return Tuple(-x, -y, -z, -w); }

Tuple RayTracer::Tuple::operator*(float v)
{ return Tuple(x * v, y * v, z * v, w * v); }

Tuple RayTracer::Tuple::operator/(float v)
{ return Tuple(x / v, y / v, z / v, w / v); }

Tuple RayTracer::operator*(float v, Tuple t)
{ return Tuple(t.x * v, t.y * v, t.z * v, t.w * v); }


// ------------------------------------------------
// Ponto
// ------------------------------------------------

RayTracer::Point::Point(float px, float py, float pz) 
	: Tuple(px, py, pz, 1.0f) {}

RayTracer::Point::Point(Tuple&& t) 
	: Tuple(t.x, t.y, t.z, 1.0f) {}

// ------------------------------------------------
// Vetor
// ------------------------------------------------

RayTracer::Vector::Vector(float px, float py, float pz) 
	: Tuple(px, py, pz, 0.0f) {}

RayTracer::Vector::Vector(Tuple&& t) 
	: Tuple(t.x, t.y, t.z, 0.0f) {}

float RayTracer::Vector::Magnitude()
{ return sqrt(x*x + y*y + z*z + w*w); }

Vector RayTracer::Vector::Normalized()
{ float mag = Magnitude(); return Vector(x / mag, y / mag, z / mag); }

float RayTracer::Vector::Dot(Vector v) 
{ return x * v.x + y * v.y + z * v.z; }

Vector RayTracer::Vector::Cross(Vector v) 
{	return Vector(y * v.z - z * v.y, z * v.x - x * v.z, x * v.y - y * v.x); }

// ------------------------------------------------
// Cor
// ------------------------------------------------

RayTracer::Color::Color() 
	: Tuple(0.0f, 0.0f, 0.0f, 0.0f) {}

RayTracer::Color::Color(float r, float g, float b) 
	: Tuple(r,g, b, 0.0f) {}

RayTracer::Color::Color(Tuple&& t) 
	: Tuple(t.x, t.y, t.z, 0.0f) {}

Color RayTracer::operator*(const Color c1, const Color c2)
{ return Color(c1.x * c2.x, c1.y * c2.y, c1.z * c2.z); }

// ------------------------------------------------
// Matriz
// ------------------------------------------------

RayTracer::Matrix::Matrix(unsigned rows, unsigned cols)
	: mRows(rows),
	  mCols(cols),
	  mSize(rows*cols),
	  mData(new float[mSize]{0})
{
}

RayTracer::Matrix::~Matrix()
{
	delete [] mData;
}

unsigned RayTracer::Matrix::Size() const
{ return mSize; }

void RayTracer::Matrix::operator=(std::initializer_list<float> init) 
{
	initializer_list<float>::iterator it;
	unsigned i;
	for (i=0, it = init.begin(); it != init.end() && i < mSize; ++it)
		mData[i++] = *it;
}

float & RayTracer::Matrix::operator()(unsigned i, unsigned j)
{
	return mData[i * mCols + j];
}

float RayTracer::Matrix::operator()(unsigned i, unsigned j) const
{
	return mData[i * mCols + j];
}

bool RayTracer::Matrix::operator==(Matrix &m) const
{
	// se tem tamanhos diferentes
	if (mSize != m.Size())
		return false;

	// compara os elementos usando a função 
	// de comparação de pontos-flutuantes
	for (int i = 0; i < mRows; ++i)
		for (int j = 0; j < mCols; ++j)
			if (!Equal((*this)(i,j), m(i,j)))
				return false;

	return true;
}

bool RayTracer::Matrix::operator!=(Matrix &m) const
{ return !operator==(m); }

// -----------------------------------