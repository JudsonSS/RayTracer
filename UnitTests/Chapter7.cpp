/**********************************************************************************
// Test7 (Arquivo de Código Fonte)
//
// Criação:		29 Jun 2021
// Atualização:	04 Jul 2021
// Compilador:	Clang++ 12.0.5 / GNU g++ 9.3.0
//
// Descrição:	Define os testes de unidade criados para o Capítulo 6,
//              Luz e Sombreamento, do livro "The Ray Tracer Challenge".
//              Os testes utilizam o framework GoogleTest.
//
**********************************************************************************/

#include <gtest/gtest.h>
#include "World.h"
using namespace RayTracer;

namespace Chapter7
{
    TEST(World, Empty)
	{
        World world;
        EXPECT_TRUE(world.Objects() == 0);
        EXPECT_TRUE(world.Lights() == 0);
    }

    TEST(World, Default)
	{
        PointLight light {Point{-10,10,-10}, Color{1,1,1}};

        Sphere s1, s2;
        s1.material.color = Color{0.8, 1.0, 0.6};
        s1.material.diffuse = 0.7;
        s1.material.specular = 0.2;
        s2.transform = Scaling(0.5, 0.5, 0.5);
        
        World world(World::Default);
        
        EXPECT_TRUE(world.Contains(light));
        EXPECT_TRUE(world.Contains(s1));
        EXPECT_TRUE(world.Contains(s2));
    }

    TEST(World, RayIntersect)
	{
        World world(World::Default);
        Ray ray { Point{0,0,-5}, Vector{0,0,1} };
        vector<Intersection> xs = world.Intersect(ray);
        
        EXPECT_EQ(xs.size(), 4);
        EXPECT_EQ(xs[0].time, 4.0);
        EXPECT_EQ(xs[1].time, 4.5);
        EXPECT_EQ(xs[2].time, 5.5);
        EXPECT_EQ(xs[3].time, 6.0);
    }
}