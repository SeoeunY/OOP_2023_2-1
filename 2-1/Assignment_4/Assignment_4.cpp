#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string.h>
#include <fstream>
using namespace std;

int main()
{
	ifstream fin;
	fin.open("binary.txt");//바이너리 파일 오픈
	fstream f_alpha;
	f_alpha.open("alphabet.txt");//알파벳 파일 오픈

	if (!fin) {//예외처리
		cout << "Unable to open binary text file" << endl;
		return 0;
	}
	if (!f_alpha) {//예외처리
		cout << "Unable to open alphabet text file" << endl;
		return 0;
	}

	char binary[1000]{};//바이너리 정보 저장
	char convert[100]{};//알파벳 저장
	fin.getline(binary, 1000);
	int cnt = 0;
	int k = 0;

	int len = strlen(binary);//바이너리 길이 저장

	int i = 0;
	while (i <= len) {//계속 돌다가 1 만나거나 0이 25개면 알파벳 저장
		if (binary[i] == '1') {
			convert[k] = cnt + 'a';//아스키코드값으로 저장
			cnt = 0;//0 개수 초기화 -> 다음 바이너리 탐색
			k++;
			i++;
			continue;
		}

		if (cnt == 25) {//z임
			convert[k] = cnt + 'a';//z 저장
			cnt = 1;
			k++;
			i++;
			continue;
		}
		cnt++;
		i++;
	}
	
	f_alpha.write(convert, k);//알파벳 텍스트 파일에 저장

	f_alpha.close();//파일 닫기
	fin.close();//파일 닫기

	return 0;
}