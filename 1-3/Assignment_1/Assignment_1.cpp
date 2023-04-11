#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cmath>
using namespace std;

#define PI 3.141592

int main()
{
	double degrees;
	double coor[3];

	cout << "Degrees : ";
	cin >> degrees;
	cout << "Coordinate : ";
	for (int i = 0; i < 3; i++)
		cin >> coor[i];

	double radian = degrees * PI / 180.0;


	double T[3][3] = { -cos(radian),sin(radian),0,
								sin(radian),cos(radian),0,
								0,0,0 };

	double re[3];

	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			T[i][j] *= 10000;
			T[i][j] = round(T[i][j]);
			T[i][j] /= 10000;
		}
	}

	for (int i = 0; i < 3; i++)
		re[i] = coor[i] * (T[i][0] + T[i][1] + T[i][2]);

	cout << endl << endl;
	for (int i = 0; i < 3; i++) {
		cout.width(10);
		cout << std::right << re[i];
	}
}