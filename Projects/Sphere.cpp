/**********************************************************************************
// Sphere (Arquivo de Código Fonte)
//
// Criação:     29 Jun 2021
// Atualização:	17 Jul 2021
// Compilador:	Clang++ 12.0.5 / GNU g++ 9.3.0
//
// Descrição:	Aplicação desenha a silhueta de uma esfera no plano. 
//              O traçamento de raios é feito a partir de um ponto fixo.
//
**********************************************************************************/

#include "Types.h"
#include "Canvas.h"
#include "Matrix.h"
#include "Shape.h"
#include "Ray.h"
using namespace RayTracer;
using std::vector;

int main()
{
    Point origin {0,0,-4};
    float wall_z = 10;
    float wall_size = 10;
    unsigned canvas_size = 500;
    float pixel_size = wall_size / canvas_size;
    float half_size = wall_size / 2;

    Canvas canvas { canvas_size, canvas_size }; 
    Sphere shape; shape.material.color = Color(1, 0.2, 1);
    PointLight light { Point{-10, 10, -10}, Color{1,1,1} };
    vector<Intersection> intersections;
    float world_x, world_y;
    
    // para cada linha de pixels no canvas
    for (int y = 0; y < canvas_size; y++)
    {
        world_y = half_size - pixel_size * y;

        // para cada pixel na linha
        for (int x = 0; x < canvas_size; x++)
        {
            world_x = -half_size + pixel_size * x;

            // posição alvo do raio na parede
            Point target { world_x, world_y, wall_z };
            Vector direction = Vector(target - origin).Normalized();

            Ray ray { origin, direction };
            intersections = shape.Intersect(ray);
            Intersection hit = Hit(intersections);

            // se o raio atingiu a esfera
            if (hit.object)
            {
                Point hit_point = ray.Position(hit.time);
                Vector hit_normal = shape.Normal(hit_point);
                Vector eye = -ray.direction;
                Color color = Lighting(shape.material, shape, light, hit_point, eye, hit_normal, false);
                canvas.Paint(x,y,color);
            }
        }
    }

    canvas.Save("sphere.ppm");
}