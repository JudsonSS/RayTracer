/**********************************************************************************
// Light (Arquivo de Cabeçalho)
//
// Criação:     17 Jul 2021
// Atualização:	17 Jul 2021
// Compilador:	Clang++ 12.0.5 / GNU g++ 9.3.0
//
// Descrição:	Define a representação de um ponto de luz e os dados necessários 
//              para calcular o sombreamento de uma superfície com base no 
//              método de Phong.
//
**********************************************************************************/

#ifndef RAY_TRACER_LIGHT
#define RAY_TRACER_LIGHT

#include "Types.h"
#include "Point.h"
#include "Vector.h"
#include "Color.h"

namespace RayTracer
{
    // declarações adiantadas
    struct Stripe;   
    class  Shape;                               

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
        Stripe * pattern;                           // padrão do material
        Color color;                                // cor do material
        double ambient;                             // intensidade da luz do ambiente
        double diffuse;                             // intensidade da reflexão da luz
        double specular;                            // intensidade do ponto de luz
        double shininess;                           // tamanho do reflexo do ponto de luz

        Material();                                 // construtor padrão
    };

    // comparação de igualdade entre materiais
    bool operator==(const Material &a, const Material &b);
    
    // ---------------------------------------------------------------------------------------
    // Iluminação
    // ---------------------------------------------------------------------------------------

    // função de iluminação
    Color Lighting(const Material &material,        // material da superfície
                   const Shape &shape,              // forma geométrica 
                   const PointLight &light,         // ponto de luz
                   const Point &point,              // ponto da superfície
                   const Vector &eye,               // direção do olho
                   const Vector &normal,            // normal da supercífie
                   bool position_in_shadow);        // posição está na sombra

    // ---------------------------------------------------------------------------------------
}

#endif