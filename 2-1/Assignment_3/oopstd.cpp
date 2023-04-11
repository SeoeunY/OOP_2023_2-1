#include <iostream>
#include <string.h>
#include <cmath>

namespace oopstd {
	void* memset(void* ptr, int value, size_t num) {
		char* ptr_c = (char *)ptr;//char������ �迭 ��ȯ
		
		for (int i = 0; i < num; i++) {//�Է� ���� num��ŭ value�� �迭 �ٲ�
			*(ptr_c + i) = value;
		}

		return ptr_c;
	}
	void* memcpy(void* destination, const void* source, size_t num) {
		char* destination_c = (char*)destination;
		char* source_c = (char*)source;

		for (int i = 0; i < num; i++) {//�Է� ���� num��ŭ ���ڿ� ����
			*(destination_c + i) = *(source_c + i);
		}

		return destination_c;
	}
	int strcmp(const char* str1, const char* str2) {
		int len1 = std::strlen(str1);
		int len2 = std::strlen(str2);

		int a = 0;
		int b = 0;

		for (int i = 0; i < len1; i++)//�ƽ�Ű�ڵ尪 ���ϱ�
			a += str1[i];
		for (int i = 0; i < len2; i++)
			b += str2[i];
		
		//��
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

		for (int i = 0; i < num; i++)//num��ŭ �迭 �ƽ�Ű �ڵ尪 ���ϱ�
			a += str1[i];
		for (int i = 0; i < num; i++)
			b += str2[i];

		//��
		if (a > b)
			return 1;
		else if (a < b)
			return -1;
		else if (a == b)
			return 0;
	}
	char* strcpy(char* destination, const char* source) {
		int len = std::strlen(source);

		for (int i = 0; i < len; i++) {//source ���̸�ŭ ���ڿ� ����
			*(destination + i) = *(source + i);
		}//==���ڿ� ����
		destination[len] = NULL;//���ڿ� ������ NULL�� �ʱ�ȭ

		return destination;
	}
	char* strncpy(char* destination, const char* source, size_t num) {
		for (int i = 0; i < num; i++)//num��ŭ ���ڿ� ����
			*(destination + i) = *(source + i);
		destination[num] = NULL;

		return destination;
	}
	size_t strlen(const char* str) {
		int i = 0;
		while (str[i] != NULL) {
			i++;//NULL ������ ������ i ����
		}

		return i;
	}
	int atoi(const char* str) {
		int number = 0;
		if (str[0] == '-') {//������ ��
			int len = std::strlen(str);
			int cnt = 0;

			for (int i = 0; i < len; i++) {
				if (str[i] == '.') {//Ȥ�� �Ǽ� �Է� �޾Ҵٸ� ���� �κи� ����
					len = i;
					break;
				}
			}

			for (int i = len-1; i > 0; i--) {
				number += (str[i]-48) * pow(10, cnt);//10�� �ŵ�������ŭ ���ϱ�
				cnt++;
			}
			number *= (-1);//����
		}
		else {//��� �� ��
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

		if (str[0] == '-') {//���� �� ��
			int dot = 0;
			int cnt = 0;

			for (dot; dot < len; dot++) {
				if (str[dot] == '.')//����, �Ҽ� �κ� ������
					break;
			}

			if (dot == len-1) {//. ����
				int a = 0;
				while (str[a] != NULL) {
					number += (str[a] - 48) * pow(10, dot);
					dot--;
				}
			}
			else {//�Ǽ��� ��
				for (int i = dot - 1; i > 0; i--) {
					number += (str[i] - 48) * pow(10, cnt);
					cnt++;
				}//���� ����
				cnt = -1;
				for (int i = dot + 1; i < len; i++) {
					number += (str[i] - 48) * pow(10, cnt);
					cnt--;
				}
			}
			
			number *= (-1.0);

			return number;
		}


		else {//����� ��
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
				}//���� ����
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