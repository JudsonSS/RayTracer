/**********************************************************************************
// Test4 (Arquivo de Código Fonte)
//
// Criação:		21 Jun 2021
// Atualização:	04 Jul 2021
// Compilador:	Clang++ 12.0.5 / GNU g++ 9.3.0
//
// Descrição:	Define os testes de unidade criados para o Capítulo 4,
//              Transformações de Matrizes, do livro "The Ray Tracer Challenge".
//              Os testes utilizam o framework GoogleTest.
//
**********************************************************************************/

#include <gtest/gtest.h>
#include <cmath>
#include "Types.h"
#include "Matrix.h"
using namespace RayTracer;

namespace Chapter4
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

    TEST(Transformations, RotationX)
	{
        Point p {0, 1, 0};
        Matrix HalfQuarter = RotationX(PI/4);
        Matrix FullQuarter = RotationX(PI/2); 
        
        Point hq {0, sqrt(2.0f)/2.0f, sqrt(2.0f)/2.0f};
        Point fq {0, 0, 1};
		EXPECT_TRUE(HalfQuarter * p == hq);
        EXPECT_TRUE(FullQuarter * p == fq);
	}

    TEST(Transformations, RotationXInv)
	{
        Point p {0, 1, 0};
        Point hq {0, sqrt(2.0f)/2.0f, sqrt(2.0f)/2.0f};
        Matrix HalfQuarter = RotationX(PI/4);
        Matrix HQInv = HalfQuarter.Inverse(); 
        
		EXPECT_TRUE(HQInv * hq == p);
	}

    TEST(Transformations, RotationY)
	{
        Point p {0, 0, 1};
        Matrix HalfQuarter = RotationY(PI/4);
        Matrix FullQuarter = RotationY(PI/2); 
        
        Point hq {sqrt(2.0f)/2.0f, 0, sqrt(2.0f)/2.0f};
        Point fq {1, 0, 0};
		EXPECT_TRUE(HalfQuarter * p == hq);
        EXPECT_TRUE(FullQuarter * p == fq);
	}

    TEST(Transformations, RotationZ)
	{
        Point p {0, 1, 0};
        Matrix HalfQuarter = RotationZ(PI/4);
        Matrix FullQuarter = RotationZ(PI/2); 
        
        Point hq {-sqrt(2.0f)/2.0f, sqrt(2.0f)/2.0f, 0};
        Point fq {-1, 0, 0};
		EXPECT_TRUE(HalfQuarter * p == hq);
        EXPECT_TRUE(FullQuarter * p == fq);
	}

    TEST(Transformations, ShearingXY)
	{
        Matrix S = Shearing(1,0,0,0,0,0); 
        Point p {2, 3, 4};
        Point r {5, 3, 4};
		EXPECT_TRUE(S * p == r);
	}

    TEST(Transformations, ShearingXZ)
	{
        Matrix S = Shearing(0,1,0,0,0,0); 
        Point p {2, 3, 4};
        Point r {6, 3, 4};
		EXPECT_TRUE(S * p == r);
	}

    TEST(Transformations, ShearingYX)
	{
        Matrix S = Shearing(0,0,1,0,0,0); 
        Point p {2, 3, 4};
        Point r {2, 5, 4};
		EXPECT_TRUE(S * p == r);
	}

    TEST(Transformations, ShearingYZ)
	{
        Matrix S = Shearing(0,0,0,1,0,0); 
        Point p {2, 3, 4};
        Point r {2, 7, 4};
		EXPECT_TRUE(S * p == r);
	}

    TEST(Transformations, ShearingZX)
	{
        Matrix S = Shearing(0,0,0,0,1,0); 
        Point p {2, 3, 4};
        Point r {2, 3, 6};
		EXPECT_TRUE(S * p == r);
	}

    TEST(Transformations, ShearingZY)
	{
        Matrix S = Shearing(0,0,0,0,0,1); 
        Point p {2, 3, 4};
        Point r {2, 3, 7};
		EXPECT_TRUE(S * p == r);
	}

    TEST(Transformations, Individual)
	{
        Point p {1, 0, 1};
        Matrix R = RotationX(PI/2);
        Matrix S = Scaling(5,5,5);
        Matrix T = Translation(10,5,7);

        // primeiro rotação
        Point p2 = R * p;
        EXPECT_TRUE(p2 == Point(1,-1,0));

        // depois aplica escala
        Point p3 = S * p2;
        EXPECT_TRUE(p3 == Point(5,-5,0));
        
        // e por fim translação
        Point p4 = T * p3;
		EXPECT_TRUE(p4 == Point(15,0,7));
	}

    TEST(Transformations, Chained)
	{
        Point p {1, 0, 1};
        Matrix R = RotationX(PI/2);
        Matrix S = Scaling(5,5,5);
        Matrix T = Translation(10,5,7);

        Matrix C = T*S*R;
		EXPECT_TRUE(C * p == Point(15,0,7));
	}
}