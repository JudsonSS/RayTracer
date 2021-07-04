/**********************************************************************************
// Ray (Arquivo de Código Fonte)
//
// Criação:		25 Jun 2021
// Atualização:	03 Jul 2021
// Compilador:	Clang++ 12.0.5 / GNU g++ 9.3.0
//
// Descrição:	Define a representação de um raio, 
//              a ser usada por um traçador de raios.
//
**********************************************************************************/

#include <cmath>
#include <algorithm>
#include "Ray.h"
using std::sort;

namespace RayTracer
{
    // -------------------------------------------------------------------------------

    Ray::Ray(Point orig, Vector dir)
        : origin(orig), direction(dir) {}

    Point Ray::Position(float t)
    { return origin + direction * t; }

    Ray Ray::Transform(Matrix m)
    { return Ray {m * origin, m * direction}; }

    // -------------------------------------------------------------------------------

    Intersection::Intersection(float t, Object &obj)
        : time(t), object(&obj) {}

    bool operator==(const Intersection &a, const Intersection &b)
    {
        return (a.time == b.time) && (a.object == b.object);
    }

    bool operator<(const Intersection &a, const Intersection &b)
    {
        return a.time < b.time;
    }

    // -------------------------------------------------------------------------------

    Intersection * Hit(vector<Intersection> & intersections)
    {
        sort(intersections.begin(), intersections.end());

        for (auto &i : intersections)
        {
            if (i.time >= 0)
                return &i;
        }
        return nullptr;
    }

    // -------------------------------------------------------------------------------

    Material::Material()
        : color(Color(1,1,1)), 
          ambient(0.1f), 
          diffuse(0.9f), 
          specular(0.9f), 
          shininess(200.0f) {}

    bool operator==(const Material &a, const Material &b)
    {
        return a.color == b.color &&
               a.ambient == b.ambient &&
               a.diffuse == b.diffuse &&
               a.specular == b.specular &&
               a.shininess == b.shininess;
    }

    Color Lighting(const Material &material,      // material da superfície
                     const PointLight &light,       // ponto de luz
                     const Point &point,            // ponto da superfície
                     const Vector &eye,             // direção do olho
                     const Vector &normal)          // normal da supercífie
    {
        // combina a cor da superfície com a cor da luz
        Color effective_color = material.color * light.intensity;

        // encontra a direção para a fonte de luz
        Vector lightv = Vector(light.position - point).Normalized();

        // calcula a contribuição do ambiente
        Color ambient = effective_color * material.ambient;

        // representa o cosseno do ângulo entre o vetor da luz e o vetor normal
        // um número negativo quer dizer que a luz está atrás da superfície
        float light_dot_normal = lightv.Dot(normal); 
        Color diffuse {0,0,0};
        Color specular {0,0,0};
        if (light_dot_normal >= 0)
        {
            // calcula a contribuição da reflexão difusa
            diffuse = effective_color * material.diffuse * light_dot_normal;

            // calcula vetor reflexão
            Vector in = -lightv;
            Vector reflectv = in.Reflect(normal);

            // representa o cosseno do ângulo entre o vetor reflexão e o olho
            // um número negativo quer dizer que a luz reflete na direção oposta ao olho
            float reflect_dot_eye = reflectv.Dot(eye); 
            if (reflect_dot_eye >= 0) 
            {
                // calcula a contribuição especular
                float factor = pow(reflect_dot_eye, material.shininess);
                specular = light.intensity * material.specular * factor;
            }
        }

        return ambient + diffuse + specular;
    }

    // -------------------------------------------------------------------------------
}