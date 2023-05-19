#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
using namespace std;

class Score {
private:
	Score* m_pNext;//다음 노드 포인터
	Score* m_pPrev;//이전 노드 포인터
	double m_Avg;//평균

public:
	Score() {//생성자 (초기화)
		m_pNext = NULL;
		m_pPrev = NULL;
		m_Avg = 0;
	}
	~Score() {//소멸자 (초기화)
		m_pNext = NULL;
		m_pPrev = NULL;
		m_Avg = 0;
	}

	void SetAvg(double avg) { m_Avg = avg; }
	void SetNext(Score* pNext) { m_pNext = pNext; }
	void SetPrev(Score* pPrev) { m_pPrev = pPrev; }
	double GetAvg() { return m_Avg; }
	Score* GetNext() { return m_pNext; }
	Score* GetPrev() { return m_pPrev; }
};

class StudentScoreList {
private:
	Score* m_pHead;//첫 노드 가리킴
	Score* m_pTail;//마지막 노드 가리킴

public:
	StudentScoreList() {//생성자
		m_pHead = NULL;
		m_pTail = NULL;
	}
	~StudentScoreList() {//소멸자 (할당 해제)
		Score* cur = m_pHead;
		Score* del = NULL;
		while (cur != NULL) {
			del = cur;
			cur = cur->GetNext();
			delete del;
		}
		delete cur;
	}

	void Insert(Score* pScore);//노드 삽입
	void PrintList(bool isAscending);//출력
};

void StudentScoreList::Insert(Score* pScore) {//노드 삽입
	if (m_pHead == NULL) {//첫 삽입
		m_pHead = m_pTail = pScore;
	}
	else {
		Score* cur = m_pHead;
		while (cur != NULL) {
			if (cur->GetAvg() >= pScore->GetAvg()) {
				if (cur == m_pHead) {//맨 앞 삽입
					pScore->SetNext(cur);
					cur->SetPrev(pScore);
					m_pHead = pScore;
					return;
				}
				else {//중간 삽입
					cur->GetPrev()->SetNext(pScore);
					pScore->SetNext(cur);
					pScore->SetPrev(cur->GetPrev());
					cur->SetPrev(pScore);
					return;
				}
			}
			if (cur->GetNext() == NULL) {//마지막 삽입
				cur->SetNext(pScore);
				pScore->SetPrev(cur);
				m_pTail = pScore;
				return;
			}
			cur = cur->GetNext();
		}
	}
}

void StudentScoreList::PrintList(bool isAsecding) {
	if (isAsecding == true) {//오름차순
		Score* cur = m_pHead;
		while (cur != NULL) {
			cout << cur->GetAvg() << "   ";
			cur = cur->GetNext();
		}
	}
	else {//내림차순
		Score* cur = m_pTail;
		while (cur != NULL) {
			cout << cur->GetAvg() << "   ";
			cur = cur->GetPrev();
		}
	}
	cout << endl;
}

double insert(char* score) {//평균 계산
	double num[20]{};
	char* ptr = strtok(score, " ");//공백 기준 문자열 자르기
	int i = 0;
	while (ptr != NULL) {
		num[i] = (double)atof(ptr);//double형으로 형변환
		ptr = strtok(NULL, " ");
		i++;
	}
	double t_score = 0;
	for (int j = 0; j < i; j++)//평균 계산
		t_score += num[j];
	t_score /= i;
	return t_score;
}

int main() {
	StudentScoreList* Score_list = new StudentScoreList;//연결 리스트 객체 생성
	int command = 0;
	char score[1000]{};
	
	while (1) {
		cout << "1. insert 2. print 3. exit : ";
		cin >> command;

		if (command == 1) {//삽입
			cin.getline(score, 1000, '\n');//숫자 입력
			char* temp = score + 1;
			double t_score = insert(score);//평균 계산
			Score* pScore = new Score;//노드 생성
			pScore->SetAvg(t_score);//평균 저장
			Score_list->Insert(pScore);//노드 삽입
			continue;
		}
		else if (command == 2) {//출력
			cout << "1. ascending 2. descending : ";
			cin >> command;
			if (command == 1)//오름차순 출력
				Score_list->PrintList(true);
			else if (command == 2)//내림차순 출력
				Score_list->PrintList(false);
		}
		else if (command == 3)//프로그램 종료
			break;
		else
			continue;
	}
	delete Score_list;//객체 삭제
	return 0;
}