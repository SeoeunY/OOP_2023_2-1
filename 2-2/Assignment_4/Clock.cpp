#include "Clock.h"

Clock::Clock() {//생성자
	hour = 0;//초기화
	minute = 0;
	second = 0;
	cout << "Class clock has constructed."<<endl;
}

Clock::~Clock() {
	//소멸자
	cout << "Class clock has destroyed.";
}

void Clock::increaseHour() {
	hour++;//시 증가
	if (hour == 24)//초기화
		hour = 0;
}

void Clock::increaseMinute() {
	minute++;//분 증가
	if (minute == 60) {//초기화
		minute = 0;
		increaseHour();//시 증가
	}
}

void Clock::increaseSecond() {
	second++;//초 증가
	if (second == 60) {
		second = 0;
		increaseMinute();
	}
}

void Clock::setTime(int second) {
	int temp = second / 60;//분단위
	int hour = temp / 60;
	setHour(hour);//시단위
	setMinute(temp - hour * 60);//분단위
	setSecond(second % 60);//초단위
	print();//출력
}

void Clock::setHour(int hour) {//숫자만큼 시 증가
	for (int i = 0; i < hour; i++)
		increaseHour();
}

void Clock::setMinute(int minute) {//숫자만큼 분 증가
	for (int i = 0; i < minute; i++)
		increaseMinute();
}

void Clock::setSecond(int second) {//숫자만큼 초 증가
	for (int i = 0; i < second; i++)
		increaseSecond();
}

void Clock::print() {//출력
	cout << this->hour << "H "<<this->minute<<"M "<<this->second<<"S"<<endl;
}