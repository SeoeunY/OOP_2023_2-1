#include <iostream>
#include <string.h>
#include <cmath>

namespace oopstd {
	void* memset(void* ptr, int value, size_t num) {
		char* ptr_c = (char *)ptr;//char형으로 배열 변환
		
		for (int i = 0; i < num; i++) {//입력 받은 num만큼 value로 배열 바꿈
			*(ptr_c + i) = value;
		}

		return ptr_c;
	}
	void* memcpy(void* destination, const void* source, size_t num) {
		char* destination_c = (char*)destination;
		char* source_c = (char*)source;

		for (int i = 0; i < num; i++) {//입력 받은 num만큼 문자열 복사
			*(destination_c + i) = *(source_c + i);
		}

		return destination_c;
	}
	int strcmp(const char* str1, const char* str2) {
		int len1 = std::strlen(str1);
		int len2 = std::strlen(str2);

		int a = 0;
		int b = 0;

		for (int i = 0; i < len1; i++)//아스키코드값 더하기
			a += str1[i];
		for (int i = 0; i < len2; i++)
			b += str2[i];
		
		//비교
		if (a > b)
			return 1;
		else if (a < b)
			return -1;
		else if (a == b)
			return 0;
	}
	int strncmp(const char* str1, const char* str2, size_t num) {
		int a = 0;
		int b = 0;

		for (int i = 0; i < num; i++)//num만큼 배열 아스키 코드값 더하기
			a += str1[i];
		for (int i = 0; i < num; i++)
			b += str2[i];

		//비교
		if (a > b)
			return 1;
		else if (a < b)
			return -1;
		else if (a == b)
			return 0;
	}
	char* strcpy(char* destination, const char* source) {
		int len = std::strlen(source);

		for (int i = 0; i < len; i++) {//source 길이만큼 문자열 저장
			*(destination + i) = *(source + i);
		}//==문자열 복시
		destination[len] = NULL;//문자열 마지막 NULL로 초기화

		return destination;
	}
	char* strncpy(char* destination, const char* source, size_t num) {
		for (int i = 0; i < num; i++)//num만큼 문자열 복사
			*(destination + i) = *(source + i);
		destination[num] = NULL;

		return destination;
	}
	size_t strlen(const char* str) {
		int i = 0;
		while (str[i] != NULL) {
			i++;//NULL 나오기 전까지 i 증가
		}

		return i;
	}
	int atoi(const char* str) {
		int number = 0;
		if (str[0] == '-') {//음수일 때
			int len = std::strlen(str);
			int cnt = 0;

			for (int i = 0; i < len; i++) {
				if (str[i] == '.') {//혹시 실수 입력 받았다면 정수 부분만 저장
					len = i;
					break;
				}
			}

			for (int i = len-1; i > 0; i--) {
				number += (str[i]-48) * pow(10, cnt);//10의 거듭제곱만큼 곱하기
				cnt++;
			}
			number *= (-1);//음수
		}
		else {//양수 일 때
			int len = std::strlen(str);
			int cnt = 0;

			for (int i = 0; i < len; i++) {
				if (str[i] == '.') {
					len = i;
					break;
				}
			}

			for (int i = len-1; i >= 0; i--) {
				number += (str[i] - 48) * pow(10, cnt);
				cnt++;
			}
		}
		return number;
	}
	float atof(const char* str) {
		float number = 0;
		int len = std::strlen(str);

		if (str[0] == '-') {//음수 일 때
			int dot = 0;
			int cnt = 0;

			for (dot; dot < len; dot++) {
				if (str[dot] == '.')//정수, 소수 부분 나누기
					break;
			}

			if (dot == len-1) {//. 없음
				int a = 0;
				while (str[a] != NULL) {
					number += (str[a] - 48) * pow(10, dot);
					dot--;
				}
			}
			else {//실수일 때
				for (int i = dot - 1; i > 0; i--) {
					number += (str[i] - 48) * pow(10, cnt);
					cnt++;
				}//정수 저장
				cnt = -1;
				for (int i = dot + 1; i < len; i++) {
					number += (str[i] - 48) * pow(10, cnt);
					cnt--;
				}
			}
			
			number *= (-1.0);

			return number;
		}


		else {//양수일 때
			int dot = 0;
			int cnt = 0;
			
			for (dot; dot < len; dot++) {
				if (str[dot] == '.')
					break;
			}

			if (dot == len - 1) {
				int a = 0;
				while (str[a] != NULL) {
					number += (str[a] - 48) * pow(10, dot);
					dot--;
				}
			}
			else {
				for (int i = dot - 1; i >= 0; i--) {
					number += (str[i] - 48) * pow(10, cnt);
					cnt++;
				}//정수 저장
				cnt = -1;
				for (int i = dot + 1; i < len; i++) {
					number += (str[i] - 48) * pow(10, cnt);
					cnt--;
				}
			}
		}

		return number;
	}
}