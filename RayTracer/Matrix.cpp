/**********************************************************************************
// Matrix (Arquivo de Código Fonte)
//
// Criação:		19 Jun 2020
// Atualização:	19 Jun 2021
// Compilador:	Clang++ 12.0.5 / GNU g++ 9.3.0
//
// Descrição:	Define uma classe para uma matriz dinâmica com as operações
//              necessárias para criação do traçador de raios.
//
**********************************************************************************/

#include "Matrix.h"
using namespace RayTracer;

// ----------------------------------------------

// membros estáticos da classe
Matrix Matrix::Identity { 4, 4, 
  { 1,0,0,0,
    0,1,0,0,
    0,0,1,0,
    0,0,0,1 } 
};

// ----------------------------------------------

RayTracer::Matrix::Matrix()
	: mRows(0),
	  mCols(0),
	  mSize(0),
	  mData(nullptr) { }

RayTracer::Matrix::Matrix(unsigned rows, unsigned cols)
	: mRows(rows),
	  mCols(cols),
	  mSize(rows*cols),
	  mData(new float[mSize]{0}) { }

RayTracer::Matrix::Matrix(unsigned rows, unsigned cols, initializer_list<float> init)
	: mRows(rows),
	  mCols(cols),
	  mSize(rows*cols),
	  mData(new float[mSize]{0})	
{
	initializer_list<float>::iterator it;
	unsigned i;
	for (i=0, it = init.begin(); it != init.end() && i < mSize; ++it)
		mData[i++] = *it;
}

RayTracer::Matrix::Matrix(Matrix &mat)
	: mRows(mat.mRows),
	  mCols(mat.mCols),
	  mSize(mat.mSize),
	  mData(new float[mSize])
{
	for (int i = 0; i < mat.mSize; ++i)
		mData[i] = mat.mData[i];
}

RayTracer::Matrix::Matrix(Matrix &&mat)
	: mRows(mat.mRows),
	  mCols(mat.mCols),
	  mSize(mat.mSize),
	  mData(mat.mData)
{ 
	mat.mData = nullptr;
}

RayTracer::Matrix::~Matrix()
{ delete [] mData; }

// ----------------------------------------------

Matrix& RayTracer::Matrix::operator=(Matrix& mat)
{
	mRows = mat.mRows;
	mCols = mat.mCols;
	mSize = mat.mSize;

	delete [] mData;
	mData = new float[mSize];

	for (int i = 0; i < mSize; ++i)
		mData[i] = mat.mData[i];
	
	return *this;
}

Matrix& RayTracer::Matrix::operator=(Matrix&& mat)
{
	mRows = mat.mRows;
	mCols = mat.mCols;
	mSize = mat.mSize;
	delete [] mData;
	mData = mat.mData;
	mat.mData = nullptr;
	return *this;
}

Matrix& RayTracer::Matrix::operator=(std::initializer_list<float> init) 
{
	initializer_list<float>::iterator it;
	unsigned i;
	for (i=0, it = init.begin(); it != init.end() && i < mSize; ++it)
		mData[i++] = *it;
	return *this;
}

// ----------------------------------------------

float & RayTracer::Matrix::operator()(unsigned i, unsigned j)
{
	return mData[i * mCols + j];
}

float RayTracer::Matrix::operator()(unsigned i, unsigned j) const
{
	return mData[i * mCols + j];
}

// ----------------------------------------------

bool RayTracer::operator==(const Matrix &m1, const Matrix &m2)
{
	// se tem tamanhos diferentes
	if (m1.mSize != m2.mSize)
		return false;

	// compara os elementos usando a função 
	// de comparação de pontos-flutuantes
	for (int i = 0; i < m1.mSize; ++i)
		if (!Equal(m1.mData[i], m2.mData[i]))
			return false;

	return true;
}

bool RayTracer::operator!=(const Matrix &m1, const Matrix &m2)
{ 
	return !(m1 == m2); 
}

// ----------------------------------------------

Matrix RayTracer::operator*(const Matrix &m1, const Matrix &m2)
{
	assert(m1.mCols == m2.mRows);
    Matrix M{m1.mRows,m2.mCols};

	for (int row = 0; row < m1.mRows; ++row)
		for (int col = 0; col < m2.mCols; ++col)
			for (int i = 0; i < m1.mCols; ++i)
				M(row,col) += m1(row,i) * m2(i,col);

    return M;
}

Tuple RayTracer::operator*(const Matrix &m, const Tuple t)
{
	assert(m.mRows == 4);
	assert(m.mCols == 4);
    Tuple r;

	r.x = m(0,0) * t.x + m(0,1) * t.y + m(0,2) * t.z + m(0,3) * t.w;
	r.y = m(1,0) * t.x + m(1,1) * t.y + m(1,2) * t.z + m(1,3) * t.w;
	r.z = m(2,0) * t.x + m(2,1) * t.y + m(2,2) * t.z + m(2,3) * t.w;
	r.w = m(3,0) * t.x + m(3,1) * t.y + m(3,2) * t.z + m(3,3) * t.w;
	
	return r;
}

// ----------------------------------------------

Matrix RayTracer::Matrix::Transpose() const
{
	Matrix T {mRows, mCols};
	for (int i = 0; i < mRows; ++i)
		for (int j = 0; j < mCols; ++j)
			T(j,i) = mData[i * mCols + j];
	return T;
}

float RayTracer::Matrix::Determinant() const
{
	// só existe determinante para matrizes quadradas
	assert(mRows == mCols);

	float det = 0;

	if (mRows == 2)
	{
		// determinante de matrizes 2x2 é dado por
		// (M[0,0] * M[1,1]) - (M[0,1] * M[1,0])
		det = mData[0] * mData[3] - mData[1] * mData[2];
	}
	else
	{
		// determinante de matrizes maiores depende
		// de cofatores, que dependem de minor, que 
		// dependem do determinte de submatrizes
		for (unsigned col = 0; col < mCols; ++col)
		{
			// det = det + M[0,col] * cofactor(M, 0, col)
			det += mData[col] * Cofactor(0, col);
		}
	}

	return det;
}

Matrix RayTracer::Matrix::Submatrix(unsigned row, unsigned col) const
{
	// linha e coluna precisa existir na matrix
	assert(row < mRows);
	assert(col < mCols);

	// ao remover linha e coluna, a matrix fica 
	// dividida em 4 quadrantes que precisam ser 
	// copiados para a submatrix resultante
	// 
	// Q1 | Q2
	// -------
	// Q3 | Q4

	Matrix S {mRows-1, mCols-1};
	
	// cópia do quadrante 1 
	for (unsigned i = 0; i < row; ++i)
		for (unsigned j = 0; j < col; ++j)
				S(i,j) = mData[i * mCols + j];

	// cópia do quadrante 2
	for (unsigned i = 0; i < row; ++i)
		for (unsigned j = col+1; j < mCols; ++j)
				S(i,j-1) = mData[i * mCols + j];

	// cópia do quadrante 3
	for (unsigned i = row+1; i < mRows; ++i)
		for (unsigned j = 0; j < col; ++j)
				S(i-1,j) = mData[i * mCols + j];

	// cópia do quadrante 4
	for (unsigned i = row+1; i < mRows; ++i)
		for (unsigned j = col+1; j < mCols; ++j)
				S(i-1,j-1) = mData[i * mCols + j];

	return S;
}

float RayTracer::Matrix::Minor(unsigned row, unsigned col) const
{
	return Submatrix(row,col).Determinant();
}

float RayTracer::Matrix::Cofactor(unsigned row, unsigned col) const
{
	float minor = Minor(row, col);
	// se linha + coluna é um número ímpar retorna -minor
	return ((row+col) % 2 == 0) ? minor : -minor; 
}

bool RayTracer::Matrix::Invertible() const
{
	return (Determinant() == 0) ? false : true;  
}

Matrix RayTracer::Matrix::Inverse() const
{
	assert(Invertible());
	float det = Determinant();

	Matrix M {mRows, mCols};

	for (unsigned row = 0; row < mRows; ++row)
		for (unsigned col = 0; col < mCols; ++col)
			// usar [col,row] em vez de [row,col] faz a transposição da matriz  
			M(col,row) = Cofactor(row,col) / det;

	return M;
}