/**********************************************************************************
// Plane (Arquivo de Código Fonte)
//
// Criação:     11 Jul 2021
// Atualização:	15 Jul 2021
// Compilador:	Clang++ 12.0.5 / GNU g++ 9.3.0
//
// Descrição:	Desenho de uma cena com um plano e três esferas. 
//              O traçamento de raios é feito a partir da câmera.
//
**********************************************************************************/

#include "Types.h"
#include "Canvas.h"
#include "Matrix.h"
#include "Object.h"
#include "World.h"
#include "Ray.h"
using namespace RayTracer;
using std::vector;

int main()
{
    Plane * floor = new Plane();
    floor->material.color = Color(1, 0.9, 0.9);
    floor->material.specular = 0;
    
    Sphere * middle = new Sphere();
    middle->transform = Translation(-0.5, 1, 0.5);
    middle->material.color = Color(1, 0, 0);
    middle->material.diffuse = 0.7;
    middle->material.specular = 0.3;

    Sphere * right = new Sphere();
    right->transform = Translation(1.5, 0.5, -0.5) * Scaling(0.5, 0.5, 0.5);
    right->material.color = Color(0, 1, 0);
    right->material.diffuse = 0.7;
    right->material.specular = 0.3;

    Sphere * left = new Sphere();
    left->transform = Translation(-1.5, 0.33, -0.75) * Scaling(0.33, 0.33, 0.33);
    left->material.color = Color(1, 1, 0);
    left->material.diffuse = 0.9;
    left->material.specular = 0.9;

    World world {World::Empty};
    world.objects.push_back(floor);
    world.objects.push_back(middle);
    world.objects.push_back(right);
    world.objects.push_back(left);
    world.light = PointLight{ Point{-10, 10, -10}, Color{1,1,1} };

    Camera camera {1000, 500, PI/3};
    camera.transform = ViewTransform(Point{0, 1.5, -5}, Point{0,1,0}, Vector{0,1,0});

    Canvas canvas = camera.Render(world);
    canvas.Save("plane.ppm");
}