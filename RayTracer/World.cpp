/**********************************************************************************
// World (Arquivo de Código Fonte)
//
// Criação:		04 Jul 2021
// Atualização:	04 Jul 2021
// Compilador:	Clang++ 12.0.5 / GNU g++ 9.3.0
//
// Descrição:	Um mundo contém uma coleção de objetos e fontes de luz.
//
**********************************************************************************/

#include "World.h"

namespace RayTracer
{
    // -------------------------------------------------------------------------------

    World::World(int config)
    {
        if (config == World::Default)
        {
            lights.push_back(PointLight{Point{-10,10,-10}, Color{1,1,1}});
            
            Sphere s1;
            s1.material.color = Color{0.8, 1.0, 0.6};
            s1.material.diffuse = 0.7;
            s1.material.specular = 0.2;
            
            Sphere s2;
            s2.transform = Scaling(0.5, 0.5, 0.5);

            objects.push_back(s1);
            objects.push_back(s2);
        }
    }

    // -------------------------------------------------------------------------------

}