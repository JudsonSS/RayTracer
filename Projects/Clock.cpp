/**********************************************************************************
// Clock (Arquivo de Código Fonte)
//
// Criação:     24 Jun 2021
// Atualização:	30 Jun 2021
// Compilador:	Clang++ 12.0.5 / GNU g++ 9.3.0
//
// Descrição:	Aplicação desenha o pano de fundo de um relógio. 
//              O objetivo é testar as matrizes de transformação.
//
**********************************************************************************/

#include "Types.h"
#include "Tuple.h"
#include "Point.h"
#include "Color.h"
#include "Canvas.h"
#include "Matrix.h"
using namespace RayTracer;

int main()
{
    Canvas canvas {300,300};
    Color white {1,1,1};
    Point center {canvas.Width()/2.0f, canvas.Height()/2.0f, 0};
    Point p {0,1,0};
    Point draw {0,0,0};
    float radius = 3.0f * canvas.Width() / 8.0f; 

    Matrix R = RotationZ(PI/6);
    Matrix S = Scaling(radius, radius, 0);
    Matrix T = Translation(center.x, center.y, 0);

    // ajusta escala do ponto inicial
    p = S * p;    

    for (int i=1; i<=12; ++i)
    {
        // posição de desenho é relativa ao centro do relógio
        draw = T * p;
        // desenha o ponto no canvas
        canvas.Paint(draw.x, draw.y, white);
        // rotaciona ponto
        p = R * p;
    }

    canvas.Save("clock.ppm");
    return 0;
}
