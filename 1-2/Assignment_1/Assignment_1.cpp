#define CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cmath>
using namespace std;

int main()
{
    char input_1[20], input_2[20];//입력받을 정수

    for (int i = 0; i < 20; i++) {//초기화 (-1 입력받을 경우 없음)
        input_1[i] = -1;
        input_2[i] = -1;
    }

    cout << "Enter two integer input : ";
    cin >> input_1 >> input_2;//정수 입력

    int size_1 = 0, size_2 = 0;//정수 길이 변수

    cout << "Output : ";

    for (int i = 0; i < 20; i++) {//길이 저장
        if (input_1[i] != -1)
            size_1++;
        if (input_2[i] != -1)
            size_2++;
    }
    size_1 -= 1;//입력받을 때 null 빼주기
    size_2 -= 1;

    int att_num[50]={0,};//두 정수 붙일 배열
    int count = 0;

    for (count; count < size_1; count++) {
       att_num[count] = int(input_1[count])-48;
    }

    for (int i=0; i<size_2; i++) {
        att_num[count+i] = int(input_2[i]) - 48;
    }//숫자 2개 att_num 배열에 저장
    
    int num[10];//중복 제외할 배열
    for (int i = 0; i < 9; i++)//초기화
        num[i] = -1;

    int compare;//att_num에서 가져오는 숫자
    int num_num = 0;//중복 제외 배열에 compare 넣을거임
    for (int i = 0; i < size_1+size_2; i++) {//중요!!!!!!!
        int cnt = 1;//숫자의 개수
        compare = att_num[i];//첫번째 숫자부터 비교 시작

        for (int j = i+1; j < size_1 + size_2; j++) {
            if (compare == att_num[j])
                cnt++;
        }
        
        for (int j = 0; j < 9; j++) {
            if (compare == num[j])//중복
                compare = -1;
        }

        if (compare == -1)
            continue;
        //출력 및 저장
        num[num_num] = compare;
        num_num++;
        cout << compare << cnt;
    }

    return 0;
}