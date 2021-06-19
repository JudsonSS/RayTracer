/**********************************************************************************
// Types (Arquivo de Cabeçalho)
//
// Criação:		27 Jun 2020
// Atualização:	17 Jun 2021
// Compilador:	Clang++ 12.0.5 / GNU g++ 9.3.0
//
// Descrição:	Define os tipos básicos necessários para a construção de um 
//              traçador de raios: tuplas, pontos, vetores, cores, etc.
//
**********************************************************************************/

#ifndef RAY_TRACER_TYPES
#define RAY_TRACER_TYPES

#include <string>
#include <initializer_list>
using std::string;
using std::initializer_list;

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

		Tuple(float px, float py, float pz, float pw); 	// construtor
		bool operator==(const Tuple t);				   	// comparação de igualdade
		Tuple operator+(const Tuple t);				   	// soma
		Tuple operator-(const Tuple t);				   	// subtração
		Tuple operator-();							   	// menos unário
		Tuple operator*(float v);					   	// multiplicação por escalar
		Tuple operator/(float v);					   	// divisão por escalar
	};

	bool Equal(float a, float b);	   					// comparação de pontos-flutuantes
	Tuple operator*(float v, Tuple t); 					// multiplicação por escalar

	// -----------------------------------
	// Ponto
	// -----------------------------------

	class Point : public Tuple
	{
	public:
		Point(float px, float py, float pz); 			// construtor
		Point(Tuple &&t);					 			// conversão de tupla para ponto
	};

	// -----------------------------------
	// Vetor
	// -----------------------------------

	class Vector : public Tuple
	{
	public:
		Vector(float px, float py, float pz); 			// construtor
		Vector(Tuple &&t);					  			// conversão de tupla para vetor

		float Magnitude();								// comprimento do vetor
		Vector Normalized();							// vetor normalizado
		float Dot(Vector v);							// produto escalar entre vetores
		Vector Cross(Vector v); 						// produto vetorial entre vetores
	};

	// -----------------------------------
	// Cor
	// -----------------------------------

	class Color : public Tuple
	{
	public:
		Color();										// construtor padrão
		Color(float red, float green, float blue); 		// construtor
		Color(Tuple &&t);						   		// conversão de tupla para cor
	};

	Color operator*(const Color c1, const Color c2); 	// multiplicação de cores (blend)

	// -----------------------------------
	// Matriz
	// -----------------------------------

	class Matrix
	{
	private:
		unsigned mRows; 								// número de linhas
		unsigned mCols; 								// número de colunas
		unsigned mSize;  								// número de elementos
		float *mData;									// dados da matriz

	public:
		Matrix(unsigned rows, unsigned cols);			// construtor
		~Matrix();										// destrutor

		unsigned Size() const;							// retorna quantidade de elementos da matriz
		void operator=(initializer_list<float> init);	// atribuição de lista de valores
		float &operator()(unsigned i, unsigned j);		// retorna referência a elemento
		float operator()(unsigned i, unsigned j) const;	// retorna cópia do elemento
		bool operator==(Matrix &m) const;				// igualdade de matrizes
		bool operator!=(Matrix &m) const;				// desigualdade de matrizes
	};

	// -----------------------------------
}

#endif
