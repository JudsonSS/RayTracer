/**********************************************************************************
// World (Arquivo de Código Fonte)
//
// Criação:		04 Jul 2021
// Atualização:	08 Jul 2021
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

    HitData PrepareComputations(Intersection &intersection, Ray &ray)
    {
        HitData comps;
        comps.time = intersection.time;
        comps.object = intersection.object;
        comps.point = ray.Position(intersection.time);
        comps.eye = -ray.direction;
        comps.normal = comps.object->Normal(comps.point);
        comps.inside = false;

        // se os vetores tem direções opostas
        if (comps.normal.Dot(comps.eye) < 0)
        {
            comps.inside = true;
            comps.normal = -comps.normal;
        }
        
        return comps;
    }

    // -------------------------------------------------------------------------------

    World::World(int config)
    {
        if (config == World::Default)
        {
            light = PointLight{Point{-10,10,-10}, Color{1,1,1}};
            
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
        for (Object * obj : objects)
            delete obj;
    }

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

    Color World::ShadeHit(HitData hit)
    {
        return Lighting(hit.object->material,
                        light,
                        hit.point,
                        hit.eye,
                        hit.normal);
    }

    Color World::ColorAt(Ray r)
    {
        vector<Intersection> intersections = Intersect(r);
        if (intersections.size() == 0)
            return Color {0,0,0};

        Intersection intersection = Hit(intersections);
        HitData hit = PrepareComputations(intersection, r);
        return ShadeHit(hit);
    }

    // -------------------------------------------------------------------------------
}