/**********************************************************************************
// Test5 (Arquivo de Código Fonte)
//
// Criação:     25 Jun 2021
// Atualização:	10 Jul 2021
// Compilador:	Clang++ 12.0.5 / GNU g++ 9.3.0
//
// Descrição:	Define os testes de unidade criados para o Capítulo 5,
//              Interseções Raio-Esfera, do livro "The Ray Tracer Challenge".
//              Os testes utilizam o framework GoogleTest.
//
**********************************************************************************/

#include <gtest/gtest.h>
#include "Types.h"
#include "Ray.h"
#include "Matrix.h"
#include "Object.h"
using namespace RayTracer;

namespace Chapter5
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
        vector<Intersection> xs = s.Intersect(r);

        EXPECT_EQ(xs.size(), 2);
        EXPECT_EQ(xs[0].time, 5.0);
        EXPECT_EQ(xs[1].time, 5.0);
    }

    TEST(Ray, NoIntersection)
    {
        Ray r {Point(0,2,-5), Vector(0,0,1)};
        Sphere s;
        vector<Intersection> xs = s.Intersect(r);
        EXPECT_EQ(xs.size(), 0);
    }

    TEST(Ray, InsideSphere)
    {
        Ray r {Point(0,0,0), Vector(0,0,1)};
        Sphere s;
        vector<Intersection> xs = s.Intersect(r);
        
        EXPECT_EQ(xs.size(), 2);
        EXPECT_EQ(xs[0].time, -1.0);
        EXPECT_EQ(xs[1].time, 1.0);
    }

    TEST(Ray, AfterSphere)
    {
        Ray r {Point(0,0,5), Vector(0,0,1)};
        Sphere s;
        vector<Intersection> xs = s.Intersect(r);
        
        EXPECT_EQ(xs.size(), 2);
        EXPECT_EQ(xs[0].time, -6.0);
        EXPECT_EQ(xs[1].time, -4.0);
    }

    TEST(Ray, ObjectIntersection)
    {
        Sphere s;
        Intersection i {3.5,s};
        
        EXPECT_EQ(i.time, 3.5);
        EXPECT_EQ(i.object, &s);
    }	

    TEST(Ray, AgregatingIntersection)
    {
        Sphere s;
        Intersection i1 {1,s};
        Intersection i2 {2,s};
        vector<Intersection> intersections;
        intersections.push_back(i1);
        intersections.push_back(i2);
        
        EXPECT_EQ(intersections.size(), 2);
        EXPECT_EQ(intersections[0].time, 1);
        EXPECT_EQ(intersections[1].time, 2);
    }

    TEST(Ray, SetObjectOnIntersection)
    {
        Ray r {Point(0,0,-5), Vector(0,0,1)};
        Sphere s;
        vector<Intersection> xs = s.Intersect(r);

        EXPECT_EQ(xs.size(), 2);
        EXPECT_EQ(xs[0].object, &s);
        EXPECT_EQ(xs[1].object, &s);
    }   

    TEST(Ray, HitAllPositive)
    {
        Sphere s;
        Intersection i1 {1,s};
        Intersection i2 {2,s};
        vector<Intersection> xs {i1,i2};
        Intersection i = Hit(xs); 
        EXPECT_TRUE(i == i1);
    }

    TEST(Ray, HitSomeNegative)
    {
        Sphere s;
        Intersection i1 {-1,s};
        Intersection i2 {1,s};
        vector<Intersection> xs {i2,i1};
        Intersection i = Hit(xs); 
        EXPECT_TRUE(i == i2);
    }

    TEST(Ray, HitAllNegative)
    {
        Sphere s;
        Intersection i1 {-2,s};
        Intersection i2 {-1,s};
        vector<Intersection> xs {i2,i1};
        Intersection i = Hit(xs); 
        EXPECT_EQ(i.object, nullptr);
    }

    TEST(Ray, HitAlwaysLowest)
    {
        Sphere s;
        Intersection i1 {5,s};
        Intersection i2 {7,s};
        Intersection i3 {-3,s};
        Intersection i4 {2,s};
        vector<Intersection> xs {i1,i2,i3,i4};
        sort(xs.begin(), xs.end());
        Intersection i = Hit(xs); 
        EXPECT_TRUE(i == i4);
    }

    TEST(Ray, TranslatingRay)
    {
        Ray r {Point(1,2,3), Vector(0,1,0)};
        Matrix T = Translation(3,4,5);
        Ray r2 = r.Transform(T);
        EXPECT_TRUE(r2.origin == Point(4,6,8));
        EXPECT_TRUE(r2.direction == Vector(0,1,0));
    }

    TEST(Ray, ScalingRay)
    {
        Ray r {Point(1,2,3), Vector(0,1,0)};
        Matrix T = Scaling(2,3,4);
        Ray r2 = r.Transform(T);
        EXPECT_TRUE(r2.origin == Point(2,6,12));
        EXPECT_TRUE(r2.direction == Vector(0,3,0));
    }

    TEST(Ray, SphereDefaultTransform)
    {
        Sphere s;
        EXPECT_TRUE(s.transform == Matrix::Identity);
    }

    TEST(Ray, ChangingSphereTransform)
    {
        Sphere s;
        Matrix T = Translation(2,3,4);
        s.transform = T;
        EXPECT_TRUE(s.transform == T);
    }

    TEST(Ray, IntersectScaledSphere)
    {
        Ray r {Point(0,0,-5), Vector(0,0,1)};
        Sphere s;
        s.transform = Scaling(2,2,2);
        vector<Intersection> xs = s.Intersect(r);

        EXPECT_EQ(xs.size(), 2);
        EXPECT_EQ(xs[0].time, 3);
        EXPECT_EQ(xs[1].time, 7);
    }

    TEST(Ray, IntersectTranslatedSphere)
    {
        Ray r {Point(0,0,-5), Vector(0,0,1)};
        Sphere s;
        s.transform = Translation(5,0,0);
        vector<Intersection> xs = s.Intersect(r);
        EXPECT_EQ(xs.size(), 0);
    }
}