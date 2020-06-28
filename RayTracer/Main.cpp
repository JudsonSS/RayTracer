#include <iostream>
#include "Types.h"

using namespace std;
using namespace RayTracer;

int main()
{

	Tuple t{ 4.3f, -4.2f, 3.1f, 1.0f };
	Point p{ 4.3f, -4.2f, 3.1f };
	Vector v{ 4.3f, -4.2f, 3.1f };

	cout << boolalpha << (p == t) << endl;
	cout << boolalpha << (v == t) << endl;
	return 0;
}