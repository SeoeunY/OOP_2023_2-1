#include <iostream>
using namespace std;

int cnt = 1;//거리 측정 변수 전역 변수 설정
int a, b;//미로 크기

void find(int** arr, int h, int w, int h2, int w2);//동서남북 확인 함수 호출
void find_east(int** arr, int h, int w, int h2, int w2);//노드 동쪽으로 이동해 확인
void find_west(int** arr, int h, int w, int h2, int w2);//노드 서쪽으로 이동해 확인
void find_north(int** arr, int h, int w, int h2, int w2);//노드 북쪽으로 이동해 확인
void find_south(int** arr, int h, int w, int h2, int w2);//노드 남쪽으로 이동해 확인

int main()	
{
	cin >> a >> b;//미로 크기 입력
	
	char** arr_c = new char* [a];//char형으로 배열 동적할당
	for (int i = 0; i < a; i++)
		arr_c[i] = new char[b];

	for (int i = 0; i < a; i++) {//char형으로 입력 받으면 공백 없이 입력 받을 수 있음
		for (int j = 0; j < b; j++)
			cin >> arr_c[i][j];
	}

	int** arr = new int*[a];//int형으로 동적할당
	for (int i = 0; i < a; i++)
		arr[i] = new int[b];

	for (int i = 0; i < a; i++) {//int형 배열에 미로 입력
		for (int j = 0; j < b; j++)
			arr[i][j] = arr_c[i][j] - '0';
	}

	int h1, w1, h2, w2;//시작 좌표, 도착 좌표

	cin >> w1 >> h1 >> w2 >> h2;
	w1--;
	h1--;
	w2--;
	h2--;
	//(h1,w1) 시작 좌표, (h2,w2) 끝 좌표


	find(arr, h1, w1, h2, w2);//거리 계산 함수 호출

	for (int i = 0; i < a; i++)//동적 할당 해제
		delete[] arr[i];
	delete[] arr;

	return 0;
}

void find(int** arr, int h, int w, int h2, int w2)//동서남북 호출
{	
	find_east(arr, h, w, h2, w2);
	find_west(arr, h, w, h2, w2);
	find_north(arr, h, w, h2, w2);
	find_south(arr, h, w, h2, w2);
	cnt--;//사방면 다 검색해서 도착 못함
}

void find_east(int** arr, int h, int w, int h2, int w2)
{
	if (h < 0 || h >= a)//구간 체크
		return;
	if (w < 0 || w >= b)
		return;
	if (h == h2 && w == w2) {//도착
		cout << endl << endl << cnt;
		exit(0);//강제 종료
	}

	arr[h][w] = 1;//중복 제외

	if (w + 1 >= b)//구간 벗어남 예외처리
		return;
	if (arr[h][w + 1] == 0) {
		cnt++;
		find(arr, h, w + 1, h2, w2);
	}
}

void find_west(int** arr, int h, int w, int h2, int w2)
{
	if (h < 0 || h >= a)//구간 체크
		return;
	if (w < 0 || w >= b)
		return;
	if (h == h2 && w == w2) {//도착
		cout << endl << endl << cnt;
		exit(0);
	}

	arr[h][w] = 1;

	if (w - 1 < 0)//구간 벗어남 예외처리
		return;
	if (arr[h][w - 1] == 0) {
		cnt++;
		find(arr, h, w - 1, h2, w2);
	}
}

void find_north(int** arr, int h, int w, int h2, int w2)
{
	if (h < 0 || h >= a)//구간 체크
		return;
	if (w < 0 || w >= b)
		return;
	if (h == h2 && w == w2) {//도착
		cout << endl << endl << cnt;
		exit(0);
	}

	arr[h][w] = 1;

	if (h - 1 < 0)//구간 벗어남 예외처리
		return;
	if (arr[h - 1][w] == 0) {
		cnt++;
		find(arr, h - 1, w, h2, w2);
	}
}

void find_south(int** arr, int h, int w, int h2, int w2)
{
	if (h < 0 || h >= a)//구간 체크
		return;
	if (w < 0 || w >= b)
		return;
	if (h == h2 && w == w2) {//도착
		cout << endl << endl << cnt;
		exit(0);
	}

	arr[h][w] = 1;

	if (h + 1 >= a)//구간 벗어남 예외처리
		return;
	if (arr[h + 1][w] == 0) {
		cnt++;
		find(arr, h + 1, w, h2, w2);
	}
}