/**********************************************************************************
// Test1 (Arquivo de Código Fonte)
//
// Criação:		27 Jun 2020
// Atualização:	04 Jul 2021
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
		EXPECT_EQ(c.x, 0.0f);
		EXPECT_EQ(c.y, 0.0f);
		EXPECT_EQ(c.z, 0.0f);
		EXPECT_EQ(c.w, 0.0f);
	}
	
	TEST(Colors, ColorsAreTuples)
	{
		Color c{-0.5f, 0.4f, 1.7f};
		EXPECT_EQ(c.x, -0.5f);
		EXPECT_EQ(c.y, 0.4f);
		EXPECT_EQ(c.z, 1.7f);
	}

	TEST(Colors, AddColors)
	{
		Color c1{0.9f, 0.6f, 0.75f};
		Color c2{0.7f, 0.1f, 0.25f};
		Color r{1.6f, 0.7f, 1.0f};

		Color add = c1 + c2;

		EXPECT_TRUE(r == add);
	}

	TEST(Colors, SubtractColors)
	{
		Color c1{0.9f, 0.6f, 0.75f};
		Color c2{0.7f, 0.1f, 0.25f};
		Color r{0.2f, 0.5f, 0.5f};

		Color sub = c1 - c2;

		EXPECT_TRUE(r == sub);
	}

	TEST(Colors, ScaleColors)
	{
		Color c{0.2f, 0.3f, 0.4f};
		Color r{0.4f, 0.6f, 0.8f};

		EXPECT_TRUE(c * 2.0f == r);
		EXPECT_TRUE(2.0f * c == r);
	}

	TEST(Colors, MultiplyColors)
	{
		Color c1{1.0f, 0.2f, 0.4f};
		Color c2{0.9f, 1.0f, 0.1f};
		Color r{0.9f, 0.2f, 0.04f};

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
		Color orange {1.0f, 0.8f, 0.6f};

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
