#include <iostream>
using namespace std;

class Node {//노드 클래스 생성
private:
	int value;//데이터값
	Node* next;//전 노드 포인터
	Node* prev;//다음 노드 포인터

public:
	Node() {//자동생성자
		this->value = 0;//초기화
		this->next = NULL;
		this->prev = NULL;
	}
	~Node() {
		this->value = 0;//초기화
		this->next = NULL;
		this->prev = NULL;
	}
	void setValue(int data) { this->value = data; }//숫자 저장
	int getValue() { return this->value; }//숫자 불러옴
	void setNext(Node* nextNode) { this->next = nextNode; }//다음노드 설정
	Node* getNext() { return this->next; }//다음노드 반환
	void setPrev(Node* prevNode) { this->prev = prevNode; }//이전노드 설정
	Node* getPrev() { return this->prev; }//이전노드 반환
};

class Stack {//스택 클래스 생성
private:
	Node* top;//최상단
	Node* bottom;//최하단
	int size;//스택 노드 개수
	int max_size;//스택 최대 노드 개수

public:
	Stack() {//자동생성자
		this->top = NULL;//초기화
		this->bottom = NULL;
		this->size = 0;
		this->max_size = 0;
	}
	~Stack() {//소멸자
		Node* curNode = top;//동적할당 해제
		Node* delNode = NULL;
		while (curNode != NULL) {
			delNode = curNode;
			curNode = curNode->getPrev();
			delete delNode;
		}
	}

	void setMax_size(int n) { max_size = n; }//스택 최대 길이 설정
	bool isEmpty();//스택 데이터값 존재 유무 판단
	bool isFull();//스택 꽉 찼는지 확인
	void reset();//쓰레기값 방지 top, tail -> NULL
	bool push(Node* pNode);//숫자 삽입
	Node* pop();//숫자 삭제
	void printStack();//스택 출력
};

bool Stack::isEmpty() {
	if (this->size == 0)//스택에 데이터값이 없다면
		return true;
	else//데이터값이 있다면
		return false;
}

bool Stack::isFull() {
	if (size == max_size)//스택이 꽉 찼다면
		return true;
	else//스택 자리가 비어 있다면
		return false;
}

void Stack::reset() {
	bottom = NULL;//쓰레기값 방지
	top = NULL;
}

bool Stack::push(Node* pNode) {//삽입
	if (isEmpty()) {//true (데이터값 존재 X)
		top = bottom = pNode;//처음 노드 삽입
		this->size++;
		return true;
	}
	else if (isFull()) {//삽입 불가
		cout << "stack is full" << endl;
		return false;
	}
	else {//false (데이터값 존재함)
		top->setNext(pNode);//순방향 노드 연결
		pNode->setPrev(top);//역방향 노드 연결
		top = top->getNext();//top 위치 변경 (한 칸 위로)
		this->size++;//사이즈 증가
		return true;
	}
}

Node* Stack::pop() {//삭제
	if (isEmpty())//데이터값 존재 X
		return NULL;
	if (this->size == 1) {//데이터값 1개 존재
		this->size--;//size=0
		return bottom;
	}
	Node* popNode = top;//삭제할 노드
	top = top->getPrev();//top 위치 변경  (한 칸 아래로)
	top->setNext(NULL);//쓰레기값 방지
	this->size--;
	return popNode;
}

void Stack::printStack() {//출력
	Node* curNode = bottom;

	while (curNode != NULL) {
		cout << curNode->getValue() << "   ";//bottom부터 출력
		curNode = curNode->getNext();//다음 노드로 이동
	}
	cout << endl;
}

int main() {
	char command[20];
	int data = 0;
	Stack* stack = new Stack;//스택 동적 할당
	int a = 0;//마지막 pop 초기화 변수

	cout << "Please enter maximum size of stack: ";
	cin >> data;
	stack->setMax_size(data);//스택 최대길이 설정

	while (1) {
		cin >> command;

		if (strcmp(command, "push") == 0) {//push
			cin >> data;
			Node* newNode = new Node;
			newNode->setValue(data);//newNode 데이터값 저장
			bool check = true;
			check = stack->push(newNode);//제대로 삽입됐는지 확인
			if (check == true)
				cout << "push success" << endl;//삽입 성공
			else {
				cout << "push unsuccess" << endl;//삽입 실패
				delete newNode;
			}
		}
		else if (strcmp(command, "pop") == 0) {//pop
			Node* node = stack->pop();
			if (stack->isEmpty())//노드 하나 남았을 때
				a = 1;
			if (node != NULL) {//삭제할 노드가 있을 때
				cout << node->getValue() << endl;
				delete node;
			}
			if (a == 1)//스택 초기화
				stack->reset();
		}

		else if (strcmp(command, "print") == 0)//print
			stack->printStack();//출력

		else if (strcmp(command, "check_empty") == 0) {//스택 비어있는지 확인
			bool check = false;
			check = stack->isEmpty();
			if (check == true)
				cout << "stack is empty" << endl;
			else
				cout << "stack is not empty" << endl;
		}

		else if (strcmp(command, "check_full") == 0) {//스택 꽉 찼는지 확인
			bool check = false;
			check = stack->isFull();
			if (check == true)
				cout << "stack is full" << endl;
			else
				cout << "stack is not full" << endl;
		}

		else if (strcmp(command, "exit") == 0)//프로그램 종료
			break;

		else
			continue;
	}

	delete stack;//동적 할당 해제
	return 0;
}