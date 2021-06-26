/**********************************************************************************
// Test5 (Arquivo de Código Fonte)
//
// Criação:		25 Jun 2021
// Atualização:	25 Jun 2021
// Compilador:	Clang++ 12.0.5 / GNU g++ 9.3.0
//
// Descrição:	Define os testes de unidade criados para o Capítulo 5,
//              Interseções Raio-Esfera, do livro "The Ray Tracer Challenge".
//              Os testes utilizam o framework GoogleTest.
//
**********************************************************************************/

#include "../RayTracer/Types.h"
#include "../RayTracer/Ray.h"
#include <gtest/gtest.h>
using namespace RayTracer;

namespace Test5
{
    TEST(Ray, Creation)
	{
        Point origin {1,2,3};
        Vector direction {4,5,6};
        Ray ray {origin, direction};
		EXPECT_TRUE(ray.origin == origin);
        EXPECT_TRUE(ray.direction == direction);
	}

    TEST(Ray, Position)
	{
        Ray ray {Point(2,3,4), Vector(1,0,0)};
		EXPECT_TRUE(ray.Position(0) == Point(2,3,4));
        EXPECT_TRUE(ray.Position(1) == Point(3,3,4));
        EXPECT_TRUE(ray.Position(-1) == Point(1,3,4));
        EXPECT_TRUE(ray.Position(2.5) == Point(4.5,3,4));
	}

    TEST(Ray, TangentIntersect)
	{
        Ray r {Point(0,1,-5), Vector(0,0,1)};
        Sphere s;
        Intersection pos = s.Intersect(r);

		EXPECT_EQ(pos.count, 2);
        EXPECT_EQ(pos[0], 5.0f);
        EXPECT_EQ(pos[1], 5.0f);
    }

    TEST(Ray, NoIntersection)
	{
        Ray r {Point(0,2,-5), Vector(0,0,1)};
        Sphere s;
        Intersection pos = s.Intersect(r);
		EXPECT_EQ(pos.count, 0);
    }

    TEST(Ray, InsideSphere)
	{
        Ray r {Point(0,0,0), Vector(0,0,1)};
        Sphere s;
        Intersection pos = s.Intersect(r);
		
        EXPECT_EQ(pos.count, 2);
        EXPECT_EQ(pos[0], -1.0f);
        EXPECT_EQ(pos[1], 1.0f);
    }

    TEST(Ray, AfterSphere)
	{
        Ray r {Point(0,0,5), Vector(0,0,1)};
        Sphere s;
        Intersection pos = s.Intersect(r);
		
        EXPECT_EQ(pos.count, 2);
        EXPECT_EQ(pos[0], -6.0f);
        EXPECT_EQ(pos[1], -4.0f);
    }	
}