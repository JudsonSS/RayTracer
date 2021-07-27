/**********************************************************************************
// Shape (Arquivo de Cabeçalho)
//
// Criação:     26 Jun 2021
// Atualização:	26 Jul 2021
// Compilador:	Clang++ 12.0.5 / GNU g++ 9.3.0
//
// Descrição:	Define uma classe base para as formas 3D e classes para algumas 
//              formas comuns como esferas, planos, cubos, cilíndros, etc.
//
**********************************************************************************/

#ifndef RAY_TRACER_SHAPE
#define RAY_TRACER_SHAPE

#include <vector>
#include "Types.h"
#include "Point.h"
#include "Vector.h"
#include "Matrix.h"
#include "Ray.h"
#include "Lighting.h"
using std::vector;

namespace RayTracer
{
    // -------------------------------------------------------------------------------------------------
    
    enum ShapeTypes
    {
        UNKNOWN_T,                                                      // desconhecido
        SPHERE_T,                                                       // esfera
        PLANE_T                                                         // plano
    };

    // -------------------------------------------------------------------------------------------------
    // Forma Geométrica
    // -------------------------------------------------------------------------------------------------

    class Shape
    {
    private:
        virtual vector<Intersection> ShapeIntersect(const Ray &r) = 0;  // retorna pontos de interseção
        virtual Vector ShapeNormal(const Point &p) = 0;                 // obtém a normal no ponto

    public:
        uint type;                                                      // identifica forma geométrica
        Matrix transform;                                               // matrix de transformação
        Material material;                                              // material da superfície

        Shape();                                                        // construtor padrão
        virtual ~Shape();                                               // destrutor da classe base
        vector<Intersection> Intersect(const Ray &r);                   // retorna pontos de interseção
        Vector Normal(const Point &p);                                  // obtém a normal no ponto P
    };

    // -------------------------------------------------------------------------------------------------
    // Esfera
    // -------------------------------------------------------------------------------------------------

    class Sphere : public Shape
    {
    private:
        Point center;                                                   // posição do centro 
        double radius;                                                  // tamanho do raio
        vector<Intersection> ShapeIntersect(const Ray &r);              // retorna pontos de interseção
        Vector ShapeNormal(const Point &p);                             // obtém a normal no ponto

    public:
        Sphere();                                                       // construtor padrão
        
        // compara igualdade de esferas
        friend bool operator==(const Sphere &a, const Sphere &b);
    };

    // -------------------------------------------------------------------------------------------------
    // Plano
    // -------------------------------------------------------------------------------------------------

    class Plane : public Shape
    {
    private:
        vector<Intersection> ShapeIntersect(const Ray &r);              // retorna pontos de interseção
        Vector ShapeNormal(const Point &p);                             // obtém a normal no ponto

    public:
        Plane();                                                        // construtor padrão
    };

    // -------------------------------------------------------------------------------------------------
}

#endif