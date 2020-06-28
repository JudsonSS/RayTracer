#include "pch.h"
#include "CppUnitTest.h"
#include "../RayTracer/Types.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace RayTracer;

namespace UnitTest
{
	TEST_CLASS(UnitTest)
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

		TEST_METHOD(TupleAdd)
		{
			Tuple t1{ 3.0f, -2.0f, 5.0f, 1.0f };
			Tuple t2{ -2.0f, 3.0f, 1.0f, 0.0f };
			Tuple t{ 1.0f, 1.0f, 6.0f, 1.0f };

			Assert::IsTrue(t == t1 + t2);

			Tuple add = t1 + t2;

			Assert::AreEqual(add.x, t.x);
			Assert::AreEqual(add.y, t.y);
			Assert::AreEqual(add.z, t.z);
			Assert::AreEqual(add.w, t.w);
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
	};
}
