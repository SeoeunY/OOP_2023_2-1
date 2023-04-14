#pragma once

#include <iostream>
using namespace std;

class Clock {
private:
	void setHour(int hour);//시분초 설정
	void setMinute(int minute);
	void setSecond(int second);

	int hour;
	int minute;
	int second;

public:
	Clock();
	~Clock();
		
	void increaseHour();//시분초 업데이트
	void increaseMinute();
	void increaseSecond();

	void setTime(int second);//초 입력

	void print();
};