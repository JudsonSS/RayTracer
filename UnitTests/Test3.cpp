/**********************************************************************************
// Test3 (Arquivo de Código Fonte)
//
// Criação:		18 Jun 2020
// Atualização:	18 Jun 2021
// Compilador:	Clang++ 12.0.5 / GNU g++ 9.3.0
//
// Descrição:	Define os testes de unidade criados no Capítulo 3 
//              (Matrizes) do livro "The Ray Tracer Challenge". 
//              Os testes utilizam o framework GoogleTest.
//
**********************************************************************************/

#include "../RayTracer/Types.h"
#include <gtest/gtest.h>
using namespace RayTracer;

namespace Test3
{
    TEST(Matrix, M4x4)
	{
        Matrix M {4,4};
        
        M = 
        { 
            1, 2, 3, 4, 
            5.5, 6.5, 7.5, 8.5, 
            9, 10, 11, 12, 
            13.5, 14.5, 15.5, 16.5
        };

		EXPECT_EQ(M(0,0), 1);
		EXPECT_EQ(M(0,3), 4);
        EXPECT_EQ(M(1,0), 5.5);
        EXPECT_EQ(M(1,2), 7.5);
        EXPECT_EQ(M(2,2), 11);
        EXPECT_EQ(M(3,0), 13.5);
        EXPECT_EQ(M(3,2), 15.5);
	}

    TEST(Matrix, M3x3)
    {
        Matrix M {3,3};
        
        M = 
        {
            -3, 5, 0,
            1, -2, -7,
            0, 1, 1
        };

        EXPECT_EQ(M(0,0), -3);
        EXPECT_EQ(M(1,1), -2);
        EXPECT_EQ(M(2,2), 1);
    }

    TEST(Matrix, M2x2)
    {
        Matrix M {2,2}; 
        
        M = 
        {
            -3, 5,
            1, -2
        };

        EXPECT_EQ(M(0,0), -3);
        EXPECT_EQ(M(0,1), 5);
        EXPECT_EQ(M(1,0), 1);
        EXPECT_EQ(M(1,1), -2);
    }

    TEST(Matrix, Equality)
	{
        Matrix A {4,4};
        
        A = 
        { 
            1,2,3,4,
            5,6,7,8,
            9,8,7,6,
            5,4,3,2
        };

        Matrix B {4,4};
        
        B = 
        { 
            1,2,3,4,
            5,6,7,8,
            9,8,7,6,
            5,4,3,2
        };

		EXPECT_TRUE(A == B);
	}

    TEST(Matrix, Inequality)
	{
        Matrix A {4,4};
        
        A = 
        { 
            1,2,3,4,
            5,6,7,8,
            9,8,7,6,
            5,4,3,2
        };

        Matrix B {4,4};
        
        B = 
        { 
            2,3,4,5,
            6,7,8,9,
            8,7,6,5,
            4,3,2,1
        };

		EXPECT_TRUE(A != B);
	}

    TEST(Matrix, Empty)
    {
        Matrix A{3, 3};
        Matrix B{3, 3};

        B =
        {
            0, 0, 0,
            0, 0, 0,
            0, 0, 0
        };

        EXPECT_TRUE(A == B);
    }
}
