/**********************************************************************************
// Test6 (Arquivo de Código Fonte)
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
#include <cmath>
#include "Types.h"
#include "Ray.h"
#include "Matrix.h"
#include "Object.h"
using namespace RayTracer;

namespace Chapter6
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
        Vector n = s.Normal(Point(0, sqrt(2)/2, -sqrt(2)/2));
        EXPECT_TRUE(n == Vector(0, 0.97014, -0.24254));
	}

    TEST(Reflection, Reflect45)
	{
        Vector v {1, -1, 0};
        Vector n {0, 1, 0};
        Vector r = v.Reflect(n);
        EXPECT_TRUE(r == Vector(1, 1, 0));
	}

    TEST(Reflection, ReflectSlanted)
	{
        Vector v {0, -1, 0};
        Vector n (sqrt(2)/2, sqrt(2)/2, 0);
        Vector r = v.Reflect(n);
        EXPECT_TRUE(r == Vector(1, 0, 0));
	}

    TEST(Reflection, PointLight)
	{
        Color intensity {1, 1, 1};
        Point position {0,0,0};
        PointLight light {position, intensity};
        EXPECT_TRUE(light.position == position);
        EXPECT_TRUE(light.intensity == intensity);
	}

    TEST(Reflection, DefaultMaterial)
	{
        Material m;
        EXPECT_TRUE(m.color == Color(1,1,1));
        EXPECT_TRUE(m.ambient == 0.1f);
        EXPECT_TRUE(m.diffuse == 0.9f);
        EXPECT_TRUE(m.specular == 0.9f);
        EXPECT_TRUE(m.shininess == 200.0f);
	}

    TEST(Reflection, SphereDefaults)
	{
        Sphere s;
        EXPECT_TRUE(s.material == Material());
	}

    TEST(Reflection, SphereMaterial)
	{
        Sphere s;
        Material m;
        m.ambient = 1;
        s.material = m;
        EXPECT_TRUE(s.material == m);
	}

    TEST(Lighting, LightEyeSurface)
	{
        Material m;
        Point position {0,0,0}; 
        Vector eye {0,0,-1};
        Vector normal {0,0,-1};
        PointLight light {Point(0,0,-10), Color(1,1,1)};
        Color result = Lighting(m, light, position, eye, normal);
        EXPECT_TRUE(result == Color(1.9, 1.9, 1.9));
	}

    TEST(Lighting, LightEye45Surface)
	{
        Material m;
        Point position {0,0,0}; 
        Vector eye (0, sqrt(2)/2, -sqrt(2)/2); 
        Vector normal {0,0,-1};
        PointLight light {Point(0,0,-10), Color(1,1,1)};
        Color result = Lighting(m, light, position, eye, normal);
        EXPECT_TRUE(result == Color(1.0, 1.0, 1.0));
	}

    TEST(Lighting, Light45EyeSurface)
	{
        Material m;
        Point position {0,0,0}; 
        Vector eye {0, 0, -1}; 
        Vector normal {0,0,-1};
        PointLight light {Point(0,10,-10), Color(1,1,1)};
        Color result = Lighting(m, light, position, eye, normal);
        EXPECT_TRUE(result == Color(0.7364, 0.7364, 0.7364));
	}

    TEST(Lighting, Light45Eye45Surface)
	{
        Material m;
        Point position {0,0,0}; 
        Vector eye (0, -sqrt(2)/2, -sqrt(2)/2);
        Vector normal {0,0,-1};
        PointLight light {Point(0,10,-10), Color(1,1,1)};
        Color result = Lighting(m, light, position, eye, normal);
        EXPECT_EQ(result, Color(1.63638, 1.63638, 1.63638));
	}

    TEST(Lighting, LightBehindSurface)
	{
        Material m;
        Point position {0,0,0}; 
        Vector eye {0,0,-1};
        Vector normal {0,0,-1};
        PointLight light {Point(0,0,10), Color(1,1,1)};
        Color result = Lighting(m, light, position, eye, normal);
        EXPECT_TRUE(result == Color(0.1, 0.1, 0.1));
	}
}