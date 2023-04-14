#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
using namespace std;

class Node {
private:
	string info;//���ڿ� ����
	Node* next;//�迭
	Node* down;//nested array ����

public:
	Node() {//�ڵ�������
		this->info = {};
		this->next = NULL;
		this->down = NULL;
	}

	void setValue(string data) { this->info = data; }//���ڿ� ����
	string getValue() { return this->info; }//���ڿ� �ҷ���
	void setNext(Node* nextNode) { this->next = nextNode; }//��� ����
	Node* getNext() { return this->next; }//���� ���� �̵�
	void setDown(Node* down) { this->down = down; }//nested array ����
	Node* getDown() { return this->down; }//nested array �̵�
};

class Array {//�迭 Ŭ����
private:
	Node* start;//�迭 ����
	Node* end;//�迭 ��

public:
	Array() {//�ڵ�������
		this->start = NULL;
		this->end = NULL;
	}
	~Array() {
		Deallocate(getstart());
	}
	Node* getstart() { return start; }//�迭 ���� �ҷ���
	Node* getend() { return end; }//�迭 �� �ҷ���
	void Insert(string input);//��� ����
	void Insert_down(Array* temp_array);//nested array ����
	void Print_all(Node* curNode);//��� �迭 ���
	void Print(Node* curNode, int* num, int count);//���� ��� �˻� �� ���
	void Deallocate(Node* curNode);
};

void Array::Insert(string input) {
	Node* newNode = new Node;
	newNode->setValue(input);//���ڿ� ����

	if (start == NULL) {//ù �迭 ����
		start = end = newNode;
	}
	else {//��� ����
		end->setNext(newNode);
		end = newNode;
	}
}

void Array::Insert_down(Array* temp_array) {//nested array ����
	Node* newNode = new Node;
	end->setNext(newNode);
	end = end->getNext();

	end->setDown(temp_array->start);
}

void Array::Print_all(Node* curNode) {
	if (curNode == nullptr)
		return;

	if (curNode->getDown() != NULL) {//nested array�� ��
		cout << "[";
		Print_all(curNode->getDown());
		cout << "]";
	}
	if (curNode->getNext() == NULL) {//������ ���ڿ�
		cout << curNode->getValue();
	}
	else {
		cout << curNode->getValue() << ", ";//�߰� ���ڿ�
	}
	Print_all(curNode->getNext());//curNode �̵� �� Print_all ���ȣ��
}

void Array::Print(Node* curNode, int* num, int count) {
	Node* checkNode = new Node;

	for (int j = 0; j < count; j++) {
		for (int k = 0; k < num[j]; k++) {
			curNode = curNode->getNext();//num[j] ũ�⸸ŭ ��� ������ �̵�
		}

		checkNode = curNode;
		if (curNode->getDown() != NULL) {//������ ��ǥ�� nested array �����̶��
			curNode = curNode->getDown();
		}
	}

	if (checkNode->getValue()=="") {//������ ��ǥ�� nested array �����̶��
		cout << "[";
		Print_all(checkNode->getDown());//nested array ��� ���
		cout << "]" << endl;
	}
	else {
		cout << curNode->getValue() << endl;//���
	}
}

void Array::Deallocate(Node* curNode) {//�Ҹ�
	if (curNode == nullptr)
		return;

	if (curNode->getDown() != NULL) {
		Deallocate(curNode->getDown());//nested array ���� �Ҹ�
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
				Array* temp_array = new Array;//nested array �����Ҵ�
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
		else {//���ڰ� �ִ��
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
			array->Print_all(array->getstart());//�迭 ��� ���
			cout << "]" << endl;
		}
		else if (strcmp(input, "exit") == 0)//���α׷� ����
			break;
		else {
			int num[100]{};//�迭 �ε��� �� ����
			int count = 0;//nested array ����
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

			array->Print(array->getstart(), num, count);//���
		}
	}

	delete array;//�Ҹ�

	return 0;
}