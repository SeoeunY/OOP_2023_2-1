#define CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<cmath>
using namespace std;

void value(float a, float b, float c)
{
    float  x_1, x_2, x, D;

    D = b*b - 4 * a * c;//판별식

    if (a == 0) {//이차방정식 성립 안함
        cout << "Unexpected factor of a quadratic term" << endl;
        return;
    }

    cout << "the roots of " << a << "x^2+" << b << "x+" << c << "=0 :" << endl;

    if (D > 0)//서로 다른 두 실근 가짐
    {
        x_1 = (-2 * c) / (b + sqrt(D));//뺄셈 오차 방지
        x_2 = (b + sqrt(D)) / (-2 * a);//근의 공식

        
        cout << "x_1:" << x_1 << endl << "x_2:" << x_2 << endl;
    }
    else if (D == 0)//중근
    {
        x = b / (-2 * a);
        cout << "x:" << x << " (double root)" << endl;
    }
    else///D<0, 허근 가짐
        cout << "The equation has no real number solutions." << endl;
}

int main()
{
    float a, b, c;

    cout << "enter a,b,c : ";
    cin >> a>>b>>c;

    value(a, b, c);

    return 0;
}