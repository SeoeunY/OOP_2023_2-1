#pragma once

#include <iostream>
using namespace std;

class Clock {
private:
	void setHour(int hour);//�ú��� ����
	void setMinute(int minute);
	void setSecond(int second);

	int hour;
	int minute;
	int second;

public:
	Clock();
	~Clock();
		
	void increaseHour();//�ú��� ������Ʈ
	void increaseMinute();
	void increaseSecond();

	void setTime(int second);//�� �Է�

	void print();
};