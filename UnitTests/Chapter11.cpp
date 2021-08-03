/**********************************************************************************
// Chapter11 (Arquivo de Código Fonte)
//
// Criação:     26 Jul 2021
// Atualização:	26 Jul 2021
// Compilador:	Clang++ 12.0.5 / GNU g++ 9.3.0
//
// Descrição:	Define os testes de unidade criados para o Capítulo 11,
//              Reflexão e Refração, do livro "The Ray Tracer Challenge".
//              Os testes utilizam o framework GoogleTest.
//
**********************************************************************************/

#include <gtest/gtest.h>
#include <cmath>
#include "Ray.h"
#include "Lighting.h"
#include "Shape.h"
#include "World.h"
using namespace RayTracer;

namespace Chapter11
{
    TEST(ReflectRefract, DefaultReflective)
    {
        Material m;
        EXPECT_EQ(m.reflective, 0.0);
    }

    TEST(ReflectRefract, ReflectionVector)
    {
        Plane shape;
        Ray ray { Point{0, 1, -1}, Vector{0, -sqrt(2)/2, sqrt(2)/2}};
        Intersection i { sqrt(2), shape };
        HitData hit = PrepareComputations(i, ray); 
        EXPECT_EQ(hit.reflect, Vector(0, sqrt(2)/2, sqrt(2)/2));
    }

    TEST(ReflectRefract, ReflectedColorNRM)
    {   
        World world { World::Default };
        Ray ray { Point{0, 0, 0}, Vector{0, 0, 1}};
        Shape * shape = world.objects[1];
        shape->material.ambient = 1;
        Intersection i { 1, *shape };
        HitData hit = PrepareComputations(i, ray); 
        Color color = world.ReflectedColor(hit);
        EXPECT_EQ(color, Color::Black);
    }

    TEST(ReflectRefract, ReflectedColorRM)
    {
        Plane shape;
        shape.material.reflective = 0.5;
        shape.transform = Translation(0, -1, 0);
        
        World world { World::Default };
        world.objects.push_back(&shape);

        Ray ray { Point{0, 0, -3}, Vector{0, -sqrt(2)/2, sqrt(2)/2}};
        Intersection i { sqrt(2.0), shape };
        HitData hit = PrepareComputations(i, ray); 
        Color color = world.ReflectedColor(hit);
        EXPECT_TRUE(color == Color(0.19032, 0.23790, 0.14274));
    }

    TEST(ReflectRefract, ShadeHitRM)
    {
        Plane shape;
        shape.material.reflective = 0.5;
        shape.transform = Translation(0, -1, 0);
        
        World world { World::Default };
        world.objects.push_back(&shape);

        Ray ray { Point{0, 0, -3}, Vector{0, -sqrt(2)/2, sqrt(2)/2}};
        Intersection i { sqrt(2.0), shape };
        HitData hit = PrepareComputations(i, ray); 
        Color color = world.ShadeHit(hit);
        EXPECT_TRUE(color == Color(0.87677, 0.92436, 0.82918));
    }

    TEST(ReflectRefract, MutualReflection)
    {
        Plane lower;
        lower.material.reflective = 1.0;
        lower.transform = Translation(0, -1, 0);

        Plane upper;
        upper.material.reflective = 1.0;
        upper.transform = Translation(0, 1, 0);
        
        World world { World::Empty };
        world.light = PointLight{ Point{0,0,0}, Color{1,1,1} };
        world.objects.push_back(&lower);
        world.objects.push_back(&upper);

        Ray ray { Point{0,0,0}, Vector{0,1,0} };
        
        // espera que a função termine sem 
        // entrar em uma recursão infinita
        EXPECT_TRUE(world.ColorAt(ray) == Color(11.4, 11.4, 11.4));
    }

    TEST(ReflectRefract, ReflectedAtMaxRecursion)
    {
        Plane shape;
        shape.material.reflective = 0.5;
        shape.transform = Translation(0, -1, 0);
        
        World world { World::Default };
        world.objects.push_back(&shape);

        Ray ray { Point{0, 0, -3}, Vector{0, -sqrt(2)/2, sqrt(2)/2}};
        Intersection i { sqrt(2.0), shape };
        HitData hit = PrepareComputations(i, ray); 
        Color color = world.ReflectedColor(hit, 0);
        EXPECT_TRUE(color == Color(0,0,0));
    }
}