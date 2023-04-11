#define CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cmath>
using namespace std;

long long LCM(int a, int b)//최소공배수 함수
{
	if (a <= b) {//입력받은 정수 크기 비교
		int temp = a;
		a = b;
		b = temp;
	}
	//a>b

	if (a == 0 || b == 0) {//예외처리
		cout << "GCD is 0. LCM not exist";
		return 0;
	}

	long long c = (long long)a;//정수 형변환
	long long d = (long long)b;

	long long k=1;
	while (k != 0) {//유클리드 호제법
		k = c % d;
		c = d;
		d = k;
	}
	
	long long GCD = c;//최대공약수

	long long LCM = (long long)a * (long long)b / GCD;//최소공배수

	return LCM;//최소공배수 main으로 반환
}

int main() {
	int a = 0;
	int b = 0;
	long long result = 0;

	cout << "Enter two integer : ";//정수 2개 입력
	cin >> a >> b;

	result = LCM(a, b);//최소공배수 구하기

	if (a == 0 || b == 0) {//예외처리
		return 0;
	}

	cout << "LCM : " << result << endl;//최소공배수 출력

	return 0;
}