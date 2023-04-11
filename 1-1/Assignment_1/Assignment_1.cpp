#define CRT_SECURE_NO_WARNINGS
#include <iostream>
using namespace std;

char Sie_tri[384][767];//그릴 수 있는 최대 크기의 삼각형 배열을 전역변수 설정

void print(int col, int row)//'$' 그려넣기
{
	Sie_tri[col][row] = '$';

	Sie_tri[col +1][row - 1] = '$';
	Sie_tri[col + 1][row + 1] = '$';

	for (int i = 0; i < 5; i++)
		Sie_tri[col +2][row - 2 + i] = '$';
}

void tri(int len,int col, int row)//삼각형 배열
{
	if (len == 3) {//최소 크기 삼각형
		print(col, row);
		return;
	}

	//재귀함수 호출
	tri(len / 2, col, row);//상
	tri(len / 2, col + len / 2, row - len / 2);//하 좌
	tri(len / 2, col + len / 2, row + len / 2);//하 우
}

int main()
{
	for (int i = 0; i < 384; i++) {//배열 초기화
		for (int j = 0; j < 767; j++)
			Sie_tri[i][j] = ' ';
	}

	unsigned char input;
	cout << "input : ";
	cin >> input;//입력값 k

	int input_int = input - 48;//아스키코드 계산, int 형으로 변환

	int row = 6 * pow(2, input_int - 1) - 1;//가로
	int col = 3 * pow(2, input_int - 1);//세로
	//Sie_tri[col][row]

	tri(col, 0, col-1);//삼각형을 그려보자

	//출력
	for (int i = 0; i < 3 * pow(2, input_int - 1); i++) {
		for (int j = 0; j < 6 * pow(2, input_int - 1) - 1; j++)
			cout << Sie_tri[i][j];
		cout << endl;
	}

	return 0;
}