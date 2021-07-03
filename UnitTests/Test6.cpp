/**********************************************************************************
// Test6 (Arquivo de Código Fonte)
//
// Criação:		29 Jun 2021
// Atualização:	30 Jun 2021
// Compilador:	Clang++ 12.0.5 / GNU g++ 9.3.0
//
// Descrição:	Define os testes de unidade criados para o Capítulo 6,
//              Luz e Sombreamento, do livro "The Ray Tracer Challenge".
//              Os testes utilizam o framework GoogleTest.
//
**********************************************************************************/

#include <gtest/gtest.h>
#include <cmath>
#include "Types.h"
#include "Ray.h"
#include "Matrix.h"
#include "Geometry.h"
using namespace RayTracer;

namespace Test6
{
    TEST(Normal, PointXAxis)
	{
        Sphere s;
        Vector n = s.Normal(Point(1,0,0));
        EXPECT_TRUE(n == Vector(1,0,0));
    }

    TEST(Normal, PointYAxis)
	{
        Sphere s;
        Vector n = s.Normal(Point(0,1,0));
        EXPECT_TRUE(n == Vector(0,1,0));
	}

    TEST(Normal, PointZAxis)
	{
        Sphere s;
        Vector n = s.Normal(Point(0,0,1));
        EXPECT_TRUE(n == Vector(0,0,1));
	}

    TEST(Normal, PointNonAxial)
	{
        Sphere s;
        Vector n = s.Normal(Point(sqrt(3.0f)/3.0f, sqrt(3.0f)/3.0f, sqrt(3.0f)/3.0f));
        EXPECT_TRUE(n == Vector(sqrt(3.0f)/3.0f, sqrt(3.0f)/3.0f, sqrt(3.0f)/3.0f));
	}

    TEST(Normal, NormalizedVector)
	{
        Sphere s;
        Vector n = s.Normal(Point(sqrt(3.0f)/3.0f, sqrt(3.0f)/3.0f, sqrt(3.0f)/3.0f));
        EXPECT_TRUE(n == n.Normalized());
	}

    TEST(Normal, TranslatedSphere)
	{
        Sphere s;
        s.transform = Translation(0,1,0);
        Vector n = s.Normal(Point(0, 1.70711, -0.70711));
        EXPECT_TRUE(n == Vector(0, 0.70711, -0.70711));
	}

    TEST(Normal, TransformedSphere)
	{
        Sphere s;
        s.transform = Scaling(1, 0.5, 1) * RotationZ(PI/5);
        Vector n = s.Normal(Point(0, sqrt(2.0f)/2.0f, -sqrt(2.0f)/2.0f));
        EXPECT_TRUE(n == Vector(0, 0.97014, -0.24254));
	}

    TEST(Normal, Reflect45)
	{
        Vector v {1, -1, 0};
        Vector n {0, 1, 0};
        Vector r = v.Reflect(n);
        EXPECT_TRUE(r == Vector(1, 1, 0));
	}

    TEST(Normal, ReflectSlanted)
	{
        Vector v {0, -1, 0};
        Vector n {sqrt(2.0f)/2.0f, sqrt(2.0f)/2.0f, 0};
        Vector r = v.Reflect(n);
        EXPECT_TRUE(r == Vector(1, 0, 0));
	}
}