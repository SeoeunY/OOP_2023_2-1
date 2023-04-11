#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cmath>
#include <string.h>
using namespace std;

char hexa_table[16] = { 0,1,2,3,4,5,6,7,8,9,'A','B','C','D','E','F' };//16진수 표

int convert_to_decimal(int num[100], int convert, int len)//2,8,10진수 배열에 저장 -> int형 정수로 변환
{
	int decimal_number = 0;
	int cnt = 0;
	if (convert == 2) {//2->10
		for (int i = len - 1; i >= 0; i--) {
			decimal_number += num[i] * pow(2, cnt);
			cnt++;
		}
	}

	else if (convert == 8) {//8->10
		for (int i = len - 1; i >= 0; i--) {
			decimal_number += num[i] * pow(8, cnt);
			cnt++;
		}
	}

	else if (convert == 10) {//10->10
		for (int i = len - 1; i >= 0; i--) {
			decimal_number += num[i] * pow(10, cnt);
			cnt++;
		}
	}

	return decimal_number;//10진수 반환
}

int hexa_to_decimal(char num_char[100], int len)//16진수 -> 10진수
{
	int temp;
	int decimal[100]{};
	int decimal_number = 0;
	int cnt = 0;
	int num = 0;
	for (int i = 0; i < len; i++) {//알파벳 숫자로 변경
		if (num_char[i] >= 65 && num_char[i] <= 90) {
			decimal[num] = num_char[i] - 55;
			num++;
		}
		else {
			decimal[num] = num_char[i] - 48;//정수 배열에 저장
			num++;
		}
	}

	for (int i = len - 1; i >= 0; i--) {
		decimal_number += decimal[i] * pow(16, cnt);
		cnt++;
	}

	return decimal_number;//10진수 반환
}

void change(int number, int desire)//10진수에서 원하는 형으로 변형
{
	if (desire == 2) {//10->2
		int quo = number / 2;
		int remain = number % 2;

		if (quo != 0)
			change(quo, 2);//재귀 호출
		cout << remain;
	}

	else if (desire == 8) {//10->8
		int quo = number / 8;
		int remain = number % 8;

		if (quo != 0)
			change(quo, 8);
		cout << remain;
	}

	else if (desire == 16) {//10->16
		int quo = number / 16;
		int remain = number % 16;

		if (quo != 0)
			change(quo, 16);

		if (remain > 9)//알파벳으로 변환
			cout << hexa_table[remain];
		else
			cout << remain;
	}
}

int main()
{
	char num_char[100]{};
	int num[100]{};
	int convert, desire;
	int decimal_number;

	cin >> num_char >> convert >> desire;

	int cnt = 0;
	for (int i = 0; i < strlen(num_char); i++) {//알파벳 있는지 확인 (16진수만 존재)
		if (num_char[i] >= 65 && num_char[i] <= 90)
			cnt++;
	}

	if (cnt == 0) {//2,8,10진수
		for (int i = 0; i < strlen(num_char); i++)
			num[i] = num_char[i] - 48;//정수 배열에 저장
	}

	int len_num = strlen(num_char);

	//10진수로 변경
	if (convert == 2 || convert == 8 || convert == 10) {
		decimal_number = convert_to_decimal(num, convert, len_num);
	}
	else if (convert == 16) {
		decimal_number = hexa_to_decimal(num_char, len_num);
	}

	//원하는 형으로 변경
	if (desire == 10) {
		cout << decimal_number;
		return 0;
	}
	else
		change(decimal_number, desire);

	return 0;
}