/**********************************************************************************
// Lighting (Arquivo de Cabeçalho)
//
// Criação:     17 Jul 2021
// Atualização:	26 Jul 2021
// Compilador:	Clang++ 12.0.5 / GNU g++ 9.3.0
//
// Descrição:	Define funções, tipos e estruturas de dados necessárias para
//              iluminação de uma cena. O método de Phong é utilizado para
//              o sombreamento de superfícies.
//
**********************************************************************************/

#ifndef RAY_TRACER_LIGHTING
#define RAY_TRACER_LIGHTING

#include "Types.h"
#include "Point.h"
#include "Vector.h"
#include "Color.h"

namespace RayTracer
{
    // declarações adiantadas
    struct Pattern;   
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
        Pattern * pattern;                          // padrão do material
        Color color;                                // cor do material
        double ambient;                             // intensidade da luz do ambiente
        double diffuse;                             // intensidade da reflexão da luz
        double specular;                            // intensidade do ponto de luz
        double shininess;                           // tamanho do reflexo do ponto de luz
        double reflective;                          // índice de reflectividade

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