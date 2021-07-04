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
#include <algorithm>
using std::find;
using std::sort;

namespace RayTracer
{
    // -------------------------------------------------------------------------------

    World::World(int config)
    {
        if (config == World::Default)
        {
            lights.push_back(new PointLight{Point{-10,10,-10}, Color{1,1,1}});
            
            Sphere * s1 = new Sphere;
            s1->material.color = Color{0.8, 1.0, 0.6};
            s1->material.diffuse = 0.7;
            s1->material.specular = 0.2;
            
            Sphere * s2 = new Sphere;
            s2->transform = Scaling(0.5, 0.5, 0.5);

            objects.push_back(s1);
            objects.push_back(s2);
        }
    }

    World::~World()
    {
        for (Object * o : objects)
            delete o;

        for (PointLight * p : lights)
            delete p;
    }

    // -------------------------------------------------------------------------------

    unsigned World::Objects() const
    { return objects.size(); }

    unsigned World::Lights() const
    { return lights.size(); }

    // -------------------------------------------------------------------------------

    bool World::Contains(Object &obj)
    {
        for (Object * item : objects)
        {
            if (item->type == SPHERE_T && obj.type == SPHERE_T)
            {
                if (((Sphere &) *item) == ((Sphere &) obj))
                    return true;
            }
        }
        return false;
    }
    
    bool World::Contains(PointLight &light)
    {
        for (PointLight * item : lights)
        {
            if (*item == light)
                return true;
        }
        return false;
    }

    // -------------------------------------------------------------------------------

    vector<Intersection> World::Intersect(Ray r)
    {
        vector<Intersection> world_intersections;

        for (Object * obj : objects)
        {
            vector<Intersection> object_intersections = obj->Intersect(r);
            for (Intersection & i : object_intersections)
                world_intersections.push_back(i);
        }
        sort(world_intersections.begin(), world_intersections.end());
        return world_intersections;
    }
}