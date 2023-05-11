#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
using namespace std;

class myMusic {
private:
	char m_title[32];//이름
	char m_singer[32];//가수
	char m_album[32];//앨범명
	int m_track_no;//트랙 넘버
	int m_year;//발매 연도

public:
	myMusic() {//초기화
		m_title[0] = '\0';
		m_singer[0] = '\0';
		m_album[0] = '\0';
		m_track_no = -1;
		m_year = -1;
	}
	~myMusic() {//초기화
		m_title[0] = '\0';
		m_singer[0] = '\0';
		m_album[0] = '\0';
		m_track_no = -1;
		m_year = -1;
	}

	void setTitle(char* title) { strcpy(m_title, title); }
	void setSinger(char* singer) { strcpy(m_singer, singer); }
	void setAlbum(char* album) { strcpy(m_album, album); }
	void setYear(int year) { m_year = year; }
	void setTrackNo(int track_no) { m_track_no = track_no; }

	char* getTitle() { return m_title; }
	char* getSinger() { return m_singer; }
	char* getAlbum() { return m_album; }
	int getYear() { return m_year; }
	int getTrackNo() { return m_track_no; }

	void print();//출력
};

void myMusic::print() {//해당 곡 정보 출력
	cout << "Title : " << getTitle() << endl;
	cout << "Singer : " << getSinger() << endl;
	cout << "Album : " << getAlbum() << endl;
	cout << "Track number : " << getTrackNo() << endl;
	cout << "Year : " << getYear() << endl;
	cout << "----------" << endl;
}

char* except(char* a) {//앞뒤 공백 삭제
	int i = 0;
	while (a[i] == ' ')
		i++;
	if (i > 0) {//맨앞 공백 삭제
		int j = 0;
		while (a[i + j] != '\0') {
			a[j] = a[i + j];
			j++;
		}
		a[j] = '\0';
	}

	int len = strlen(a);//맨뒤 공백 삭제
	while (len > 0 && a[len - 1] == ' ')
		len--;
	a[len] = '\0';

	return a;
}

int main() {
	myMusic* Music[100]{};
	char command[20]{};
	int cnt = 0;

	while (1) {
		cout << "command(insert, print, exit) : ";
		cin >> command;

		if (strcmp(command, "insert") == 0) {//삽입
			if (cnt > 100)//배열 꽉 참
				cout << "No more space to insert music :(";
			else {
				Music[cnt] = new myMusic;//메모리 동적 할당
				char info[1000]{};
				cin.getline(info,1000,'\n');
				char* info_ptr = info;//띄어쓰기 무시
				char* ptr = NULL;
				char* ptr_copy = NULL;

				ptr = strtok(info_ptr, ",");
				ptr = except(ptr);
				if (strlen(ptr) > 32) {
					cout << "Title too long :(" << endl;
					continue;
				}
				Music[cnt]->setTitle(ptr);//이름 저장

				ptr = strtok(NULL, ",");
				Music[cnt]->setSinger(except(ptr));//가수 저장

				ptr = strtok(NULL, ",");
				Music[cnt]->setAlbum(except(ptr));//앨범명 저장

				int num = 0;
				ptr = strtok(NULL, ",");
				num = atoi(except(ptr));//숫자 정수형으로 변환
				Music[cnt]->setYear(num);//발매 연도 저장

				ptr = strtok(NULL, ",");
				num = atoi(except(ptr));//숫자 정수형으로 변환
				Music[cnt]->setTrackNo(num);//트랙 넘버 저장

				cnt++;
			}
		}

		if (strcmp(command, "print") == 0) {//for문 돌면서 각 곡 정보 출력
			for (int i = 0; i < cnt; i++)
				Music[i]->print();
		}

		if (strcmp(command, "exit") == 0)//프로그램 종료
			break;

		else
			continue;
	}

	for (int i = 0; i < cnt; i++)//메모리 할당 해제
		delete Music[i];
	return 0;
}