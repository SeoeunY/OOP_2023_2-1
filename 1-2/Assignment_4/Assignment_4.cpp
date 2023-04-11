#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <fstream>
using namespace std;

uint8_t** memory_alloc2D(size_t height, size_t width);//메모리 할당 함수
int memory_free2D(uint8_t** memory);//메모리 해제 함수
int w, h;//좌표 간 거리

int main()
{
    //각 이미지 이름
    const char* HORIZON_NAME = "Barbara_horizontalflip.raw";
    const char* VERTICAL_NAME = "Barbara_verticalflip.raw";
    const int IMAGE_HEIGHT = 512,//사진 크기
        IMAGE_WIDTH = 512;

    FILE* fp = 0;
    uint8_t** input_image = 0;
    uint8_t** cropped_image = 0;
    uint8_t** horizon_flip = 0;
    uint8_t** vertical_flip = 0;

    char search[101];

    cout << "Input file name : ";//파일 이름 입력
    cin >> search;


    fopen_s(&fp, search, "rb");//파일 오픈
    if (fp == 0)
    {
        cout << "Failed to open filename(" << search << ")" << endl;
        return -1;
    }

    input_image = memory_alloc2D(IMAGE_HEIGHT, IMAGE_WIDTH);//메모리 할당
    if (input_image == 0)
    {
        cout << "Failed to allocate memory" << endl;
        return -1;
    }

    fread((uint8_t*)input_image[0], sizeof(uint8_t), IMAGE_WIDTH * IMAGE_HEIGHT, fp);//파일 배열에 저장
    fclose(fp);//파일 닫기

    //crop
    int x1, y1, x2, y2;//좌표 변수

    cout << "1st coordinate : ";
    cin >> x1;
    cin.ignore(2, ',');//쉼표 무시
    cin >> y1;
    cout << "2st coordinate : ";
    cin >> x2;
    cin.ignore(2, ',');
    cin >> y2;

    int start_x;//사각형 왼쪽 위 좌표
    int start_y;

    if (x1 > x2) {
        w = x1 - x2;
        if (y1 > y2) {
            h = y1 - y2;
            start_x = x2;
            start_y = y2;
        }
        else {
            h = y2 - y1;
            start_x = x2;
            start_y = y1;
        }
    }
    else {
        w = x2 - x1;
        if (y1 > y2) {
            h = y1 - y2;
            start_x = x1;
            start_y = y2;
        }
        else {
            h = y2 - y1;
            start_x = x1;
            start_y = y1;
        }
    }

    cropped_image = memory_alloc2D(h, w);//메모리 할당
    if (cropped_image == 0)
    {
        cout << "Failed to allocate memory" << endl;
        return -1;
    }

    for (int i = 0; i < h; i++) {//픽셀값 저장
        for (int j = 0; j < w; j++)
            cropped_image[i][j] = input_image[start_y + i][start_x + j];
    }

    char crop_name[32] = "Barbara_cropped_";//파일 이름 제작
    char end[5] = ".raw";
    crop_name[16] = '(';
    crop_name[17] = w / 100 + 48;
    crop_name[18] = (w % 100) / 10 + 48;
    crop_name[19] = (w % 100) % 10 + 48;
    crop_name[20] = ')';
    crop_name[21] = 'X';
    crop_name[22] = '(';
    crop_name[23] = h / 100 + 48;
    crop_name[24] = (h % 100) / 10 + 48;
    crop_name[25] = (h % 100) % 10 + 48;
    crop_name[26] = ')';
    for (int i = 0; i < 5; i++)
        crop_name[27 + i] = end[i];

    //좌우반전
    horizon_flip = memory_alloc2D(IMAGE_HEIGHT, IMAGE_WIDTH);
    if (horizon_flip == 0)
    {
        cout << "Failed to allocate memory" << endl;
        return -1;
    }

    for (int i = 0; i < IMAGE_HEIGHT; i++) {//flip
        for (int j = 0; j < IMAGE_WIDTH; j++)
            horizon_flip[i][j] = input_image[i][512 - j];
    }

    //상하반전
    vertical_flip = memory_alloc2D(IMAGE_HEIGHT, IMAGE_WIDTH);
    if (vertical_flip == 0)
    {
        cout << "Failed to allocate memory" << endl;
        return -1;
    }

    for (int i = 0; i < IMAGE_HEIGHT; i++) {//flip
        for (int j = 0; j < IMAGE_WIDTH; j++)
            vertical_flip[i][j] = input_image[511 - i][j];//null 제외
    }

    //이미지 -> 파일로 저장
    fopen_s(&fp, crop_name, "wb");
    if (fp == NULL)
    {
        cout << "Failed to open filename(" << crop_name << ")" << endl;
        return -1;
    }
    fwrite((uint8_t*)cropped_image[0], sizeof(uint8_t), (size_t)(h * w), fp);
    fclose(fp);

    fopen_s(&fp, HORIZON_NAME, "wb");
    if (fp == 0)
    {
        cout << "Failed to open filename(" << HORIZON_NAME << ")" << endl;
        return -1;
    }
    fwrite((uint8_t*)horizon_flip[0], sizeof(uint8_t), (size_t)(IMAGE_WIDTH * IMAGE_HEIGHT), fp);
    fclose(fp);

    fopen_s(&fp, VERTICAL_NAME, "wb");
    if (fp == 0)
    {
        cout << "Failed to open filename(" << VERTICAL_NAME << ")" << endl;
        return -1;
    }
    fwrite((uint8_t*)vertical_flip[0], sizeof(uint8_t), (size_t)(IMAGE_WIDTH * IMAGE_HEIGHT), fp);
    fclose(fp);

    //메모리 할당 해제
    memory_free2D(cropped_image);
    memory_free2D(horizon_flip);
    memory_free2D(vertical_flip);
    memory_free2D(input_image);

    return 0;
}

uint8_t** memory_alloc2D(size_t height, size_t width)//메모리 할당
{
    uint8_t** memory = new uint8_t * [height];
    if (memory == 0)
        return 0;

    memory[0] = new uint8_t[height * width];
    if (memory[0] == 0)
    {
        delete[] memory;
        return 0;
    }

    for (size_t i = 1; i < height; i++)
        memory[i] = memory[i - 1] + width;

    return memory;
}

int memory_free2D(uint8_t** memory)//메모리 해제
{
    if (memory == 0)
        return -1;
    if (memory[0])
        delete[] memory[0];

    delete[] memory;
    return 0;
}