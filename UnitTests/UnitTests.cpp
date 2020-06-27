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
			Tuple  t = { 4.3f, -4.2f, 3.1f, 1.0f };

			Assert::AreEqual(t.x, 4.3f);
			Assert::AreEqual(t.y, -4.2f);
			Assert::AreEqual(t.z, 3.1f);
			Assert::AreEqual(t.w, 1.0f);
		}

		TEST_METHOD(TupleZero)
		{
			Tuple  t = { 4.3f, -4.2f, 3.1f, 0.0f };

			Assert::AreEqual(t.x, 4.3f);
			Assert::AreEqual(t.y, -4.2f);
			Assert::AreEqual(t.z, 3.1f);
			Assert::AreEqual(t.w, 0.0f);
		}

		TEST_METHOD(TuplePoint)
		{
			Tuple t = { 4.3f, -4.2f, 3.1f, 1.0f };
			Point p = { 4.3f, -4.2f, 3.1f };

			Assert::AreEqual(t.x, p.x);
			Assert::AreEqual(t.y, p.y);
			Assert::AreEqual(t.z, p.z);
			Assert::AreEqual(t.w, p.w);
		}

		TEST_METHOD(TupleVector)
		{
			Tuple t = { 4.3f, -4.2f, 3.1f, 0.0f };
			Vector v = { 4.3f, -4.2f, 3.1f };

			Assert::AreEqual(t.x, v.x);
			Assert::AreEqual(t.y, v.y);
			Assert::AreEqual(t.z, v.z);
			Assert::AreEqual(t.w, v.w);
		}
	};
}
