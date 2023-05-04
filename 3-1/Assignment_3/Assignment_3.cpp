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

	void setValue(int data) { this->value = data; }//숫자 저장
	int getValue() { return this->value; }//숫자 불러옴
	void setNext(Node* nextNode) { this->next = nextNode; }//다음노드 설정
	Node* getNext() { return this->next; }//다음노드 반환
	void setPrev(Node* prevNode) { this->prev = prevNode; }//이전노드 설정
	Node* getPrev() { return this->prev; }//이전노드 반환
};

class Queue {//큐 클래스 생성
private:
	Node* front;//앞 (삭제)
	Node* rear;//뒤 (삽입)
	int size;//큐 노드 개수
	int max_size;//큐 최대 길이

public:
	Queue() {//자동생성자
		this->front = NULL;//초기화
		this->rear = NULL;
		this->size = 0;
		this->max_size = 0;
	}
	~Queue() {//소멸자
		Node* curNode = rear;
		Node* delNode = NULL;
		while (curNode != NULL) {
			delNode = curNode;
			curNode = curNode->getNext();
			if (delNode == rear) {
				this->front = NULL;//초기화
				this->rear = NULL;
			}
			delete delNode;
		}
		delete curNode;
	}

	bool isEmpty();//데이터 존재 유무 확인
	bool isFull();//큐 꽉 차있는지 확인
	void reset();//초기화 (마지막 삭제)
	bool enqueue(Node* pNode);//삽입
	Node* dequeue();//삭제
	void printQueue();//출력
	void setMax_size(int data) { this->max_size = data; }//큐 최대 길이 설정
};

bool Queue::isEmpty() {
	if (this->size == 0)//비어있음
		return true;
	else
		return false;
}

bool Queue::isFull() {
	if (size == max_size)//꽉 차있음
		return true;
	else
		return false;
}

void Queue::reset() {
	rear = NULL;//쓰레기값 방지
	front = NULL;
}

bool Queue::enqueue(Node* pNode) {
	if (isEmpty()) {//queue empty
		front = rear = pNode;
		this->size++;
		return true;
	}
	else if (isFull()) {//queue full
		cout << "queue is full" << endl;
		return false;
	}
	else {
		pNode->setNext(rear);//rear 뒤에 뉴노드 삽입
		rear->setPrev(pNode);//양방향 연결
		rear = pNode;//새 노드 rear로 설정
		this->size++;
		return true;
	}
}

Node* Queue::dequeue() {
	if (isEmpty()) {//데이터 존재 X
		cout << "queue underflow" << endl;
		return NULL;
	}
	else {
		if (this->size == 1) {
			this->size--;
			return rear;
		}
		Node* dequeueNode = front;
		front = front->getPrev();//front 노드 이동 (한 칸 뒤로)
		front->setNext(NULL);//쓰레기값 방지 (초기화)
		this->size--;
		return dequeueNode;
	}
}

void Queue::printQueue() {//큐 출력
	Node* curNode = rear;

	while (curNode != NULL) {//rear부터 노드 이동하면서 출력
		cout << curNode->getValue() << "    ";
		curNode = curNode->getNext();
	}
	cout << endl << "Data count: " << this->size << endl;
	delete curNode;
}

int main() {
	char command[100];
	int data = 0;
	Queue* queue = new Queue;//큐 동적 할당
	int a = 0;
	
	cout << "Please enter maximum size of queue: ";
	cin >> data;
	queue->setMax_size(data);//큐 최대길이 설정

	while (1) {
		cout << "Please Enter Command(enqueue, dequeue, check_empty, check_full, print, exit): ";
		cin >> command;

		if (strcmp(command, "enqueue") == 0) {//enqueue
			cin >> data;

			Node* newNode = new Node;
			newNode->setValue(data);//뉴노드 데이터값 저장
			bool check = true;
			check = queue->enqueue(newNode);
			if (check == true)
				cout << "enqueue success" << endl;//삽입 성공
			else {
				cout << "enqueue unsuccess" << endl;//삽입 실패
				delete newNode;//노드 삭제
			}
		}

		else if (strcmp(command, "dequeue") == 0) {//dequeue
			Node* node = queue->dequeue();
			if (queue->isEmpty())//마지막 dequeue
				a = 1;
			if (node != NULL) {//삭제할 노드가 NULL이 아닐때
				cout << node->getValue() << endl;
				delete node;
			}
			if (a == 1)
				queue->reset();//큐 초기화
		}

		else if (strcmp(command, "check_empty") == 0) {//check_empty
			bool check = false;
			check = queue->isEmpty();
			if (check == true)
				cout << "queue is empty" << endl;
			else
				cout << "queue is not empty" << endl;
		}

		else if (strcmp(command, "check_full") == 0) {//check_full
			bool check = false;
			check = queue->isFull();
			if (check == true)
				cout << "queue is full" << endl;
			else
				cout << "queue is not full" << endl;
		}

		else if (strcmp(command, "print") == 0) {//print
			queue->printQueue();//출력
		}

		else if (strcmp(command, "exit") == 0)//exit
			break;

		else//예외
			continue;
	}

	delete queue;//동적할당 해제
	return 0;
}