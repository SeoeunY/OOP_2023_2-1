#include "Clock.h"

Clock::Clock() {//������
	hour = 0;//�ʱ�ȭ
	minute = 0;
	second = 0;
	cout << "Class clock has constructed."<<endl;
}

Clock::~Clock() {
	//�Ҹ���
	cout << "Class clock has destroyed.";
}

void Clock::increaseHour() {
	hour++;//�� ����
	if (hour == 24)//�ʱ�ȭ
		hour = 0;
}

void Clock::increaseMinute() {
	minute++;//�� ����
	if (minute == 60) {//�ʱ�ȭ
		minute = 0;
		increaseHour();//�� ����
	}
}

void Clock::increaseSecond() {
	second++;//�� ����
	if (second == 60) {
		second = 0;
		increaseMinute();
	}
}

void Clock::setTime(int second) {
	int temp = second / 60;//�д���
	int hour = temp / 60;
	setHour(hour);//�ô���
	setMinute(temp - hour * 60);//�д���
	setSecond(second % 60);//�ʴ���
	print();//���
}

void Clock::setHour(int hour) {//���ڸ�ŭ �� ����
	for (int i = 0; i < hour; i++)
		increaseHour();
}

void Clock::setMinute(int minute) {//���ڸ�ŭ �� ����
	for (int i = 0; i < minute; i++)
		increaseMinute();
}

void Clock::setSecond(int second) {//���ڸ�ŭ �� ����
	for (int i = 0; i < second; i++)
		increaseSecond();
}

void Clock::print() {//���
	cout << this->hour << "H "<<this->minute<<"M "<<this->second<<"S"<<endl;
}