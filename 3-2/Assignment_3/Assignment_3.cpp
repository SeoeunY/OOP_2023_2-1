#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <fstream>
using namespace std;

class SongNode {
private:
	char name[100]{};
	SongNode* next = NULL;
	SongNode* prev = NULL;

public:
	void setValue(char* str) { strcpy(name, str); }//단어 저장
	char* getValue() { return name; }//단어 반환
	void setNext(SongNode* node) { this->next = node; }//다음 노드 연결
	SongNode* getNext() { return this->next; }//다음 노드 반환
	void setPrev(SongNode* node) { this->prev = node; }//이전 노드 연결
	SongNode* getPrev() { return this->prev; }//이전 노드 반환
};

class ArtistNode {
private:
	char name[100]{};//아티스트 이름
	ArtistNode* next = NULL;
	SongNode* first_song = NULL;

public:
	void setName(char* str) { strcpy(name, str); }//단어 저장
	char* getName() { return name; }//단어 반환
	void setNext(ArtistNode* node) { this->next = node; }//다음 노드 연결
	ArtistNode* getNext() { return this->next; }//다음 노드 반환

	void setSong(SongNode* node) { first_song = node; }//음악 노드 연결
	SongNode* getSong() { return first_song; }//음악 노드 반환
};

class MyMusicManagementList {
private:
	ArtistNode* head = NULL;

public:
	~MyMusicManagementList() {//소멸자
		ArtistNode* curNode = head->getNext();//head 다음 노드부터 삭제
		ArtistNode* delNode = NULL;

		while (curNode != NULL) {
			if (curNode == head) {//마지막으로 head 삭제하고 소멸자 종료
				SongNode* cur = curNode->getSong();
				SongNode* delcur = NULL;
				while (cur != NULL) {//곡 삭제
					delcur = cur;
					cur = cur->getNext();
					delete delcur;
				}
				delete curNode;
				return;
			}
			else {
				delNode = curNode;
				curNode = curNode->getNext();
				SongNode* cur = delNode->getSong();
				SongNode* delcur = NULL;
				while (cur != NULL) {//곡 삭제
					delcur = cur;
					cur = cur->getNext();
					delete delcur;
				}
				delete delNode;
			}
		}
	}

	void read();
	void insert(char* artist, char* music);
	void print();
	void print_artist();
	void search_artist(char* artist);//해당 가수 있으면 노래까지 출력
};

void MyMusicManagementList::read() {//파일입출력
	ifstream info;
	info.open("Music_Info.txt");
	if (!info)
		return;

	char list[100]{};
	info.getline(list, 100);
	while (!info.eof()) {
		list[0] = '\0';
		info.getline(list, 100);
		char* artist{};
		char* music{};
		char* ptr = strtok(list, "\t/");
		while (ptr != NULL) {
			if (artist == NULL)//가수
				artist = ptr;
			else//곡
				music = ptr;
			ptr = strtok(NULL, "\t/");
		}
		insert(artist, music);//삽입
	}

	info.close();
}

void MyMusicManagementList::insert(char* artist, char* music) {
	ArtistNode* curNode = head;
	bool loop = false;
	for (int i = 0; i < strlen(music); i++) {//대문자 있으면 소문자로 변경
		if (music[i] >= 65 && music[i] <= 90)
			music[i] += 32;
	}
	while (curNode != NULL) {
		if (loop == true)
			break;
		if (strcmp(curNode->getName(), artist) == 0) {//이미 추가되어 있는 아티스트 -> 노래만 삽입
			SongNode* cur = curNode->getSong();//cur은 해당 아티스트 첫 곡
			while (cur != NULL) {
				int comp = 0;
				comp = strcmp(music, cur->getValue());//문자열 비교
				
				if (comp < 0) {//music<cur - > cur 앞에 저장
					if (cur == curNode->getSong()) {//맨 앞 저장 (Artist node에서 곡 정보가 바뀜)
						SongNode* second = new SongNode;
						second->setValue(music);
						second->setNext(cur);
						cur->setPrev(second);
						curNode->setSong(second);
						return;//노래 저장 후 함수 탈출
					}
					else {//중간 삽입
						SongNode* second = new SongNode;
						second->setValue(music);
						cur->getPrev()->setNext(second);
						second->setPrev(cur->getPrev());
						cur->setPrev(second);
						second->setNext(cur);
						return;//노래 저장 후 함수 탈출
					}
				}
				if (cur->getNext() == NULL) {//마지막 연결
					SongNode* second = new SongNode;
					second->setValue(music);
					cur->setNext(second);
					second->setPrev(cur);
					return;//노래 저장 후 함수 탈출
				}
				else
					cur = cur->getNext();
			}
		}
		curNode = curNode->getNext();
		if (curNode == head)//모든 가수 정보 확인함
			loop = true;
	}

	ArtistNode* newNode = new ArtistNode;//새로운 가수 노드 생성
	newNode->setName(artist);
	SongNode* first = new SongNode;
	first->setValue(music);
	newNode->setSong(first);

	if (head == NULL)//첫 삽입
		head = newNode;
	else {
		curNode = head;
		loop = false;
		while (1) {
			if (curNode->getNext() == NULL) {//두번째 곡 삽입
				curNode->setNext(newNode);
				newNode->setNext(head);
				break;
			}
			else if (curNode->getNext() == head) {//head 전 노드에 새 노드 삽입
				newNode->setNext(head);
				curNode->setNext(newNode);
				break;
			}
			curNode = curNode->getNext();
		}
	}
}

void MyMusicManagementList::print() {//출력
	ArtistNode* curNode = head;
	bool loop = false;

	cout << endl;
	while (loop == false) {
		cout << "Artist : " << endl;
		cout << curNode->getName() << endl;//가수
		cout << "Song : " << endl;
		SongNode* cur = curNode->getSong();
		while (cur != NULL) {//곡 정보 출력
			cout << cur->getValue() << endl;
			cur = cur->getNext();
		}
		cout << endl;
		curNode = curNode->getNext();
		if (curNode == head)//곡 정보 모두 출력 완료
			loop = true;
	}
}

void MyMusicManagementList::print_artist() {//가수만 출력
	ArtistNode* curNode = head;
	bool loop = false;
	
	cout << endl << "Artist list : " << endl;
	while (loop == false) {
		cout << curNode->getName() << endl;
		curNode = curNode->getNext();
		if (curNode == head)
			loop = true;
	}
	cout << endl;
}

void MyMusicManagementList::search_artist(char* artist) {//특정 가수 검색
	ArtistNode* curNode = head;
	bool loop = false;

	while (loop == false) {
		if (strcmp(curNode->getName(), artist) == 0) {//동일 가수 존재
			cout << "Artist found : " << artist << endl;
			cout << "Song : " << endl;//해당 가수 곡 출력
			SongNode* cur = curNode->getSong();
			while (cur != NULL) {
				cout << cur->getValue() << endl;
				cur = cur->getNext();
			}
			cout << endl;
			return;
		}
		curNode = curNode->getNext();
		if (curNode == head)
			loop = true;
	}
	cout << "Artist NOT found" << endl;//동일 가수 없음
}

int main() {
	MyMusicManagementList* myMusic = new MyMusicManagementList;//객체 생성

	myMusic->read();//연결 리스트 생성 (노드 삽입)

	int num = 0;
	char command[50]{};

	while (1) {
		cout << "1. print all / 2. print all artist / 3. search artist / 4. exit : ";
		cin >> num;

		if (num == 1)//전체 출력 (가수, 노래)
			myMusic->print();
		else if (num == 2)//가수 출력
			myMusic->print_artist();
		else if (num == 3) {//가수 검색
			cin.getline(command, '\n');
			char* a = command + 1;//띄어쓰기 삭제
			myMusic->search_artist(a);
		}
		else if (num == 4)//프로그램 종료
			break;
		else
			continue;
	}

	delete myMusic;//할당 해제
	return 0;
}