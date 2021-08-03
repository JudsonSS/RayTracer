/**********************************************************************************
// World (Arquivo de Cabeçalho)
//
// Criação:     04 Jul 2021
// Atualização:	17 Jul 2021
// Compilador:	Clang++ 12.0.5 / GNU g++ 9.3.0
//
// Descrição:	Um mundo contém uma coleção de objetos e fontes de luz.
//
**********************************************************************************/

#ifndef RAY_TRACER_WORLD
#define RAY_TRACER_WORLD

#include <vector>
#include "Shape.h"
#include "Canvas.h"
#include "Ray.h"
using std::vector;

namespace RayTracer
{
    // ---------------------------------------------------------------------------------------
    // HitData
    // ---------------------------------------------------------------------------------------

    struct HitData
    {
        double time;        // valor de distância ao longo do raio
        Shape * object;     // objeto em que ocorreu a interseção
        Point point;        // posição em coordenadas do mundo
        Point over_point;   // posição para cálculo da sombra
        Vector eye;         // vetor na direção do observador
        Vector normal;      // vetor normal no local da interseção 
        Vector reflect;     // vetor reflexão do raio com a normal
        bool inside;        // observador está dentro do objeto
    };

    // pré-calcula algumas informações para o sombreamento do ponto de interseção
    HitData PrepareComputations(Intersection &intersection, Ray &ray);

    // ---------------------------------------------------------------------------------------
    // Mundo
    // ---------------------------------------------------------------------------------------

    struct World
    {
        vector<Shape*> objects;			                        // coleção de objetos
        PointLight light;                                       // ponto de luz

        enum {Empty, Default};                                  // opções do construtor
        World(int config = Empty);		                        // construtor padrão

        bool Contains(Shape &obj);                              // mundo contém objeto        
        vector<Intersection> Intersect(Ray &r);                 // retorna pontos de interseção
        Color ShadeHit(HitData &hit, int remaining = 5);        // retorna cor no ponto de interseção
        Color ColorAt(Ray &r, int remaining = 5);               // retorna cor na interseção com o raio
        bool IsShadowed(Point &p);                              // retorna se o ponto está na sombra
        Color ReflectedColor(HitData &hit, int remaining = 5);  // retorna a cor refletida para a interseção
    };    

    // retorna matrix de transformação da câmera
    Matrix ViewTransform(const Point &from, const Point &to, const Vector &up);

    // ---------------------------------------------------------------------------------------
    // Camera
    // ---------------------------------------------------------------------------------------

    struct Camera
    {
        uint hsize;             // tamanho horizontal (em pixels)
        uint vsize;             // tamanho vertical (em pixels)
        double fov;             // field of view (ângulo em radianos)
        double pixel_size;      // tamanho de cada pixel
        double half_width;      // metade da largura (do mundo)
        double half_height;     // metade da altura (do mundo)
        Matrix transform;       // view transform matrix

        // construtor com valor padrão para a matrix de transformação
        Camera(uint horizontal, 
               uint vertical, 
               double field_of_view, 
               Matrix view_transform = Matrix::Identity); 
        
        // retorna raio que passa por (px,py)
        Ray RayForPixel(uint px, uint py);
        
        // retorna imagem da rederização do mundo 
        Canvas Render(World & world);
    };

    // ---------------------------------------------------------------------------------------
}

#endif