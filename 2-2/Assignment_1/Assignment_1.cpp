#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
using namespace std;

class Node {
private:
	string info;//문자열 저장
	Node* next;//배열
	Node* down;//nested array 연결

public:
	Node() {//자동생성자
		this->info = {};
		this->next = NULL;
		this->down = NULL;
	}

	void setValue(string data) { this->info = data; }//문자열 저장
	string getValue() { return this->info; }//문자열 불러옴
	void setNext(Node* nextNode) { this->next = nextNode; }//노드 연결
	Node* getNext() { return this->next; }//다음 노드로 이동
	void setDown(Node* down) { this->down = down; }//nested array 연결
	Node* getDown() { return this->down; }//nested array 이동
};

class Array {//배열 클래스
private:
	Node* start;//배열 시작
	Node* end;//배열 끝

public:
	Array() {//자동생성자
		this->start = NULL;
		this->end = NULL;
	}
	~Array() {
		Deallocate(getstart());
	}
	Node* getstart() { return start; }//배열 시작 불러옴
	Node* getend() { return end; }//배열 끝 불러옴
	void Insert(string input);//노드 삽입
	void Insert_down(Array* temp_array);//nested array 연결
	void Print_all(Node* curNode);//모든 배열 출력
	void Print(Node* curNode, int* num, int count);//구성 요소 검색 및 출력
	void Deallocate(Node* curNode);
};

void Array::Insert(string input) {
	Node* newNode = new Node;
	newNode->setValue(input);//문자열 저장

	if (start == NULL) {//첫 배열 저장
		start = end = newNode;
	}
	else {//노드 연결
		end->setNext(newNode);
		end = newNode;
	}
}

void Array::Insert_down(Array* temp_array) {//nested array 저장
	Node* newNode = new Node;
	end->setNext(newNode);
	end = end->getNext();

	end->setDown(temp_array->start);
}

void Array::Print_all(Node* curNode) {
	if (curNode == nullptr)
		return;

	if (curNode->getDown() != NULL) {//nested array로 들어가
		cout << "[";
		Print_all(curNode->getDown());
		cout << "]";
	}
	if (curNode->getNext() == NULL) {//마지막 문자열
		cout << curNode->getValue();
	}
	else {
		cout << curNode->getValue() << ", ";//중간 문자열
	}
	Print_all(curNode->getNext());//curNode 이동 후 Print_all 재귀호출
}

void Array::Print(Node* curNode, int* num, int count) {
	Node* checkNode = new Node;

	for (int j = 0; j < count; j++) {
		for (int k = 0; k < num[j]; k++) {
			curNode = curNode->getNext();//num[j] 크기만큼 노드 옆으로 이동
		}

		checkNode = curNode;
		if (curNode->getDown() != NULL) {//움직인 좌표가 nested array 시작이라면
			curNode = curNode->getDown();
		}
	}

	if (checkNode->getValue()=="") {//움직인 좌표가 nested array 시작이라면
		cout << "[";
		Print_all(checkNode->getDown());//nested array 모두 출력
		cout << "]" << endl;
	}
	else {
		cout << curNode->getValue() << endl;//출력
	}
}

void Array::Deallocate(Node* curNode) {//소멸
	if (curNode == nullptr)
		return;

	if (curNode->getDown() != NULL) {
		Deallocate(curNode->getDown());//nested array 들어가서 소멸
		curNode->setDown(NULL);
		curNode = curNode->getNext();
	}

	Node* delNode = new Node;
	delNode = curNode;
	Deallocate(curNode->getNext());
	delete delNode;
}

int i;
void word(Array* array, char* input, string temp_str) {
	for (; i < strlen(input); i++) {
		if (input[i] == '[') {
			if (i == 0)
				continue;
			else {
				Array* temp_array = new Array;//nested array 동적할당
				i++;
				word(temp_array, input, temp_str);
				array->Insert_down(temp_array);
			}
		}
		else if (input[i] == ']') {
			if (temp_str != "") {
				array->Insert(temp_str);
				temp_str = "";
			}
			return;
		}
		else if (input[i] == ',') {
			i++;
			if (temp_str != "") {
				array->Insert(temp_str);
				temp_str = "";
			}
		}
		else {//문자가 있대요
			temp_str.push_back(input[i]);
		}
	}
}

int main()
{
	Array* array = new Array;
	char input[100001]{};
	string temp_str = "";

	cin.getline(input, 10001, '\n');

	word(array, input, temp_str);

	while (1) {
		input[0] = {};
		temp_str = "";

		cin >> input;

		if (strcmp(input, "arr") == 0) {
			cout << "[";
			array->Print_all(array->getstart());//배열 모두 출력
			cout << "]" << endl;
		}
		else if (strcmp(input, "exit") == 0)//프로그램 종료
			break;
		else {
			int num[100]{};//배열 인덱스 값 저장
			int count = 0;//nested array 개수
			temp_str = "";
			for (int k = 3; k < strlen(input); k++) {
				if (input[k] == '[') {
					k++;
					while (input[k] != ']') {
						temp_str.push_back(input[k]);
						k++;
					}
					num[count] = stoi(temp_str);
					temp_str = "";
					count++;
				}
			}

			array->Print(array->getstart(), num, count);//출력
		}
	}

	delete array;//소멸

	return 0;
}