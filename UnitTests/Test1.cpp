#include "../RayTracer/Types.h"
#include <gtest/gtest.h>
#include <cmath>

using namespace RayTracer;

namespace Test1
{
	TEST(Tuples, TupleOne)
	{
		Tuple t{4.3f, -4.2f, 3.1f, 1.0f};

		EXPECT_EQ(t.x, 4.3f);
		EXPECT_EQ(t.y, -4.2f);
		EXPECT_EQ(t.z, 3.1f);
		EXPECT_EQ(t.w, 1.0f);
	}

	TEST(Tuples, TupleZero)
	{
		Tuple t{4.3f, -4.2f, 3.1f, 0.0f};

		EXPECT_EQ(t.x, 4.3f);
		EXPECT_EQ(t.y, -4.2f);
		EXPECT_EQ(t.z, 3.1f);
		EXPECT_EQ(t.w, 0.0f);
	}

	TEST(Tuples, PointOne)
	{
		Tuple t{4.3f, -4.2f, 3.1f, 1.0f};
		Point p{4.3f, -4.2f, 3.1f};

		EXPECT_EQ(t.x, p.x);
		EXPECT_EQ(t.y, p.y);
		EXPECT_EQ(t.z, p.z);
		EXPECT_EQ(t.w, p.w);
	}

	TEST(Tuples, VectorZero)
	{
		Tuple t{4.3f, -4.2f, 3.1f, 0.0f};
		Vector v{4.3f, -4.2f, 3.1f};

		EXPECT_EQ(t.x, v.x);
		EXPECT_EQ(t.y, v.y);
		EXPECT_EQ(t.z, v.z);
		EXPECT_EQ(t.w, v.w);
	}

	TEST(Tuples, TupleEquality)
	{
		Tuple ta{4.3f, -4.2f, 3.1f, 1.0f};
		Tuple tb{4.3f, -4.2f, 3.1f, 0.0f};
		Tuple tc{4.3f, -4.2f, 3.1f, 1.0f};
		Tuple td{2.0f, 1.0f, -4.5f, 1.0f};

		EXPECT_FALSE(ta == tb);
		EXPECT_FALSE(ta == td);
		EXPECT_FALSE(tb == td);
		EXPECT_TRUE(ta == tc);
	}

	TEST(Tuples, TupleIsPoint)
	{
		Tuple t{4.3f, -4.2f, 3.1f, 1.0f};
		Point p{4.3f, -4.2f, 3.1f};
		Vector v{4.3f, -4.2f, 3.1f};

		EXPECT_TRUE(t == p);
		EXPECT_FALSE(t == v);
	}

	TEST(Tuples, TupleIsVector)
	{
		Tuple t{4.3f, -4.2f, 3.1f, 0.0f};
		Point p{4.3f, -4.2f, 3.1f};
		Vector v{4.3f, -4.2f, 3.1f};

		EXPECT_FALSE(t == p);
		EXPECT_TRUE(t == v);
	}

	TEST(Tuples, TupleAdd)
	{
		Tuple t1{3.0f, -2.0f, 5.0f, 1.0f};
		Tuple t2{-2.0f, 3.0f, 1.0f, 0.0f};
		Tuple t{1.0f, 1.0f, 6.0f, 1.0f};
		Tuple add = t1 + t2;

		EXPECT_TRUE(t == add);
	}

	TEST(Tuples, PointSubtract)
	{
		Point p1{3.0f, 2.0f, 1.0f};
		Point p2{5.0f, 6.0f, 7.0f};
		Vector v{-2.0f, -4.0f, -6.0f};

		EXPECT_TRUE(v == p1 - p2);
	}

	TEST(Tuples, PointVectorSubtract)
	{
		Point p{3.0f, 2.0f, 1.0f};
		Vector v{5.0f, 6.0f, 7.0f};
		Point q{-2.0f, -4.0f, -6.0f};

		EXPECT_TRUE(q == p - v);
	}

	TEST(Tuples, VectorVectorSubtract)
	{
		Vector v1{3.0f, 2.0f, 1.0f};
		Vector v2{5.0f, 6.0f, 7.0f};
		Vector r{-2.0f, -4.0f, -6.0f};

		EXPECT_TRUE(r == v1 - v2);
	}

	TEST(Tuples, TupleNegation)
	{
		Tuple t{1.0f, -2.0f, 3.0f, -4.0f};
		Tuple n{-1.0f, 2.0f, -3.0f, 4.0f};

		Vector v{5.0f, 6.0f, 7.0f};
		Vector i{-5.0f, -6.0f, -7.0f};

		EXPECT_TRUE(-t == n);
		EXPECT_TRUE(-v == i);
	}

	TEST(Tuples, ScalarMultiplication)
	{
		Tuple t{1.0f, -2.0f, 3.0f, -4.0f};
		Tuple m{3.5f, -7.0f, 10.5f, -14.0f};

		EXPECT_TRUE(t * 3.5 == m);
		EXPECT_TRUE(3.5 * t == m);
	}

	TEST(Tuples, ScalarDivision)
	{
		Tuple t{1.0f, -2.0f, 3.0f, -4.0f};
		Tuple d{0.5f, -1.0f, 1.5f, -2.0f};

		EXPECT_TRUE(t / 2.0f == d);
	}

	TEST(Vectors, Magnitude)
	{
		Vector v1{1.0f, 0.0f, 0.0f};
		Vector v2{0.0f, 1.0f, 0.0f};
		Vector v3{0.0f, 0.0f, 1.0f};

		Vector v4{1.0f, 2.0f, 3.0f};
		Vector v5{-1.0f, -2.0f, -3.0f};

		EXPECT_TRUE(Equal(v1.Magnitude(), 1.0f));
		EXPECT_TRUE(Equal(v2.Magnitude(), 1.0f));
		EXPECT_TRUE(Equal(v3.Magnitude(), 1.0f));
		EXPECT_TRUE(Equal(v4.Magnitude(), sqrt(14.0f)));
		EXPECT_TRUE(Equal(v5.Magnitude(), sqrt(14.0f)));
	}

	TEST(Vectors, Normalization)
	{
		Vector v1{4.0f, 0.0f, 0.0f};
		Vector v2{1.0f, 2.0f, 3.0f};

		EXPECT_TRUE(v1.Normalized() == Vector(1.0f, 0.0f, 0.0f));
		EXPECT_TRUE(v2.Normalized() == Vector(1.0f / sqrt(14.0f), 2.0f / sqrt(14.0f), 3.0f / sqrt(14.0f)));
		EXPECT_TRUE(Equal(v1.Normalized().Magnitude(), 1.0f));
		EXPECT_TRUE(Equal(v2.Normalized().Magnitude(), 1.0f));
	}

	TEST(Vectors, DotProduct)
	{
		Vector v1{1.0f, 2.0f, 3.0f};
		Vector v2{2.0f, 3.0f, 4.0f};

		EXPECT_TRUE(Equal(v1.Dot(v2), 20.0f));
	}

	TEST(Vectors, CrossProduct)
	{
		Vector v1{1.0f, 2.0f, 3.0f};
		Vector v2{2.0f, 3.0f, 4.0f};

		EXPECT_TRUE(v1.Cross(v2) == Vector(-1.0f, 2.0f, -1.0f));
		EXPECT_TRUE(v2.Cross(v1) == Vector(1.0f, -2.0f, 1.0f));
	}
}

int main(int argc, char **argv) 
{
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
