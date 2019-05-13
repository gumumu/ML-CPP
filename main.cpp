#include <iostream>
#include <stdlib.h>
#include "Matrix.h"
#include "LinearRegression.h"
#include "SGDRegression.h"
#include "PolynomialFeatures.h"

using namespace std;

int main(void)
{
	srand((unsigned int)time(NULL));
	double a[16] = {
		1,2,3,3,4,6,4,6,9,12,24,56,78,89,32,11
	};
	double b[16] = {
		21,13,11,54,5,42,66,19,17,87,63,34,35,53,21,26
	};
	try
	{
		Matrix x(a, 8, 2);
		Matrix x2(b, 8, 2);
		Matrix y(8, 1);
		Matrix y2(8, 1);
		for (int i = 0; i < x.getRowNum(); i++)
		{
			y.set(i, 0, x.get(i, 0) * 4 + x.get(i, 1) * 7 + 48 + (-1 + rand() % 2));
		}
		for (int i = 0; i < x2.getRowNum(); i++)
		{
			y2.set(i, 0, x2.get(i, 0) * 4 + x2.get(i, 1) * 7 + 48);
		}
		
		long epochs = 100000;
		double learning_rate = 0.0004;
		double decay_rate = 0.0;
		double momentum = 0.9;
		SGDRegression lr(learning_rate, decay_rate, momentum, false);
		lr.fit(x, y, epochs, 8, 0.0001);
		//LinearRegression lr;
		//lr.fit(x, y);
		
		cout << lr.predict(x2);
		cout << y2;

		cout <<"score:"<< lr.score(x2, y2);
	}
	catch (const char *e)
	{
		cout << e;
	}
	cout << endl;
	getchar();
	return 0;
}