/**********************************************************************************
// Chapter9 (Arquivo de Código Fonte)
//
// Criação:     16 Jul 2021
// Atualização:	16 Jul 2021
// Compilador:	Clang++ 12.0.5 / GNU g++ 9.3.0
//
// Descrição:	Define os testes de unidade criados para o Capítulo 10,
//              Padrões, do livro "The Ray Tracer Challenge".
//              Os testes utilizam o framework GoogleTest.
//
**********************************************************************************/

#include <gtest/gtest.h>
#include "Color.h"
#include "Ray.h"
using namespace RayTracer;

namespace Chapter10
{
    TEST(Patterns, StripePattern)
    {
        Stripe pattern {Color::White, Color::Black};
        EXPECT_EQ(pattern.a, Color::White);
        EXPECT_EQ(pattern.b, Color::Black);
    }

    TEST(Patterns, StripeConstantY)
    {
        Stripe pattern {Color::White, Color::Black};
        EXPECT_EQ(pattern.At(Point(0,0,0)), Color::White);
        EXPECT_EQ(pattern.At(Point(0,1,0)), Color::White);
        EXPECT_EQ(pattern.At(Point(0,2,0)), Color::White);
    }

    TEST(Patterns, StripeConstantZ)
    {
        Stripe pattern {Color::White, Color::Black};
        EXPECT_EQ(pattern.At(Point(0,0,0)), Color::White);
        EXPECT_EQ(pattern.At(Point(0,0,1)), Color::White);
        EXPECT_EQ(pattern.At(Point(0,0,2)), Color::White);
    }

    TEST(Patterns, StripeAlternateX)
    {
        Stripe pattern {Color::White, Color::Black};
        EXPECT_EQ(pattern.At(Point(0,0,0)), Color::White);
        EXPECT_EQ(pattern.At(Point(0.9,0,0)), Color::White);
        EXPECT_EQ(pattern.At(Point(1,0,0)), Color::Black);
        EXPECT_EQ(pattern.At(Point(-0.1,0,0)), Color::Black);
        EXPECT_EQ(pattern.At(Point(-1,0,0)), Color::Black);
        EXPECT_EQ(pattern.At(Point(-1.1,0,0)), Color::White);
    }

    TEST(Patterns, LightingPattern)
    {
        Material m;
        Stripe listra {Color::White, Color::Black};
        m.pattern = &listra;
        m.ambient = 1;
        m.diffuse = 0;
        m.specular = 0;
        Vector eye {0,0,-1};
        Vector normal {0,0,-1};
        PointLight light { Point{0,0,-10}, Color{1,1,1} };

        Color c1 = Lighting(m, light, Point{0.9,0,0}, eye, normal, false);
        Color c2 = Lighting(m, light, Point{1.1,0,0}, eye, normal, false);

        EXPECT_EQ(c1, Color::White);
        EXPECT_EQ(c2, Color::Black);
    }
}