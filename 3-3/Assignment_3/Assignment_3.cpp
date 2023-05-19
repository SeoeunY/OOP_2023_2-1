#include <iostream>
using namespace std;

class Matrix {
private:
    double matrix[3][3];

public:
    Matrix() {//생성자 (초기화)
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                matrix[i][j] = 0;
            }
        }
    }
    void setMatrix(double num[][3]) {//matrix 숫자 저장
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                matrix[i][j] = num[i][j];
            }
        }
    }

    void printMatrix() {//matrix 출력
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                cout << matrix[i][j] << " ";
            }
            cout << std::endl;
        }
    }

    Matrix& operator+=(const Matrix& other) {//+= 연산자
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                this->matrix[i][j] += other.matrix[i][j];
            }
        }
        return *this;
    }

    Matrix& operator-=(const Matrix& other) {//-= 연산자
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                this->matrix[i][j] -= other.matrix[i][j];
            }
        }
        return *this;
    }

    Matrix& operator*(const Matrix& other) {//* 연산자
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                this->matrix[i][j] *= other.matrix[i][j];
            }
        }
        return *this;
    }
};

int main() {
    Matrix matrix1;
    Matrix matrix1_1;
    Matrix matrix1_2;
    double num[3][3]{};
    cout << "enter number of matrix1 : " << endl;
    for (int i = 0; i < 3; i++) {//첫번째 matrix 숫자 입력
        for (int j = 0; j < 3; j++)
            cin >> num[i][j];
    }
    matrix1.setMatrix(num);//객체 3개에 동일한 matrix 숫자 저장
    matrix1_1.setMatrix(num);
    matrix1_2.setMatrix(num);

    Matrix matrix2;
    cout << endl << "enter number of matrix2 : " << endl;
    for (int i = 0; i < 3; i++) {//두번째 matrix 숫자 입력
        for (int j = 0; j < 3; j++)
            cin >> num[i][j];
    }
    matrix2.setMatrix(num);
    cout << endl;

    cout << "result of += operator" << endl;//+= 연산자 실행
    matrix1.operator+=(matrix2);
    matrix1.printMatrix();//출력
    
    cout << endl << "result of -= operator" << endl;//-= 연산자 실행
    matrix1_1.operator-=(matrix2);
    matrix1_1.printMatrix();//출력

    cout << endl << "result of * operator" << endl;//* 연산자 실행
    matrix1_2.operator*(matrix2);
    matrix1_2.printMatrix();//출력

    return 0;
}