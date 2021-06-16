#include "pch.h"
#include "CppUnitTest.h"
#include "../RayTracer/Types.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace RayTracer;

namespace Chapter2
{
	TEST_CLASS(Construction)
	{
	public:
		TEST_METHOD(ColorsAreTuples)
		{
			Color c{ -0.5f, 0.4f, 1.7f };

			Assert::AreEqual(c.x, -0.5f);
			Assert::AreEqual(c.y, 0.4f);
			Assert::AreEqual(c.z, 1.7f);
		}
	};

	TEST_CLASS(Arithmetic)
	{
	public:

		TEST_METHOD(AddingColors)
		{
			Color c1{ 0.9f, 0.6f, 0.75f };
			Color c2{ 0.7f, 0.1f, 0.25f };
			Color r { 1.6f, 0.7f, 1.0f };

			Color add = c1 + c2;

			Assert::IsTrue(r == add);
		}

		TEST_METHOD(SubtractingColors)
		{
			Color c1{ 0.9f, 0.6f, 0.75f };
			Color c2{ 0.7f, 0.1f, 0.25f };
			Color r{ 0.2f, 0.5f, 0.5f };

			Color sub = c1 - c2;

			Assert::IsTrue(r == sub);
		}

		TEST_METHOD(MultiplyColorScalar)
		{
			Color c{ 0.2f, 0.3f, 0.4f };
			Color r{ 0.4f, 0.6f, 0.8f };

			Assert::IsTrue(c * 2.0f == r);
			Assert::IsTrue(2.0f * c == r);
		}

		TEST_METHOD(MultiplyColors)
		{
			Color c1{ 1.0f, 0.2f, 0.4f };
			Color c2{ 0.9f, 1.0f, 0.1f };
			Color r { 0.9f, 0.2f, 0.04f };

			Assert::IsTrue(c1 * c2 == r);
		}
	};

	TEST_CLASS(Operations)
	{
	public:


	};
}
