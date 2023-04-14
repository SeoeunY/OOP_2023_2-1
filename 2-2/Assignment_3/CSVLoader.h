#pragma once

#include <fstream>
#include <string>

class CSVLoader {
private:
	float** data;//2���� �迭
	int cols;
	int rows;

public:
	static constexpr unsigned int MAX_BUFFER_SIZE = 128;

	CSVLoader();//������
	CSVLoader(const char* path);
	~CSVLoader();//�Ҹ���

	float** getData() const;
	int getRows() const;
	int getCols() const;

	void parse(const char* path);
	void print(void);
};