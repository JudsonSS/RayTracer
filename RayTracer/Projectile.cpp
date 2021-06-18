/**********************************************************************************
// Projectile (Arquivo de Código Fonte)
//
// Criação:		01 Jul 2020
// Atualização:	18 Jun 2021
// Compilador:	Clang++ 12.0.5 / GNU g++ 9.3.0
//
// Descrição:	Aplicação simula o disparo de um projétil estabelecendo uma 
//              posição e velocidade iniciais e calculando o efeito da gravidade  
//              e do vento sobre o projétil. O objetivo do programa é testar os 
//              tipos Tuple, Point e Vector.
//
**********************************************************************************/


#include <iostream>
#include "Types.h"
#include "Canvas.h"

using namespace std;
using namespace RayTracer;

struct Projectile
{
	Point position;
	Vector velocity;
};

struct Environment
{
	Vector gravity;
	Vector wind;
};

Projectile Tick(Environment e, Projectile p)
{
	Point position{ p.position + p.velocity };
	Vector velocity{ p.velocity + e.gravity + e.wind };
	Projectile proj{ position, velocity };
	return proj;
}

int main()
{

	// estado inicial do projétil
	Point start {0, 1, 0};
	Vector velocity { 1, 1.8, 0 };
	Projectile proj { start, velocity.Normalized() * 11.25 };

	// estado inicial do ambiente
	Vector gravity {0, -0.1f, 0};
	Vector wind {-0.01f, 0, 0};
	Environment env{ gravity, wind };

	// constrói canvas e cor de plotagem
	Canvas canvas {900, 550};
	Color red {1, 0, 0};

	unsigned tickCount = 0;
	do
	{
		proj = Tick(env, proj);
		++tickCount;
		canvas.Paint(proj.position.x, canvas.Height() - proj.position.y, red);
		cout << "Position after " << tickCount << ": (" << proj.position.x << ", " << proj.position.y << ", " << proj.position.z << ")\n";
	} 
	while (proj.position.y > 0);

	canvas.Save("canvas.ppm");
	cout << "Hit the ground with: " << tickCount << " ticks\n";
	
	return 0;
}
