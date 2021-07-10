/**********************************************************************************
// Test1 (Arquivo de Código Fonte)
//
// Criação:		27 Jun 2020
// Atualização:	10 Jul 2021
// Compilador:	Clang++ 12.0.5 / GNU g++ 9.3.0
//
// Descrição:	Define os testes de unidade criados no Capítulo 1, Tuplas,
//              Pontos e Vetores, do livro "The Ray Tracer Challenge". 
//              Os testes utilizam o framework GoogleTest.
//
**********************************************************************************/

#include <gtest/gtest.h>
#include <cmath>
#include "Types.h"

using namespace RayTracer;

namespace Chapter1
{
	TEST(Tuples, TupleEmpty)
	{
		Tuple t;

		EXPECT_EQ(t.x, 0.0);
		EXPECT_EQ(t.y, 0.0);
		EXPECT_EQ(t.z, 0.0);
		EXPECT_EQ(t.w, 0.0);
	}

	TEST(Tuples, TupleOne)
	{
		Tuple t{4.3, -4.2, 3.1, 1.0};

		EXPECT_EQ(t.x, 4.3);
		EXPECT_EQ(t.y, -4.2);
		EXPECT_EQ(t.z, 3.1);
		EXPECT_EQ(t.w, 1.0);
	}

	TEST(Tuples, TupleZero)
	{
		Tuple t{4.3, -4.2, 3.1, 0.0};

		EXPECT_EQ(t.x, 4.3);
		EXPECT_EQ(t.y, -4.2);
		EXPECT_EQ(t.z, 3.1);
		EXPECT_EQ(t.w, 0.0);
	}

	TEST(Tuples, PointOne)
	{
		Tuple t{4.3, -4.2, 3.1, 1.0};
		Point p{4.3, -4.2, 3.1};

		EXPECT_EQ(t.x, p.x);
		EXPECT_EQ(t.y, p.y);
		EXPECT_EQ(t.z, p.z);
		EXPECT_EQ(t.w, p.w);
	}

	TEST(Tuples, VectorZero)
	{
		Tuple t{4.3, -4.2, 3.1, 0.0};
		Vector v{4.3, -4.2, 3.1};

		EXPECT_EQ(t.x, v.x);
		EXPECT_EQ(t.y, v.y);
		EXPECT_EQ(t.z, v.z);
		EXPECT_EQ(t.w, v.w);
	}

	TEST(Tuples, TupleEquality)
	{
		Tuple ta{4.3, -4.2, 3.1, 1.0};
		Tuple tb{4.3, -4.2, 3.1, 0.0};
		Tuple tc{4.3, -4.2, 3.1, 1.0};
		Tuple td{2.0, 1.0, -4.5, 1.0};

		EXPECT_FALSE(ta == tb);
		EXPECT_FALSE(ta == td);
		EXPECT_FALSE(tb == td);
		EXPECT_TRUE(ta == tc);
	}

	TEST(Tuples, TupleIsPoint)
	{
		Tuple t{4.3, -4.2, 3.1, 1.0};
		Point p{4.3, -4.2, 3.1};
		Vector v{4.3, -4.2, 3.1};

		EXPECT_TRUE(t == p);
		EXPECT_FALSE(t == v);
	}

	TEST(Tuples, TupleIsVector)
	{
		Tuple t{4.3, -4.2, 3.1, 0.0};
		Point p{4.3, -4.2, 3.1};
		Vector v{4.3, -4.2, 3.1};

		EXPECT_FALSE(t == p);
		EXPECT_TRUE(t == v);
	}

	TEST(Tuples, TupleAdd)
	{
		Tuple t1{3.0, -2.0, 5.0, 1.0};
		Tuple t2{-2.0, 3.0, 1.0, 0.0};
		Tuple t{1.0, 1.0, 6.0, 1.0};
		Tuple add = t1 + t2;

		EXPECT_TRUE(t == add);
	}

	TEST(Tuples, PointSubtract)
	{
		Point p1{3.0, 2.0, 1.0};
		Point p2{5.0, 6.0, 7.0};
		Vector v{-2.0, -4.0, -6.0};

		EXPECT_TRUE(v == p1 - p2);
	}

	TEST(Tuples, PointVectorSubtract)
	{
		Point p{3.0, 2.0, 1.0};
		Vector v{5.0, 6.0, 7.0};
		Point q{-2.0, -4.0, -6.0};

		EXPECT_TRUE(q == p - v);
	}

	TEST(Tuples, VectorVectorSubtract)
	{
		Vector v1{3.0, 2.0, 1.0};
		Vector v2{5.0, 6.0, 7.0};
		Vector r{-2.0, -4.0, -6.0};

		EXPECT_TRUE(r == v1 - v2);
	}

	TEST(Tuples, TupleNegation)
	{
		Tuple t{1.0, -2.0, 3.0, -4.0};
		Tuple n{-1.0, 2.0, -3.0, 4.0};

		Vector v{5.0, 6.0, 7.0};
		Vector i{-5.0, -6.0, -7.0};

		EXPECT_TRUE(-t == n);
		EXPECT_TRUE(-v == i);
	}

	TEST(Tuples, ScalarMultiplication)
	{
		Tuple t{1.0, -2.0, 3.0, -4.0};
		Tuple m{3.5, -7.0, 10.5, -14.0};

		EXPECT_TRUE(t * 3.5 == m);
		EXPECT_TRUE(3.5 * t == m);
	}

	TEST(Tuples, ScalarDivision)
	{
		Tuple t{1.0, -2.0, 3.0, -4.0};
		Tuple d{0.5, -1.0, 1.5, -2.0};

		EXPECT_TRUE(t / 2.0 == d);
	}

	TEST(Vectors, Magnitude)
	{
		Vector v1{1.0, 0.0, 0.0};
		Vector v2{0.0, 1.0, 0.0};
		Vector v3{0.0, 0.0, 1.0};

		Vector v4{1.0, 2.0, 3.0};
		Vector v5{-1.0, -2.0, -3.0};

		EXPECT_TRUE(Equal(v1.Magnitude(), 1.0));
		EXPECT_TRUE(Equal(v2.Magnitude(), 1.0));
		EXPECT_TRUE(Equal(v3.Magnitude(), 1.0));
		EXPECT_TRUE(Equal(v4.Magnitude(), sqrt(14.0)));
		EXPECT_TRUE(Equal(v5.Magnitude(), sqrt(14.0)));
	}

	TEST(Vectors, Normalization)
	{
		Vector v1{4.0, 0.0, 0.0};
		Vector v2{1.0, 2.0, 3.0};

		EXPECT_TRUE(v1.Normalized() == Vector(1.0, 0.0, 0.0));
		EXPECT_TRUE(v2.Normalized() == Vector(1.0 / sqrt(14.0), 2.0 / sqrt(14.0), 3.0 / sqrt(14.0)));
		EXPECT_TRUE(Equal(v1.Normalized().Magnitude(), 1.0));
		EXPECT_TRUE(Equal(v2.Normalized().Magnitude(), 1.0));
	}

	TEST(Vectors, DotProduct)
	{
		Vector v1{1.0, 2.0, 3.0};
		Vector v2{2.0, 3.0, 4.0};

		EXPECT_TRUE(Equal(v1.Dot(v2), 20.0));
	}

	TEST(Vectors, CrossProduct)
	{
		Vector v1{1.0, 2.0, 3.0};
		Vector v2{2.0, 3.0, 4.0};

		EXPECT_TRUE(v1.Cross(v2) == Vector(-1.0, 2.0, -1.0));
		EXPECT_TRUE(v2.Cross(v1) == Vector(1.0, -2.0, 1.0));
	}
}

int main(int argc, char **argv) 
{
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
