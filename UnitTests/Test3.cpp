/**********************************************************************************
// Test3 (Arquivo de Código Fonte)
//
// Criação:		18 Jun 2021
// Atualização:	20 Jun 2021
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

    TEST(Matrix, TransIdentity)
    {
        Matrix A = Matrix::Identity.Transpose();
        EXPECT_TRUE(A == Matrix::Identity);
    }

    TEST(Matrix, Determinant2x2)
    {
        Matrix A {2,2};
        A = {1, 5, 
            -3, 2};

        EXPECT_EQ(A.Determinant(), 17);
    }

    TEST(Matrix, Submatrix2x2)
    {
        Matrix A {3,3};
        Matrix R {2,2};

        A = { 1, 5, 0, 
             -3, 2, 7,
              0, 6,-3 };

        R = {-3, 2,
              0, 6 };
        
        Matrix S = A.Submatrix(0,2);
        EXPECT_TRUE(S == R);
    }

    TEST(Matrix, Submatrix3x3)
    {
        Matrix A {4,4};
        Matrix R {3,3};

        A = {-6, 1, 1, 6, 
             -8, 5, 8, 6,
             -1, 0, 8, 2,
             -7, 1,-1, 1 };

        R = {-6, 1, 6,
             -8, 8, 6,
             -7, -1, 1 };
        
        Matrix S = A.Submatrix(2,1);
        EXPECT_TRUE(S == R);
    }

    TEST(Matrix, Minor)
    {
        Matrix A {3,3};
    
        A = { 3, 5, 0, 
              2,-1,-7,
              6,-1, 5 };

        Matrix B = A.Submatrix(1,0);
        EXPECT_EQ(B.Determinant(), 25);
        EXPECT_EQ(A.Minor(1,0), 25);
    }

    TEST(Matrix, Cofactor)
    {
        Matrix A {3,3};
    
        A = { 3, 5, 0, 
              2,-1,-7,
              6,-1, 5 };

        EXPECT_EQ(A.Minor(0,0), -12);
        EXPECT_EQ(A.Cofactor(0,0), -12);
        EXPECT_EQ(A.Minor(1,0), 25);
        EXPECT_EQ(A.Cofactor(1,0), -25);
    }

    TEST(Matrix, Determinant3x3)
    {
        Matrix A {3,3};
    
        A = { 1, 2, 6, 
             -5, 8,-4,
              2, 6, 4 };

        EXPECT_EQ(A.Cofactor(0,0), 56);
        EXPECT_EQ(A.Cofactor(0,1), 12);
        EXPECT_EQ(A.Cofactor(0,2), -46);
        EXPECT_EQ(A.Determinant(), -196);
    }

    TEST(Matrix, Determinant4x4)
    {
        Matrix A {4,4};
    
        A = {-2,-8, 3, 5, 
             -3, 1, 7, 3,
              1, 2,-9, 6,
             -6, 7, 7, -9 };

        EXPECT_EQ(A.Cofactor(0,0), 690);
        EXPECT_EQ(A.Cofactor(0,1), 447);
        EXPECT_EQ(A.Cofactor(0,2), 210);
        EXPECT_EQ(A.Cofactor(0,3), 51);
        EXPECT_EQ(A.Determinant(), -4071);
    }

    TEST(Matrix, Invertible)
    {
        Matrix A {4,4};
    
        A = { 6, 4, 4, 4, 
              5, 5, 7, 6,
              4,-9, 3,-7,
              9, 1, 7,-6 };

        EXPECT_EQ(A.Determinant(), -2120);
        EXPECT_TRUE(A.Invertible());
    }

    TEST(Matrix, Noninvertible)
    {
        Matrix A {4,4};
    
        A = {-4, 2,-2,-3, 
              9, 6, 2, 6,
              0,-5, 1,-5,
              0, 0, 0, 0 };

        EXPECT_EQ(A.Determinant(), 0);
        EXPECT_FALSE(A.Invertible());
    }

    TEST(Matrix, Inverse)
    {
        Matrix A {4,4};
    
        A = {-5, 2, 6,-8, 
              1,-5, 1, 8,
              7, 7,-6,-7,
              1,-3, 7, 4 };
        
        Matrix B = A.Inverse();
        
        EXPECT_EQ(A.Determinant(), 532);
        EXPECT_EQ(A.Cofactor(2,3), -160);
        EXPECT_EQ(B(3,2), -160.0f/532.0f);
        EXPECT_EQ(A.Cofactor(3,2), 105);
        EXPECT_EQ(B(2,3), 105.0f/532.0f);

        Matrix Inv {4,4};

        Inv = { 0.21805, 0.45113, 0.24060,-0.04511, 
               -0.80827,-1.45677,-0.44361, 0.52068,
               -0.07895,-0.22368,-0.05263, 0.19737,
               -0.52256,-0.81391,-0.30075, 0.30639 }; 

        EXPECT_TRUE(B == Inv);
    }

    TEST(Matrix, Inverse2)
    {
        Matrix A {4,4};
    
        A = { 8,-5, 9, 2, 
              7, 5, 6, 1,
             -6, 0, 9, 6,
             -3, 0,-9,-4 };
        
        Matrix InvA {4,4};

        InvA = {-0.15385,-0.15385,-0.28205,-0.53846, 
                -0.07692, 0.12308, 0.02564, 0.03077,
                 0.35897, 0.35897, 0.43590, 0.92308,
                -0.69231,-0.69231,-0.76923,-1.92308 };
        
        EXPECT_TRUE(A.Inverse() == InvA);
    }

    TEST(Matrix, Inverse3)
    {
        Matrix A {4,4};
    
        A = { 9, 3, 0, 9, 
             -5,-2,-6,-3,
             -4, 9, 6, 4,
             -7, 6, 6, 2 };
        
        Matrix InvA {4,4};

        InvA = {-0.04074,-0.07778, 0.14444,-0.22222, 
                -0.07778, 0.03333, 0.36667,-0.33333,
                -0.02901,-0.14630,-0.10926, 0.12963,
                 0.17778, 0.06667,-0.26667, 0.33333 };
        
        EXPECT_TRUE(A.Inverse() == InvA);
    }

    TEST(Matrix, ProductInv)
    {
        Matrix A {4,4};
    
        A = { 3,-9, 7, 3, 
              3,-8, 2,-9,
             -4, 4, 4, 1,
             -6, 5,-1, 1 };
        
        Matrix B {4,4};

        B = { 8, 2, 2, 2,
              3,-1, 7, 0,
              7, 0, 5, 4,
              6,-2, 0, 5 };
        
        Matrix C = A * B;

        EXPECT_TRUE(C * B.Inverse() == A);
    }

    TEST(Matrix, IdentityInv)
    {
        Matrix Inv = Matrix::Identity.Inverse(); 
        EXPECT_TRUE(Inv == Matrix::Identity);
    }

    TEST(Matrix, AxAinv)
    {
        Matrix A {4,4};
    
        A = { 3,-9, 7, 3, 
              3,-8, 2,-9,
             -4, 4, 4, 1,
             -6, 5,-1, 1 };

        EXPECT_TRUE(A * A.Inverse() == Matrix::Identity);
    }

    TEST(Matrix, TransposeInverse)
    {
        Matrix A {4,4};
    
        A = { 3,-9, 7, 3, 
              3,-8, 2,-9,
             -4, 4, 4, 1,
             -6, 5,-1, 1 };

        EXPECT_TRUE(A.Transpose().Inverse() == A.Inverse().Transpose());
    }
}