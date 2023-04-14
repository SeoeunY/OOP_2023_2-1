#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <fstream>
#include "CSVLoader.h"
using namespace std;

CSVLoader::CSVLoader() {//������
	this->data = NULL;
	this->cols = 0;
	this->rows = 0;
}

CSVLoader::CSVLoader(const char* path) {//�Ű������� �ִ� ������ (�Ű����� �־ ȣ������� ��)
	this->data = NULL;
	this->cols = 0;
	this->rows = 0;
	parse(path);
}

CSVLoader::~CSVLoader() {//�Ҹ���
	if (data != NULL) {
		for (int i = 0; i < getRows(); i++)//���� �Ҵ� ����
			delete data[i];
		delete data;
	}
}

float** CSVLoader::getData() const {//������ �迭 ��ȯ
	return this->data;
}

int CSVLoader::getCols() const {//�� ��ȯ
	return this->cols;
}

int CSVLoader::getRows() const {//�� ��ȯ
	return this->rows;
}

void CSVLoader::parse(const char* path) {//�Ľ� �Լ�
	ifstream file;
	file.open(path);

	if (!file)//���� �������� ���� ��
		return;

	char str[MAX_BUFFER_SIZE];
	int cnt_c = 0;
	int cnt_r = 0;
	int temp = 0;

	while (!file.eof()) {
		file.getline(str, MAX_BUFFER_SIZE);
		str[strlen(str)] = '\0';//���� ����

		for (int i = 0; i <= strlen(str); i++) {
			if (str[i] == ',' || str[i] == '\0') {//��ǥ, ���� ����ġ�� temp++
				temp++;
			}
		}
		if (temp > cnt_c)//�ִ� �� ����
			cnt_c = temp;
		temp = 0;
		cnt_r++;//��++
	}

	this->cols = cnt_c;//��� ����
	this->rows = cnt_r;

	file.close();

	this->data = new float* [rows];//2���� �迭 ���� �Ҵ�
	for (int i = 0; i < rows; i++)
		data[i] = new float[cols];

	ifstream file_a;
	file_a.open(path);

	if (!file_a)
		return;
	cnt_c = 0;
	cnt_r = 0;

	while (!file_a.eof()) {//���� ���� ������
		file_a.getline(str, MAX_BUFFER_SIZE);
		int len = strlen(str);
		str[len] = '\0';
		cnt_c = 0;
		string temp_str = "";

		for (int i = 0; i < len+1; i++) {
			if (str[i] == ',' || str[i] == '\0') {//��ǥ�� ���� ������ ���� data �迭�� ����
				data[cnt_r][cnt_c] = stof(temp_str);//�����ߴ� ���ڿ� �Ǽ������� ��ȯ, ����
				cnt_c++;
				temp_str = "";//���ڿ� �ʱ�ȭ
			}
			else {//���� ����
				temp_str.push_back(str[i]);
			}
		}
		cnt_r++;
	}

	print();//��� �Լ� ȣ��
}

void CSVLoader::print(void) {//���
	float** p_data = getData();//�迭 �ҷ���
	cout << "CSV PARSING" << endl;
	for (int i = 0; i < getRows(); i++) {//�� �ҷ���
		for (int j = 0; j < getCols(); j++) {//�� �ҷ���
			cout.width(10);
			cout << right << p_data[i][j];//data �迭�� ����� ���� ���
		}
		cout << endl;
	}

}