/**********************************************************************************
// Chapter8 (Arquivo de Código Fonte)
//
// Criação:     09 Jul 2021
// Atualização:	17 Jul 2021
// Compilador:	Clang++ 12.0.5 / GNU g++ 9.3.0
//
// Descrição:	Define os testes de unidade criados para o Capítulo 8,
//              Sombras, do livro "The Ray Tracer Challenge".
//              Os testes utilizam o framework GoogleTest.
//
**********************************************************************************/

#include <gtest/gtest.h>
#include <cmath>
#include "Types.h"
#include "Point.h"
#include "Vector.h"
#include "Color.h"
#include "Matrix.h"
#include "Ray.h"
#include "Shape.h"
#include "World.h"
using namespace RayTracer;

namespace Chapter8
{
    TEST(Shadows, SurfaceInShadow)
    {
        Material m;
        Point position {0,0,0}; 
        Vector eye {0,0,-1};
        Vector normal {0,0,-1};
        PointLight light {Point(0,0,-10), Color(1,1,1)};
        bool in_shadow = true;
        Sphere sphere;
        Color result = Lighting(m, sphere, light, position, eye, normal, in_shadow);
        EXPECT_TRUE(result == Color(0.1, 0.1, 0.1));
    }

    TEST(Shadows, Scenario1)
    {
        World world {World::Default};
        Point p {0, 10, 0};
        EXPECT_FALSE(world.IsShadowed(p));
    }

    TEST(Shadows, Scenario2)
    {
        World world {World::Default};
        Point p {10, -10, 10};
        EXPECT_TRUE(world.IsShadowed(p));
    }

    TEST(Shadows, Scenario3)
    {
        World world {World::Default};
        Point p {-20, 20, -20};
        EXPECT_FALSE(world.IsShadowed(p));
    }

    TEST(Shadows, Scenario4)
    {
        World world {World::Default};
        Point p {-2, 2, -2};
        EXPECT_FALSE(world.IsShadowed(p));
    }

    TEST(Shadows, IntersectionInShadow)
    {
        World world {World::Empty};
        world.light = PointLight{ Point{0,0,-10}, Color{1,1,1} };
        Sphere * s1 = new Sphere;
        Sphere * s2 = new Sphere;
        s2->transform = Translation(0,0,10);
        world.objects.push_back(s1);
        world.objects.push_back(s2);

        Ray ray { Point{0,0,5}, Vector{0,0,1} };
        Intersection i {4, *s2};
        HitData hit = PrepareComputations(i, ray);
        Color color = world.ShadeHit(hit);
        EXPECT_TRUE(color == Color(0.1, 0.1, 0.1));
    }

    TEST(Shadows, OverPoint)
    {
        Ray ray { Point{0,0,-5}, Vector{0,0,1} };
        Sphere shape;
        shape.transform = Translation(0,0,1);
        Intersection i {5, shape};
        HitData hit = PrepareComputations(i, ray);
        EXPECT_TRUE(hit.over_point.z < -EPSILON/2);
        EXPECT_TRUE(hit.point.z > hit.over_point.z);
    }
}