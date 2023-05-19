#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
using namespace std;

class Person {//부모 클래스
protected:
    int age;//나이
    char name[32];//이름

public:
    Person() {
        age = 0;
        name[0] = '\0';
    }
    ~Person() {
        age = 0;
        name[0] = '\0';
    }
    virtual void Say() = 0;
};

class Student :public Person {
protected:
    char studentNum[11];//학번
    char major[32];//전공
    int schoolYear;//학년

public:
    Student() {
        studentNum[0] = '\0';
        major[0] = '\0';
        schoolYear = 0;
    }
    ~Student() {
        studentNum[0] = '\0';
        major[0] = '\0';
        schoolYear = 0;
    }
    int getAge() { return age; }
    char* getName() { return name; }
    char* getStudentNum() { return studentNum; }
    char* getMajor() { return major; }
    int getSchoolYear() { return schoolYear; }
    void setAge(int age) { this->age = age; }
    void setName(char* name) { strcpy(this->name, name); }
    void setStudentNum(char* studentNum) { strcpy(this->studentNum, studentNum); }
    void setMajor(char* major) { strcpy(this->major, major); }
    void setSchoolYear(int year) { this->schoolYear = year; }
    void Say() {//출력 함수
        cout << "<Student Information>" << endl;
        cout << "I'm a student of KW University." << endl;
        cout << "My name is " << getName() << "." << endl;
        cout << "My student number is " << getStudentNum() << "." << endl;
        cout << "I'm " << getAge() << " years old and I'm a ";
        if (getSchoolYear() == 1)
            cout << "freshman." << endl;
        else if (getSchoolYear() == 2)
            cout << "sophomore." << endl;
        else if (getSchoolYear() == 3)
            cout << "junior." << endl;
        else
            cout << "senior." << endl;
        cout << "I'm majoring in " << getMajor() << "." << endl;
    }
};

class Professor :public Person {
protected:
    char professorNum[11];//교수 넘버
    char major[32];//전공

public:
    Professor() {
        professorNum[0] = '\0';
        major[0] = '\0';
    }
    ~Professor() {
        professorNum[0] = '\0';
        major[0] = '\0';
    }

    int getAge() { return age; }
    char* getName() { return name; }
    char* getProfessorNum() { return professorNum; }
    char* getMajor() { return major; }
    void setAge(int age) { this->age = age; }
    void setName(char* name) { strcpy(this->name, name); }
    void setProfessorNum(char* professorNum) { strcpy(this->professorNum, professorNum); }
    void setMajor(char* major) { strcpy(this->major, major); }
    void Say() {//출력 함수
        cout << "<Professor Information>" << endl;
        cout << "I'm a professor of KW University." << endl;
        cout << "My name is " << getName() << "." << endl;
        cout << "My professor number is " << getProfessorNum() << "." << endl;
        cout << "I'm " << getAge() << " years old." << endl;
        cout << "I'm majoring in " << getMajor() << "." << endl;
    }
};

int main()
{
    Student* student = new Student;
    char command[50]{};
    int num = 0;

    //학생 정보 입력 및 저장
    cout << "Enter student information: " << endl;
    cout << "Name: ";
    cin.getline(command, 32, '\n');
    student->setName(command);
    cout << "Age: ";
    cin >> num;
    student->setAge(num);
    cout << "StudentNum: ";
    command[0] = '\0';
    cin >> command;
    student->setStudentNum(command);
    command[0] = '\0';
    cout << "Major: ";
    cin.getline(command, 1, '\n');
    cin.getline(command, 32, '\n');
    student->setMajor(command);
    cout << "SchoolYear: ";
    cin >> num;
    student->setSchoolYear(num);
    cout << endl << endl;

    //교수 정보 입력 및 저장
    Professor* professor = new Professor;
    cout << "Enter professor information: " << endl;
    cout << "Name: ";
    command[0] = '\0';
    cin.getline(command, 1, '\n');
    cin.getline(command, 32, '\n');
    professor->setName(command);
    cout << "Age: ";
    cin >> num;
    professor->setAge(num);
    cout << "ProfessorNum: ";
    command[0] = '\0';
    cin >> command;
    professor->setProfessorNum(command);
    cout << "Major: ";
    command[0] = '\0';
    cin.getline(command, 1, '\n');
    cin.getline(command, 32, '\n');
    professor->setMajor(command);
    cout << endl << endl;

    //저장된 정보 출력
    student->Say();
    cout << endl;
    professor->Say();

    //객체 삭제
    delete student;
    delete professor;
    return 0;
}