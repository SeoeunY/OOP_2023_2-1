#pragma once

#include <fstream>
#include <string>

class CSVLoader {
private:
	float** data;//2차원 배열
	int cols;
	int rows;

public:
	static constexpr unsigned int MAX_BUFFER_SIZE = 128;

	CSVLoader();//생성자
	CSVLoader(const char* path);
	~CSVLoader();//소멸자

	float** getData() const;
	int getRows() const;
	int getCols() const;

	void parse(const char* path);
	void print(void);
};