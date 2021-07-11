/**********************************************************************************
// Chapter9 (Arquivo de Código Fonte)
//
// Criação:     10 Jul 2021
// Atualização:	10 Jul 2021
// Compilador:	Clang++ 12.0.5 / GNU g++ 9.3.0
//
// Descrição:	Define os testes de unidade criados para o Capítulo 9,
//              Planos, do livro "The Ray Tracer Challenge".
//              Os testes utilizam o framework GoogleTest.
//
**********************************************************************************/

#include <gtest/gtest.h>
#include <cmath>
#include "Object.h"
using namespace RayTracer;

namespace Chapter9
{
    TEST(Planes, DefaultTransformation)
    {
        class TestShape : public Object
        {
            vector<Intersection> ShapeIntersect(const Ray &r)
            { return vector<Intersection>(); }
            
            Vector ShapeNormal(const Point &p)
            { return Vector(); }
        };

        TestShape s;
        EXPECT_TRUE(s.transform == Matrix::Identity);
    }

    TEST(Planes, AssigningTransformation)
    {
        class TestShape : public Object
        {
            vector<Intersection> ShapeIntersect(const Ray &r)
            { return vector<Intersection>(); }
            
            Vector ShapeNormal(const Point &p)
            { return Vector(); }
        };

        TestShape s;
        s.transform = Translation(2,3,4);
        EXPECT_TRUE(s.transform == Translation(2,3,4));
    }

    TEST(Planes, DefaultMaterial)
    {
        class TestShape : public Object
        {
            vector<Intersection> ShapeIntersect(const Ray &r)
            { return vector<Intersection>(); }
            
            Vector ShapeNormal(const Point &p)
            { return Vector(); }
        };

        TestShape s;
        Material m = s.material;
        EXPECT_TRUE(m == Material());
    }

    TEST(Planes, AssigningMaterial)
    {
        class TestShape : public Object
        {
            vector<Intersection> ShapeIntersect(const Ray &r)
            { return vector<Intersection>(); }
            
            Vector ShapeNormal(const Point &p)
            { return Vector(); }
        };

        TestShape s;
        Material m;
        m.ambient = 1;
        s.material = m;
        EXPECT_TRUE(s.material == m);
    }

    TEST(Planes, IntersectScaledShape)
    {
        class TestShape : public Object
        {
        public:
            Ray saved_ray;
        
        private:
            vector<Intersection> ShapeIntersect(const Ray &r)
            { saved_ray = r; return vector<Intersection>(); }

            Vector ShapeNormal(const Point &p)
            { return Vector(); }
        };

        Ray ray { Point{0,0,-5}, Vector{0,0,1} };
        TestShape shape;
        shape.transform = Scaling(2,2,2);
        auto xs = shape.Intersect(ray);
        EXPECT_TRUE(shape.saved_ray.origin == Point(0,0,-2.5));
        EXPECT_TRUE(shape.saved_ray.direction == Vector(0,0,0.5));
    }
    
    TEST(Planes, IntersectTranslatedShape)
    {
        class TestShape : public Object
        {
        public:
            Ray saved_ray;
        
        private:
            vector<Intersection> ShapeIntersect(const Ray &r)
            { saved_ray = r; return vector<Intersection>(); }

            Vector ShapeNormal(const Point &p)
            { return Vector(); }
        };

        Ray ray { Point{0,0,-5}, Vector{0,0,1} };
        TestShape shape;
        shape.transform = Translation(5,0,0);
        auto xs = shape.Intersect(ray);
        EXPECT_TRUE(shape.saved_ray.origin == Point(-5,0,-5));
        EXPECT_TRUE(shape.saved_ray.direction == Vector(0,0,1));
    }

    TEST(Planes, NormalTranslatedShape)
    {
        class TestShape : public Object
        {
            vector<Intersection> ShapeIntersect(const Ray &r)
            { return vector<Intersection>(); }

            Vector ShapeNormal(const Point &p)
            { return Vector(p.x, p.y, p.z); }
        };

        TestShape shape;
        shape.transform = Translation(0,1,0);
        Vector n = shape.Normal(Point {0, 1.70711, -0.70711});
        EXPECT_TRUE(n == Vector(0, 0.70711, -0.70711));
    }
    
    TEST(Planes, NormalTransformedShape)
    {
        class TestShape : public Object
        {
            vector<Intersection> ShapeIntersect(const Ray &r)
            { return vector<Intersection>(); }

            Vector ShapeNormal(const Point &p)
            { return Vector(p.x, p.y, p.z); }
        };

        TestShape shape;
        shape.transform = Scaling(1,0.5,1) * RotationZ(PI/5);
        Vector n = shape.Normal(Point {0, sqrt(2)/2, -sqrt(2)/2});
        EXPECT_TRUE(n == Vector(0, 0.97014, -0.24254));
    }

    TEST(Planes, TheNormalIsConstant)
    {
        Plane plane;
        Vector n1 = plane.Normal(Point(0,0,0));
        Vector n2 = plane.Normal(Point(10,0,-10));
        Vector n3 = plane.Normal(Point(-5,0,150));
        EXPECT_TRUE(n1 == Vector(0,1,0));
        EXPECT_TRUE(n2 == Vector(0,1,0));
        EXPECT_TRUE(n3 == Vector(0,1,0));
    }

    TEST(Planes, IntersectRayParallel)
    {
        Plane plane;
        Ray ray { Point{0,10,0}, Vector{0,0,1} };
        auto xs = plane.Intersect(ray);
        EXPECT_TRUE(xs.size() == 0);
    }

    TEST(Planes, IntersectRayCoplanar)
    {
        Plane plane;
        Ray ray { Point{0,0,0}, Vector{0,0,1} };
        auto xs = plane.Intersect(ray);
        EXPECT_TRUE(xs.size() == 0);
    } 

    TEST(Planes, IntersectFromAbove)
    {
        Plane plane;
        Ray ray { Point{0,1,0}, Vector{0,-1,0} };
        auto xs = plane.Intersect(ray);
        EXPECT_TRUE(xs.size() == 1);
        EXPECT_TRUE(xs[0].time == 1);
        EXPECT_TRUE(xs[0].object == &plane);
    }   

    TEST(Planes, IntersectFromBelow)
    {
        Plane plane;
        Ray ray { Point{0,-1,0}, Vector{0,1,0} };
        auto xs = plane.Intersect(ray);
        EXPECT_TRUE(xs.size() == 1);
        EXPECT_TRUE(xs[0].time == 1);
        EXPECT_TRUE(xs[0].object == &plane);
    } 
}