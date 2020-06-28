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

	};
}
