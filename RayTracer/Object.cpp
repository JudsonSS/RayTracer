/**********************************************************************************
// Object (Arquivo de Código Fonte)
//
// Criação:     26 Jun 2021
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
    // ---------------------------------------------------------------------------------------
    // Objeto
    // ---------------------------------------------------------------------------------------


    Object::Object()
        : type(UNKNOWN_T), 
          transform(Matrix::Identity) {}
        
    Object::~Object() {}

    // ---------------------------------------------------------------------------------------

    vector<Intersection> Object::Intersect(const Ray &r)
    {
        // ao invés de calcular a interseção em coordenadas globais,
        // faz a transformada inversa sobre o raio, trazendo-o para as
        // coordenadas locais do objeto, antes de calcular a interseção
        Ray ray = r.Transform(transform.Inverse());

        // realiza os cáculos específicos de cada forma geométrica
        return ShapeIntersect(ray);
    }

    Vector Object::Normal(const Point &point)
    {
        // converte o ponto em coordenadas locais do objeto
        Matrix invT = transform.Inverse(); 
        Point local_point = invT * point;

        // realiza os cáculos específicos de cada forma geométrica
        Vector local_normal = ShapeNormal(local_point);

        // a transposta da inversa fornece a normal correta para o objeto transformado
        Vector world_normal = invT.Transpose() * local_normal;
        world_normal.w = 0;
        return world_normal.Normalized();
    }

    // ---------------------------------------------------------------------------------------
    // Esfera
    // ---------------------------------------------------------------------------------------

    Sphere::Sphere()
        : center(Point{0,0,0}), radius(1)
    {
        type = SPHERE_T;
    }

    // ---------------------------------------------------------------------------------------

    vector<Intersection> Sphere::ShapeIntersect(const Ray &ray)
    {
        // vetor do centro da esfera, posição (0,0,0), até a origem do raio
        Vector center_origin = ray.origin - Point{0, 0, 0};

        // coeficientes da equação do segundo grau: at2 + bt + c = 0
        double a = ray.direction.Dot(ray.direction);
        double b = 2 * ray.direction.Dot(center_origin);
        double c = center_origin.Dot(center_origin) - 1;

        // discriminante da equação do segundo grau
        double discriminant = b * b - 4 * a * c;

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

    // ---------------------------------------------------------------------------------------

    Vector Sphere::ShapeNormal(const Point &point)
    {
        return point - center;
    }

    // ---------------------------------------------------------------------------------------

    bool operator==(const Sphere &a, const Sphere &b)
    {
        if (a.type == b.type && 
            a.radius == b.radius && 
            a.center == b.center && 
            a.material == b.material && 
            a.transform == b.transform)

            return true;
        else
            return false;
    }

    // ---------------------------------------------------------------------------------------
    // Plano
    // ---------------------------------------------------------------------------------------

    Plane::Plane()
    {
        type = PLANE_T;
    }

    // ---------------------------------------------------------------------------------------

    vector<Intersection> Plane::ShapeIntersect(const Ray &ray)
    {
        // se a componente y é zero (ou muito próxima)
        // o raio é coplanar ou paralelo ao plano 
        if (abs(ray.direction.y) < EPSILON)
            return vector<Intersection>();
        
        // esse cálculo só funciona para o pleno em xz
        double t = -ray.origin.y / ray.direction.y;

        vector<Intersection> intersections;
        intersections.push_back(Intersection(t, *this));
        return intersections;
    }

    // ---------------------------------------------------------------------------------------

    Vector Plane::ShapeNormal(const Point &point)
    {
        return Vector{0,1,0};
    }

    // ---------------------------------------------------------------------------------------
}