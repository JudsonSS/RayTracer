/**********************************************************************************
// Test1 (Arquivo de Código Fonte)
//
// Criação:     27 Jun 2020
// Atualização:	10 Jul 2021
// Compilador:	Clang++ 12.0.5 / GNU g++ 9.3.0
//
// Descrição:	Define os testes de unidade criados no Capítulo 2, Desenhando
//              em um Canvas, do livro "The Ray Tracer Challenge". 
//              Os testes utilizam o framework GoogleTest.
//
**********************************************************************************/

#include <gtest/gtest.h>
#include <fstream>
#include <string>
#include "Types.h"
#include "Canvas.h"

using std::string;
using std::ifstream;
using namespace RayTracer;

namespace Chapter2
{
    TEST(Colors, ColorZero)
    {
        Color c;
        EXPECT_EQ(c.x, 0.0);
        EXPECT_EQ(c.y, 0.0);
        EXPECT_EQ(c.z, 0.0);
        EXPECT_EQ(c.w, 0.0);
    }
    
    TEST(Colors, ColorsAreTuples)
    {
        Color c{-0.5, 0.4, 1.7};
        EXPECT_EQ(c.x, -0.5);
        EXPECT_EQ(c.y, 0.4);
        EXPECT_EQ(c.z, 1.7);
    }

    TEST(Colors, AddColors)
    {
        Color c1{0.9, 0.6, 0.75};
        Color c2{0.7, 0.1, 0.25};
        Color r {1.6, 0.7, 1.0};

        Color add = c1 + c2;

        EXPECT_TRUE(r == add);
    }

    TEST(Colors, SubtractColors)
    {
        Color c1{0.9, 0.6, 0.75};
        Color c2{0.7, 0.1, 0.25};
        Color r {0.2, 0.5, 0.5};

        Color sub = c1 - c2;

        EXPECT_TRUE(r == sub);
    }

    TEST(Colors, ScaleColors)
    {
        Color c{0.2, 0.3, 0.4};
        Color r{0.4, 0.6, 0.8};

        EXPECT_TRUE(c * 2.0 == r);
        EXPECT_TRUE(2.0 * c == r);
    }

    TEST(Colors, MultiplyColors)
    {
        Color c1{1.0, 0.2, 0.4};
        Color c2{0.9, 1.0, 0.1};
        Color r{0.9, 0.2, 0.04};

        EXPECT_TRUE(c1 * c2 == r);
    }

    TEST(Canvas, Construction)
    {
        Canvas c {2, 3};
        Color black {0,0,0};
        
        EXPECT_EQ(c.Width(), 2);
        EXPECT_EQ(c.Height(), 3);

        EXPECT_TRUE(c.At(0,0) == black);
        EXPECT_TRUE(c.At(0,1) == black);
        EXPECT_TRUE(c.At(0,2) == black);
        EXPECT_TRUE(c.At(1,0) == black);
        EXPECT_TRUE(c.At(1,1) == black);
        EXPECT_TRUE(c.At(1,2) == black);
    }

    TEST(Canvas, Paint)
    {
        Canvas c {10, 20};
        Color red {1,0,0};
        c.Paint(2,3,red);
        
        EXPECT_TRUE(c.At(2,3) == red);
    }

    TEST(Canvas, HeaderPPM)
    {
        Canvas c {5,3};
        ASSERT_TRUE(c.Save("canvas.ppm"));

        ifstream fin;
        fin.open("canvas.ppm");
        ASSERT_TRUE(fin.is_open());
        string id;
        int width = 0, height = 0;
        int max_color = 0;
        fin >> id;
        fin >> width >> height;
        fin >> max_color;
        fin.close();

        EXPECT_EQ(id, "P3");
        EXPECT_EQ(width, 5);
        EXPECT_EQ(height, 3);
        EXPECT_EQ(max_color, 255);
    }

    TEST(Canvas, PixelDataPPM)
    {
        Canvas c {5,3};
        Color c1 { 1.5, 0, 0};
        Color c2 { 0, 0.5, 0};
        Color c3 { -0.5, 0, 1};

        c.Paint(0, 0, c1);
        c.Paint(2, 1, c2);
        c.Paint(4, 2, c3);

        ASSERT_TRUE(c.Save("canvas.ppm"));

        ifstream fin;
        fin.open("canvas.ppm");
        ASSERT_TRUE(fin.is_open());
        string id;
        int width = 0, height = 0;
        int max_color = 0;
        fin >> id;
        fin >> width >> height;
        fin >> max_color;
        fin.ignore();

        string line1, line2, line3;
        getline(fin, line1);
        getline(fin, line2);
        getline(fin, line3);
        fin.close();

        EXPECT_EQ(line1, "255 0 0 0 0 0 0 0 0 0 0 0 0 0 0 ");
        EXPECT_EQ(line2, "0 0 0 0 0 0 0 128 0 0 0 0 0 0 0 ");
        EXPECT_EQ(line3, "0 0 0 0 0 0 0 0 0 0 0 0 0 0 255 ");
    }

    TEST(Canvas, LongLinesPPM)
    {
        Canvas c {10,2};
        Color orange {1.0, 0.8, 0.6};

        for (int x=0; x<10; x++)
            for (int y=0; y<2; y++)
                c.Paint(x, y, orange);

        ASSERT_TRUE(c.Save("canvas.ppm"));

        ifstream fin;
        fin.open("canvas.ppm");
        ASSERT_TRUE(fin.is_open());
        string id;
        int width = 0, height = 0;
        int max_color = 0;
        fin >> id;
        fin >> width >> height;
        fin >> max_color;
        fin.ignore();

        string line1, line2, line3, line4;
        getline(fin, line1);
        getline(fin, line2);
        getline(fin, line3);
        getline(fin, line4);
        fin.close();

        EXPECT_EQ(line1, "255 204 153 255 204 153 255 204 153 255 204 153 255 204 153 255 204 ");
        EXPECT_EQ(line2, "153 255 204 153 255 204 153 255 204 153 255 204 153 ");
        EXPECT_EQ(line3, "255 204 153 255 204 153 255 204 153 255 204 153 255 204 153 255 204 ");
        EXPECT_EQ(line4, "153 255 204 153 255 204 153 255 204 153 255 204 153 ");
    }

    TEST(Canvas, NewLinePPM)
    {
        Canvas c {5,3};
        
        ASSERT_TRUE(c.Save("canvas.ppm"));

        ifstream fin;
        fin.open("canvas.ppm");
        ASSERT_TRUE(fin.is_open());
        char ch;
        
        while(fin.get(ch))
            continue;
        fin.close();

        EXPECT_EQ(ch, '\n');
    }
}
