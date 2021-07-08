/**********************************************************************************
// Object (Arquivo de Código Fonte)
//
// Criação:		26 Jun 2021
// Atualização:	04 Jul 2021
// Compilador:	Clang++ 12.0.5 / GNU g++ 9.3.0
//
// Descrição:	Define uma classe base para objetos 3D e classes para alguns 
//              objetos comuns como esferas, cubos, cilíndros, etc.
//
**********************************************************************************/

#include <cmath>
#include "Object.h"

namespace RayTracer
{
    // -------------------------------------------------------------------------------

    Object::Object()
        : type(UNKNOWN_T), 
          transform(Matrix::Identity) {}
        
    Object::~Object() {}

    // -------------------------------------------------------------------------------

    Sphere::Sphere()
        : center(Point{0,0,0}), radius(1)
    {
        type = SPHERE_T;
    }

    // -------------------------------------------------------------------------------

    vector<Intersection> Sphere::Intersect(Ray ray)
    {
        // aplica inversa da transformação da esfera
        // ao raio antes de testar a interseção
        ray = ray.Transform(transform.Inverse());

        // vetor do centro da esfera, posição (0,0,0), até a origem do raio
        Vector center_origin = ray.origin - Point{0, 0, 0};

        // coeficientes da equação do segundo grau: at2 + bt + c = 0
        float a = ray.direction.Dot(ray.direction);
        float b = 2 * ray.direction.Dot(center_origin);
        float c = center_origin.Dot(center_origin) - 1;

        // discriminante da equação do segundo grau
        float discriminant = b * b - 4 * a * c;

        // se o discriminante é negativo não há raízes reais
        if (discriminant < 0)
            return {};

        // existem duas raízes iguais
        // quando o discriminante é igual a zero
        // ou duas raízes diferentes se ele é positivo
        vector<Intersection> v;
        v.push_back(Intersection((-b - sqrt(discriminant)) / (2 * a), *this));
        v.push_back(Intersection((-b + sqrt(discriminant)) / (2 * a), *this));
        return v;
    }

    Vector Sphere::Normal(Point point_world)
    {
        // A transposta da inversa fornece o vetor normal 
        // correto após a transformação do objeto
        Matrix invT = transform.Inverse(); 
        Point point_object = invT * point_world;
        Vector normal_object = point_object - center;
        Vector normal_world = invT.Transpose() * normal_object;
        normal_world.w = 0;
        return normal_world.Normalized();
    }

    bool operator==(const Sphere &a, const Sphere &b)
    {
        if (a.type == b.type 
        && a.radius == b.radius 
        && a.center == b.center
        && a.material == b.material
        && a.transform == b.transform)
        {
            return true;
        }
        return false;
    }

    // -------------------------------------------------------------------------------
}