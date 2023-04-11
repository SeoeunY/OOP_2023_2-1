#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <fstream>
#include <string.h>
using namespace std;

int main()
{
	char file_name[101];
	int num;

	cout << "Input file name : ";//파일 이름 입력
	cin >> file_name;
	
	ifstream fin;
	fin.open(file_name);//파일 오픈

	if (!fin) {//찾는 파일이 없다면
		cout << "no file exist" << endl;
		return 0;
	}

	cin >> num;//찾을 파일 형식 개수

	char** input_list = new char* [num];//이차원 동적할당
	for (int i = 0; i < num; i++)
		input_list[i] = new char[101];

	for (int i = 0; i < num; i++)
		cin >> input_list[i];//찾을 파일 형식 입력/*,? 존재함
	
	char file_list[100][101]{};//파일에 적혀있는 파일 리스트

	int k = 0;//파일 리스트 개수
	while (!fin.eof()) {//파일 리스트 저장
		fin.getline(file_name, 100);
		strcpy(file_list[k], file_name);
		k++;
	}

	cout << endl << endl;

	char* compare;
	char* ptr=nullptr;
	char* ptr3 = nullptr;
	int z = 0;

	for (int i = 0; i < num; i++) {//지정한 횟수만큼 반복
		for (int j = 0; j < k; j++) {//한 줄씩 특수문자 탐색

			if (input_list[i][j]=='*') {//*이 있을 때
				compare=strtok(input_list[i], "*");//그 앞의 문자열 저장
				for (int m = 0; m < k; m++) {//파일 리스트 전체 검색
					ptr = strstr(file_list[m],compare);//문자열 파일 같은지 탐색
					if (ptr == NULL)//동일 X
						continue;//다음 문자열 탐색
					cout << ptr << endl;//동일하면 출력
				}
			}

			else if (input_list[i][j] == '?') {//? 있을 때
				char comp_file[101]{};
				int a=0;//? 개수 (? 1개 이상일 수 있음)
				
				ptr = input_list[i];
				for (int p = 0; p < strlen(input_list[i]); p++) {
					if (input_list[i][p] == '*') {
						ptr = strtok(input_list[i], "*");//* 앞으로만 잘라 저장
						z = 1;
						break;
					}
				}

				for (int o = 0; o < strlen(ptr); o++) {
					comp_file[o] = *(ptr+o);
				}
				
				for (int q = 0; q < strlen(comp_file); q++) {
					if (comp_file[q] == '?') {//? 자리만 공백으로 초기화
						comp_file[q] = ' ';
						a++;
					}
				}
				//뒤에 *있어도 comp_file 에는 공백(물음표)만 존재
				for (int m = 0; m < k; m++) {//파일리스트 한 줄씩 탐색
					int cnt = 0;
					for (int p = 0; p < strlen(comp_file); p++) {//파일리스트와 비교해 다르면 cnt  증가
						if (comp_file[p] != file_list[m][p])
							cnt++;//비교
					}

					if (z == 1) {//*있음
						ptr3 = NULL;
						int x;
						int count;
						for (x = 0; x < strlen(file_list[m]); x++) {//파일 리스트 한 줄 안에서
							count = 0;
							char* ptr5 = strtok(ptr, "?");
							ptr3 = strstr(file_list[m], ptr5);//문자열 파일 같은지 탐색
							if (ptr3 != NULL)//동일
								count++;
							for (int p = 0; p < a-1; p++) {
								ptr5 = strtok(NULL, "?");
								ptr3 = strstr(file_list[m], ptr5);//문자열 파일 같은지 탐색
								if (ptr3 != NULL)
									count++;
							}
							ptr5 = strtok(NULL,"?");
							ptr3 = strstr(file_list[m], ptr5);//문자열 파일 같은지 탐색
							if (ptr3 != NULL)
								count++;

							if (count == a + 1) {
								cout << file_list[m] << endl;
								break;
							}
						}
					}
					else {//* 없을 때
						if (cnt == a) {
							cout << file_list[m] << endl;
						}
					}
				}
			}
		}
	}

	fin.close();//파일 닫기

	for (int i = 0; i < num; i++)//동적할당 해제
		delete input_list[i];
	delete input_list;

	return 0;
}