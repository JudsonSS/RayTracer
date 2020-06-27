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
		
		TEST_METHOD(TestTuplePoint)
		{
			Tuple  t = { 4.3f, -4.2f, 3.1f, 1.0f };

			Assert::AreEqual(t.x, 4.3f);
			Assert::AreEqual(t.y, -4.2f);
			Assert::AreEqual(t.z, 3.1f);
			Assert::AreEqual(t.w, 1.0f);
		}
	};
}
