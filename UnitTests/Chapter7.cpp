/**********************************************************************************
// Test7 (Arquivo de Código Fonte)
//
// Criação:     29 Jun 2021
// Atualização:	10 Jul 2021
// Compilador:	Clang++ 12.0.5 / GNU g++ 9.3.0
//
// Descrição:	Define os testes de unidade criados para o Capítulo 6,
//              Luz e Sombreamento, do livro "The Ray Tracer Challenge".
//              Os testes utilizam o framework GoogleTest.
//
**********************************************************************************/

#include <gtest/gtest.h>
#include <cmath>
#include "World.h"
#include "Canvas.h"
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

    TEST(World, DefaultViewTransform)
    {
        Point from {0, 0, 0};
        Point to {0, 0, -1};
        Vector up { 0, 1, 0};
        Matrix view = ViewTransform(from, to, up);
        EXPECT_EQ(view, Matrix::Identity);
    }

    TEST(World, LookingPositiveZ)
    {
        Point from {0, 0, 0};
        Point to {0, 0, 1};
        Vector up { 0, 1, 0};
        Matrix view = ViewTransform(from, to, up);
        EXPECT_EQ(view, Scaling(-1,1,-1));
    }

    TEST(World, ViewTransformMovesWorld)
    {
        Point from {0, 0, 8};
        Point to {0, 0, 0};
        Vector up { 0, 1, 0};
        Matrix view = ViewTransform(from, to, up);
        EXPECT_EQ(view, Translation(0,0,-8));
    }

    TEST(World, ArbitraryViewTransform)
    {
        Point from {1, 3, 2};
        Point to {4, -2, 8};
        Vector up { 1, 1, 0};
        Matrix view = ViewTransform(from, to, up);
        Matrix T {4, 4,  
            { 
              -0.50709, 0.50709,  0.67612, -2.36643,
               0.76772, 0.60609,  0.12122, -2.82843,
              -0.35857, 0.59761, -0.71714,  0.00000,
               0.00000, 0.00000,  0.00000,  1.00000 
            } 
        };
        EXPECT_EQ(view, T);
    }

    TEST(Camera, Constructor)
    {
        unsigned hsize = 160;
        unsigned vsize = 120;
        float fov = PI/2;
        Camera cam {hsize, vsize, fov};
        
        EXPECT_TRUE(cam.hsize == 160);
        EXPECT_TRUE(cam.vsize == 120);
        EXPECT_TRUE(Equal(cam.fov, PI/2));
        EXPECT_TRUE(cam.transform == Matrix::Identity);
    }

    TEST(Camera, HorizontalCanvas)
    {
        Camera cam {200, 125, PI/2};
        EXPECT_TRUE(Equal(cam.pixel_size, 0.01));
    }

    TEST(Camera, VerticalCanvas)
    {
        Camera cam {125, 200, PI/2};
        EXPECT_TRUE(Equal(cam.pixel_size, 0.01));
    }

    TEST(Camera, RayThroughCenter)
    {
        Camera cam {201, 101, PI/2};
        Ray ray = cam.RayForPixel(100, 50);
        EXPECT_TRUE(ray.origin == Point(0,0,0));
        EXPECT_TRUE(ray.direction == Vector(0,0,-1));
    }

    TEST(Camera, RayThroughCorner)
    {
        Camera cam {201, 101, PI/2};
        Ray ray = cam.RayForPixel(0, 0);
        EXPECT_TRUE(ray.origin == Point(0,0,0));
        EXPECT_TRUE(ray.direction == Vector(0.66519, 0.33259, -0.66851));
    }

    TEST(Camera, RayWithCameraTrasformed)
    {
        Camera cam {201, 101, PI/2};
        cam.transform = RotationY(PI/4) * Translation(0, -2, 5);
        Ray ray = cam.RayForPixel(100, 50);
        EXPECT_TRUE(ray.origin == Point(0,2,-5));
        EXPECT_TRUE(ray.direction == Vector(sqrt(2)/2, 0, -sqrt(2)/2));
    }

    TEST(Camera, RenderingWorld)
    {
        World world {World::Default};
        Camera cam {11, 11, PI/2};
        Point from {0,0,-5};
        Point to {0,0,0};
        Vector up {0,1,0};
        cam.transform = ViewTransform(from, to, up);
        Color result = cam.Render(world).At(5,5);
        EXPECT_TRUE(result == Color(0.38066, 0.47583, 0.2855));
    }
}