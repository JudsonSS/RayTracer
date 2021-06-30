/**********************************************************************************
// Sphere (Arquivo de Código Fonte)
//
// Criação:     29 Jun 2021
// Atualização:	30 Jun 2021
// Compilador:	Clang++ 12.0.5 / GNU g++ 9.3.0
//
// Descrição:	Aplicação desenha a sombra de uma esfera no plano. 
//              O traçamento de raios é feito a partir de um ponto fixo.
//
**********************************************************************************/

#include "Types.h"
#include "Canvas.h"
#include "Matrix.h"
#include "Geometry.h"
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
    Color red { 1,0,0 };
    Sphere shape;
    float world_x, world_y;
    vector<Intersection> intersections;

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
            Ray ray { origin, target - origin };
            intersections = shape.Intersect(ray);

            // se o raio atingiu a esfera
            if (Hit(intersections))
                canvas.Paint(x,y,red);
        }
    }

    canvas.Save("sphere.ppm");
}