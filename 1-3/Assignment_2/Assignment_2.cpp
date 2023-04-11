#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cmath>
using namespace std;

double Parallel_Resistance(double R1, double R2)//병렬 저항 함수
{
	return R1 * R2 / (R1 + R2);
}

void remain(double c, double d)//순환소수 순환마디 구하기
{
	int a = (int)c;//나머지 연산자가 int형에서 수행됨
	int b = (int)d;

	int arr[2][100]{};//순환마디 몫, 나머지 저장

	double remain;
	int quo;
	int i;
	quo = a / b;//정수 부분
	int check = 0;//순환마디 시작 부분 체크

	int cnt = 0;
	while (cnt < 100) {//계속 나머지 연산을 해주다가 순환마디 찾으면 탈출
		remain = a % b;
		arr[1][cnt] = remain;//나머지 저장
		a = remain * 10;//다음 나머지를 위한 과정

		for (i = 0; i < cnt; i++) {//같은 나머지 있었는지 확인
			if (arr[1][i] == arr[1][cnt]) {
				check = 1;
				break;
			}
		}
		if (check == 1)
			break;
		arr[0][cnt] = a / b;//소수 몫 저장
		cnt++;
	}

	double quotient = 0;
	quotient += (double)quo;

	if (check == 0) {//순환마디가 100자리 이상이거나 무한소수일 때
		cout << endl << "No repeating decimal";
		return;
	}

	if (i != 0) {//소수 첫번째 자리가 순환마디의 시작이 아닐 때
		for (int q = 0; q < i; q++)
			quotient += arr[0][q] * pow(10, -1 - q);
		cout.precision(i);//소수점 표시
		cout << fixed;
		cout << " = " << quotient << "(";
	}
	else//소수 첫번째 자리가 순환마디의 시작일 때
		cout << " = " << quo << ".(";

	for (int z = i; z < cnt; z++)//순환마디 출력
		cout << arr[0][z];
	cout << ")";
}

int main()
{
	double Vs, R1, R2, RL;

	//전압, 저항 입력
	cout << "Vs : ";
	cin >> Vs;
	cout << "R1 : ";
	cin >> R1;
	cout << "R2 : ";
	cin >> R2;
	cout << "R(Load) : ";
	cin >> RL;


	double I;
	double Vo;

	if (RL == 0) {
		I = Vs / (R1 + R2);
		Vo = I * R2;

		cout << "Vout : " << Vs * R2 << "/" << R1 + R2;
		remain(Vs * R2, R1 + R2);
	}

	else {
		double Ra = Parallel_Resistance(R2, RL);//병렬 저항 계산

		I = Vs / (R1 + Ra);
		Vo = I * Ra;

		double PL = pow(Vo, 2) / RL;
		double PS = Vs * I;

		double LPR = PL / PS * 100;

		cout << "Vout : " << Vs * Ra << "/" << R1 + Ra;
		remain(Vs * Ra, R1 + Ra);
		cout.precision(2);//소수 둘째자리까지 표시
		cout << fixed;
		cout << endl << "Load power ratio : " << LPR << "%";
	}
}