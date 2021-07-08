/**********************************************************************************
// World (Arquivo de Cabeçalho)
//
// Criação:		04 Jul 2021
// Atualização:	08 Jul 2021
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
    struct HitData
    {
        float time;                             // valor de distância ao longo do raio
        Object * object;                        // objeto em que ocorreu a interseção
        Point point;                            // posição em coordenadas do mundo
        Vector eye;                             // vetor na direção do observador
        Vector normal;                          // vetor normal no local da interseção 
        bool inside;                            // observador está dentro do objeto
    };

    // pré-calcula algumas informações para o sombreamento do ponto de interseção
    HitData PrepareComputations(Intersection &intersection, Ray &ray);

	struct World
	{
		vector<Object*> objects;			    // coleção de objetos
        PointLight light;                       // ponto de luz

        enum {Empty, Default};                  // opções do construtor
        World(int config = Empty);		        // construtor padrão
        ~World();                               // destrutor

        bool Contains(Object &obj);             // mundo contém objeto        
        vector<Intersection> Intersect(Ray r);  // retorna pontos de interseção
        Color ShadeHit(HitData hit);            // retorna cor no ponto de interseção
        Color ColorAt(Ray r);                   // retorna cor na interseção com o raio
	};    

    // retorna matrix de transformação da câmera
    Matrix ViewTransform(Point from, Point to, Vector up);
}

#endif