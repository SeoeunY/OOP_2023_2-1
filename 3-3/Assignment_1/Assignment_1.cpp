#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
using namespace std;

class Sale {
private:
	double Price;//가격

public:
	Sale() {//자동생성자
		Price = 0;
	}
	Sale(double ThePrice) {//생성자
		Price = ThePrice;
	}
	~Sale() {//소멸자
		Price = 0;
	}

	double GetPrice() { return Price; }
	virtual double Bill() { return Price; }
	double Savings(Sale& Other) {//다른 item 대비 얼마나 아낄 수 있는지
		return (GetPrice() - Other.GetPrice());
	}
	bool operator<(Sale& Other) {//가격 비교
		return (GetPrice() < Other.GetPrice());
	}
};

class DiscountSale : public Sale {
private:
	double Discount;//discount percentage

public:
	DiscountSale() {//자동생성자
		Discount = 0;
	}
	DiscountSale(double ThePrice, double theDiscount):Sale(ThePrice) {//생성자 (Sale 클래스 가격 저장)
		Discount = theDiscount;//할인율 저장
	}
	~DiscountSale() {//소멸자
		Discount = 0;
	}
	double GetDiscount() { return Discount; }//할인율 반환
	void SetDiscount(double theDiscount) { Discount = theDiscount; }//할인율 저장
	double Bill() {//할인률 적용된 가격
		return (GetPrice() - (GetPrice() * Discount / 100));
	}
	double Savings(DiscountSale& Other) {
		return (Bill() - Other.Bill());//virtual이기 때문에 DiscountSale 의 Bill 호출
	}
	bool operator<(DiscountSale& Other) {//가격 비교
		return (Bill() - Other.Bill());
	}
};

int main() {
	cout << "==============================" << endl;
	cout << "Price Compare Program" << endl;
	cout << "==============================" << endl;

	//물건 가격 입력
	char command[20]{};
	cout << "Insert item1 price: ";
	cin >> command;
	double item1 = (double)atof(strtok(command, "$"));
	cout << "Insert item2 price: ";
	cin >> command;
	double item2 = (double)atof(strtok(command, "$"));

	//예외처리 두 물건의 가격이 동일할 때
	if (item1 == item2) {
		cout << "Same Price" << endl;
		return 0;	
	}

	cout << "------------------------------" << endl;
	cout << "Insert discount percent: ";
	cin >> command;
	double discount = (double)atof(strtok(command, "%"));//할인율 입력
	cout << "------------------------------" << endl;
	cout << "Result:" << endl;

	DiscountSale item_1(item1, discount);
	DiscountSale item_2(item2, discount);

	if (item_1 < item_2)//두 item 크기 비교
		cout << "Discount of item1 is cheaper." << endl;
	else
		cout << "Discount of item2 is cheaper." << endl;

	cout << fixed;
	cout.precision(1);
	cout << "Saving discount price is $" << fabs(item_1.Savings(item_2)) << endl;//다른 item보다 얼마나 아낄 수 있는지

	return 0;
}