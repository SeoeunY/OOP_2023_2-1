#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string.h>
#include "Clock.h"
using namespace std;

int main()
{
	Clock* clock = new Clock;//객체 선언

	char command[20];
	int second;

	while (1) {
		cin >> command;

		if (strcmp(command, "time") == 0) {
			cin >> second;//초 입력

			clock->setTime(second);
		}
		
		if (strcmp(command, "exit") == 0)//프로그램 종료
			break;
	}

	delete clock;
	return 0;
}