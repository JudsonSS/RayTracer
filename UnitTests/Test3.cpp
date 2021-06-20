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
#include "../RayTracer/Matrix.h"
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

    TEST(Matrix, CopyMove)
    {
        Matrix A {2, 2};
        Matrix B {2, 2};
        A = 
        { 
            1,2,
            3,4
        };

        B = 
        { 
            5,6,
            7,8
        };

        Matrix M {A*B};
        Matrix N {B};
        Matrix T = A * B;
        Matrix R = A;
        
        EXPECT_TRUE(M == T);
        EXPECT_TRUE(R == A);
    }

    TEST(Matrix, Multiplying)
    {
        Matrix A {4,4};
        Matrix B {4,4};
        Matrix R {4,4};

        A = 
        { 
            1,2,3,4,
            5,6,7,8,
            9,8,7,6,
            5,4,3,2
        };

        B = 
        { 
            -2,1,2,3,
            3,2,1,-1,
            4,3,6,5,
            1,2,7,8
        };

        R = 
        { 
            20,22,50,48,
            44,54,114,108,
            40,58,110,102,
            16,26,46,42
        };

        Matrix M = A*B;
        EXPECT_TRUE(M == R);
    }

    TEST(Matrix, TupleMultiply)
    {
        Matrix A {4,4};

        A = { 1,2,3,4,
              2,4,4,2,
              8,6,4,1,
              0,0,0,1 };

        Tuple t {1, 2, 3, 1};
        Tuple r {18,24,33,1};
        EXPECT_TRUE(A * t == r);
    }

    TEST(Matrix, Identity)
    {
        Matrix A {4,4};
        Matrix R {4,4};

        A = { 0,1,2,4,
              1,2,4,8,
              2,4,8,16,
              4,8,16,32 };
        
        R = A * Matrix::Identity;
        EXPECT_TRUE(R == A);
    }

    TEST(Matrix, Transpose)
    {
        Matrix A {4,4};
        Matrix T {4,4};

        A = { 0,9,3,0,
              9,8,0,8,
              1,8,5,3,
              0,0,5,8 };

        T = { 0,9,1,0,
              9,8,8,0,
              3,0,5,5,
              0,8,3,8 };
        
        EXPECT_TRUE(T == A.Transpose());
    }
}