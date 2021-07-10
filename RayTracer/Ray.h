/**********************************************************************************
// Ray (Arquivo de Cabeçalho)
//
// Criação:     25 Jun 2021
// Atualização:	09 Jul 2021
// Compilador:	Clang++ 12.0.5 / GNU g++ 9.3.0
//
// Descrição:	Define a representação de um raio, 
//              a ser usada por um traçador de raios.
//
**********************************************************************************/

#ifndef RAY_TRACER_RAY
#define RAY_TRACER_RAY

#include "Types.h"
#include "Matrix.h"
#include <vector>
using std::vector;

namespace RayTracer
{
    // ---------------------------------------------------------------------------------------

    class Object;                                   // declaração adiantada

    // ---------------------------------------------------------------------------------------
    // Raio
    // ---------------------------------------------------------------------------------------

    struct Ray
    {
        Point origin;                               // ponto de origem do raio
        Vector direction;                           // direção do raio

        Ray(const Point &orig, const Vector &dir);  // construtor
        Point Position(double t) const;             // retorna posição na distância t ao longo do raio
        Ray Transform(const Matrix &m) const;       // retorna raio transformado pela matrix
    };

    // ---------------------------------------------------------------------------------------
    // Interseção
    // ---------------------------------------------------------------------------------------

    struct Intersection
    {           
        double time;                                // valor de distância ao longo do raio
        Object * object;                            // objeto em que ocorreu a interseção
        Intersection();                             // construtor padrão
        Intersection(double t, Object & obj);       // construtor com tempo e objeto
    };
    
    // comparação de igualdade entre interseções
    bool operator==(const Intersection &a, const Intersection &b);
    
    // comparação de menor entre interseções  
    bool operator<(const Intersection &a, const Intersection &b);

    // retorna interseção com menor valor não-negativo   
    Intersection Hit(vector<Intersection> &intersections);          

    // ---------------------------------------------------------------------------------------
    // Ponto de Luz
    // ---------------------------------------------------------------------------------------

    struct PointLight
    {
        Point position;                             // posição da luz
        Color intensity;                            // intensidade da luz
    };

    // comparação de igualdade entre pontos de luz
    bool operator==(const PointLight &a, const PointLight &b);

    // ---------------------------------------------------------------------------------------
    // Material
    // ---------------------------------------------------------------------------------------

    struct Material
    {
        Color color;                                // cor do material
        double ambient;                             // intensidade da luz do ambiente
        double diffuse;                             // intensidade da reflexão da luz
        double specular;                            // intensidade do ponto de luz
        double shininess;                           // tamanho do reflexo do ponto de luz
        Material();                                 // construtor padrão
    };

    // comparação de igualdade entre materiais
    bool operator==(const Material &a, const Material &b);
    
    // função de iluminação
    Color Lighting(const Material &material, 
                     const PointLight &light, 
                     const Point &point, 
                     const Vector &eye,
                     const Vector &normal,
                     bool shadow);

    // ---------------------------------------------------------------------------------------
}

#endif