#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstdlib>//랜덤함수 사용
#include <ctime>
using namespace std;

int divisor[5];//divisor 전역변수 선언

void SHIFT(int(&compare)[5])//<< 비트연산 사용 함수
{
	int num = 0;
	int num_shift;
	for (int i = 0; i < 5; i++)
		num += compare[i] * pow(2, 4 - i);//십진수로 변환
	num_shift = num << 1;//shift 연산

	int comp_temp=0;
	for (int i = 4; i >= 0; i--) {//이진수 변환
		compare[comp_temp] = (num_shift >> i) & 1;
		comp_temp++;
	}
}

void Reciever(int(&Recieved_frame)[16])//reciever 함수
{
	int compare[5]{};

	for (int j = 0; j < 5; j++)
		compare[j] = Recieved_frame[j];

	int i = 1;
	while (i < 12) {
		if (compare[0] == 1) {
			for (int j = 0; j < 5; j++)
				compare[j] = divisor[j] ^ compare[j];
			//XOR 연산
		}

		for (int j = 0; j < 5; j++) {
			if (compare[0] == 0) {
				SHIFT(compare);
				compare[4] = Recieved_frame[4 + i];
				i++;
			}
			else {//compare[j]==1
				break;
			}
		}
	}

	for (int j = 0; j < 5; j++)
		compare[j] = divisor[j] ^ compare[j];

	cout << "Reconstructed_frame : ";
	for (int i = 0; i < 12; i++)
		cout << Recieved_frame[i];
	cout << endl;

	int Remain[4]{};//오류 검출
	for (int i = 0; i < 4; i++)
		Remain[0] = compare[i + 1];
	int count = 0;
	for (int i = 0; i < 4; i++) {
		if (Remain[i] == 0)
			count++;
	}

	if(count==4)//나머지 0000
		cout << "No detected error";
	else
		cout << "Reciever has detected error";
}

void Transmission_Channel(int(&Coded_frame)[16])
{
	int Recieved_frame[16]{};
	int rand_num;

	srand((unsigned int)time(NULL));//프로그램을 실행할 때마다 다른 난수 생성

	for (int i = 0; i < 16; i++) {
		rand_num = rand() % 100;
		if (rand_num < 95) {//에러가 나지 않을 경우
			if (Coded_frame[i] == 1)
				Recieved_frame[i] = 1;
			else if (Coded_frame[i] == 0)
				Recieved_frame[i] = 0;
		}
		else {//rand_num=95,96,97,98,99
			if (Coded_frame[i] == 1)
				Recieved_frame[i] = 0;
			else if (Coded_frame[i] == 0)
				Recieved_frame[i] = 1;
		}
	}

	cout << "Recieved_frame : ";
	for (int i = 0; i < 16; i++)
		cout << Recieved_frame[i] ;
	cout << endl;

	Reciever(Recieved_frame);
}

void Sender(void)//Sender 함수
{
	char divisor_char[6] = "11011";
	for (int i = 0; i < 5; i++)
		divisor[i] = divisor_char[i] - 48;

	char input_char[13];//2진수 입력

	cout << "Enter the input data : ";
	cin >> input_char;

	int input[12]{};
	for (int i = 0; i < 12; i++)
		input[i] = input_char[i] - 48;

	int XOR[16]{};

	for (int i = 0; i < 12; i++)
		XOR[i] = input[i];

	for (int i = 0; i < 4; i++)
		XOR[12 + i] = 0;//XOR배열에 FCS 저장
	//////////////////////////////////////////

	int compare[5]{};
	
	for (int j = 0; j < 5; j++)
		compare[j] = XOR[j];

	int i=1;
	while (i < 12) {
		if (compare[0] == 1) {
			for (int j = 0; j < 5; j++)
				compare[j] = divisor[j] ^ compare[j];
			//XOR 연산
		}

		for (int j = 0; j < 5; j++) {
			if (compare[0] == 0) {
				SHIFT(compare);
				compare[4] = XOR[4 + i];
				i++;
			}
			else {//compare[j]==1
				break;
			}
		}
	}

	for (int j = 0; j < 5; j++)
		compare[j] = divisor[j] ^ compare[j];

	int Coded_frame[16]{};
	for (int i = 0; i < 12; i++)
		Coded_frame[i] = input[i];

	for (int i = 0; i < 4; i++)
		Coded_frame[12 + i] = compare[1 + i];

	cout << "Coded_frame : ";
	for (int i = 0; i < 16; i++)
		cout << Coded_frame[i];
	cout << endl;

	Transmission_Channel(Coded_frame);
}

int main()
{
	Sender();//함수 호출

	return 0;
}