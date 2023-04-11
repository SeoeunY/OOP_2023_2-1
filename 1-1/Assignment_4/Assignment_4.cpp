#define CRT_SECURE_NO_WARNINGS
#include <iostream>
using namespace std;

int main()
{
	int mat_A[3][3]{};//정수형 행렬 선언

	cout << "input : " << endl;
	for (int i = 0; i < 3; i++) {//행렬 입력 받기
		for (int j = 0; j < 3; j++) {
			cin >> mat_A[i][j];
		}
	}

	int det_A = 0;//det 선언 및 계산
	det_A += mat_A[0][0] * mat_A[1][1] * mat_A[2][2];
	det_A += mat_A[0][1] * mat_A[1][2] * mat_A[2][0];
	det_A += mat_A[0][2] * mat_A[1][0] * mat_A[2][1];
	det_A -= mat_A[0][2] * mat_A[1][1] * mat_A[2][0];
	det_A -= mat_A[0][1] * mat_A[1][0] * mat_A[2][2];
	det_A -= mat_A[0][0] * mat_A[1][2] * mat_A[2][1];

	if (det_A == 0) {//det 값이 0일 때 (역행렬 존재하지 않음)
		cout << "The inverse matrix does not exist.";
		return 0;
	}

	int mat_C[3][3]{};//cofactor matrix 선언 및 계산, 저장

	mat_C[0][0] = mat_A[1][1] * mat_A[2][2] - mat_A[1][2] * mat_A[2][1];
	mat_C[0][1] = -(mat_A[1][0] * mat_A[2][2] - mat_A[1][2] * mat_A[2][0]);
	mat_C[0][2] = mat_A[1][0] * mat_A[2][1] - mat_A[1][1] * mat_A[2][0];
	mat_C[1][0] = -(mat_A[0][1] * mat_A[2][2] - mat_A[0][2] * mat_A[2][1]);
	mat_C[1][1] = mat_A[0][0] * mat_A[2][2] - mat_A[0][2] * mat_A[2][0];
	mat_C[1][2] = -(mat_A[0][0] * mat_A[2][1] - mat_A[0][1] * mat_A[2][0]);
	mat_C[2][0] = mat_A[0][1] * mat_A[1][2] - mat_A[0][2] * mat_A[1][1];
	mat_C[2][1] = -(mat_A[0][0] * mat_A[1][2] - mat_A[0][2] * mat_A[1][0]);
	mat_C[2][2] = mat_A[0][0] * mat_A[1][1] - mat_A[0][1] * mat_A[1][0];

	int mat_CT[3][3]{};//transpose cofactor matrix

	for (int i = 0; i < 3; i++) {//행렬 복사
		for (int j = 0; j < 3; j++) {
			mat_CT[i][j] = mat_C[i][j];
		}
	}

	int temp;//숫자 자리 변경
	//1
	temp = mat_CT[1][0];
	mat_CT[1][0] = mat_CT[0][1];
	mat_CT[0][1] = temp;
	//2
	temp = mat_CT[2][0];
	mat_CT[2][0] = mat_CT[0][2];
	mat_CT[0][2] = temp;
	//3
	temp = mat_CT[2][1];
	mat_CT[2][1] = mat_CT[1][2];
	mat_CT[1][2] = temp;

	float mat_iA[3][3]{};//실수형 역행렬 저장 배열 선언

	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			mat_iA[i][j] = float(mat_CT[i][j])/float(det_A);//역행렬 계산 및 저장
		}
	}
	cout << endl<<endl<<"output : "<<endl;
	for (int i = 0; i < 3; i++) {//역행렬 출력
		for (int j = 0; j < 3; j++) {
			cout.width(5);
			cout << std::right << mat_iA[i][j];
		}
		cout << endl;
	}
}