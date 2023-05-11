#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

class Node {//노드 클래스
private:
    int num = 0;//숫자
	Node* next = NULL;//포인터
	Node* prev = NULL;

public:
	void setValue(int data) { this->num = data; }
	int getValue() { return this->num; }
	void setNext(Node* nextNode) { this->next = nextNode; }
	Node* getNext() { return this->next; }
	void setPrev(Node* prevNode) { this->prev = prevNode; }
	Node* getPrev() { return this->prev; }
};

class Binary {//숫자 16개 저장 리스트
private:
	Node* head;//맨 앞 노드
	int size = 0;

public:
	Binary() {//초기화
		head = NULL;
	}
	~Binary() {//할당 해제
		Node* curNode = head;
		Node* delNode = NULL;

		while (curNode != NULL) {
			delNode = curNode;
			curNode = curNode->getNext();
			delete delNode;
		}
		delete curNode;
	}

	int getSize() { return size; }
	bool insert(int num);
	void print();
	Node* getHead() { return head; }
	void setHead(Node* p) { head = p; }
};

bool Binary::insert(int num) {//리스트에 노드 삽입
	Node* curNode = head;

	for (int i = 0; i < size; i++) {//숫자 중복 확인
		if (num == curNode->getValue()) {//같을 경우 삽입 안하고 return
			return false;
		}
		curNode = curNode->getNext();
	}

	Node* newNode = new Node;//새 노드 생성
	newNode->setValue(num);
	curNode = head;
	if (size == 0) {//첫 삽입
		head =  newNode;
		size++;
		return true;
	}
	else {//뒤에 연결
		while (curNode != NULL) {
			if (curNode->getNext() == NULL) {
				curNode->setNext(newNode);
				newNode->setPrev(curNode);
				size++;
				return true;
			}
			curNode = curNode->getNext();
		}
	}
	return false;
}

void Binary::print() {//리스트 출력
	Node* curNode = head;
	while (curNode != NULL) {
		cout << curNode->getValue() << "  ";
		curNode = curNode->getNext();
	}
}

Node* Insertion_sort(Node* p) {//insertion sort
	Node* head = p;
	Node* curNode = p;

	while (curNode != NULL) {
		Node* comp = head;
		while (comp != curNode) {
			if (curNode->getValue() > comp->getValue()) {//comp 앞에 curNode 삽입
				if (comp == head) {//맨앞에 삽입
					if (curNode->getNext() != NULL) {//curNode 중간에 위치
						Node* prev = curNode->getPrev();
						Node* next = curNode->getNext();
						prev->setNext(next);
						next->setPrev(prev);
					}
					else//curNode=마지막 노드
						curNode->getPrev()->setNext(NULL);
					curNode->setNext(comp);//삽입
					comp->setPrev(curNode);
					head = curNode;
					curNode->setPrev(NULL);
				}
				else {
					if (curNode->getNext() != NULL) {//curNode 중간에 위치
						Node* prev = curNode->getPrev();
						Node* next = curNode->getNext();
						prev->setNext(next);
						next->setPrev(prev);
					}
					else//curNode=마지막 노드
						curNode->getPrev()->setNext(NULL);
					comp->getPrev()->setNext(curNode);//중간 삽입
					curNode->setNext(comp);
					curNode->setPrev(comp->getPrev());
					comp->setPrev(curNode);
				}
				break;
			}
			comp = comp->getNext();
		}

		curNode = curNode->getNext();
	}
	p = head;
	return p;
}

Node* Binary_Search(Node* p, int n) {//binary search 함수
	p = Insertion_sort(p);//내림차순 정렬

	cout << "Binary after insertion sort :" << endl;
	Node* z = p;
	while (z != NULL) {
		cout << z->getValue() << "   ";
		z = z->getNext();
	}
	cout << endl << endl;

	Node* p_copy = p;
	int L = 0;
	int H = 15;
	int mid = 0;

	while (L <= H && p->getValue() != n) {//binary search algorithm 탈출 조건
		p = p_copy;
		mid = (L + H) / 2;//mid부터 탐색
		for (int i = 0; i < mid; i++)
			p = p->getNext();
		cout << p->getValue() << " -> ";
		if (p->getValue() > n)//n은 mid 오른쪽에 위치
			L = mid + 1;
		else if (p->getValue() < n)//n은 mid 왼쪽에 위치
			H = mid - 1;
	}
	cout << endl;

	if (p->getValue() == n) {//탐색 성공
		cout << "Binary search succesful! Node num : " << mid + 1 << endl;
		return p;
	}
	else {//탐색 실패
		cout << "Binary search unsuccesful!" << endl << "closest node num : ";
		Node* a = p_copy;
		Node* b = p_copy;
		if (H == -1) {//첫번째 노드보다 큰 수를 탐색할 때
			cout << "1" << endl;
			cout << "closest number : ";
			return p;
		}
		else if (L == 16) {//마지막 노드보다 작은 수를 탐색할 때
			cout << "16" << endl;
			Node* curNode = p;
			while (curNode != NULL) {
				if (curNode->getNext() == NULL) {
					cout << "closest number : ";
					break;
				}
				curNode = curNode->getNext();
			}
			return curNode;
		}
		//찾는 수가 노드 2개 사이에 존재할 때
		for (int z = 0; z < L; z++)
			a = a->getNext();
		for (int z = 0; z < H; z++)
			b = b->getNext();
		int c = n - a->getValue();//숫자 차 비교
		int d = b->getValue() - n;
		if (c >= d) {//차가 더 작은 노드 반환
			cout << H + 1 << endl;
			cout << "closest number : ";
			return b;
		}
		else if (c < d) {
			cout << L + 1 << endl;
			cout << "closest number : ";
			return a;
		}
	}
}

int main()
{
	Binary* binary = new Binary;//객체 생성
	bool check = true;

	srand((unsigned int)time(NULL));//난수 생성
	for (int i = 0; i < 16; i++) {
		check = binary->insert(rand() % 201);
		if (check == false)//insert 안됐으면 숫자 감소 (최종적으로 16개 노드 생성)
			i--;
	}

	cout << "Binary before insertion order :" << endl;//처음 리스트 출력
	binary->print();

	int n = 0;
	cout << endl << endl << "enter the number that you want to search : ";//탐색 숫자 입력
	cin >> n;

	cout << "Result :" << endl;
	Node* printNode = Binary_Search(binary->getHead(), n);//binary search 함수 호출
	cout << printNode->getValue() << endl;//반환받은 노드 출력

	Node* curNode = binary->getHead();//binary head 탐색
	while (curNode != NULL) {
		if (curNode->getPrev() == NULL) {
			binary->setHead(curNode);
			break;
		}
		curNode = curNode->getPrev();
	}

	delete binary;//할당 해제
	return 0;
}