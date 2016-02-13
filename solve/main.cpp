#include <iostream>
#include <stdlib.h> 
#include <cmath> 

using namespace std;

int main(int argc, const char* argv[])
{

	//Проверяем, что подано нужное количество аргументов 
	if (argc < 4)
	{
		cout << "Usage: <A> <B> <C>" << endl;
		return 0;
	}

	// Переводим в нужный нам формат числа из командной строки 
	double a = atof(argv[1]);
	double b = atof(argv[2]);
	double c = atof(argv[3]);


	if (!a) 
	{
		cout << "A=0" << endl;
		return 0;
	}

	double D = b * b - 4 * a * c;

	if (D < 0) 
	{
		cout << "There is not real root" << endl;
		return 0;
	}

	if (!D) 
	{
		cout << "x1= " << -b / (2 * a) << endl;
	}
	else 
	{
		double x1 = (-b + sqrt(D)) / (2 * a);
		double x2 = (-b - sqrt(D)) / (2 * a);
		cout << "x1= " << x1 << " x2= " << x2 << endl;
	}
	return 0;
}