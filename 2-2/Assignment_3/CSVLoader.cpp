#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <fstream>
#include "CSVLoader.h"
using namespace std;

CSVLoader::CSVLoader() {//생성자
	this->data = NULL;
	this->cols = 0;
	this->rows = 0;
}

CSVLoader::CSVLoader(const char* path) {//매개변수가 있는 생성자 (매개변수 넣어서 호출해줘야 됨)
	this->data = NULL;
	this->cols = 0;
	this->rows = 0;
	parse(path);
}

CSVLoader::~CSVLoader() {//소멸자
	if (data != NULL) {
		for (int i = 0; i < getRows(); i++)//동적 할당 해제
			delete data[i];
		delete data;
	}
}

float** CSVLoader::getData() const {//데이터 배열 반환
	return this->data;
}

int CSVLoader::getCols() const {//행 반환
	return this->cols;
}

int CSVLoader::getRows() const {//열 반환
	return this->rows;
}

void CSVLoader::parse(const char* path) {//파싱 함수
	ifstream file;
	file.open(path);

	if (!file)//파일 존재하지 않을 때
		return;

	char str[MAX_BUFFER_SIZE];
	int cnt_c = 0;
	int cnt_r = 0;
	int temp = 0;

	while (!file.eof()) {
		file.getline(str, MAX_BUFFER_SIZE);
		str[strlen(str)] = '\0';//개행 삽입

		for (int i = 0; i <= strlen(str); i++) {
			if (str[i] == ',' || str[i] == '\0') {//쉼표, 개행 마주치면 temp++
				temp++;
			}
		}
		if (temp > cnt_c)//최대 행 저장
			cnt_c = temp;
		temp = 0;
		cnt_r++;//열++
	}

	this->cols = cnt_c;//행렬 저장
	this->rows = cnt_r;

	file.close();

	this->data = new float* [rows];//2차원 배열 동적 할당
	for (int i = 0; i < rows; i++)
		data[i] = new float[cols];

	ifstream file_a;
	file_a.open(path);

	if (!file_a)
		return;
	cnt_c = 0;
	cnt_r = 0;

	while (!file_a.eof()) {//파일 끝날 때까지
		file_a.getline(str, MAX_BUFFER_SIZE);
		int len = strlen(str);
		str[len] = '\0';
		cnt_c = 0;
		string temp_str = "";

		for (int i = 0; i < len+1; i++) {
			if (str[i] == ',' || str[i] == '\0') {//쉼표나 개행 만나면 숫자 data 배열에 저장
				data[cnt_r][cnt_c] = stof(temp_str);//저장했던 문자열 실수형으로 변환, 저장
				cnt_c++;
				temp_str = "";//문자열 초기화
			}
			else {//숫자 저장
				temp_str.push_back(str[i]);
			}
		}
		cnt_r++;
	}

	print();//출력 함수 호출
}

void CSVLoader::print(void) {//출력
	float** p_data = getData();//배열 불러옴
	cout << "CSV PARSING" << endl;
	for (int i = 0; i < getRows(); i++) {//열 불러옴
		for (int j = 0; j < getCols(); j++) {//행 불러옴
			cout.width(10);
			cout << right << p_data[i][j];//data 배열에 저장된 숫자 출력
		}
		cout << endl;
	}

}