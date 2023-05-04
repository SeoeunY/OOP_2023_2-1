#include <iostream>
using namespace std;

char* my_strtok(char* str) {
	char delimiter[] = "@.";//구분자
	int i = 0;
	int len = 0;//구분자 개수
	while (delimiter[len] != '\0')
		len++;
	static char* temp = NULL;

	if (str != NULL && !temp)//temp에 str 복사
		temp = str;
	if (str == NULL && !temp)//문자열 종료
		return NULL;
	//if문에 !temp 없으면 안됨 temp에 옮기고 그 다음부터 str은 NULL이 들어오기 때문에 한 번 출력하고 끝나버림

	char* index = temp;//index에 temp 복사
	while (true) {
		for (i = 0; i < len; i++) {//첫번째 자리에 구분자 있는지 확인
			if (*index == delimiter[i]) {
				index++;//있으면 index 한 칸 뒤로 포인터 이동
				temp++;
				break;
			}
		}
		if (i == len) {
			temp = index;
			break;
		}
	}

	if (*temp == '\0') {//문자열 끝남
		temp = NULL;
		return temp;
	}

	while (*temp != '\0') {
		for (i = 0; i < len; i++) {
			if (*temp == delimiter[i]) {
				*temp = '\0';//구분자일 때 '\0'로 변환
				break;//for문 탈출
			}
		}
		temp++;//포인터 앞으로 이동
		if (i < len)//구분자 있음
			break;//while문 탈출
	}
	return index;
}


int main() {
	char str[1000]{};
	cin >> str;
	
	int len = 0;
	while (str[len] != '\0')
		len++;

	int cnt = 0;
	for (int i = 0; i < len; i++) {
		if (str[i] == '@')
			cnt++;
	}
	if (cnt > 1) {
		cout << "email format not satisfied" << endl;
		return 0;
	}

	char* ptr = my_strtok(str);//함수 호출
	if (ptr == NULL) {//구분자 없음
		cout << str << endl << "nothing to tokenize";
	}
	else {
		while (ptr != NULL) {//문자열 끝날 때까지
			cout << ptr << endl;//출력
			ptr = my_strtok(NULL);//함수 호출
		}
	}
	return 0;
}