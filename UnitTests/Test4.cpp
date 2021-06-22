/**********************************************************************************
// Test4 (Arquivo de Código Fonte)
//
// Criação:		21 Jun 2021
// Atualização:	21 Jun 2021
// Compilador:	Clang++ 12.0.5 / GNU g++ 9.3.0
//
// Descrição:	Define os testes de unidade criados para o Capítulo 4,
//              Transformações de Matrizes, do livro "The Ray Tracer Challenge".
//              Os testes utilizam o framework GoogleTest.
//
**********************************************************************************/

#include "../RayTracer/Types.h"
#include "../RayTracer/Matrix.h"
#include <gtest/gtest.h>
using namespace RayTracer;

namespace Test4
{
    TEST(Transformations, TranslatePoint)
	{
        Matrix T = Translation(5, -3, 2);
        Point p {-3, 4, 5};
        Point r {2, 1 ,7};
        
		EXPECT_TRUE(T * p == r);
	}

    TEST(Transformations, TranslateInverse)
	{
        Matrix T = Translation(5, -3, 2);
        Matrix InvT = T.Inverse(); 
        Point p {-3, 4, 5};
        Point r {2, 1 ,7};
		EXPECT_TRUE(InvT * r == p);
	}

    TEST(Transformations, TranslateVector)
	{
        Matrix T = Translation(5, -3, 2); 
        Vector v {-3, 4, 5};
		EXPECT_TRUE(T * v == v);
	}

    TEST(Transformations, ScalePoint)
	{
        Matrix S = Scaling(2, 3, 4); 
        Point p {-4, 6, 8};
        Point r {-8, 18, 32};
		EXPECT_TRUE(S * p == r);
	}

    TEST(Transformations, ScaleInverse)
	{
        Matrix S = Scaling(2, 3, 4); 
        Matrix InvS = S.Inverse();
        Point p {-4, 6, 8};
        Point r {-2, 2, 2};
		EXPECT_TRUE(InvS * p == r);
	}

    TEST(Transformations, ScaleVector)
	{
        Matrix S = Scaling(2, 3, 4); 
        Vector v {-4, 6, 8};
        Vector w {-8, 18, 32};
		EXPECT_TRUE(S * v == w);
	}

    TEST(Transformations, Reflection)
	{
        Matrix S = Scaling(-1, 1, 1); 
        Point p {2, 3, 4};
        Point r {-2, 3, 4};
		EXPECT_TRUE(S * p == r);
	}
}