#include <iostream>
#include "Types.h"

using namespace std;
using namespace RayTracer;

int main()
{

	Point p{ 3.0f, 2.0f, 1.0f };
	Vector v{ 5.0f, 6.0f, 7.0f };
	Point q{ -2.0f, -4.0f, -6.0f };

	cout << boolalpha << (q == p - v) << endl;
	
	return 0;
}