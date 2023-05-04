#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
using namespace std;

class Node {
private:
	char str[100]="";//단어 저장
	Node* next = NULL;//다음 노드 포인터
	Node* prev = NULL;//이전 노드 포인터

public:
	void setValue(char* str) { strcpy(this->str, str); }//단어 저장
	char* getValue() { return this->str; }//단어 반환
	void setNext(Node* node) { this->next = node; }//다음 노드 연결
	Node* getNext() { return this->next; }//다음 노드 반환
	void setPrev(Node* node) { this->prev = node; }//이전 노드 연결
	Node* getPrev() { return this->prev; }//이전 노드 반환

	Node* insert(Node* p, char* ptr);//노드 삽입
	Node* merge_list(Node* p, Node* node);//p3 연결 (실제 노드 연결)
	int compare(char* str1, char* str2);//단어 크기 비교
	Node* merge(Node* p1, Node* p2, Node* p3);//p1, p2 비교해 merge_list() 호출
	void print(Node* p);//문장 출력
	void deallocate(Node* p);//메모리 해제
};

int Node::compare(char* str1, char* str2) {
	bool a = true;
	bool b = true;
	int arr1[100]{};
	int arr2[100]{};
	int j = 0;
	int k = 0;
	for (int i = 0; i < strlen(str1); i++) {//대문자 있으면 소문자로 변경
		if (str1[i] >= 65 && str1[i] <= 90) {
			str1[i] += 32;
			arr1[j] = i;
			j++;
			a = false;
		}
	}
	
	for (int i = 0; i < strlen(str2); i++) {//대문자 있으면 소문자로 변경
		if (str2[i] >= 65 && str2[i] <= 90) {
			str2[i] += 32;
			arr2[k] = i;
			k++;
			b = false;
		}
	}

	int comp = 0;
	comp = strcmp(str1, str2);//문자열 비교
	if (a == false) {//소문자 대문자로 변경
		for (int i = 0; i < j; i++)
			str1[arr1[j]] -= 32;
	}
	if (b == false) {//소문자 대문자로 변경
		for (int i = 0; i < k; i++)
			str2[arr2[k]] -= 32;
	}
	return comp;
}

Node* Node::insert(Node* p, char* ptr) {//노드 삽입
	Node* curNode = p;
	Node* newNode = new Node;
	newNode->setValue(ptr);

	if (curNode == NULL) {//첫 노드 삽입
		p = newNode;
		return p;
	}
	else {
		while (curNode != NULL) {
			int a = compare(curNode->getValue(),ptr);
			if (a>0) {
				if (curNode == p) {//맨 앞에 삽입
					newNode->setNext(curNode);//새 노드 순방향 연결
					curNode->setPrev(newNode);//역방향 연결
					p = newNode;//head 재설정
					return p;
				}
				else {//중간 삽입
					curNode->getPrev()->setNext(newNode);//curNode의 전노드의 next 포인터 new노드로 연결
					newNode->setPrev(curNode->getPrev());//newNode의 prev, curNode 전 노드로 연결
					//newNode와 curNode 연결
					curNode->setPrev(newNode);
					newNode->setNext(curNode);
					return p;
				}
			}
			if (curNode->getNext() == NULL) {//마지막 연결
				curNode->setNext(newNode);
				newNode->setPrev(curNode);
				return p;
			}
			else//포인터 이동
				curNode = curNode->getNext();
		}
	}
	return p;
}

Node* Node::merge_list(Node* p, Node* node) {//p3에 노드 삽입
	if (p == NULL) {//첫 삽입
		p = node;
		p->setNext(NULL);
		return p;
	}
	else {
		Node* curNode = p;
		while (1) {
			if (curNode->getNext() == NULL) {//맨 뒤에 노드 삽입
				curNode->setNext(node);
				node->setPrev(curNode);
				node->setNext(NULL);
				return p;
			}
			else
				curNode = curNode->getNext();//노드 이동
		}
		return p;
	}
}

Node* Node::merge(Node* p1, Node* p2, Node* p3) {//p1, p2 노드 비교
	Node* node = NULL;
	Node* merge = NULL;

	while (p1 != NULL && p2 != NULL) {//둘이 비교
		int a = compare(p1->getValue(), p2->getValue());
		if (a >= 0) {//p2 작아
			merge = p2;
			node = p2->getNext();//p2 포인터 이동
			p2->setNext(NULL);
			if (p2->getPrev() != nullptr)
				p2->setPrev(NULL);
			p3 = merge_list(p3,merge);
			p2 = node;
		}
		else if (a < 0) {//p1 작아
			merge = p1;
			node = p1->getNext();
			p1->setNext(NULL);
			if (p1->getPrev() != nullptr)
				p1->setPrev(NULL);
			p3 = merge_list(p3, merge);
			p1 = node;
		}
	}

	while (p1 != NULL) {//p2 다 끝남
		merge = p1;
		if (p1->getNext() == NULL) {
			p1->setPrev(NULL);
			p3 = merge_list(p3, merge);
			break;
		}
		node = p1->getNext();
		p3 = merge_list(p3, merge);
		p1 = node;
	}
	while (p2 != NULL) {//p1 다 끝남
		merge = p2;
		if (p2->getNext() == NULL) {
			p2->setPrev(NULL);
			p3 = merge_list(p3, merge);
			break;
		}
		node = p2->getNext();
		p3 = merge_list(p3, merge);
		p2 = node;
	}

	return p3;
}

void Node::print(Node* p) {//문장 출력
	Node* node = p;
	while (node != NULL) {
		cout << node->getValue() << " ";
		node = node->getNext();
	}
}

void Node::deallocate(Node* p) {//메모리 해제
	Node* curNode = p;
	Node* delNode = NULL;

	while (curNode != NULL) {
		delNode = curNode;
		curNode = curNode->getNext();
		delete delNode;
	}
	delete curNode;
}


int main()
{
	Node* p1 = NULL;
	Node* p2 = NULL;
	Node* p3 = NULL;

	char str1[1000]{};
	char str2[1000]{};

	cout << "Input>>" << endl;
	cout << "Input list 1: ";
	cin.getline(str1, 1000, '\n');
	cout << "Input list 2: ";
	cin.getline(str2, 1000, '\n');

	char* ptr1 = strtok(str1, " ");
	while (ptr1 != NULL) {//p1 연결
		p1 = p1->insert(p1, ptr1);
		ptr1 = strtok(NULL, " ");
	}

	char* ptr2 = strtok(str2, " ");
	while (ptr2 != NULL) {//p2 연결
		p2 = p2->insert(p2, ptr2);
		ptr2 = strtok(NULL, " ");
	}

	p3 = p3->merge(p1, p2, p3);//p3에 merge

	cout << "Output>>" << endl << "Result: ";
	p3->print(p3);//p3 출력
	cout << endl;

	p3->deallocate(p3);//p3 메모리 해제

	return 0;
}