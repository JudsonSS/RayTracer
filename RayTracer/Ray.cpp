/**********************************************************************************
// Ray (Arquivo de Código Fonte)
//
// Criação:     25 Jun 2021
// Atualização:	15 Jul 2021
// Compilador:	Clang++ 12.0.5 / GNU g++ 9.3.0
//
// Descrição:	Define a representação de um raio, 
//              a ser usada por um traçador de raios.
//
**********************************************************************************/

#include <cmath>
#include <algorithm>
#include "Ray.h"
#include "Object.h"
using std::sort;

namespace RayTracer
{
    // ---------------------------------------------------------------------------------------
    // Raio
    // ---------------------------------------------------------------------------------------

    Ray::Ray()
        : origin(Point{0,0,0}), direction(Vector{0,0,0}) {}

    Ray::Ray(const Point &orig, const Vector &dir)
        : origin(orig), direction(dir) {}

    Point Ray::Position(double t) const
    { return origin + direction * t; }

    Ray Ray::Transform(const Matrix &m) const
    { return Ray {m * origin, m * direction}; }

    // ---------------------------------------------------------------------------------------
    // Interseção
    // ---------------------------------------------------------------------------------------

    Intersection::Intersection()
        : time(0), object(nullptr) {}

    Intersection::Intersection(double t, Object &obj)
        : time(t), object(&obj) {}

    bool operator==(const Intersection &a, const Intersection &b)
    { return (a.time == b.time) && (a.object == b.object); }

    bool operator<(const Intersection &a, const Intersection &b)
    { return a.time < b.time; }

    // ---------------------------------------------------------------------------------------

    Intersection Hit(vector<Intersection> &intersections)
    {
        for (auto &i : intersections)
        {
            if (i.time >= 0)
                return i;
        }
        return Intersection();
    }

    // ---------------------------------------------------------------------------------------
    // Ponto de Luz
    // ---------------------------------------------------------------------------------------

    bool operator==(const PointLight &a, const PointLight &b)
    {
        return (a.position == b.position && a.intensity == b.intensity);
    }

    // ---------------------------------------------------------------------------------------
    // Material
    // ---------------------------------------------------------------------------------------

    Material::Material()
        : pattern(nullptr),
          color(Color(1,1,1)), 
          ambient(0.1), 
          diffuse(0.9), 
          specular(0.9), 
          shininess(200.0) {}

    bool operator==(const Material &a, const Material &b)
    {
        return a.pattern == b.pattern &&
               a.color == b.color &&
               a.ambient == b.ambient &&
               a.diffuse == b.diffuse &&
               a.specular == b.specular &&
               a.shininess == b.shininess;
    }

    // ---------------------------------------------------------------------------------------

    Color Lighting(const Material &material,      // material da superfície
                   const PointLight &light,       // ponto de luz
                   const Point &point,            // ponto da superfície
                   const Vector &eye,             // direção do olho
                   const Vector &normal,          // normal da supercífie
                   bool position_in_shadow)       // posição está na sombra
    {
        Color surface_color;

        // se o material possui um padrão
        if (material.pattern)
            surface_color = material.pattern->At(point);
        else
            surface_color = material.color;

        // combina a cor da superfície com a cor da luz
        Color effective_color = surface_color * light.intensity;

        // calcula a contribuição do ambiente
        Color ambient = effective_color * material.ambient;

        // apenas o ambiente contribui para o cor final
        if (position_in_shadow)
            return ambient;        
        
        // encontra a direção para a fonte de luz
        Vector light_vector = Vector(light.position - point).Normalized();

        // representa o cosseno do ângulo entre o vetor da luz e o vetor normal
        // um número negativo quer dizer que a luz está atrás da superfície
        double light_dot_normal = light_vector.Dot(normal); 
        Color diffuse {0,0,0};
        Color specular {0,0,0};
        if (light_dot_normal >= 0)
        {
            // calcula a contribuição da reflexão difusa
            diffuse = effective_color * material.diffuse * light_dot_normal;

            // calcula vetor reflexão
            Vector in = -light_vector;
            Vector reflectv = in.Reflect(normal);

            // representa o cosseno do ângulo entre o vetor reflexão e o olho
            // um número negativo quer dizer que a luz reflete na direção oposta ao olho
            double reflect_dot_eye = reflectv.Dot(eye); 
            if (reflect_dot_eye >= 0) 
            {
                // calcula a contribuição especular
                double factor = pow(reflect_dot_eye, material.shininess);
                specular = light.intensity * material.specular * factor;
            }
        }

        return ambient + diffuse + specular;
    }

    // -------------------------------------------------------------------------------
}