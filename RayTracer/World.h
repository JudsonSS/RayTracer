/**********************************************************************************
// World (Arquivo de Cabeçalho)
//
// Criação:		04 Jul 2021
// Atualização:	04 Jul 2021
// Compilador:	Clang++ 12.0.5 / GNU g++ 9.3.0
//
// Descrição:	Um mundo contém uma coleção de objetos e fontes de luz.
//
**********************************************************************************/

#ifndef RAY_TRACER_WORLD
#define RAY_TRACER_WORLD

#include <vector>
#include "Object.h"
#include "Ray.h"
using std::vector;

namespace RayTracer
{
	class World
	{
	private:
		vector<Object> objects;				// coleção de objetos
        vector<PointLight> lights;          // coleção de pontos de luzes
		
	public:
        const int Default = 1;              // configuração padrão do mundo 
        World(int config = 0);		        // construtor padrão
	};
}

#endif