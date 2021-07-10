/**********************************************************************************
// Object (Arquivo de Cabeçalho)
//
// Criação:		26 Jun 2021
// Atualização:	04 Jul 2021
// Compilador:	Clang++ 12.0.5 / GNU g++ 9.3.0
//
// Descrição:	Define uma classe base para objetos 3D e classes para alguns 
//              objetos comuns como esferas, cubos, cilíndros, etc.
//
**********************************************************************************/

#ifndef RAY_TRACER_OBJECT
#define RAY_TRACER_OBJECT

#include <vector>
#include "Ray.h"
#include "Matrix.h"
using std::vector;

namespace RayTracer
{
    // ---------------------------------------------------------------------------------------
    
    enum ObjectTypes
    {
        UNKNOWN_T,                                                  // desconhecido
        SPHERE_T                                                    // esfera
    };

    // ---------------------------------------------------------------------------------------
	// Objeto
	// ---------------------------------------------------------------------------------------

    struct Object
    {
        unsigned type;                                              // tipo do objeto 
        Matrix transform;                                           // matrix de transformação
        Material material;                                          // material da superfície

        Object();                                                   // construtor padrão
        virtual ~Object();                                          // destrutor da classe base
        virtual vector<Intersection> Intersect(const Ray &r) = 0;   // retorna pontos de interseção
        virtual Vector Normal(const Point &p) = 0;                  // obtém a normal no ponto P
    };

    // ---------------------------------------------------------------------------------------
	// Esfera
	// ---------------------------------------------------------------------------------------

    class Sphere : public Object
    {
    private:
        Point center;                                               // posição do centro 
        double radius;                                              // tamanho do raio

    public:
        Sphere();                                                   // construtor padrão
        vector<Intersection> Intersect(const Ray &r);               // retorna pontos de interseção
        Vector Normal(const Point &p);                              // obtém a normal no ponto P
        
        // compara igualdade de esferas
        friend bool operator==(const Sphere &a, const Sphere &b);
    };

    // ---------------------------------------------------------------------------------------
}

#endif