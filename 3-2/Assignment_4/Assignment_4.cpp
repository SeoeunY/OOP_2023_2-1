#include <iostream>
using namespace std;
char variable;

class Term {
private:
    int m_Coefficient;//계수
    int m_Exponent;//차수
    Term* m_pNext;//다음 Term 포인터

public:
    Term() {//생성자
        m_Coefficient = 0;
        m_Exponent = 0;
        m_pNext = NULL;
    }
    ~Term() {//소멸자
        m_Coefficient = 0;
        m_Exponent = 0;
        m_pNext = NULL;
    }

    void SetCoeff(int coeff) { m_Coefficient = coeff; }//계수 저장
    void SetExponent(int exponent) { m_Exponent = exponent; }//계수 반환
    int GetCoeff() { return m_Coefficient; }//차수 저장
    int GetExponent() { return m_Exponent; }//차수 반환
    void SetNext(Term* pNext) { m_pNext = pNext; }//다음 Term 가리킴
    Term* GetNext() { return m_pNext; }//다음 Term 반환
};

class Polynomial {
private:
    Term* m_pHead;//Polynomial 첫 Term 가리킴

public:
    Polynomial() { m_pHead = NULL; }//생성자
    ~Polynomial() {//소멸자
        Term* curTerm = m_pHead;//연결 리스트 해제
        Term* delTerm = NULL;
        while (curTerm != NULL) {
            delTerm = curTerm;
            curTerm = curTerm->GetNext();
            delete delTerm;
        }
    }

    void Insert(Term* pTerm);//Term 삽입
    void PrintList();//리스트 출력
    void Add(Polynomial& poly);//덧셈
    void Sub(Polynomial& poly);//뺄셈
};

void Polynomial::Insert(Term* pTerm) {//Term 삽입
    if (m_pHead == NULL)//첫 삽입
        m_pHead = pTerm;
    else {//마지막 노드 찾아서 그 뒤에 삽입
        Term* curTerm = m_pHead;
        while (curTerm != NULL) {
            if (curTerm->GetNext() == NULL) {
                curTerm->SetNext(pTerm);
                return;
            }
            curTerm = curTerm->GetNext();
        }
    }
}

void Polynomial::PrintList() {//결과값 출력
    Term* curTerm = m_pHead;

    while (curTerm != NULL) {
        if ((curTerm->GetCoeff() == 1 || curTerm->GetCoeff() == -1) && curTerm->GetExponent() == 1) {//+-x
            if (curTerm == m_pHead && curTerm->GetCoeff() == -1)//첫번째 노드 음수일 때
                cout << "- ";
            cout << variable;//따로 계수, 차수 표현 X
        }
        else if (curTerm->GetExponent() == 0) {//n
            cout << curTerm->GetCoeff();
        }
        else if (curTerm->GetExponent() == 1) {//nx
            cout << curTerm->GetCoeff() << variable;
        }
        else {//nx^n
            if (curTerm->GetCoeff() == 1 || curTerm->GetCoeff() == -1) {
                cout << variable << "^" << curTerm->GetExponent();
            }
            else
                cout << curTerm->GetCoeff() << variable << "^" << curTerm->GetExponent();
        }
        curTerm = curTerm->GetNext();
        if (curTerm != NULL) {//마지막 노드 아닐 때
            if (curTerm->GetCoeff() > 0)
                cout << " + ";
            else {
                cout << " - ";
                curTerm->SetCoeff(curTerm->GetCoeff() * -1);//계수의 부호는 출력해주기 때문에 양수로 변환 후 출력
            }
        }
    }
}

Term* descending_order(Term* head) {//차수 높은 순부터 차례대로 정렬
    Term* curTerm = head;
    Term* sort = NULL;//정렬된 포인터

    while (curTerm != NULL) {
        Term* next = curTerm->GetNext();
        if (sort == NULL || curTerm->GetExponent() > sort->GetExponent()) {
            curTerm->SetNext(sort);//curTerm sort와 연결
            sort = curTerm;
        }
        else {
            Term* ptr = sort;
            while (ptr->GetNext() != NULL && ptr->GetNext()->GetExponent() > curTerm->GetExponent())//ptr이 마지막 항이거나 ptr의 다음 항의 차수가 curTerm의 차수보다 낮은 경우 while문 탈출
                ptr = ptr->GetNext();
            curTerm->SetNext(ptr->GetNext());//ptr->curTerm->ptr 다음항 연결
            ptr->SetNext(curTerm);
        }
        curTerm = next;//curTerm 한 칸 이동
    }
    return sort;
}

void Polynomial::Add(Polynomial& poly) {//덧셈
    Polynomial* result = new Polynomial;//결과로 나오는 이차식 저장
    Term* cur1 = m_pHead;
    Term* cur2 = poly.m_pHead;

    while (cur1 != NULL) {//cur1 연산 먼저하기
        bool merge = false;
        int expo = cur1->GetExponent();
        cur2 = poly.m_pHead;
        while (cur2 != NULL) {//cur2 돌면서 같은 차수 있으면 덧셈 연산 수행
            if (expo == cur2->GetExponent()) {
                Term* newTerm = new Term;
                newTerm->SetCoeff(cur1->GetCoeff() + cur2->GetCoeff());
                newTerm->SetExponent(expo);
                if (newTerm->GetCoeff() != 0)//연산한 계수가 0이 아닐 때만 result에 삽입
                    result->Insert(newTerm);
                else//연산한 계수가 0
                    delete newTerm;//할당 해제
                merge = true;
                break;
            }
            cur2 = cur2->GetNext();
        }
        if (merge == false) {//cur2에 같은 차수 없음
            Term* newTerm = new Term;//cur1 그대로 result에 저장
            newTerm->SetCoeff(cur1->GetCoeff());
            newTerm->SetExponent(expo);
            result->Insert(newTerm);
        }
        cur1 = cur1->GetNext();
    }

    cur1 = m_pHead;
    cur2 = poly.m_pHead;
    while (cur2 != NULL) {//cur2 비교해서 cur1에 포함되어있지 않은 차수항 result에 저장
        int expo = cur2->GetExponent();
        bool check = false;
        cur1 = m_pHead;
        while (cur1 != NULL) {
            if (expo == cur1->GetExponent())
                check = true;//이미 추가됨
            cur1 = cur1->GetNext();
        }
        if (check == false) {//추가 안되어 있음
            Term* newTerm = new Term;//cur2 그대로 저장
            newTerm->SetCoeff((cur2->GetCoeff()));
            newTerm->SetExponent(expo);
            result->Insert(newTerm);
        }
        cur2 = cur2->GetNext();
    }

    result->m_pHead = descending_order(result->m_pHead);//차수 내림차순 저장

    cout << "Add function : ";
    result->PrintList();//결과 출력
    cout << endl;

    delete result;//할당 해제
}

void Polynomial::Sub(Polynomial& poly) {//뺄셈 (덧셈 연산과 동일)
    Polynomial* result = new Polynomial;
    Term* cur1 = m_pHead;
    Term* cur2 = poly.m_pHead;

    while (cur1 != NULL) {
        bool merge = false;
        int expo = cur1->GetExponent();
        cur2 = poly.m_pHead;
        while (cur2 != NULL) {
            if (expo == cur2->GetExponent()) {
                Term* newTerm = new Term;
                newTerm->SetCoeff(cur1->GetCoeff() - cur2->GetCoeff());//계수 빼주기
                newTerm->SetExponent(expo);
                if (newTerm->GetCoeff() != 0)
                    result->Insert(newTerm);
                else
                    delete newTerm;
                merge = true;
                break;
            }
            cur2 = cur2->GetNext();
        }
        if (merge == false) {
            Term* newTerm = new Term;
            newTerm->SetCoeff(cur1->GetCoeff());
            newTerm->SetExponent(expo);
            result->Insert(newTerm);
        }
        cur1 = cur1->GetNext();
    }

    cur1 = m_pHead;
    cur2 = poly.m_pHead;
    while (cur2 != NULL) {
        int expo = cur2->GetExponent();
        bool check = false;
        cur1 = m_pHead;
        while (cur1 != NULL) {
            if (expo == cur1->GetExponent())
                check = true;
            cur1 = cur1->GetNext();
        }
        if (check == false) {
            Term* newTerm = new Term;
            newTerm->SetCoeff((cur2->GetCoeff()) * (-1));//뺄셈 연산이기 때문에 계수에 - 곱해서 삽입
            newTerm->SetExponent(expo);
            result->Insert(newTerm);
        }
        cur2 = cur2->GetNext();
    }

    result->m_pHead = descending_order(result->m_pHead);
    cout << "Sub function : ";
    result->PrintList();
    cout << endl;

    delete result;
}

void Classify(Polynomial& poly, char* command) {
    int num[2]{};//계수, 차수 각각 저장
    int number = 0;
    bool negative = false;
    bool variable_exist = false;
    bool save_coeff = false;
    char* ptr = command;

    while (ptr != NULL) {
        if (*ptr == ' ' || *ptr == '\0') {//차수 저장 및 insert
            if (*(ptr - 1) == '+' || *(ptr - 1) == '-') {//부호 뒤에 나오는 띄어쓰기 무시
                ptr++;
                continue;
            }
            if (*ptr == '\0') {//마지막 항 경우 고려
                if (variable_exist == false) {//미지수 없음 -> 상수
                    Term* term = new Term;
                    term->SetCoeff(number);
                    term->SetExponent(0);
                    poly.Insert(term);
                    return;
                }
                else if (*(ptr - 1) == variable) {//차수=1
                    Term* term = new Term;
                    term->SetCoeff(num[0]);
                    term->SetExponent(1);
                    poly.Insert(term);
                    return;
                }
            }

            else if (*(ptr - 1) == variable)
                number = 1;//차수=1
            if (negative == true)
                number *= -1;//음수
            if (save_coeff == false)
                num[0] = number;
            else
                num[1] = number;//차수 저장
            number = 0;//초기화
            Term* term = new Term;
            term->SetCoeff(num[0]);
            term->SetExponent(num[1]);
            poly.Insert(term);//노드 삽입
            num[0] = 0;//초기화
            num[1] = 0;
            variable_exist = false;
            negative = false;
            save_coeff = false;
            ptr++;
            continue;
        }

        if (*ptr == '-') {//음수표시
            negative = true;
        }
        else if (*ptr == '^' || *ptr == '+') {
            ptr++;
            continue;
        }
        else if (*ptr == variable) {//계수 저장
            variable_exist = true;
            if (number == 0)//계수 1이면 숫자 생략됨
                number = 1;
            if (negative == true)
                number *= -1;
            num[0] = number;//계수 저장
            save_coeff = true;
            number = 0;//초기화
        }
        else if (*ptr >= '0' && *ptr <= '9') {//숫자 저장
            number *= 10;
            number += *ptr - '0';
        }
        ptr++;
    }
}

int main()
{
    Polynomial* poly1 = new Polynomial;//리스트 2개 선언
    Polynomial* poly2 = new Polynomial;

    char command[100]{};
    cout << "Insert first polynomial : ";//첫번째 리스트 입력
    cin.getline(command, 1000, '\n');
    for (int i = 0; i < strlen(command); i++) {//미지수 확인 및 저장
        if ((command[i] >= 'a' && command[i] <= 'z') || (command[i] >= 'A' && command[i] <= 'Z')) {
            variable = command[i];
            break;
        }
    }
    Classify(*poly1, command);//리스트에 Term 저장
    
    command[0] = '\0';
    cout << "Insert second polynomial : ";//두번째 리스트 입력
    cin.getline(command, 1000, '\n');
    Classify(*poly2, command);//리스트에 Term 저장
    
    poly1->Add(*poly2);//덧셈
    poly1->Sub(*poly2);//뺄셈


    delete poly1;//메모리 해제
    delete poly2;
    return 0;
}