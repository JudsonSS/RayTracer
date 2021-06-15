#include "pch.h"
#include "CppUnitTest.h"
#include "../RayTracer/Types.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace RayTracer;

namespace UnitTest
{
	TEST_CLASS(Construction)
	{
	public:

		TEST_METHOD(TupleOne)
		{
			Tuple t { 4.3f, -4.2f, 3.1f, 1.0f };

			Assert::AreEqual(t.x, 4.3f);
			Assert::AreEqual(t.y, -4.2f);
			Assert::AreEqual(t.z, 3.1f);
			Assert::AreEqual(t.w, 1.0f);
		}

		TEST_METHOD(TupleZero)
		{
			Tuple t { 4.3f, -4.2f, 3.1f, 0.0f };

			Assert::AreEqual(t.x, 4.3f);
			Assert::AreEqual(t.y, -4.2f);
			Assert::AreEqual(t.z, 3.1f);
			Assert::AreEqual(t.w, 0.0f);
		}

		TEST_METHOD(PointOne)
		{
			Tuple t { 4.3f, -4.2f, 3.1f, 1.0f };
			Point p { 4.3f, -4.2f, 3.1f };

			Assert::AreEqual(t.x, p.x);
			Assert::AreEqual(t.y, p.y);
			Assert::AreEqual(t.z, p.z);
			Assert::AreEqual(t.w, p.w);
		}

		TEST_METHOD(VectorZero)
		{
			Tuple t { 4.3f, -4.2f, 3.1f, 0.0f };
			Vector v { 4.3f, -4.2f, 3.1f };

			Assert::AreEqual(t.x, v.x);
			Assert::AreEqual(t.y, v.y);
			Assert::AreEqual(t.z, v.z);
			Assert::AreEqual(t.w, v.w);
		}

		TEST_METHOD(TupleEquality)
		{
			Tuple ta{ 4.3f, -4.2f, 3.1f, 1.0f };
			Tuple tb{ 4.3f, -4.2f, 3.1f, 0.0f };
			Tuple tc{ 4.3f, -4.2f, 3.1f, 1.0f };
			Tuple td{ 2.0f, 1.0f, -4.5f, 1.0f };

			Assert::IsFalse(ta == tb);
			Assert::IsFalse(ta == td);
			Assert::IsFalse(tb == td);
			Assert::IsTrue(ta == tc);
		}

		TEST_METHOD(TupleIsPoint)
		{
			Tuple t{ 4.3f, -4.2f, 3.1f, 1.0f };
			Point p{ 4.3f, -4.2f, 3.1f };
			Vector v{ 4.3f, -4.2f, 3.1f };

			Assert::IsTrue(t == p);
			Assert::IsFalse(t == v);
		}

		TEST_METHOD(TupleIsVector)
		{
			Tuple t{ 4.3f, -4.2f, 3.1f, 0.0f };
			Point p{ 4.3f, -4.2f, 3.1f };
			Vector v{ 4.3f, -4.2f, 3.1f };

			Assert::IsFalse(t == p);
			Assert::IsTrue(t == v);
		}
	};

	TEST_CLASS(Arithmetic)
	{
	public:
		TEST_METHOD(TupleAdd)
		{
			Tuple t1{ 3.0f, -2.0f, 5.0f, 1.0f };
			Tuple t2{ -2.0f, 3.0f, 1.0f, 0.0f };
			Tuple t{ 1.0f, 1.0f, 6.0f, 1.0f };
			Tuple add = t1 + t2;

			Assert::IsTrue(t == add);
		}

		TEST_METHOD(PointSubtract)
		{
			Point p1{ 3.0f, 2.0f, 1.0f };
			Point p2{ 5.0f, 6.0f, 7.0f };
			Vector v{ -2.0f, -4.0f, -6.0f };

			Assert::IsTrue(v == p1 - p2);
		}

		TEST_METHOD(PointVectorSubtract)
		{
			Point p{ 3.0f, 2.0f, 1.0f };
			Vector v{ 5.0f, 6.0f, 7.0f };
			Point q{ -2.0f, -4.0f, -6.0f };

			Assert::IsTrue(q == p - v);
		}

		TEST_METHOD(VectorVectorSubtract)
		{
			Vector v1{ 3.0f, 2.0f, 1.0f };
			Vector v2{ 5.0f, 6.0f, 7.0f };
			Vector r{ -2.0f, -4.0f, -6.0f };

			Assert::IsTrue(r == v1 - v2);
		}

		TEST_METHOD(TupleNegation)
		{
			Tuple t{ 1.0f, -2.0f, 3.0f, -4.0f };
			Tuple n{ -1.0f, 2.0f, -3.0f, 4.0f };

			Vector v{ 5.0f, 6.0f, 7.0f };
			Vector i{ -5.0f, -6.0f, -7.0f };

			Assert::IsTrue(-t == n);
			Assert::IsTrue(-v == i);
		}

		TEST_METHOD(ScalarMultiplication)
		{
			Tuple t{ 1.0f, -2.0f, 3.0f, -4.0f };
			Tuple m{ 3.5f, -7.0f, 10.5f, -14.0f };

			Assert::IsTrue(t * 3.5 == m);
			Assert::IsTrue(3.5 * t == m);
		}

		TEST_METHOD(ScalarDivision)
		{
			Tuple t{ 1.0f, -2.0f, 3.0f, -4.0f };
			Tuple d{ 0.5f, -1.0f, 1.5f, -2.0f };

			Assert::IsTrue(t / 2.0f == d);
		}

	};

	TEST_CLASS(VectorOperations)
	{
	public:
		TEST_METHOD(Magnitude)
		{
			Vector v1{ 1.0f, 0.0f, 0.0f };
			Vector v2{ 0.0f, 1.0f, 0.0f };
			Vector v3{ 0.0f, 0.0f, 1.0f };
			
			Vector v4{ 1.0f, 2.0f, 3.0f };
			Vector v5{ -1.0f, -2.0f, -3.0f };
			
			Assert::IsTrue(Equal(v1.Magnitude(), 1.0f));
			Assert::IsTrue(Equal(v2.Magnitude(), 1.0f));
			Assert::IsTrue(Equal(v3.Magnitude(), 1.0f));
			Assert::IsTrue(Equal(v4.Magnitude(), sqrt(14.0f)));
			Assert::IsTrue(Equal(v5.Magnitude(), sqrt(14.0f)));
		}

		TEST_METHOD(Normalization)
		{
			Vector v1{ 4.0f, 0.0f, 0.0f };
			Vector v2{ 1.0f, 2.0f, 3.0f };

			Assert::IsTrue(v1.Normalized() == Vector(1.0f, 0.0f, 0.0f));
			Assert::IsTrue(v2.Normalized() == Vector(1.0f / sqrt(14.0f), 2.0f / sqrt(14.0f), 3.0f / sqrt(14.0f)));

			Assert::IsTrue(Equal(v1.Normalized().Magnitude(), 1.0f));
			Assert::IsTrue(Equal(v2.Normalized().Magnitude(), 1.0f));
		}

		TEST_METHOD(DotProduct)
		{
			Vector v1{ 1.0f, 2.0f, 3.0f };
			Vector v2{ 2.0f, 3.0f, 4.0f };
			
			Assert::IsTrue(Equal(v1.Dot(v2), 20.0f));
		}

		TEST_METHOD(CrossProduct)
		{
			Vector v1{ 1.0f, 2.0f, 3.0f };
			Vector v2{ 2.0f, 3.0f, 4.0f };

			Assert::IsTrue(v1.Cross(v2) == Vector(-1.0f, 2.0f, -1.0f));
			Assert::IsTrue(v2.Cross(v1) == Vector(1.0f, -2.0f, 1.0f));
		}
	};
}
