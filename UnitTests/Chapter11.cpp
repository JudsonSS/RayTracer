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
        auto hit = PrepareComputations(i, ray); 
        EXPECT_EQ(hit.reflect, Vector(0, sqrt(2)/2, sqrt(2)/2));
    }

}