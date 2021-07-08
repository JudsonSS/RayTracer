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
        EXPECT_TRUE(world.objects.size() == 0);
        EXPECT_TRUE(world.light == PointLight());
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
        
        EXPECT_TRUE(world.light == light);
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

    TEST(World, StateOfIntersection)
	{
        Ray ray { Point{0,0,-5}, Vector{0,0,1} };
        Sphere shape;
        Intersection i {4, shape};
        HitData comps = PrepareComputations(i, ray);
        
        EXPECT_EQ(comps.time, i.time);
        EXPECT_EQ(comps.object, i.object);
        EXPECT_EQ(comps.point, Point(0,0,-1));
        EXPECT_EQ(comps.eye, Vector(0,0,-1));
        EXPECT_EQ(comps.normal, Vector(0,0,-1));
    }

    TEST(World, HitOutsideObject)
	{
        Ray ray { Point{0,0,-5}, Vector{0,0,1} };
        Sphere shape;
        Intersection i {4, shape};
        HitData comps = PrepareComputations(i, ray);
        EXPECT_EQ(comps.inside, false);
    }

    TEST(World, HitInsideObject)
	{
        Ray ray { Point{0,0,0}, Vector{0,0,1} };
        Sphere shape;
        Intersection i {1, shape};
        HitData comps = PrepareComputations(i, ray);
        EXPECT_EQ(comps.inside, true);
        EXPECT_EQ(comps.point, Point(0,0,1));
        EXPECT_EQ(comps.eye, Vector(0,0,-1));
        EXPECT_EQ(comps.normal, Vector(0,0,-1));
    }

    TEST(World, ShadingIntersection)
	{
        World world(World::Default);
        Ray ray { Point{0,0,-5}, Vector{0,0,1} };
        Sphere & shape = *((Sphere*) world.objects[0]); 
        Intersection i {4, shape};
        HitData comps = PrepareComputations(i, ray);
        Color color = world.ShadeHit(comps);
        EXPECT_EQ(color, Color(0.38066, 0.47583, 0.2855));
    }

    TEST(World, ShadingFromInside)
	{
        World world(World::Default);
        world.light = PointLight{Point{0,0.25,0}, Color{1,1,1}};
        Ray ray { Point{0,0,0}, Vector{0,0,1} };
        Sphere & shape = *((Sphere*) world.objects[1]); 
        Intersection i {0.5, shape};
        HitData comps = PrepareComputations(i, ray);
        Color color = world.ShadeHit(comps);
        EXPECT_EQ(color, Color(0.90498, 0.90498, 0.90498));
    }

    TEST(World, ColorRayMisses)
	{
        World world(World::Default);
        Ray ray { Point{0,0,-5}, Vector{0,1,0} };
        Color color = world.ColorAt(ray);
        EXPECT_EQ(color, Color(0, 0, 0));
    }

    TEST(World, ColorRayHits)
	{
        World world(World::Default);
        Ray ray { Point{0,0,-5}, Vector{0,0,1} };
        Color color = world.ColorAt(ray);
        EXPECT_EQ(color, Color(0.38066, 0.47583, 0.2855));
    }

    TEST(World, ColorBehindRay)
	{
        World world(World::Default);
        Sphere & outer = *((Sphere*) world.objects[0]); 
        Sphere & inner = *((Sphere*) world.objects[1]);
        outer.material.ambient = 1;
        inner.material.ambient = 1; 

        Ray ray { Point{0, 0, 0.75}, Vector{0, 0, -1} };
        Color color = world.ColorAt(ray);
        EXPECT_EQ(color, inner.material.color);
    }
}