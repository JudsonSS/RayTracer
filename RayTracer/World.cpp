/**********************************************************************************
// World (Arquivo de Código Fonte)
//
// Criação:     04 Jul 2021
// Atualização:	17 Jul 2021
// Compilador:	Clang++ 12.0.5 / GNU g++ 9.3.0
//
// Descrição:	Um mundo contém uma coleção de objetos e fontes de luz.
//
**********************************************************************************/

#include "World.h"
#include <cmath>
#include <algorithm>
using std::find;
using std::sort;

namespace RayTracer
{
    // ---------------------------------------------------------------------------------------
    // HitData
    // ---------------------------------------------------------------------------------------

    HitData PrepareComputations(Intersection &intersection, Ray &ray)
    {
        HitData hit;
        hit.time = intersection.time;
        hit.object = intersection.object;
        hit.point = ray.Position(intersection.time);
        hit.eye = -ray.direction;
        hit.normal = hit.object->Normal(hit.point);
        hit.reflect = ray.direction.Reflect(hit.normal);
        hit.inside = false;

        // se os vetores tem direções opostas
        if (hit.normal.Dot(hit.eye) < 0)
        {
            hit.inside = true;
            hit.normal = -hit.normal;
        }

        hit.over_point = hit.point + hit.normal * EPSILON;
        return hit;
    }

    // ---------------------------------------------------------------------------------------
    // Mundo
    // ---------------------------------------------------------------------------------------

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

    // -------------------------------------------------------------------------------

    bool World::Contains(Shape &obj)
    {
        for (Shape * item : objects)
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

    vector<Intersection> World::Intersect(Ray &r)
    {
        vector<Intersection> world_intersections;

        for (Shape * obj : objects)
        {
            vector<Intersection> object_intersections = obj->Intersect(r);
            for (Intersection & i : object_intersections)
                world_intersections.push_back(i);
        }
        sort(world_intersections.begin(), world_intersections.end());
        return world_intersections;
    }

    // -------------------------------------------------------------------------------

    Color World::ShadeHit(HitData &hit)
    {
        bool shadowed = IsShadowed(hit.over_point);

        return Lighting(hit.object->material,
                        *hit.object,
                        light,
                        hit.over_point,
                        hit.eye,
                        hit.normal,
                        shadowed);
    }

    // -------------------------------------------------------------------------------

    Color World::ColorAt(Ray &r)
    {
        // se não há interseções do raio com o mundo
        vector<Intersection> intersections = Intersect(r);
        if (intersections.size() == 0)
            return Color {0,0,0};

        Intersection intersection = Hit(intersections);

        // se não há interseções válidas (t >= 0) 
        if (intersection.object == nullptr)
            return Color{0,0,0};

        HitData hit = PrepareComputations(intersection, r);
        return ShadeHit(hit);
    }

    // -------------------------------------------------------------------------------

    bool World::IsShadowed(Point &p)
    {
        Vector v = light.position - p;
        double distance = v.Magnitude();
        Vector direction = v.Normalized();
        Ray shadow_ray {p, direction};
        auto intersections = Intersect(shadow_ray);
        Intersection hit = Hit(intersections);
        
        if (hit.object != nullptr && hit.time < distance)
            return true;
        else
            return false;
    }

    // -------------------------------------------------------------------------------

    Matrix ViewTransform(const Point &from, const Point &to, const Vector &up)
    {
        Vector forward = Vector(to - from).Normalized();
        Vector left = forward.Cross(up.Normalized());
        Vector true_up = left.Cross(forward);
        Matrix orientation {4,4, 
            {
                left.x,     left.y,     left.z,    0,
                true_up.x,  true_up.y,  true_up.z, 0,
               -forward.x, -forward.y, -forward.z, 0,
                0,          0,          0,         1
            } 
        };

        return orientation * Translation(-from.x, -from.y, -from.z);
    }

    // ---------------------------------------------------------------------------------------
    // Camera
    // ---------------------------------------------------------------------------------------

    Camera::Camera(uint horizontal, uint vertical, double field_of_view, Matrix view_transform)
        : hsize(horizontal), vsize(vertical), fov(field_of_view), transform(view_transform) 
    {
        double half_view = tan(fov/2);
        double aspect = double(hsize)/vsize;

        if (aspect >= 1)
        {
            // aspecto horizontal
            // half_view é metade da largura
            half_width = half_view;
            half_height = half_view / aspect;
        }
        else
        {
            // aspecto vertical
            // half_view é metade da altura
            half_width = half_view * aspect;
            half_height = half_view;
        }

        pixel_size = (half_width * 2) / hsize;
    }

    // -------------------------------------------------------------------------------

    Ray Camera::RayForPixel(uint px, uint py)
    {
        // offset da borda da tela ao centro do pixel
        double x_offset = (px + 0.5) * pixel_size;
        double y_offset = (py + 0.5) * pixel_size;

        // coordenadas do pixel no espaço do mundo
        double world_x = half_width - x_offset;
        double world_y = half_height - y_offset;

        Matrix invTrans = transform.Inverse();
        Point pixel =  invTrans * Point(world_x, world_y, -1);
        Point origin = invTrans * Point(0,0,0);
        Vector direction = Vector(pixel - origin).Normalized();

        return Ray{origin, direction};
    }

    // -------------------------------------------------------------------------------

    Canvas Camera::Render(World & world)
    {
        Canvas image {hsize, vsize};
        for (uint y = 0; y < vsize - 1; ++y)
        {
            for (uint x = 0; x < hsize - 1; ++x)
            {
                Ray ray = RayForPixel(x,y);
                Color color = world.ColorAt(ray);
                image.Paint(x, y, color);
            }
        }
        return image;
    }

    // -------------------------------------------------------------------------------
}