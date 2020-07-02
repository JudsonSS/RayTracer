#include <iostream>
#include "Types.h"

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

	// projétil inicia um unidade acima do chão
	// velocidade é normalizada para 1 unidade/tick
	Projectile proj { Point(0, 1, 0), Vector(1, 1, 0).Normalized() };

	// gravidade é -0.1 unidades/tick, e vento é -0.01 unidades/tick
	Environment env{ Vector(0, -0.1f, 0), Vector(-0.01f, 0, 0) };

	unsigned tickCount = 0;

	do
	{
		proj = Tick(env, proj);
		++tickCount;
		
		cout << "Position after " << tickCount << ": (" << proj.position.x << ", " << proj.position.y << ", " << proj.position.z << ")\n";
	} 
	while (proj.position.y > 0);

	cout << "Hit the ground with: " << tickCount << " ticks\n";
	
	return 0;
}
