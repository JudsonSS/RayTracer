/**********************************************************************************
// Test1 (Arquivo de Código Fonte)
//
// Criação:		27 Jun 2020
// Atualização:	17 Jun 2021
// Compilador:	Clang++ 12.0.5 / GNU g++ 9.3.0
//
// Descrição:	Define os testes de unidade criados no capítulo 1
//              do livro "The Ray Tracer Challenge". Os testes utilizam
//              o framework GoogleTest.
//
**********************************************************************************/

#include "../RayTracer/Types.h"
#include <gtest/gtest.h>

using namespace RayTracer;

namespace Test2
{
	TEST(Colors, ColorsAreTuples)
	{
		Color c{-0.5f, 0.4f, 1.7f};
		EXPECT_EQ(c.x, -0.5f);
		EXPECT_EQ(c.y, 0.4f);
		EXPECT_EQ(c.z, 1.7f);
	}

	TEST(Colors, AddColors)
	{
		Color c1{0.9f, 0.6f, 0.75f};
		Color c2{0.7f, 0.1f, 0.25f};
		Color r{1.6f, 0.7f, 1.0f};

		Color add = c1 + c2;

		EXPECT_TRUE(r == add);
	}

	TEST(Colors, SubtractColors)
	{
		Color c1{0.9f, 0.6f, 0.75f};
		Color c2{0.7f, 0.1f, 0.25f};
		Color r{0.2f, 0.5f, 0.5f};

		Color sub = c1 - c2;

		EXPECT_TRUE(r == sub);
	}

	TEST(Colors, ScaleColors)
	{
		Color c{0.2f, 0.3f, 0.4f};
		Color r{0.4f, 0.6f, 0.8f};

		EXPECT_TRUE(c * 2.0f == r);
		EXPECT_TRUE(2.0f * c == r);
	}

	TEST(Colors, MultiplyColors)
	{
		Color c1{1.0f, 0.2f, 0.4f};
		Color c2{0.9f, 1.0f, 0.1f};
		Color r{0.9f, 0.2f, 0.04f};

		EXPECT_TRUE(c1 * c2 == r);
	}
}
